//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.42
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;


namespace CrypTool {
    
    
    /// <summary>
    /// DlgMain
    /// </summary>
    public partial class DlgMain : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        internal System.Windows.Controls.Menu Menu;
        
        internal System.Windows.Controls.MenuItem MenuItemFile;
        
        internal System.Windows.Controls.MenuItem MenuItemQuit;
        
        internal System.Windows.Controls.MenuItem MenuItemEncryption;
        
        internal System.Windows.Controls.MenuItem MenuItemSymetricClass;
        
        internal System.Windows.Controls.MenuItem MenuItemCaesarRot13;
        
        internal System.Windows.Controls.MenuItem Options;
        
        internal System.Windows.Controls.MenuItem TextOptions;
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/GUI;component/dlgmain.xaml", System.UriKind.Relative);
            System.Windows.Application.LoadComponent(this, resourceLocater);
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.Menu = ((System.Windows.Controls.Menu)(target));
            return;
            case 2:
            this.MenuItemFile = ((System.Windows.Controls.MenuItem)(target));
            return;
            case 3:
            this.MenuItemQuit = ((System.Windows.Controls.MenuItem)(target));
            
            #line 9 "..\..\DlgMain.xaml"
            this.MenuItemQuit.Click += new System.Windows.RoutedEventHandler(this.CloseDlgMain);
            
            #line default
            #line hidden
            return;
            case 4:
            this.MenuItemEncryption = ((System.Windows.Controls.MenuItem)(target));
            return;
            case 5:
            this.MenuItemSymetricClass = ((System.Windows.Controls.MenuItem)(target));
            return;
            case 6:
            this.MenuItemCaesarRot13 = ((System.Windows.Controls.MenuItem)(target));
            
            #line 13 "..\..\DlgMain.xaml"
            this.MenuItemCaesarRot13.Click += new System.Windows.RoutedEventHandler(this.ShowDlgCaesarRot13);
            
            #line default
            #line hidden
            return;
            case 7:
            this.Options = ((System.Windows.Controls.MenuItem)(target));
            return;
            case 8:
            this.TextOptions = ((System.Windows.Controls.MenuItem)(target));
            
            #line 17 "..\..\DlgMain.xaml"
            this.TextOptions.Click += new System.Windows.RoutedEventHandler(this.ShowDlgTextOptions);
            
            #line default
            #line hidden
            return;
            }
            this._contentLoaded = true;
        }
    }
}
