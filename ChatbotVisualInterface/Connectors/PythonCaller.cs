using Python.Runtime;
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
            string pythonDll = "Python312\\python312.dll";
            Runtime.PythonDLL = pythonDll;

            PythonEngine.Initialize();
            using (Py.GIL())
            {
                using (PyModule scope = Py.CreateScope())
                {
                    const string ScriptFile = "TextProcessingLayer.py";
                    var code = File.ReadAllText(ScriptFile);
                    var scriptCompiled = PythonEngine.Compile(code, ScriptFile);

                    scope.Execute(scriptCompiled);
                    func = scope.Get("text_processing_layer");
                }
            }
        }

        /// <summary>Send question to script</summary>
        /// <returns>The answer as string</returns>
        public string ProcessScript(string question)
        {
            return func(question);
        }
    }
}
