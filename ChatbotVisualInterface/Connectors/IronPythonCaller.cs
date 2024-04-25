using IronPython.Hosting;
using Microsoft.Scripting.Hosting;
using System.Collections.Generic;

namespace ChatbotVisualInterface.Connectors
{
    /// <summary>
    /// Container for iron python script runner engine, connected to the text-processing layer
    /// </summary>
    public class IronPythonCaller
    {
        private readonly ScriptEngine engine;
        private readonly ScriptSource source;
        private readonly ScriptScope scope;
        private readonly dynamic text_processing_layer;

        /// <summary>
        /// Constructor sets up connection to the python script
        /// </summary>
        /// <param name="window">Where the answer is displayed on completion</param>
        public IronPythonCaller()
        {
            engine = Python.CreateEngine();

            // Where python libraries are stored
            var sarchPaths = new List<string>
            {
                @"..\..\..\ChatbotVisualInterface\lib\",
                @"..\..\..\TextProcessingLayer\",
                @"..\..\..\TextProcessingLayer\ChatbotPythonAppEnv\Lib\site-packages\"
            };
            engine.SetSearchPaths(sarchPaths);

            // The python script itself
            source = engine.CreateScriptSourceFromFile(@"..\..\..\TextProcessingLayer\TextProcessingLayer.py");
            scope = engine.CreateScope();
            source.Execute(scope);

            // Save function upon build
            text_processing_layer = scope.GetVariable("text_processing_layer");
        }

        /// <summary>
        /// Send question to script
        /// </summary>
        /// <returns>The answer as an html-style formated string</returns>
        public string ProcessScript(string question)
        {
            var ans = (string)text_processing_layer(question);
            return ans;
        }
    }
}
