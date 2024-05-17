
#include <wx/wx.h>
#include <wx/dcbuffer.h>

class MyFrame : public wxFrame
{
public:
    MyFrame() : wxFrame(nullptr, wxID_ANY, wxT("Pie Chart"), wxDefaultPosition, wxSize(400, 400))
    {
        SetBackgroundColour(wxColour(255, 255, 255));
        Bind(wxEVT_PAINT, &MyFrame::OnPaint, this);
    }

private:
    void OnPaint(wxPaintEvent& event)
    {
        wxBufferedPaintDC dc(this);
        dc.SetBackground(wxBrush(wxColour(255, 255, 255)));
        dc.Clear();

        int data[] = { 20, 30, 50 }; // sample data
        int colors[][3] = { {255, 0, 0}, {0, 255, 0}, {0, 0, 255} }; // red, green, blue
        int total = 0;
        for (int i = 0; i < 3; i++)
            total += data[i];

        wxRect rect(50, 50, 300, 300);
        int startAngle = 0;
        for (int i = 0; i < 3; i++)
        {
            int angle = (int)(data[i] * 360.0 / total + 0.5);
            dc.SetBrush(wxBrush(wxColour(colors[i][0], colors[i][1], colors[i][2])));
            dc.SetPen(wxPen(wxColour(colors[i][0], colors[i][1], colors[i][2]), 1));
            dc.DrawEllipticArc(wxPoint(50,50),wxSize(300,300), startAngle, startAngle + angle);
            startAngle += angle;
        }
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

wxIMPLEMENT_APP(MyApp);

//---------------------------------------------------------------------------------------------------------------------
        wxPaintDC dc(this);
        wxGraphicsContext *gc = wxGraphicsContext::Create( dc );

        gc->SetPen(*wxBLACK_PEN);
        gc->SetBrush(*wxRED_BRUSH);
        wxGraphicsPath p = gc->CreatePath();
        p.AddCircle(100, 100, 100);
        p.AddCircle(100, 100,  50);
        //gc->StrokePath(p);    // this would just draw two circles
        gc->FillPath(p);
        
        
//---------------------------------------------------------------------------------------------------------------------
        wxPaintDC dc(this)
wxGraphicsContext *gc = wxGraphicsContext::Create( dc );

gc->SetPen(*wxBLACK_PEN);
gc->SetBrush(*wxRED_BRUSH);
wxGraphicsPath p = gc->CreatePath();
p.AddCircle(100, 100, 100);
p.AddCircle(100, 100,  50);
//gc->StrokePath(p);    // this would just draw two circles
gc->FillPath(p);

delete gc;
//---------------------------------------------------------------------------------------------------------------------
#include <wx/wx.h>
#include <wx/graphics.h>
#include <math.h>

class MyFrame : public wxFrame
{
public:
    MyFrame()
        : wxFrame(NULL, wxID_ANY, wxT("Annular Sector"), wxDefaultPosition, wxSize(640, 480))
    {
        Connect(wxEVT_PAINT, wxPaintEventHandler(MyFrame::OnPaint));
    }

private:
    void OnPaint(wxPaintEvent& event)
    {
        wxPaintDC pdc(this);
        wxGraphicsContext* gc = wxGraphicsContext::Create(pdc);

        if (gc)
        {
            gc->SetPen(wxPen(wxColor(255, 0, 0), 2));       // set the pen color and width
            gc->SetBrush(wxBrush(wxColor(255, 255, 0)));   // set the brush color

            // define the outer and inner radii of the annular sector
            const double r1 = 100.0;
            const double r2 = 60.0;

            // define the start and end angles of the annular sector, in radians
            const double startAngle = M_PI / 3.0;
            const double endAngle = 2.0 * M_PI / 3.0;

            wxPoint center;
            center.x = GetClientSize().GetWidth() / 2;
            center.y = GetClientSize().GetHeight() / 2;

            // calculate the coordinate of each endpoint of the annular sector
            wxPoint pt1, pt2, pt3, pt4;
            pt1.x = static_cast<int>(center.x + r1 * cos(startAngle));
            pt1.y = static_cast<int>(center.y - r1 * sin(startAngle));
            pt2.x = static_cast<int>(center.x + r1 * cos(endAngle));
            pt2.y = static_cast<int>(center.y - r1 * sin(endAngle));
            pt3.x = static_cast<int>(center.x + r2 * cos(endAngle));
            pt3.y = static_cast<int>(center.y - r2 * sin(endAngle));
            pt4.x = static_cast<int>(center.x + r2 * cos(startAngle));
            pt4.y = static_cast<int>(center.y - r2 * sin(startAngle));

            // create a graphics path object from the coordinate of each endpoint and draw it
            wxGraphicsPath path = gc->CreatePath();
            path.MoveToPoint(pt1.x, pt1.y);

            //path.AddLineToPoint(pt2.x, pt2.y);
            //path.AddLineToPoint(pt3.x, pt3.y);
            //path.AddLineToPoint(pt4.x, pt4.y);
            //path.AddLineToPoint(pt1.x, pt1.y);

            path.AddArc(center.x, center.y, static_cast<float>(r1), 2*M_PI - static_cast<float>(startAngle), 2*M_PI - static_cast<float>(endAngle), false);
            path.AddLineToPoint(pt3.x, pt3.y);
            path.AddArc(center.x, center.y, static_cast<float>(r2), 2*M_PI - static_cast<float>(endAngle), 2*M_PI - static_cast<float>(startAngle), true);
            path.AddLineToPoint(pt1.x, pt1.y);


            path.CloseSubpath();
            gc->FillPath(path);

            delete gc;
        }
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