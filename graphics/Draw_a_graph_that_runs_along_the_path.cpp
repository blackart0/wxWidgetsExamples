//wxGraphicsPath  Draw a graph that runs along the path

#include <wx/graphics.h>
#include <vector>

void DrawGraphOnPath(wxGraphicsContext* gc, wxGraphicsPath& path)
{
    // Calculate points along the path
    std::vector<wxPoint2D> points;
    wxGraphicsMatrix matrix;
    double pos = 0.0;
    double step = 0.01; // adjust this value to control the granularity of the graph
    while (pos < 1.0)
    {
        wxPoint2D point = path.GetPointAtLength(pos);
        points.push_back(point);
        pos += step;
    }

    // Draw graph connecting the points
    gc->SetPen(*wxBLACK_PEN);
    gc->SetBrush(*wxTRANSPARENT_BRUSH);
    for (size_t i = 1; i < points.size(); ++i)
    {
        gc->StrokeLine(points[i - 1], points[i]);
    }
}

void DrawGraph(wxWindow* window)
{
    // Get the device context associated with the window
    wxClientDC dc(window);

    // Create a graphics context from the device context
    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if (gc)
    {
        // Create a graphics path
        wxGraphicsPath path = gc->CreatePath();

        // Define the path (you can define your own path here)
        path.MoveToPoint(100, 100);
        path.AddLineToPoint(200, 200);
        path.AddLineToPoint(300, 100);

        // Draw the path
        gc->SetPen(*wxBLACK_PEN);
        gc->SetBrush(*wxTRANSPARENT_BRUSH);
        gc->StrokePath(path);

        // Draw graph along the path
        DrawGraphOnPath(gc, path);

        // Delete the graphics context when done
        delete gc;
    }
}

// wxGraphicsPath AddCurveToPoint Draw a graph that runs along the path
#include <wx/graphics.h>
#include <vector>

void DrawGraphOnCurve(wxGraphicsContext* gc, const wxPoint2D& start, const wxPoint2D& ctrl1,
                      const wxPoint2D& ctrl2, const wxPoint2D& end)
{
    const double step = 0.01; // adjust this value to control the granularity of the curve
    double t = 0.0;
    
    while (t <= 1.0)
    {
        double x = (1 - t) * (1 - t) * (1 - t) * start.x + 3 * (1 - t) * (1 - t) * t * ctrl1.x +
                   3 * (1 - t) * t * t * ctrl2.x + t * t * t * end.x;
        double y = (1 - t) * (1 - t) * (1 - t) * start.y + 3 * (1 - t) * (1 - t) * t * ctrl1.y +
                   3 * (1 - t) * t * t * ctrl2.y + t * t * t * end.y;
        
        // Draw the graph point at (x, y)
        gc->StrokePoint(wxPoint2D(x, y));

        t += step;
    }
}

void DrawGraph(wxWindow* window)
{
    // Get the device context associated with the window
    wxClientDC dc(window);

    // Create a graphics context from the device context
    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if (gc)
    {
        // Create a graphics path
        wxGraphicsPath path = gc->CreatePath();

        // Define the path (for example, add a curve)
        wxPoint2D start(100, 100);
        wxPoint2D ctrl1(200, 50);
        wxPoint2D ctrl2(250, 150);
        wxPoint2D end(300, 100);
        
        path.MoveToPoint(start);
        path.AddCurveToPoint(ctrl1, ctrl2, end);

        // Draw the path
        gc->SetPen(*wxBLACK_PEN);
        gc->SetBrush(*wxTRANSPARENT_BRUSH);
        gc->StrokePath(path);

        // Draw graph along the curve
        DrawGraphOnCurve(gc, start, ctrl1, ctrl2, end);

        // Delete the graphics context when done
        delete gc;
    }
}

// wxGraphicsPath AddArcToPoint  AddLineToPoint Draw a graph that runs along the path

#include <wx/graphics.h>
#include <vector>

void DrawGraphOnPath(wxGraphicsContext* gc, const wxGraphicsPath& path)
{
    const double step = 0.01; // adjust this value to control the granularity of the path
    double pos = 0.0;
    
    while (pos <= 1.0)
    {
        wxPoint2D point = path.GetPointAtLength(pos);
        
        // Draw the graph point at the current position
        gc->StrokePoint(point);

        pos += step;
    }
}

void DrawGraph(wxWindow* window)
{
    // Get the device context associated with the window
    wxClientDC dc(window);

    // Create a graphics context from the device context
    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if (gc)
    {
        // Create a graphics path
        wxGraphicsPath path = gc->CreatePath();

        // Define the path (for example, add an arc and a line)
        path.MoveToPoint(100, 100);
        path.AddArcToPoint(200, 50, 300, 100, 100);
        path.AddLineToPoint(400, 200);

        // Draw the path
        gc->SetPen(*wxBLACK_PEN);
        gc->SetBrush(*wxTRANSPARENT_BRUSH);
        gc->StrokePath(path);

        // Draw graph along the path
        DrawGraphOnPath(gc, path);

        // Delete the graphics context when done
        delete gc;
    }
}
