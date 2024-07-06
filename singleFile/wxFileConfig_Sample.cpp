#include <wx/config.h>  
#include <wx/fileconf.h>  
#include <wx/filename.h>  
  
// 获取可执行文件的当前目录  
wxFileName exeName(wxStandardPaths::Get().GetExecutablePath());  
wxString exeDir = exeName.GetPath();  

// 创建wxFileConfig对象，指定配置文件名称，但不指定路径（将使用当前目录）  
wxFileConfig *config = new wxFileConfig(_("AppName"), _("VendorName"), _("config.ini"), _(""), wxCONFIG_USE_RELATIVE_PATH);  

// 或者，你可以显式地指定配置文件的完整路径  
// wxString configPath = exeDir + wxFILE_SEP_PATH + _("config.ini");  
// wxFileConfig *config = new wxFileConfig(_("AppName"), _("VendorName"), configPath);  
// 写入配置信息  
config->Write(_("/General/Setting1"), _("Value1"));  
config->Write(_("/General/Setting2"), 123); // 写入整型值  

// 读取配置信息  
wxString value1;  
long value2;  
config->Read(_("/General/Setting1"), &value1);  
config->Read(_("/General/Setting2"), &value2);  

// 接下来，你可以像之前一样使用config对象读写配置信息  
// ...  

// 释放资源  
delete config;