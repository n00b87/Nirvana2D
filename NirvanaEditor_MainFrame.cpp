#include "NirvanaEditor_MainFrame.h"
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/arrstr.h>

#include "Nirvana_Project.h"
#include "NirvanaEditor_NewSprite_Dialog.h"
#include "NirvanaEditor_NewTileset_Dialog.h"
#include "NirvanaEditor_SpriteLayer_SelectTileset_Dialog.h"
#include "NirvanaEditor_SpriteLayer_ChangeTilesetWarning_Dialog.h"



NirvanaEditor_MainFrame::NirvanaEditor_MainFrame( wxWindow* parent )
:
Nirvana_MainFrame( parent )
{
	project = new Nirvana_Project();

	tile_editor = new Nirvana_TileEditor(this, m_tileAnimation_tileSheet_panel, m_tileAnimation_tileFrames_panel,
											m_tileAnimation_preview_panel, m_tileMask_tileSheet_panel);

	tile_editor->setProject(project);

	tile_editor->getAnimationSheetControl()->tileEdit_animationMode = TILE_EDIT_ANIMATION_MODE_SELECT;
	tile_editor->getAnimationFrameControl()->tileEdit_animationMode = TILE_EDIT_ANIMATION_MODE_SELECT;

	m_tileEdit_mode_auiToolBar->ToggleTool(m_tileEdit_tileSelect_tool->GetId(), true);

	tile_editor->getAnimationSheetControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());

	sprite_editor = new Nirvana_SpriteEditor(this, m_spriteAnimation_spriteSheet_panel, m_spriteAnimation_frame_panel,
												m_spriteAnimation_preview_panel, m_spriteCollision_edit_panel);

	sprite_editor->setProject(project);

	sprite_editor->getAnimationSheetControl()->GetDevice()->getContextManager()->activateContext(irr::video::SExposedVideoData());
	sprite_editor->getAnimationSheetControl()->update_events = false;

	m_spriteEdit_collisionShape_comboBox->Append(_("BOX"));
	m_spriteEdit_collisionShape_comboBox->Append(_("POLYGON"));
	m_spriteEdit_collisionShape_comboBox->Append(_("CIRCLE"));

	m_layerSettings_spriteGridType_comboBox->Append(_("SQUARE"));
	m_layerSettings_spriteGridType_comboBox->Append(_("ISOMETRIC"));

	m_layerSettings_spriteSortBy_comboBox->Append(_("NONE"));
	m_layerSettings_spriteSortBy_comboBox->Append(_("LEAST X"));
	m_layerSettings_spriteSortBy_comboBox->Append(_("GREATEST X"));
	m_layerSettings_spriteSortBy_comboBox->Append(_("LEAST Y"));
	m_layerSettings_spriteSortBy_comboBox->Append(_("GREATEST Y"));

	m_layerSettings_spriteOrderBy_comboBox->Append(_("ASCENDING"));
	m_layerSettings_spriteOrderBy_comboBox->Append(_("DESCENDING"));

	m_layerSettings_shapeData_comboBox->Append(_("GENERATE SHAPES"));
	m_layerSettings_shapeData_comboBox->Append(_("EXPORT DATA ONLY"));


	map_editor = new Nirvana_MapEditor(this, m_mapEdit_map_panel, m_mapEdit_tileSelect_panel);
	map_editor->getMapViewControl()->GetDevice()->getContextManager()->activateContext(map_editor->getMapViewControl()->GetDevice()->getVideoDriver()->getExposedVideoData());
	map_editor->getMapViewControl()->mapEdit_hasContext = true;
	map_editor->getMapViewControl()->project = project;

	map_editor->getTileSelectControl()->update_events = true;

	map_editor->setProject(project);

	sprite_editor->getAnimationSheetControl()->shared_control.push_back(map_editor->getMapViewControl());
	sprite_editor->getAnimationSheetControl()->shared_control.push_back(map_editor->getTileSelectControl());
	sprite_editor->getAnimationSheetControl()->shared_control.push_back(tile_editor->getAnimationSheetControl());
	sprite_editor->getAnimationSheetControl()->shared_control.push_back(tile_editor->getMaskSheetControl());
	sprite_editor->getAnimationSheetControl()->shared_control.push_back(sprite_editor->getAnimationSheetControl());
	sprite_editor->getAnimationSheetControl()->shared_control.push_back(sprite_editor->getCollisionControl());

	sprite_editor->getCollisionControl()->shared_control.push_back(map_editor->getMapViewControl());
	sprite_editor->getCollisionControl()->shared_control.push_back(map_editor->getTileSelectControl());
	sprite_editor->getCollisionControl()->shared_control.push_back(tile_editor->getAnimationSheetControl());
	sprite_editor->getCollisionControl()->shared_control.push_back(tile_editor->getMaskSheetControl());
	sprite_editor->getCollisionControl()->shared_control.push_back(sprite_editor->getAnimationSheetControl());
	sprite_editor->getCollisionControl()->shared_control.push_back(sprite_editor->getCollisionControl());

	tile_editor->getAnimationSheetControl()->shared_control.push_back(map_editor->getMapViewControl());
	tile_editor->getAnimationSheetControl()->shared_control.push_back(map_editor->getTileSelectControl());
	tile_editor->getAnimationSheetControl()->shared_control.push_back(tile_editor->getAnimationSheetControl());
	tile_editor->getAnimationSheetControl()->shared_control.push_back(tile_editor->getMaskSheetControl());
	tile_editor->getAnimationSheetControl()->shared_control.push_back(sprite_editor->getAnimationSheetControl());
	tile_editor->getAnimationSheetControl()->shared_control.push_back(sprite_editor->getCollisionControl());

	tile_editor->getMaskSheetControl()->shared_control.push_back(map_editor->getMapViewControl());
	tile_editor->getMaskSheetControl()->shared_control.push_back(map_editor->getTileSelectControl());
	tile_editor->getMaskSheetControl()->shared_control.push_back(tile_editor->getAnimationSheetControl());
	tile_editor->getMaskSheetControl()->shared_control.push_back(tile_editor->getMaskSheetControl());
	tile_editor->getMaskSheetControl()->shared_control.push_back(sprite_editor->getAnimationSheetControl());
	tile_editor->getMaskSheetControl()->shared_control.push_back(sprite_editor->getCollisionControl());

	map_editor->getMapViewControl()->shared_control.push_back(map_editor->getMapViewControl());
	map_editor->getMapViewControl()->shared_control.push_back(map_editor->getTileSelectControl());
	map_editor->getMapViewControl()->shared_control.push_back(tile_editor->getAnimationSheetControl());
	map_editor->getMapViewControl()->shared_control.push_back(tile_editor->getMaskSheetControl());
	map_editor->getMapViewControl()->shared_control.push_back(sprite_editor->getAnimationSheetControl());
	map_editor->getMapViewControl()->shared_control.push_back(sprite_editor->getCollisionControl());

	map_editor->getTileSelectControl()->shared_control.push_back(map_editor->getMapViewControl());
	map_editor->getTileSelectControl()->shared_control.push_back(map_editor->getTileSelectControl());
	map_editor->getTileSelectControl()->shared_control.push_back(tile_editor->getAnimationSheetControl());
	map_editor->getTileSelectControl()->shared_control.push_back(tile_editor->getMaskSheetControl());
	map_editor->getTileSelectControl()->shared_control.push_back(sprite_editor->getAnimationSheetControl());
	map_editor->getTileSelectControl()->shared_control.push_back(sprite_editor->getCollisionControl());

	map_editor->getTileSelectControl()->stage_edit_control = map_editor->getMapViewControl();

	editor_init = true;


	stage_tree_imageList = new wxImageList(16,16,true);
    stage_tree_rootImage = stage_tree_imageList->Add(wxArtProvider::GetBitmap( wxART_FOLDER, wxART_MENU ));
    stage_tree_stageImage  = stage_tree_imageList->Add(wxArtProvider::GetBitmap( wxART_NORMAL_FILE, wxART_MENU ));

    m_project_treeCtrl->AssignImageList(stage_tree_imageList);

	project_root_treeItem = m_project_treeCtrl->AddRoot(wxString::FromUTF8(_("NO PROJECT")), stage_tree_rootImage);


	m_mapSet_auiToolBar->ToggleTool(m_mapSet_free_tool->GetId(), true);


	wxPGChoices choices;
	choices.Clear();

	choices.Add(_("STATIC"));
	choices.Add(_("KINEMATIC"));
	choices.Add(_("DYNAMIC"));

	m_mapEdit_sprite_propertyGrid->GetProperty(_("body_type"))->SetChoices(choices);

	wxPGProperty * sprite_pos_x = m_mapEdit_sprite_propertyGrid->GetProperty(_("position_x"));
	wxPGProperty * sprite_pos_y = m_mapEdit_sprite_propertyGrid->GetProperty(_("position_y"));
	wxPGProperty * sprite_angle = m_mapEdit_sprite_propertyGrid->GetProperty(_("angle"));
	wxPGProperty * sprite_scale_x = m_mapEdit_sprite_propertyGrid->GetProperty(_("scale_x"));
	wxPGProperty * sprite_scale_y = m_mapEdit_sprite_propertyGrid->GetProperty(_("scale_y"));

	map_editor->getMapViewControl()->nv_sprite_positionX_property = sprite_pos_x;
    map_editor->getMapViewControl()->nv_sprite_positionY_property = sprite_pos_y;
    map_editor->getMapViewControl()->nv_sprite_angle_property = sprite_angle;
    map_editor->getMapViewControl()->nv_sprite_scaleX_property = sprite_scale_x;
    map_editor->getMapViewControl()->nv_sprite_scaleY_property = sprite_scale_y;


    map_editor->getMapViewControl()->m_cameraAbsoluteX_staticText = m_cameraAbsoluteX_staticText;
	map_editor->getMapViewControl()->m_cameraAbsoluteY_staticText = m_cameraAbsoluteY_staticText;
	map_editor->getMapViewControl()->m_cameraTileX_staticText = m_cameraTileX_staticText;
	map_editor->getMapViewControl()->m_cameraTileY_staticText = m_cameraTileY_staticText;

	map_editor->getMapViewControl()->m_stageAbsoluteX_staticText = m_stageAbsoluteX_staticText;
	map_editor->getMapViewControl()->m_stageAbsoluteY_staticText = m_stageAbsoluteY_staticText;
	map_editor->getMapViewControl()->m_stageTileX_staticText = m_stageTileX_staticText;
	map_editor->getMapViewControl()->m_stageTileY_staticText = m_stageTileY_staticText;

	map_editor->getMapViewControl()->m_screenAbsoluteX_staticText = m_screenAbsoluteX_staticText;
	map_editor->getMapViewControl()->m_screenAbsoluteY_staticText = m_screenAbsoluteY_staticText;

	map_editor->getMapViewControl()->m_mapEdit_boxShape_posX_spinCtrl = m_mapEdit_boxShape_posX_spinCtrl;
	map_editor->getMapViewControl()->m_mapEdit_boxShape_posY_spinCtrl = m_mapEdit_boxShape_posY_spinCtrl;
	map_editor->getMapViewControl()->m_mapEdit_boxShape_width_spinCtrl = m_mapEdit_boxShape_width_spinCtrl;
	map_editor->getMapViewControl()->m_mapEdit_boxShape_height_spinCtrl = m_mapEdit_boxShape_height_spinCtrl;

	map_editor->getMapViewControl()->m_mapEdit_polyShape_grid = m_mapEdit_polyShape_grid;

	map_editor->getMapViewControl()->m_mapEdit_circleShape_centerX_spinCtrl = m_mapEdit_circleShape_centerX_spinCtrl;
	map_editor->getMapViewControl()->m_mapEdit_circleShape_centerY_spinCtrl = m_mapEdit_circleShape_centerY_spinCtrl;
	map_editor->getMapViewControl()->m_mapEdit_circleShape_radius_spinCtrl = m_mapEdit_circleShape_radius_spinCtrl;

	map_editor->getMapViewControl()->m_mapEdit_collisionShape_listBox = m_mapEdit_collisionShape_listBox;


	//Default settings
	map_editor->getMapViewControl()->show_grid = false;
	map_editor->getMapViewControl()->show_shapes_all = false;


	//load config
	wxFileName fname(wxStandardPaths::Get().GetExecutablePath());
	fname.AppendDir(_("config"));
	fname.SetFullName(_("nirvana.config"));

	if(!fname.Exists())
	{
		//Create config file if it doesn't exists
		wxFile cfg_file(fname.GetAbsolutePath(), wxFile::write);

		if(cfg_file.IsOpened())
		{
			cfg_file.Write(_("MAP_EDITOR_MAP_CONTROL scroll_speed=3 show_grid=true grid_color=") + wxString::Format(_("%u"), irr::video::SColor(255,100,100,100).color) + _(" show_shapes=true;") + _("\n"));
			cfg_file.Write(_("MAP_EDITOR_TILE_SELECT_CONTROL scroll_speed=3;") + _("\n"));
			cfg_file.Write(_("TILE_EDITOR_ANIMATION_SHEET_CONTROL scroll_speed=3;") + _("\n"));
			cfg_file.Write(_("TILE_EDITOR_MASK_SHEET_CONTROL scroll_speed=3;") + _("\n"));
			cfg_file.Write(_("SPRITE_EDITOR_ANIMATION_SHEET_CONTROL scroll_speed=3;") + _("\n"));
			cfg_file.Write(_("SPRITE_EDITOR_SHAPE_SHEET_CONTROL scroll_speed=3;") + _("\n"));

			cfg_file.Close();
		}
	}

	if(fname.Exists())
	{
		wxFile cfg_file(fname.GetAbsolutePath());
		wxString p_data = _("");

		if(cfg_file.IsOpened())
		{
			cfg_file.ReadAll(&p_data);
			cfg_file.Close();
		}

		std::vector<nirvana_project_file_obj> p_cmd = project->getParams(p_data);

		for(int i = 0; i < p_cmd.size(); i++)
		{
			if(p_cmd[i].dict.size() == 0)
				continue;

			if(p_cmd[i].dict[0].key.compare(_("MAP_EDITOR_MAP_CONTROL"))==0)
			{
				for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
				{
					if(p_cmd[i].dict[obj_index].key.compare(_("scroll_speed"))==0)
					{
						p_cmd[i].dict[obj_index].val.ToInt(&map_editor->getMapViewControl()->scroll_speed);
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("show_grid"))==0)
					{
						map_editor->getMapViewControl()->show_grid = ( (p_cmd[i].dict[obj_index].val.Lower().Trim().compare(_("true"))==0) ? true : false );
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("grid_color"))==0)
					{
						unsigned int g_color = 0;
						p_cmd[i].dict[obj_index].val.ToUInt(&g_color);
						map_editor->getMapViewControl()->grid_color.set(g_color);
					}
					else if(p_cmd[i].dict[obj_index].key.compare(_("show_shapes"))==0)
					{
						map_editor->getMapViewControl()->show_shapes_all = ( (p_cmd[i].dict[obj_index].val.Lower().Trim().compare(_("true"))==0) ? true : false );
					}
				}
			}
			else if(p_cmd[i].dict[0].key.compare(_("TILE_SELECT_CONTROL"))==0)
			{
				for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
				{
					if(p_cmd[i].dict[obj_index].key.compare(_("scroll_speed"))==0)
					{
						int speed = 1;
						p_cmd[i].dict[obj_index].val.ToInt(&speed);

						map_editor->getTileSelectControl()->scroll_speed = speed;
                        tile_editor->getAnimationSheetControl()->scroll_speed = speed;
                        tile_editor->getMaskSheetControl()->scroll_speed = speed;
					}
				}
			}
			else if(p_cmd[i].dict[0].key.compare(_("SPRITE_SELECT_CONTROL"))==0)
			{
				for(int obj_index = 1; obj_index < p_cmd[i].dict.size(); obj_index++)
				{
					if(p_cmd[i].dict[obj_index].key.compare(_("scroll_speed"))==0)
					{
					    int speed = 1;
						p_cmd[i].dict[obj_index].val.ToInt(&speed);

						sprite_editor->getAnimationSheetControl()->scroll_speed = speed;
                        sprite_editor->getCollisionControl()->scroll_speed = speed;
					}
				}
			}
		}
	}

	m_mapEdit_showShapes_checkBox->SetValue( map_editor->getMapViewControl()->show_shapes_all );
	m_mapEdit_showGrid_checkBox->SetValue( map_editor->getMapViewControl()->show_grid );
	m_mapEdit_gridColor_colourPicker->SetColour( wxColour( map_editor->getMapViewControl()->grid_color.getRed(),
														   map_editor->getMapViewControl()->grid_color.getGreen(),
														   map_editor->getMapViewControl()->grid_color.getBlue(),
														   255 ) );
	m_mapEdit_cameraSpeed_spinCtrl->SetValue( map_editor->getMapViewControl()->scroll_speed );

	m_mapEdit_tileSelect_Speed_spinCtrl->SetValue( map_editor->getTileSelectControl()->scroll_speed );
	m_mapEdit_spriteSelect_Speed_spinCtrl->SetValue( sprite_editor->getAnimationSheetControl()->scroll_speed );



	map_editor->getMapViewControl()->force_refresh();
	map_editor->getMapViewControl()->is_tile_select_screen = true;
}

void NirvanaEditor_MainFrame::OnNirvanaClose( wxCloseEvent& event )
{
    //On Windows, writing the config file on close doesn't seem to work
    #ifdef _WIN32
    Close();
    #endif // _WIN32

	wxFileName fname(wxStandardPaths::Get().GetExecutablePath());
	fname.AppendDir(_("config"));
	fname.SetFullName(_("nirvana.config"));

	//Create config file if it doesn't exists
	wxFile cfg_file(fname.GetAbsolutePath(), wxFile::write);

	if(cfg_file.IsOpened())
	{
		wxString map_control_config = _("MAP_EDITOR_MAP_CONTROL ");
		map_control_config += _("scroll_speed=") + wxString::Format(_("%i"), map_editor->getMapViewControl()->scroll_speed) + _(" ");
		map_control_config += _("show_grid=") + (map_editor->getMapViewControl()->show_grid ? _("true") : _("false")) + _(" ");
		map_control_config += _("grid_color=") + wxString::Format(_("%u"), map_editor->getMapViewControl()->grid_color.color) + _(" ");
		map_control_config += _("show_shapes=") + (map_editor->getMapViewControl()->show_shapes_all ? _("true") : _("false")) + _(";");

		wxString tileSelect_control_config = _("TILE_SELECT_CONTROL ");
		tileSelect_control_config += _("scroll_speed=") + wxString::Format(_("%i"), map_editor->getTileSelectControl()->scroll_speed) + _(";");

		wxString spriteSelect_control_config = _("SPRITE_SELECT_CONTROL ");
		spriteSelect_control_config += _("scroll_speed=") + wxString::Format(_("%i"), sprite_editor->getAnimationSheetControl()->scroll_speed) + _(";");


		cfg_file.Write(map_control_config + _("\n"));
		cfg_file.Write(tileSelect_control_config + _("\n"));
		cfg_file.Write(spriteSelect_control_config + _("\n"));

		cfg_file.Close();
	}

	Close();
}

void NirvanaEditor_MainFrame::PreDialog()
{
	map_mapView_update = map_editor->getMapViewControl()->update_events;
	map_tileSelect_update = map_editor->getTileSelectControl()->update_events;
	tile_sheetSelect_update = tile_editor->getAnimationSheetControl()->update_events;
	tile_frameSelect_update = tile_editor->getAnimationFrameControl()->update_events;
	tile_maskSelect_update = tile_editor->getMaskSheetControl()->update_events;
	sprite_sheetSelect_update = sprite_editor->getAnimationSheetControl()->update_events;
	sprite_frameSelect_update = sprite_editor->getAnimationFrameControl()->update_events;
	sprite_collisionSelect_update = sprite_editor->getCollisionControl()->update_events;

	map_editor->getMapViewControl()->update_events = false;
	map_editor->getTileSelectControl()->update_events = false;
	tile_editor->getAnimationSheetControl()->update_events = false;
	tile_editor->getAnimationFrameControl()->update_events = false;
	tile_editor->getMaskSheetControl()->update_events = false;
	sprite_editor->getAnimationSheetControl()->update_events = false;
	sprite_editor->getAnimationFrameControl()->update_events = false;
	sprite_editor->getCollisionControl()->update_events = false;
}

void NirvanaEditor_MainFrame::PostDialog()
{
	map_editor->getMapViewControl()->update_events = map_mapView_update;
	map_editor->getTileSelectControl()->update_events = map_tileSelect_update;
	tile_editor->getAnimationSheetControl()->update_events = tile_sheetSelect_update;
	tile_editor->getAnimationFrameControl()->update_events = tile_frameSelect_update;
	tile_editor->getMaskSheetControl()->update_events = tile_maskSelect_update;
	sprite_editor->getAnimationSheetControl()->update_events = sprite_sheetSelect_update;
	sprite_editor->getAnimationFrameControl()->update_events = sprite_frameSelect_update;
	sprite_editor->getCollisionControl()->update_events = sprite_collisionSelect_update;
}

void NirvanaEditor_MainFrame::OnLayerComboClose( wxCommandEvent& event )
{
	PostDialog();
}

void NirvanaEditor_MainFrame::OnLayerComboOpen( wxCommandEvent& event )
{
	PreDialog();
}

void NirvanaEditor_MainFrame::OnProjectPropertiesTabChanged( wxAuiNotebookEvent& event )
{
}

void NirvanaEditor_MainFrame::OnMapEditToolsTabChanged( wxAuiNotebookEvent& event )
{
	if(!editor_init)
		return;

	int page_index = event.GetSelection();
	wxPanel* new_panel = (wxPanel*)m_mapEdit_layerObjectTools_auinotebook->GetPage(page_index);

	map_editor->getTileSelectControl()->update_events = false;
	map_editor->getMapViewControl()->is_tile_select_screen = false;

	map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.clear();
	map_editor->getMapViewControl()->mapEdit_selectTileTool_selection.clear();
	map_editor->getMapViewControl()->mapEdit_selectTileTool_box.clear();
	map_editor->getMapViewControl()->selected_sprite = -1;

	if(new_panel == m_mapEdit_tile_panel)
	{
		map_editor->startEditor(0);

		//default to select tool
		selected_map_tool = MAP_TOOL_TILE_SELECT;
		map_editor->setMapTool(selected_map_tool);
		m_mapEdit_tileTools_auiToolBar->ToggleTool(m_mapEdit_tileToolbar_select_tool->GetId(), true);
		map_editor->getTileSelectControl()->update_events = true;
		map_editor->getMapViewControl()->is_tile_select_screen = true;
	}
	else if(new_panel == m_mapEdit_sprite_panel)
	{
		map_editor->startEditor(1);

		//default to select tool
		selected_map_tool = MAP_TOOL_SPRITE_SELECT;
		map_editor->setMapTool(selected_map_tool);
		m_mapEdit_spriteTools_auiToolBar->ToggleTool(m_mapEdit_spriteToolbar_select_tool->GetId(), true);
		m_mapEdit_layerSprite_listBox->DeselectAll();
		map_editor->selectSprite(-1);
		map_editor->selectShape(-1);
		map_editor->getMapViewControl()->selected_sprite = -1;
		map_editor->getMapViewControl()->selected_shape = -1;
	}
	else if(new_panel == m_mapEdit_collision_panel)
	{
		map_editor->startEditor(2);

		//default to select tool
		selected_map_tool = MAP_TOOL_SHAPE_SELECT;
		map_editor->setMapTool(selected_map_tool);
		m_mapEdit_shapeTools_auiToolBar->ToggleTool(m_mapEdit_shapeToolbar_select_tool->GetId(), true);
		m_mapEdit_collisionShape_listBox->DeselectAll();
		map_editor->selectSprite(-1);
		map_editor->selectShape(-1);
		map_editor->getMapViewControl()->selected_sprite = -1;
		map_editor->getMapViewControl()->selected_shape = -1;
	}
}

void NirvanaEditor_MainFrame::OnEnterMapEditTileSelect( wxMouseEvent& event )
{
	if(!editor_init)
		return;

	map_editor->getTileSelectControl()->stage_window_isActive = true;
}

void NirvanaEditor_MainFrame::OnLeaveMapEditTileSelect( wxMouseEvent& event )
{
	if(!editor_init)
		return;

	map_editor->getTileSelectControl()->stage_window_isActive = false;
}

void NirvanaEditor_MainFrame::OnUpdateMapEditTileSelect( wxUpdateUIEvent& event )
{
	map_editor->getMapViewControl()->map_tool = selected_map_tool;
}

void NirvanaEditor_MainFrame::OnTileEditor_Edit_Changed( wxAuiNotebookEvent& event )
{
	if(!editor_init)
		return;

	int page_index = event.GetSelection();
	wxPanel* new_panel = (wxPanel*)m_tileEdit_tools_auinotebook->GetPage(page_index);

	tile_editor->stopEditor();

	if(new_panel == m_tileEdit_tileAnimation_panel)
	{
		tile_editor->startEditor(0);
	}
	else if(new_panel == m_tileEdit_tileMask_panel)
	{
		tile_editor->startEditor(1);
	}
}


void NirvanaEditor_MainFrame::OnSetSpriteLayerTileset( wxCommandEvent& event )
{
    if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0)
		return;

    int layer_index = map_editor->getSelectedLayer();

	if(layer_index < 0)
	{
		return;
	}

    if(project->stages[stage_index].layers[layer_index].layer_map.nv_tileset_index >= 0)
    {
        NirvanaEditor_SpriteLayer_ChangeTilesetWarning_Dialog* warning_dialog = new NirvanaEditor_SpriteLayer_ChangeTilesetWarning_Dialog(this);
        PreDialog();
        warning_dialog->ShowModal();
        PostDialog();

        if(!warning_dialog->continue_flag)
            return;
    }


	NirvanaEditor_SpriteLayer_SelectTileset_Dialog* dialog = new NirvanaEditor_SpriteLayer_SelectTileset_Dialog(this);

	int tile_width = project->getStageTileSize(stage_index).X;
	int tile_height = project->getStageTileSize(stage_index).Y;

	for(int i = 0; i < project->getTilesetCount(); i++)
	{
		if(tile_width == project->getTilesetTileSize(i).X && tile_height == project->getTilesetTileSize(i).Y)
			dialog->tileset_list.push_back(wxString(project->getTilesetName(i)));
	}

	dialog->refresh_list();

	PreDialog();
	dialog->ShowModal();
	PostDialog();

	if(!dialog->select_flag)
		return;

    // Delete current tile sprites
	for(int i = 0; i < project->stages[stage_index].layers[layer_index].layer_tile_sprites.size(); i++)
	{
		int map_spr_id = project->stages[stage_index].layers[layer_index].layer_tile_sprites[i].sprite_id;
		map_editor->getMapViewControl()->deleteSprite(map_spr_id);
	}

	project->stages[stage_index].layers[layer_index].layer_tile_sprites.clear();

	map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.clear();
	map_editor->getMapViewControl()->selected_sprite = -1;



	int nv_tileset_index = project->getTilesetIndex(dialog->selected_tileset.ToStdString());

	if(nv_tileset_index < 0)
        return;

	project->setLayerTileset(stage_index, layer_index, nv_tileset_index);

	m_mapEdit_layerTileset_staticText->SetLabelText( wxString(project->getTilesetName( project->getLayerTileset(stage_index, layer_index) )));

	// Update Tile select with tilesheet directly since it was just selected
	map_editor->getTileSelectControl()->mapEdit_getContext();
    if(map_editor->getTileSelectControl()->imageExists( map_editor->getTileSelectControl()->current_sheet_image ))
        map_editor->getTileSelectControl()->deleteImage(map_editor->getTileSelectControl()->current_sheet_image);

    wxFileName gfx_dir(project->getDir());

    if(project)
        gfx_dir.AppendDir(project->tile_path);
    else
        gfx_dir.AppendDir(_("gfx"));

    Nirvana_Map_Layer n_layer = project->getStageLayer(stage_index, layer_index);

    std::string sheet_file_name = project->getTileset(nv_tileset_index).file.ToStdString();

    gfx_dir.SetFullName(wxString(sheet_file_name));

    if(sheet_file_name.compare("")!=0)
        map_editor->getTileSelectControl()->current_sheet_image = map_editor->getTileSelectControl()->loadImage(gfx_dir.GetAbsolutePath().ToStdString());

    //std::cout << "TS Current Sheet: " << map_editor->getTileSelectControl()->current_sheet_image << std::endl;
}


void NirvanaEditor_MainFrame::OnMapEdit_TSTool_Select( wxCommandEvent& event )
{
    if(!editor_init)
		return;

	selected_map_tool = MAP_TOOL_TS_SELECT;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_TSTool_BoxSelect( wxCommandEvent& event )
{
    if(!editor_init)
		return;

	selected_map_tool = MAP_TOOL_TS_BOXSELECT;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_TSTool_Move( wxCommandEvent& event )
{
    if(!editor_init)
		return;

	selected_map_tool = MAP_TOOL_TS_MOVE;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_TSTool_SetTile( wxCommandEvent& event )
{
    if(!editor_init)
		return;

	selected_map_tool = MAP_TOOL_TS_SET;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_TSTool_DeleteSelected( wxCommandEvent& event )
{
    if(!editor_init)
		return;

    if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0)
		return;

	int layer_index = map_editor->getSelectedLayer();
	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	if(project->getLayerType(stage_index, layer_index) != LAYER_TYPE_SPRITE)
	{
		return;
	}

	if(map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.size() == 0)
		return;

	irr::core::array<int> layer_spr_array; //The irrlicht array has built-in sort and I don't feel like doing it myself

	for(int i = 0; i < map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.size(); i++)
	{
		int map_spr_id = map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection[i].layer_sprite_index;
		int spr_index = map_editor->getMapViewControl()->sprite[map_spr_id].layer_ts_index;

		map_editor->getMapViewControl()->deleteSprite(map_spr_id);
		layer_spr_array.push_back(spr_index);
	}

	for(int i = 0; i < layer_spr_array.size(); i++)
	{
		if(i < 0)
			break;

		//std::cout << "array: " << layer_spr_array[i] << ", " << project->stages[stage_index].layers[layer_index].layer_sprites[layer_spr_array[i]].sprite_name << std::endl;

		project->stages[stage_index].layers[layer_index].layer_tile_sprites[layer_spr_array[i]].sprite_id = -1;
		project->stages[stage_index].layers[layer_index].layer_tile_sprites[layer_spr_array[i]].sheet_index = -1;
		project->stages[stage_index].layers[layer_index].layer_tile_sprites[layer_spr_array[i]].image_id = -1;
		project->stages[stage_index].layers[layer_index].layer_tile_sprites[layer_spr_array[i]].cut_index = -1;
		project->stages[stage_index].layers[layer_index].layer_tile_sprites[layer_spr_array[i]].tset = -1;
	}


	map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.clear();
	map_editor->getMapViewControl()->selected_sprite = -1;
}




void NirvanaEditor_MainFrame::OnSpriteEditor_Edit_Changed( wxAuiNotebookEvent& event )
{
	if(!editor_init)
		return;

	int page_index = event.GetSelection();
	wxPanel* new_panel = (wxPanel*)m_spriteEdit_tools_auinotebook->GetPage(page_index);

	sprite_editor->stopEditor();

	if(new_panel == m_spriteEdit_spriteAnimation_panel)
	{
		sprite_editor->startEditor(0);
	}
	else if(new_panel == m_spriteEdit_spriteCollision_panel)
	{
		sprite_editor->startEditor(1);
	}
}

void NirvanaEditor_MainFrame::reloadStage()
{
	if(!editor_init)
		return;

	int stage_index = map_editor->getSelectedStage();
	int layer_index = map_editor->getSelectedLayer();

	//std::cout << "RELOAD: " << stage_index << ", " << layer_index << std::endl;

	map_editor->selectStage(stage_index);
	map_editor->selectLayer(layer_index);

	updateMapEditor();
}

void NirvanaEditor_MainFrame::OnMainTabChanged( wxAuiNotebookEvent& event )
{
	if(!editor_init)
		return;

	int page_index = event.GetSelection();
	wxPanel* new_panel = (wxPanel*)m_editorMainTab_auinotebook->GetPage(page_index);

	switch(main_page_index)
	{
		case NIRVANA_MAIN_PAGE_INDEX_MAP:
			map_editor->stopEditor(true);
		break;

		case NIRVANA_MAIN_PAGE_INDEX_TILE:
			tile_editor->stopEditor();
		break;

		case NIRVANA_MAIN_PAGE_INDEX_SPRITE:
			sprite_editor->stopEditor();
		break;
	}

	if(new_panel == m_mapEdit_panel)
	{
		main_page_index = NIRVANA_MAIN_PAGE_INDEX_MAP;

		map_editor->startEditor(map_editor->getEditorPageIndex(), true);
		map_editor->getMapViewControl()->clearStage();
		reloadStage();
	}
	else if(new_panel == m_tileEdit_panel)
	{
		tile_editor->startEditor(tile_editor->getEditorPageIndex());

		main_page_index = NIRVANA_MAIN_PAGE_INDEX_TILE;
	}
	else if(new_panel == m_spriteEdit_panel)
	{
		sprite_editor->startEditor(sprite_editor->getEditorPageIndex());
		UpdateSpriteEditor();

		main_page_index = NIRVANA_MAIN_PAGE_INDEX_SPRITE;
	}
}

wxArrayString NirvanaEditor_MainFrame::getDirFileList(wxString dir_path, wxString wildcard)
{
	wxDir dir;
	wxString filename;
	wxString filespec = _T("*.*");

	//if(wildcard.compare(_(""))!=0)
	//	filespec = wildcard;

	wxArrayString files_list;

	if ( dir.Open( dir_path ) )
	{
		bool cont = dir.GetFirst(&filename, filespec, wxDIR_FILES);
		while ( cont )
		{
			files_list.Add( filename );
			cont = dir.GetNext(&filename);
		}
	}
	else
	{
		wxMessageBox(_("Error: Could not open dir: ") + dir_path);
	}

	files_list.Sort();

	return files_list;
}


// ------- SPRITE EDITOR ----------------
void NirvanaEditor_MainFrame::UpdateSpriteEditor()
{
	if(!editor_init)
		return;

	int page_index = m_editorMainTab_auinotebook->GetSelection();
	wxPanel* current_panel = (wxPanel*)m_editorMainTab_auinotebook->GetPage(page_index);

	if(current_panel == m_spriteEdit_panel)
	{
		int tool_page_index = m_spriteEdit_tools_auinotebook->GetSelection();
		wxPanel* tool_panel = (wxPanel*)m_spriteEdit_tools_auinotebook->GetPage(tool_page_index);

		if(tool_panel == m_spriteEdit_spriteAnimation_panel)
		{
			sprite_editor->setAnimationView();
		}
		else if(tool_panel == m_spriteEdit_spriteCollision_panel)
		{
			// TODO
		}
	}
}

void NirvanaEditor_MainFrame::OnNewSpriteClicked( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	if(!project->active)
	{
		wxMessageBox(_("You must have an open project."));
		return;
	}

	NirvanaEditor_NewSprite_Dialog* dialog = new NirvanaEditor_NewSprite_Dialog(this);

	wxFileName gfx_path(project->getDir());

	if(project)
		gfx_path.AppendDir(project->sprite_path);
	else
		gfx_path.AppendDir(_("gfx"));

	dialog->files = getDirFileList(gfx_path.GetAbsolutePath());

	dialog->refresh_list();

	dialog->project = project;

	for(int i = 0; i < project->getSpriteCount(); i++)
	{
		dialog->current_sprite_id.push_back(wxString(project->getSpriteBaseName(i)).Trim());
	}

	PreDialog();
	dialog->ShowModal();
	PostDialog();

	if(!dialog->create_flag)
		return;

	wxFileName p_spr_def(project->getDir());
	p_spr_def.AppendDir(project->sprite_path);
	p_spr_def.SetFullName(dialog->selected_file + _(".sprite"));

	int spr_index = -1;

	if(!p_spr_def.Exists())
	{
		if(!project->checkName(dialog->id_name.ToStdString()))
			return;
	}
	else
		spr_index = project->loadSpriteDefinition(dialog->selected_file);

	if(spr_index < 0)
	{
		project->createSprite(dialog->id_name, dialog->selected_file, dialog->frame_width, dialog->frame_height);
		m_spriteEdit_sprite_listBox->AppendAndEnsureVisible(dialog->id_name);
	}
	else
	{
		wxString spr_name = project->sprite_base[spr_index].sprite_name;
		m_spriteEdit_sprite_listBox->AppendAndEnsureVisible(spr_name);
	}
}

void NirvanaEditor_MainFrame::OnDeleteSpriteClicked( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	int list_index = m_spriteEdit_sprite_listBox->GetSelection();

	if(list_index < 0 || list_index >= m_spriteEdit_sprite_listBox->GetCount())
		return;

	int spr_index = sprite_editor->getSelectedSprite();

	if(spr_index < 0 || spr_index >= project->getSpriteCount())
		return;

	project->deleteSprite(spr_index);

	m_spriteEdit_sprite_listBox->Delete(spr_index);
	sprite_editor->selectSprite(_(""));

	m_spriteEdit_sprite_listBox->SetSelection(-1);
	m_spriteEdit_spriteID_textCtrl->SetValue(_(""));
	m_spriteEdit_numFrames_spinCtrl->SetValue(0);
	m_spriteEdit_FPS_spinCtrl->SetValue(0);
	m_spriteEdit_animationID_textCtrl->SetValue(_(""));
	m_spriteEdit_animation_listBox->Clear();

	m_spriteEdit_collisionBox_X_spinCtrl->SetValue(0);
	m_spriteEdit_collisionBox_Y_spinCtrl->SetValue(0);
	m_spriteEdit_collisionBox_Width_spinCtrl->SetValue(0);
	m_spriteEdit_collisionBox_Height_spinCtrl->SetValue(0);

	m_spriteEdit_collisionPolygon_grid->ClearGrid();

	m_spriteEdit_collisionCircle_X_spinCtrl->SetValue(0);
	m_spriteEdit_collisionCircle_Y_spinCtrl->SetValue(0);
	m_spriteEdit_collisionCircle_Radius_spinCtrl->SetValue(0);
}

void NirvanaEditor_MainFrame::OnSpriteEdit_Sprite_Selected( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	int selected_index = event.GetSelection();
	wxString sprite_name = m_spriteEdit_sprite_listBox->GetString(selected_index);

	int spriteEdit_current_tab = m_spriteEdit_tools_auinotebook->GetSelection();
	spriteEdit_current_tab = spriteEdit_current_tab < 0 ? 0 : spriteEdit_current_tab;

	sprite_editor->selectSprite(sprite_name);

	int spr_id = sprite_editor->getSelectedSprite();
	if(spr_id < 0)
		return;

	m_spriteEdit_spriteID_textCtrl->SetValue(sprite_name);

	m_spriteEdit_animationID_textCtrl->SetValue(_(""));
	m_spriteEdit_animation_listBox->Clear();

	sprite2D_obj n_sprite = project->getSprite(spr_id).object;

	m_spriteEdit_frameSize_staticText->SetLabel(wxString::Format(_("%i"), n_sprite.frame_size.Width)  + _(" x ") + wxString::Format(_("%i"), n_sprite.frame_size.Height));

	//std::cout << "N_SPRT2: " << n_sprite.physics.offset_x << std::endl;

	for(int i = 0; i < n_sprite.animation.size(); i++)
	{
		m_spriteEdit_animation_listBox->AppendAndEnsureVisible(wxString(n_sprite.animation[i].name));
	}

	sprite_editor->getAnimationSheetControl()->scroll_offset_x = 0;
	sprite_editor->getAnimationSheetControl()->scroll_offset_y = 0;

	m_spriteEdit_detachShape_checkBox->SetValue(n_sprite.physics.detached);

	//Set Physics Stuff
	switch(n_sprite.physics.shape_type)
	{
		case SPRITE_SHAPE_BOX:
			m_spriteEdit_collisionShape_comboBox->SetSelection(0);
			m_spriteCollision_shape_simplebook->SetSelection(0);

			//std::cout << "n_sprite physics = " << n_sprite.physics.offset_x << ", " << n_sprite.physics.offset_y << std::endl;

			m_spriteEdit_collisionBox_X_spinCtrl->SetValue(n_sprite.physics.offset_x);
			m_spriteEdit_collisionBox_Y_spinCtrl->SetValue(n_sprite.physics.offset_y);
			m_spriteEdit_collisionBox_Width_spinCtrl->SetValue(n_sprite.physics.box_width);
			m_spriteEdit_collisionBox_Height_spinCtrl->SetValue(n_sprite.physics.box_height);
		break;

		case SPRITE_SHAPE_POLYGON:
			m_spriteEdit_collisionShape_comboBox->SetSelection(1);
			m_spriteCollision_shape_simplebook->SetSelection(1);

			if(m_spriteEdit_collisionPolygon_grid->GetNumberRows() > 0)
				m_spriteEdit_collisionPolygon_grid->DeleteRows(0, m_spriteEdit_collisionPolygon_grid->GetNumberRows());

			for(int i = 0; i < n_sprite.physics.points.size(); i++)
			{
				m_spriteEdit_collisionPolygon_grid->AppendRows();
				m_spriteEdit_collisionPolygon_grid->SetCellValue(i, 0, wxString::Format(_("%i"), (int)n_sprite.physics.points[i].X));
				m_spriteEdit_collisionPolygon_grid->SetCellValue(i, 1, wxString::Format(_("%i"), (int)n_sprite.physics.points[i].Y));
			}
		break;

		case SPRITE_SHAPE_CIRCLE:
			m_spriteEdit_collisionShape_comboBox->SetSelection(2);
			m_spriteCollision_shape_simplebook->SetSelection(2);

			m_spriteEdit_collisionCircle_X_spinCtrl->SetValue(n_sprite.physics.offset_x);
			m_spriteEdit_collisionCircle_Y_spinCtrl->SetValue(n_sprite.physics.offset_y);
			m_spriteEdit_collisionCircle_Radius_spinCtrl->SetValue(n_sprite.physics.radius);
		break;
	}

	m_spriteEdit_tools_auinotebook->SetSelection(spriteEdit_current_tab);
}

void NirvanaEditor_MainFrame::OnSpriteEdit_Animation_Selected( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	int selected_index = event.GetSelection();
	wxString ani_name = m_spriteEdit_animation_listBox->GetString(selected_index);

	sprite_editor->selectAnimation(ani_name);

	int spr_id = sprite_editor->getSelectedSprite();
	int ani_id = sprite_editor->getSelectedAnimation();

	if(spr_id < 0 || spr_id >= project->getSpriteCount())
		return;

	if(ani_id < 0 || ani_id >= project->getSpriteNumAnimations(spr_id))
		return;

	m_spriteEdit_animationID_textCtrl->SetValue(ani_name);
	m_spriteEdit_numFrames_spinCtrl->SetValue(project->getSpriteNumAnimationFrames(spr_id, ani_id));
	m_spriteEdit_FPS_spinCtrl->SetValue(project->getSpriteAnimationFPS(spr_id, ani_id));

	sprite_editor->getAnimationFrameControl()->scroll_offset_x = 0;
}

void NirvanaEditor_MainFrame::OnSpriteEdit_NewAnimation_Click( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	int animation_id = sprite_editor->newAnimation();
	int spr_id = sprite_editor->getSelectedSprite();

	if(spr_id < 0 || spr_id >= project->getSpriteCount())
		return;

	sprite2D_obj n_sprite = project->getSprite(spr_id).object;
	if(animation_id < 0 || animation_id >= n_sprite.animation.size())
		return;

	m_spriteEdit_animation_listBox->AppendAndEnsureVisible(wxString(n_sprite.animation[animation_id].name));
}

void NirvanaEditor_MainFrame::OnSpriteEdit_DeleteAnimation_Click( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	int spr_id = sprite_editor->getSelectedSprite();

	//sprite and animation bounds checks are done in deleteAnimation()
	sprite_editor->deleteAnimation();

	m_spriteEdit_animation_listBox->Clear();

	sprite2D_obj n_sprite = project->getSprite(spr_id).object;

	for(int i = 0; i < n_sprite.animation.size(); i++)
	{
		m_spriteEdit_animation_listBox->AppendAndEnsureVisible(wxString(n_sprite.animation[i].name));
	}
}

void NirvanaEditor_MainFrame::OnSpriteEdit_SpriteIDChanged( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	int list_index = m_spriteEdit_sprite_listBox->GetSelection();

	if(list_index < 0 || list_index >= m_spriteEdit_sprite_listBox->GetCount())
		return;

	int spr_id = sprite_editor->getSelectedSprite();

	if(spr_id < 0 || spr_id >= project->getSpriteCount())
		return;

	wxString new_value = m_spriteEdit_spriteID_textCtrl->GetValue();

	wxString test_id = new_value.Upper().Trim();
	for(int i = 0; i < project->getSpriteCount(); i++)
	{
		if(wxString(project->getSpriteBaseName(i)).Upper().Trim().compare(test_id)==0)
			return;
	}

	m_spriteEdit_sprite_listBox->SetString(list_index, new_value);
	project->setSpriteName(spr_id, new_value.ToStdString());
}

void NirvanaEditor_MainFrame::OnSpriteEdit_AnimationIDChanged( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	int list_index = m_spriteEdit_animation_listBox->GetSelection();

	if(list_index < 0 || list_index >= m_spriteEdit_animation_listBox->GetCount())
		return;

	int spr_id = sprite_editor->getSelectedSprite();

	if(spr_id < 0 || spr_id >= project->getSpriteCount())
		return;

	int ani_id = sprite_editor->getSelectedAnimation();

	if(ani_id < 0 || ani_id >= project->getSpriteNumAnimations(spr_id))
		return;

	wxString new_value = m_spriteEdit_animationID_textCtrl->GetValue();

	wxString test_id = new_value.Upper().Trim();
	for(int i = 0; i < project->sprite_base[spr_id].object.animation.size(); i++)
	{
		if(wxString(project->sprite_base[spr_id].object.animation[i].name).Upper().Trim().compare(test_id)==0)
			return;
	}

	m_spriteEdit_animation_listBox->SetString(list_index, new_value);
	project->setSpriteAnimationName(spr_id, list_index, new_value.ToStdString());
}

void NirvanaEditor_MainFrame::OnSpriteEdit_NumFramesChange( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	int spr_id = sprite_editor->getSelectedSprite();

	if(spr_id < 0 || spr_id >= project->getSpriteCount())
		return;

	int ani_id = sprite_editor->getSelectedAnimation();

	if(ani_id < 0 || ani_id >= project->getSpriteNumAnimations(spr_id))
		return;

	int new_frame_count = event.GetValue();

	if(new_frame_count < 0 || new_frame_count >= m_spriteEdit_numFrames_spinCtrl->GetMax())
		return;

	project->setSpriteNumAnimationFrames(spr_id, ani_id, new_frame_count);
	sprite_editor->updateSpriteAnimation();
}

void NirvanaEditor_MainFrame::OnSpriteEdit_FPSChanged( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	int spr_id = sprite_editor->getSelectedSprite();

	if(spr_id < 0 || spr_id >= project->getSpriteCount())
		return;

	int ani_id = sprite_editor->getSelectedAnimation();

	if(ani_id < 0 || ani_id >= project->getSpriteNumAnimations(spr_id))
		return;

	int new_fps = event.GetValue();

	if(new_fps < 0 || new_fps >= m_spriteEdit_FPS_spinCtrl->GetMax())
		return;

	project->setSpriteAnimationFPS(spr_id, ani_id, new_fps);
	sprite_editor->updateSpriteAnimation();
}

void NirvanaEditor_MainFrame::OnSpriteEdit_PreviousFrame_Click( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	int spr_id = sprite_editor->getSelectedSprite();

	if(spr_id < 0 || spr_id >= project->getSpriteCount())
		return;

	int ani_id = sprite_editor->getSelectedAnimation();

	if(ani_id < 0 || ani_id >= project->getSpriteNumAnimations(spr_id))
		return;

	int new_offset = sprite_editor->getAnimationFrameControl()->scroll_offset_x - 64;

	sprite_editor->getAnimationFrameControl()->scroll_offset_x = new_offset;
}

void NirvanaEditor_MainFrame::OnSpriteEdit_NextFrame_Click( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	int spr_id = sprite_editor->getSelectedSprite();

	if(spr_id < 0 || spr_id >= project->getSpriteCount())
		return;

	int ani_id = sprite_editor->getSelectedAnimation();

	if(ani_id < 0 || ani_id >= project->getSpriteNumAnimations(spr_id))
		return;

	int new_offset = sprite_editor->getAnimationFrameControl()->scroll_offset_x + 64;

	sprite_editor->getAnimationFrameControl()->scroll_offset_x = new_offset;
}

void NirvanaEditor_MainFrame::OnUpdateSpriteAnimationUI( wxUpdateUIEvent& event )
{
	if(!editor_init)
		return;

	int sheet_selected_frame = sprite_editor->getAnimationSheetControl()->selected_frame;
	int frame_selected_frame = sprite_editor->getAnimationFrameControl()->selected_frame;
	int spr_index = sprite_editor->getSelectedSprite();
	int ani_index = sprite_editor->getSelectedAnimation();

	if(spr_index >= 0 && spr_index < project->getSpriteCount())
	{
		//Collision stuff
		if(sprite_editor->getCollisionControl()->collision_object_modified)
		{
			project->setSpritePhysics(spr_index, sprite_editor->getCollisionControl()->collision_physics_obj);
			sprite_editor->getCollisionControl()->collision_object_modified = false;

			sprite2D_physics_obj physics = project->getSpritePhysics(spr_index);

			//std::cout << "Physics Update: " << physics.offset_x << ", " << physics.offset_y << std::endl;

			switch(physics.shape_type)
			{
				case SPRITE_SHAPE_BOX:
					m_spriteEdit_collisionBox_X_spinCtrl->SetValue(physics.offset_x);
					m_spriteEdit_collisionBox_Y_spinCtrl->SetValue(physics.offset_y);
					m_spriteEdit_collisionBox_Width_spinCtrl->SetValue(physics.box_width);
					m_spriteEdit_collisionBox_Height_spinCtrl->SetValue(physics.box_height);
				break;

				case SPRITE_SHAPE_POLYGON:
					if(m_spriteEdit_collisionPolygon_grid->GetNumberRows() > 0)
						m_spriteEdit_collisionPolygon_grid->DeleteRows(0, m_spriteEdit_collisionPolygon_grid->GetNumberRows());

					for(int i = 0; i < physics.points.size(); i++)
					{
						m_spriteEdit_collisionPolygon_grid->AppendRows();
						m_spriteEdit_collisionPolygon_grid->SetCellValue(i, 0, wxString::Format(_("%i"), (int)physics.points[i].X));
						m_spriteEdit_collisionPolygon_grid->SetCellValue(i, 1, wxString::Format(_("%i"), (int)physics.points[i].Y));
					}
				break;

				case SPRITE_SHAPE_CIRCLE:
					m_spriteEdit_collisionCircle_X_spinCtrl->SetValue(physics.offset_x);
					m_spriteEdit_collisionCircle_Y_spinCtrl->SetValue(physics.offset_y);
					m_spriteEdit_collisionCircle_Radius_spinCtrl->SetValue(physics.radius);
				break;
			}
		}

		//Animation stuff
		if(ani_index >= 0 && ani_index < project->getSpriteNumAnimations(spr_index))
		{
			if(frame_selected_frame >= 0 && frame_selected_frame < project->getSpriteNumAnimationFrames(spr_index, ani_index))
			{
				if(sheet_selected_frame >= 0) //Its set to -1 if outside the sprite sheet so I am not wasting my time checking here. Also, I am fucking lazy.
				{
					//std::cout << "Set frames: " << frame_selected_frame << " -> " << sheet_selected_frame  << std::endl;
					project->setSpriteAnimationFrame(spr_index, ani_index, frame_selected_frame, sheet_selected_frame);
					sprite_editor->updateSpriteAnimation();
				}
			}
		}
	}

	sprite_editor->getAnimationSheetControl()->selected_frame = -1;
}

void NirvanaEditor_MainFrame::OnSpriteEdit_PlayPreviewClick( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	sprite_editor->getAnimationPreviewControl()->setSpriteAnimation(sprite_editor->getAnimationPreviewControl()->spriteEdit_selected_sprite,
																	sprite_editor->getSelectedAnimation(), -1);
	sprite_editor->updateSpriteAnimation();
}

void NirvanaEditor_MainFrame::OnSpriteEdit_StopPreviewClick( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	sprite_editor->getAnimationPreviewControl()->setSpriteAnimation(sprite_editor->getAnimationPreviewControl()->spriteEdit_selected_sprite,
																	0, 0);
	sprite_editor->updateSpriteAnimation();
}

void NirvanaEditor_MainFrame::OnEnterSpriteAnimationSheet( wxMouseEvent& event )
{
	if(!editor_init)
		return;

	//std::cout << "ENTER" << std::endl;
	sprite_editor->getAnimationSheetControl()->stage_window_isActive = true;
}

void NirvanaEditor_MainFrame::OnLeaveSpriteAnimationSheet( wxMouseEvent& event )
{
	if(!editor_init)
		return;

	sprite_editor->getAnimationSheetControl()->stage_window_isActive = false;
	//std::cout << "LEAVE" << std::endl;
}


void NirvanaEditor_MainFrame::OnSpriteAnimationSheetSize( wxSizeEvent& event )
{
}



// SPRITE COLLISION
void NirvanaEditor_MainFrame::OnSpriteEdit_CollisionShapeDetached_Check( wxCommandEvent& event )
{
    if(!editor_init)
		return;

	int spr_id = sprite_editor->getSelectedSprite();
	if(spr_id < 0)
		return;

    project->setSpriteCollision_Detach(spr_id, event.IsChecked());
}

void NirvanaEditor_MainFrame::OnSpriteEdit_ShapeSelect( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	int shape_index = event.GetSelection();

	//There are currently only 3 sprite shapes supported in the sprite editor.
	//The chain shape is only accessible in the map editor
	if(shape_index < 0 || shape_index >= 3)
		return;

	m_spriteCollision_shape_simplebook->SetSelection(shape_index);

	m_spriteEdit_collisionBox_X_spinCtrl->SetValue(0);
	m_spriteEdit_collisionBox_Y_spinCtrl->SetValue(0);
	m_spriteEdit_collisionBox_Width_spinCtrl->SetValue(0);
	m_spriteEdit_collisionBox_Height_spinCtrl->SetValue(0);

	if(m_spriteEdit_collisionPolygon_grid->GetNumberRows() > 0)
		m_spriteEdit_collisionPolygon_grid->DeleteRows(0, m_spriteEdit_collisionPolygon_grid->GetNumberRows());

	m_spriteEdit_collisionCircle_X_spinCtrl->SetValue(0);
	m_spriteEdit_collisionCircle_Y_spinCtrl->SetValue(0);
	m_spriteEdit_collisionCircle_Radius_spinCtrl->SetValue(0);

	int spr_id = sprite_editor->getSelectedSprite();
	if(spr_id < 0)
		return;

	sprite2D_obj n_sprite = project->getSprite(spr_id).object;

	//Set Physics Stuff
	switch(shape_index+1)
	{
		case SPRITE_SHAPE_BOX:
			project->setSpriteCollision_Shape(spr_id, SPRITE_SHAPE_BOX);
		break;

		case SPRITE_SHAPE_POLYGON:
			project->setSpriteCollision_Shape(spr_id, SPRITE_SHAPE_POLYGON);
		break;

		case SPRITE_SHAPE_CIRCLE:
			project->setSpriteCollision_Shape(spr_id, SPRITE_SHAPE_CIRCLE);
		break;
	}

	n_sprite = project->getSprite(spr_id).object; // re-pulling sprite since it has changed with the last switch

	//Set Physics Stuff
	switch(n_sprite.physics.shape_type)
	{
		case SPRITE_SHAPE_BOX:
			m_spriteEdit_collisionBox_X_spinCtrl->SetValue(n_sprite.physics.offset_x);
			m_spriteEdit_collisionBox_Y_spinCtrl->SetValue(n_sprite.physics.offset_y);
			m_spriteEdit_collisionBox_Width_spinCtrl->SetValue(n_sprite.physics.box_width);
			m_spriteEdit_collisionBox_Height_spinCtrl->SetValue(n_sprite.physics.box_height);
		break;

		case SPRITE_SHAPE_POLYGON:
			if(m_spriteEdit_collisionPolygon_grid->GetNumberRows() > 0)
				m_spriteEdit_collisionPolygon_grid->DeleteRows(0, m_spriteEdit_collisionPolygon_grid->GetNumberRows());

			for(int i = 0; i < n_sprite.physics.points.size(); i++)
			{
				m_spriteEdit_collisionPolygon_grid->AppendRows();
				m_spriteEdit_collisionPolygon_grid->SetCellValue(i, 0, wxString::Format(_("%i"), (int)n_sprite.physics.points[i].X));
				m_spriteEdit_collisionPolygon_grid->SetCellValue(i, 1, wxString::Format(_("%i"), (int)n_sprite.physics.points[i].Y));
			}
		break;

		case SPRITE_SHAPE_CIRCLE:
			m_spriteEdit_collisionCircle_X_spinCtrl->SetValue(n_sprite.physics.offset_x);
			m_spriteEdit_collisionCircle_Y_spinCtrl->SetValue(n_sprite.physics.offset_y);
			m_spriteEdit_collisionCircle_Radius_spinCtrl->SetValue(n_sprite.physics.radius);
		break;
	}

	sprite_editor->getCollisionControl()->collision_physics_obj = project->getSpritePhysics(sprite_editor->getSelectedSprite());
}

void NirvanaEditor_MainFrame::OnSpriteEdit_Collision_Select_Click( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	sprite_editor->getCollisionControl()->collision_tool = COLLISION_TOOL_SELECT;
}

void NirvanaEditor_MainFrame::OnSpriteEdit_Collision_BoxSelect_Click( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	sprite_editor->getCollisionControl()->collision_tool = COLLISION_TOOL_BOX_SELECT;
}

void NirvanaEditor_MainFrame::OnSpriteEdit_Collision_Move_Click( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	sprite_editor->getCollisionControl()->collision_tool = COLLISION_TOOL_MOVE;
}

void NirvanaEditor_MainFrame::OnSpriteEdit_Collision_Draw_Click( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	sprite_editor->getCollisionControl()->collision_tool = COLLISION_TOOL_DRAW;
}

void NirvanaEditor_MainFrame::OnSpriteEdit_collisionBox_X_spinCtrl( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	int spr_id = sprite_editor->getSelectedSprite();
	if(spr_id < 0)
		return;

	project->setSpriteCollision_OffsetX(spr_id, event.GetValue());
	sprite_editor->getCollisionControl()->collision_physics_obj = project->getSpritePhysics(sprite_editor->getSelectedSprite());
}

void NirvanaEditor_MainFrame::OnSpriteEdit_collisionBox_Y_spinCtrl( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	int spr_id = sprite_editor->getSelectedSprite();
	if(spr_id < 0)
		return;

	project->setSpriteCollision_OffsetY(spr_id, event.GetValue());
	sprite_editor->getCollisionControl()->collision_physics_obj = project->getSpritePhysics(sprite_editor->getSelectedSprite());
}

void NirvanaEditor_MainFrame::OnSpriteEdit_collisionBox_Width_spinCtrl( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	int spr_id = sprite_editor->getSelectedSprite();
	if(spr_id < 0)
		return;

	project->setSpriteCollisionBox_Width(spr_id, event.GetValue());
	sprite_editor->getCollisionControl()->collision_physics_obj = project->getSpritePhysics(sprite_editor->getSelectedSprite());
}

void NirvanaEditor_MainFrame::OnSpriteEdit_collisionBox_Height_spinCtrl( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	int spr_id = sprite_editor->getSelectedSprite();
	if(spr_id < 0)
		return;

	project->setSpriteCollisionBox_Height(spr_id, event.GetValue());
	sprite_editor->getCollisionControl()->collision_physics_obj = project->getSpritePhysics(sprite_editor->getSelectedSprite());
}


void NirvanaEditor_MainFrame::OnSpriteEdit_collisionCircle_X_spinCtrl( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	int spr_id = sprite_editor->getSelectedSprite();
	if(spr_id < 0)
		return;

	project->setSpriteCollision_OffsetX(spr_id, event.GetValue());
	sprite_editor->getCollisionControl()->collision_physics_obj = project->getSpritePhysics(sprite_editor->getSelectedSprite());
}

void NirvanaEditor_MainFrame::OnSpriteEdit_collisionCircle_Y_spinCtrl( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	int spr_id = sprite_editor->getSelectedSprite();
	if(spr_id < 0)
		return;

	project->setSpriteCollision_OffsetY(spr_id, event.GetValue());
	sprite_editor->getCollisionControl()->collision_physics_obj = project->getSpritePhysics(sprite_editor->getSelectedSprite());
}

void NirvanaEditor_MainFrame::OnSpriteEdit_collisionCircle_Radius_spinCtrl( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	int spr_id = sprite_editor->getSelectedSprite();
	if(spr_id < 0)
		return;

	project->setSpriteCollisionCircle_Radius(spr_id, event.GetValue());
	sprite_editor->getCollisionControl()->collision_physics_obj = project->getSpritePhysics(sprite_editor->getSelectedSprite());
}

void NirvanaEditor_MainFrame::OnSpriteEdit_collisionPolygon_gridCellChange( wxGridEvent& event )
{
	if(!editor_init)
		return;

	int spr_id = sprite_editor->getSelectedSprite();
	if(spr_id < 0)
		return;

	int cell_value = 0;
	int col = event.GetCol();
	int row = event.GetRow();

	m_spriteEdit_collisionPolygon_grid->GetCellValue(row, col).ToInt(&cell_value);

	sprite2D_physics_obj physics = project->getSpritePhysics(spr_id);

	if(row < 0 || row >= physics.points.size())
		return;

	if(col == 0)
		physics.points[row].X = cell_value;
	else
		physics.points[row].Y = cell_value;

	project->setSpritePhysics(spr_id, physics);
	sprite_editor->getCollisionControl()->collision_physics_obj = project->getSpritePhysics(sprite_editor->getSelectedSprite());

	m_spriteEdit_collisionPolygon_grid->SetCellValue(row, col, wxString::Format(_("%i"), cell_value));

	//std::cout << "Cell DBG: point_num=" << event.GetRow() << " " << (event.GetCol() == 0 ? "x -> " : "y -> ") << cell_value << std::endl;
}

//TILE EDITOR
void NirvanaEditor_MainFrame::OnNewTilesetClick( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	if(!project->active)
	{
		wxMessageBox(_("You must have an open project."));
		return;
	}

	NirvanaEditor_NewTileset_Dialog* dialog = new NirvanaEditor_NewTileset_Dialog(this);

	wxFileName gfx_path(project->getDir());

	if(project)
		gfx_path.AppendDir(project->tile_path);
	else
		gfx_path.AppendDir(_("gfx"));

	dialog->files = getDirFileList(gfx_path.GetAbsolutePath());

	dialog->project = project;

	for(int i = 0; i < project->getTilesetCount(); i++)
	{
		dialog->current_tset_id.push_back(wxString(project->getTilesetName(i)).Trim());
	}

	dialog->refresh_list();

	PreDialog();
	dialog->ShowModal();
	PostDialog();

	if(!dialog->create_flag)
		return;

	wxFileName p_tset_def(project->getDir());
	p_tset_def.AppendDir(project->tile_path);
	p_tset_def.SetFullName(dialog->selected_file + _(".tset"));

	int tset_index = -1;

	if(!p_tset_def.Exists())
	{
		if(!project->checkName(dialog->id_name.ToStdString()))
			return;
	}
	else
		tset_index = project->loadTileset(dialog->selected_file);

	if(tset_index < 0)
	{
		wxFileName img_file = gfx_path;
		img_file.SetFullName(dialog->selected_file);
		int tmp_image = tile_editor->getAnimationFrameControl()->loadImage(img_file.GetAbsolutePath().ToStdString());
		if(tmp_image < 0)
		{
			wxMessageBox(_("Could not load image: ") + img_file.GetAbsolutePath().ToStdString());
			return;
		}

		int frame_tset_index = tile_editor->getAnimationFrameControl()->createTileSet(tmp_image, dialog->frame_width, dialog->frame_height);

		if(frame_tset_index < 0)
		{
			wxMessageBox(_("Failed to create tileset from [") + img_file.GetAbsolutePath().ToStdString());
			return;
		}

		project->createTileset(dialog->id_name, dialog->selected_file, dialog->frame_width, dialog->frame_height);

		int project_tset_index = project->getTilesetIndex(dialog->id_name.ToStdString());

		if(project_tset_index < 0)
		{
			tile_editor->getAnimationFrameControl()->deleteTileSet(frame_tset_index);
			tile_editor->getAnimationFrameControl()->deleteImage(tmp_image);
			return;
		}

		//std::cout << "HOLLA: " << tile_editor->getAnimationFrameControl()->tileset[frame_tset_index].tiles[0].frames.size() << std::endl;
		project->setTilesetObject(project_tset_index, tile_editor->getAnimationFrameControl()->tileset[frame_tset_index]);
		project->tileset[project_tset_index].object.img_id = -1;

		m_tileEdit_tileset_listBox->AppendAndEnsureVisible(dialog->id_name);

		tile_editor->getAnimationFrameControl()->deleteTileSet(frame_tset_index);
		tile_editor->getAnimationFrameControl()->deleteImage(tmp_image);
	}
	else
	{
		project->tileset[tset_index].object.img_id = -1;
		m_tileEdit_tileset_listBox->AppendAndEnsureVisible(project->tileset[tset_index].tileset_name);
	}
}

void NirvanaEditor_MainFrame::OnDeleteTilesetClick( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	int list_index = m_tileEdit_tileset_listBox->GetSelection();

	if(list_index < 0 || list_index >= m_tileEdit_tileset_listBox->GetCount())
		return;

	int tset_id = tile_editor->getSelectedTileset();

	if(tset_id < 0 || tset_id >= project->getTilesetCount())
		return;

	int stage_index = map_editor->getSelectedStage();

	map_editor->getMapViewControl()->clearStage();

	std::vector<Nirvana_Tileset> tmp_tilesets = project->tileset;
	project->deleteTileset(tset_id);

	for(int st_i = 0; st_i < project->stages.size(); st_i++)
	{
		for(int layer_index = 0; layer_index < project->stages[st_i].layers.size(); layer_index++)
		{
			if(layer_index < 0)
				continue;

			if(project->stages[st_i].layers[layer_index].layer_type == LAYER_TYPE_TILEMAP || project->stages[st_i].layers[layer_index].layer_type == LAYER_TYPE_ISO_TILEMAP)
			{
				if(project->stages[st_i].layers[layer_index].layer_map.nv_tileset_index == tset_id)
				{
					project->deleteLayer(st_i, layer_index);
					layer_index = -1;
				}
				else if(project->stages[st_i].layers[layer_index].layer_map.nv_tileset_index > tset_id)
                {
                    project->stages[st_i].layers[layer_index].layer_map.nv_tileset_index--;
                    int n_tset_index = project->stages[st_i].layers[layer_index].layer_map.nv_tileset_index;
                    if(n_tset_index >= 0 && n_tset_index < project->tileset.size())
                        project->stages[st_i].layers[layer_index].layer_map.nv_tileset_name = project->tileset[n_tset_index].tileset_name.ToStdString();
                }
			}
			else if(project->stages[st_i].layers[layer_index].layer_type == LAYER_TYPE_SPRITE)
            {
                if(project->stages[st_i].layers[layer_index].layer_map.nv_tileset_index == tset_id)
                {
                    //std::cout << "SP LAYER: " << layer_index << std::endl;
                    for(int spr_index = 0; spr_index < project->stages[st_i].layers[layer_index].layer_tile_sprites.size(); spr_index++)
                    {
                        int sprite_id = project->stages[st_i].layers[layer_index].layer_tile_sprites[spr_index].sprite_id;
                        map_editor->getMapViewControl()->deleteSprite(sprite_id);
                    }
                    project->stages[st_i].layers[layer_index].layer_tile_sprites.clear();
                    project->stages[st_i].layers[layer_index].layer_map.nv_tileset_index = -1;
                    project->stages[st_i].layers[layer_index].layer_map.nv_tileset_name = "";
                    //project->setLayerTileset(st_i, layer_index, -1);
                    map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.clear();
                    map_editor->getMapViewControl()->selected_sprite = -1;

                    layer_index = -1;
                }
                else if(project->stages[st_i].layers[layer_index].layer_map.nv_tileset_index > tset_id)
                {
                    project->stages[st_i].layers[layer_index].layer_map.nv_tileset_index--;
                    int n_tset_index = project->stages[st_i].layers[layer_index].layer_map.nv_tileset_index;

                    for(int spr_index = 0; spr_index < project->stages[st_i].layers[layer_index].layer_tile_sprites.size(); spr_index++)
                    {
                        project->stages[st_i].layers[layer_index].layer_tile_sprites[spr_index].tset = n_tset_index;
                    }

                    if(n_tset_index >= 0 && n_tset_index < project->tileset.size())
                    {
                        project->stages[st_i].layers[layer_index].layer_map.nv_tileset_name = project->tileset[n_tset_index].tileset_name.ToStdString();

                        if((n_tset_index+1) < tmp_tilesets.size())
                        {
                            project->tileset[n_tset_index].tileset_cut = tmp_tilesets[n_tset_index+1].tileset_cut;
                        }
                    }
                }
            }
		}
	}

	if(stage_index >= 0 && stage_index < project->stages.size())
	{
		wxString active_layer_name = wxString(project->getLayerName(stage_index, map_editor->getSelectedLayer())).Upper().Trim();

		//SET LAYER COMBO AND CHECKLIST
		m_layerVisible_checkList->Clear();
		m_activeLayer_comboBox->Clear();

		for(int i = 0; i < project->getStageNumLayers(stage_index); i++)
		{
			m_layerVisible_checkList->AppendAndEnsureVisible(wxString(project->getLayerName(stage_index, i)));
			m_layerVisible_checkList->Check(i, project->getLayerVisible(stage_index, i));

			m_activeLayer_comboBox->Append(project->getLayerName(stage_index, i));
		}

		int active_layer_index = project->getLayerIndex(stage_index, active_layer_name.ToStdString());
		m_activeLayer_comboBox->SetSelection(active_layer_index);
		map_editor->selectLayer(active_layer_index);

		m_layerName_textCtrl->SetValue(_(""));
		m_mapEdit_layerHScroll_spinCtrlDouble->SetValue(0.0);
		m_mapEdit_layerVScroll_spinCtrlDouble->SetValue(0.0);
		m_mapEdit_layerAlpha_spinCtrl->SetValue(0);
	}


	m_tileEdit_tileset_listBox->Delete(tset_id);
	tile_editor->selectTileset(_(""));

	m_tileEdit_tileset_listBox->SetSelection(-1);
	m_tileEdit_tilesetID_textCtrl->SetValue(_(""));
	m_tileEdit_numFrames_spinCtrl->SetValue(0);
	m_tileEdit_FPS_spinCtrl->SetValue(0);
	m_tileEdit_maskID_textCtrl->SetValue(_(""));
	m_tileEdit_mask_listBox->Clear();
}

void NirvanaEditor_MainFrame::OnTileEdit_TileIDChanged( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	int list_index = m_tileEdit_tileset_listBox->GetSelection();

	if(list_index < 0 || list_index >= m_tileEdit_tileset_listBox->GetCount())
		return;

	int tset_id = tile_editor->getSelectedTileset();

	if(tset_id < 0 || tset_id >= project->getTilesetCount())
		return;

	wxString new_value = m_tileEdit_tilesetID_textCtrl->GetValue();

	if(!project->checkName(new_value.ToStdString()))
		return;

	wxString test_id = new_value.Upper().Trim();
	for(int i = 0; i < project->getTilesetCount(); i++)
	{
		if(wxString(project->getTilesetName(i)).Upper().Trim().compare(test_id)==0)
			return;
	}

	m_tileEdit_tileset_listBox->SetString(list_index, new_value);
	project->setTilesetName(tset_id, new_value.ToStdString());
}

void NirvanaEditor_MainFrame::OnTileEdit_TilesetSelected( wxCommandEvent& event )
{
	if(!editor_init)
		return;

    //std::cout << "TSET DEBUG 1" << std::endl;

	int selected_index = event.GetSelection();
	wxString tileset_name = m_tileEdit_tileset_listBox->GetString(selected_index);

	int tileEdit_current_tab = m_tileEdit_tools_auinotebook->GetSelection();
	tileEdit_current_tab = tileEdit_current_tab < 0 ? 0 : tileEdit_current_tab;

	tile_editor->selectTileset(tileset_name);

	int tset_id = tile_editor->getSelectedTileset();
	if(tset_id < 0)
		return;

    //std::cout << "TSET DEBUG 2" << std::endl;

	m_tileEdit_tilesetID_textCtrl->SetValue(tileset_name);

	m_tileEdit_maskID_textCtrl->SetValue(_(""));

	tileset_obj n_tile = project->getTileset(tset_id).object;

	m_tileSize_staticText->SetLabel(wxString::Format(_("%i"), n_tile.tile_width)  + _(" x ") + wxString::Format(_("%i"), n_tile.tile_height));

	tile_editor->getAnimationSheetControl()->setActiveCanvas(tile_editor->getAnimationSheetControl()->sheet_canvas);
	tile_editor->getAnimationSheetControl()->clearCanvas();

	//tile_editor->getAnimationSheetControl()->setColor(tile_editor->getAnimationSheetControl()->rgb(255,0,0));
	//tile_editor->getAnimationSheetControl()->drawRect(10, 10, 100, 100);

	tile_editor->getAnimationSheetControl()->force_refresh();

	tile_editor->getMaskSheetControl()->setActiveCanvas(tile_editor->getMaskSheetControl()->sheet_canvas);
	tile_editor->getMaskSheetControl()->clearCanvas();
	tile_editor->getAnimationSheetControl()->force_refresh();

	tile_editor->getAnimationSheetControl()->scroll_offset_x = 0;
	tile_editor->getAnimationSheetControl()->scroll_offset_y = 0;
	tile_editor->getAnimationSheetControl()->tileEdit_selected_sheet_frame = -1;
	tile_editor->getAnimationFrameControl()->tileEdit_selected_tile = -1;

	m_tileEdit_mask_listBox->Clear();

	Nirvana_Tileset n_tset = project->getTileset(tset_id);
	for(int i = 0; i < n_tset.mask.size(); i++)
	{
		m_tileEdit_mask_listBox->AppendAndEnsureVisible(n_tset.mask[i].mask_name);
	}
	tilemask_obj empty_mask;
	empty_mask.active = false;
	tile_editor->getMaskSheetControl()->tileEdit_tileMask = empty_mask;

	m_tileEdit_tools_auinotebook->SetSelection(tileEdit_current_tab);
}

void NirvanaEditor_MainFrame::OnEnterTileAnimationSheet( wxMouseEvent& event )
{
	if(!editor_init)
		return;

	//std::cout << "ENTER" << std::endl;
	tile_editor->getAnimationSheetControl()->stage_window_isActive = true;
}

void NirvanaEditor_MainFrame::OnLeaveTileAnimationSheet( wxMouseEvent& event )
{
	if(!editor_init)
		return;

	tile_editor->getAnimationSheetControl()->stage_window_isActive = false;
	//std::cout << "LEAVE" << std::endl;
}

void NirvanaEditor_MainFrame::OnUpdateTileAnimationUI( wxUpdateUIEvent& event )
{
	if(!editor_init)
		return;

	if(tile_editor->getAnimationSheetControl()->tileEdit_Sheet_Update)
	{
		tile_editor->getAnimationSheetControl()->tileEdit_Sheet_Update = false;

		if(tile_editor->getAnimationSheetControl()->tileEdit_animationMode == TILE_EDIT_ANIMATION_MODE_SELECT)
		{
			tile_editor->selectTile(tile_editor->getAnimationSheetControl()->tileEdit_selected_sheet_frame);
			int selected_tileset = tile_editor->getSelectedTileset();
			int selected_tile = tile_editor->getSelectedTile();

			m_tileEdit_numFrames_spinCtrl->SetValue(project->getTileNumAnimationFrames(selected_tileset, selected_tile));
			m_tileEdit_FPS_spinCtrl->SetValue(project->getTileAnimationFPS(selected_tileset, selected_tile));
		}
		else if(tile_editor->getAnimationSheetControl()->tileEdit_animationMode == TILE_EDIT_ANIMATION_MODE_ANIMATE)
		{
			int selected_tileset = tile_editor->getSelectedTileset();
			int selected_tile = tile_editor->getSelectedTile();
			int selected_ani_frame = tile_editor->getAnimationFrameControl()->tileEdit_selected_frame_frame;
			int selected_sheet_frame = tile_editor->getAnimationSheetControl()->tileEdit_selected_sheet_frame;

			project->setTileAnimationFrame(selected_tileset, selected_tile, selected_ani_frame, selected_sheet_frame);
		}

		tile_editor->updateTileAnimation();
		//tile_editor->getAnimationFrameControl()->tileEdit_selected_tile = selected_tile;
		//tile_editor->getAnimationPreviewControl()->tileEdit_selected_tile = selected_tile;
	}
}

void NirvanaEditor_MainFrame::OnTileEdit_NumFramesChange( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	int tset_id = tile_editor->getSelectedTileset();

	if(tset_id < 0 || tset_id >= project->getTilesetCount())
		return;

	int tile_id = tile_editor->getSelectedTile();

	if(tile_id < 0 || tile_id >= project->getTilesetNumTiles(tset_id))
		return;

	int new_frame_count = event.GetValue();

	if(new_frame_count < 0 || new_frame_count >= m_tileEdit_numFrames_spinCtrl->GetMax())
		return;

	project->setTileNumAnimationFrames(tset_id, tile_id, new_frame_count);
	tile_editor->updateTileAnimation();
}

void NirvanaEditor_MainFrame::OnTileEdit_FPSChanged( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	int tset_id = tile_editor->getSelectedTileset();

	if(tset_id < 0 || tset_id >= project->getTilesetCount())
		return;

	int tile_id = tile_editor->getSelectedTile();

	if(tile_id < 0 || tile_id >= project->getTilesetNumTiles(tset_id))
		return;

	int new_fps = event.GetValue();

	project->setTileAnimationFPS(tset_id, tile_id, new_fps);
	tile_editor->updateTileAnimation();
}

void NirvanaEditor_MainFrame::OnTileEdit_TileSelect_Tool( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	tile_editor->getAnimationSheetControl()->tileEdit_animationMode = TILE_EDIT_ANIMATION_MODE_SELECT;
	tile_editor->getAnimationFrameControl()->tileEdit_animationMode = TILE_EDIT_ANIMATION_MODE_SELECT;
	m_tileEdit_mode_auiToolBar->ToggleTool(m_tileEdit_tileSelect_tool->GetId(), true);
}

void NirvanaEditor_MainFrame::OnTileEdit_TileAnimation_Tool( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	tile_editor->getAnimationSheetControl()->tileEdit_animationMode = TILE_EDIT_ANIMATION_MODE_ANIMATE;
	tile_editor->getAnimationFrameControl()->tileEdit_animationMode = TILE_EDIT_ANIMATION_MODE_ANIMATE;
	m_tileEdit_mode_auiToolBar->ToggleTool(m_tileEdit_tileAnimate_tool->GetId(), true);
}

void NirvanaEditor_MainFrame::OnTileEdit_PreviousFrame_Click( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	int tset_id = tile_editor->getSelectedTileset();

	if(tset_id < 0 || tset_id >= project->getTilesetCount())
		return;

	int tile_id = tile_editor->getSelectedTile();

	if(tile_id < 0 || tile_id >= project->getTilesetNumTiles(tset_id))
		return;

	int new_offset = tile_editor->getAnimationFrameControl()->scroll_offset_x - 64;

	tile_editor->getAnimationFrameControl()->scroll_offset_x = new_offset;
}

void NirvanaEditor_MainFrame::OnTileEdit_NextFrame_Click( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	int tset_id = tile_editor->getSelectedTileset();

	if(tset_id < 0 || tset_id >= project->getTilesetCount())
		return;

	int tile_id = tile_editor->getSelectedTile();

	if(tile_id < 0 || tile_id >= project->getTilesetNumTiles(tset_id))
		return;

	int new_offset = tile_editor->getAnimationFrameControl()->scroll_offset_x + 64;

	tile_editor->getAnimationFrameControl()->scroll_offset_x = new_offset;
}

void NirvanaEditor_MainFrame::OnTileEdit_PlayPreviewClick( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	tile_editor->playPreview();
}

void NirvanaEditor_MainFrame::OnTileEdit_StopPreviewClick( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	tile_editor->stopPreview();
}


//MASK

void NirvanaEditor_MainFrame::OnTileEdit_newMaskClick( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	int tset_id = tile_editor->getSelectedTileset();

	if(tset_id < 0 || tset_id >= project->getTilesetCount())
		return;

	int n = 0;
	wxString tmp_name = _("MASK") + wxString::Format(_("%i"), n);
	for(int i = 0; i < project->getMaskCount(tset_id); i++)
	{
		if(i < 0)
			continue;

		wxString mask_name = wxString(project->getMaskName(tset_id, i));
		if(mask_name.Upper().compare(tmp_name)==0)
		{
			n++;
			tmp_name = _("MASK") + wxString::Format(_("%i"), n);
			i = -1;
		}
	}

	project->createMask(tset_id, tmp_name.ToStdString());
	m_tileEdit_mask_listBox->AppendAndEnsureVisible(tmp_name);
}

void NirvanaEditor_MainFrame::OnTileEdit_deleteMaskClick( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	int tset_id = tile_editor->getSelectedTileset();

	if(tset_id < 0 || tset_id >= project->getTilesetCount())
		return;

	int mask_index = tile_editor->getSelectedMask();

	if(mask_index < 0 || mask_index >= project->getMaskCount(tset_id))
		return;

	project->deleteMask(tset_id, mask_index);

	m_tileEdit_mask_listBox->Clear();

	Nirvana_Tileset n_tset = project->getTileset(tset_id);
	for(int i = 0; i < n_tset.mask.size(); i++)
	{
		m_tileEdit_mask_listBox->AppendAndEnsureVisible(n_tset.mask[i].mask_name);
	}

	tile_editor->selectMask(_("[NULL]"));
}

void NirvanaEditor_MainFrame::OnTileEdit_maskIDChanged( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	int tset_id = tile_editor->getSelectedTileset();

	if(tset_id < 0 || tset_id >= project->getTilesetCount())
		return;

	int mask_index = tile_editor->getSelectedMask();

	if(mask_index < 0 || mask_index >= project->getMaskCount(tset_id))
		return;

	//wxMessageBox(_("MASK COUNT: ") + wxString::Format(_("%i"), project->getMaskCount(tset_id)) + ", " + wxString::Format(_("%i"), mask_index));

	project->setMaskName(tset_id, mask_index, event.GetString().ToStdString());

	m_tileEdit_mask_listBox->SetString(mask_index, wxString(project->getMaskName(tset_id, mask_index)));
}

void NirvanaEditor_MainFrame::OnEnterTileMaskSheet( wxMouseEvent& event )
{
	if(!editor_init)
		return;

	tile_editor->getMaskSheetControl()->stage_window_isActive = true;
}

void NirvanaEditor_MainFrame::OnLeaveTileMaskSheet( wxMouseEvent& event )
{
	if(!editor_init)
		return;

	tile_editor->getMaskSheetControl()->stage_window_isActive = false;
}

void NirvanaEditor_MainFrame::OnTileEdit_maskSelected( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	int tset_id = tile_editor->getSelectedTileset();

	if(tset_id < 0 || tset_id >= project->getTilesetCount())
		return;

	tile_editor->selectMask(event.GetString());

	int mask_index = tile_editor->getSelectedMask();

	if(mask_index < 0 || mask_index >= project->getMaskCount(tset_id))
		return;

	m_tileEdit_maskID_textCtrl->SetValue(project->getMaskName(tset_id, mask_index));
}

void NirvanaEditor_MainFrame::OnUpdateTileMaskUI( wxUpdateUIEvent& event )
{
	if(!editor_init)
		return;

	if(tile_editor->getMaskSheetControl()->tileEdit_Sheet_Update)
	{
		tile_editor->getMaskSheetControl()->tileEdit_Sheet_Update = false;

		tile_editor->selectTile(tile_editor->getAnimationSheetControl()->tileEdit_selected_sheet_frame);
		int selected_tileset = tile_editor->getSelectedTileset();
		int selected_tile = tile_editor->getMaskSheetControl()->tileEdit_selected_sheet_frame;
		int selected_mask = tile_editor->getSelectedMask();
		bool mask_set = tile_editor->getMaskSheetControl()->tileEdit_mask_set;

		if(selected_tileset >= 0 && selected_tileset < project->getTilesetCount())
		{
			if(selected_mask >= 0 && selected_mask < project->getMaskCount(selected_tileset))
			{
				project->setTileMask(selected_tileset, selected_mask, selected_tile, mask_set);
				tile_editor->getMaskSheetControl()->tileEdit_tileMask = project->getTileset(selected_tileset).mask[selected_mask];
			}
		}
	}
}
