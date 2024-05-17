#include <wx/wx.h>
#include <wx/graphics.h>

class AngularGauge : public wxWindow
{
    public:
        AngularGauge(wxWindow *parent, wxWindowID id, wxPoint Position, int Size);
        wxWindow *m_parent;

        FILE *debug;

        char col;
        int Width,Height;
        double InputAngle;
        double pi = 3.14159265359;
        wxString Name = "ANGLE", Unit = "DEGREES";
        void OnPaint(wxPaintEvent& event);
        void SetValue(double Value);
        wxPoint2DDouble Rot2D(wxPoint2DDouble point, wxPoint2DDouble pref, double theta);
};