#include "NirvanaEditor_MainFrame.h"
#include <wx/stdpaths.h>
#include <wx/dir.h>
#include <wx/arrstr.h>

#include "NirvanaEditor_NewStage_Dialog.h"
#include "NirvanaEditor_NewLayer_Dialog.h"
#include "NirvanaEditor_DeleteStage_Dialog.h"
#include "NirvanaEditor_StageProperties_Dialog.h"
#include "Nirvana_Project.h"

void NirvanaEditor_MainFrame::OnMapEdit_TileTool_Select( wxCommandEvent& event )
{
	selected_map_tool = MAP_TOOL_TILE_SELECT;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_TileTool_BoxSelect( wxCommandEvent& event )
{
	selected_map_tool = MAP_TOOL_TILE_BOXSELECT;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_TileTool_Move( wxCommandEvent& event )
{
	selected_map_tool = MAP_TOOL_TILE_MOVE;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_TileTool_SetTile( wxCommandEvent& event )
{
	selected_map_tool = MAP_TOOL_TILE_SET;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_TileTool_CopyTile( wxCommandEvent& event )
{
	selected_map_tool = MAP_TOOL_TILE_COPY;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_TileTool_FillTile( wxCommandEvent& event )
{
	selected_map_tool = MAP_TOOL_TILE_FILL;
	map_editor->setMapTool(selected_map_tool);
}

void NirvanaEditor_MainFrame::OnMapEdit_TileTool_DeleteSelected( wxCommandEvent& event )
{
	selected_map_tool = MAP_TOOL_TILE_DELETE;
	map_editor->setMapTool(selected_map_tool);
}
