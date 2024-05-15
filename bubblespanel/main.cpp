#include <wx/wx.h>
#include "mainwin.h"

class MyApp : public wxApp
{
public:
   bool OnInit() override  /*此函数为入口函数，必须重写*/
   {
       MainWin *frame = new MainWin();
       frame->Show();
       frame->Center();  // 主窗口居中显示
       return true;
   }
};

wxIMPLEMENT_APP(MyApp); // NOLINT
