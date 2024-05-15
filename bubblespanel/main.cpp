#include <wx/wx.h>
#include "mainwin.h"

class MyApp : public wxApp
{
public:
   bool OnInit() override  
   {
       MainWin *frame = new MainWin();
       frame->Show();
       frame->Center(); 
       return true;
   }
};

wxIMPLEMENT_APP(MyApp); // NOLINT
