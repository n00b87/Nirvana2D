#include "NirvanaEditor_NewStage_Dialog.h"

NirvanaEditor_NewStage_Dialog::NirvanaEditor_NewStage_Dialog( wxWindow* parent )
:
NewStage_Dialog( parent )
{
	create_flag = false;
}

void NirvanaEditor_NewStage_Dialog::OnCreate( wxCommandEvent& event )
{
	wxString test_id = m_stageID_textCtrl->GetValue().Upper().Trim();
	if(project)
	{
		if(!project->checkName(test_id.ToStdString()))
		{
			wxMessageBox(_("Illegal Character in Stage Name"));
			return;
		}

		for(int i = 0; i < project->getStageCount(); i++)
		{
			if(wxString(project->getStageName(i)).Upper().Trim().compare(test_id)==0)
			{
				wxMessageBox(_("Stage Name already exists in current project"));
				return;
			}
		}
	}

	create_flag = true;
	stage_name = m_stageID_textCtrl->GetValue().Trim();
	tile_width = m_tileWidth_spinCtrl->GetValue();
	tile_height = m_tileHeight_spinCtrl->GetValue();
	width_in_tiles = m_width_spinCtrl->GetValue();
	height_in_tiles = m_height_spinCtrl->GetValue();
	Close();
}

void NirvanaEditor_NewStage_Dialog::OnCancel( wxCommandEvent& event )
{
	Close();
}
