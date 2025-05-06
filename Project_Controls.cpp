#include "NirvanaEditor_MainFrame.h"
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/arrstr.h>

#include "NirvanaEditor_NewStage_Dialog.h"
#include "NirvanaEditor_NewLayer_Dialog.h"
#include "NirvanaEditor_DeleteStage_Dialog.h"
#include "NirvanaEditor_StageProperties_Dialog.h"
#include "Nirvana_Project.h"

void NirvanaEditor_MainFrame::OnNewStage( wxCommandEvent& event )
{
	if(!project)
		return;

	NirvanaEditor_NewStage_Dialog* dialog = new NirvanaEditor_NewStage_Dialog(this);

	dialog->ShowModal();

	if(!dialog->create_flag)
		return;

	project->createStage(dialog->stage_name.ToStdString(), dialog->tile_width, dialog->tile_height);

	int stage_index = project->getStageIndex(dialog->stage_name.ToStdString());

	if(stage_index < 0)
		return;

	project->setStageSize(stage_index, dialog->width_in_tiles, dialog->height_in_tiles);

	wxTreeItemId stage_item = m_project_treeCtrl->AppendItem(project_root_treeItem, dialog->stage_name, stage_tree_stageImage);

	stage_treeItem.push_back(stage_item);
}

void NirvanaEditor_MainFrame::OnDeleteStage( wxCommandEvent& event )
{
	if(!project)
		return;

	wxString stage_name = m_project_treeCtrl->GetItemText(m_project_treeCtrl->GetSelection());
	int stage_index = project->getStageIndex(stage_name.ToStdString());

	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	NirvanaEditor_DeleteStage_Dialog* dialog = new NirvanaEditor_DeleteStage_Dialog(this);

	dialog->setStageName(project->getStageName(stage_index));

	dialog->ShowModal();

	if(!dialog->delete_flag)
		return;

	if(stage_index == map_editor->getSelectedStage())
	{
		wxMessageBox(_("Can't delete stage while its active"));
		return;
	}

	wxString active_stage_name = wxString(project->getStageName(map_editor->getSelectedStage()));

	project->deleteStage(stage_index);

	m_project_treeCtrl->Delete( stage_treeItem[stage_index] );
	stage_treeItem.erase(stage_treeItem.begin() + stage_index);

	int active_stage_index = project->getStageIndex(active_stage_name.ToStdString());

	if(active_stage_index < 0)
		return;

	map_editor->selectStage(active_stage_index);

	//SET LAYER COMBO AND CHECKLIST
	m_layerVisible_checkList->Clear();

	for(int i = 0; i < project->getStageNumLayers(active_stage_index); i++)
	{
		m_layerVisible_checkList->AppendAndEnsureVisible(wxString(project->getLayerName(active_stage_index, i)));
		m_layerVisible_checkList->Check(i, project->getLayerVisible(active_stage_index, i));
	}
}

void NirvanaEditor_MainFrame::OnMapEdit_StageSettingsClick( wxCommandEvent& event )
{
	if(!project)
		return;

	wxString stage_name = m_project_treeCtrl->GetItemText(m_project_treeCtrl->GetSelection());
	int stage_index = project->getStageIndex(stage_name.ToStdString());

	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	NirvanaEditor_StageProperties_Dialog* dialog = new NirvanaEditor_StageProperties_Dialog(this);

	int tile_width = project->getStageTileSize(stage_index).X;
	int tile_height = project->getStageTileSize(stage_index).Y;

	int tiles_across = project->getStageSize(stage_index).X;
	int tiles_down = project->getStageSize(stage_index).Y;

	dialog->setStageProperties(stage_name, tile_width, tile_height, tiles_across, tiles_down);


	dialog->ShowModal();

	if(!dialog->set_flag)
		return;

	if(stage_index == map_editor->getSelectedStage())
	{
		m_mapEdit_stageName_staticText->SetLabelText(_("STAGE: ") + dialog->stage_name);
	}

	project->setStageName(stage_index, dialog->stage_name.ToStdString());
	project->setStageSize(stage_index, dialog->tiles_across, dialog->tiles_down);

	m_project_treeCtrl->SetItemText( stage_treeItem[stage_index], dialog->stage_name );

}

void NirvanaEditor_MainFrame::OnMapEdit_CopyStageClick( wxCommandEvent& event )
{
	if(!project)
		return;

	wxString stage_name = m_project_treeCtrl->GetItemText(m_project_treeCtrl->GetSelection());
	int stage_index = project->getStageIndex(stage_name.ToStdString());

	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int copy_index = project->copyStage(stage_index);

	wxTreeItemId stage_item = m_project_treeCtrl->AppendItem(project_root_treeItem, project->getStageName(copy_index), stage_tree_stageImage);

	stage_treeItem.push_back(stage_item);
}

void NirvanaEditor_MainFrame::OnMapEdit_NewLayerClick( wxCommandEvent& event )
{
	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0)
		return;

	NirvanaEditor_NewLayer_Dialog* dialog = new NirvanaEditor_NewLayer_Dialog(this);

	int tile_width = project->getStageTileSize(stage_index).X;
	int tile_height = project->getStageTileSize(stage_index).Y;

	for(int i = 0; i < project->getTilesetCount(); i++)
	{
		if(tile_width == project->getTilesetTileSize(i).X && tile_height == project->getTilesetTileSize(i).Y)
			dialog->tileset_list.push_back(wxString(project->getTilesetName(i)));
	}

	dialog->refresh_list();

	dialog->ShowModal();

	if(!dialog->create_flag)
		return;

	project->addLayer(stage_index, dialog->layer_name.ToStdString(), dialog->selected_type);
	int layer_index = project->getLayerIndex(stage_index, dialog->layer_name.ToStdString());

	if(layer_index < 0)
	{
		return;
	}


	project->setLayerTileset(stage_index, layer_index, project->getTilesetIndex(dialog->selected_tileset.ToStdString()));

	map_editor->getMapViewControl()->initLayer(layer_index);

	updateMapEditor();

	m_layerVisible_checkList->AppendAndEnsureVisible(wxString(project->getLayerName(stage_index, layer_index)));
	m_layerVisible_checkList->Check(m_layerVisible_checkList->GetCount()-1, true);
	m_activeLayer_comboBox->Append(project->getLayerName(stage_index, layer_index));
}

void NirvanaEditor_MainFrame::OnMapEdit_CopyLayerClick( wxCommandEvent& event )
{
	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = m_layerVisible_checkList->GetSelection();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	int copy_index = project->copyLayer(stage_index, layer_index);

	if(copy_index < 0)
		return;

	wxString copy_name = wxString(project->getLayerName(stage_index, copy_index));
	m_layerVisible_checkList->AppendAndEnsureVisible(copy_name);
	m_layerVisible_checkList->Check(m_layerVisible_checkList->GetCount()-1, project->getLayerVisible(stage_index, copy_index));
	m_activeLayer_comboBox->Append(copy_name);
}

void NirvanaEditor_MainFrame::OnMapEdit_ShowAllLayersClick( wxCommandEvent& event )
{
	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	for(int i = 0; i < project->getStageNumLayers(stage_index); i++)
	{
		project->setLayerVisible(stage_index, i, true);

		if(project->stages[stage_index].layers[i].ref_canvas >= 0 && project->stages[stage_index].layers[i].ref_canvas < map_editor->getMapViewControl()->canvas.size())
			map_editor->getMapViewControl()->setCanvasVisible(project->stages[stage_index].layers[i].ref_canvas, true);
	}

	for(int i = 0; i < m_layerVisible_checkList->GetCount(); i++)
	{
		m_layerVisible_checkList->Check(i, true);
	}
}

void NirvanaEditor_MainFrame::OnMapEdit_HideAllLayersClick( wxCommandEvent& event )
{
	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	for(int i = 0; i < project->getStageNumLayers(stage_index); i++)
	{
		project->setLayerVisible(stage_index, i, false);

		if(project->stages[stage_index].layers[i].ref_canvas >= 0 && project->stages[stage_index].layers[i].ref_canvas < map_editor->getMapViewControl()->canvas.size())
			map_editor->getMapViewControl()->setCanvasVisible(project->stages[stage_index].layers[i].ref_canvas, false);
	}

	for(int i = 0; i < m_layerVisible_checkList->GetCount(); i++)
	{
		m_layerVisible_checkList->Check(i, false);
	}
}


void NirvanaEditor_MainFrame::OnProjectItemActivated( wxTreeEvent& event )
{
	wxTreeItemId selected_item = event.GetItem();
	bool is_stage = false;

	for(int i = 0; i < stage_treeItem.size(); i++)
	{
		if(selected_item == stage_treeItem[i])
		{
			is_stage = true;
			break;
		}
	}

	if(!is_stage)
		return;

	wxString item_label = m_project_treeCtrl->GetItemText(selected_item);
	int stage_index = project->getStageIndex(item_label.ToStdString());

	map_editor->getMapViewControl()->mapEdit_getContext();
	map_editor->getMapViewControl()->clearStage();
	map_editor->getMapViewControl()->mapEdit_selectTileTool_selection.clear();
	map_editor->selectStage(stage_index);
	map_editor->selectLayer(-1);

	m_mapEdit_stageName_staticText->SetLabelText(_("STAGE: ") + wxString(project->getStageName(stage_index)));



	//SET LAYER COMBO AND CHECKLIST
	m_layerVisible_checkList->Clear();
	m_activeLayer_comboBox->Clear();

	for(int i = 0; i < project->getStageNumLayers(stage_index); i++)
	{
		m_layerVisible_checkList->AppendAndEnsureVisible(wxString(project->getLayerName(stage_index, i)));
		m_layerVisible_checkList->Check(i, project->getLayerVisible(stage_index, i));

		m_activeLayer_comboBox->Append(project->getLayerName(stage_index, i));
	}

	//CLEAR SPRITE LIST
	m_mapEdit_layerSprite_listBox->Clear();

	//CLEAR SHAPE LIST
	m_mapEdit_collisionShape_listBox->Clear();

	m_layerName_textCtrl->SetValue(_(""));
	m_mapEdit_layerHScroll_spinCtrlDouble->SetValue(0);
	m_mapEdit_layerVScroll_spinCtrlDouble->SetValue(0);
	m_mapEdit_layerAlpha_spinCtrl->SetValue(0);
}

void NirvanaEditor_MainFrame::updateMapEditor()
{
	//Clear All Canvases

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	wxString selected_stage_name(project->getStageName(stage_index));

	int layer_index = map_editor->getSelectedLayer();
	wxString selected_layer_name(project->getLayerName(stage_index, layer_index));

//	m_project_treeCtrl->DeleteChildren(project_root_treeItem);
//	stage_treeItem.clear();
//
//	for(int i = 0; i < project->getStageCount(); i++)
//	{
//		stage_treeItem.push_back(m_project_treeCtrl->AppendItem(project_root_treeItem, wxString(project->getStageName(i)), stage_tree_stageImage));
//	}

	if(stage_index >= 0 && stage_index < project->getStageCount())
	{
		wxPGProperty * sprite_id = m_mapEdit_sprite_propertyGrid->GetProperty(_("sprite_id"));
		wxPGProperty * sprite_body_type = m_mapEdit_sprite_propertyGrid->GetProperty(_("body_type"));
		wxPGProperty * sprite_animation = m_mapEdit_sprite_propertyGrid->GetProperty(_("animation"));
		wxPGProperty * sprite_pos_x = m_mapEdit_sprite_propertyGrid->GetProperty(_("position_x"));
		wxPGProperty * sprite_pos_y = m_mapEdit_sprite_propertyGrid->GetProperty(_("position_y"));
		wxPGProperty * sprite_angle = m_mapEdit_sprite_propertyGrid->GetProperty(_("angle"));
		wxPGProperty * sprite_scale_x = m_mapEdit_sprite_propertyGrid->GetProperty(_("scale_x"));
		wxPGProperty * sprite_scale_y = m_mapEdit_sprite_propertyGrid->GetProperty(_("scale_y"));
		wxPGProperty * sprite_alpha = m_mapEdit_sprite_propertyGrid->GetProperty(_("alpha"));
		wxPGProperty * sprite_visible = m_mapEdit_sprite_propertyGrid->GetProperty(_("visible"));


		sprite_id->SetValueFromString(_(""));
		sprite_body_type->SetChoiceSelection(0);
		sprite_animation->SetChoices(wxPGChoices());
		sprite_pos_x->SetValue( 0 );
		sprite_pos_y->SetValue( 0 );
		sprite_angle->SetValue( 0 );
		sprite_scale_x->SetValue( 0 );
		sprite_scale_y->SetValue( 0 );
		sprite_alpha->SetValueFromInt( 0 );
		sprite_visible->SetValue( false );

		m_mapEdit_layerSprite_listBox->Clear();
		m_mapEdit_collisionShape_listBox->Clear();

		m_mapEdit_shapeName_textCtrl->SetValue(_(""));

		m_mapEdit_shapeEdit_simplebook->SetSelection(0);

		map_editor->getTileSelectControl()->mapEdit_layerType = project->getLayerType(stage_index, layer_index);

		Nirvana_Map_Layer current_layer = project->getStageLayer(stage_index, layer_index);

		switch(project->getLayerType(stage_index, layer_index))
		{
			case LAYER_TYPE_TILEMAP:
			{
			}
			break;

			case LAYER_TYPE_SPRITE:
			{
				m_mapEdit_layerSprite_listBox->Clear();
				for(int i = 0; i < current_layer.layer_sprites.size(); i++)
				{
					m_mapEdit_layerSprite_listBox->AppendAndEnsureVisible(wxString(current_layer.layer_sprites[i].sprite_name));
				}

				m_mapEdit_collisionShape_listBox->Clear();
				for(int i = 0; i < current_layer.layer_shapes.size(); i++)
				{
					m_mapEdit_collisionShape_listBox->AppendAndEnsureVisible(wxString(current_layer.layer_shapes[i].shape_name));
				}

				reloadSpriteProperties();
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
}

void NirvanaEditor_MainFrame::OnEnterMapView( wxMouseEvent& event )
{
	map_editor->getMapViewControl()->stage_window_isActive = true;
	map_editor->getMapViewControl()->mapEdit_tile_selection = map_editor->getTileSelectControl()->mapEdit_tile_selection;
}

void NirvanaEditor_MainFrame::OnLeaveMapView( wxMouseEvent& event )
{
	map_editor->getMapViewControl()->stage_window_isActive = false;
	map_editor->getMapViewControl()->mapEdit_lastAction_erase = false;
}

void NirvanaEditor_MainFrame::OnActiveLayerSelect( wxCommandEvent& event )
{
	map_editor->selectLayer(event.GetSelection());
	updateMapEditor();
}

void NirvanaEditor_MainFrame::OnLayerCheckListSelect( wxCommandEvent& event )
{
	wxString layer_name = event.GetString();
	m_layerName_textCtrl->SetValue(layer_name);

	int stage_index = map_editor->getSelectedStage();
	int layer_index = project->getLayerIndex(stage_index, layer_name.ToStdString());
	irr::core::vector2df scroll_speed = project->getLayerScrollSpeed(stage_index, layer_index);
	m_mapEdit_layerHScroll_spinCtrlDouble->SetValue(scroll_speed.X);
	m_mapEdit_layerVScroll_spinCtrlDouble->SetValue(scroll_speed.Y);

	int alpha = project->getLayerAlpha(stage_index, layer_index);
	m_mapEdit_layerAlpha_spinCtrl->SetValue(alpha);
}

void NirvanaEditor_MainFrame::OnLayerCheckList_Visible_Toggle( wxCommandEvent& event )
{
	int selected_item = m_layerVisible_checkList->GetSelection();
	if(selected_item < 0 || selected_item >= m_layerVisible_checkList->GetCount())
		return;

	wxString layer_name = m_layerVisible_checkList->GetString(selected_item);

	int stage_index = map_editor->getSelectedStage();
	int layer_index = project->getLayerIndex(stage_index, layer_name.ToStdString());

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	project->setLayerVisible(stage_index, layer_index, m_layerVisible_checkList->IsChecked(selected_item));

	int canvas_id = project->stages[stage_index].layers[layer_index].ref_canvas;

	if(canvas_id < 0 || canvas_id >= map_editor->getMapViewControl()->canvas.size())
		return;

	map_editor->getMapViewControl()->setCanvasVisible(canvas_id, project->getLayerVisible(stage_index, layer_index));
}

void NirvanaEditor_MainFrame::OnMapEdit_LayerNameChange( wxCommandEvent& event )
{
	if(event.GetString().Trim().length()==0)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = m_layerVisible_checkList->GetSelection();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	wxString test_layer_name = wxString(project->getLayerName(stage_index, layer_index)).Upper().Trim(); //Need to get name before change

	project->setLayerName(stage_index, layer_index, event.GetString().ToStdString());

	m_layerVisible_checkList->SetString(layer_index, wxString(project->getLayerName(stage_index, layer_index)));
	m_activeLayer_comboBox->SetString(layer_index, wxString(project->getLayerName(stage_index, layer_index)));
}

void NirvanaEditor_MainFrame::OnMapEdit_LayerHScroll( wxSpinDoubleEvent& event )
{
	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = m_layerVisible_checkList->GetSelection();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	irr::core::vector2df scroll_speed = project->getLayerScrollSpeed(stage_index, layer_index);
	scroll_speed.X = m_mapEdit_layerHScroll_spinCtrlDouble->GetValue();
	project->setLayerScrollSpeed(stage_index, layer_index, scroll_speed.X, scroll_speed.Y);
}

void NirvanaEditor_MainFrame::OnMapEdit_LayerVScroll( wxSpinDoubleEvent& event )
{
	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = m_layerVisible_checkList->GetSelection();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	irr::core::vector2df scroll_speed = project->getLayerScrollSpeed(stage_index, layer_index);
	scroll_speed.Y = m_mapEdit_layerVScroll_spinCtrlDouble->GetValue();
	project->setLayerScrollSpeed(stage_index, layer_index, scroll_speed.X, scroll_speed.Y);
}

void NirvanaEditor_MainFrame::OnMapEdit_LayerAlpha( wxSpinEvent& event )
{
	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = m_layerVisible_checkList->GetSelection();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	int alpha = m_mapEdit_layerAlpha_spinCtrl->GetValue();
	project->setLayerAlpha(stage_index, layer_index, alpha);
}

void NirvanaEditor_MainFrame::OnMapEdit_LayerUpClick( wxCommandEvent& event )
{
	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = m_layerVisible_checkList->GetSelection();

	//
	if(layer_index < 1 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	wxString active_layer_name = wxString(project->getLayerName(stage_index, map_editor->getSelectedLayer())).Upper().Trim();
	wxString checklist_layer_name = wxString(project->getLayerName(stage_index, layer_index)).Upper().Trim();

	bool active_layer_changed = (map_editor->getSelectedLayer() == layer_index);

	int new_layer_index = layer_index - 1;
	project->setLayerOrder(stage_index, layer_index, new_layer_index);

	//SET LAYER COMBO AND CHECKLIST
	m_layerVisible_checkList->Clear();
	m_activeLayer_comboBox->Clear();

	for(int i = 0; i < project->getStageNumLayers(stage_index); i++)
	{
		m_layerVisible_checkList->AppendAndEnsureVisible(wxString(project->getLayerName(stage_index, i)));
		m_layerVisible_checkList->Check(i, project->getLayerVisible(stage_index, i));

		m_activeLayer_comboBox->Append(project->getLayerName(stage_index, i));
	}

	m_layerVisible_checkList->SetSelection(new_layer_index);

	int active_layer_index = project->getLayerIndex(stage_index, active_layer_name.ToStdString());
	//std::cout << "ACT: " << active_layer_name.ToStdString() << " -> " << active_layer_index << std::endl;
	m_activeLayer_comboBox->SetSelection(active_layer_index);

	map_editor->selectLayer(active_layer_index);
}

void NirvanaEditor_MainFrame::OnMapEdit_LayerDownClick( wxCommandEvent& event )
{
	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = m_layerVisible_checkList->GetSelection();

	//
	if(layer_index < 0 || layer_index >= (project->getStageNumLayers(stage_index)-1) )
		return;

	wxString active_layer_name = wxString(project->getLayerName(stage_index, map_editor->getSelectedLayer())).Upper().Trim();
	wxString checklist_layer_name = wxString(project->getLayerName(stage_index, layer_index)).Upper().Trim();

	bool active_layer_changed = (map_editor->getSelectedLayer() == layer_index);

	int new_layer_index = layer_index + 1;
	project->setLayerOrder(stage_index, layer_index, new_layer_index);

	//SET LAYER COMBO AND CHECKLIST
	m_layerVisible_checkList->Clear();
	m_activeLayer_comboBox->Clear();

	for(int i = 0; i < project->getStageNumLayers(stage_index); i++)
	{
		m_layerVisible_checkList->AppendAndEnsureVisible(wxString(project->getLayerName(stage_index, i)));
		m_layerVisible_checkList->Check(i, project->getLayerVisible(stage_index, i));

		m_activeLayer_comboBox->Append(project->getLayerName(stage_index, i));
	}

	m_layerVisible_checkList->SetSelection(new_layer_index);

	int active_layer_index = project->getLayerIndex(stage_index, active_layer_name.ToStdString());
	//std::cout << "ACT: " << active_layer_name.ToStdString() << " -> " << active_layer_index << std::endl;
	m_activeLayer_comboBox->SetSelection(active_layer_index);

	map_editor->selectLayer(active_layer_index);
}

void NirvanaEditor_MainFrame::OnMapEdit_LayerDeleteClick( wxCommandEvent& event )
{
	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = m_layerVisible_checkList->GetSelection();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	wxString active_layer_name = wxString(project->getLayerName(stage_index, map_editor->getSelectedLayer())).Upper().Trim();
	wxString checklist_layer_name = wxString(project->getLayerName(stage_index, layer_index)).Upper().Trim();

	bool active_layer_changed = (map_editor->getSelectedLayer() == layer_index);

	map_editor->getMapViewControl()->canvasClose(project->stages[stage_index].layers[layer_index].ref_canvas);
	map_editor->getMapViewControl()->mapEdit_selectTileTool_selection.clear();
	project->stages[stage_index].layers[layer_index].ref_canvas = -1;
	project->deleteLayer(stage_index, layer_index);

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
	//std::cout << "ACT: " << active_layer_name.ToStdString() << " -> " << active_layer_index << std::endl;
	m_activeLayer_comboBox->SetSelection(active_layer_index);
	map_editor->selectLayer(active_layer_index);

	m_layerName_textCtrl->SetValue(_(""));
	m_mapEdit_layerHScroll_spinCtrlDouble->SetValue(0.0);
	m_mapEdit_layerVScroll_spinCtrlDouble->SetValue(0.0);
	m_mapEdit_layerAlpha_spinCtrl->SetValue(0);

	refreshCurrentLayerUI();
}

void NirvanaEditor_MainFrame::refreshCurrentLayerUI()
{
	m_mapEdit_layerSprite_listBox->Clear();

	wxPGProperty * sprite_id = m_mapEdit_sprite_propertyGrid->GetProperty(_("sprite_id"));
	wxPGProperty * sprite_body_type = m_mapEdit_sprite_propertyGrid->GetProperty(_("body_type"));
	wxPGProperty * sprite_animation = m_mapEdit_sprite_propertyGrid->GetProperty(_("animation"));
	wxPGProperty * sprite_pos_x = m_mapEdit_sprite_propertyGrid->GetProperty(_("position_x"));
	wxPGProperty * sprite_pos_y = m_mapEdit_sprite_propertyGrid->GetProperty(_("position_y"));
	wxPGProperty * sprite_angle = m_mapEdit_sprite_propertyGrid->GetProperty(_("angle"));
	wxPGProperty * sprite_scale_x = m_mapEdit_sprite_propertyGrid->GetProperty(_("scale_x"));
	wxPGProperty * sprite_scale_y = m_mapEdit_sprite_propertyGrid->GetProperty(_("scale_y"));
	wxPGProperty * sprite_alpha = m_mapEdit_sprite_propertyGrid->GetProperty(_("alpha"));
	wxPGProperty * sprite_visible = m_mapEdit_sprite_propertyGrid->GetProperty(_("visible"));


	sprite_id->SetValue(_(""));
	sprite_body_type->SetChoiceSelection(0);
	sprite_animation->SetChoices(wxPGChoices());
	sprite_pos_x->SetValue( 0 );
	sprite_pos_y->SetValue( 0 );
	sprite_angle->SetValue( 0 );
	sprite_scale_x->SetValue( 0 );
	sprite_scale_y->SetValue( 0 );
	sprite_alpha->SetValueFromInt( 0 );
	sprite_visible->SetValue( false );

	m_mapEdit_collisionShape_listBox->Clear();

	m_mapEdit_canvasImage_comboBox->Clear();
	//m_mapEdit_canvasRenderSetting_comboBox->SetSelection(0);

	int active_stage = map_editor->getSelectedStage();
	int active_layer = map_editor->getSelectedLayer();

	if(active_stage < 0 || active_stage >= project->stages.size())
		return;

	if(active_layer < 0 || active_layer >= project->stages[active_stage].layers.size())
		return;


	switch(project->getLayerType(active_stage, active_layer))
	{
		case LAYER_TYPE_TILEMAP:
		{
		}
		break;

		case LAYER_TYPE_SPRITE:
		{
			reloadSpriteProperties();
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

void NirvanaEditor_MainFrame::OnMapEdit_Map_UpdateUI( wxUpdateUIEvent& event )
{
	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();

	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = map_editor->getSelectedLayer();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	if(project->getLayerType(stage_index, layer_index)==LAYER_TYPE_SPRITE)
	{
		if(map_editor->getMapViewControl()->mapEdit_selectSpriteTool_selection.size()==1)
		{
			if(map_editor->getMapViewControl()->map_sprite_selection_changed)
			{
				int selected_sprite = map_editor->getMapViewControl()->selected_sprite;
				if(selected_sprite >= 0 && selected_sprite < project->stages[stage_index].layers[layer_index].layer_sprites.size())
				{
					wxString spr_name = wxString(project->stages[stage_index].layers[layer_index].layer_sprites[selected_sprite].sprite_name).Upper().Trim();

					//std::cout << std::endl << "LOOKUP: " << spr_name.ToStdString() << std::endl;

					for(int i = 0; i < m_mapEdit_layerSprite_listBox->GetCount(); i++)
					{
						wxString list_item = m_mapEdit_layerSprite_listBox->GetString(i).Upper().Trim();
						if(list_item.compare(spr_name) == 0)
						{
							//std::cout << "Found: " << spr_name << " at " << i << std::endl;
							m_mapEdit_layerSprite_listBox->SetSelection(i);
							break;
						}
					}
				}
				else
				{
					m_mapEdit_layerSprite_listBox->DeselectAll();
				}

				reloadSpriteProperties();
			}
		}
		else if(map_editor->getMapViewControl()->map_sprite_selection_changed)
		{
			m_mapEdit_layerSprite_listBox->DeselectAll();
			reloadSpriteProperties();
		}

		if(map_editor->getMapViewControl()->pick_shape_update)
		{
			map_editor->getMapViewControl()->pick_shape_update = false;
			refreshCurrentShapeUI();
		}
	}

	map_editor->getMapViewControl()->map_sprite_selection_changed = false;
}
