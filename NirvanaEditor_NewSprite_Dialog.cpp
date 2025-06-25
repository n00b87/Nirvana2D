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
	wxString test_id = m_spriteID_textCtrl->GetValue().Upper().Trim();

	if(m_spriteSheet_listBox->GetSelection() >= 0 && m_spriteSheet_listBox->GetSelection() < m_spriteSheet_listBox->GetCount())
		selected_file = m_spriteSheet_listBox->GetString( m_spriteSheet_listBox->GetSelection() );
	else
		selected_file = _("");

	if(selected_file.compare(_(""))==0)
	{
		wxMessageBox(_("Must select image for sprite"));
		return;
	}

	wxFileName p_spr_def(project->getDir());
	p_spr_def.AppendDir(project->sprite_path);
	p_spr_def.SetFullName(selected_file + _(".sprite"));

	if(!p_spr_def.Exists())
	{
		if(project)
		{
			if(!project->checkName(test_id.ToStdString()))
			{
				wxMessageBox(_("Illegal Character in Sprite ID"));
				return;
			}
		}
	}
	else
	{
		test_id = _("");
	}

	for(int i = 0; i < current_sprite_id.size(); i++)
	{
		if(current_sprite_id.Item(i).Upper().Trim().compare(test_id)==0)
		{
			wxMessageBox(_("Sprite ID already exists"));
			return;
		}
	}

	id_name = m_spriteID_textCtrl->GetValue();

	create_flag = true;

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

	wxString ignore_ext = _(".sprite");

	for(int i = 0; i < files.size(); i++)
	{
		if(files.Item(i).length() >= ignore_ext.length())
		{
			if(files.Item(i).substr(files.Item(i).length() - ignore_ext.length()).compare(ignore_ext)==0)
				continue;
		}

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
