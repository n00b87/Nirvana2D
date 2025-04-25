#include "NirvanaEditor_StageProperties_Dialog.h"

NirvanaEditor_StageProperties_Dialog::NirvanaEditor_StageProperties_Dialog( wxWindow* parent )
:
StageProperties_Dialog( parent )
{
	set_flag = false;
}

void NirvanaEditor_StageProperties_Dialog::OnCreate( wxCommandEvent& event )
{
	stage_name = m_stageID_textCtrl->GetValue();

	tiles_across = m_width_spinCtrl->GetValue();
	tiles_down = m_height_spinCtrl->GetValue();

	set_flag = true;
	Close();
}

void NirvanaEditor_StageProperties_Dialog::OnCancel( wxCommandEvent& event )
{
	Close();
}

void NirvanaEditor_StageProperties_Dialog::setStageProperties(wxString s_name, int t_width, int t_height, int stage_w, int stage_h)
{
	m_stageID_textCtrl->SetValue(s_name);
	m_tileWidth_staticText->SetLabelText( wxString::Format(_("%i"), t_width) );
	m_tileHeight_staticText->SetLabelText( wxString::Format(_("%i"), t_height) );
	m_width_spinCtrl->SetValue(stage_w);
	m_height_spinCtrl->SetValue(stage_h);
}
