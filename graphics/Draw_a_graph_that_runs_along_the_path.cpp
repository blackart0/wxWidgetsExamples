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
// 贝塞尔曲线是应用于二维图形应用程序的数学曲线，它由线段与节点组成，节点是可拖动的支点，线段像可伸缩的皮筋13。为了获得贝塞尔曲线上一个点的位置，我们通常需要利用贝塞尔曲线的定义和参数方程。

// 贝塞尔曲线的公式依赖于其阶数，即控制点的数量。例如，一个三阶贝塞尔曲线（也称为立方贝塞尔曲线）有四个控制点，并使用参数t（通常取值范围从0到1）来计算曲线上的点。以下是一个三阶贝塞尔曲线的公式示例：

// B(t) = (1-t)^3 * P0 + 3*(1-t)^2 * t * P1 + 3*(1-t) * t^2 * P2 + t^3 * P3

// 其中，P0, P1, P2, 和 P3 是控制点，t 是参数（0 ≤ t ≤ 1）。当t从0变化到1时，B(t)描述了从起点P0到终点P3的曲线上的点。

// 对于二阶贝塞尔曲线（有三个控制点）和一阶贝塞尔曲线（即线性插值，有两个控制点），也有类似的公式。对于n阶贝塞尔曲线，会有n+1个控制点，并使用相应的公式来计算曲线上的点。

// 在实际应用中，如果你想计算曲线上特定位置的点（比如t=0.5时的点，即曲线中点），你可以将t值代入上述公式中，然后计算得到的结果就是该点在二维空间中的坐标。

// 注意，计算贝塞尔曲线上点的位置通常是在图形软件或计算机图形库中完成的，这些软件或库提供了现成的函数或方法来进行这样的计算。如果你是编程人员，并且正在使用某个特定的图形库，那么你应该查阅该库的文档，以了解如何正确地使用它来计算贝塞尔曲线上的点。

// 此外，值得注意的是，贝塞尔曲线的计算可能会涉及到复杂的数学运算和数值稳定性问题，特别是在高阶贝塞尔曲线的情况下。因此，在实际应用中，通常会使用现成的图形库或工具来处理这些计算，以确保准确性和效率。
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
