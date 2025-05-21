#include "NirvanaEditor_NewProject_Dialog.h"
#include <wx/wx.h>

NirvanaEditor_NewProject_Dialog::NirvanaEditor_NewProject_Dialog( wxWindow* parent )
:
NewProject_Dialog( parent )
{
	m_projectName_textCtrl->SetValue(_("UNTITLED"));
	create_flag = false;
}

void NirvanaEditor_NewProject_Dialog::OnCreate( wxCommandEvent& event )
{
	if(m_projectName_textCtrl->GetValue().Trim().compare(_(""))==0)
	{
		wxMessageBox(_("Project name is missing"));
		return;
	}
	project_path = m_projectLocation_dirPicker->GetDirName();
	project_name = m_projectName_textCtrl->GetValue().Trim();
	create_flag = true;
	Close();
}

void NirvanaEditor_NewProject_Dialog::OnCancel( wxCommandEvent& event )
{
	Close();
}
