#include "NirvanaEditor_SetSpriteSheet_Dialog.h"

NirvanaEditor_SetSpriteSheet_Dialog::NirvanaEditor_SetSpriteSheet_Dialog( wxWindow* parent )
:
SetSpriteSheet_Dialog( parent )
{
	create_flag = false;
}

void NirvanaEditor_SetSpriteSheet_Dialog::OnSearch( wxCommandEvent& event )
{
	refresh_list();
}

void NirvanaEditor_SetSpriteSheet_Dialog::OnCancel( wxCommandEvent& event )
{
	Close();
}

void NirvanaEditor_SetSpriteSheet_Dialog::OnCreate( wxCommandEvent& event )
{
	if(m_spriteSheet_listBox->GetSelection() >= 0 && m_spriteSheet_listBox->GetSelection() < m_spriteSheet_listBox->GetCount())
		selected_file = m_spriteSheet_listBox->GetString( m_spriteSheet_listBox->GetSelection() );
	else
		selected_file = _("");

	if(selected_file.compare(_(""))==0)
	{
		wxMessageBox(_("Must select image for sprite"));
		return;
	}

	wxFileName p_spr(project->getDir());
	p_spr.AppendDir(project->sprite_path);
	p_spr.SetFullName(selected_file);

	if(!p_spr.Exists())
	{
		wxMessageBox(_("Error loading sprite sheet"));
		Close();
	}


	create_flag = true;

	Close();
}

void NirvanaEditor_SetSpriteSheet_Dialog::refresh_list()
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
