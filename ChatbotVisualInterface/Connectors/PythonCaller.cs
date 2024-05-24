using System.Collections.Generic;
using System.Diagnostics;
using System.IO;

namespace ChatbotVisualInterface.Connectors
{
    /// <summary>
    /// Container for iron python script runner engine, connected to the text-processing layer
    /// </summary>
    public class PythonCaller
    {
        private List<string> Run_cmd(string cmd, string args)
        {
            ProcessStartInfo start = new ProcessStartInfo();
            // start.FileName = ".\\Python312\\python.exe";
            start.FileName = ".\\TextProcessingLayer.exe";
            // start.Arguments = string.Format("{0} {1}", cmd, args);
            start.Arguments = args;
            start.UseShellExecute = false;
            start.RedirectStandardOutput = true;
            start.CreateNoWindow = true;
            List<string> result = new List<string>();
            using (Process process = Process.Start(start))
            {
                using (StreamReader reader = process.StandardOutput)
                {
                    while (!reader.EndOfStream)
                    {
                        string line = reader.ReadLine();
                        if (!string.IsNullOrEmpty(line))
                        {
                            result.Add(line);
                        }
                    }
                }
            }
            return result;
        }

        /// <summary>Send question to script</summary>
        /// <returns>The answer as string</returns>
        public List<string> ProcessScript(string question)
        {
            //dynamic pyList = func(question);
            //string[] mylist = (string[])pyList;
            List<string> mylist = Run_cmd("TextProcessingLayer.py", $"\"{question}\"");
            return mylist;
        }
    }
}
