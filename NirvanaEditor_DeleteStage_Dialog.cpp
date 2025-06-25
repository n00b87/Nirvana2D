#include "NirvanaEditor_DeleteStage_Dialog.h"

NirvanaEditor_DeleteStage_Dialog::NirvanaEditor_DeleteStage_Dialog( wxWindow* parent )
:
DeleteStage_Dialog( parent )
{
	delete_flag = false;
}

void NirvanaEditor_DeleteStage_Dialog::OnDelete( wxCommandEvent& event )
{
	delete_flag = true;
	Close();
}

void NirvanaEditor_DeleteStage_Dialog::OnCancel( wxCommandEvent& event )
{
	Close();
}

void NirvanaEditor_DeleteStage_Dialog::setStageName(wxString stage_name)
{
	m_msg_staticText->SetLabelText(_("DELETE STAGE: ") + stage_name);
}
