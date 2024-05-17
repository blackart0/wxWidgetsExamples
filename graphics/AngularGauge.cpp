#include "AngularGauge.h"

AngularGauge::AngularGauge(wxWindow *parent, wxWindowID id, wxPoint Position, int Size)
    : wxWindow(parent, id, Position, wxSize(Size,Size), wxTRANSPARENT_WINDOW)
{
    m_parent = parent;
    Connect(wxEVT_PAINT, wxPaintEventHandler(AngularGauge::OnPaint));
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Width = Size;
    Height = Size;
}


void AngularGauge::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
    wxPoint2DDouble Needle[6], BigMark[2], SmallMark[2], AuxMark[2], TextPos, AuxTextPos, Center = wxPoint2DDouble(Width/2,Height/2);
    int i;
    int CircleDiameter= 0.95*Width, CircleRadius;
    double AngleRad;
    double BorderWidth = 2;
    wxString AuxString;
    wxFont font(Height/20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxFont font1(Height/25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxFont font2(Height/30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    wxDouble txt_width, txt_height, txt_descent, txt_extleading;

    //El diámetro del círculo es un 95% del área total
    CircleRadius = 0.5*CircleDiameter;

    //Dibujar sector circular rojo (babor)
    wxGraphicsPath port_sector = gc->CreatePath();
    gc->SetPen(wxPen(wxColor(255,0,0), 1, wxPENSTYLE_SOLID));
    port_sector.MoveToPoint(Width/2, Center.m_y+CircleRadius);
    port_sector.AddLineToPoint(Width/2, Center.m_y+0.8*CircleRadius);
    port_sector.AddArc(Center,0.8*CircleRadius,pi/2,1.25*pi,true);
    port_sector.MoveToPoint(Rot2D(wxPoint2DDouble(Width/2,Center.m_y+0.8*CircleRadius),Center,135*pi/180));
    port_sector.AddLineToPoint(Rot2D(wxPoint2DDouble(Width/2,Center.m_y+CircleRadius),Center,135*pi/180));
    port_sector.AddArc(Center,CircleRadius,1.25*pi,pi/2,false);
    gc->SetBrush(*wxRED);
    gc->FillPath(port_sector);
    gc->StrokePath(port_sector);

    //Dibujar sector circular verde (estribor)
    wxGraphicsPath stbd_sector = gc->CreatePath();
    gc->SetPen(wxPen(wxColor(0,255,0), 1, wxPENSTYLE_SOLID));
    stbd_sector.MoveToPoint(Width/2, Center.m_y+CircleRadius);
    stbd_sector.AddLineToPoint(Width/2, Center.m_y+0.8*CircleRadius);
    stbd_sector.AddArc(Center,0.8*CircleRadius,pi/2,-0.25*pi,false);
    stbd_sector.MoveToPoint(Rot2D(wxPoint2DDouble(Width/2,Center.m_y+0.8*CircleRadius),Center,1.25*pi));
    stbd_sector.AddLineToPoint(Rot2D(wxPoint2DDouble(Width/2,Center.m_y+CircleRadius),Center,1.25*pi));
    stbd_sector.AddArc(Center,CircleRadius,-0.25*pi,pi/2,true);
    gc->SetBrush(*wxGREEN);
    gc->FillPath(stbd_sector);
    gc->StrokePath(stbd_sector);

    //Dibujar divisiones mayores
    gc->SetPen(wxPen(wxColor(0,0,0), 3, wxPENSTYLE_SOLID));
    BigMark[0] = wxPoint2DDouble(Center.m_x,Center.m_y+CircleRadius);
    BigMark[1] = wxPoint2DDouble(Center.m_x,Center.m_y+0.7*CircleRadius);
    gc->DrawLines(2,BigMark,wxODDEVEN_RULE);

    AuxMark[0] = BigMark[0];
    AuxMark[1] = BigMark[1];

    for(i=0;i<4;i++)
    {
        AuxMark[0] = Rot2D(AuxMark[0],Center,30*(pi/180));
        AuxMark[1] = Rot2D(AuxMark[1],Center,30*(pi/180));
        gc->DrawLines(2,AuxMark,wxODDEVEN_RULE);
    }

    AuxMark[0] = BigMark[0];
    AuxMark[1] = BigMark[1];

    for(i=0;i<4;i++)
    {
        AuxMark[0] = Rot2D(AuxMark[0],Center,-30*(pi/180));
        AuxMark[1] = Rot2D(AuxMark[1],Center,-30*(pi/180));
        gc->DrawLines(2,AuxMark,wxODDEVEN_RULE);
    }

    //Dibujar divisiones menores
    gc->SetPen(wxPen(wxColor(0,0,0), 1, wxPENSTYLE_SOLID));
    SmallMark[0] = wxPoint2DDouble(Center.m_x,Center.m_y+CircleRadius);
    SmallMark[1] = wxPoint2DDouble(Center.m_x,Center.m_y+0.8*CircleRadius);
    gc->DrawLines(2,SmallMark,wxODDEVEN_RULE);

    AuxMark[0] = SmallMark[0];
    AuxMark[1] = SmallMark[1];

    for(i=0;i<45;i++)
    {
        AuxMark[0] = Rot2D(AuxMark[0],Center,3*(pi/180));
        AuxMark[1] = Rot2D(AuxMark[1],Center,3*(pi/180));
        gc->DrawLines(2,AuxMark,wxODDEVEN_RULE);
    }

    AuxMark[0] = SmallMark[0];
    AuxMark[1] = SmallMark[1];

    for(i=0;i<45;i++)
    {
        AuxMark[0] = Rot2D(AuxMark[0],Center,-3*(pi/180));
        AuxMark[1] = Rot2D(AuxMark[1],Center,-3*(pi/180));
        gc->DrawLines(2,AuxMark,wxODDEVEN_RULE);
    }

    //Dibujar divisiones intermedias, cada 5 grados

    gc->SetPen(wxPen(wxColor(0,0,0), 2, wxPENSTYLE_SOLID));
    SmallMark[0] = wxPoint2DDouble(Center.m_x,Center.m_y+CircleRadius);
    SmallMark[1] = wxPoint2DDouble(Center.m_x,Center.m_y+0.75*CircleRadius);
    gc->DrawLines(2,SmallMark,wxODDEVEN_RULE);

    AuxMark[0] = SmallMark[0];
    AuxMark[1] = SmallMark[1];

    for(i=0;i<8;i++)
    {
        AuxMark[0] = Rot2D(AuxMark[0],Center,15*(pi/180));
        AuxMark[1] = Rot2D(AuxMark[1],Center,15*(pi/180));
        gc->DrawLines(2,AuxMark,wxODDEVEN_RULE);
    }

    AuxMark[0] = SmallMark[0];
    AuxMark[1] = SmallMark[1];

    for(i=0;i<8;i++)
    {
        AuxMark[0] = Rot2D(AuxMark[0],Center,-15*(pi/180));
        AuxMark[1] = Rot2D(AuxMark[1],Center,-15*(pi/180));
        gc->DrawLines(2,AuxMark,wxODDEVEN_RULE);
    }

    //Dibujar etiquetas
    gc->SetFont(font,*wxBLACK);
    AuxString = "0";
    gc->GetTextExtent((const char*)AuxString,&txt_width,&txt_height,&txt_descent,&txt_extleading);
    TextPos = wxPoint2DDouble(Center.m_x,0.75*Height);
    AuxTextPos = wxPoint2DDouble(TextPos.m_x,TextPos.m_y);
    gc->DrawText(AuxString,AuxTextPos.m_x-0.5*txt_width,AuxTextPos.m_y-0.5*txt_height);

    //Etiquetas babor
    for(i=1;i<=4;i++)
    {
        AuxString = wxString::Format("%02d",10*i);
        gc->GetTextExtent((const char*)AuxString,&txt_width,&txt_height,&txt_descent,&txt_extleading);
        AuxTextPos = Rot2D(AuxTextPos,Center,30*(pi/180));
        gc->SetBrush(*wxTRANSPARENT_BRUSH);
        gc->DrawText(AuxString,AuxTextPos.m_x-0.5*txt_width,AuxTextPos.m_y-0.5*txt_height);
    }

    AuxTextPos = wxPoint2DDouble(TextPos.m_x,TextPos.m_y);

    //Etiquetas estribor
    for(i=1;i<=4;i++)
    {
        AuxString = wxString::Format("%02d",10*i);
        gc->GetTextExtent((const char*)AuxString,&txt_width,&txt_height,&txt_descent,&txt_extleading);
        AuxTextPos = Rot2D(AuxTextPos,Center,-30*(pi/180));
        gc->SetBrush(*wxTRANSPARENT_BRUSH);
        gc->DrawText(AuxString,AuxTextPos.m_x-0.5*txt_width,AuxTextPos.m_y-0.5*txt_height);
    }

    //Nombre del indicador
    gc->GetTextExtent((const char*)Name,&txt_width,&txt_height,&txt_descent,&txt_extleading);
    gc->DrawText(Name,Center.m_x-0.5*txt_width,Height/10-0.5*txt_height);
    gc->SetFont(font1,*wxBLACK);//font.SetPixelSize(Height/25);
    gc->GetTextExtent((const char*)Unit,&txt_width,&txt_height,&txt_descent,&txt_extleading);
    gc->DrawText(Unit,Center.m_x-0.5*txt_width,Height/6-0.5*txt_height);

    //Etiquetas de PORT y STBD
    gc->SetFont(font2,*wxBLACK);
    AuxString = "PORT";
    gc->GetTextExtent((const char*)AuxString,&txt_width,&txt_height,&txt_descent,&txt_extleading);
    TextPos = wxPoint2DDouble(Center.m_x,0.85*Height);
    AuxTextPos = wxPoint2DDouble(TextPos.m_x,TextPos.m_y);
    AuxTextPos = Rot2D(AuxTextPos,Center,0.75*pi);
    gc->DrawText(AuxString,AuxTextPos.m_x,AuxTextPos.m_y-0.5*txt_height);
    AuxString = "STBD";
    AuxTextPos = Rot2D(AuxTextPos,Center,-1.5*pi);
    gc->GetTextExtent((const char*)AuxString,&txt_width,&txt_height,&txt_descent,&txt_extleading);
    gc->DrawText(AuxString,AuxTextPos.m_x-txt_width,AuxTextPos.m_y-0.5*txt_height);


    //Dibujar aguja
    Needle[0] = wxPoint2DDouble(Width/2, 0.95*Height);
    Needle[1] = wxPoint2DDouble(Width/2 - Width/15, Height/2);
    Needle[2] = wxPoint2DDouble(Width/2 + Width/15, Height/2);

    //AngleRad = -3*InputAngle*pi/180;
    AngleRad = -InputAngle*pi/60;

    //Rotación en el plano, dependiendo de Angle00
    for(i=0;i<3;i++)
        Needle[i] = Rot2D(Needle[i],Center,AngleRad);

    gc->SetPen(wxPen(wxColor(0,0,0), 2, wxPENSTYLE_SOLID));
    gc->SetBrush(*wxYELLOW);
    wxGraphicsPath the_needle = gc->CreatePath();
    the_needle.MoveToPoint(Needle[0].m_x, Needle[0].m_y);
    the_needle.AddLineToPoint(Needle[1].m_x, Needle[1].m_y);
    the_needle.AddLineToPoint(Needle[2].m_x, Needle[2].m_y);
    the_needle.AddLineToPoint(Needle[0].m_x, Needle[0].m_y);
    gc->FillPath(the_needle);
    gc->StrokePath(the_needle);


    //Dibujar círculo central
    wxGraphicsPath center_circle = gc->CreatePath();
    gc->SetPen(wxPen(wxColor(0,0,0), 1, wxPENSTYLE_SOLID));
    gc->SetBrush(*wxBLACK);
    center_circle.AddArc(Center,0.35*CircleRadius,0,2*pi,true);
    gc->FillPath(center_circle);
    gc->StrokePath(center_circle);

    delete gc;
}


void AngularGauge::SetValue(double Value)
{
    InputAngle = Value;
    Refresh();
}


/*
Rotación en el plano

Ángulo theta se debe expresar en en radianes; el sentido de giro es antihorario
*/
wxPoint2DDouble AngularGauge::Rot2D(wxPoint2DDouble point, wxPoint2DDouble pref, double theta)
{
    double x,y,rx,ry,x1,y1;
    wxPoint2DDouble auxpoint;

    x = point.m_x; y = point.m_y;
    rx = pref.m_x; ry = pref.m_y;

    x = x-rx; y = y-ry;

    x1 = x*cos(theta)-y*sin(theta);
    y1 = x*sin(theta)+y*cos(theta);

    x1 = x1 + rx; y1 = y1 + ry;

    auxpoint = wxPoint2DDouble(x1,y1);
    return(auxpoint);
}