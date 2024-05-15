#include <wx/dcbuffer.h>
#include "bubblespanel.h"

/// 事件定义：圆移动了一步
wxDEFINE_EVENT(BubblesPanel_MovedStep, wxCommandEvent);

wxBEGIN_EVENT_TABLE(BubblesPanel, wxWindow)
    EVT_PAINT(BubblesPanel::PaintEvent)
    EVT_TIMER(wxID_ANY, BubblesPanel::TimerEvent)
wxEND_EVENT_TABLE()


BubblesPanel::BubblesPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos,
                           const wxSize &size, long style, const wxString &name) :
    wxWindow(parent, id, pos, size, style, name),
    m_timer(this, wxID_ANY),
    m_pbmpCircle(nullptr),
    m_clrCircle(123, 209, 234),
    m_ptCircle(100, 100),
    m_nStep(5),
    m_nCircleDirection(73)
{
    GenerateCircleBitmap(100, 100);
}


BubblesPanel::~BubblesPanel()
{
    delete m_pbmpCircle;
    m_pbmpCircle = nullptr;
}


void BubblesPanel::StartAnimation(int nInterval)
{
    m_timer.Start(nInterval);
}


void BubblesPanel::StopAnimation()
{
    m_timer.Stop();
}


void BubblesPanel::SetCirclePosition(const wxPoint &pt)
{
    m_ptCircle = pt;
    Refresh();
}


void BubblesPanel::SetCircleSize(int w, int h)
{
    GenerateCircleBitmap(w, h);
    Refresh();
}


void BubblesPanel::SetCircleColor(const wxColour &clr)
{
    m_clrCircle = clr;
    RepaintCircleBmp();
    Refresh();
}


void BubblesPanel::SetCircleStep(int nStep)
{
    m_nStep = nStep;
}


void BubblesPanel::SetCircleDirection(int nDirection)
{
    m_nCircleDirection = nDirection;
}


void BubblesPanel::PaintEvent(wxPaintEvent &e)
{
    wxPaintDC dc(this);
    dc.SetBackground(*wxTRANSPARENT_BRUSH);
    dc.Clear();
    dc.DrawBitmap(*m_pbmpCircle, m_ptCircle);
}


void BubblesPanel::TimerEvent(wxTimerEvent &e)
{
    MoveCircle();
}


void BubblesPanel::MoveCircle()
{
    // 如果球已经超出边缘，则直接回到边缘
    if (m_ptCircle.x < 0)
        m_ptCircle.x = 0;
    if (m_ptCircle.x > GetClientSize().GetWidth() - m_pbmpCircle->GetWidth())
        m_ptCircle.x = GetClientSize().GetWidth() - m_pbmpCircle->GetWidth();
    if (m_ptCircle.y < 0)
        m_ptCircle.y = 0;
    if (m_ptCircle.y > GetClientSize().GetHeight() - m_pbmpCircle->GetHeight())
        m_ptCircle.y = GetClientSize().GetHeight() - m_pbmpCircle->GetHeight();

    double dXNext = m_ptCircle.x + m_nStep * std::cos(m_nCircleDirection * M_PI / 180);  // 圆的下一步的x坐标
    double dYNext = m_ptCircle.y + m_nStep * std::sin(m_nCircleDirection * M_PI / 180);  // 圆的下一步的y坐标

    // 判断圆的下一步是否已经到达控件边界，如果是，则会反弹，改变方向
    if (dXNext < 0 || dXNext > GetClientSize().GetWidth() - m_pbmpCircle->GetWidth())
        m_nCircleDirection = 180 - m_nCircleDirection;
    if (dYNext < 0 || dYNext > GetClientSize().GetHeight() - m_pbmpCircle->GetHeight())
        m_nCircleDirection = 360 - m_nCircleDirection;

    // 根据圆的位置、步长、方向，计算圆下一步的位置（四舍五入）
    dXNext       = m_ptCircle.x + m_nStep * std::cos(m_nCircleDirection * M_PI / 180);
    dYNext       = m_ptCircle.y + m_nStep * std::sin(m_nCircleDirection * M_PI / 180);
    m_ptCircle.x = static_cast<int>(lround(dXNext));
    m_ptCircle.y = static_cast<int>(lround(dYNext));

    wxCommandEvent event(BubblesPanel_MovedStep);
    event.SetEventObject(this);
    GetEventHandler()->ProcessEvent(event);  // 发送事件

    // 重绘控件
    Refresh();
}


void BubblesPanel::GenerateCircleBitmap(int w, int h)
{
    if (m_pbmpCircle && m_pbmpCircle->GetSize() != wxSize(w, h)
        || !m_pbmpCircle)
    {
        delete m_pbmpCircle;
        m_pbmpCircle = new wxBitmap(w, h, 32);
    }

    // 重新绘制圆
    RepaintCircleBmp();
}


void BubblesPanel::RepaintCircleBmp()
{
    wxMemoryDC dcBmp(*m_pbmpCircle);
    dcBmp.SetBackground(*wxTRANSPARENT_BRUSH);
    dcBmp.Clear();
    dcBmp.SetPen(*wxTRANSPARENT_PEN);
    dcBmp.SetBrush(m_clrCircle);

    int w = m_pbmpCircle->GetWidth();
    int h = m_pbmpCircle->GetHeight();
    dcBmp.DrawCircle(w / 2, h / 2, w / 2);
}
