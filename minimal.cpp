// Name:        minimal.cpp
// Purpose:     Minimal wxWidgets sample
// Author:      Julian Smart


#include "wx/wx.h"

// 定义应用程序类
class MyApp : public wxApp
{
public:
    // 这个函数将会在程序启动的时候被调用
    virtual bool OnInit();
};

// 定义主窗口类
class MyFrame : public wxFrame
{
public:
    // 主窗口类的构造函数
    MyFrame(const wxString& title);

    // 事件处理函数
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

private:
    // 声明事件表
    DECLARE_EVENT_TABLE()
};

// 有了这一行就可以使用 MyApp& wxGetApp()了
DECLARE_APP(MyApp)

// 告诉wxWidgets主应用程序是哪个类
IMPLEMENT_APP(MyApp)

// 初始化程序
bool MyApp::OnInit()
{
    // 创建主窗口
    MyFrame *frame = new MyFrame(wxT("Minimal wxWidgets App"));

    // 显示主窗口
    frame->Show(true);

    // 开始事件处理循环
    return true;
}

// MyFrame类的事件表
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
    EVT_MENU(wxID_EXIT,  MyFrame::OnQuit)
END_EVENT_TABLE()

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg;
    msg.Printf(wxT("Hello and welcome to %s"),
               wxVERSION_STRING);

    wxMessageBox(msg, wxT("About Minimal"),
                 wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnQuit(wxCommandEvent& event)
{
    // 释放主窗口
    Close();
}

#include "mondrian.xpm"

MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
    // 设置窗口图标
    SetIcon(wxIcon(mondrian_xpm));

    // 创建菜单条
    wxMenu *fileMenu = new wxMenu;

    // 添加“关于”菜单项
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT, wxT("&About...\tF1"),
                     wxT("Show about dialog"));

    fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"),
                     wxT("Quit this program"));

    // 将菜单项添加到菜单条中
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(helpMenu, wxT("&Help"));

    // ...然后将菜单条放置在主窗口上
    SetMenuBar(menuBar);

    // 创建一个状态条来让一切更有趣些。
    CreateStatusBar(2);
    SetStatusText(wxT("Welcome to wxWidgets!"));
}