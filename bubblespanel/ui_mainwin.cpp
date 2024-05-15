///
// C++ code generated with wxFormBuilder (version 3.10.1-370-gc831f1f7-dirty)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///

#include "ui_mainwin.h"

///
using namespace UI;

MainWin::MainWin(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name) :
    wxPanel(parent, id, pos, size, style, name)
{
    wxBoxSizer *bSizer1;
    bSizer1 = new wxBoxSizer(wxVERTICAL);

    m_bubblesPanel = new BubblesPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME);
    bSizer1->Add(m_bubblesPanel, 1, wxALL | wxEXPAND, 5);

    ctrlPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    wxBoxSizer *bSizer3;
    bSizer3 = new wxBoxSizer(wxHORIZONTAL);

    bSizer3->SetMinSize(wxSize(-1, 150));
    wxBoxSizer *bSizer7;
    bSizer7 = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *bSizer31;
    bSizer31 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText1 = new wxStaticText(ctrlPanel, wxID_ANY, wxT("颜色"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
    m_staticText1->Wrap(-1);
    m_staticText1->SetMinSize(wxSize(120, -1));

    bSizer31->Add(m_staticText1, 0, wxALL, 5);

    m_clr = new wxColourPickerCtrl(ctrlPanel, wxID_ANY, wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW), wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE);
    bSizer31->Add(m_clr, 0, wxALL, 5);


    bSizer7->Add(bSizer31, 0, wxBOTTOM | wxEXPAND, 5);

    wxBoxSizer *bSizer311;
    bSizer311 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText11 = new wxStaticText(ctrlPanel, wxID_ANY, wxT("位置"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
    m_staticText11->Wrap(-1);
    m_staticText11->SetMinSize(wxSize(120, -1));

    bSizer311->Add(m_staticText11, 0, wxALL, 5);

    m_staticText8 = new wxStaticText(ctrlPanel, wxID_ANY, wxT("X"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText8->Wrap(-1);
    bSizer311->Add(m_staticText8, 0, wxALL, 5);

    m_textX = new wxTextCtrl(ctrlPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    m_textX->SetValidator(wxTextValidator(wxFILTER_NUMERIC, &m_strVtrX));

    bSizer311->Add(m_textX, 0, wxEXPAND, 5);


    bSizer311->Add(20, 0, 0, wxEXPAND, 5);

    m_staticText9 = new wxStaticText(ctrlPanel, wxID_ANY, wxT("Y"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText9->Wrap(-1);
    bSizer311->Add(m_staticText9, 0, wxALL, 5);

    m_textY = new wxTextCtrl(ctrlPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    bSizer311->Add(m_textY, 0, wxEXPAND, 5);


    bSizer311->Add(0, 0, 3, wxEXPAND, 5);


    bSizer7->Add(bSizer311, 0, wxBOTTOM | wxEXPAND, 5);

    wxBoxSizer *bSizer312;
    bSizer312 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText12 = new wxStaticText(ctrlPanel, wxID_ANY, wxT("步长"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
    m_staticText12->Wrap(-1);
    m_staticText12->SetMinSize(wxSize(120, -1));

    bSizer312->Add(m_staticText12, 0, wxALL, 5);

    m_textStep = new wxTextCtrl(ctrlPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    m_textStep->SetValidator(wxTextValidator(wxFILTER_NUMERIC, &m_strVtrStep));

    bSizer312->Add(m_textStep, 0, wxEXPAND, 5);


    bSizer7->Add(bSizer312, 0, wxBOTTOM | wxEXPAND, 5);

    wxBoxSizer *bSizer313;
    bSizer313 = new wxBoxSizer(wxHORIZONTAL);

    m_staticText13 = new wxStaticText(ctrlPanel, wxID_ANY, wxT("方向"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
    m_staticText13->Wrap(-1);
    m_staticText13->SetMinSize(wxSize(120, -1));

    bSizer313->Add(m_staticText13, 0, wxALL, 5);

    m_textDirect = new wxTextCtrl(ctrlPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    m_textDirect->SetValidator(wxTextValidator(wxFILTER_NUMERIC, &m_strVtrDirect));

    bSizer313->Add(m_textDirect, 0, wxEXPAND, 5);


    bSizer7->Add(bSizer313, 0, wxBOTTOM | wxEXPAND, 5);


    bSizer3->Add(bSizer7, 1, wxEXPAND, 5);

    m_btnAction = new wxButton(ctrlPanel, wxID_ANY, wxT("开始"), wxDefaultPosition, wxDefaultSize, 0);
    m_btnAction->SetMinSize(wxSize(-1, 50));

    bSizer3->Add(m_btnAction, 1, wxALIGN_CENTER | wxALL, 5);


    ctrlPanel->SetSizer(bSizer3);
    ctrlPanel->Layout();
    bSizer3->Fit(ctrlPanel);
    bSizer1->Add(ctrlPanel, 0, wxEXPAND | wxALL, 5);


    this->SetSizer(bSizer1);
    this->Layout();
}

MainWin::~MainWin()
{
}
