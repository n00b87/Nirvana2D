#include "NirvanaEditor_SpriteLayer_SelectTileset_Dialog.h"

NirvanaEditor_SpriteLayer_SelectTileset_Dialog::NirvanaEditor_SpriteLayer_SelectTileset_Dialog( wxWindow* parent )
:
SpriteLayer_SelectTileset_Dialog( parent )
{
    select_flag = false;
}

void NirvanaEditor_SpriteLayer_SelectTileset_Dialog::OnSearch( wxCommandEvent& event )
{
    refresh_list();
}

void NirvanaEditor_SpriteLayer_SelectTileset_Dialog::OnCancel( wxCommandEvent& event )
{
    Close();
}

void NirvanaEditor_SpriteLayer_SelectTileset_Dialog::OnSelect( wxCommandEvent& event )
{
    int selected_list_item = m_tileset_listBox->GetSelection();
	if(selected_list_item >= 0 && selected_list_item < m_tileset_listBox->GetCount())
		selected_tileset = m_tileset_listBox->GetString(selected_list_item);

    select_flag = true;

    Close();
}

void NirvanaEditor_SpriteLayer_SelectTileset_Dialog::refresh_list()
{
	tileset_list.Sort();

	wxString search_string = m_tileset_searchCtrl->GetValue();
	search_string = search_string.Lower();

	m_tileset_listBox->Clear();

	for(int i = 0; i < tileset_list.size(); i++)
	{
		if(search_string.Length() == 0)
		{
			m_tileset_listBox->AppendAndEnsureVisible(tileset_list.Item(i));
		}
		else if( tileset_list.Item(i).Lower().substr(0, search_string.length()).compare(search_string) == 0 )
		{
			m_tileset_listBox->AppendAndEnsureVisible(tileset_list.Item(i));
		}
	}
}
