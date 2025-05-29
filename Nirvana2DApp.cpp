/***************************************************************
 * Name:      Nirvana2DApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2025-04-01
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#include "Nirvana2DApp.h"
#include "NirvanaEditor_MainFrame.h"

IMPLEMENT_APP(Nirvana2DApp);

bool Nirvana2DApp::OnInit()
{
	wxInitAllImageHandlers();
    NirvanaEditor_MainFrame* frame = new NirvanaEditor_MainFrame(0);

    #ifdef _WIN32
    frame->SetIcon(wxICON(aaaa));
    #endif // _WIN32

    frame->Show();
    return true;
}
