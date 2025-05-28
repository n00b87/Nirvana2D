#include "NirvanaEditor_MainFrame.h"
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/arrstr.h>

#include "Nirvana_Project.h"


void NirvanaEditor_MainFrame::OnMapEdit_ShapeTool_Select( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	selected_map_tool = MAP_TOOL_SHAPE_SELECT;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_ShapeTool_BoxSelect( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	selected_map_tool = MAP_TOOL_SHAPE_BOXSELECT;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_ShapeTool_Move( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	selected_map_tool = MAP_TOOL_SHAPE_MOVE;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_ShapeTool_Draw( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	selected_map_tool = MAP_TOOL_SHAPE_DRAW;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_ShapeTool_NewBoxShape( wxCommandEvent& event )
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

	int shape_index = project->createShape(stage_index, layer_index, SPRITE_SHAPE_BOX);

	if(shape_index < 0)
		return;

	wxString shape_name = wxString(project->getShapeName(stage_index, layer_index, shape_index)).Trim();
	m_mapEdit_collisionShape_listBox->AppendAndEnsureVisible(shape_name);
	m_mapEdit_collisionShape_listBox->SetSelection(m_mapEdit_collisionShape_listBox->GetCount()-1);

	map_editor->selectShape(shape_index);

	selected_map_tool = MAP_TOOL_SHAPE_DRAW;
	map_editor->setMapTool(selected_map_tool);
	m_mapEdit_shapeTools_auiToolBar->ToggleTool(m_mapEdit_shapeToolbar_draw_tool->GetId(), true);

	refreshCurrentShapeUI();
}

void NirvanaEditor_MainFrame::OnMapEdit_ShapeTool_NewPolygonShape( wxCommandEvent& event )
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

	int shape_index = project->createShape(stage_index, layer_index, SPRITE_SHAPE_POLYGON);

	if(shape_index < 0)
		return;

	wxString shape_name = wxString(project->getShapeName(stage_index, layer_index, shape_index)).Trim();
	m_mapEdit_collisionShape_listBox->AppendAndEnsureVisible(shape_name);
	m_mapEdit_collisionShape_listBox->SetSelection(m_mapEdit_collisionShape_listBox->GetCount()-1);

	map_editor->selectShape(shape_index);

	selected_map_tool = MAP_TOOL_SHAPE_DRAW;
	map_editor->setMapTool(selected_map_tool);
	m_mapEdit_shapeTools_auiToolBar->ToggleTool(m_mapEdit_shapeToolbar_draw_tool->GetId(), true);

	refreshCurrentShapeUI();
}

void NirvanaEditor_MainFrame::OnMapEdit_ShapeTool_NewChainShape( wxCommandEvent& event )
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

	int shape_index = project->createShape(stage_index, layer_index, SPRITE_SHAPE_CHAIN);

	if(shape_index < 0)
		return;

	wxString shape_name = wxString(project->getShapeName(stage_index, layer_index, shape_index)).Trim();
	m_mapEdit_collisionShape_listBox->AppendAndEnsureVisible(shape_name);
	m_mapEdit_collisionShape_listBox->SetSelection(m_mapEdit_collisionShape_listBox->GetCount()-1);

	map_editor->selectShape(shape_index);

	selected_map_tool = MAP_TOOL_SHAPE_DRAW;
	map_editor->setMapTool(selected_map_tool);
	m_mapEdit_shapeTools_auiToolBar->ToggleTool(m_mapEdit_shapeToolbar_draw_tool->GetId(), true);

	refreshCurrentShapeUI();
}

void NirvanaEditor_MainFrame::OnMapEdit_ShapeTool_NewCircleShape( wxCommandEvent& event )
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

	int shape_index = project->createShape(stage_index, layer_index, SPRITE_SHAPE_CIRCLE);

	if(shape_index < 0)
		return;

	wxString shape_name = wxString(project->getShapeName(stage_index, layer_index, shape_index)).Trim();
	m_mapEdit_collisionShape_listBox->AppendAndEnsureVisible(shape_name);
	m_mapEdit_collisionShape_listBox->SetSelection(m_mapEdit_collisionShape_listBox->GetCount()-1);

	map_editor->selectShape(shape_index);

	selected_map_tool = MAP_TOOL_SHAPE_DRAW;
	map_editor->setMapTool(selected_map_tool);
	m_mapEdit_shapeTools_auiToolBar->ToggleTool(m_mapEdit_shapeToolbar_draw_tool->GetId(), true);

	refreshCurrentShapeUI();
}

void NirvanaEditor_MainFrame::OnMapEdit_ShapeTool_DeleteShape( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = map_editor->getSelectedLayer();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	int shape_index = map_editor->getSelectedShape();

	if(shape_index < 0 || shape_index >= project->stages[stage_index].layers[layer_index].layer_shapes.size())
		return;

	project->deleteShape(stage_index, layer_index, shape_index);
	map_editor->selectShape(-1);

	m_mapEdit_collisionShape_listBox->DeselectAll();
	m_mapEdit_collisionShape_listBox->Clear();
	for(int i = 0; i < project->stages[stage_index].layers[layer_index].layer_shapes.size(); i++)
	{
		m_mapEdit_collisionShape_listBox->AppendAndEnsureVisible(wxString(project->stages[stage_index].layers[layer_index].layer_shapes[i].shape_name));
	}

	m_mapEdit_shapeEdit_simplebook->SetSelection(0);
	refreshCurrentShapeUI();
}


void NirvanaEditor_MainFrame::refreshCurrentShapeUI()
{
	if(!editor_init)
		return;

	m_mapEdit_shapeName_textCtrl->SetValue(_(""));

	m_mapEdit_boxShape_posX_spinCtrl->SetValue(0);
	m_mapEdit_boxShape_posY_spinCtrl->SetValue(0);
	m_mapEdit_boxShape_width_spinCtrl->SetValue(0);
	m_mapEdit_boxShape_height_spinCtrl->SetValue(0);

	if(m_mapEdit_polyShape_grid->GetNumberRows() > 0)
		m_mapEdit_polyShape_grid->DeleteRows(0, m_mapEdit_polyShape_grid->GetNumberRows());

	m_mapEdit_circleShape_centerX_spinCtrl->SetValue(0);
	m_mapEdit_circleShape_centerY_spinCtrl->SetValue(0);
	m_mapEdit_circleShape_radius_spinCtrl->SetValue(0);

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0)
		return;

	int layer_index = map_editor->getSelectedLayer();
	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	int shape_index = map_editor->getSelectedShape();

	if(shape_index < 0)
		return;

	int shape_type = project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].shape_type;

	int box_page_index = 1;
	int poly_page_index = 2;
	int circle_page_index = 3;

	m_mapEdit_shapeName_textCtrl->SetValue(wxString(project->getShapeName(stage_index, layer_index, shape_index)));


	switch(shape_type)
	{
		case SPRITE_SHAPE_BOX:
		{
			m_mapEdit_shapeEdit_simplebook->SetSelection(box_page_index);

			m_mapEdit_boxShape_posX_spinCtrl->SetValue(project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].offset_x);
			m_mapEdit_boxShape_posY_spinCtrl->SetValue(project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].offset_y);
			m_mapEdit_boxShape_width_spinCtrl->SetValue(project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].box_width);
			m_mapEdit_boxShape_height_spinCtrl->SetValue(project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].box_height);
		}
		break;

		case SPRITE_SHAPE_POLYGON:
		{
			m_mapEdit_shapeEdit_simplebook->SetSelection(poly_page_index);
			m_mapEdit_polyShape_grid->AppendRows(project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].points.size());

			for(int i = 0; i < project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].points.size(); i++)
			{
				int point_x = project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].points[i].X;
				int point_y = project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].points[i].Y;
				m_mapEdit_polyShape_grid->SetCellValue(i, 0, wxString::Format(_("%i"), point_x) );
				m_mapEdit_polyShape_grid->SetCellValue(i, 1, wxString::Format(_("%i"), point_y) );
			}
		}
		break;

		case SPRITE_SHAPE_CIRCLE:
		{
			m_mapEdit_shapeEdit_simplebook->SetSelection(circle_page_index);

			m_mapEdit_circleShape_centerX_spinCtrl->SetValue(project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].offset_x);
			m_mapEdit_circleShape_centerY_spinCtrl->SetValue(project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].offset_y);
			m_mapEdit_circleShape_radius_spinCtrl->SetValue(project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].radius);
		}
		break;

		case SPRITE_SHAPE_CHAIN:
		{
			m_mapEdit_shapeEdit_simplebook->SetSelection(poly_page_index);
			m_mapEdit_polyShape_grid->AppendRows(project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].points.size());

			for(int i = 0; i < project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].points.size(); i++)
			{
				int point_x = project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].points[i].X;
				int point_y = project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].points[i].Y;
				m_mapEdit_polyShape_grid->SetCellValue(i, 0, wxString::Format(_("%i"), point_x) );
				m_mapEdit_polyShape_grid->SetCellValue(i, 1, wxString::Format(_("%i"), point_y) );
			}
		}
		break;
	}
}

void NirvanaEditor_MainFrame::OnMapEdit_shapeListSelect( wxCommandEvent& event )
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

	int shapeList_index = m_mapEdit_collisionShape_listBox->GetSelection();
	if(shapeList_index < 0 || shapeList_index >= m_mapEdit_collisionShape_listBox->GetCount())
		return;

	wxString shapeList_item_name = m_mapEdit_collisionShape_listBox->GetString(shapeList_index);
	int shape_index = project->getShapeIndex(stage_index, layer_index, shapeList_item_name.ToStdString());

	if(shape_index < 0)
		return;

	wxString shape_name = wxString(project->getShapeName(stage_index, layer_index, shape_index)).Trim();

	int shape_type = project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].shape_type;

	map_editor->selectShape(shape_index);

	refreshCurrentShapeUI();

	//std::cout << "shape_name: " << shape_name.ToStdString() << ", " << shape_index << std::endl;
}


void NirvanaEditor_MainFrame::OnMapEdit_ShapeName( wxCommandEvent& event )
{
	if(!editor_init)
		return;

	if(event.GetString().Trim().length()==0)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = map_editor->getSelectedLayer();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	int shape_index = map_editor->getSelectedShape();

	if(shape_index < 0 || shape_index >= project->stages[stage_index].layers[layer_index].layer_shapes.size())
		return;

	wxString shape_name = wxString(project->getShapeName(stage_index, layer_index, shape_index)).Upper().Trim(); //Need to get name before change

	project->setShapeName(stage_index, layer_index, shape_index, event.GetString().ToStdString());

	m_mapEdit_collisionShape_listBox->SetString(shape_index, wxString(project->getShapeName(stage_index, layer_index, shape_index)));
}

void NirvanaEditor_MainFrame::OnMapEdit_BoxShape_PosX( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = map_editor->getSelectedLayer();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	int shape_index = map_editor->getSelectedShape();

	if(shape_index < 0 || shape_index >= project->stages[stage_index].layers[layer_index].layer_shapes.size())
		return;

	project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].offset_x = m_mapEdit_boxShape_posX_spinCtrl->GetValue();
}

void NirvanaEditor_MainFrame::OnMapEdit_BoxShape_PosY( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = map_editor->getSelectedLayer();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	int shape_index = map_editor->getSelectedShape();

	if(shape_index < 0 || shape_index >= project->stages[stage_index].layers[layer_index].layer_shapes.size())
		return;

	project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].offset_y = m_mapEdit_boxShape_posY_spinCtrl->GetValue();
}

void NirvanaEditor_MainFrame::OnMapEdit_BoxShape_Width( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = map_editor->getSelectedLayer();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	int shape_index = map_editor->getSelectedShape();

	if(shape_index < 0 || shape_index >= project->stages[stage_index].layers[layer_index].layer_shapes.size())
		return;

	project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].box_width = m_mapEdit_boxShape_width_spinCtrl->GetValue();
}

void NirvanaEditor_MainFrame::OnMapEdit_BoxShape_Height( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = map_editor->getSelectedLayer();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	int shape_index = map_editor->getSelectedShape();

	if(shape_index < 0 || shape_index >= project->stages[stage_index].layers[layer_index].layer_shapes.size())
		return;

	project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].box_height = m_mapEdit_boxShape_height_spinCtrl->GetValue();
}

void NirvanaEditor_MainFrame::OnMapEdit_PolyShape_CellChange( wxGridEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = map_editor->getSelectedLayer();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	int shape_index = map_editor->getSelectedShape();

	if(shape_index < 0 || shape_index >= project->stages[stage_index].layers[layer_index].layer_shapes.size())
		return;

	int cell_row = event.GetRow();
	int cell_col = event.GetCol();

	if(cell_row < 0 || cell_row >= m_mapEdit_polyShape_grid->GetNumberRows())
		return;

	if(cell_col < 0 || cell_col >= m_mapEdit_polyShape_grid->GetNumberCols())
		return;

	if(cell_row >= project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].points.size())
		return;

	if(cell_col == 0)
		m_mapEdit_polyShape_grid->GetCellValue(cell_row, cell_col).ToInt(&project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].points[cell_row].X);
	else if(cell_col == 1)
		m_mapEdit_polyShape_grid->GetCellValue(cell_row, cell_col).ToInt(&project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].points[cell_row].Y);
}

void NirvanaEditor_MainFrame::OnMapEdit_CircleShape_CenterX( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = map_editor->getSelectedLayer();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	int shape_index = map_editor->getSelectedShape();

	if(shape_index < 0 || shape_index >= project->stages[stage_index].layers[layer_index].layer_shapes.size())
		return;

	project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].offset_x = m_mapEdit_circleShape_centerX_spinCtrl->GetValue();
}

void NirvanaEditor_MainFrame::OnMapEdit_CircleShape_CenterY( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = map_editor->getSelectedLayer();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	int shape_index = map_editor->getSelectedShape();

	if(shape_index < 0 || shape_index >= project->stages[stage_index].layers[layer_index].layer_shapes.size())
		return;

	project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].offset_y = m_mapEdit_circleShape_centerY_spinCtrl->GetValue();
}

void NirvanaEditor_MainFrame::OnMapEdit_CircleShape_Radius( wxSpinEvent& event )
{
	if(!editor_init)
		return;

	if(!project)
		return;

	int stage_index = map_editor->getSelectedStage();
	if(stage_index < 0 || stage_index >= project->getStageCount())
		return;

	int layer_index = map_editor->getSelectedLayer();

	if(layer_index < 0 || layer_index >= project->getStageNumLayers(stage_index))
		return;

	int shape_index = map_editor->getSelectedShape();

	if(shape_index < 0 || shape_index >= project->stages[stage_index].layers[layer_index].layer_shapes.size())
		return;

	project->stages[stage_index].layers[layer_index].layer_shapes[shape_index].radius = m_mapEdit_circleShape_radius_spinCtrl->GetValue();
}
