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
	wxString test_id = m_spriteID_textCtrl->GetValue().Upper().Trim();
	if(project)
	{
		if(!project->checkName(test_id.ToStdString()))
		{
			wxMessageBox(_("Illegal Character in Sprite ID"));
			return;
		}


		if(stage_index >= 0 && stage_index < project->stages.size())
		{
			if(layer_index >= 0 && layer_index < project->stages[stage_index].layers.size())
			{
				for(int i = 0; i < project->getStageLayerNumSprites(stage_index, layer_index); i++)
				{
					if(wxString(project->stages[stage_index].layers[layer_index].layer_sprites[i].sprite_name).Upper().Trim().compare(test_id)==0)
					{
						wxMessageBox(_("Sprite ID already exists in current layer"));
						return;
					}
				}
			}
		}
	}

	create_flag = true;
	id_name = m_spriteID_textCtrl->GetValue().Trim();

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
