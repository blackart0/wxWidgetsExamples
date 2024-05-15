#ifndef BUBBLES_BUBBLESPANEL_H
#define BUBBLES_BUBBLESPANEL_H

#include <wx/wx.h>

/// 事件声明：圆移动了一步
wxDECLARE_EVENT(BubblesPanel_MovedStep, wxCommandEvent);

class BubblesPanel : public wxWindow
{
public:
    explicit BubblesPanel(wxWindow *parent, wxWindowID id = wxID_ANY,
                          const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize,
                          long style = wxTAB_TRAVERSAL, const wxString &name = wxPanelNameStr);
    ~BubblesPanel() override;

    /**
     * @brief 开始动画
     * @param[in] nInterval 动画的时间间隔，单位为毫秒
     */
    void StartAnimation(int nInterval);

    /// 停止动画
    void StopAnimation();

    /// 设置圆的位置
    void SetCirclePosition(const wxPoint &pt);

    /// 设置圆的大小
    void SetCircleSize(int w, int h);

    /// 设置圆的颜色
    void SetCircleColor(const wxColour &clr);

    /// 设置圆的步长
    void SetCircleStep(int nStep);

    /// 设置圆的方向
    void SetCircleDirection(int nDirection);

    /// 获取圆的位置
    [[nodiscard]] wxPoint GetCirclePosition() const { return m_ptCircle; }

    /// 获取圆的大小
    [[nodiscard]] wxSize GetCircleSize() const { return m_pbmpCircle->GetSize(); }

    /// 获取圆的颜色
    [[nodiscard]] wxColour GetCircleColor() const { return m_clrCircle; }

    /// 获取圆的步长
    [[nodiscard]] int GetCircleStep() const { return m_nStep; }

    /// 获取圆的方向
    [[nodiscard]] int GetCircleDirection() const { return m_nCircleDirection; }

protected:
    void PaintEvent(wxPaintEvent &e);
    void TimerEvent(wxTimerEvent &e);

    /**
     * @brief 圆移动一步
     * @note
     * 1. 判断圆的下一步是否已经到达控件边界，如果是，则会反弹，改变方向
     * 2. 根据圆的位置、步长、方向，计算圆下一步的位置
     */
    void MoveCircle();

    /// 生成圆的位图
    void GenerateCircleBitmap(int w, int h);

    /// 重新绘制圆的位图
    void RepaintCircleBmp();

    wxTimer m_timer;         ///< 定时器，用于动画
    wxBitmap *m_pbmpCircle;  ///< 圆的位图
    wxColour m_clrCircle;    ///< 圆的颜色
    wxPoint m_ptCircle;      ///< 圆的位置
    int m_nStep;             ///< 圆的步长，每次移动的距离，单位像素
    int m_nCircleDirection;  ///< 圆下一步的方向，360度，0度为正右方，顺时针增加

    wxDECLARE_EVENT_TABLE();
};

#endif  //! BUBBLES_BUBBLESPANEL_H
