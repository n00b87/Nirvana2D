#include "NirvanaEditor_SetCamera_Dialog.h"

NirvanaEditor_SetCamera_Dialog::NirvanaEditor_SetCamera_Dialog( wxWindow* parent )
:
SetCamera_Dialog( parent )
{
	set_flag = false;
}

void NirvanaEditor_SetCamera_Dialog::OnCancel( wxCommandEvent& event )
{
	Close();
}

void NirvanaEditor_SetCamera_Dialog::OnSet( wxCommandEvent& event )
{
	m_posX_textCtrl->GetValue().ToInt(&offset_x);
	m_posY_textCtrl->GetValue().ToInt(&offset_y);

	set_flag = true;
	Close();
}

void NirvanaEditor_SetCamera_Dialog::initOffset(int x, int y)
{
	m_posX_textCtrl->SetValue(wxString::Format(_("%i"), x));
	m_posY_textCtrl->SetValue(wxString::Format(_("%i"), y));
}
