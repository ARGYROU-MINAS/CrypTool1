//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.312
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
    /// DlgHash
    /// </summary>
    public partial class DlgHash : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        internal System.Windows.Controls.TextBox textBoxMD5;
        
        internal System.Windows.Controls.Button button1;
        
        internal System.Windows.Controls.Label labelMD5;
        
        internal System.Windows.Controls.Button buttonShowFileMD5;
        
        internal System.Windows.Controls.Button buttonShowFileSHA1;
        
        internal System.Windows.Controls.Button buttonShowFileSHA256;
        
        internal System.Windows.Controls.Button buttonShowFileSHA384;
        
        internal System.Windows.Controls.Button buttonShowFileSHA512;
        
        internal System.Windows.Controls.TextBox textBoxSHA1;
        
        internal System.Windows.Controls.TextBox textBoxSHA256;
        
        internal System.Windows.Controls.TextBox textBoxSHA384;
        
        internal System.Windows.Controls.TextBox textBox1SHA512;
        
        internal System.Windows.Controls.Label labelSHA1;
        
        internal System.Windows.Controls.Label labelSHA256;
        
        internal System.Windows.Controls.Label labelSHA384;
        
        internal System.Windows.Controls.Label labelSHA512;
        
        internal System.Windows.Controls.Button buttonShowAllInFiles;
        
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
            System.Uri resourceLocater = new System.Uri("/GUI;component/dlghash.xaml", System.UriKind.Relative);
            System.Windows.Application.LoadComponent(this, resourceLocater);
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.textBoxMD5 = ((System.Windows.Controls.TextBox)(target));
            return;
            case 2:
            this.button1 = ((System.Windows.Controls.Button)(target));
            
            #line 7 "..\..\DlgHash.xaml"
            this.button1.Click += new System.Windows.RoutedEventHandler(this.OnButtonClose);
            
            #line default
            #line hidden
            return;
            case 3:
            this.labelMD5 = ((System.Windows.Controls.Label)(target));
            return;
            case 4:
            this.buttonShowFileMD5 = ((System.Windows.Controls.Button)(target));
            
            #line 9 "..\..\DlgHash.xaml"
            this.buttonShowFileMD5.Click += new System.Windows.RoutedEventHandler(this.ButtonShowFileMD5_OnClick);
            
            #line default
            #line hidden
            return;
            case 5:
            this.buttonShowFileSHA1 = ((System.Windows.Controls.Button)(target));
            
            #line 10 "..\..\DlgHash.xaml"
            this.buttonShowFileSHA1.Click += new System.Windows.RoutedEventHandler(this.ButtonShowFileSHA1_OnClick);
            
            #line default
            #line hidden
            return;
            case 6:
            this.buttonShowFileSHA256 = ((System.Windows.Controls.Button)(target));
            
            #line 11 "..\..\DlgHash.xaml"
            this.buttonShowFileSHA256.Click += new System.Windows.RoutedEventHandler(this.ButtonShowFileSHA256_OnClick);
            
            #line default
            #line hidden
            return;
            case 7:
            this.buttonShowFileSHA384 = ((System.Windows.Controls.Button)(target));
            
            #line 12 "..\..\DlgHash.xaml"
            this.buttonShowFileSHA384.Click += new System.Windows.RoutedEventHandler(this.ButtonShowFileSHA384_OnClick);
            
            #line default
            #line hidden
            return;
            case 8:
            this.buttonShowFileSHA512 = ((System.Windows.Controls.Button)(target));
            
            #line 13 "..\..\DlgHash.xaml"
            this.buttonShowFileSHA512.Click += new System.Windows.RoutedEventHandler(this.ButtonShowFileSHA512_OnClick);
            
            #line default
            #line hidden
            return;
            case 9:
            this.textBoxSHA1 = ((System.Windows.Controls.TextBox)(target));
            return;
            case 10:
            this.textBoxSHA256 = ((System.Windows.Controls.TextBox)(target));
            return;
            case 11:
            this.textBoxSHA384 = ((System.Windows.Controls.TextBox)(target));
            return;
            case 12:
            this.textBox1SHA512 = ((System.Windows.Controls.TextBox)(target));
            return;
            case 13:
            this.labelSHA1 = ((System.Windows.Controls.Label)(target));
            return;
            case 14:
            this.labelSHA256 = ((System.Windows.Controls.Label)(target));
            return;
            case 15:
            this.labelSHA384 = ((System.Windows.Controls.Label)(target));
            return;
            case 16:
            this.labelSHA512 = ((System.Windows.Controls.Label)(target));
            return;
            case 17:
            this.buttonShowAllInFiles = ((System.Windows.Controls.Button)(target));
            
            #line 22 "..\..\DlgHash.xaml"
            this.buttonShowAllInFiles.Click += new System.Windows.RoutedEventHandler(this.ButtonShowAllInFiles_OnClick);
            
            #line default
            #line hidden
            return;
            }
            this._contentLoaded = true;
        }
    }
}
