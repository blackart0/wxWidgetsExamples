
//----
#include <vector>
#include "wx/wx.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
#include "wx/dcgraph.h"

class MyCanvas : public wxWindow {
public:
    wxTimer* m_timer;
    const double step = 0.01; // adjust this value to control the granularity of the path
    double pos;
    MyCanvas(wxWindow* parent) : wxWindow(parent, wxID_ANY) {
        Bind(wxEVT_PAINT, &MyCanvas::OnPaint, this);
        Bind(wxEVT_ERASE_BACKGROUND, &MyCanvas::OnEraseBackground, this);
        m_timer = new wxTimer(this, wxID_ANY); // 创建定时器	
        Bind(wxEVT_TIMER, &MyCanvas::OnTimer, this); // 绑定定时器事件处理器
        pos = 0.0;
    }
    ~MyCanvas()
    {
        if (m_timer->IsRunning())
            m_timer->Stop();
        delete m_timer;
    }
private:
    
    void DrawGraphOnPath(wxGraphicsContext* gc, const wxGraphicsPath& path)
    {
        //const double step = 0.01; // adjust this value to control the granularity of the path
        pos = 0.0;

        while (pos <= 1.0)
        {
            //wxPoint2DDouble point = path.GetPointAtLength(pos);

            // Draw the graph point at the current position
            //gc->StrokePoint(point);

            pos += step;
        }
    }

    void OnTimer(wxTimerEvent& event)
    {

    }

    void OnPaint(wxPaintEvent& event) {
        wxBufferedPaintDC dc(this); // Use buffered paint DC for flicker-free drawing

        // Retrieve Direct2D renderer
        wxGraphicsRenderer* renderer = wxGraphicsRenderer::GetDirect2DRenderer();
        if (renderer) {
            // Use Direct2D rendering for optimal performance
            wxGraphicsContext* gc = renderer->CreateContext(dc);
            if (gc) {
                gc->SetAntialiasMode(wxANTIALIAS_DEFAULT);
                // Draw your content using Direct2D
                gc->SetBrush(*wxRED_BRUSH);
                gc->SetPen(*wxWHITE_PEN);
                //gc->DrawRectangle(0, 0, GetSize().GetWidth(), GetSize().GetHeight());
                // Draw other elements...
                wxGraphicsPath path = gc->CreatePath();

                // Define the path (for example, add an arc and a line)
                path.MoveToPoint(100, 100);
                path.AddArcToPoint(200, 50, 300, 100, 100);
                path.AddLineToPoint(400, 200);

                // Draw the path
                gc->SetPen(*wxBLUE_PEN);
                gc->SetBrush(*wxTRANSPARENT_BRUSH);
                gc->StrokePath(path);

                // Draw graph along the path
                //DrawGraphOnPath(gc, path);
                //gc->Flush();

                delete gc;
            }
        }
    }

    void OnEraseBackground(wxEraseEvent& event) {
        // Do nothing to prevent flicker
    }
};

class MyFrame : public wxFrame {
public:
    MyFrame() : wxFrame(nullptr, wxID_ANY, "Flicker-Free Drawing Example", wxDefaultPosition, wxSize(800, 600)) {
        new MyCanvas(this);
    }
};

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        MyFrame* frame = new MyFrame();
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
