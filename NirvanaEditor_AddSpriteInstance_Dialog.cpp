#include "NirvanaEditor_AddSpriteInstance_Dialog.h"

NirvanaEditor_AddSpriteInstance_Dialog::NirvanaEditor_AddSpriteInstance_Dialog( wxWindow* parent )
:
AddSpriteInstance_Dialog( parent )
{
	create_flag = false;
}

void NirvanaEditor_AddSpriteInstance_Dialog::OnSearch( wxCommandEvent& event )
{
	refresh_list();
}

void NirvanaEditor_AddSpriteInstance_Dialog::OnCreate( wxCommandEvent& event )
{
	create_flag = true;
	id_name = m_spriteID_textCtrl->GetValue();

	if(m_baseSpriteList_listBox->GetSelection() >= 0 && m_baseSpriteList_listBox->GetSelection() < m_baseSpriteList_listBox->GetCount())
		selected_base = m_baseSpriteList_listBox->GetString( m_baseSpriteList_listBox->GetSelection() );
	else
		selected_base = _("");

	Close();
}

void NirvanaEditor_AddSpriteInstance_Dialog::OnCancel( wxCommandEvent& event )
{
	Close();
}

void NirvanaEditor_AddSpriteInstance_Dialog::refresh_list()
{
	base_sprites.Sort();

	wxString search_string = m_baseSprite_searchCtrl->GetValue();
	search_string = search_string.Lower();

	m_baseSpriteList_listBox->Clear();

	for(int i = 0; i < base_sprites.size(); i++)
	{
		if(search_string.Length() == 0)
		{
			m_baseSpriteList_listBox->AppendAndEnsureVisible(base_sprites.Item(i));
		}
		else if( base_sprites.Item(i).Lower().substr(0, search_string.length()).compare(search_string) == 0 )
		{
			m_baseSpriteList_listBox->AppendAndEnsureVisible(base_sprites.Item(i));
		}
	}
}
