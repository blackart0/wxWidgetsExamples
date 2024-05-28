// 创建一个继承自wxFrame的窗口类
class MyFrame : public wxFrame
{
public:
    MyFrame() : wxFrame(NULL, wxID_ANY, "窗口标题")
    {
        // 创建wxChartView实例并添加到窗口
        m_chartView = new wxChartView(this);
        
        // 捕获窗口的尺寸改变事件
        Bind(wxEVT_SIZE, &MyFrame::OnSize, this);
    }
    
    void OnSize(wxSizeEvent& event)
    {
        wxSize size = event.GetSize(); // 获取窗口的新尺寸
        
        // 调整wxChartView的大小
        m_chartView->Resize(size.GetWidth(), size.GetHeight());
        
        event.Skip();
    }
    
private:
    wxChartView* m_chartView;
};

// 在应用程序中创建窗口并运行事件循环
class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        MyFrame* frame = new MyFrame();
        frame->Show();
        
        return true;
    }
};

IMPLEMENT_APP(MyApp);
