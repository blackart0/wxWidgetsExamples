// wxBufferedDC  Flicker-Free Drawing EVT_ERASE_BACKGROUND 
#include <wx/wx.h>

class MyCanvas : public wxPanel
{
public:
    MyCanvas(wxFrame* parent)
        : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
    {
        Bind(wxEVT_PAINT, &MyCanvas::OnPaint, this);
        Bind(wxEVT_ERASE_BACKGROUND, &MyCanvas::OnEraseBackground, this);
    }

    void OnPaint(wxPaintEvent& event)
    {
        wxBufferedPaintDC dc(this); // Use wxBufferedPaintDC for flicker-free drawing

        // Draw whatever you want here
        wxPen pen(*wxBLACK, 2);
        dc.SetPen(pen);
        dc.DrawLine(0, 0, 100, 100);
    }

    void OnEraseBackground(wxEraseEvent& event)
    {
        // Prevent background erasing to avoid flickering
        //event.Skip();
    }
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title)
        : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300))
    {
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        m_canvas = new MyCanvas(this);
        sizer->Add(m_canvas, 1, wxEXPAND);
        SetSizer(sizer);
    }

private:
    MyCanvas* m_canvas;
};

class MyApp : public wxApp
{
public:
    virtual bool OnInit() override
    {
        MyFrame* frame = new MyFrame("Flicker-Free Drawing");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);

// wxBufferedDC  Flicker-Free Drawing EVT_ERASE_BACKGROUND  wxGraphicsRenderer::GetDirect2DRenderer
#include <wx/wx.h>
#include <wx/dcbuffer.h>

class MyCanvas : public wxPanel
{
public:
    MyCanvas(wxFrame* parent)
        : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
    {
        Bind(wxEVT_PAINT, &MyCanvas::OnPaint, this);
        Bind(wxEVT_ERASE_BACKGROUND, &MyCanvas::OnEraseBackground, this);
    }

    void OnPaint(wxPaintEvent& event)
    {
        wxBufferedPaintDC dc(this); // Use wxBufferedPaintDC for flicker-free drawing

        // Draw whatever you want here
        wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
        if (gc)
        {
            // Use Direct2D renderer if available
            wxGraphicsRenderer* renderer = wxGraphicsRenderer::GetDirect2DRenderer();
            if (renderer)
                gc->SetRenderingHint(wxGraphicsContext::RENDERING_CONTEXT, renderer);

            // Draw example content
            wxPen pen(*wxBLACK, 2);
            gc->SetPen(pen);
            gc->DrawLine(0, 0, 100, 100);

            delete gc;
        }
    }

    void OnEraseBackground(wxEraseEvent& event)
    {
        // Prevent background erasing to avoid flickering
        //event.Skip();
    }
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title)
        : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300))
    {
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        m_canvas = new MyCanvas(this);
        sizer->Add(m_canvas, 1, wxEXPAND);
        SetSizer(sizer);
    }

private:
    MyCanvas* m_canvas;
};

class MyApp : public wxApp
{
public:
    virtual bool OnInit() override
    {
        MyFrame* frame = new MyFrame("Flicker-Free Drawing with Direct2D Rendering");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);

//----
#include <wx/wx.h>
#include <wx/graphics.h>

class MyCanvas : public wxWindow {
public:
    MyCanvas(wxWindow* parent) : wxWindow(parent, wxID_ANY) {
        Bind(wxEVT_PAINT, &MyCanvas::OnPaint, this);
        Bind(wxEVT_ERASE_BACKGROUND, &MyCanvas::OnEraseBackground, this);
    }

private:
    void OnPaint(wxPaintEvent& event) {
        wxBufferedPaintDC dc(this); // Use buffered paint DC for flicker-free drawing

        // Retrieve Direct2D renderer
        wxGraphicsRenderer* renderer = wxGraphicsRenderer::GetDirect2DRenderer();
        if (renderer) {
            // Use Direct2D rendering for optimal performance
            wxGraphicsContext* gc = renderer->CreateContext(dc);
            if (gc) {
                // Draw your content using Direct2D
                gc->SetBrush(*wxWHITE_BRUSH);
                gc->SetPen(*wxBLACK_PEN);
                gc->DrawRectangle(0, 0, GetSize().GetWidth(), GetSize().GetHeight());
                // Draw other elements...
                delete gc;
            }
        }
    }

    void OnEraseBackground(wxEraseEvent& event) {
        // Do nothing to prevent flicker
    }

    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyCanvas, wxWindow)
    EVT_PAINT(MyCanvas::OnPaint)
    EVT_ERASE_BACKGROUND(MyCanvas::OnEraseBackground)
wxEND_EVENT_TABLE()

class MyFrame : public wxFrame {
public:
    MyFrame() : wxFrame(nullptr, wxID_ANY, "Flicker-Free Drawing Example", wxDefaultPosition, wxSize(400, 300)) {
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
