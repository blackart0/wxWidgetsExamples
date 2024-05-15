#include "wx/wx.h"
#include <wx/graphics.h>


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
    : wxFrame(nullptr, wxID_ANY, "Hello World",wxDefaultPosition,wxSize(800,600))
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
    wxLogMessage("Hello world from wxWidgets!");
}

MyPanel::MyPanel(wxWindow* parent)
    : wxPanel(parent) {
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    renderer = wxGraphicsRenderer::GetDirect2DRenderer();
};

void MyPanel::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);
    if (renderer) {
        wxGraphicsContext* context = renderer->CreateContext(dc);
        if (context) {
            // 绘制一个简单的矩形
            wxColour color1(255, 0, 0, 128); // 最后一个参数是 alpha 值（128 表示半透明）
            wxColour color2(0, 255, 0, 128); // 最后一个参数是 alpha 值（128 表示半透明）
            context->SetPen(wxPen(color1, 2));
            context->SetBrush(wxBrush(color2));
            context->DrawRectangle(10, 10, 100, 100);
            context->SetPen(wxPen(color2, 2));
            context->SetBrush(wxBrush(color1));
            context->DrawRectangle(50, 50, 100, 100);
            // 释放资源
            delete context;
        }
        //delete renderer;
    }
}