#include "wx/wx.h"
#include <iostream>

class ScrolledImageComponent : public wxScrolledWindow
{
    wxBitmap* bitmap;
    int w,h;
    ScrolledImageComponent* m_peer;
        
public:
    ScrolledImageComponent(wxWindow* parent, wxWindowID id, wxString image_path) : wxScrolledWindow(parent, id)
    {
        m_peer = NULL;
        
        wxImage image(image_path);
        if(!image.IsOk())
        {
            wxMessageBox(wxT("there was an error loading the image"));
            return;
        }
        
        w = image.GetWidth();
        h = image.GetHeight();
        
        /* init scrolled area size, scrolling speed, etc. */
        SetScrollbars(1,1, w, h, 0, 0);
        
        bitmap = new wxBitmap( image );
        
        Connect(wxID_ANY, wxEVT_SCROLLWIN_THUMBTRACK, wxScrollWinEventHandler(ScrolledImageComponent::onScroll), NULL, this);
        Connect(wxID_ANY, wxEVT_SCROLLWIN_THUMBRELEASE, wxScrollWinEventHandler(ScrolledImageComponent::onScroll), NULL, this);
        Connect(wxID_ANY, wxEVT_SCROLLWIN_LINEUP, wxScrollWinEventHandler(ScrolledImageComponent::onScroll), NULL, this);
        Connect(wxID_ANY, wxEVT_SCROLLWIN_LINEDOWN, wxScrollWinEventHandler(ScrolledImageComponent::onScroll), NULL, this);
    }
    ~ScrolledImageComponent()
    {
        delete bitmap;
    }
    
    void SetPeer(ScrolledImageComponent* other)
    {
        m_peer = other;
    }
    
    void onScroll(wxScrollWinEvent& evt)
    {
        if (m_peer != NULL)
        {
            m_peer->Scroll(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
        }
        evt.Skip(); // let the event go
    }
    
    void OnDraw(wxDC& dc)
    {
        /* render the image - in a real app, if your scrolled area
         is somewhat big, you will want to draw only visible parts,
         not everything like below */
        dc.DrawBitmap(*bitmap, 0, 0, false);
        
        // also check wxScrolledWindow::PrepareDC
    }
};


class MyApp: public wxApp
{
    wxFrame *frame;
public:
    
    bool OnInit()
    {
        wxInitAllImageHandlers();
        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
        frame = new wxFrame((wxFrame *)NULL, -1,  wxT("Scrolling an Image"), wxPoint(50,50), wxSize(650,650));
        
        ScrolledImageComponent* my_image = new ScrolledImageComponent(frame, wxID_ANY, wxT("my_image.jpg") );
        sizer->Add(my_image, 1, wxALL | wxEXPAND, 5);
        
        ScrolledImageComponent* my_image2 = new ScrolledImageComponent(frame, wxID_ANY, wxT("my_image.jpg") );
        sizer->Add(my_image2, 1, wxALL | wxEXPAND, 5);
        
        my_image->SetPeer(my_image2);
        my_image2->SetPeer(my_image);
        
        frame->SetSizer(sizer);
        
        frame->Show();
        return true;
    } 
};

IMPLEMENT_APP(MyApp)