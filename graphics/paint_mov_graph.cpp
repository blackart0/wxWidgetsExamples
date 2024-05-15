#include "wx/wx.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
#include "wx/colordlg.h"
#include "wx/image.h"
#include "wx/artprov.h"
#include "wx/dcgraph.h"
#include "wx/overlay.h"
#include "wx/filename.h"
#include "wx/metafile.h"
#include "wx/settings.h"

class MyPanel : public wxPanel {
public:
    MyPanel(wxFrame* parent)  : wxPanel(parent) {
        Connect(wxEVT_TIMER, wxTimerEventHandler(MyPanel::OnTimer));
        Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
        timer = new wxTimer(this, wxID_ANY);
        timer->Start(10); // 每100毫秒触发一次
        posX = 0;
        posY = 0;
    }

    ~MyPanel()
    {
        if (timer->IsRunning())
            timer->Stop();
    }

    void OnPaint(wxPaintEvent& event) {
        wxPaintDC dc(this);
        Draw(dc);
    }

    void OnTimer(wxTimerEvent& event) {
        if (posX < 800 && posY < 500)
        {
            // 更新位置
            posX += 1;
            posY += 1;
        }
        else
        {
            posX = 0;
            posY = 0;
        }
        // 重绘
        Refresh();
    }

    void Draw(wxDC& dc) {
        // 设置矩形颜色
        wxBrush brush(wxColor(255, 0, 0));
        dc.SetBrush(brush);

        // 绘制矩形
        dc.DrawRectangle(posX, posY, 50, 25);
    }

private:
    wxTimer* timer;
    int posX, posY;
};

class MyFrame : public wxFrame {
public:
    MyFrame() : wxFrame(nullptr, wxID_ANY, "wxWidgets Motion Graphics", wxDefaultPosition, wxSize(800, 600)) {
        MyPanel* panel = new MyPanel(this);
    }
};

class MyApp : public wxApp {
public:
    bool OnInit() override {
        MyFrame* frame = new MyFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);