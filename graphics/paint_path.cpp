//cpp
#include "wx/wx.h"
#include "wx/graphics.h"

#include <vector>


class MyPanel : public wxPanel {
public:
    std::vector<wxPoint> controlPoints;
    wxPoint currentPoint;
    int currentIndex;
    double t;
    wxTimer* timer;
    wxGraphicsRenderer* renderer;

    MyPanel(wxWindow* parent);
    ~MyPanel();
    void OnTimer(wxTimerEvent& event);
    void DrawPath(wxGraphicsContext* gc);
    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
};

class MyFrame : public wxFrame {
    MyPanel* panel;
    

public:
    MyFrame() : wxFrame(nullptr, wxID_ANY, "Curved Motion") {
        panel = new MyPanel(this);   
    }

    ~MyFrame() {
        
    }

    DECLARE_EVENT_TABLE()
};

class MyApp : public wxApp {
    bool OnInit() override {
        (new MyFrame())->Show();
        return true;
    }
};

MyPanel::MyPanel(wxWindow* parent)
    : wxPanel(parent) {
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    Bind(wxEVT_TIMER, &MyPanel::OnTimer, this);
    Bind(wxEVT_SIZE, &MyPanel::OnSize, this);
    t = 0;
    timer = new wxTimer(this, wxID_ANY);
    timer->Start(100); // 10 FPS
    renderer = wxGraphicsRenderer::GetDirect2DRenderer();
    // 初始化控制点，定义曲线
    controlPoints = {
        wxPoint(50, 50),
        wxPoint(150, 50),
        wxPoint(250, 150),
        wxPoint(150, 250),
        wxPoint(50, 250)
    };
    currentIndex = 0;
    currentPoint = controlPoints[currentIndex];

};

MyPanel::~MyPanel()
{
    if (timer->IsRunning())
    {
        timer->Stop();
    }

}
void MyPanel::OnSize(wxSizeEvent& event)
{
    Refresh();
}
void MyPanel::OnTimer(wxTimerEvent& event) {
	//if (currentIndex < controlPoints.size() - 1) {
	//	currentPoint.x += 1; // 每次移动1个像素
	//	if (currentPoint.x > controlPoints[currentIndex + 1].x) {
	//		currentIndex++;
	//		currentPoint = controlPoints[currentIndex];
	//	}
	//}
    t += 0.01;
    if (t > 1) t = 0;
	Refresh();
}

void MyPanel::OnPaint(wxPaintEvent& event) {
    //wxPaintDC dc(this);
    //dc.SetPen(*wxRED_PEN);
    //for (size_t i = 0; i < controlPoints.size() - 1; i++) {
    //    dc.DrawLine(controlPoints[i], controlPoints[i + 1]);
    //}
    //dc.SetBrush(*wxTRANSPARENT_BRUSH);
    //dc.DrawCircle(currentPoint, 5);

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
            DrawPath(context);
            // 释放资源
            delete context;
        }
        //delete renderer;
    }
}
void MyPanel::DrawPath(wxGraphicsContext* gc)
{
    // 创建路径
    wxGraphicsPath path = gc->CreatePath();

    // 定义一个简单的曲线
    path.MoveToPoint(0, 0);
    path.AddQuadCurveToPoint(1, 1, 1, 0);

    // 参数化路径长度，使用三次贝塞尔曲线进行插值
    double cp1x, cp1y, cp2x, cp2y;
    path.GetControlPoints(t * path.GetPointCount(), &cp1x, &cp1y, &cp2x, &cp2y);
    path.MoveToPoint(0, 0);
    path.AddBezierCurveToPoint(cp1x, cp1y, cp2x, cp2y, t);

    // 使用路径绘图
    gc->SetPen(wxPen(*wxBLUE, 2));
    gc->StrokePath(path);
}
IMPLEMENT_APP(MyApp)
