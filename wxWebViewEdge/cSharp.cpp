  private void Form1_Load(object? sender, EventArgs e)
        {
            webView21.Source = new Uri(AppDomain.CurrentDomain.BaseDirectory + "line_chart.html");

        }



  private void toolStripLabel1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "*.data|*.data";
            openFileDialog.InitialDirectory = AppDomain.CurrentDomain.BaseDirectory;
            openFileDialog.ShowDialog();
            if (string.IsNullOrEmpty(openFileDialog.FileName)) return;
            var s = File.ReadAllText(openFileDialog.FileName);
            var js = $"let dd = {s};" +
                $"LoadData(dd);";
            webView21.CoreWebView2.ExecuteScriptAsync(js);
        }
