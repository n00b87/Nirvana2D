#include "Nirvana_Project.h"
#include <wx/wx.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/arrstr.h>

Nirvana_Project::Nirvana_Project()
{
	project_filename_obj = wxFileName(_(""));
	this->active = false;
}

std::vector<nirvana_project_file_obj> Nirvana_Project::getParams(wxString p_data)
{
	std::vector<nirvana_project_file_obj> dlist;

	nirvana_project_file_obj dlist_obj;

	std::vector<nirvana_project_dict_obj> dict;
	nirvana_project_dict_obj dict_obj;
	dict_obj.key = _("");
	dict_obj.val = _("");

	p_data.Replace(_(";"), _(" ;"));
	p_data.Replace(_("\n"), _(""));
	p_data.Replace(_("\r"), _(""));
	p_data.Replace(_("\t"), _(" "));

	bool isKey = true;

	bool in_quotes = false;

	bool dbg_out = false;
	int dbg_index = 0;


	for(int i = 0; i < p_data.length(); i++)
	{
		if(p_data.substr(i, 1).compare(_(";"))==0)
		{
			dlist.push_back(dlist_obj);
			dlist_obj.dict.clear();

			//clear parameters
			dict_obj.key = _("");
			dict_obj.val = _("");
			continue;
		}

		if( (in_quotes && p_data.substr(i, 1).compare(_("\""))==0) || ((!in_quotes) && p_data.substr(i, 1).compare(_(" "))==0) )
		{
			/*if(dict_obj.val.compare(_("sydney"))==0)
			{
				dbg_out = true;
				dbg_index = dlist.size();
			}*/

			if(dict_obj.key.compare(_(""))!=0)
				dlist_obj.dict.push_back(dict_obj);
			dict_obj.key = _("");
			dict_obj.val = _("");
			isKey = true;
			in_quotes = false;
		}
		else if(p_data.substr(i, 1).compare(_("="))==0)
		{
			isKey = false;
		}
		else if(p_data.substr(i, 1).compare(_("\""))==0)
		{
			in_quotes = true;
		}
		else if(isKey)
		{
			dict_obj.key.Append(p_data.substr(i,1));
		}
		else
		{
			dict_obj.val.Append(p_data.substr(i,1));
		}
	}

	return dlist;
}

std::vector<wxString> Nirvana_Project::delimArgs(wxString args)
{
	args += _(",");
	std::vector<wxString> arg_array;

	wxString n_arg = _("");

	for(int i = 0; i < args.length(); i++)
	{
		if(args.substr(i,1).compare(_(","))==0)
		{
			if(n_arg.Trim().compare(_(""))!=0)
				arg_array.push_back(n_arg);
			n_arg = _("");
		}
		else
			n_arg += args.substr(i,1);
	}

	return arg_array;
}

wxString Nirvana_Project::getDir()
{
	wxFileName d_path = project_filename_obj;
	d_path.SetFullName(_(""));
	return d_path.GetAbsolutePath();
}

wxString Nirvana_Project::getFileName()
{
	return project_filename_obj.GetFullName();
}

bool Nirvana_Project::checkName(std::string t_name)
{
	wxString test_name = wxString(t_name).Trim();

	if(test_name.length()==0)
		return false;

	std::vector<std::string> restricted_char;
	restricted_char.push_back("[");
	restricted_char.push_back("]");
	restricted_char.push_back("\n");
	restricted_char.push_back("\r");

	for(int i = 0; i < test_name.length(); i++)
	{
		for(int rc = 0; rc < restricted_char.size(); rc++)
		{
			if(restricted_char[rc].compare(test_name.substr(i,1))==0)
				return false;
		}
	}

	return true;
}

void Nirvana_Project::resetIncludeFlags()
{
	for(int i = 0; i < sprite_base.size(); i++)
	{
		sprite_base[i].include_flag = false;
	}
}


bool Nirvana_Project::createSprite(wxString spr_id, wxString img_file, int frame_width, int frame_height)
{
	wxString check_id = spr_id.Lower().Trim();

	for(int i = 0; i < sprite_base.size(); i++)
	{
		if(check_id.compare(sprite_base[i].sprite_name.Lower().Trim())==0)
			return false;
	}

	Nirvana_SpriteBase obj;
	obj.sprite_name = spr_id.Trim();
	obj.file = img_file;
	obj.object.frame_size.set(frame_width, frame_height);
	obj.object.active = true;
	obj.object.image_id = -1;
	obj.unique_id = obj_uid_counter;
	obj_uid_counter++;

	sprite_base.push_back(obj);

	return true;
}

int Nirvana_Project::loadSpriteDefinition(wxString spr_file)
{
	Nirvana_SpriteBase obj;
	obj.sprite_name = _("sprite");
	obj.file = spr_file;
	obj.object.frame_size.set(32, 32); //32 is default for now
	obj.object.active = true;
	obj.object.image_id = -1;
	obj.unique_id = obj_uid_counter;
	obj_uid_counter++;


	wxFileName fname(getDir());
	fname.AppendDir(sprite_path);

	wxFileName pfile_fname = fname;
	pfile_fname.SetFullName(spr_file.Trim() + _(".sprite"));

	wxFile pfile(pfile_fname.GetAbsolutePath(), wxFile::read);

	if(pfile.IsOpened())
	{
		wxString p_data = _("");
		pfile.ReadAll(&p_data);
		pfile.Close();

		std::vector<nirvana_project_file_obj> p_cmd = getParams(p_data);

		for(int i = 0; i < p_cmd.size(); i++)
		{
			if(p_cmd[i].dict.size() == 0)
				continue;

			if(p_cmd[i].dict[0].key.compare(_("SPRITE"))==0)
			{
				for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
				{
					if(p_cmd[i].dict[obj_index].key.compare(_("name"))==0)
					{
						obj.sprite_name = p_cmd[i].dict[obj_index].val;
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("frame_size"))==0)
					{
						std::vector<wxString> args = delimArgs(p_cmd[i].dict[obj_index].val);
						obj.object.frame_size.set(32, 32); //default size

						if(args.size() >= 2)
						{
							int frame_width = 0;
							int frame_height = 0;
							args[0].ToInt(&frame_width);
							args[1].ToInt(&frame_height);
							obj.object.frame_size.set(frame_width, frame_height);
						}
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("detached_shape"))==0)
					{
						obj.object.physics.detached = p_cmd[i].dict[obj_index].val.Upper().compare(_("TRUE"))==0 ? true : false;
					}
				}
			}
			else if(p_cmd[i].dict[0].key.compare(_("SHAPE"))==0)
			{
				for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
				{
					if(p_cmd[i].dict[obj_index].key.compare(_("type"))==0)
					{
						if(p_cmd[i].dict[obj_index].val.compare(_("SPRITE_SHAPE_BOX"))==0)
						{
							obj.object.physics.shape_type = SPRITE_SHAPE_BOX;
						}
						else if(p_cmd[i].dict[obj_index].val.compare(_("SPRITE_SHAPE_CIRCLE"))==0)
						{
							obj.object.physics.shape_type = SPRITE_SHAPE_CIRCLE;
						}
						else if(p_cmd[i].dict[obj_index].val.compare(_("SPRITE_SHAPE_CHAIN"))==0)
						{
							obj.object.physics.shape_type = SPRITE_SHAPE_CHAIN;
						}
						else if(p_cmd[i].dict[obj_index].val.compare(_("SPRITE_SHAPE_POLYGON"))==0)
						{
							obj.object.physics.shape_type = SPRITE_SHAPE_POLYGON;
						}
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("size"))==0)
					{
						std::vector<wxString> args = delimArgs(p_cmd[i].dict[obj_index].val);

						if(args.size() >= 2)
						{
							int b_width = 0;
							int b_height = 0;
							args[0].ToInt(&b_width);
							args[1].ToInt(&b_height);
							//std::cout << " sprite_shape: " << b_width << ", " << b_height << std::endl;
							obj.object.physics.box_width = b_width;
							obj.object.physics.box_height = b_height;
						}
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("point"))==0)
					{
						std::vector<wxString> args = delimArgs(p_cmd[i].dict[obj_index].val);

						obj.object.physics.offset_x = 0;
						obj.object.physics.offset_y = 0;

						if(args.size() >= 2)
						{
							int x = 0;
							int y = 0;
							args[0].ToInt(&x);
							args[1].ToInt(&y);

							// offset is ignored for chain and polygon
							obj.object.physics.offset_x = x;
							obj.object.physics.offset_y = y;

							// points are ignored for box and circle
							obj.object.physics.points.push_back( irr::core::vector2di(x, y) );
						}
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("radius"))==0)
					{
						p_cmd[i].dict[obj_index].val.ToDouble(&obj.object.physics.radius);
					}
				}
			}
			else if(p_cmd[i].dict[0].key.compare(_("ANIMATION"))==0)
			{
				sprite2D_animation_obj ani_obj;
				for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
				{
					if(p_cmd[i].dict[obj_index].key.compare(_("name"))==0)
					{
						ani_obj.name = p_cmd[i].dict[obj_index].val.ToStdString();
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("frame_count"))==0)
					{
						p_cmd[i].dict[obj_index].val.ToInt(&ani_obj.num_frames);
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("fps"))==0)
					{
						p_cmd[i].dict[obj_index].val.ToDouble(&ani_obj.fps);
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("frame"))==0)
					{
						std::vector<wxString> args = delimArgs(p_cmd[i].dict[obj_index].val);

						ani_obj.frames.clear();
						for(int arg_index = 0; arg_index < args.size(); arg_index++)
						{
							int frame_value = 0;
							args[arg_index].ToInt(&frame_value);
							ani_obj.frames.push_back(frame_value);
						}
					}
				}

				obj.object.animation.push_back(ani_obj);
			}
		}
	}
	else
		return -1;

	wxString check_id = obj.sprite_name.Trim();
	int n = 1;

	for(int i = 0; i < sprite_base.size(); i++)
	{
		if(i < 0)
			continue;

		if(check_id.Lower().Trim().compare(sprite_base[i].sprite_name.Lower().Trim())==0)
		{
			check_id = obj.sprite_name.Trim() + wxString::Format(_("%i"), n);
			n++;
			i = -1;
		}
	}

	obj.sprite_name = check_id;
	obj.object.physics.init = true;

	//std::cout << "Physics check: " << obj.object.physics.offset_x << ", " << obj.object.physics.offset_y << std::endl;

	int sprite_index = sprite_base.size();
	sprite_base.push_back(obj);

	return sprite_index;
}

Nirvana_SpriteBase Nirvana_Project::getSprite(int spr_index)
{
	if(spr_index >= 0 && spr_index < sprite_base.size())
	{
		return sprite_base[spr_index];
	}

	Nirvana_SpriteBase obj;
	obj.object.active = false;
	return obj;
}

void Nirvana_Project::setSpriteObject(int spr_index, sprite2D_obj obj)
{
	if(spr_index >= 0 && spr_index < sprite_base.size())
	{
		if(sprite_base[spr_index].object.physics.init)
		{
			sprite2D_physics_obj physics = sprite_base[spr_index].object.physics;
			sprite_base[spr_index].object = obj;
			sprite_base[spr_index].object.physics = physics;
		}
		else
		{
			sprite_base[spr_index].object = obj;
			sprite_base[spr_index].object.physics.init = true;
		}
	}
}

void Nirvana_Project::setSpritePhysics(int spr_index, sprite2D_physics_obj obj)
{
	if(spr_index >= 0 && spr_index < sprite_base.size())
	{
		sprite_base[spr_index].object.physics = obj;
	}
}

sprite2D_physics_obj Nirvana_Project::getSpritePhysics(int spr_index)
{
	if(spr_index >= 0 && spr_index < sprite_base.size())
	{
		return sprite_base[spr_index].object.physics;
	}
	sprite2D_physics_obj obj;
	return obj;
}

void Nirvana_Project::setSpriteName(int  spr_index, std::string spr_name)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return;

	sprite_base[spr_index].sprite_name = spr_name;
}

void Nirvana_Project::setSpriteAnimationName(int spr_index, int animation_index, std::string ani_name)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return;

	if(animation_index < 0 || animation_index >= sprite_base[spr_index].object.animation.size())
		return;

	sprite_base[spr_index].object.animation[animation_index].name = ani_name;
}

void Nirvana_Project::deleteSprite(int spr_index)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return;


	int base_unique_id = sprite_base[spr_index].unique_id;
	sprite_base.erase(sprite_base.begin() + spr_index);

	//delete all instances of base sprite
	for(int stage_index = 0; stage_index < stages.size(); stage_index++)
	{
		for(int layer_index = 0; layer_index < stages[stage_index].layers.size(); layer_index++)
		{
			for(int i = 0; i < stages[stage_index].layers[layer_index].layer_sprites.size(); i++)
			{
				if(i < 0)
					continue;

				if(stages[stage_index].layers[layer_index].layer_sprites[i].base_unique_id == base_unique_id)
				{
					stages[stage_index].layers[layer_index].layer_sprites.erase( stages[stage_index].layers[layer_index].layer_sprites.begin() + i );
					i = -1;
				}
			}
		}
	}

	//set sprite_base_index based off unique id
	for(int stage_index = 0; stage_index < stages.size(); stage_index++)
	{
		for(int layer_index = 0; layer_index < stages[stage_index].layers.size(); layer_index++)
		{
			for(int i = 0; i < stages[stage_index].layers[layer_index].layer_sprites.size(); i++)
			{
				for(int base_index = 0; base_index < sprite_base.size(); base_index++)
				{
					if(sprite_base[base_index].unique_id == stages[stage_index].layers[layer_index].layer_sprites[i].base_unique_id)
					{
						//std::cout << "REMAP: " << stages[stage_index].layers[layer_index].layer_sprites[i].sprite_name << " to " << base_index << std::endl;
						stages[stage_index].layers[layer_index].layer_sprites[i].sprite_base = base_index;
						break;
					}
				}
			}
		}
	}
}

int Nirvana_Project::getSpriteBaseIndex(std::string sprite_name)
{
	wxString test_name = wxString(sprite_name).Upper().Trim();
	for(int i = 0; i < sprite_base.size(); i++)
	{
		if(wxString(sprite_base[i].sprite_name).Upper().Trim().compare(test_name)==0)
			return i;
	}

	return -1;
}

std::string Nirvana_Project::getSpriteBaseName(int spr_index)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return "";

	return sprite_base[spr_index].sprite_name.ToStdString();
}


void Nirvana_Project::setSpriteNumAnimationFrames(int spr_index, int animation_index, int num_frames)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return;

	if(animation_index < 0 || animation_index >= sprite_base[spr_index].object.animation.size())
		return;

	int frame_diff = num_frames - sprite_base[spr_index].object.animation[animation_index].frames.size();

	if(frame_diff > 0)
	{
		//add frames
		for(int i = 0; i < frame_diff; i++)
		{
			sprite_base[spr_index].object.animation[animation_index].frames.push_back(0);
		}
	}
	else if(frame_diff < 0)
	{
		//remove frames
		frame_diff *= -1; //make frame diff positive
		int last_index = sprite_base[spr_index].object.animation[animation_index].frames.size()-frame_diff;
		sprite_base[spr_index].object.animation[animation_index].frames.erase(last_index, frame_diff);
	}

	sprite_base[spr_index].object.animation[animation_index].frames.reallocate(num_frames);
	sprite_base[spr_index].object.animation[animation_index].num_frames = sprite_base[spr_index].object.animation[animation_index].frames.size();

	//std::cout << "CHECK: " << num_frames << " ~ " << sprite_base[spr_index].object.animation[animation_index].frames.size() << std::endl;
}

void Nirvana_Project::setSpriteAnimationFrame(int spr_index, int animation_index, int ani_frame, int sheet_frame)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return;

	if(animation_index < 0 || animation_index >= sprite_base[spr_index].object.animation.size())
		return;

	if(ani_frame < 0 || ani_frame >= sprite_base[spr_index].object.animation[animation_index].frames.size())
		return;

	sprite_base[spr_index].object.animation[animation_index].frames[ani_frame] = sheet_frame;
}

void Nirvana_Project::setSpriteAnimationFPS(int spr_index, int animation_index, int fps)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return;

	if(animation_index < 0 || animation_index >= sprite_base[spr_index].object.animation.size())
		return;

	sprite_base[spr_index].object.animation[animation_index].fps = fps;
}

int Nirvana_Project::getSpriteNumAnimations(int spr_index)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return 0;

	return sprite_base[spr_index].object.animation.size();
}

int Nirvana_Project::getSpriteNumAnimationFrames(int spr_index, int animation_index)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return 0;

	if(animation_index < 0 || animation_index >= sprite_base[spr_index].object.animation.size())
		return 0;

	return sprite_base[spr_index].object.animation[animation_index].frames.size();
}

int Nirvana_Project::getSpriteAnimationFrame(int spr_index, int animation_index, int ani_frame)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return -1;

	if(animation_index < 0 || animation_index >= sprite_base[spr_index].object.animation.size())
		return -1;

	if(ani_frame < 0 || ani_frame >= sprite_base[spr_index].object.animation[animation_index].frames.size())
		return -1;

	return sprite_base[spr_index].object.animation[animation_index].frames[ani_frame];
}

int Nirvana_Project::getSpriteAnimationFPS(int spr_index, int animation_index)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return 0;

	if(animation_index < 0 || animation_index >= sprite_base[spr_index].object.animation.size())
		return 0;

	return (int)sprite_base[spr_index].object.animation[animation_index].fps;
}



void Nirvana_Project::setSpriteCollision_Shape(int spr_index, int shape)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return;

	sprite_base[spr_index].object.physics.shape_type = shape;
}

int Nirvana_Project::getSpriteCollision_Shape(int spr_index)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return 0;

	return sprite_base[spr_index].object.physics.shape_type;
}

void Nirvana_Project::setSpriteCollision_Detach(int spr_index, bool flag)
{
    if(spr_index < 0 || spr_index >= sprite_base.size())
		return;

	sprite_base[spr_index].object.physics.detached = flag;
}

bool Nirvana_Project::getSpriteCollision_Detach(int spr_index)
{
    if(spr_index < 0 || spr_index >= sprite_base.size())
		return false;

	return sprite_base[spr_index].object.physics.detached;
}

void Nirvana_Project::setSpriteCollision_OffsetX(int spr_index, int x)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return;

	sprite_base[spr_index].object.physics.offset_x = x;
}

int Nirvana_Project::getSpriteCollision_OffsetX(int spr_index)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return 0;

	return sprite_base[spr_index].object.physics.offset_x;
}

void Nirvana_Project::setSpriteCollision_OffsetY(int spr_index, int y)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return;

	sprite_base[spr_index].object.physics.offset_y = y;
}

int Nirvana_Project::getSpriteCollision_OffsetY(int spr_index)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return 0;

	return sprite_base[spr_index].object.physics.offset_y;
}

void Nirvana_Project::setSpriteCollisionBox_Width(int spr_index, int width)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return;

	sprite_base[spr_index].object.physics.box_width = width;
}

int Nirvana_Project::getSpriteCollisionBox_Width(int spr_index)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return 0;

	return sprite_base[spr_index].object.physics.box_width;
}

void Nirvana_Project::setSpriteCollisionBox_Height(int spr_index, int height)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return;

	sprite_base[spr_index].object.physics.box_height = height;
}

int Nirvana_Project::getSpriteCollisionBox_Height(int spr_index)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return 0;

	return sprite_base[spr_index].object.physics.box_height;
}

void Nirvana_Project::setSpriteCollisionCircle_Radius(int spr_index, float radius)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return;

	sprite_base[spr_index].object.physics.radius = radius;
}

float Nirvana_Project::getSpriteCollisionCircle_Radius(int spr_index)
{
	if(spr_index < 0 || spr_index >= sprite_base.size())
		return 0;

	return sprite_base[spr_index].object.physics.radius;
}


int Nirvana_Project::getSpriteCount()
{
	return sprite_base.size();
}

//TILESETS
bool Nirvana_Project::createTileset(wxString tset_id, wxString img_file, int tile_width, int tile_height)
{
	wxString check_id = tset_id.Lower().Trim();

	for(int i = 0; i < tileset.size(); i++)
	{
		if(check_id.compare(tileset[i].tileset_name.Lower().Trim())==0)
			return false;
	}

	Nirvana_Tileset obj;
	obj.tileset_name = tset_id.Trim();
	obj.file = img_file;
	obj.object.tile_width = tile_width;
	obj.object.tile_height = tile_height;
	obj.object.active = true;
	obj.object.img_id = -1;

	tileset.push_back(obj);

	return true;
}

int Nirvana_Project::loadTileset(wxString tset_file)
{
	Nirvana_Tileset obj;
	obj.tileset_name = _("tileset");
	obj.file = tset_file;
	obj.object.tile_width = 32;
	obj.object.tile_height = 32;
	obj.object.active = true;
	obj.object.img_id = -1;


	wxFileName fname(getDir());
	fname.AppendDir(tile_path);

	wxFileName pfile_fname = fname;
	pfile_fname.SetFullName(tset_file.Trim() + _(".tset"));

	wxFile pfile(pfile_fname.GetAbsolutePath(), wxFile::read);

	if(pfile.IsOpened())
	{
		wxString p_data = _("");
		pfile.ReadAll(&p_data);
		pfile.Close();

		std::vector<nirvana_project_file_obj> p_cmd = getParams(p_data);

		for(int i = 0; i < p_cmd.size(); i++)
		{
			if(p_cmd[i].dict.size() == 0)
				continue;

			if(p_cmd[i].dict[0].key.compare(_("TILESET"))==0)
			{
				for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
				{
					if(p_cmd[i].dict[obj_index].key.compare(_("name"))==0)
					{
						obj.tileset_name = p_cmd[i].dict[obj_index].val;
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("frame_size"))==0)
					{
						std::vector<wxString> args = delimArgs(p_cmd[i].dict[obj_index].val);

						if(args.size() >= 2)
						{
							int frame_width = 0;
							int frame_height = 0;
							args[0].ToInt(&frame_width);
							args[1].ToInt(&frame_height);
							obj.object.tile_width = frame_width;
							obj.object.tile_height = frame_height;
						}
					}
				}
			}
			else if(p_cmd[i].dict[0].key.compare(_("TILE"))==0)
			{
				tile_obj n_tile;

				for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
				{
					if(p_cmd[i].dict[obj_index].key.compare(_("fps"))==0)
					{
						p_cmd[i].dict[obj_index].val.ToDouble(&n_tile.fps);
						n_tile.frame_swap_time = 1000/n_tile.fps;
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("frame"))==0)
					{
						std::vector<wxString> args = delimArgs(p_cmd[i].dict[obj_index].val);

						n_tile.frames.clear();
						n_tile.num_frames = args.size();

						for(int arg_index = 0; arg_index < args.size(); arg_index++)
						{
							int frame_value = 0;
							args[arg_index].ToInt(&frame_value);
							n_tile.frames.push_back(frame_value);
						}
					}
				}

				obj.object.tiles.push_back(n_tile);
			}
			else if(p_cmd[i].dict[0].key.compare(_("MASK"))==0)
			{
				tilemask_obj n_mask;
				n_mask.active = true;

				for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
				{
					if(p_cmd[i].dict[obj_index].key.compare(_("name"))==0)
					{
						n_mask.mask_name = p_cmd[i].dict[obj_index].val.ToStdString();
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("value"))==0)
					{
						std::vector<wxString> args = delimArgs(p_cmd[i].dict[obj_index].val);

						n_mask.tiles.size();

						for(int arg_index = 0; arg_index < args.size(); arg_index++)
						{
							int frame_value = 0;
							args[arg_index].ToInt(&frame_value);
							n_mask.tiles.push_back( (frame_value != 0 ? true : false) );
						}
					}
				}

				obj.mask.push_back(n_mask);
			}
		}
	}

	wxString check_id = obj.tileset_name.Trim();
	int n = 1;

	for(int i = 0; i < tileset.size(); i++)
	{
		if(i < 0)
			continue;

		if(check_id.Lower().Trim().compare(tileset[i].tileset_name.Lower().Trim())==0)
		{
			check_id = obj.tileset_name.Trim() + wxString::Format(_("%i"), n);
			n++;
			i = -1;
			continue;
		}
	}

	obj.tileset_name = check_id;

	int tileset_index = tileset.size();
	tileset.push_back(obj);

	return tileset_index;
}

void Nirvana_Project::setTilesetObject(int tileset_index, tileset_obj obj)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		tileset[tileset_index].object = obj;
	}
}

void Nirvana_Project::setTilesetName(int  tileset_index, std::string tileset_name)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		tileset[tileset_index].tileset_name = tileset_name;
	}
}

std::string Nirvana_Project::getTilesetName(int tileset_index)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		return tileset[tileset_index].tileset_name.ToStdString();
	}
	return "";
}

int Nirvana_Project::getTilesetIndex(std::string tileset_name)
{
	wxString tst_name = wxString(tileset_name).Upper().Trim();
	for(int i = 0; i < tileset.size(); i++)
	{
		wxString t_name = tileset[i].tileset_name.Upper().Trim();
		if(t_name.compare(tst_name)==0)
			return i;
	}

	return -1;
}

irr::core::vector2di Nirvana_Project::getTilesetTileSize(int tileset_index)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		return irr::core::vector2di(tileset[tileset_index].object.tile_width, tileset[tileset_index].object.tile_height);
	}
	return irr::core::vector2di();
}

void Nirvana_Project::deleteTileset(int tileset_index)
{
	if(tileset_index < 0 || tileset_index >= tileset.size())
		return;

	tileset.erase(tileset.begin() + tileset_index);
}

void Nirvana_Project::setTileNumAnimationFrames(int tileset_index, int base_tile_index, int num_frames)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		if(base_tile_index >= 0 && base_tile_index < tileset[tileset_index].object.tiles.size())
		{
			for(int i = tileset[tileset_index].object.tiles[base_tile_index].frames.size(); i < num_frames; i++)
				tileset[tileset_index].object.tiles[base_tile_index].frames.push_back(base_tile_index);

			tileset[tileset_index].object.tiles[base_tile_index].num_frames = num_frames;
		}
	}
}

void Nirvana_Project::setTileAnimationFrame(int tileset_index, int base_tile_index, int ani_frame, int sheet_frame)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		if(base_tile_index >= 0 && base_tile_index < tileset[tileset_index].object.tiles.size())
		{
			if(ani_frame >= 0 && ani_frame < tileset[tileset_index].object.tiles[base_tile_index].frames.size())
				tileset[tileset_index].object.tiles[base_tile_index].frames[ani_frame] = sheet_frame;
		}
	}
}

void Nirvana_Project::setTileAnimationFPS(int tileset_index, int base_tile_index, int fps)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		if(base_tile_index >= 0 && base_tile_index < tileset[tileset_index].object.tiles.size())
		{
			tileset[tileset_index].object.tiles[base_tile_index].fps = fps;
			tileset[tileset_index].object.tiles[base_tile_index].frame_swap_time = 1000/fps;
		}
	}
}

int Nirvana_Project::getTileNumAnimationFrames(int tileset_index, int base_tile_index)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		if(base_tile_index >= 0 && base_tile_index < tileset[tileset_index].object.tiles.size())
		{
			return tileset[tileset_index].object.tiles[base_tile_index].num_frames;
		}
	}
	return 0;
}

int Nirvana_Project::getTileAnimationFrame(int tileset_index, int base_tile_index, int ani_frame)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		if(base_tile_index >= 0 && base_tile_index < tileset[tileset_index].object.tiles.size())
		{
			if(ani_frame >= 0 && ani_frame < tileset[tileset_index].object.tiles[base_tile_index].frames.size())
				return tileset[tileset_index].object.tiles[base_tile_index].frames[ani_frame];
		}
	}

	return -1;
}

int Nirvana_Project::getTileAnimationFPS(int tileset_index, int base_tile_index)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		if(base_tile_index >= 0 && base_tile_index < tileset[tileset_index].object.tiles.size())
		{
			return tileset[tileset_index].object.tiles[base_tile_index].fps;
		}
	}

	return 0;
}

Nirvana_Tileset Nirvana_Project::getTileset(int tileset_index)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		return tileset[tileset_index];
	}

	Nirvana_Tileset obj;
	return obj;
}

int Nirvana_Project::getTilesetCount()
{
	return tileset.size();
}

int Nirvana_Project::getTilesetNumTiles(int tileset_index)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		return tileset[tileset_index].object.tiles.size();
	}
	return 0;
}


//--------MASK------------
int Nirvana_Project::createMask(int tileset_index, std::string mask_name)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		tilemask_obj obj;
		obj.mask_name = mask_name;
		obj.active = true;
		for(int i = 0; i < tileset[tileset_index].object.tiles.size(); i++)
		{
			obj.tiles.push_back(false);
		}

		int mask_id = tileset[tileset_index].mask.size();
		tileset[tileset_index].mask.push_back(obj);

		return mask_id;
	}

	return 0;
}

void Nirvana_Project::deleteMask(int tileset_index, int mask_index)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		if(mask_index >= 0 && mask_index < tileset[tileset_index].mask.size())
		{
			tileset[tileset_index].mask.erase( tileset[tileset_index].mask.begin() + mask_index );
		}
	}
}

int Nirvana_Project::getMaskIndex(int tileset_index, std::string mask_name)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		for(int i = 0; i < tileset[tileset_index].mask.size(); i++)
		{
			if(tileset[tileset_index].mask[i].mask_name.compare(mask_name)==0)
				return i;
		}
	}

	return -1;
}

void Nirvana_Project::setTileMask(int tileset_index, int mask_index, int tile_index, bool flag)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		if(mask_index >= 0 && mask_index < tileset[tileset_index].mask.size())
		{
			if(tile_index >= 0 && tile_index < tileset[tileset_index].mask[mask_index].tiles.size())
			{
				tileset[tileset_index].mask[mask_index].tiles[tile_index] = flag;
			}
		}
	}
}

bool Nirvana_Project::getTileMask(int tileset_index, int mask_index, int tile_index)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		if(mask_index >= 0 && mask_index < tileset[tileset_index].mask.size())
		{
			if(tile_index >= 0 && tile_index < tileset[tileset_index].mask[mask_index].tiles.size())
			{
				return tileset[tileset_index].mask[mask_index].tiles[tile_index];
			}
		}
	}
	return false;
}

void Nirvana_Project::clearTileMask(int tileset_index, int mask_index)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		if(mask_index >= 0 && mask_index < tileset[tileset_index].mask.size())
		{
			for(int i = 0; i < tileset[tileset_index].mask[mask_index].tiles.size(); i++)
			{
				tileset[tileset_index].mask[mask_index].tiles[i] = false;
			}
		}
	}
}

int Nirvana_Project::getMaskCount(int tileset_index)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		return tileset[tileset_index].mask.size();
	}
	return 0;
}

bool Nirvana_Project::isValidName(wxString test_name)
{
	if(test_name.Trim().length() == 0)
		return false;

	if(test_name.substr(0,1).compare("[") == 0)
		return false;

	return true;
}

void Nirvana_Project::setMaskName(int tileset_index, int mask_index, std::string mask_name)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		if(mask_index >= 0 && mask_index < tileset[tileset_index].mask.size())
		{
			if(isValidName(wxString(mask_name)))
			{
				for(int i = 0; i < tileset[tileset_index].mask.size(); i++)
				{
					wxString tm_name = wxString(tileset[tileset_index].mask[i].mask_name);
					if(tm_name.Trim().Upper().compare(wxString(mask_name).Trim().Upper())==0)
						return;
				}
				tileset[tileset_index].mask[mask_index].mask_name = mask_name;
			}
		}
	}
}

std::string Nirvana_Project::getMaskName(int tileset_index, int mask_index)
{
	if(tileset_index >= 0 && tileset_index < tileset.size())
	{
		if(mask_index >= 0 && mask_index < tileset[tileset_index].mask.size())
		{
			return tileset[tileset_index].mask[mask_index].mask_name;
		}
	}
	return "";
}


//STAGE
void Nirvana_Project::createStage(std::string stage_name, int tile_width, int tile_height)
{
	Nirvana_Stage new_stage;
	new_stage.stage_name = stage_name;
	new_stage.tile_width = tile_width;
	new_stage.tile_height = tile_height;
	new_stage.width_in_tiles = 0;
	new_stage.height_in_tiles = 0;
	new_stage.stage_id = 0;
	new_stage.layers.clear();
	new_stage.layer_order.clear();

	for(int i = 0; i < stages.size(); i++)
	{
		if(stages[i].stage_id >= new_stage.stage_id)
			new_stage.stage_id = stages[i].stage_id + 1;
	}

	stages.push_back(new_stage);
}

int Nirvana_Project::loadStage(wxString stage_file)
{
	Nirvana_Stage obj;
	obj.stage_name = _("stage");
	obj.tile_width = 32;
	obj.tile_height = 32;
	obj.width_in_tiles = 0;
	obj.height_in_tiles = 0;
	obj.stage_id = 0;
	obj.layers.clear();
	obj.layer_order.clear();

	for(int i = 0; i < stages.size(); i++)
	{
		if(stages[i].stage_id >= obj.stage_id)
			obj.stage_id = stages[i].stage_id + 1;
	}


	wxFileName fname(getDir());
	fname.AppendDir(stage_path);

	wxFileName pfile_fname = fname;
	pfile_fname.SetFullName(stage_file.Trim());

	wxFile pfile(pfile_fname.GetAbsolutePath(), wxFile::read);

	if(pfile.IsOpened())
	{
		wxString p_data = _("");
		pfile.ReadAll(&p_data);
		pfile.Close();

		std::vector<nirvana_project_file_obj> p_cmd = getParams(p_data);

		int layer_index = 0;

		int layer_tmap_index = 0;

		for(int i = 0; i < p_cmd.size(); i++)
		{
			if(p_cmd[i].dict.size() == 0)
				continue;

			if(p_cmd[i].dict[0].key.compare(_("STAGE"))==0)
			{
				for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
				{
					if(p_cmd[i].dict[obj_index].key.compare(_("name"))==0)
					{
						obj.stage_name = p_cmd[i].dict[obj_index].val;
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("tile_size"))==0)
					{
						std::vector<wxString> args = delimArgs(p_cmd[i].dict[obj_index].val);

						if(args.size() >= 2)
						{
							int frame_width = 0;
							int frame_height = 0;
							args[0].ToInt(&frame_width);
							args[1].ToInt(&frame_height);
							obj.tile_width = frame_width;
							obj.tile_height = frame_height;
						}
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("stage_size"))==0)
					{
						std::vector<wxString> args = delimArgs(p_cmd[i].dict[obj_index].val);

						if(args.size() >= 2)
						{
							int t_width = 0;
							int t_height = 0;
							args[0].ToInt(&t_width);
							args[1].ToInt(&t_height);
							obj.width_in_tiles = t_width;
							obj.height_in_tiles = t_height;
						}
					}
				}
			}
			else if(p_cmd[i].dict[0].key.compare(_("LAYER"))==0)
			{
				Nirvana_Map_Layer n_layer;
				n_layer.ref_canvas = -1;
				n_layer.layer_map.tile_map_index = -1;
				n_layer.layer_map.tile_map.texture = NULL;
				n_layer.layer_map.tile_map.tileset = -1;

				layer_tmap_index = 0;

				for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
				{
					if(p_cmd[i].dict[obj_index].key.compare(_("name"))==0)
					{
						n_layer.layer_name = p_cmd[i].dict[obj_index].val.ToStdString();
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("type"))==0)
					{
						n_layer.layer_type = -7;
						if(p_cmd[i].dict[obj_index].val.compare(_("LAYER_TYPE_CANVAS_2D"))==0)
						{
							n_layer.layer_type = LAYER_TYPE_CANVAS_2D;
						}
						else if(p_cmd[i].dict[obj_index].val.compare(_("LAYER_TYPE_CANVAS_3D"))==0)
						{
							n_layer.layer_type = LAYER_TYPE_CANVAS_3D;
						}
						else if(p_cmd[i].dict[obj_index].val.compare(_("LAYER_TYPE_TILEMAP"))==0)
						{
							n_layer.layer_type = LAYER_TYPE_TILEMAP;
						}
						else if(p_cmd[i].dict[obj_index].val.compare(_("LAYER_TYPE_ISO_TILEMAP"))==0)
						{
							n_layer.layer_type = LAYER_TYPE_ISO_TILEMAP;
						}
						else if(p_cmd[i].dict[obj_index].val.compare(_("LAYER_TYPE_SPRITE"))==0)
						{
							n_layer.layer_type = LAYER_TYPE_SPRITE;
						}
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("tileset"))==0)
					{
						n_layer.layer_map.nv_tileset_name = p_cmd[i].dict[obj_index].val.ToStdString();
						n_layer.layer_map.nv_tileset_index = getTilesetIndex(n_layer.layer_map.nv_tileset_name);
						//n_layer.layer_map.tile_map_index

						//std::cout << "debug tilemap: " << n_layer.layer_map.nv_tileset_name << " -> " << n_layer.layer_map.nv_tileset_index << std::endl;
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("scroll_speed"))==0)
					{
						std::vector<wxString> args = delimArgs(p_cmd[i].dict[obj_index].val);

						if(args.size() >= 2)
						{
							double scroll_x = 0;
							double scroll_y = 0;
							args[0].ToDouble(&scroll_x);
							args[1].ToDouble(&scroll_y);
							n_layer.scroll_speed.set(scroll_x, scroll_y);
						}
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("alpha"))==0)
					{
						p_cmd[i].dict[obj_index].val.ToInt(&n_layer.layer_alpha);
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("visible"))==0)
					{
						n_layer.visible = ( p_cmd[i].dict[obj_index].val.compare(_("TRUE"))==0 ? true : false );
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("sprite_grid"))==0)
					{
						n_layer.spriteGrid_type = ( p_cmd[i].dict[obj_index].val.compare(_("ISOMETRIC"))==0 ? SPRITE_LAYER_GRID_ISOMETRIC : SPRITE_LAYER_GRID_SQUARE );
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("sprite_sort_by"))==0)
					{
						n_layer.spriteSortBy = SPRITE_LAYER_SORT_BY_NONE;

						if(p_cmd[i].dict[obj_index].val.compare(_("NONE"))==0)
                        {
                            n_layer.spriteSortBy = SPRITE_LAYER_SORT_BY_NONE;
                        }
                        else if(p_cmd[i].dict[obj_index].val.compare(_("LEAST_X"))==0)
                        {
                            n_layer.spriteSortBy = SPRITE_LAYER_SORT_BY_LEAST_X;
                        }
                        else if(p_cmd[i].dict[obj_index].val.compare(_("GREATEST_X"))==0)
                        {
                            n_layer.spriteSortBy = SPRITE_LAYER_SORT_BY_GREATEST_X;
                        }
                        else if(p_cmd[i].dict[obj_index].val.compare(_("LEAST_Y"))==0)
                        {
                            n_layer.spriteSortBy = SPRITE_LAYER_SORT_BY_LEAST_Y;
                        }
                        else if(p_cmd[i].dict[obj_index].val.compare(_("GREATEST_Y"))==0)
                        {
                            n_layer.spriteSortBy = SPRITE_LAYER_SORT_BY_GREATEST_Y;
                        }
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("sprite_order"))==0)
					{
						n_layer.spriteSortOrder = ( p_cmd[i].dict[obj_index].val.compare(_("DESCENDING"))==0 ? SPRITE_LAYER_ORDER_DESCENDING : SPRITE_LAYER_ORDER_ASCENDING );
					}
				}

				layer_index = obj.layers.size();
				obj.layers.push_back(n_layer);
			}
			else if(p_cmd[i].dict[0].key.compare(_("BKG"))==0)
			{
				for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
				{
					if(p_cmd[i].dict[obj_index].key.compare(_("image"))==0)
					{
						obj.layers[layer_index].bkg.img_file = p_cmd[i].dict[obj_index].val.ToStdString();
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("render_setting"))==0)
					{
						obj.layers[layer_index].bkg.render_setting = -7;
						if(p_cmd[i].dict[obj_index].val.compare(_("IMG_RENDER_SETTING_NORMAL"))==0)
						{
							obj.layers[layer_index].bkg.render_setting = IMG_RENDER_SETTING_NORMAL;
						}
						else if(p_cmd[i].dict[obj_index].val.compare(_("IMG_RENDER_SETTING_STRETCHED"))==0)
						{
							obj.layers[layer_index].bkg.render_setting = IMG_RENDER_SETTING_STRETCHED;
						}
						else if(p_cmd[i].dict[obj_index].val.compare(_("IMG_RENDER_SETTING_TILED"))==0)
						{
							obj.layers[layer_index].bkg.render_setting = IMG_RENDER_SETTING_TILED;
						}
					}
				}
			}
			else if(p_cmd[i].dict[0].key.compare(_("START_TILEMAP"))==0)
			{
			    if(layer_tmap_index == 0)
			    {
			        obj.layers[layer_index].layer_map.nv_tileset_index = -1;
                    obj.layers[layer_index].layer_map.tile_map.rows.clear();
                    obj.layers[layer_index].layer_map.tile_map.num_tiles_across = 0;
                    obj.layers[layer_index].layer_map.tile_map.num_tiles_down = 0;
			    }
			    else if(layer_tmap_index == 1)
                {
                    obj.layers[layer_index].layer_map.tile_map2.rows.clear();
                    obj.layers[layer_index].layer_map.tile_map2.num_tiles_across = 0;
                    obj.layers[layer_index].layer_map.tile_map2.num_tiles_down = 0;
                }
			}
			else if(p_cmd[i].dict[0].key.compare(_("ROW"))==0)
			{
				tilemap_row_obj t_row;
				t_row.tile.clear();

				for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
				{
					if(p_cmd[i].dict[obj_index].key.compare(_("value"))==0)
					{
						std::vector<wxString> args = delimArgs(p_cmd[i].dict[obj_index].val);

						for(int arg_index = 0; arg_index < args.size(); arg_index++)
						{
							int tile_value = 0;
							args[arg_index].ToInt(&tile_value);
							//if(tile_value == 16)
                            //    std::cout << "TILE CHECK: " << obj.layers[layer_index].layer_map.tile_map.rows.size() << ", " << t_row.tile.size() << std::endl;
							t_row.tile.push_back(tile_value);
						}

						if(layer_tmap_index == 0)
						{
						    if(t_row.tile.size() >= obj.layers[layer_index].layer_map.tile_map.num_tiles_across)
                            {
                                obj.layers[layer_index].layer_map.tile_map.num_tiles_across = t_row.tile.size();
                            }
						}
						else if(layer_tmap_index == 1)
                        {
                            if(t_row.tile.size() >= obj.layers[layer_index].layer_map.tile_map2.num_tiles_across)
                            {
                                obj.layers[layer_index].layer_map.tile_map2.num_tiles_across = t_row.tile.size();
                            }
                        }
					}
				}

				if(layer_tmap_index == 0)
				{
				    obj.layers[layer_index].layer_map.tile_map.rows.push_back(t_row);
                    obj.layers[layer_index].layer_map.tile_map.num_tiles_down = obj.layers[layer_index].layer_map.tile_map.rows.size();
				}
				else if(layer_tmap_index == 1)
                {
                    obj.layers[layer_index].layer_map.tile_map2.rows.push_back(t_row);
                    obj.layers[layer_index].layer_map.tile_map2.num_tiles_down = obj.layers[layer_index].layer_map.tile_map2.rows.size();
                }


			}
			else if(p_cmd[i].dict[0].key.compare(_("END_TILEMAP"))==0)
			{
				layer_tmap_index++;

			}
			else if(p_cmd[i].dict[0].key.compare(_("SPRITE"))==0)
			{
				Nirvana_Map_Sprite n_sprite;
				n_sprite.layer_id = layer_index;
				n_sprite.layer_sprite_unique_id = obj_uid_counter;
				obj_uid_counter++;

				for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
				{
					if(p_cmd[i].dict[obj_index].key.compare(_("name"))==0)
					{
						n_sprite.sprite_name = p_cmd[i].dict[obj_index].val.ToStdString();
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("base"))==0)
					{
						std::string spr_base = p_cmd[i].dict[obj_index].val.ToStdString();
						int base_index = getSpriteBaseIndex(spr_base);

						if(base_index >= 0)
						{
							n_sprite.sprite_base = base_index;
							n_sprite.base_unique_id = sprite_base[base_index].unique_id;
						}
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("type"))==0)
					{
						if(p_cmd[i].dict[obj_index].val.compare(_("SPRITE_TYPE_STATIC"))==0)
						{
							n_sprite.body_type = SPRITE_TYPE_STATIC;
						}
						else if(p_cmd[i].dict[obj_index].val.compare(_("SPRITE_TYPE_DYNAMIC"))==0)
						{
							n_sprite.body_type = SPRITE_TYPE_DYNAMIC;
						}
						if(p_cmd[i].dict[obj_index].val.compare(_("SPRITE_TYPE_KINEMATIC"))==0)
						{
							n_sprite.body_type = SPRITE_TYPE_KINEMATIC;
						}
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("position"))==0)
					{
						std::vector<wxString> args = delimArgs(p_cmd[i].dict[obj_index].val);

						if(args.size() >= 2)
						{
							int pos_x = 0;
							int pos_y = 0;
							args[0].ToInt(&pos_x);
							args[1].ToInt(&pos_y);
							n_sprite.position.set(pos_x, pos_y);
						}
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("scale"))==0)
					{
						std::vector<wxString> args = delimArgs(p_cmd[i].dict[obj_index].val);

						if(args.size() >= 2)
						{
							double scale_x = 0;
							double scale_y = 0;
							args[0].ToDouble(&scale_x);
							args[1].ToDouble(&scale_y);
							n_sprite.scale.set(scale_x, scale_y);
						}
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("rotation"))==0)
					{
						double angle = 0;
						p_cmd[i].dict[obj_index].val.ToDouble(&angle);
						n_sprite.angle = 360-angle;
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("alpha"))==0)
					{
						int n_alpha = 0;
						p_cmd[i].dict[obj_index].val.ToInt(&n_alpha);
						n_sprite.alpha = (irr::u8) n_alpha;
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("animation"))==0)
					{
						n_sprite.animation_name = p_cmd[i].dict[obj_index].val.ToStdString();
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("visible"))==0)
					{
						n_sprite.visible = ( p_cmd[i].dict[obj_index].val.compare(_("TRUE"))==0 ? true : false );
					}
				}

				obj.layers[layer_index].layer_sprites.push_back(n_sprite);
			}
			else if(p_cmd[i].dict[0].key.compare(_("SHAPE"))==0)
			{
				sprite2D_physics_obj physics;

				for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
				{
					if(p_cmd[i].dict[obj_index].key.compare(_("name"))==0)
					{
						physics.shape_name = p_cmd[i].dict[obj_index].val.ToStdString();
					}
					if(p_cmd[i].dict[obj_index].key.compare(_("type"))==0)
					{
						if(p_cmd[i].dict[obj_index].val.compare(_("SPRITE_SHAPE_BOX"))==0)
						{
							physics.shape_type = SPRITE_SHAPE_BOX;
						}
						else if(p_cmd[i].dict[obj_index].val.compare(_("SPRITE_SHAPE_CIRCLE"))==0)
						{
							physics.shape_type = SPRITE_SHAPE_CIRCLE;
						}
						else if(p_cmd[i].dict[obj_index].val.compare(_("SPRITE_SHAPE_CHAIN"))==0)
						{
							physics.shape_type = SPRITE_SHAPE_CHAIN;
						}
						else if(p_cmd[i].dict[obj_index].val.compare(_("SPRITE_SHAPE_POLYGON"))==0)
						{
							physics.shape_type = SPRITE_SHAPE_POLYGON;
						}
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("size"))==0)
					{
						std::vector<wxString> args = delimArgs(p_cmd[i].dict[obj_index].val);

						if(args.size() >= 2)
						{
							int b_width = 0;
							int b_height = 0;
							args[0].ToInt(&b_width);
							args[1].ToInt(&b_height);
							//std::cout << " sprite_shape: " << b_width << ", " << b_height << std::endl;
							physics.box_width = b_width;
							physics.box_height = b_height;
						}
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("point"))==0)
					{
						std::vector<wxString> args = delimArgs(p_cmd[i].dict[obj_index].val);

						physics.offset_x = 0;
						physics.offset_y = 0;

						if(args.size() >= 2)
						{
							int x = 0;
							int y = 0;
							args[0].ToInt(&x);
							args[1].ToInt(&y);

							// offset is ignored for chain and polygon
							physics.offset_x = x;
							physics.offset_y = y;

							// points are ignored for box and circle
							physics.points.push_back( irr::core::vector2di(x, y) );
						}
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("radius"))==0)
					{
						p_cmd[i].dict[obj_index].val.ToDouble(&physics.radius);
					}
				}

				obj.layers[layer_index].layer_shapes.push_back(physics);
			}
		}
	}

	wxString check_id = wxString(obj.stage_name).Trim();
	int n = 1;

	for(int i = 0; i < stages.size(); i++)
	{
		if(i < 0)
			continue;

		if(check_id.Lower().Trim().compare(wxString(stages[i].stage_name).Lower().Trim())==0)
		{
			check_id = wxString(obj.stage_name).Trim() + wxString::Format(_("%i"), n);
			n++;
			i = -1;
			continue;
		}
	}

	obj.stage_name = check_id.ToStdString();

	int stage_index = stages.size();
	stages.push_back(obj);

	//std::cout << "FINAL CHECK: " << stages[0].layers[1].layer_map.tile_map.rows[9].tile[3] << std::endl;

	//setStageSize(stage_index, obj.width_in_tiles, obj.height_in_tiles);

	return stage_index;
}

void Nirvana_Project::deleteStage(int stage_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

	stages.erase(stages.begin() + stage_index);
}

int Nirvana_Project::copyStage(int stage_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return -1;

	int n = 1;

	Nirvana_Stage tmp = stages[stage_index];

	wxString tst_name = wxString(tmp.stage_name).Upper().Trim() + _("_");
	wxString nameB = tst_name + wxString::Format(_("%i"), n).Upper().Trim();

	for(int i = 0; i < stages.size(); i++)
	{
		if(i < 0)
			continue;

		wxString nameA = wxString(stages[i].stage_name).Upper().Trim();
		if(nameA.compare(nameB) == 0)
		{
			i = -1;
			n++;
			nameB = tst_name + wxString::Format(_("%i"), n).Upper().Trim();
			continue;
		}
	}

	tmp.stage_name = nameB.ToStdString();

	int copy_index = stages.size();
	stages.push_back(tmp);

	return copy_index;
}

int Nirvana_Project::getStageCount()
{
	return stages.size();
}

int Nirvana_Project::getStageIndex(std::string stage_name)
{
	wxString tst_name(stage_name);
	tst_name = tst_name.Upper().Trim();

	for(int i = 0; i < stages.size(); i++)
	{
		wxString s_name = wxString(stages[i].stage_name).Upper().Trim();

		if(s_name.compare(tst_name)==0)
			return i;
	}

	return -1;
}

std::string Nirvana_Project::getStageName(int stage_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return "";

	return stages[stage_index].stage_name;
}

void Nirvana_Project::setStageName(int stage_index, std::string stage_name)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

	stages[stage_index].stage_name = stage_name;
}

void Nirvana_Project::setStageSize(int stage_index, int width, int height)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

    //std::cout << "SET STAGE SIZE" << std::endl;

	stages[stage_index].width_in_tiles = width;
	stages[stage_index].height_in_tiles = height;

	for(int i = 0; i < stages[stage_index].layers.size(); i++)
	{
		if(stages[stage_index].layers[i].layer_type == LAYER_TYPE_TILEMAP)
		{
			int original_width = stages[stage_index].layers[i].layer_map.tile_map.num_tiles_across;
			int original_height = stages[stage_index].layers[i].layer_map.tile_map.num_tiles_down;

			stages[stage_index].layers[i].layer_map.tile_map.num_tiles_across = width;
			stages[stage_index].layers[i].layer_map.tile_map.num_tiles_down = height;

			stages[stage_index].layers[i].layer_map.tile_map.rows.resize(height);

			//std::cout << "ROWS: " << stages[stage_index].layers[i].layer_map.tile_map.rows.size() << std::endl;

			for(int m_row = 0; m_row < stages[stage_index].layers[i].layer_map.tile_map.rows.size(); m_row++)
			{
				stages[stage_index].layers[i].layer_map.tile_map.rows[m_row].tile.resize(width);

				for(int m_col = (m_row < original_height ? original_width : 0); m_col < width; m_col++)
				{
					//std::cout << "C = " << m_col << std::endl;
					if(m_col < 0)
						continue;

					stages[stage_index].layers[i].layer_map.tile_map.rows[m_row].tile[m_col] = -1;
				}
			}
		}
	}
}

void Nirvana_Project::setStageSizeISO(int stage_index, int width, int height)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

    //std::cout << "SET STAGE SIZE" << std::endl;

	stages[stage_index].width_in_tiles = width;
	stages[stage_index].height_in_tiles = height;

	for(int i = 0; i < stages[stage_index].layers.size(); i++)
	{
		if(stages[stage_index].layers[i].layer_type == LAYER_TYPE_ISO_TILEMAP)
		{
			int original_width = stages[stage_index].layers[i].layer_map.tile_map.num_tiles_across;
			int original_height = stages[stage_index].layers[i].layer_map.tile_map.num_tiles_down;

			stages[stage_index].layers[i].layer_map.tile_map.num_tiles_across = width;
			stages[stage_index].layers[i].layer_map.tile_map.num_tiles_down = height;

			stages[stage_index].layers[i].layer_map.tile_map2.num_tiles_across = width;
			stages[stage_index].layers[i].layer_map.tile_map2.num_tiles_down = height;

			stages[stage_index].layers[i].layer_map.tile_map.rows.resize(height+1);
			stages[stage_index].layers[i].layer_map.tile_map2.rows.resize(height+1);

			//std::cout << "ROWS: " << stages[stage_index].layers[i].layer_map.tile_map.rows.size() << std::endl;

			for(int m_row = 0; m_row < stages[stage_index].layers[i].layer_map.tile_map.rows.size(); m_row++)
			{
				stages[stage_index].layers[i].layer_map.tile_map.rows[m_row].tile.resize(width+1);
				stages[stage_index].layers[i].layer_map.tile_map2.rows[m_row].tile.resize(width+1);

				for(int m_col = (m_row < original_height ? original_width : 0); m_col < (width+1); m_col++)
				{
					//std::cout << "C = " << m_col << std::endl;
					if(m_col < 0)
						continue;

					stages[stage_index].layers[i].layer_map.tile_map.rows[m_row].tile[m_col] = -1;
					stages[stage_index].layers[i].layer_map.tile_map2.rows[m_row].tile[m_col] = -1;
				}
			}
		}
	}
}

irr::core::vector2di Nirvana_Project::getStageSize(int stage_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return irr::core::vector2di();

	return irr::core::vector2di(stages[stage_index].width_in_tiles, stages[stage_index].height_in_tiles);
}

irr::core::vector2di Nirvana_Project::getStageTileSize(int stage_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return irr::core::vector2di();

	return irr::core::vector2di(stages[stage_index].tile_width, stages[stage_index].tile_height);
}

//LAYER
void Nirvana_Project::addLayer(int stage_index, std::string layer_name, int layer_type)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

	Nirvana_Map_Layer n_layer;
	n_layer.layer_name = layer_name;
	n_layer.layer_type = layer_type;
	n_layer.scroll_speed.set(1.0, 1.0);
	n_layer.layer_alpha = 255;
	n_layer.layer_map.tile_map.num_tiles_across = 0;
	n_layer.layer_map.tile_map.num_tiles_down = 0;
	n_layer.layer_map.nv_tileset_index = -1;
	n_layer.layer_map.tile_map_index = -1;
	n_layer.layer_map.tile_map.tileset = -1;
	n_layer.spriteGrid_type = SPRITE_LAYER_GRID_SQUARE;
	n_layer.spriteSortBy = SPRITE_LAYER_SORT_BY_NONE;
	n_layer.spriteSortOrder = SPRITE_LAYER_ORDER_ASCENDING;
	n_layer.ref_canvas = -1;

	wxString n_layer_name = wxString(layer_name).Upper().Trim();

	for(int i = 0; i < stages[stage_index].layers.size(); i++)
	{
		wxString st_layer_name = wxString(stages[stage_index].layers[i].layer_name).Upper().Trim();

		if(st_layer_name.compare(layer_name) == 0)
			return;
	}

	stages[stage_index].layers.push_back(n_layer);

	if(layer_type == LAYER_TYPE_TILEMAP)
		setStageSize(stage_index, stages[stage_index].width_in_tiles, stages[stage_index].height_in_tiles);
    else if(layer_type == LAYER_TYPE_ISO_TILEMAP)
        setStageSizeISO(stage_index, stages[stage_index].width_in_tiles, stages[stage_index].height_in_tiles);
}

int Nirvana_Project::getStageNumLayers(int stage_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return 0;

	return stages[stage_index].layers.size();
}

int Nirvana_Project::getLayerIndex(int stage_index, std::string layer_name)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return -1;

	wxString n_layer_name = wxString(layer_name).Upper().Trim();

	for(int i = 0; i < stages[stage_index].layers.size(); i++)
	{
		wxString st_layer_name = wxString(stages[stage_index].layers[i].layer_name).Upper().Trim();

		if(st_layer_name.compare(n_layer_name) == 0)
			return i;
	}

	//std::cout << "Layer [" << layer_name << "] NOT FOUND" << std::endl;

	return -1;
}

int Nirvana_Project::getLayerType(int stage_index, int layer_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return -1;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return -1;

	return stages[stage_index].layers[layer_index].layer_type;
}

void Nirvana_Project::setLayerName(int stage_index, int layer_index, std::string layer_name)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return;

	wxString test_name = wxString(layer_name).Upper().Trim();
	if(test_name.length()==0)
		return;

	for(int i = 0; i < stages[stage_index].layers.size(); i++)
	{
		wxString l_name = wxString(stages[stage_index].layers[layer_index].layer_name).Upper().Trim();
		if(l_name.compare(test_name)==0)
		{
			return;
		}
	}

	stages[stage_index].layers[layer_index].layer_name = layer_name;
}

std::string Nirvana_Project::getLayerName(int stage_index, int layer_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return "";

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return "";

	return stages[stage_index].layers[layer_index].layer_name;
}

void Nirvana_Project::setLayerScrollSpeed(int stage_index, int layer_index, float h_scroll, float v_scroll)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return;

	stages[stage_index].layers[layer_index].scroll_speed.set(h_scroll, v_scroll);
}

irr::core::vector2df Nirvana_Project::getLayerScrollSpeed(int stage_index, int layer_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return irr::core::vector2df(0, 0);

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return irr::core::vector2df(0, 0);

	return stages[stage_index].layers[layer_index].scroll_speed;
}

void Nirvana_Project::setLayerAlpha(int stage_index, int layer_index, int alpha)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return;

	stages[stage_index].layers[layer_index].layer_alpha = alpha;
}

int Nirvana_Project::getLayerAlpha(int stage_index, int layer_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return 0;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return 0;

	return stages[stage_index].layers[layer_index].layer_alpha;
}

void Nirvana_Project::setLayerVisible(int stage_index, int layer_index, bool visible_flag)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return;

	stages[stage_index].layers[layer_index].visible = visible_flag;
}

bool Nirvana_Project::getLayerVisible(int stage_index, int layer_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return false;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return false;

	return stages[stage_index].layers[layer_index].visible;
}

void Nirvana_Project::setLayerTileset(int stage_index, int layer_index, int tileset_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return;

	if(tileset_index < 0 || tileset_index >= tileset.size())
		return;

	stages[stage_index].layers[layer_index].layer_map.nv_tileset_index = tileset_index;
	stages[stage_index].layers[layer_index].layer_map.nv_tileset_name = tileset[tileset_index].tileset_name.ToStdString();
}

int Nirvana_Project::getLayerTileset(int stage_index, int layer_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return -1;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return -1;

	return stages[stage_index].layers[layer_index].layer_map.nv_tileset_index;
}

void Nirvana_Project::setLayerTile(int stage_index, int layer_index, int x_in_tiles, int y_in_tiles, int tile_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return;

	if(y_in_tiles < 0 || y_in_tiles >= stages[stage_index].layers[layer_index].layer_map.tile_map.rows.size())
		return;

	if(x_in_tiles < 0 || x_in_tiles >= stages[stage_index].layers[layer_index].layer_map.tile_map.rows[y_in_tiles].tile.size())
		return;

	//std::cout << "SETLAYERTILE" << std::endl;
	stages[stage_index].layers[layer_index].layer_map.tile_map.rows[y_in_tiles].tile[x_in_tiles] = tile_index;
}

int Nirvana_Project::getLayerTile(int stage_index, int layer_index, int x_in_tiles, int y_in_tiles)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return -1;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return -1;

	if(y_in_tiles < 0 || y_in_tiles >= stages[stage_index].layers[layer_index].layer_map.tile_map.rows.size())
		return -1;

	if(x_in_tiles < 0 || x_in_tiles >= stages[stage_index].layers[layer_index].layer_map.tile_map.rows[y_in_tiles].tile.size())
		return -1;

	return stages[stage_index].layers[layer_index].layer_map.tile_map.rows[y_in_tiles].tile[x_in_tiles];
}

int Nirvana_Project::addLayerSprite(int stage_index, int layer_index, std::string sprite_name, int sprite_base_index, int x, int y)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return -1;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return -1;

	if(sprite_base_index < 0 || sprite_base_index >= sprite_base.size())
		return -1;

	Nirvana_Map_Sprite layer_sprite;
	layer_sprite.sprite_name = sprite_name;
	layer_sprite.sprite_base = sprite_base_index;
	layer_sprite.base_unique_id = sprite_base[sprite_base_index].unique_id;
	layer_sprite.layer_sprite_unique_id = obj_uid_counter;
	obj_uid_counter++;

	wxString tst_name = wxString(sprite_name).Upper().Trim();

	for(int i = 0; i < sprite_base.size(); i++)
	{
		wxString sp_name = sprite_base[i].sprite_name.Upper().Trim();
		if(sp_name.compare(tst_name)==0)
			return -1;
	}

	layer_sprite.position.set(x, y);
	layer_sprite.scale.set(1, 1);
	layer_sprite.angle = 0;
	layer_sprite.layer_id = layer_index;
	layer_sprite.map_sprite_id = -1;
	layer_sprite.alpha = 255;

	int s_index = stages[stage_index].layers[layer_index].layer_sprites.size();
	stages[stage_index].layers[layer_index].layer_sprites.push_back(layer_sprite);

	return s_index;
}

void Nirvana_Project::deleteLayerSprite(int stage_index, int layer_index, int sprite_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return;

	if(sprite_index < 0 || sprite_index >= stages[stage_index].layers[layer_index].layer_sprites.size())
		return;

	stages[stage_index].layers[layer_index].layer_sprites.erase( stages[stage_index].layers[layer_index].layer_sprites.begin() + sprite_index );
}

int Nirvana_Project::copyLayerSprite(int stage_index, int layer_index, int sprite_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return -1;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return -1;

	if(sprite_index < 0 || sprite_index >= stages[stage_index].layers[layer_index].layer_sprites.size())
		return -1;

	int n = 1;
	wxString base_spr_name = wxString(stages[stage_index].layers[layer_index].layer_sprites[sprite_index].sprite_name).Upper().Trim();
	wxString copy_spr_name = base_spr_name + _("_") + wxString::Format(_("%i"), n);

	for(int i = 0; i < stages[stage_index].layers[layer_index].layer_sprites.size(); i++)
	{
		if(i < 0)
			continue;

		if(wxString(stages[stage_index].layers[layer_index].layer_sprites[i].sprite_name).Upper().Trim().compare(copy_spr_name)==0)
		{
			n++;
			copy_spr_name = base_spr_name + _("_") + wxString::Format(_("%i"), n);
			i = -1;
		}
	}

	Nirvana_Map_Sprite n_sprite = stages[stage_index].layers[layer_index].layer_sprites[sprite_index];
	n_sprite.sprite_name = copy_spr_name.ToStdString();
	n_sprite.map_sprite_id = -1;
	n_sprite.layer_sprite_unique_id = obj_uid_counter;
	obj_uid_counter++;

	int copy_index = stages[stage_index].layers[layer_index].layer_sprites.size();

	stages[stage_index].layers[layer_index].layer_sprites.push_back(n_sprite);

	return copy_index;
}

int Nirvana_Project::getLayerSpriteGridType(int stage_index, int layer_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return 0;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return 0;

	return stages[stage_index].layers[layer_index].spriteGrid_type;
}

int Nirvana_Project::getLayerSpriteSortBy(int stage_index, int layer_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return 0;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return 0;

	return stages[stage_index].layers[layer_index].spriteSortBy;
}

int Nirvana_Project::getLayerSpriteSortOrder(int stage_index, int layer_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return 0;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return 0;

	return stages[stage_index].layers[layer_index].spriteSortOrder;
}

void Nirvana_Project::setLayerSpriteGridType(int stage_index, int layer_index, int grid_type)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return;

	stages[stage_index].layers[layer_index].spriteGrid_type = grid_type;
}

void Nirvana_Project::setLayerSpriteSortBy(int stage_index, int layer_index, int sortBy)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return;

	stages[stage_index].layers[layer_index].spriteSortBy = sortBy;
}

void Nirvana_Project::setLayerSpriteSortOrder(int stage_index, int layer_index, int sortOrder)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return;

	stages[stage_index].layers[layer_index].spriteSortOrder = sortOrder;
}


int Nirvana_Project::getLayerSpriteIndex(int stage_index, int layer_index, std::string sprite_name)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return -1;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return -1;

	wxString tst_name = wxString(sprite_name).Upper().Trim();

	for(int i = 0; i < stages[stage_index].layers[layer_index].layer_sprites.size(); i++)
	{
		wxString sp_name = wxString(stages[stage_index].layers[layer_index].layer_sprites[i].sprite_name).Upper().Trim();
		if(sp_name.compare(tst_name)==0)
			return i;
	}

	return -1;
}

int Nirvana_Project::getLayerSpriteBaseIndex(int stage_index, int layer_index, int sprite_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return -1;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return -1;

	if(sprite_index < 0 || sprite_index >= stages[stage_index].layers[layer_index].layer_sprites.size())
		return -1;

	return stages[stage_index].layers[layer_index].layer_sprites[sprite_index].sprite_base;
}

void Nirvana_Project::setLayerSpritePosition(int stage_index, int layer_index, int sprite_index, int x, int y)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return;

	if(sprite_index < 0 || sprite_index >= stages[stage_index].layers[layer_index].layer_sprites.size())
		return ;

	stages[stage_index].layers[layer_index].layer_sprites[sprite_index].position.set(x, y);
}

irr::core::vector2di Nirvana_Project::getLayerSpritePosition(int stage_index, int layer_index, int sprite_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return irr::core::vector2di();

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return irr::core::vector2di();

	if(sprite_index < 0 || sprite_index >= stages[stage_index].layers[layer_index].layer_sprites.size())
		return irr::core::vector2di();

	return stages[stage_index].layers[layer_index].layer_sprites[sprite_index].position;
}

void Nirvana_Project::setLayerSpriteRotation(int stage_index, int layer_index, int sprite_index, float angle)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return;

	if(sprite_index < 0 || sprite_index >= stages[stage_index].layers[layer_index].layer_sprites.size())
		return;

	stages[stage_index].layers[layer_index].layer_sprites[sprite_index].angle = angle;
}

float Nirvana_Project::getLayerSpriteRotation(int stage_index, int layer_index, int sprite_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return 0;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return 0;

	if(sprite_index < 0 || sprite_index >= stages[stage_index].layers[layer_index].layer_sprites.size())
		return 0;

	return stages[stage_index].layers[layer_index].layer_sprites[sprite_index].angle;
}

void Nirvana_Project::setLayerSpriteScale(int stage_index, int layer_index, int sprite_index, float scale_x, float scale_y)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return;

	if(sprite_index < 0 || sprite_index >= stages[stage_index].layers[layer_index].layer_sprites.size())
		return ;

	stages[stage_index].layers[layer_index].layer_sprites[sprite_index].scale.set(scale_x, scale_y);
}

irr::core::vector2df Nirvana_Project::getLayerSpriteScale(int stage_index, int layer_index, int sprite_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return irr::core::vector2df();

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return irr::core::vector2df();

	if(sprite_index < 0 || sprite_index >= stages[stage_index].layers[layer_index].layer_sprites.size())
		return irr::core::vector2df();

	return stages[stage_index].layers[layer_index].layer_sprites[sprite_index].scale;
}

int Nirvana_Project::getStageLayerNumSprites(int stage_index, int layer_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return 0;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return 0;

	return stages[stage_index].layers[layer_index].layer_sprites.size();
}

Nirvana_Map_Layer Nirvana_Project::getStageLayer(int stage_index, int layer_index)
{
	Nirvana_Map_Layer empty_layer;
	empty_layer.layer_type = -1;

	if(stage_index < 0 || stage_index >= stages.size())
		return empty_layer;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return empty_layer;

	return stages[stage_index].layers[layer_index];
}

void Nirvana_Project::setLayerOrder(int stage_index, int layer_index, int new_layer_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return;

	if(layer_index == new_layer_index)
		return;

	if(new_layer_index < 0 || new_layer_index >= stages[stage_index].layers.size())
		return;

	Nirvana_Map_Layer tmp = stages[stage_index].layers[layer_index];

	stages[stage_index].layers.erase( stages[stage_index].layers.begin() + layer_index );

	stages[stage_index].layers.insert( stages[stage_index].layers.begin() + new_layer_index, tmp);

	//for(int i = 0; i < stages[stage_index].layers.size(); i++)
	//	std::cout << "LAYER: " << stages[stage_index].layers[i].layer_name << std::endl;
}


void Nirvana_Project::deleteLayer(int stage_index, int layer_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return;

	stages[stage_index].layers.erase( stages[stage_index].layers.begin() + layer_index);
}

int Nirvana_Project::copyLayer(int stage_index, int layer_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return -1;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return -1;

	Nirvana_Map_Layer tmp = stages[stage_index].layers[layer_index];

	int n = 1;
	wxString tst_name = wxString(tmp.layer_name).Upper().Trim() + _("_");
	wxString nameB = tst_name + wxString::Format(_("%i"), n).Upper().Trim();

	for(int i = 0; i < stages[stage_index].layers.size(); i++)
	{
		if(i < 0)
			continue;

		wxString nameA = wxString(stages[stage_index].layers[i].layer_name).Upper().Trim();
		if(nameA.compare(nameB) == 0)
		{
			i = -1;
			n++;
			nameB = tst_name + wxString::Format(_("%i"), n).Upper().Trim();
			continue;
		}
	}

	tmp.layer_name = nameB.ToStdString();

	int new_index = stages[stage_index].layers.size();

	stages[stage_index].layers.push_back(tmp);

	stages[stage_index].layers[new_index].ref_canvas = -1;

	return new_index;
}


int Nirvana_Project::createShape(int stage_index, int layer_index, int shape_type)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return -1;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return -1;

	if(stages[stage_index].layers[layer_index].layer_type != LAYER_TYPE_SPRITE)
	{
		wxMessageBox(_("Must be in sprite layer to add collision shape"));
		return -1;
	}

	sprite2D_physics_obj p_obj;

	int n = 1;
	wxString shape_base_name = _("");

	if(shape_type == SPRITE_SHAPE_BOX)
		shape_base_name = _("BOX_");
	else if(shape_type == SPRITE_SHAPE_CHAIN)
		shape_base_name = _("CHAIN_");
	else if(shape_type == SPRITE_SHAPE_POLYGON)
		shape_base_name = _("POLYGON_");
	else if(shape_type == SPRITE_SHAPE_CIRCLE)
		shape_base_name = _("CIRCLE_");

	wxString shape_name = shape_base_name + wxString::Format(_("%i"),n);

	for(int i = 0; i < stages[stage_index].layers[layer_index].layer_shapes.size(); i++)
	{
		if(i < 0)
			continue;

		if(shape_name.compare(wxString(stages[stage_index].layers[layer_index].layer_shapes[i].shape_name).Upper().Trim())==0)
		{
			n++;
			shape_name = shape_base_name + wxString::Format(_("%i"),n);
			i = -1;
		}
	}

	//std::cout << "NAME: " << shape_name.ToStdString() << std::endl;
	p_obj.shape_name = shape_name.ToStdString();
	p_obj.shape_type = shape_type;

	p_obj.offset_x = 0;
	p_obj.offset_y = 0;
	p_obj.box_width = 0;
	p_obj.box_height = 0;
	p_obj.radius = 0;

	int shape_index = stages[stage_index].layers[layer_index].layer_shapes.size();
	stages[stage_index].layers[layer_index].layer_shapes.push_back(p_obj);
	return shape_index;
}

bool Nirvana_Project::setShapeName(int stage_index, int layer_index, int shape_index, std::string shape_name)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return false;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return false;

	if(shape_index < 0 || shape_index >= stages[stage_index].layers[layer_index].layer_shapes.size())
		return false;

	wxString test_name = wxString(shape_name).Upper().Trim();

	for(int i = 0; i < stages[stage_index].layers[layer_index].layer_shapes.size(); i++)
	{
		if(test_name.compare(wxString(stages[stage_index].layers[layer_index].layer_shapes[i].shape_name).Upper().Trim())==0)
		{
			return false;
		}
	}

	stages[stage_index].layers[layer_index].layer_shapes[shape_index].shape_name = shape_name;

	return true;
}

std::string Nirvana_Project::getShapeName(int stage_index, int layer_index, int shape_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return "";

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return "";

	if(shape_index < 0 || shape_index >= stages[stage_index].layers[layer_index].layer_shapes.size())
		return "";

	return stages[stage_index].layers[layer_index].layer_shapes[shape_index].shape_name;
}

int Nirvana_Project::getShapeIndex(int stage_index, int layer_index, std::string shape_name)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return -1;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return -1;

	wxString test_name = wxString(shape_name).Upper().Trim();

	for(int i = 0; i < stages[stage_index].layers[layer_index].layer_shapes.size(); i++)
	{
		if(wxString(stages[stage_index].layers[layer_index].layer_shapes[i].shape_name).Upper().Trim().compare(test_name)==0)
			return i;
	}

	return -1;
}

int Nirvana_Project::getShapeType(int stage_index, int layer_index, int shape_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return -1;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return -1;

	if(shape_index < 0 || shape_index >= stages[stage_index].layers[layer_index].layer_shapes.size())
		return -1;

	return stages[stage_index].layers[layer_index].layer_shapes[shape_index].shape_type;
}

void Nirvana_Project::deleteShape(int stage_index, int layer_index, int shape_index)
{
	if(stage_index < 0 || stage_index >= stages.size())
		return;

	if(layer_index < 0 || layer_index >= stages[stage_index].layers.size())
		return;

	if(shape_index < 0 || shape_index >= stages[stage_index].layers[layer_index].layer_shapes.size())
		return;

	stages[stage_index].layers[layer_index].layer_shapes.erase( stages[stage_index].layers[layer_index].layer_shapes.begin() + shape_index );
}
