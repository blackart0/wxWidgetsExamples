///
// C++ code generated with wxFormBuilder (version 3.10.1-370-gc831f1f7-dirty)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include "bubblespanel.h"
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/clrpicker.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/valtext.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/panel.h>

///

namespace UI
{

    ///
    /// Class MainWin
    ///
    class MainWin : public wxPanel
    {
    private:

    protected:
        wxPanel *ctrlPanel;
        wxStaticText *m_staticText1;
        wxStaticText *m_staticText11;
        wxStaticText *m_staticText8;
        wxStaticText *m_staticText9;
        wxStaticText *m_staticText12;
        wxStaticText *m_staticText13;

    public:
        BubblesPanel *m_bubblesPanel;
        wxColourPickerCtrl *m_clr;
        wxTextCtrl *m_textX;
        wxTextCtrl *m_textY;
        wxTextCtrl *m_textStep;
        wxTextCtrl *m_textDirect;
        wxButton *m_btnAction;
        wxString m_strVtrX;
        wxString m_strVtrY;
        wxString m_strVtrStep;
        wxString m_strVtrDirect;

        MainWin(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxSize(1024, 768), long style = wxTAB_TRAVERSAL, const wxString &name = wxEmptyString);

        ~MainWin();
    };

}  // namespace UI
