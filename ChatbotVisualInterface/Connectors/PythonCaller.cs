using Python.Runtime;
using System.Collections.Generic;
using System.IO;

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

        /// <summary>Send question to script</summary>
        /// <returns>The answer as string</returns>
        public string[] ProcessScript(string question)
        {
            dynamic pyList = func(question);
            string[] mylist = (string[])pyList;
            return mylist;
        }
    }
}
