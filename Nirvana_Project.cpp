#include "Nirvana_Project.h"
#include <wx/wx.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/arrstr.h>

Nirvana_Project::Nirvana_Project()
{
	project_filename_obj = wxFileName(_("/home/n00b/Projects/Nirvana2D/test_project/test.nvprj"));

	tileSheet_target = NULL;
	tileFrame_target = NULL;
	tilePreview_target = NULL;
	tileMask_target = NULL;

	spriteCollision_target = NULL;

	spriteSheet_target = NULL;
	spriteFrame_target = NULL;
	spritePreview_target = NULL;
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

bool Nirvana_Project::createSprite(wxString spr_id, wxString img_file, int frame_width, int frame_height)
{
	wxString check_id = spr_id.Lower().Trim();

	for(int i = 0; i < sprite_base.size(); i++)
	{
		if(check_id.compare(sprite_base[i].sprite_name)==0)
			return false;
	}

	Nirvana_SpriteBase obj;
	obj.sprite_name = spr_id.Trim();
	obj.file = img_file;
	obj.object.frame_size.set(frame_width, frame_height);
	obj.object.active = true;

	sprite_base.push_back(obj);

	return true;
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



int Nirvana_Project::getSpriteCount()
{
	return sprite_base.size();
}
