//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.832
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
    /// DlgKeySymModern
    /// </summary>
    public partial class DlgKeySymModern : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        internal System.Windows.Controls.Label label2;
        
        internal System.Windows.Controls.ComboBox comboBoxKeyLen;
        
        internal System.Windows.Controls.Label label3;
        
        internal System.Windows.Controls.Button buttonEncrypt;
        
        internal System.Windows.Controls.Button buttonDecrypt;
        
        internal System.Windows.Controls.Button buttonCancel;
        
        internal System.Windows.Controls.TextBox textBoxKey;
        
        internal System.Windows.Controls.GroupBox groupBoxCryptographicAlgorithm;
        
        internal System.Windows.Controls.ComboBox comboBoxAlgTitle;
        
        internal System.Windows.Controls.TextBox textBoxRounds;
        
        internal System.Windows.Controls.ComboBox comboBoxPadding;
        
        internal System.Windows.Controls.Label label1;
        
        internal System.Windows.Controls.Label label4;
        
        internal System.Windows.Controls.GroupBox groupBoxInitializationVector;
        
        internal System.Windows.Controls.RadioButton radioButtonDefault;
        
        internal System.Windows.Controls.RadioButton radioButtonManual;
        
        internal System.Windows.Controls.RadioButton radioButtonInternalRandomNumberGen;
        
        internal System.Windows.Controls.Button buttonGetIV;
        
        internal System.Windows.Controls.TextBox textBoxIV;
        
        internal System.Windows.Controls.GroupBox groupBoxKey;
        
        internal System.Windows.Controls.GroupBox groupBoxInfo;
        
        internal System.Windows.Controls.TextBox textBoxInfo;
        
        internal System.Windows.Controls.ComboBox comboBoxCipherMode;
        
        internal System.Windows.Controls.Label label5;
        
        internal System.Windows.Controls.ComboBox comboBoxKeyInputMethod;
        
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
            System.Uri resourceLocater = new System.Uri("/GUI;component/dlgkeysymmodern.xaml", System.UriKind.Relative);
            System.Windows.Application.LoadComponent(this, resourceLocater);
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.label2 = ((System.Windows.Controls.Label)(target));
            return;
            case 2:
            this.comboBoxKeyLen = ((System.Windows.Controls.ComboBox)(target));
            return;
            case 3:
            this.label3 = ((System.Windows.Controls.Label)(target));
            return;
            case 4:
            this.buttonEncrypt = ((System.Windows.Controls.Button)(target));
            
            #line 9 "..\..\DlgKeySymModern.xaml"
            this.buttonEncrypt.Click += new System.Windows.RoutedEventHandler(this.Encrypt);
            
            #line default
            #line hidden
            return;
            case 5:
            this.buttonDecrypt = ((System.Windows.Controls.Button)(target));
            
            #line 10 "..\..\DlgKeySymModern.xaml"
            this.buttonDecrypt.Click += new System.Windows.RoutedEventHandler(this.Decrypt);
            
            #line default
            #line hidden
            return;
            case 6:
            this.buttonCancel = ((System.Windows.Controls.Button)(target));
            
            #line 11 "..\..\DlgKeySymModern.xaml"
            this.buttonCancel.Click += new System.Windows.RoutedEventHandler(this.Cancel);
            
            #line default
            #line hidden
            return;
            case 7:
            this.textBoxKey = ((System.Windows.Controls.TextBox)(target));
            return;
            case 8:
            this.groupBoxCryptographicAlgorithm = ((System.Windows.Controls.GroupBox)(target));
            return;
            case 9:
            this.comboBoxAlgTitle = ((System.Windows.Controls.ComboBox)(target));
            
            #line 14 "..\..\DlgKeySymModern.xaml"
            this.comboBoxAlgTitle.SelectionChanged += new System.Windows.Controls.SelectionChangedEventHandler(this.setAlgID);
            
            #line default
            #line hidden
            return;
            case 10:
            this.textBoxRounds = ((System.Windows.Controls.TextBox)(target));
            return;
            case 11:
            this.comboBoxPadding = ((System.Windows.Controls.ComboBox)(target));
            return;
            case 12:
            this.label1 = ((System.Windows.Controls.Label)(target));
            return;
            case 13:
            this.label4 = ((System.Windows.Controls.Label)(target));
            return;
            case 14:
            this.groupBoxInitializationVector = ((System.Windows.Controls.GroupBox)(target));
            return;
            case 15:
            this.radioButtonDefault = ((System.Windows.Controls.RadioButton)(target));
            
            #line 21 "..\..\DlgKeySymModern.xaml"
            this.radioButtonDefault.Click += new System.Windows.RoutedEventHandler(this.getDefaultIV);
            
            #line default
            #line hidden
            return;
            case 16:
            this.radioButtonManual = ((System.Windows.Controls.RadioButton)(target));
            
            #line 22 "..\..\DlgKeySymModern.xaml"
            this.radioButtonManual.Click += new System.Windows.RoutedEventHandler(this.getManualIV);
            
            #line default
            #line hidden
            return;
            case 17:
            this.radioButtonInternalRandomNumberGen = ((System.Windows.Controls.RadioButton)(target));
            
            #line 23 "..\..\DlgKeySymModern.xaml"
            this.radioButtonInternalRandomNumberGen.Click += new System.Windows.RoutedEventHandler(this.getInternalRandomIV);
            
            #line default
            #line hidden
            return;
            case 18:
            this.buttonGetIV = ((System.Windows.Controls.Button)(target));
            
            #line 25 "..\..\DlgKeySymModern.xaml"
            this.buttonGetIV.Click += new System.Windows.RoutedEventHandler(this.getInternalRandomIV);
            
            #line default
            #line hidden
            return;
            case 19:
            this.textBoxIV = ((System.Windows.Controls.TextBox)(target));
            return;
            case 20:
            this.groupBoxKey = ((System.Windows.Controls.GroupBox)(target));
            return;
            case 21:
            this.groupBoxInfo = ((System.Windows.Controls.GroupBox)(target));
            return;
            case 22:
            this.textBoxInfo = ((System.Windows.Controls.TextBox)(target));
            return;
            case 23:
            this.comboBoxCipherMode = ((System.Windows.Controls.ComboBox)(target));
            return;
            case 24:
            this.label5 = ((System.Windows.Controls.Label)(target));
            return;
            case 25:
            this.comboBoxKeyInputMethod = ((System.Windows.Controls.ComboBox)(target));
            return;
            }
            this._contentLoaded = true;
        }
    }
}
