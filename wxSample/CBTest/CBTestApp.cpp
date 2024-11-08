/***************************************************************
 * Name:      CBTestApp.cpp
 * Purpose:   Code for Application Class
 * Author:    xcz (xcz@xcz.com)
 * Created:   2024-05-22
 * Copyright: xcz ()
 * License:
 **************************************************************/

#include "CBTestApp.h"

//(*AppHeaders
#include "CBTestMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(CBTestApp);

bool CBTestApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	CBTestFrame* Frame = new CBTestFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
