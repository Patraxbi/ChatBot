using System.Windows;
using System.Windows.Media;

namespace ChatbotVisualInterface.Connectors
{
    /// <summary>
    /// Datastructure for displaying a simple text message as either question or answer
    /// </summary>
    public class SimpleTextMessage
    {
        public string Text { get; set; }
        public SolidColorBrush ColorBrush { get; set; }
        public CornerRadius CornerRadius { get; set; }
        public HorizontalAlignment AlignmentX { get; set; }

        private readonly Color questionColor = (Color)ColorConverter.ConvertFromString("#141E46");
        private readonly Color answerColor = (Color)ColorConverter.ConvertFromString("#006837");

        public SimpleTextMessage(string text, bool isQuestion = false)
        {
            Text = text;
            if (isQuestion)
            {
                ColorBrush = new SolidColorBrush(questionColor);
                CornerRadius = new CornerRadius(14, 0, 14, 14);
                AlignmentX = HorizontalAlignment.Right;
            }
            else
            {
                ColorBrush = new SolidColorBrush(answerColor);
                CornerRadius = new CornerRadius(0, 14, 14, 14);
                AlignmentX = HorizontalAlignment.Left;
            }
        }
    }
}
