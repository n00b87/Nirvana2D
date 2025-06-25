#include "Nirvana_TileAnimation.h"
#include <wx/display.h>
#include <irrlicht.h>

Nirvana_TileEditor::Nirvana_TileEditor(wxWindow* parent, wxPanel* ani_sheet_panel, wxPanel* ani_frame_panel, wxPanel* ani_preview_panel, wxPanel* mask_sheet_panel)
{
	this->parent = parent;
	animation_tileSheet = ani_sheet_panel;
	animation_tileFrames = ani_frame_panel;
	animation_preview = ani_preview_panel;
	mask_surface = mask_sheet_panel;

	tileSheet_target = NULL;
	tileFrame_target = NULL;
	tilePreview_target = NULL;
	tileMask_target = NULL;

	initMaskSheet();
	getMaskSheetControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());

	initAnimationSheet();
	initAnimationFrame();
	initAnimationPreview();

	getAnimationSheetControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());

	project = NULL;
}

Nirvana_TileEditor::~Nirvana_TileEditor()
{
}

void Nirvana_TileEditor::setProject(Nirvana_Project* p)
{
	this->project = p;
}

wxIrrlicht* Nirvana_TileEditor::getAnimationSheetControl()
{
	return tileSheet_target;
}

wxIrrlicht* Nirvana_TileEditor::getAnimationFrameControl()
{
	return tileFrame_target;
}

wxIrrlicht* Nirvana_TileEditor::getAnimationPreviewControl()
{
	return tilePreview_target;
}

wxIrrlicht* Nirvana_TileEditor::getMaskSheetControl()
{
	return tileMask_target;
}

void Nirvana_TileEditor::initAnimationSheet()
{
	animation_tileSheet->SetFocus();

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

	tileSheet_target=new wxIrrlicht(animation_tileSheet, wxID_ANY, false, wxPoint(ClientW(0), ClientH(0)), wxGetDisplaySize());

	tileSheet_target->debug_string = _("sheet");

	irr::SIrrlichtCreationParameters params;
    params.DriverType = irr::video::EDT_OPENGL;
    params.WindowSize = irr::core::dimension2du(t_size, t_size);

	tileSheet_target->InitIrr(&params);
	tileSheet_target->StartRendering();

	irr::IrrlichtDevice* device = tileSheet_target->GetDevice();
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* smgr = device->getSceneManager();
	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

	tileSheet_target->sheet_canvas = tileSheet_target->createCanvas(t_size, t_size, 0, 0, animation_tileSheet->GetClientSize().GetX(), animation_tileSheet->GetClientSize().GetY());
	tileSheet_target->control_id = NV_TILE_EDIT_ANIMATION_SHEET;
}

void Nirvana_TileEditor::initAnimationFrame()
{
	animation_tileFrames->SetFocus();

	int numDisplays = wxDisplay::GetCount();

	int t_size = 640;

	for(int i = 0; i < numDisplays; i++)
	{
		wxDisplay display(i);
		int w = display.GetClientArea().GetWidth();

		t_size = ( w > t_size ? w : t_size );

		//wxMessageBox(_("SIZE[") + wxString::Format(_("%i"), i) + _("] = ") + wxString::Format(_("%i"), w) + _(", ") + wxString::Format(_("%i"), h) );
	}

	tileFrame_target=new wxIrrlicht(animation_tileFrames, wxID_ANY, false, wxPoint(ClientW(0), ClientH(0)), wxGetDisplaySize());

	tileFrame_target->debug_string = _("frame");

	irr::SIrrlichtCreationParameters params;
    params.DriverType = irr::video::EDT_BURNINGSVIDEO;
    params.WindowSize = irr::core::dimension2du(t_size, 96);

	tileFrame_target->InitIrr(&params);
	tileFrame_target->StartRendering();

	irr::IrrlichtDevice* device = tileFrame_target->GetDevice();
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* smgr = device->getSceneManager();
	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

	tileFrame_target->frame_canvas = tileFrame_target->createCanvas(t_size, 200, 0, 0, 1920, 200);
	tileFrame_target->control_id = NV_TILE_EDIT_ANIMATION_FRAME;
}

void Nirvana_TileEditor::initAnimationPreview()
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

	tilePreview_target=new wxIrrlicht(animation_preview, wxID_ANY, false, wxPoint(ClientW(0), ClientH(0)), wxGetDisplaySize());

	tilePreview_target->debug_string = _("preview");

	irr::SIrrlichtCreationParameters params;
    params.DriverType = irr::video::EDT_BURNINGSVIDEO;
    params.WindowSize = irr::core::dimension2du(t_size, t_size);

	tilePreview_target->InitIrr(&params);
	tilePreview_target->StartRendering();

	irr::IrrlichtDevice* device = tilePreview_target->GetDevice();
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* smgr = device->getSceneManager();
	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

	tilePreview_target->preview_canvas = tilePreview_target->createCanvas(t_size, t_size, 0, 0, t_size, t_size);
	tilePreview_target->control_id = NV_TILE_EDIT_ANIMATION_PREVIEW;
}

void Nirvana_TileEditor::initMaskSheet()
{
	mask_surface->SetFocus();

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

	tileMask_target=new wxIrrlicht(mask_surface, wxID_ANY, false, wxPoint(ClientW(0), ClientH(0)), wxGetDisplaySize());

	tileMask_target->debug_string = _("mask");

	irr::SIrrlichtCreationParameters params;
    params.DriverType = irr::video::EDT_OPENGL;
    params.WindowSize = irr::core::dimension2du(t_size, t_size);

	tileMask_target->InitIrr(&params);
	tileMask_target->StartRendering();

	irr::IrrlichtDevice* device = tileMask_target->GetDevice();
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* smgr = device->getSceneManager();
	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

	tileMask_target->sheet_canvas = tileMask_target->createCanvas(t_size, t_size, 0, 0, mask_surface->GetClientSize().GetX(), mask_surface->GetClientSize().GetY());
	tileMask_target->control_id = NV_TILE_EDIT_MASK_SHEET;
}

void Nirvana_TileEditor::setAnimationView()
{
	//clearEditor();
	//initAnimationSheet();
}

void Nirvana_TileEditor::stopEditor()
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
			getMaskSheetControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());
			getMaskSheetControl()->update_events = false;
		break;
	}
}

void Nirvana_TileEditor::startEditor(int n)
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
			getMaskSheetControl()->GetDevice()->getContextManager()->activateContext(getMaskSheetControl()->GetDevice()->getVideoDriver()->getExposedVideoData());
			getMaskSheetControl()->update_events = true;

			getMaskSheetControl()->force_refresh();
		break;
	}

	editor_page_num = n;
}

int Nirvana_TileEditor::getEditorPageIndex()
{
	return editor_page_num;
}


void Nirvana_TileEditor::selectTileset(wxString tset_id)
{
	if(!project)
		return;

	Nirvana_Tileset n_tileset;
	bool tileset_found = false;

	selected_tile = -1;
	selected_mask = -1;

	for(int i = 0; i < project->getTilesetCount(); i++)
	{
		n_tileset = project->getTileset(i);
		if(!n_tileset.object.active)
			continue;

		if(n_tileset.tileset_name.compare(tset_id)==0)
		{
			//if(n_tileset.object.tiles.size() > 0)
			//	std::cout << "TST 0: " << n_tileset.object.tiles[0].fps << std::endl;

			tileset_found = true;
			selected_tileset = i;
			break;
		}
	}

	if(!tileset_found)
	{
		stopEditor(); //just to temporarily release context from whatever has it

		//START COLLISION SCREEN IMAGE LOADING
		getMaskSheetControl()->GetDevice()->getContextManager()->activateContext(getMaskSheetControl()->GetDevice()->getVideoDriver()->getExposedVideoData());
		getMaskSheetControl()->setActiveCanvas(getMaskSheetControl()->sheet_canvas);
		getMaskSheetControl()->clearCanvas();

		getMaskSheetControl()->scroll_offset_x = 0;
		getMaskSheetControl()->scroll_offset_y = 0;

		if(tileMask_target->imageExists(tileMask_target->current_sheet_image))
			tileMask_target->deleteImage(tileMask_target->current_sheet_image);

		tileMask_target->current_sheet_image = -1;

		//STOP COLLISION SCREEN IMAGE LOADING
		getMaskSheetControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());
		getAnimationSheetControl()->GetDevice()->getContextManager()->activateContext(getAnimationSheetControl()->GetDevice()->getVideoDriver()->getExposedVideoData());
		getAnimationSheetControl()->setActiveCanvas(getMaskSheetControl()->sheet_canvas);
		getAnimationSheetControl()->clearCanvas();

		getAnimationSheetControl()->scroll_offset_x = 0;
		getAnimationSheetControl()->scroll_offset_y = 0;

		if(tileSheet_target->imageExists(tileSheet_target->current_sheet_image))
		tileSheet_target->deleteImage(tileSheet_target->current_sheet_image);

		tileSheet_target->current_sheet_image = -1;

		getAnimationSheetControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());
		startEditor(editor_page_num);

		//FRAME and PREVIEW are both software devices
		getAnimationFrameControl()->setActiveCanvas(getAnimationFrameControl()->frame_canvas);
		getAnimationFrameControl()->clearCanvas();

		getAnimationFrameControl()->scroll_offset_x = 0;
		getAnimationFrameControl()->scroll_offset_y = 0;

		if(tileFrame_target->tilesetExists(tileFrame_target->tileEdit_selected_tileset))
			tileFrame_target->deleteTileSet(tileFrame_target->tileEdit_selected_tileset);

		if(tileFrame_target->imageExists(tileFrame_target->current_sheet_image))
			tileFrame_target->deleteImage(tileFrame_target->current_sheet_image);

		getAnimationPreviewControl()->setActiveCanvas(getAnimationPreviewControl()->preview_canvas);
		getAnimationPreviewControl()->clearCanvas();

		getAnimationPreviewControl()->tileEdit_play_preview = false;

		if(tilePreview_target->tileEdit_preview_tilemap >= 0 && tilePreview_target->tileEdit_preview_tilemap < tilePreview_target->tilemap.size())
			tilePreview_target->deleteTileMap(tilePreview_target->tileEdit_preview_tilemap);

		tilePreview_target->tileEdit_preview_tilemap = -1;

		if(tilePreview_target->tilesetExists(tilePreview_target->tileEdit_selected_tileset))
			tilePreview_target->deleteTileSet(tilePreview_target->tileEdit_selected_tileset);

		tilePreview_target->tileEdit_selected_tileset = -1;

		if(tilePreview_target->imageExists(tilePreview_target->current_sheet_image))
			tilePreview_target->deleteImage(tilePreview_target->current_sheet_image);

		tilePreview_target->current_sheet_image = -1;
		return;
	}

	//std::cout << "NSP TEST: " << n_sprite.object.physics.offset_x << std::endl;

	wxFileName fname(project->getDir());
	if(project)
		fname.AppendDir(project->tile_path);
	else
		fname.AppendDir(_("gfx"));
	fname.SetFullName(n_tileset.file);

	std::string tile_sheet_file = fname.GetAbsolutePath().ToStdString();

	//wxMessageBox(_("sprite: ") + wxString(n_sprite.sprite_name) + _("\nimg: ") + wxString(sprite_sheet_file));

	stopEditor(); //just to temporarily release context from whatever has it

	//START COLLISION SCREEN IMAGE LOADING
	getMaskSheetControl()->GetDevice()->getContextManager()->activateContext(getMaskSheetControl()->GetDevice()->getVideoDriver()->getExposedVideoData());

	if(tileMask_target->imageExists(tileMask_target->current_sheet_image))
		tileMask_target->deleteImage(tileMask_target->current_sheet_image);

	tileMask_target->current_sheet_image = tileMask_target->loadImage(tile_sheet_file);
	tileMask_target->current_frame_width = n_tileset.object.tile_width;
	tileMask_target->current_frame_height = n_tileset.object.tile_height;

	//STOP COLLISION SCREEN IMAGE LOADING
	getMaskSheetControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());


	getAnimationSheetControl()->GetDevice()->getContextManager()->activateContext(getAnimationSheetControl()->GetDevice()->getVideoDriver()->getExposedVideoData());

	if(tileSheet_target->imageExists(tileSheet_target->current_sheet_image))
		tileSheet_target->deleteImage(tileSheet_target->current_sheet_image);

	tileSheet_target->current_sheet_image = tileSheet_target->loadImage(tile_sheet_file);
	tileSheet_target->current_frame_width = n_tileset.object.tile_width;
	tileSheet_target->current_frame_height = n_tileset.object.tile_height;

	getAnimationSheetControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());

	startEditor(editor_page_num);


	if(tileFrame_target->imageExists(tileFrame_target->current_sheet_image))
		tileFrame_target->deleteImage(tileFrame_target->current_sheet_image);

	tileFrame_target->current_sheet_image = tileFrame_target->loadImage(tile_sheet_file); //std::cout << "IMG DBG: " << tile_sheet_file << " -> " << tileFrame_target->current_sheet_image << std::endl;
	tileFrame_target->current_frame_width = n_tileset.object.tile_width;
	tileFrame_target->current_frame_height = n_tileset.object.tile_height;
	tileSheet_target->getImageSizeI(tileSheet_target->current_sheet_image,
									  &tileFrame_target->sheet_width,
									  &tileFrame_target->sheet_height);

	//COOK
	if(tileFrame_target->tilesetExists(tileFrame_target->tileEdit_selected_tileset))
		tileFrame_target->deleteTileSet(tileFrame_target->tileEdit_selected_tileset);

	tileFrame_target->tileEdit_selected_tileset = tileFrame_target->createTileSet(tileFrame_target->current_sheet_image,
																					  n_tileset.object.tile_width,
																					  n_tileset.object.tile_height);

	for(int i = 0; i < n_tileset.object.tiles.size(); i++)
	{
		tileFrame_target->setTileAnimationLength(tileFrame_target->tileEdit_selected_tileset,
												  i,
												  n_tileset.object.tiles[i].num_frames);

		tileFrame_target->setTileAnimationSpeed(tileFrame_target->tileEdit_selected_tileset,
												  i,
												  n_tileset.object.tiles[i].fps);

		for(int a_frame = 0; a_frame < n_tileset.object.tiles[i].frames.size(); a_frame++)
		{


			//std::cout << "debug: " << n_tileset.object.tiles.size() << ": " << i << ", " << a_frame << ", " << n_tileset.object.tiles[i].frames.size() << std::endl;
			tileFrame_target->setTileAnimationFrame(tileFrame_target->tileEdit_selected_tileset, i, a_frame, n_tileset.object.tiles[i].frames[a_frame]);
		}
	}

	//YOP
	int tileset_index = tileFrame_target->tileEdit_selected_tileset;
	//std::cout << "tileset_index = " << tileset_index << std::endl;
	project->setTilesetObject(selected_tileset, tileFrame_target->tileset[tileset_index]);


	if(tilePreview_target->imageExists(tilePreview_target->current_sheet_image))
		tilePreview_target->deleteImage(tilePreview_target->current_sheet_image);

	tilePreview_target->current_sheet_image = tilePreview_target->loadImage(tile_sheet_file);
	tilePreview_target->current_frame_width = n_tileset.object.tile_width;
	tilePreview_target->current_frame_height = n_tileset.object.tile_height;
	tileSheet_target->getImageSizeI(tileSheet_target->current_sheet_image,
									  &tilePreview_target->sheet_width,
									  &tilePreview_target->sheet_height);

	if(tilePreview_target->tilesetExists(tilePreview_target->tileEdit_selected_tileset))
		tilePreview_target->deleteTileSet(tilePreview_target->tileEdit_selected_tileset);

	tilePreview_target->setActiveCanvas(tilePreview_target->preview_canvas);
	tilePreview_target->tileEdit_selected_tileset = tilePreview_target->createTileSet(tilePreview_target->current_sheet_image,
																						  n_tileset.object.tile_width,
																						  n_tileset.object.tile_height);

	//std::cout << "Preview Sprite Check = " << spritePreview_target->spriteEdit_selected_sprite << std::endl;

	for(int i = 0; i < n_tileset.object.tiles.size(); i++)
	{
		tilePreview_target->setTileAnimationLength(tilePreview_target->tileEdit_selected_tileset,
												  i,
												  n_tileset.object.tiles[i].num_frames);

		for(int a_frame = 0; a_frame < n_tileset.object.tiles[i].frames.size(); a_frame++)
		{
			tilePreview_target->setTileAnimationFrame(tilePreview_target->tileEdit_selected_tileset, i, a_frame, n_tileset.object.tiles[i].frames[a_frame]);
		}
	}

	if(tilePreview_target->tileEdit_preview_tilemap >= 0 && tilePreview_target->tileEdit_preview_tilemap < tilePreview_target->tilemap.size())
		tilePreview_target->deleteTileMap(tilePreview_target->tileEdit_preview_tilemap);

	tilePreview_target->tileEdit_preview_tilemap = tilePreview_target->createTileMap(tilePreview_target->tileEdit_selected_tileset, 1000, 1000);
	tilePreview_target->fillTile(tilePreview_target->tileEdit_preview_tilemap, -1, 0, 0, 1000, 1000);
}


void Nirvana_TileEditor::selectTile(int tile_index)
{
	if(!project)
		return;

	selected_tile = tile_index;
	getAnimationFrameControl()->tileEdit_selected_tile = selected_tile;
	getAnimationPreviewControl()->tileEdit_selected_tile = selected_tile;
	getAnimationPreviewControl()->setTile(tilePreview_target->tileEdit_preview_tilemap, selected_tile, 0, 0);
}

int Nirvana_TileEditor::getSelectedTileset()
{
	return selected_tileset;
}

int Nirvana_TileEditor::getSelectedTile()
{
	return selected_tile;
}

void Nirvana_TileEditor::updateTileAnimation()
{
	if(selected_tileset < 0 || selected_tileset >= project->getTilesetCount())
		return;

	if(selected_tile < 0 || selected_tile >= project->getTilesetNumTiles(selected_tileset))
		return;

	int tileset_id = tileFrame_target->tileEdit_selected_tileset;
	tileFrame_target->setTileAnimationLength(tileset_id,
											 selected_tile,
											 project->getTileNumAnimationFrames(selected_tileset, selected_tile));
	tileFrame_target->setTileAnimationSpeed(tileset_id,
											selected_tile,
											project->getTileAnimationFPS(selected_tileset, selected_tile));

	int preview_tilset_id = tilePreview_target->tileEdit_selected_tileset;
	tilePreview_target->setTileAnimationLength(preview_tilset_id,
											   selected_tile,
											   project->getTileNumAnimationFrames(selected_tileset, selected_tile));
	tilePreview_target->setTileAnimationSpeed(preview_tilset_id,
											  selected_tile,
											  project->getTileAnimationFPS(selected_tileset, selected_tile));

	for(int i = 0; i < project->getTileNumAnimationFrames(selected_tileset, selected_tile); i++)
	{
		//std::cout << "Frame[" << i << "] = " << project->getTileAnimationFrame(selected_tileset, selected_tile, i) << std::endl;

		tileFrame_target->setTileAnimationFrame(tileset_id, selected_tile, i, project->getTileAnimationFrame(selected_tileset,
																  selected_tile,
																  i));

		//std::cout << "Preview" << std::endl;
		tilePreview_target->setTileAnimationFrame(preview_tilset_id, selected_tile, i, project->getTileAnimationFrame(selected_tileset,
																	  selected_tile,
																	  i));
	}
}

void Nirvana_TileEditor::playPreview()
{
	tilePreview_target->tileEdit_play_preview = true;
}

void Nirvana_TileEditor::stopPreview()
{
	tilePreview_target->tileEdit_play_preview = false;
}

void Nirvana_TileEditor::selectMask(wxString mask_name)
{
	if(selected_tileset < 0 || selected_tileset >= project->getTilesetCount())
		return;

	Nirvana_Tileset n_tileset = project->getTileset(selected_tileset);

	selected_mask = -1;
	tilemask_obj empty_mask;
	empty_mask.active = false;
	tileMask_target->tileEdit_tileMask = empty_mask;

	for(int i = 0; i < n_tileset.mask.size(); i++)
	{
		wxString t_mask(n_tileset.mask[i].mask_name);
		if(t_mask.Upper().compare(mask_name.Upper())==0)
		{
			selected_mask = i;
			tileMask_target->tileEdit_tileMask = n_tileset.mask[i];
			return;
		}
	}
}

int Nirvana_TileEditor::getSelectedMask()
{
	return selected_mask;
}
