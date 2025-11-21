#include "NirvanaEditor_SpriteLayer_ChangeTilesetWarning_Dialog.h"

NirvanaEditor_SpriteLayer_ChangeTilesetWarning_Dialog::NirvanaEditor_SpriteLayer_ChangeTilesetWarning_Dialog( wxWindow* parent )
:
SpriteLayer_ChangeTilesetWarning_Dialog( parent )
{
    continue_flag = false;
}

void NirvanaEditor_SpriteLayer_ChangeTilesetWarning_Dialog::OnContinue( wxCommandEvent& event )
{
    continue_flag = true;
    Close();
}

void NirvanaEditor_SpriteLayer_ChangeTilesetWarning_Dialog::OnCancel( wxCommandEvent& event )
{
    continue_flag = false;
    Close();
}
