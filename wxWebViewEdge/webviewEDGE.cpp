#include <wx/wx.h>
#include <wx/webview.h>

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1200, 900))
    {
        wxWebView* webView = wxWebView::New(this, wxID_ANY);
        //webView->SetPage(htmlContent, "");
        //wxString htmlContent = "<html><body><h1>Hello, World!</h1></body></html>";
        //wxMessageBox(webView->GetBackendVersionInfo().ToString(), "test");
        this->SetTitle(_T("wxWebView backend use: ")+ webView->GetBackendVersionInfo().ToString());
        webView->LoadURL(_T("file://F:/workspace/wxWidgetsExamples/x64/Debug/watermark.html"));

        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
        sizer->Add(webView, 1, wxEXPAND);
        SetSizer(sizer);
    }
};

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        MyFrame* frame = new MyFrame("Test wxWebView");
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);