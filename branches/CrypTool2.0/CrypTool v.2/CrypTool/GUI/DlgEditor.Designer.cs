namespace CrypTool
{
    partial class DlgEditor
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPagePlainText = new System.Windows.Forms.TabPage();
            this.richTextBoxPlaintext = new System.Windows.Forms.RichTextBox();
            this.tabControl1.SuspendLayout();
            this.tabPagePlainText.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPagePlainText);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(584, 380);
            this.tabControl1.TabIndex = 1;
            // 
            // tabPagePlainText
            // 
            this.tabPagePlainText.Controls.Add(this.richTextBoxPlaintext);
            this.tabPagePlainText.Location = new System.Drawing.Point(4, 22);
            this.tabPagePlainText.Name = "tabPagePlainText";
            this.tabPagePlainText.Padding = new System.Windows.Forms.Padding(3);
            this.tabPagePlainText.Size = new System.Drawing.Size(576, 354);
            this.tabPagePlainText.TabIndex = 0;
            this.tabPagePlainText.Text = "Plaintext";
            this.tabPagePlainText.UseVisualStyleBackColor = true;
            // 
            // richTextBoxPlaintext
            // 
            this.richTextBoxPlaintext.Dock = System.Windows.Forms.DockStyle.Fill;
            this.richTextBoxPlaintext.Location = new System.Drawing.Point(3, 3);
            this.richTextBoxPlaintext.Name = "richTextBoxPlaintext";
            this.richTextBoxPlaintext.Size = new System.Drawing.Size(570, 348);
            this.richTextBoxPlaintext.TabIndex = 0;
            this.richTextBoxPlaintext.Text = "";
            this.richTextBoxPlaintext.TextChanged += new System.EventHandler(this.richTextBoxPlaintext_TextChanged);
            // 
            // DlgEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(584, 380);
            this.Controls.Add(this.tabControl1);
            this.Name = "DlgEditor";
            this.Text = "DlgEditor";
            this.Activated += new System.EventHandler(this.DlgEditor_Activated);
            this.tabControl1.ResumeLayout(false);
            this.tabPagePlainText.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPagePlainText;
        private System.Windows.Forms.RichTextBox richTextBoxPlaintext;
    }
}