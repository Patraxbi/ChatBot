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
        private readonly IronPythonCaller ironPythonCaller;

        public MainWindow()
        {
            InitializeComponent();
            DataContext = this;
            ItemList = new ObservableCollection<SimpleTextMessage>();
            ironPythonCaller = new IronPythonCaller();
            RecieveAnswer("Hello World!");
        }

        /// <summary>
        /// Reads content of user's input-bar. If not empty, sends it to the next layer for processing
        /// </summary>
        private void RecieveQuestion(object sender, RoutedEventArgs e)
        {
            string question = Input_Bar.Text.Trim();
            if (question == "") return;

            ItemList.Add(new SimpleTextMessage(question, true));
            Input_Bar.Clear();

            // Scroll to bottom of conversation pannel when item is added
            if (VisualTreeHelper.GetChildrenCount(Chat_Box) > 0)
            {
                Border border = (Border)VisualTreeHelper.GetChild(Chat_Box, 0);
                ScrollViewer scrollViewer = (ScrollViewer)VisualTreeHelper.GetChild(border, 0);
                scrollViewer.ScrollToBottom();
            }

            // Send question to Python script
            string answer = ironPythonCaller.ProcessScript(question);
            RecieveAnswer(answer);
        }

        /// <summary>
        /// Displays answer in conversation pannel
        /// </summary>
        public void RecieveAnswer(string answer)
        {
            if (answer == null) return;
            ItemList.Add(new SimpleTextMessage(answer));
        }

        /// <summary>
        /// Detects input of Enter key
        /// </summary>
        private void Input_Bar_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                RecieveQuestion(sender, new RoutedEventArgs());
            }
        }

        /// <summary>
        /// Opens dialogue for user to save a conversation log file locally
        /// </summary>
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
                    if (message.isQuestion)
                        fs.Write("[Q]: ");
                    else
                        fs.Write("[A]: ");
                    fs.WriteLine(message.Text);
                }
                fs.Close();
            }
        }

        /// <summary>
        /// Emptyes conversation pannel. Does not affect saved conversation logs.
        /// </summary>
        private void ClearConversation(object sender, RoutedEventArgs e)
        {
            ItemList.Clear();
        }

        /// <summary>
        /// Ensures keyboard focus is allways in the input bar
        /// </summary>
        private void Window_GotFocus(object sender, RoutedEventArgs e)
        {
            Input_Bar.Focus();
        }
    }
}
