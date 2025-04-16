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

	initAnimationSheet();
	initAnimationFrame();
	initAnimationPreview();

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
    params.WindowSize = irr::core::dimension2d(t_size, t_size);

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
    params.WindowSize = irr::core::dimension2d(t_size, 96);

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
    params.WindowSize = irr::core::dimension2d(t_size, t_size);

	tilePreview_target->InitIrr(&params);
	tilePreview_target->StartRendering();

	irr::IrrlichtDevice* device = tilePreview_target->GetDevice();
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* smgr = device->getSceneManager();
	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

	tilePreview_target->preview_canvas = tilePreview_target->createCanvas(t_size, t_size, 0, 0, t_size, t_size);
	tilePreview_target->control_id = NV_TILE_EDIT_ANIMATION_PREVIEW;
}

void Nirvana_TileEditor::setAnimationView()
{
	//clearEditor();
	//initAnimationSheet();
}

void Nirvana_TileEditor::stopEditor()
{
	// Only doing this for control that use OPENGL
	getAnimationSheetControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());

	getAnimationSheetControl()->update_events = false;
	getAnimationFrameControl()->update_events = false;
	getAnimationPreviewControl()->update_events = false;

}

void Nirvana_TileEditor::startEditor()
{
	// Only doing this for control that use OPENGL
	getAnimationSheetControl()->GetDevice()->getContextManager()->activateContext(getAnimationSheetControl()->GetDevice()->getVideoDriver()->getExposedVideoData());
	getAnimationSheetControl()->update_events = true;
	getAnimationFrameControl()->update_events = true;
	getAnimationPreviewControl()->update_events = true;
}


void Nirvana_TileEditor::selectTileset(wxString spr_id)
{
}


void Nirvana_TileEditor::selectTile(wxString animation_id)
{
	if(!project)
		return;
}

int Nirvana_TileEditor::getSelectedTileset()
{
	return selected_tileset;
}

int Nirvana_TileEditor::getSelectedTile()
{
	return selected_tile;
}
