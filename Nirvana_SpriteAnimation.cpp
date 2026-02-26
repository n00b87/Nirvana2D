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

	getAnimationSheetControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());

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
    params.WindowSize = irr::core::dimension2du(t_size, t_size);

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
    params.WindowSize = irr::core::dimension2du(t_size, t_size);

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
    params.WindowSize = irr::core::dimension2du(t_size, 96);

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
    params.WindowSize = irr::core::dimension2du(t_size, t_size);

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

			getAnimationSheetControl()->force_refresh();
		break;

		case 1:
			getCollisionControl()->GetDevice()->getContextManager()->activateContext(getCollisionControl()->GetDevice()->getVideoDriver()->getExposedVideoData());
			getCollisionControl()->update_events = true;

			getCollisionControl()->force_refresh();
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

	int img_index = 0;

	if(n_sprite.animation.size() > 0)
    {
        img_index = n_sprite.animation[ n_sprite.animation.size()-1 ].image_file_index;
        //wxMessageBox(_("N_SIZE_DBG: ") + wxString::Format(_("%i"), n_sprite.animation.size()) + _(", ") + wxString::Format(_("%i"), img_index));
    }

	animation_obj.name = ani_name;
	animation_obj.image_file_index = img_index;
	animation_obj.fps = 0;
	animation_obj.num_frames = 1;
	animation_obj.frames.push_back(0);
	int animation_id = n_sprite.animation.size();
	n_sprite.animation.push_back(animation_obj);
	project->setSpriteObject(selected_sprite, n_sprite);

	// Add animation to Frame Panel
	spriteFrame_target->createSpriteAnimation(    img_index,
                                                  n_sprite.animation[animation_id].name,
												  spriteFrame_target->spriteEdit_selected_sprite,
												  n_sprite.animation[animation_id].num_frames,
												  n_sprite.animation[animation_id].fps);

	// Add animation to Preview Panel
	spritePreview_target->createSpriteAnimation(  img_index,
                                                  n_sprite.animation[animation_id].name,
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
	spriteFrame_target->createSprite(n_sprite.layer_sprite_index,
									 spriteFrame_target->current_sheet_image,
									 spriteFrame_target->current_frame_width,
									 spriteFrame_target->current_frame_height);

	// Add animation to Preview Panel
	spritePreview_target->deleteSprite(spritePreview_target->spriteEdit_selected_sprite);
	spritePreview_target->createSprite(n_sprite.layer_sprite_index,
									   spritePreview_target->current_sheet_image,
									   spritePreview_target->current_frame_width,
									   spritePreview_target->current_frame_height);

	// Starting at 1 because 0 is created by createSprite
	for(int i = 1; i < n_sprite.animation.size(); i++)
	{
		spriteFrame_target->createSpriteAnimation(n_sprite.animation[i].image_file_index,
                                                  n_sprite.animation[i].name,
												  spriteFrame_target->spriteEdit_selected_sprite,
												  n_sprite.animation[i].num_frames,
												  n_sprite.animation[i].fps);

		spritePreview_target->createSpriteAnimation(n_sprite.animation[i].image_file_index,
                                                    n_sprite.animation[i].name,
													spritePreview_target->spriteEdit_selected_sprite,
												    n_sprite.animation[i].num_frames,
												    n_sprite.animation[i].fps);
	}

	if(selected_animation < 0 || selected_animation >= n_sprite.animation.size()) //This should never be true but I am paranoid
		return;

	wxString animation_id = wxString(n_sprite.animation[selected_animation].name);
	//selectAnimation(animation_id);
}

void Nirvana_SpriteEditor::clearTarget(wxIrrlicht* target)
{
    for(int i = 0; i < target->spr_edit_current_sheet.size(); i++)
    {
        if(target->imageExists(target->spr_edit_current_sheet[i]))
			target->deleteImage(target->spr_edit_current_sheet[i]);
    }

    target->current_sheet_image = -1;
    target->spriteEdit_selected_sprite = -1;
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
	{
		stopEditor(); //just to temporarily release context from whatever has it

		//CLEAR COLLISION TARGET
		{
		    getCollisionControl()->GetDevice()->getContextManager()->activateContext(getCollisionControl()->GetDevice()->getVideoDriver()->getExposedVideoData());

            getCollisionControl()->setActiveCanvas(getCollisionControl()->sheet_canvas);
            getCollisionControl()->clearCanvas();

            clearTarget(spriteCollision_target);

            getCollisionControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());
		}


		//CLEAR SPRITE SHEET TARGET
		{
		    getAnimationSheetControl()->GetDevice()->getContextManager()->activateContext(getAnimationSheetControl()->GetDevice()->getVideoDriver()->getExposedVideoData());

            getAnimationSheetControl()->setActiveCanvas(getAnimationSheetControl()->sheet_canvas);
            getAnimationSheetControl()->clearCanvas();

            clearTarget(spriteSheet_target);

            getAnimationSheetControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());
		}

		startEditor(editor_page_num);


		//CLEAR ANIMATION FRAMES TARGET
		{
		    getAnimationFrameControl()->GetDevice()->getContextManager()->activateContext(getAnimationFrameControl()->GetDevice()->getVideoDriver()->getExposedVideoData());

		    getAnimationFrameControl()->setActiveCanvas(getAnimationFrameControl()->frame_canvas);
            getAnimationFrameControl()->clearCanvas();

            clearTarget(spriteFrame_target);

            getAnimationFrameControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());
		}


		//CLEAR PREVIEW TARGET
		{
		    getAnimationPreviewControl()->setActiveCanvas(getAnimationPreviewControl()->preview_canvas);
            getAnimationPreviewControl()->clearCanvas();

            clearTarget(spritePreview_target);

            getAnimationPreviewControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());
		}

		return;
	}

	//std::cout << "NSP TEST: " << n_sprite.object.physics.offset_x << std::endl;

	wxFileName fname(project->getDir());

	if(project)
		fname.AppendDir(project->sprite_path);
	else
		fname.AppendDir(_("gfx"));

	std::vector<std::string> sprite_sheet_file;

	for(int i = 0; i < n_sprite.file.size(); i++)
	{
	    fname.SetFullName(n_sprite.file[i]);
        sprite_sheet_file.push_back(fname.GetAbsolutePath().ToStdString());
	}

	//wxMessageBox(_("sprite: ") + wxString(n_sprite.sprite_name) + _("\nimg: ") + wxString(sprite_sheet_file));

	stopEditor(); //just to temporarily release context from whatever has it

	//START COLLISION SCREEN IMAGE LOADING
	getCollisionControl()->GetDevice()->getContextManager()->activateContext(getCollisionControl()->GetDevice()->getVideoDriver()->getExposedVideoData());

	clearTarget(spriteCollision_target);

	for(int i = 0; i < sprite_sheet_file.size(); i++)
	{
	    spriteCollision_target->spr_edit_current_sheet.push_back(spriteCollision_target->loadImage(sprite_sheet_file[i]));
	}

	if(spriteCollision_target->spr_edit_current_sheet.size() > 0)
        spriteCollision_target->current_sheet_image = spriteCollision_target->spr_edit_current_sheet[0];
    else
        spriteCollision_target->current_sheet_image = -1;

	spriteCollision_target->current_frame_width = n_sprite.object.frame_size.Width;
	spriteCollision_target->current_frame_height = n_sprite.object.frame_size.Height;

	//STOP COLLISION SCREEN IMAGE LOADING
	getCollisionControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());


	getAnimationSheetControl()->GetDevice()->getContextManager()->activateContext(getAnimationSheetControl()->GetDevice()->getVideoDriver()->getExposedVideoData());

	clearTarget(spriteSheet_target);

	for(int i = 0; i < sprite_sheet_file.size(); i++)
	{
	    spriteSheet_target->spr_edit_current_sheet.push_back(spriteSheet_target->loadImage(sprite_sheet_file[i]));
	}

	if(spriteSheet_target->spr_edit_current_sheet.size() > 0)
        spriteSheet_target->current_sheet_image = spriteSheet_target->spr_edit_current_sheet[0];
    else
        spriteSheet_target->current_sheet_image = -1;

	spriteSheet_target->current_frame_width = n_sprite.object.frame_size.Width;
	spriteSheet_target->current_frame_height = n_sprite.object.frame_size.Height;

	getAnimationSheetControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());

	startEditor(editor_page_num);


	spriteFrame_target->clear_flag = true;
	spriteFrame_target->spriteEdit_selected_animation = -1;

	clearTarget(spriteFrame_target);

	for(int i = 0; i < sprite_sheet_file.size(); i++)
	{
	    spriteFrame_target->spr_edit_current_sheet.push_back(spriteFrame_target->loadImage(sprite_sheet_file[i]));
	}

	if(spriteFrame_target->spr_edit_current_sheet.size() > 0)
        spriteFrame_target->current_sheet_image = spriteFrame_target->spr_edit_current_sheet[0];
    else
        spriteFrame_target->current_sheet_image = -1;

	spriteFrame_target->current_frame_width = n_sprite.object.frame_size.Width;
	spriteFrame_target->current_frame_height = n_sprite.object.frame_size.Height;
	spriteSheet_target->getImageSizeI(spriteSheet_target->current_sheet_image,
									  &spriteFrame_target->sheet_width,
									  &spriteFrame_target->sheet_height);

	if(spriteFrame_target->spriteExists(spriteFrame_target->spriteEdit_selected_sprite))
		spriteFrame_target->deleteSprite(spriteFrame_target->spriteEdit_selected_sprite);

	spriteFrame_target->spriteEdit_selected_sprite = spriteFrame_target->createSprite(-1,
																					  spriteFrame_target->current_sheet_image,
																					  n_sprite.object.frame_size.Width,
																					  n_sprite.object.frame_size.Height);

	// Starting at 1 because 0 is created by createSprite
	for(int i = 1; i < n_sprite.object.animation.size(); i++)
	{
		spriteFrame_target->createSpriteAnimation(n_sprite.object.animation[i].image_file_index,
                                                  n_sprite.object.animation[i].name,
												  spriteFrame_target->spriteEdit_selected_sprite,
												  n_sprite.object.animation[i].num_frames,
												  n_sprite.object.animation[i].fps);


		for(int a_frame = 0; a_frame < n_sprite.object.animation[i].frames.size(); a_frame++)
		{
			//std::cout << "Set frame_tgt" << std::endl;
			spriteFrame_target->setSpriteAnimationFrame(spriteFrame_target->spriteEdit_selected_sprite, i, a_frame, n_sprite.object.animation[i].frames[a_frame]);
		}
	}

	int spr_index = spriteFrame_target->spriteEdit_selected_sprite;
	project->setSpriteObject(selected_sprite, spriteFrame_target->sprite[spr_index]);

	spriteCollision_target->collision_physics_obj = project->getSpritePhysics(selected_sprite);

	spritePreview_target->clear_flag = true;
	spritePreview_target->spriteEdit_selected_animation = -1;

	clearTarget(spritePreview_target);

	for(int i = 0; i < sprite_sheet_file.size(); i++)
	{
	    spritePreview_target->spr_edit_current_sheet.push_back(spritePreview_target->loadImage(sprite_sheet_file[i]));
	}

	if(spritePreview_target->spr_edit_current_sheet.size() > 0)
        spritePreview_target->current_sheet_image = spritePreview_target->spr_edit_current_sheet[0];
    else
        spritePreview_target->current_sheet_image = -1;

	spritePreview_target->current_frame_width = n_sprite.object.frame_size.Width;
	spritePreview_target->current_frame_height = n_sprite.object.frame_size.Height;
	spriteSheet_target->getImageSizeI(spriteSheet_target->current_sheet_image,
									  &spritePreview_target->sheet_width,
									  &spritePreview_target->sheet_height);

	if(spritePreview_target->spriteExists(spritePreview_target->spriteEdit_selected_sprite))
		spritePreview_target->deleteSprite(spritePreview_target->spriteEdit_selected_sprite);

	spritePreview_target->setActiveCanvas(spritePreview_target->preview_canvas);
	spritePreview_target->spriteEdit_selected_sprite = spritePreview_target->createSprite(-1,
																						  spritePreview_target->current_sheet_image,
																						  n_sprite.object.frame_size.Width,
																						  n_sprite.object.frame_size.Height);

	//std::cout << "Preview Sprite Check = " << spritePreview_target->spriteEdit_selected_sprite << std::endl;

	for(int i = 1; i < n_sprite.object.animation.size(); i++)
	{
		//std::cout << "Animation: " << n_sprite.object.animation[i].name << " :: " << n_sprite.object.animation[i].num_frames << std::endl;
		spritePreview_target->createSpriteAnimation(n_sprite.object.animation[i].image_file_index,
                                                    n_sprite.object.animation[i].name,
													spritePreview_target->spriteEdit_selected_sprite,
												    n_sprite.object.animation[i].num_frames,
												    n_sprite.object.animation[i].fps);

		for(int a_frame = 0; a_frame < n_sprite.object.animation[i].frames.size(); a_frame++)
		{
			spritePreview_target->setSpriteAnimationFrame(spritePreview_target->spriteEdit_selected_sprite, i, a_frame, n_sprite.object.animation[i].frames[a_frame]);
		}
	}

}


void Nirvana_SpriteEditor::setSpriteSource(wxString img_file)
{
    if(selected_sprite < 0 || selected_sprite >= project->getSpriteCount())
		return;

	if(selected_animation < 0 || selected_animation >= project->getSpriteNumAnimations(selected_sprite))
		return;


    Nirvana_SpriteBase n_sprite = project->getSprite(selected_sprite);

	if(!n_sprite.object.active)
        return;


    wxFileName fname(project->getDir());

	if(project)
		fname.AppendDir(project->sprite_path);
	else
		fname.AppendDir(_("gfx"));

    fname.SetFullName(img_file.Trim());

    int img_index = -1;

	for(int i = 0; i < n_sprite.file.size(); i++)
	{
	    if(n_sprite.file[i].Trim().compare(img_file.Trim())==0)
        {
            img_index = i;
            break;
            //sprite_sheet_file.push_back(fname.GetAbsolutePath().ToStdString());
        }
	}

	int frame_index = -1;
	int frame_img_id = -1;

	int preview_index = -1;
	int preview_img_id = -1;

	int sheet_index = -1;
	int sheet_img_id = -1;

	int collision_index = -1;
	int collision_img_id = -1;

	if(img_index < 0)
    {
        img_index = project->sprite_base[selected_sprite].file.size();
        project->sprite_base[selected_sprite].file.push_back(img_file.Trim());
        project->sprite_base[selected_sprite].object.animation[selected_animation].image_file_index = img_index;

        frame_index = spriteFrame_target->spr_edit_current_sheet.size();
        frame_img_id = spriteFrame_target->loadImage(fname.GetAbsolutePath().ToStdString());
        spriteFrame_target->spr_edit_current_sheet.push_back(frame_img_id);

        preview_index = spritePreview_target->spr_edit_current_sheet.size();
        preview_img_id = spritePreview_target->loadImage(fname.GetAbsolutePath().ToStdString());
        spritePreview_target->spr_edit_current_sheet.push_back(preview_img_id);

        sheet_index = spriteSheet_target->spr_edit_current_sheet.size();
        sheet_img_id = spriteSheet_target->loadImage(fname.GetAbsolutePath().ToStdString());
        spriteSheet_target->spr_edit_current_sheet.push_back(sheet_img_id);

        collision_index = spriteCollision_target->spr_edit_current_sheet.size();
        collision_img_id = spriteCollision_target->loadImage(fname.GetAbsolutePath().ToStdString());
        spriteCollision_target->spr_edit_current_sheet.push_back(collision_img_id);
    }
    else
    {
        project->sprite_base[selected_sprite].object.animation[selected_animation].image_file_index = img_index;

        frame_index = img_index;
        frame_img_id = spriteFrame_target->spr_edit_current_sheet[frame_index];

        preview_index = img_index;
        preview_img_id = spritePreview_target->spr_edit_current_sheet[frame_index];

        sheet_index = img_index;
        sheet_img_id = spriteSheet_target->spr_edit_current_sheet[frame_index];

        collision_index = img_index;
        collision_img_id = spriteCollision_target->spr_edit_current_sheet[frame_index];
    }


	int frame_spr_id = spriteFrame_target->spriteEdit_selected_sprite;
	spriteFrame_target->sprite[frame_spr_id].animation[selected_animation].animation_image_id = frame_img_id;
	spriteFrame_target->sprite[frame_spr_id].animation[selected_animation].image_file_index = frame_index;
	spriteFrame_target->current_sheet_image = frame_img_id;


	int preview_spr_id = spritePreview_target->spriteEdit_selected_sprite;
	spritePreview_target->sprite[frame_spr_id].animation[selected_animation].animation_image_id = preview_img_id;
	spritePreview_target->sprite[frame_spr_id].animation[selected_animation].image_file_index = preview_index;
	spritePreview_target->current_sheet_image = preview_img_id;

	spriteSheet_target->current_sheet_image = sheet_img_id;
	spriteCollision_target->current_sheet_image = collision_img_id;
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

	int img_index = project->sprite_base[selected_sprite].object.animation[ani].image_file_index;

	spriteFrame_target->spriteEdit_selected_animation = ani;

	if(img_index >= 0 && img_index < project->sprite_base[selected_sprite].file.size())
	{
	    spriteFrame_target->current_sheet_image = spriteFrame_target->spr_edit_current_sheet[img_index];
        spritePreview_target->current_sheet_image = spritePreview_target->spr_edit_current_sheet[img_index];
        spriteSheet_target->current_sheet_image = spriteSheet_target->spr_edit_current_sheet[img_index];
        spriteCollision_target->current_sheet_image = spriteCollision_target->spr_edit_current_sheet[img_index];
	}


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
		//std::cout << "Frame[" << i << "] = " << project->getSpriteAnimationFrame(selected_sprite, selected_animation, i) << std::endl;

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
