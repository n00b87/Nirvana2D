#include "NirvanaEditor_NewSprite_Dialog.h"

NirvanaEditor_NewSprite_Dialog::NirvanaEditor_NewSprite_Dialog( wxWindow* parent )
:
NewSprite_Dialog( parent )
{
	create_flag = false;
}

void NirvanaEditor_NewSprite_Dialog::OnSearch( wxCommandEvent& event )
{
	refresh_list();
}

void NirvanaEditor_NewSprite_Dialog::OnCreate( wxCommandEvent& event )
{
	create_flag = true;
	id_name = m_spriteID_textCtrl->GetValue();

	if(m_spriteSheet_listBox->GetSelection() >= 0 && m_spriteSheet_listBox->GetSelection() < m_spriteSheet_listBox->GetCount())
		selected_file = m_spriteSheet_listBox->GetString( m_spriteSheet_listBox->GetSelection() );
	else
		selected_file = _("");

	frame_width = m_frameWidth_spinCtrl->GetValue();
	frame_height = m_frameHeight_spinCtrl->GetValue();

	Close();
}

void NirvanaEditor_NewSprite_Dialog::OnCancel( wxCommandEvent& event )
{
	Close();
}

void NirvanaEditor_NewSprite_Dialog::refresh_list()
{
	files.Sort();

	wxString search_string = m_spriteSheet_searchCtrl->GetValue();
	search_string = search_string.Lower();

	m_spriteSheet_listBox->Clear();

	for(int i = 0; i < files.size(); i++)
	{
		if(search_string.Length() == 0)
		{
			m_spriteSheet_listBox->AppendAndEnsureVisible(files.Item(i));
		}
		else if( files.Item(i).Lower().substr(0, search_string.length()).compare(search_string) == 0 )
		{
			m_spriteSheet_listBox->AppendAndEnsureVisible(files.Item(i));
		}
	}
}
