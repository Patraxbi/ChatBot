using ChatbotVisualInterface.Connectors;
using Microsoft.Win32;
using System.Collections.ObjectModel;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace ChatbotVisualInterface
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public ObservableCollection<SimpleTextMessage> ItemList { get; set; }

        public MainWindow()
        {
            InitializeComponent();
            DataContext = this;
            ItemList = new ObservableCollection<SimpleTextMessage>();
            RecieveAnswer(this, new RoutedEventArgs(), "Hello World!");
        }

        private void RecieveQuestion(object sender, RoutedEventArgs e)
        {
            string answer = Input_Bar.Text.Trim();
            if (answer == "") return;

            ItemList.Add(new SimpleTextMessage(answer, true));
            Input_Bar.Clear();

            if (VisualTreeHelper.GetChildrenCount(Chat_Box) > 0)
            {
                Border border = (Border)VisualTreeHelper.GetChild(Chat_Box, 0);
                ScrollViewer scrollViewer = (ScrollViewer)VisualTreeHelper.GetChild(border, 0);
                scrollViewer.ScrollToBottom();
            }
            //TODO send question to backend
        }

        public void RecieveAnswer(object sender, RoutedEventArgs e, string answer)
        {
            if (answer == null) return;
            ItemList.Add(new SimpleTextMessage(answer));
            // TODO wait for answer from backend
        }

        private void Input_Bar_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                RecieveQuestion(sender, new RoutedEventArgs());
            }
        }

        private void SaveConversation(object sender, RoutedEventArgs e)
        {
            if (ItemList.Count == 0) return;

            var dialog = new SaveFileDialog();
            dialog.Filter = "Text Files (*.txt)|*.txt";
            if (dialog.ShowDialog() == true)
            {
                string path = dialog.FileName;
                var fs = new StreamWriter(path);
                foreach (var message in ItemList)
                {
                    fs.WriteLine(message.Text);
                }
                fs.Close();
            }
        }

        private void ClearConversation(object sender, RoutedEventArgs e)
        {
            ItemList.Clear();
        }

        private void Window_GotFocus(object sender, RoutedEventArgs e)
        {
            Input_Bar.Focus();
        }
    }
}
