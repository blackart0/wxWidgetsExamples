#ifndef BUBBLES_MAINWIN_H
#define BUBBLES_MAINWIN_H

#include <wx/wx.h>

namespace UI
{
    class MainWin;
}

class MainWin : public wxFrame
{
public:
    explicit MainWin();
    ~MainWin() override;

protected:
    // 事件：圆动画控件中的圆移动了一步
    //void BubblesPanelMovedStepEvent(wxCommandEvent &e);

    // 绑定所有事件
    //void BindAll();

    // 刷新控件的值
    //void FlushCtrlsValue();

private:
    UI::MainWin *ui;

    wxDECLARE_EVENT_TABLE();
};

#endif  //! BUBBLES_MAINWIN_H
