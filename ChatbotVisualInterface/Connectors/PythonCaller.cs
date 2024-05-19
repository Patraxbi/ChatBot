using Microsoft.Scripting.Utils;
using Python.Runtime;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Windows.Documents;

namespace ChatbotVisualInterface.Connectors
{
    /// <summary>
    /// Container for iron python script runner engine, connected to the text-processing layer
    /// </summary>
    public class PythonCaller
    {
        dynamic func;

        public PythonCaller()
        {
            // Setup()
        }

        private void Setup()
        {
            const string pythonDll = ".\\Python312\\python312.dll";
            Runtime.PythonDLL = pythonDll;

            PythonEngine.Initialize();
            using (Py.GIL())
            {
                using (PyModule scope = Py.CreateScope())
                {
                    const string ScriptFile = "TextProcessingLayer.py";
                    string code = File.ReadAllText(ScriptFile);
                    PyObject scriptCompiled = PythonEngine.Compile(code, ScriptFile);

                    scope.Execute(scriptCompiled);
                    func = scope.Get("text_processing_layer");
                }
            }
        }

        private List<string> Run_cmd(string cmd, string args)
        {
            ProcessStartInfo start = new ProcessStartInfo();
            start.FileName = ".\\Python312\\python.exe";
            start.Arguments = string.Format("{0} {1}", cmd, args);
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
