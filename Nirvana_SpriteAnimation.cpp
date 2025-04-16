#include "Nirvana_SpriteAnimation.h"
#include <wx/display.h>
#include <irrlicht.h>

Nirvana_SpriteEditor::Nirvana_SpriteEditor(wxWindow* parent, wxPanel* ani_sheet_panel, wxPanel* ani_frame_panel, wxPanel* ani_preview_panel, wxPanel* col_sheet_panel)
{
	this->parent = parent;
	animation_spriteSheet = ani_sheet_panel;
	animation_spriteFrames = ani_frame_panel;
	animation_preview = ani_preview_panel;
	collision_surface = col_sheet_panel;

	spriteSheet_target = NULL;
	spriteFrame_target = NULL;
	spritePreview_target = NULL;
	spriteCollision_target = NULL;

	initCollision();
	getCollisionControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());

	initAnimationSheet();
	initAnimationFrame();
	initAnimationPreview();

	project = NULL;
}

Nirvana_SpriteEditor::~Nirvana_SpriteEditor()
{
}

void Nirvana_SpriteEditor::setProject(Nirvana_Project* p)
{
	this->project = p;
}

wxIrrlicht* Nirvana_SpriteEditor::getAnimationSheetControl()
{
	return spriteSheet_target;
}

wxIrrlicht* Nirvana_SpriteEditor::getAnimationFrameControl()
{
	return spriteFrame_target;
}

wxIrrlicht* Nirvana_SpriteEditor::getAnimationPreviewControl()
{
	return spritePreview_target;
}

wxIrrlicht* Nirvana_SpriteEditor::getCollisionControl()
{
	return spriteCollision_target;
}

void Nirvana_SpriteEditor::initCollision()
{
	collision_surface->SetFocus();

	int numDisplays = wxDisplay::GetCount();

	int t_size = 640;

	for(int i = 0; i < numDisplays; i++)
	{
		wxDisplay display(i);
		int w = display.GetClientArea().GetWidth();
		int h = display.GetClientArea().GetHeight();

		int max_length = ( w > h ? w : h);
		t_size = ( max_length > t_size ? max_length : t_size );

		//wxMessageBox(_("SIZE[") + wxString::Format(_("%i"), i) + _("] = ") + wxString::Format(_("%i"), w) + _(", ") + wxString::Format(_("%i"), h) );
	}

	spriteCollision_target=new wxIrrlicht(collision_surface, wxID_ANY, false, wxPoint(ClientW(0), ClientH(0)), wxGetDisplaySize());

	spriteCollision_target->debug_string = _("sheet");

	irr::SIrrlichtCreationParameters params;
    params.DriverType = irr::video::EDT_OPENGL;
    params.WindowSize = irr::core::dimension2d(t_size, t_size);

	spriteCollision_target->InitIrr(&params);
	spriteCollision_target->StartRendering();

	irr::IrrlichtDevice* device = spriteCollision_target->GetDevice();
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* smgr = device->getSceneManager();
	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

	spriteCollision_target->collision_canvas = spriteCollision_target->createCanvas(t_size, t_size, 0, 0, collision_surface->GetClientSize().GetX(), collision_surface->GetClientSize().GetY());
	spriteCollision_target->control_id = NV_SPRITE_EDIT_COLLISION_SHEET;
}

void Nirvana_SpriteEditor::initAnimationSheet()
{
	animation_spriteSheet->SetFocus();

	int numDisplays = wxDisplay::GetCount();

	int t_size = 640;

	for(int i = 0; i < numDisplays; i++)
	{
		wxDisplay display(i);
		int w = display.GetClientArea().GetWidth();
		int h = display.GetClientArea().GetHeight();

		int max_length = ( w > h ? w : h);
		t_size = ( max_length > t_size ? max_length : t_size );

		//wxMessageBox(_("SIZE[") + wxString::Format(_("%i"), i) + _("] = ") + wxString::Format(_("%i"), w) + _(", ") + wxString::Format(_("%i"), h) );
	}

	spriteSheet_target=new wxIrrlicht(animation_spriteSheet, wxID_ANY, false, wxPoint(ClientW(0), ClientH(0)), wxGetDisplaySize());

	spriteSheet_target->debug_string = _("sheet");

	irr::SIrrlichtCreationParameters params;
    params.DriverType = irr::video::EDT_OPENGL;
    params.WindowSize = irr::core::dimension2d(t_size, t_size);

	spriteSheet_target->InitIrr(&params);
	spriteSheet_target->StartRendering();

	irr::IrrlichtDevice* device = spriteSheet_target->GetDevice();
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* smgr = device->getSceneManager();
	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

	spriteSheet_target->sheet_canvas = spriteSheet_target->createCanvas(t_size, t_size, 0, 0, animation_spriteSheet->GetClientSize().GetX(), animation_spriteSheet->GetClientSize().GetY());
	spriteSheet_target->control_id = NV_SPRITE_EDIT_ANIMATION_SHEET;
}

void Nirvana_SpriteEditor::initAnimationFrame()
{
	animation_spriteFrames->SetFocus();

	int numDisplays = wxDisplay::GetCount();

	int t_size = 640;

	for(int i = 0; i < numDisplays; i++)
	{
		wxDisplay display(i);
		int w = display.GetClientArea().GetWidth();

		t_size = ( w > t_size ? w : t_size );

		//wxMessageBox(_("SIZE[") + wxString::Format(_("%i"), i) + _("] = ") + wxString::Format(_("%i"), w) + _(", ") + wxString::Format(_("%i"), h) );
	}

	spriteFrame_target=new wxIrrlicht(animation_spriteFrames, wxID_ANY, false, wxPoint(ClientW(0), ClientH(0)), wxGetDisplaySize());

	spriteFrame_target->debug_string = _("frame");

	irr::SIrrlichtCreationParameters params;
    params.DriverType = irr::video::EDT_BURNINGSVIDEO;
    params.WindowSize = irr::core::dimension2d(t_size, 96);

	spriteFrame_target->InitIrr(&params);
	spriteFrame_target->StartRendering();

	irr::IrrlichtDevice* device = spriteFrame_target->GetDevice();
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* smgr = device->getSceneManager();
	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

	spriteFrame_target->frame_canvas = spriteFrame_target->createCanvas(t_size, 200, 0, 0, 1920, 200);
	spriteFrame_target->control_id = NV_SPRITE_EDIT_ANIMATION_FRAME;
}

void Nirvana_SpriteEditor::initAnimationPreview()
{
	int numDisplays = wxDisplay::GetCount();

	int t_size = 640;

	for(int i = 0; i < numDisplays; i++)
	{
		wxDisplay display(i);
		int w = display.GetClientArea().GetWidth();
		int h = display.GetClientArea().GetHeight();

		int max_length = ( w > h ? w : h);
		t_size = ( max_length > t_size ? max_length : t_size );

		//wxMessageBox(_("SIZE[") + wxString::Format(_("%i"), i) + _("] = ") + wxString::Format(_("%i"), w) + _(", ") + wxString::Format(_("%i"), h) );
	}

	t_size = t_size/4;

	spritePreview_target=new wxIrrlicht(animation_preview, wxID_ANY, false, wxPoint(ClientW(0), ClientH(0)), wxGetDisplaySize());

	spritePreview_target->debug_string = _("preview");

	irr::SIrrlichtCreationParameters params;
    params.DriverType = irr::video::EDT_BURNINGSVIDEO;
    params.WindowSize = irr::core::dimension2d(t_size, t_size);

	spritePreview_target->InitIrr(&params);
	spritePreview_target->StartRendering();

	irr::IrrlichtDevice* device = spritePreview_target->GetDevice();
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* smgr = device->getSceneManager();
	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

	spritePreview_target->preview_canvas = spritePreview_target->createCanvas(t_size, t_size, 0, 0, t_size, t_size, CANVAS_TYPE_SPRITE);
	spritePreview_target->setActiveCanvas(spritePreview_target->preview_canvas);
	spritePreview_target->control_id = NV_SPRITE_EDIT_ANIMATION_PREVIEW;
}

void Nirvana_SpriteEditor::setAnimationView()
{
	//clearEditor();
	//initAnimationSheet();
}

void Nirvana_SpriteEditor::stopEditor()
{
	switch(editor_page_num)
	{
		case 0:
			// Only doing this for control that use OPENGL
			getAnimationSheetControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());
			getAnimationSheetControl()->update_events = false;
			getAnimationFrameControl()->update_events = false;
			getAnimationPreviewControl()->update_events = false;
		break;

		case 1:
			getCollisionControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());
			getCollisionControl()->update_events = false;
		break;
	}

}

void Nirvana_SpriteEditor::startEditor(int n)
{
	switch(n)
	{
		case 0:
			// Only doing this for control that use OPENGL
			getAnimationSheetControl()->GetDevice()->getContextManager()->activateContext(getAnimationSheetControl()->GetDevice()->getVideoDriver()->getExposedVideoData());
			getAnimationSheetControl()->update_events = true;
			getAnimationFrameControl()->update_events = true;
			getAnimationPreviewControl()->update_events = true;
		break;

		case 1:
			getCollisionControl()->GetDevice()->getContextManager()->activateContext(getCollisionControl()->GetDevice()->getVideoDriver()->getExposedVideoData());
			getCollisionControl()->update_events = true;
		break;
	}

	editor_page_num = n;
}

int Nirvana_SpriteEditor::getEditorPageIndex()
{
	return editor_page_num;
}

int Nirvana_SpriteEditor::newAnimation()
{
	if(selected_sprite < 0 || selected_sprite >= project->getSpriteCount())
		return -1;

	sprite2D_obj n_sprite = project->getSprite(selected_sprite).object;
	sprite2D_animation_obj animation_obj;
	int ani_num = 1;
	wxString ani_name = _("Animation1");
	for(int i = 0; i < n_sprite.animation.size(); i++)
	{
		if(wxString(n_sprite.animation[i].name).Upper().Trim().compare(ani_name.Upper())==0)
		{
			ani_num++;
			ani_name = _("Animation") + wxString::Format(_("%i"), ani_num);
			i = 0;
		}
	}
	animation_obj.name = ani_name;
	animation_obj.fps = 0;
	animation_obj.num_frames = 1;
	animation_obj.frames.push_back(0);
	int animation_id = n_sprite.animation.size();
	n_sprite.animation.push_back(animation_obj);
	project->setSpriteObject(selected_sprite, n_sprite);

	// Add animation to Frame Panel
	spriteFrame_target->createSpriteAnimation(n_sprite.animation[animation_id].name,
												  spriteFrame_target->spriteEdit_selected_sprite,
												  n_sprite.animation[animation_id].num_frames,
												  n_sprite.animation[animation_id].fps);

	// Add animation to Preview Panel
	spritePreview_target->createSpriteAnimation(n_sprite.animation[animation_id].name,
												  spritePreview_target->spriteEdit_selected_sprite,
												  n_sprite.animation[animation_id].num_frames,
												  n_sprite.animation[animation_id].fps);

	return animation_id;
}

void Nirvana_SpriteEditor::deleteAnimation()
{
	if(selected_sprite < 0 || selected_sprite >= project->getSpriteCount())
		return;

	sprite2D_obj n_sprite = project->getSprite(selected_sprite).object;

	if(selected_animation < 1 || selected_animation >= n_sprite.animation.size()) //0 can't be deleted for "reasons"
		return;

	n_sprite.animation.erase(selected_animation);

	selected_animation = -1;

	project->setSpriteObject(selected_sprite, n_sprite);

	// Add animation to Frame Panel
	spriteFrame_target->deleteSprite(spriteFrame_target->spriteEdit_selected_sprite);
	spriteFrame_target->createSprite(spriteFrame_target->current_sheet_image,
									 spriteFrame_target->current_frame_width,
									 spriteFrame_target->current_frame_height);

	// Add animation to Preview Panel
	spritePreview_target->deleteSprite(spritePreview_target->spriteEdit_selected_sprite);
	spritePreview_target->createSprite(spritePreview_target->current_sheet_image,
									   spritePreview_target->current_frame_width,
									   spritePreview_target->current_frame_height);

	// Starting at 1 because 0 is created by createSprite
	for(int i = 1; i < n_sprite.animation.size(); i++)
	{
		spriteFrame_target->createSpriteAnimation(n_sprite.animation[i].name,
												  spriteFrame_target->spriteEdit_selected_sprite,
												  n_sprite.animation[i].num_frames,
												  n_sprite.animation[i].fps);

		spritePreview_target->createSpriteAnimation(n_sprite.animation[i].name,
													spritePreview_target->spriteEdit_selected_sprite,
												    n_sprite.animation[i].num_frames,
												    n_sprite.animation[i].fps);
	}

	if(selected_animation < 0 || selected_animation >= n_sprite.animation.size()) //This should never be true but I am paranoid
		return;

	wxString animation_id = wxString(n_sprite.animation[selected_animation].name);
	//selectAnimation(animation_id);
}

void Nirvana_SpriteEditor::selectSprite(wxString spr_id)
{
	if(!project)
		return;

	Nirvana_SpriteBase n_sprite;
	bool sprite_found = false;

	selected_animation = -1;

	for(int i = 0; i < project->getSpriteCount(); i++)
	{
		n_sprite = project->getSprite(i);
		if(!n_sprite.object.active)
			continue;

		if(n_sprite.sprite_name.compare(spr_id)==0)
		{
			sprite_found = true;
			selected_sprite = i;
			break;
		}
	}

	if(!sprite_found)
		return;

	//std::cout << "NSP TEST: " << n_sprite.object.physics.offset_x << std::endl;

	wxFileName fname(project->getDir());
	fname.AppendDir(_("gfx"));
	fname.SetFullName(n_sprite.file);

	std::string sprite_sheet_file = fname.GetAbsolutePath().ToStdString();

	//wxMessageBox(_("sprite: ") + wxString(n_sprite.sprite_name) + _("\nimg: ") + wxString(sprite_sheet_file));

	stopEditor(); //just to temporarily release context from whatever has it

	//START COLLISION SCREEN IMAGE LOADING
	getCollisionControl()->GetDevice()->getContextManager()->activateContext(getCollisionControl()->GetDevice()->getVideoDriver()->getExposedVideoData());

	if(spriteCollision_target->imageExists(spriteCollision_target->current_sheet_image))
		spriteCollision_target->deleteImage(spriteCollision_target->current_sheet_image);

	spriteCollision_target->current_sheet_image = spriteCollision_target->loadImage(sprite_sheet_file);
	spriteCollision_target->current_frame_width = n_sprite.object.frame_size.Width;
	spriteCollision_target->current_frame_height = n_sprite.object.frame_size.Height;

	//STOP COLLISION SCREEN IMAGE LOADING
	getCollisionControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());


	getAnimationSheetControl()->GetDevice()->getContextManager()->activateContext(getAnimationSheetControl()->GetDevice()->getVideoDriver()->getExposedVideoData());

	if(spriteSheet_target->imageExists(spriteSheet_target->current_sheet_image))
		spriteSheet_target->deleteImage(spriteSheet_target->current_sheet_image);

	spriteSheet_target->current_sheet_image = spriteSheet_target->loadImage(sprite_sheet_file);
	spriteSheet_target->current_frame_width = n_sprite.object.frame_size.Width;
	spriteSheet_target->current_frame_height = n_sprite.object.frame_size.Height;

	getAnimationSheetControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());

	startEditor(editor_page_num);


	if(spriteFrame_target->imageExists(spriteFrame_target->current_sheet_image))
		spriteFrame_target->deleteImage(spriteFrame_target->current_sheet_image);

	spriteFrame_target->current_sheet_image = spriteFrame_target->loadImage(sprite_sheet_file);
	spriteFrame_target->current_frame_width = n_sprite.object.frame_size.Width;
	spriteFrame_target->current_frame_height = n_sprite.object.frame_size.Height;
	spriteSheet_target->getImageSizeI(spriteSheet_target->current_sheet_image,
									  &spriteFrame_target->sheet_width,
									  &spriteFrame_target->sheet_height);

	if(spriteFrame_target->spriteExists(spriteFrame_target->spriteEdit_selected_sprite))
		spriteFrame_target->deleteSprite(spriteFrame_target->spriteEdit_selected_sprite);

	spriteFrame_target->spriteEdit_selected_sprite = spriteFrame_target->createSprite(spriteFrame_target->current_sheet_image,
																					  n_sprite.object.frame_size.Width,
																					  n_sprite.object.frame_size.Height);

	// Starting at 1 because 0 is created by createSprite
	for(int i = 1; i < n_sprite.object.animation.size(); i++)
	{
		spriteFrame_target->createSpriteAnimation(n_sprite.object.animation[i].name,
												  spriteFrame_target->spriteEdit_selected_sprite,
												  n_sprite.object.animation[i].num_frames,
												  n_sprite.object.animation[i].fps);

		for(int a_frame = 0; a_frame < n_sprite.object.animation[i].frames.size(); a_frame++)
		{
			spriteFrame_target->setSpriteAnimationFrame(spriteFrame_target->spriteEdit_selected_sprite, i, a_frame, n_sprite.object.animation[i].frames[a_frame]);
		}
	}

	int spr_index = spriteFrame_target->spriteEdit_selected_sprite;
	project->setSpriteObject(selected_sprite, spriteFrame_target->sprite[spr_index]);

	spriteCollision_target->collision_physics_obj = project->getSpritePhysics(selected_sprite);

	if(spritePreview_target->imageExists(spritePreview_target->current_sheet_image))
		spritePreview_target->deleteImage(spritePreview_target->current_sheet_image);

	spritePreview_target->current_sheet_image = spritePreview_target->loadImage(sprite_sheet_file);
	spritePreview_target->current_frame_width = n_sprite.object.frame_size.Width;
	spritePreview_target->current_frame_height = n_sprite.object.frame_size.Height;
	spriteSheet_target->getImageSizeI(spriteSheet_target->current_sheet_image,
									  &spritePreview_target->sheet_width,
									  &spritePreview_target->sheet_height);

	if(spritePreview_target->spriteExists(spritePreview_target->spriteEdit_selected_sprite))
		spritePreview_target->deleteSprite(spritePreview_target->spriteEdit_selected_sprite);

	spritePreview_target->setActiveCanvas(spritePreview_target->preview_canvas);
	spritePreview_target->spriteEdit_selected_sprite = spritePreview_target->createSprite(spritePreview_target->current_sheet_image,
																						  n_sprite.object.frame_size.Width,
																						  n_sprite.object.frame_size.Height);

	//std::cout << "Preview Sprite Check = " << spritePreview_target->spriteEdit_selected_sprite << std::endl;

	for(int i = 0; i < n_sprite.object.animation.size(); i++)
	{
		spritePreview_target->createSpriteAnimation(n_sprite.object.animation[i].name,
													spritePreview_target->spriteEdit_selected_sprite,
												    n_sprite.object.animation[i].num_frames,
												    n_sprite.object.animation[i].fps);

		for(int a_frame = 0; a_frame < n_sprite.object.animation[i].frames.size(); a_frame++)
		{
			spritePreview_target->setSpriteAnimationFrame(spritePreview_target->spriteEdit_selected_sprite, i, a_frame, n_sprite.object.animation[i].frames[a_frame]);
		}
	}

}


void Nirvana_SpriteEditor::selectAnimation(wxString animation_id)
{
	if(!project)
		return;

	if(selected_sprite < 0 || selected_sprite >= project->getSpriteCount())
		return;

	Nirvana_SpriteBase n_sprite = project->getSprite(selected_sprite);

	//wxMessageBox(_("TEST: ") + wxString::Format(_("%i"), n_sprite.object.animation.size()));

	int ani = -1;

	animation_id = animation_id.Upper().Trim();

	for(int i = 0; i < n_sprite.object.animation.size(); i++)
	{
		wxString spr_animation_id = wxString(n_sprite.object.animation[i].name).Upper().Trim();

		//wxMessageBox(_("Compare: ") + spr_animation_id + _(" ~ ") + animation_id);

		if(animation_id.compare(spr_animation_id)==0)
		{
			ani = i;
			break;
		}
	}

	if(ani < 0)
		return;

	//wxMessageBox(_("ANI: ") + wxString::Format(_("%i"), ani));

	spriteFrame_target->spriteEdit_selected_animation = ani;
	selected_animation = ani;
}

void Nirvana_SpriteEditor::updateSpriteAnimation()
{
	if(selected_sprite < 0 || selected_sprite >= project->getSpriteCount())
		return;

	if(selected_animation < 0 || selected_animation >= project->getSpriteNumAnimations(selected_sprite))
		return;

	int frame_spr_id = spriteFrame_target->spriteEdit_selected_sprite;
	spriteFrame_target->setSpriteAnimationLength(frame_spr_id,
												 selected_animation,
												 project->getSpriteNumAnimationFrames(selected_sprite, selected_animation));
	spriteFrame_target->setSpriteAnimationSpeed(frame_spr_id,
												selected_animation,
												project->getSpriteAnimationFPS(selected_sprite, selected_animation));

	int preview_spr_id = spritePreview_target->spriteEdit_selected_sprite;
	spritePreview_target->setSpriteAnimationLength(preview_spr_id,
												   selected_animation,
												   project->getSpriteNumAnimationFrames(selected_sprite, selected_animation));
	spritePreview_target->setSpriteAnimationSpeed(preview_spr_id,
												  selected_animation,
												  project->getSpriteAnimationFPS(selected_sprite, selected_animation));

	for(int i = 0; i < project->getSpriteNumAnimationFrames(selected_sprite, selected_animation); i++)
	{
		std::cout << "Frame[" << i << "] = " << project->getSpriteAnimationFrame(selected_sprite, selected_animation, i) << std::endl;

		spriteFrame_target->setSpriteAnimationFrame(frame_spr_id, selected_animation, i, project->getSpriteAnimationFrame(selected_sprite,
																														  selected_animation,
																														  i));

		//std::cout << "Preview" << std::endl;
		spritePreview_target->setSpriteAnimationFrame(preview_spr_id, selected_animation, i, project->getSpriteAnimationFrame(selected_sprite,
																															  selected_animation,
																															  i));
	}
}

int Nirvana_SpriteEditor::getSelectedSprite()
{
	return selected_sprite;
}

int Nirvana_SpriteEditor::getSelectedAnimation()
{
	return selected_animation;
}
