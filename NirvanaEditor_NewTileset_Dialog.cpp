#include "NirvanaEditor_NewTileset_Dialog.h"

NirvanaEditor_NewTileset_Dialog::NirvanaEditor_NewTileset_Dialog( wxWindow* parent )
:
NewTileset_Dialog( parent )
{
	create_flag = false;
}

void NirvanaEditor_NewTileset_Dialog::OnSearch( wxCommandEvent& event )
{
	refresh_list();
}

void NirvanaEditor_NewTileset_Dialog::OnCreate( wxCommandEvent& event )
{
	create_flag = true;
	id_name = m_tilesetID_textCtrl->GetValue();

	if(m_tileSheet_listBox->GetSelection() >= 0 && m_tileSheet_listBox->GetSelection() < m_tileSheet_listBox->GetCount())
		selected_file = m_tileSheet_listBox->GetString( m_tileSheet_listBox->GetSelection() );
	else
		selected_file = _("");

	frame_width = m_tileWidth_spinCtrl->GetValue();
	frame_height = m_tileHeight_spinCtrl->GetValue();

	Close();
}

void NirvanaEditor_NewTileset_Dialog::OnCancel( wxCommandEvent& event )
{
	Close();
}

void NirvanaEditor_NewTileset_Dialog::refresh_list()
{
	files.Sort();

	wxString search_string = m_tileSheet_searchCtrl->GetValue();
	search_string = search_string.Lower();

	m_tileSheet_listBox->Clear();

	for(int i = 0; i < files.size(); i++)
	{
		if(search_string.Length() == 0)
		{
			m_tileSheet_listBox->AppendAndEnsureVisible(files.Item(i));
		}
		else if( files.Item(i).Lower().substr(0, search_string.length()).compare(search_string) == 0 )
		{
			m_tileSheet_listBox->AppendAndEnsureVisible(files.Item(i));
		}
	}
}
