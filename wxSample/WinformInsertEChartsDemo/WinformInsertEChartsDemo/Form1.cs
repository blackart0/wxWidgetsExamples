using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WinformInsertEChartsDemo
{
    //设置Com对外可访问
    [System.Runtime.InteropServices.ComVisible(true)]
    public partial class Form1 : Form
    {
        /// <summary>
        /// 根目录
        /// </summary>
        string str = System.Environment.CurrentDirectory;
        public Form1()
        {
            InitializeComponent();

            //初始化浏览器
            this.initWebBrowser();

            //加载 文件
            this.getAllHtmlFile();
        }

        /// <summary>
        /// 初始化浏览器
        /// </summary>
        private void initWebBrowser()
        {
            //防止 WebBrowser 控件打开拖放到其上的文件。
            webBrowser1.AllowWebBrowserDrop = false;

            //防止 WebBrowser 控件在用户右击它时显示其快捷菜单.
            webBrowser1.IsWebBrowserContextMenuEnabled = false;

            //以防止 WebBrowser 控件响应快捷键。
            webBrowser1.WebBrowserShortcutsEnabled = false;

            //以防止 WebBrowser 控件显示脚本代码问题的错误信息。    
            webBrowser1.ScriptErrorsSuppressed = true;

            //（这个属性比较重要，可以通过这个属性，把WINFROM中的变量，传递到JS中，供内嵌的网页使用；但设置到的类型必须是COM可见的，所以要设置     [System.Runtime.InteropServices.ComVisibleAttribute(true)]，因为我的值设置为this,所以这个特性要加载窗体类上）
            webBrowser1.ObjectForScripting = this; 
        }

        /// <summary>
        /// 窗体加载
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form1_Load(object sender, EventArgs e)
        {
            //浏览器url 取到index.html页面
            //this.webBrowser1.Url = new Uri(str + "\\index.html");
            //if (comboBox1.Items.Count > 0)
            //{
            //    comboBox1.SelectedIndex = 0;
            //    this.webBrowser1.Url = new Uri(str +"\\"+ comboBox1.Text.Trim());
            //}
        }

        /// <summary>
        /// 获取html文件
        /// </summary>
        private void getAllHtmlFile()
        {
            //获取指定文件夹的所有文件  
            string[] paths = Directory.GetFiles(str);
            foreach (var item in paths)
            {
                //获取文件后缀名  
                string extension = Path.GetExtension(item).ToLower();
                if (extension == ".html")
                {
                    comboBox1.Items.Add(Path.GetFileName(item));
                }
            }

            if (comboBox1.Items.Count > 0)
            {
                comboBox1.SelectedIndex = 0;
                this.webBrowser1.Url = new Uri(str + "\\" + comboBox1.Text.Trim());
            }
        }

        /// <summary>
        /// 刷新
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button2_Click(object sender, EventArgs e)
        {
            this.webBrowser1.Refresh();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.webBrowser1.Url = new Uri(str + "\\"+comboBox1.Text.Trim());
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.webBrowser1.Dispose();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            comboBox1.Items.Clear();
            this.getAllHtmlFile();
        }

    }
}
