#include <wx/wx.h>

class MyFrame : public wxFrame
{
public:
    MyFrame()
        : wxFrame(NULL, wxID_ANY, wxT("Circle Segment"), wxDefaultPosition, wxSize(640, 480))
    {
        Connect(wxEVT_PAINT, wxPaintEventHandler(MyFrame::OnPaint));
    }

private:
    void OnPaint(wxPaintEvent& event)
    {
        wxPaintDC pdc(this);

        // set the pen color and width
        wxPen pen(wxColor(255, 0, 0), 50);
        pen.SetCap(wxCAP_BUTT);
        pdc.SetPen(pen);

        wxPoint center;
        center.x = GetClientSize().GetWidth() / 2;
        center.y = GetClientSize().GetHeight() / 2;

        double r1 = 100;

        // define the start and end angles of the circle segment
        const double startAngle = M_PI / 3.0;
        const double endAngle = 2.0 * M_PI / 3.0;

        wxPoint pt1, pt2;
        pt1.x = static_cast<int>(center.x + r1 * cos(startAngle));
        pt1.y = static_cast<int>(center.y - r1 * sin(startAngle));
        pt2.x = static_cast<int>(center.x + r1 * cos(endAngle));
        pt2.y = static_cast<int>(center.y - r1 * sin(endAngle));

        // draw the circle segment
        pdc.DrawArc(pt1, pt2, center);
    }
};

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        MyFrame* frame = new MyFrame();
        frame->Show();
        return true;
    }
};

IMPLEMENT_APP(MyApp);