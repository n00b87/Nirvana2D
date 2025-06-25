#include "NirvanaEditor_DeleteSprite_Dialog.h"

NirvanaEditor_DeleteSprite_Dialog::NirvanaEditor_DeleteSprite_Dialog( wxWindow* parent )
:
DeleteSprite_Dialog( parent )
{
	delete_flag = false;
}

void NirvanaEditor_DeleteSprite_Dialog::OnDelete( wxCommandEvent& event )
{
	delete_flag = true;
	Close();
}

void NirvanaEditor_DeleteSprite_Dialog::OnCancel( wxCommandEvent& event )
{
	Close();
}

void NirvanaEditor_DeleteSprite_Dialog::setSpriteName(wxString stage_name)
{
	m_msg_staticText->SetLabelText(_("SPRITE: ") + stage_name);
}
