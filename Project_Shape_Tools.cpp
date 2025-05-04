#include "NirvanaEditor_MainFrame.h"
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/arrstr.h>

#include "Nirvana_Project.h"


void NirvanaEditor_MainFrame::OnMapEdit_ShapeTool_Select( wxCommandEvent& event )
{
}

void NirvanaEditor_MainFrame::OnMapEdit_ShapeTool_BoxSelect( wxCommandEvent& event )
{
}

void NirvanaEditor_MainFrame::OnMapEdit_ShapeTool_Move( wxCommandEvent& event )
{
}

void NirvanaEditor_MainFrame::OnMapEdit_ShapeTool_Draw( wxCommandEvent& event )
{
	selected_map_tool = MAP_TOOL_SHAPE_DRAW;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_ShapeTool_NewBoxShape( wxCommandEvent& event )
{
}

void NirvanaEditor_MainFrame::OnMapEdit_ShapeTool_NewPolygonShape( wxCommandEvent& event )
{
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

	refreshCurrentShapeUI();
}

void NirvanaEditor_MainFrame::OnMapEdit_ShapeTool_NewChainShape( wxCommandEvent& event )
{
}

void NirvanaEditor_MainFrame::OnMapEdit_ShapeTool_NewCircleShape( wxCommandEvent& event )
{
}

void NirvanaEditor_MainFrame::OnMapEdit_ShapeTool_DeleteShape( wxCommandEvent& event )
{
}


void NirvanaEditor_MainFrame::refreshCurrentShapeUI()
{
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


	switch(shape_type)
	{
		case SPRITE_SHAPE_BOX:
		{
		}
		break;

		case SPRITE_SHAPE_POLYGON:
		{
			m_mapEdit_shapeEdit_simplebook->SetSelection(box_page_index);
		}
		break;

		case SPRITE_SHAPE_CIRCLE:
		{
		}
		break;

		case SPRITE_SHAPE_CHAIN:
		{
		}
		break;
	}
}

void NirvanaEditor_MainFrame::OnMapEdit_shapeListSelect( wxCommandEvent& event )
{
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

	std::cout << "shape_name: " << shape_name.ToStdString() << ", " << shape_index << std::endl;
}
