//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.42
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace CrypTool {
    using System;
    using System.Windows.Input;
    using System.Windows.Media.Animation;
    using System.Windows.Controls.Primitives;
    using System.Windows;
    using System.Windows.Data;
    using System.Windows.Navigation;
    using System.Windows.Shapes;
    using System.Windows.Documents;
    using System.Windows.Controls;
    using System.Windows.Media.TextFormatting;
    using System.Windows.Media.Imaging;
    using System.Windows.Media;
    using System.Windows.Media.Media3D;
    using System.Windows.Media.Effects;
    using System.Windows.Automation;
    using System.Windows.Markup;
    
    
    /// <summary>
    /// App
    /// </summary>
    public partial class App : System.Windows.Application {
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        public void InitializeComponent() {
            this.StartupUri = new System.Uri("DlgMain.xaml", System.UriKind.Relative);
        }
        
        /// <summary>
        /// Application Entry Point.
        /// </summary>
        [System.STAThreadAttribute()]
        public static void Main() {
            CrypTool.App app = new CrypTool.App();
            app.InitializeComponent();
            app.Run();
        }
    }
}
