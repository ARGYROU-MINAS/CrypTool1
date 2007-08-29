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
            this.components = new System.ComponentModel.Container();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPagePlainText = new System.Windows.Forms.TabPage();
            this.richTextBoxPlaintext = new System.Windows.Forms.RichTextBox();
            this.contextMenuRichTextBoxPlain = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.menuItemUndo = new System.Windows.Forms.ToolStripMenuItem();
            this.redoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.cutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.copyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pasteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.deleteToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
            this.selectAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Icon = new System.Drawing.Icon("images\\idr_main.ico");
            this.tabControl1.SuspendLayout();
            this.tabPagePlainText.SuspendLayout();
            this.contextMenuRichTextBoxPlain.SuspendLayout();
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Move += new System.EventHandler(DlgEditor_Move);
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
            this.tabControl1.ShowToolTips = true;
            this.tabControl1.Selecting += new System.Windows.Forms.TabControlCancelEventHandler(tabControl1_Selecting);
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
            this.richTextBoxPlaintext.ContextMenuStrip = this.contextMenuRichTextBoxPlain;
            this.richTextBoxPlaintext.Font = new System.Drawing.Font("Arial", 10);
            this.richTextBoxPlaintext.Dock = System.Windows.Forms.DockStyle.Fill;
            this.richTextBoxPlaintext.Location = new System.Drawing.Point(3, 3);
            this.richTextBoxPlaintext.Name = "richTextBoxPlaintext";
            this.richTextBoxPlaintext.Size = new System.Drawing.Size(570, 348);
            this.richTextBoxPlaintext.TabIndex = 0;
            this.richTextBoxPlaintext.Text = "";
            this.richTextBoxPlaintext.TextChanged += new System.EventHandler(this.richTextBoxPlaintext_TextChanged);
            // 
            // contextMenuRichTextBoxPlain
            // 
            this.contextMenuRichTextBoxPlain.BindingContext = null;
            this.contextMenuRichTextBoxPlain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuItemUndo,
            this.redoToolStripMenuItem,
            this.toolStripMenuItem1,
            this.cutToolStripMenuItem,
            this.copyToolStripMenuItem,
            this.pasteToolStripMenuItem,
            this.deleteToolStripMenuItem,
            this.toolStripMenuItem2,
            this.selectAllToolStripMenuItem});
            this.contextMenuRichTextBoxPlain.Name = "contextMenuRichTextBoxPlain";
            this.contextMenuRichTextBoxPlain.Region = null;
            this.contextMenuRichTextBoxPlain.Size = new System.Drawing.Size(153, 192);
            this.contextMenuRichTextBoxPlain.Opening += new System.ComponentModel.CancelEventHandler(this.contextMenuRichTextBoxPlain_Opening);
            // 
            // menuItemUndo
            // 
            this.menuItemUndo.Name = "menuItemUndo";
            this.menuItemUndo.Size = new System.Drawing.Size(152, 22);
            this.menuItemUndo.Text = "Undo";
            this.menuItemUndo.Click += new System.EventHandler(this.menuItemUndo_Click);
            // 
            // redoToolStripMenuItem
            // 
            this.redoToolStripMenuItem.Name = "redoToolStripMenuItem";
            this.redoToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.redoToolStripMenuItem.Text = "Redo";
            this.redoToolStripMenuItem.Click += new System.EventHandler(this.redoToolStripMenuItem_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(149, 6);
            // 
            // cutToolStripMenuItem
            // 
            this.cutToolStripMenuItem.Name = "cutToolStripMenuItem";
            this.cutToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.cutToolStripMenuItem.Text = "Cut";
            this.cutToolStripMenuItem.Click += new System.EventHandler(this.cutToolStripMenuItem_Click);
            // 
            // copyToolStripMenuItem
            // 
            this.copyToolStripMenuItem.Name = "copyToolStripMenuItem";
            this.copyToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.copyToolStripMenuItem.Text = "Copy";
            this.copyToolStripMenuItem.Click += new System.EventHandler(this.copyToolStripMenuItem_Click);
            // 
            // pasteToolStripMenuItem
            // 
            this.pasteToolStripMenuItem.Name = "pasteToolStripMenuItem";
            this.pasteToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.pasteToolStripMenuItem.Text = "Paste";
            this.pasteToolStripMenuItem.Click += new System.EventHandler(this.pasteToolStripMenuItem_Click);
            // 
            // deleteToolStripMenuItem
            // 
            this.deleteToolStripMenuItem.Name = "deleteToolStripMenuItem";
            this.deleteToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.deleteToolStripMenuItem.Text = "Delete";
            this.deleteToolStripMenuItem.Click += new System.EventHandler(this.deleteToolStripMenuItem_Click);
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(149, 6);
            // 
            // selectAllToolStripMenuItem
            // 
            this.selectAllToolStripMenuItem.Name = "selectAllToolStripMenuItem";
            this.selectAllToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.selectAllToolStripMenuItem.Text = "Select All";
            this.selectAllToolStripMenuItem.Click += new System.EventHandler(this.selectAllToolStripMenuItem_Click);
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
            this.contextMenuRichTextBoxPlain.ResumeLayout(false);
            this.ResumeLayout(false);

        }
        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPagePlainText;
        private System.Windows.Forms.RichTextBox richTextBoxPlaintext;
        private System.Windows.Forms.ContextMenuStrip contextMenuRichTextBoxPlain;
        private System.Windows.Forms.ToolStripMenuItem menuItemUndo;
        private System.Windows.Forms.ToolStripMenuItem redoToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem cutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem copyToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pasteToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem deleteToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem selectAllToolStripMenuItem;
    }
}