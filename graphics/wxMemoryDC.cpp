#include "wx/wx.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
#include "wx/dcgraph.h"
#include "wx/overlay.h"

enum
{
    ID_Hello = 1
};

class MyPanel : public wxPanel {
public:
    MyPanel(wxWindow* parent);
    wxGraphicsRenderer* renderer;
    void OnPaint(wxPaintEvent& event);
};

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame
{
public:
    MyFrame();

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Hello World", wxDefaultPosition, wxSize(800, 600))
{
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
        "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    MyPanel* panel = new MyPanel(this);
    panel->SetSize(wxSize(200, 200));
    wxString str;
    if (panel->renderer)
    {
        int major, minor, micro;
        panel->renderer->GetVersion(&major, &minor, &micro);
        str = wxString::Format("Graphics renderer: %s %i.%i.%i",
            panel->renderer->GetName(), major, minor, micro);
        this->SetTitle(str);
    }
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
        "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage(_T("Hello world from wxWidgets! UTF-8 no BOM 不带签名"));
}


MyPanel::MyPanel(wxWindow* parent)
    : wxPanel(parent) {
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    renderer = wxGraphicsRenderer::GetDirect2DRenderer();
};

void MyPanel::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);
    wxGCDC gdc1,gdc2;
    wxGraphicsContext* context1;
    wxPaintDC* paintdc = wxDynamicCast(&dc, wxPaintDC);
    context1 = renderer->CreateContext(*paintdc);        
    context1->SetAntialiasMode(wxANTIALIAS_DEFAULT);

    gdc1.SetBackground(*wxLIGHT_GREY_BRUSH);// GetBackgroundColour());
    gdc1.SetGraphicsContext(context1);
    
    wxDC& dc1 = static_cast<wxDC&>(gdc1);
    PrepareDC(dc1);

        /* 准备wxMemoryDC */
    wxMemoryDC memDC;
    wxGraphicsContext* context2 = renderer->CreateContext(&memDC);
    context2->SetAntialiasMode(wxANTIALIAS_DEFAULT);
    wxRect rect = this->GetRect();
    wxBitmap bitmap(rect.GetSize());
    memDC.SelectObject(bitmap);
    memDC.Clear();

    double r = 5;
    wxCoord x, y, lstX=0, lstY=0;
    memDC.SetPen(wxPen(wxColour(0x3333cc),4));
    for (int a = 0; a <= 720; ++a) {
        double b = a * 3.1415 / 180;
        x = cos(b) * r;
        y = sin(b) * r;
        wxPoint2DDouble lines[] = { wxPoint2DDouble(400 + x, 300 + y), wxPoint2DDouble(400 + 400 + lstX, 300 + lstY) };
        if (a != 0) {
            context2->DrawLines(1, lines, wxODDEVEN_RULE);
        }
        
        r += 0.25;
        lstX = x;
        lstY = y;
    }

    //context2->SetTextForeground(*wxWHITE);
    context2->DrawText(wxT("By Tiger"), 5, 5);


    /* 绘图完毕 */

    /* 复制到wxPaintDC */
    dc1.Blit(wxPoint(0, 0), rect.GetSize(), &memDC, wxPoint(0, 0));
    
}