#include "Nirvana_MapEditor.h"
#include <wx/display.h>
#include <irrlicht.h>

Nirvana_MapEditor::Nirvana_MapEditor(wxWindow* parent, wxPanel* map_panel, wxPanel* tile_panel)
{
	this->parent = parent;

	map_surface = map_panel;
	tileSelect_Sheet = tile_panel;
	//spritePreview_surface = sprite_panel;

	map_target = NULL;
	tileSelect_target = NULL;
	//spritePreview_target = NULL;

	initMapView();
	getMapViewControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());

	initTileSelect();
	getTileSelectControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());

	//initSpritePreview();

	//getMapViewControl()->shared_control = getTileSelectControl();
	//getTileSelectControl()->shared_control = getMapViewControl();

	project = NULL;
}

Nirvana_MapEditor::~Nirvana_MapEditor()
{
}

void Nirvana_MapEditor::setProject(Nirvana_Project* p)
{
	this->project = p;
}

wxIrrlicht* Nirvana_MapEditor::getMapViewControl()
{
	return map_target;
}

wxIrrlicht* Nirvana_MapEditor::getTileSelectControl()
{
	return tileSelect_target;
}



void Nirvana_MapEditor::initMapView()
{
	map_surface->SetFocus();

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

	map_target=new wxIrrlicht(map_surface, wxID_ANY, false, wxPoint(ClientW(0), ClientH(0)), wxGetDisplaySize());

	//wxMessageBox(_("DBG: ") + wxString::Format(_("%i"),map_target->active_canvas));

	map_target->debug_string = _("MAP");

	irr::SIrrlichtCreationParameters params;
    params.DriverType = irr::video::EDT_OPENGL;
    params.WindowSize = irr::core::dimension2du(t_size, t_size);

	map_target->InitIrr(&params);
	map_target->StartRendering();

	irr::IrrlichtDevice* device = map_target->GetDevice();
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* smgr = device->getSceneManager();
	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

	map_target->sheet_canvas = map_target->createCanvas(t_size, t_size, 0, 0, map_surface->GetClientSize().GetX(), map_surface->GetClientSize().GetY());
	map_target->control_id = NV_MAP_EDIT_MAP_SHEET;
	map_target->enable_update = true;
	map_target->update_events = true;
}

void Nirvana_MapEditor::initTileSelect()
{
	tileSelect_Sheet->SetFocus();

	int numDisplays = wxDisplay::GetCount();

	int t_size = 640;

	for(int i = 0; i < numDisplays; i++)
	{
		wxDisplay display(i);
		int w = display.GetClientArea().GetWidth();

		t_size = ( w > t_size ? w : t_size );

		//wxMessageBox(_("SIZE[") + wxString::Format(_("%i"), i) + _("] = ") + wxString::Format(_("%i"), w) + _(", ") + wxString::Format(_("%i"), h) );
	}

	t_size = t_size;

	tileSelect_target=new wxIrrlicht(tileSelect_Sheet, wxID_ANY, false, wxPoint(ClientW(0), ClientH(0)), wxGetDisplaySize());

	tileSelect_target->debug_string = _("frame");

	irr::SIrrlichtCreationParameters params;
    params.DriverType = irr::video::EDT_OPENGL;
    params.WindowSize = irr::core::dimension2du(t_size, t_size);

	tileSelect_target->InitIrr(&params);
	tileSelect_target->StartRendering();

	irr::IrrlichtDevice* device = tileSelect_target->GetDevice();
	irr::video::IVideoDriver* driver = device->getVideoDriver();
	irr::scene::ISceneManager* smgr = device->getSceneManager();
	irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

	tileSelect_target->overlay_canvas = tileSelect_target->createCanvas(t_size, t_size, 0, 0, t_size, t_size);
	tileSelect_target->sheet_canvas = tileSelect_target->createCanvas(t_size, t_size, 0, 0, t_size, t_size);
	tileSelect_target->control_id = NV_MAP_EDIT_TILE_SHEET;
}




void Nirvana_MapEditor::stopEditor(bool stop_mapView)
{
	switch(editor_page_num)
	{
		case 0:
			// Only doing this for control that use OPENGL
			getTileSelectControl()->update_events = false;
		break;

		case 1:
			//getSpritePreviewControl()->update_events = false;
		break;
	}

	if(stop_mapView)
	{
		getTileSelectControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());
		getTileSelectControl()->mapEdit_hasContext = false;

		getMapViewControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());
		getMapViewControl()->update_events = false;
		getMapViewControl()->mapEdit_hasContext = false;
	}
}

void Nirvana_MapEditor::startEditor(int n, bool start_mapView)
{
	switch(n)
	{
		case 0:
			// Only doing this for control that use OPENGL
			getTileSelectControl()->update_events = true;
		break;

		case 1:
			//Sprite Panel
		break;

		case 2:
			// Collision Shape panel
		break;
	}

	if(start_mapView)
	{
		getTileSelectControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());
		getTileSelectControl()->mapEdit_hasContext = false;

		getMapViewControl()->GetDevice()->getContextManager()->activateContext(getMapViewControl()->GetDevice()->getVideoDriver()->getExposedVideoData());
		getMapViewControl()->update_events = true;
		getMapViewControl()->mapEdit_hasContext = true;
	}

	editor_page_num = n;
}

int Nirvana_MapEditor::getEditorPageIndex()
{
	return editor_page_num;
}

void Nirvana_MapEditor::setMapTool(int tool_id)
{
	map_tool = tool_id;

	getMapViewControl()->map_tool = tool_id;
	getTileSelectControl()->map_tool = tool_id;
}

void Nirvana_MapEditor::selectStage(int stage_index)
{
	selected_layer = -1;
	selected_sprite = -1;
	selected_tile = -1;
	selected_stage = stage_index;
	getMapViewControl()->selected_stage = -1;
	getMapViewControl()->mapEdit_selectTileTool_selection.clear();

	if(selected_stage >= 0 && selected_stage < project->stages.size())
	{
		getTileSelectControl()->current_frame_width = project->stages[selected_stage].tile_width;
		getTileSelectControl()->current_frame_height = project->stages[selected_stage].tile_height;
		getTileSelectControl()->mapEdit_selectSpriteTool_selection.clear();
		getTileSelectControl()->mapEdit_selectTileTool_selection.clear();
		getTileSelectControl()->mapEdit_selectTileTool_box.clear();

		getMapViewControl()->current_frame_width = project->stages[selected_stage].tile_width;
		getMapViewControl()->current_frame_height = project->stages[selected_stage].tile_height;
		getMapViewControl()->initStage(selected_stage);
		getMapViewControl()->mapEdit_selectSpriteTool_selection.clear();
		getMapViewControl()->mapEdit_selectTileTool_selection.clear();
		getMapViewControl()->mapEdit_selectTileTool_box.clear();
	}
}

void Nirvana_MapEditor::selectLayer(int layer_index)
{
	int stage_index = selected_stage;


	selected_layer = layer_index;

	getMapViewControl()->mapEdit_selectTileTool_selection.clear();

	Nirvana_Map_Layer n_layer = project->getStageLayer(stage_index, layer_index);
	getMapViewControl()->mapEdit_layerType = project->getLayerType(stage_index, layer_index);
	getMapViewControl()->selected_layer = layer_index;
	getMapViewControl()->mapEdit_selectSpriteTool_selection.clear();
	getMapViewControl()->mapEdit_selectTileTool_selection.clear();
	getMapViewControl()->mapEdit_selectTileTool_box.clear();

	getTileSelectControl()->selected_layer = layer_index;
	getTileSelectControl()->mapEdit_layerType = project->getLayerType(stage_index, layer_index);
	getTileSelectControl()->mapEdit_selectSpriteTool_selection.clear();
	getTileSelectControl()->mapEdit_selectTileTool_selection.clear();
	getTileSelectControl()->mapEdit_selectTileTool_box.clear();

	//getSpritePreviewControl()->selected_layer = layer_index;
	//getSpritePreviewControl()->mapEdit_layerType = project->getLayerType(stage_index, layer_index);

	getTileSelectControl()->mapEdit_getContext();
	getTileSelectControl()->setActiveCanvas(getTileSelectControl()->sheet_canvas);
	getTileSelectControl()->clearCanvas();

	getTileSelectControl()->setActiveCanvas(getTileSelectControl()->overlay_canvas);
	getTileSelectControl()->clearCanvas();

	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	switch(n_layer.layer_type)
	{
	    case LAYER_TYPE_SPRITE:
	    case LAYER_TYPE_ISO_TILEMAP:
		case LAYER_TYPE_TILEMAP:
		{
			getTileSelectControl()->mapEdit_getContext();
			if(getTileSelectControl()->imageExists( getTileSelectControl()->current_sheet_image ))
				getTileSelectControl()->deleteImage(getTileSelectControl()->current_sheet_image);

			wxFileName gfx_dir(project->getDir());

			if(project)
				gfx_dir.AppendDir(project->tile_path);
			else
				gfx_dir.AppendDir(_("gfx"));

			std::string sheet_file_name = project->getTileset(n_layer.layer_map.nv_tileset_index).file.ToStdString();
			gfx_dir.SetFullName(wxString(sheet_file_name));

			if(sheet_file_name.compare("")!=0)
                getTileSelectControl()->current_sheet_image = getTileSelectControl()->loadImage(gfx_dir.GetAbsolutePath().ToStdString());

			//std::cout << "CURRENT SHEET: " << getTileSelectControl()->current_sheet_image << std::endl;

			//getTileSelectControl()->setActiveCanvas(getTileSelectControl()->sheet_canvas);
			//getTileSelectControl()->drawImage_BlitEx(getTileSelectControl()->current_sheet_image, 0, 0, 4, 256, 0, 0, 512, 256);
		}
		break;

		case LAYER_TYPE_CANVAS_2D:
		{
		}
		break;

		case LAYER_TYPE_CANVAS_3D:
		{
		}
		break;
	}
}

void Nirvana_MapEditor::selectShape(int shape_index)
{
	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;

	selected_shape = shape_index;
	getMapViewControl()->selected_shape = shape_index;


	//getMapViewControl()->collision_poly_draw_flag = false;
	getMapViewControl()->collision_physics_obj.points.clear();
	getMapViewControl()->collision_physics_obj.next_points.clear();
	getMapViewControl()->collision_physics_obj.prev_points.clear();

	if(shape_index < 0 || shape_index >= project->stages[selected_stage].layers[selected_layer].layer_shapes.size())
		return;

	getMapViewControl()->collision_physics_obj.shape_type = project->stages[selected_stage].layers[selected_layer].layer_shapes[shape_index].shape_type;
}

void Nirvana_MapEditor::selectSprite(int sprite_index)
{
	if(selected_stage < 0 || selected_stage >= project->stages.size())
		return;

	if(selected_layer < 0 || selected_layer >= project->stages[selected_stage].layers.size())
		return;

	selected_sprite = sprite_index;
	getMapViewControl()->selected_sprite = sprite_index;


	//getMapViewControl()->collision_poly_draw_flag = false;
	getMapViewControl()->selected_sprite = -1;
	getMapViewControl()->mapEdit_selectSpriteTool_selection.clear();
}

int Nirvana_MapEditor::getSelectedStage()
{
	return selected_stage;
}

int Nirvana_MapEditor::getSelectedLayer()
{
	return selected_layer;
}

int Nirvana_MapEditor::getSelectedShape()
{
	return selected_shape;
}
