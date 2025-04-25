#include "NirvanaEditor_NewStage_Dialog.h"

NirvanaEditor_NewStage_Dialog::NirvanaEditor_NewStage_Dialog( wxWindow* parent )
:
NewStage_Dialog( parent )
{
	create_flag = false;
}

void NirvanaEditor_NewStage_Dialog::OnCreate( wxCommandEvent& event )
{
	create_flag = true;
	stage_name = m_stageID_textCtrl->GetValue();
	tile_width = m_tileWidth_spinCtrl->GetValue();
	tile_height = m_tileHeight_spinCtrl->GetValue();
	width_in_tiles = m_width_spinCtrl->GetValue();
	height_in_tiles = m_height_spinCtrl->GetValue();
	Close();
}

void NirvanaEditor_NewStage_Dialog::OnCancel( wxCommandEvent& event )
{
	Close();
}
