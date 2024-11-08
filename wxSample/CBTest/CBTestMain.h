/***************************************************************
 * Name:      CBTestMain.h
 * Purpose:   Defines Application Frame
 * Author:    xcz (xcz@xcz.com)
 * Created:   2024-05-22
 * Copyright: xcz ()
 * License:
 **************************************************************/

#ifndef CBTESTMAIN_H
#define CBTESTMAIN_H

//(*Headers(CBTestFrame)
#include <wx/frame.h>
#include <wx/grid.h>
#include <wx/menu.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
//*)

class CBTestFrame: public wxFrame
{
    public:

        CBTestFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~CBTestFrame();

    private:

        //(*Handlers(CBTestFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(CBTestFrame)
        static const long ID_GRID1;
        static const long ID_TEXTCTRL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(CBTestFrame)
        wxGrid* Grid1;
        wxStatusBar* StatusBar1;
        wxTextCtrl* TextCtrl1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // CBTESTMAIN_H
