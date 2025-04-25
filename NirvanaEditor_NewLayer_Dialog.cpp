#include "NirvanaEditor_NewLayer_Dialog.h"

NirvanaEditor_NewLayer_Dialog::NirvanaEditor_NewLayer_Dialog( wxWindow* parent )
:
NewLayer_Dialog( parent )
{
	create_flag = false;

	m_layerType_comboBox->Append(_("TILEMAP"));
	m_layerType_comboBox->Append(_("SPRITE"));
	m_layerType_comboBox->Append(_("CANVAS 2D"));
	m_layerType_comboBox->Append(_("CANVAS 3D"));
}

void NirvanaEditor_NewLayer_Dialog::OnCreate( wxCommandEvent& event )
{
	create_flag = true;

	selected_type = m_layerType_comboBox->GetSelection();

	layer_name = m_layerName_textCtrl->GetValue();

	int selected_list_item = m_tileset_listBox->GetSelection();
	if(selected_list_item >= 0 && selected_list_item < m_tileset_listBox->GetCount())
		selected_tileset = m_tileset_listBox->GetString(selected_list_item);

	Close();
}

void NirvanaEditor_NewLayer_Dialog::OnCancel( wxCommandEvent& event )
{
	Close();
}

void NirvanaEditor_NewLayer_Dialog::OnLayerTypeSelect( wxCommandEvent& event )
{
	if(event.GetSelection() == 0)
	{
		m_layerType_simplebook->SetSelection(1);
	}
	else
	{
		m_layerType_simplebook->SetSelection(0);
	}
}

void NirvanaEditor_NewLayer_Dialog::OnSearch( wxCommandEvent& event )
{
	refresh_list();
}

void NirvanaEditor_NewLayer_Dialog::refresh_list()
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
