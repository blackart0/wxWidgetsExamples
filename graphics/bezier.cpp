// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

class myFrame : public wxFrame
{
    public:
        myFrame( wxWindow* parent, int id = wxID_ANY, wxString title = "Demo"
                , wxPoint pos = wxDefaultPosition, wxSize size = wxDefaultSize
                , int style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
    private:
        void OnLeftDown( wxMouseEvent& event );
        void OnLeftUp( wxMouseEvent& event );
        void OnMotion( wxMouseEvent& event );
        void OnPaint( wxPaintEvent& event );

        std::vector<wxPoint> m_points;
        std::vector<wxPoint>::iterator m_selection;
        wxPanel* m_panel;
};


myFrame::myFrame( wxWindow* parent, int id, wxString title, wxPoint pos
                 , wxSize size, int style )
        :wxFrame( parent, id, title, pos, size, style )
{
    m_selection=m_points.end();
    m_panel = new wxPanel(this);

    m_panel->Bind( wxEVT_LEFT_DOWN, &myFrame::OnLeftDown, this );
    m_panel->Bind( wxEVT_LEFT_UP, &myFrame::OnLeftUp, this );
    m_panel->Bind( wxEVT_MOTION, &myFrame::OnMotion, this );
    m_panel->Bind( wxEVT_PAINT, &myFrame::OnPaint, this );
}

void myFrame::OnLeftDown( wxMouseEvent& event )
{
    wxPoint p = event.GetPosition();

    for (std::vector<wxPoint>::iterator it=m_points.begin();it!=m_points.end();++it)
    {
        if ( std::abs(it->x-p.x) + std::abs(it->y-p.y) < 6 )
        {
            m_selection=it;
            m_selection->x=p.x;
            m_selection->y=p.y;
        }
    }

    if (m_selection==m_points.end())
    {
        m_points.push_back(p);
        m_selection = m_points.end();
        --m_selection;
    }
    m_panel->Refresh();
}

void myFrame::OnLeftUp( wxMouseEvent& event )
{
    m_selection=m_points.end();
    m_panel->Refresh();
}

void myFrame::OnMotion( wxMouseEvent& event )
{
    if (event.LeftIsDown() && m_selection!=m_points.end())
    {
        wxPoint p = event.GetPosition();
        m_selection->x=p.x;
        m_selection->y=p.y;
        m_panel->Refresh();
    }
}

void myFrame::OnPaint( wxPaintEvent& event )
{
    wxPaintDC dc(m_panel);
    dc.Clear();

    dc.SetPen(wxPen(wxColour(0, 0, 128), 2));
    dc.SetBrush(*wxWHITE_BRUSH);

    if (m_points.size()>2)
    {
        dc.DrawSpline(m_points.size(),&(m_points[0]));
    }

    for (std::vector<wxPoint>::iterator it=m_points.begin();it!=m_points.end();++it)
    {
        dc.DrawCircle(*it, 4);
    }

    if ( m_selection!=m_points.end() )
    {
        dc.SetPen(*wxRED_PEN);
        dc.SetBrush(*wxRED_BRUSH);
        dc.DrawCircle(*m_selection, 4);
    }
}

class myApp : public wxApp
{
    public:
        virtual bool OnInit()
        {
            myFrame* frame = new myFrame(NULL);
            frame->Show();
            return true;
        }
};

wxIMPLEMENT_APP(myApp);