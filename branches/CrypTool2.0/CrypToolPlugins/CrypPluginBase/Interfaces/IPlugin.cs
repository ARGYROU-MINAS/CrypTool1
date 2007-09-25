using System;

namespace CrypTool.PluginBase
{
    public interface IPlugin
    {
        void Initialize();
        void Dispose();
    }
}
