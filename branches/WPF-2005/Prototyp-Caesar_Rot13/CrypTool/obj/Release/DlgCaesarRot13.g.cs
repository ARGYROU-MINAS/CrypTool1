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
    /// DlgCaesarRot13
    /// </summary>
    public partial class DlgCaesarRot13 : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        internal System.Windows.Controls.GroupBox groupBox1;
        
        internal System.Windows.Controls.RadioButton radioButton1;
        
        internal System.Windows.Controls.Label label1;
        
        internal System.Windows.Controls.TextBox textBox1;
        
        internal System.Windows.Controls.Button button1;
        
        internal System.Windows.Controls.GroupBox groupBox2;
        
        internal System.Windows.Controls.Button button2;
        
        internal System.Windows.Controls.Button button3;
        
        internal System.Windows.Controls.Button button4;
        
        internal System.Windows.Controls.Label label2;
        
        internal System.Windows.Controls.Label label3;
        
        internal System.Windows.Controls.Label label4;
        
        internal System.Windows.Controls.Label label5;
        
        internal System.Windows.Controls.TextBox textBox2;
        
        internal System.Windows.Controls.TextBox textBox3;
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("CrypTool;component\\dlgcaesarrot13.baml", System.UriKind.RelativeOrAbsolute);
            System.Windows.Application.LoadComponent(this, resourceLocater);
        }
        
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.groupBox1 = ((System.Windows.Controls.GroupBox)(target));
            return;
            case 2:
            this.radioButton1 = ((System.Windows.Controls.RadioButton)(target));
            return;
            case 3:
            this.label1 = ((System.Windows.Controls.Label)(target));
            return;
            case 4:
            this.textBox1 = ((System.Windows.Controls.TextBox)(target));
            return;
            case 5:
            this.button1 = ((System.Windows.Controls.Button)(target));
            return;
            case 6:
            this.groupBox2 = ((System.Windows.Controls.GroupBox)(target));
            return;
            case 7:
            this.button2 = ((System.Windows.Controls.Button)(target));
            return;
            case 8:
            this.button3 = ((System.Windows.Controls.Button)(target));
            return;
            case 9:
            this.button4 = ((System.Windows.Controls.Button)(target));
            this.button4.Click += new System.Windows.RoutedEventHandler(this.CloseDlgCaesarRot13);
            return;
            case 10:
            this.label2 = ((System.Windows.Controls.Label)(target));
            return;
            case 11:
            this.label3 = ((System.Windows.Controls.Label)(target));
            return;
            case 12:
            this.label4 = ((System.Windows.Controls.Label)(target));
            return;
            case 13:
            this.label5 = ((System.Windows.Controls.Label)(target));
            return;
            case 14:
            this.textBox2 = ((System.Windows.Controls.TextBox)(target));
            return;
            case 15:
            this.textBox3 = ((System.Windows.Controls.TextBox)(target));
            return;
            }
            this._contentLoaded = true;
        }
    }
}
