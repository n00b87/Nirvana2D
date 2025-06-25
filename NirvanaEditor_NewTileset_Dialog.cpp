#include "NirvanaEditor_NewTileset_Dialog.h"
#include <wx/wx.h>

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
	wxString test_id = m_tilesetID_textCtrl->GetValue().Upper().Trim();

	if(m_tileSheet_listBox->GetSelection() >= 0 && m_tileSheet_listBox->GetSelection() < m_tileSheet_listBox->GetCount())
		selected_file = m_tileSheet_listBox->GetString( m_tileSheet_listBox->GetSelection() );
	else
		selected_file = _("");

	if(selected_file.compare(_(""))==0)
	{
		wxMessageBox(_("Must select image for tileset"));
		return;
	}

	wxFileName p_tset_def(project->getDir());
	p_tset_def.AppendDir(project->tile_path);
	p_tset_def.SetFullName(selected_file + _(".tset"));

	if(!p_tset_def.Exists())
	{
		if(project)
		{
			if(!project->checkName(test_id.ToStdString()))
			{
				wxMessageBox(_("Illegal Character in Tileset ID"));
				return;
			}
		}
	}

	for(int i = 0; i < current_tset_id.size(); i++)
	{
		if(current_tset_id.Item(i).Upper().Trim().compare(test_id)==0)
		{
			wxMessageBox(_("Tileset ID already exists"));
			return;
		}
	}

	id_name = m_tilesetID_textCtrl->GetValue().Trim();

	create_flag = true;

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

	wxString ignore_ext = _(".tset");

	for(int i = 0; i < files.size(); i++)
	{
		if(files.Item(i).length() >= ignore_ext.length())
		{
			if(files.Item(i).substr(files.Item(i).length() - ignore_ext.length()).compare(ignore_ext)==0)
				continue;
		}

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
