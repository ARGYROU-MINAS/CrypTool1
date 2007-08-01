using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;
using System.Collections;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace CrypTool.AppLogic
{
    public class AlphabetHighlighter
    {
        // Search word start
        private static readonly Regex regExWordStart = new Regex(
            @"\w",
            RegexOptions.Compiled | RegexOptions.RightToLeft);

        // Search word end
        private static readonly Regex regExWordEnd = new Regex(
            @"\w",
            RegexOptions.Compiled);

        private string[] alphabetKeywords;
        private Hashtable alphKkeywordHash;
        private Color alphKeywordColor = Color.Black;
        private Color nonAlphKeyWordColor = Color.LightSlateGray;
        private RichTextBox richTextBox;
        private RichTextBoxUpdater updater = new RichTextBoxUpdater();

        //Save the selection when changing the text
        private int updating;
        private int selectionStart;
        private int selectionLength;
        private Color selectionColor;

        /// <summary>
        /// String array containing the alphabet keywords
        /// </summary>
        /// <value></value>
        public string[] AlphKeywords
        {
            get { return alphabetKeywords; }
            set
            {
                if (alphabetKeywords != value)
                {
                    alphabetKeywords = value;
                    alphKkeywordHash = null;
                }
            }
        }

        // Hashtable containing keywords for faster loop
        protected Hashtable AlphKeywordHash
        {
            get
            {
                if (alphKkeywordHash == null)
                {
                    alphKkeywordHash = BuildAlphKeywordHash(alphabetKeywords);
                }
                return alphKkeywordHash;
            }
        }

        private Hashtable BuildAlphKeywordHash(string[] alphKeywords)
        {
            Hashtable hashTable = new Hashtable();
            foreach (string k in alphKeywords)
            {
                hashTable[k] = null;
            }
            return hashTable;
        }

        /// <summary>
        /// RichTextBox Instance
        /// </summary>
        /// <value></value>
        public RichTextBox RichTextBox
        {
            get { return richTextBox; }
            set { richTextBox = value; }
        }

        /// <summary>
        /// Hightlighting a character at the index
        /// </summary>
        /// <remarks>
        /// The word before the index (which can be a character before the word)
        /// will be searched.
        /// </remarks>
        /// <param name="index">Character position in RichTextBox</param>
        public void HilightAt(int index)
        {

            // The whole text
            string text = RichTextBox.Text;

            // detect word beginning
            int wordStart = index;
            Match m = regExWordStart.Match(text, index);
            if (m.Success)
            {
                wordStart = m.Index;
            }

            // detect word end
            int wordEnd = index - 1;
            m = regExWordEnd.Match(text, wordStart);
            if (m.Success)
            {
                wordEnd = m.Index;
            }

            // detect word length
            int wordLength = wordEnd - wordStart + 1;
            if (wordLength == 0) return;

            // the word at index
            string word = text.Substring(wordStart, wordLength);

            // get the text color
            bool isKeyword = AlphKeywordHash.ContainsKey(word);
            Color wordColor;
            if(isKeyword)
                wordColor = alphKeywordColor;
            else
                wordColor = nonAlphKeyWordColor;

            BeginUpdate();

            // change text color
            RichTextBox.SelectionStart = wordStart;
            RichTextBox.SelectionLength = wordLength;
            RichTextBox.SelectionColor = wordColor;

            // special if word is splitted by hyphenate
            // not necessary here by char
            bool wordSplit = index < text.Length &&
                index - 2 == wordEnd &&
                Char.IsLetterOrDigit(text[index]);
            if (wordSplit)
            {
                HilightAt(index + 1);
            }

            EndUpdate();
        }

        /// <summary>
        /// hightlicht all alphabet keyword in the text
        /// </summary>
        public void Hilight()
        {
            // TODO
        }

        // ensure the selection and disable richtextbox update
        private void BeginUpdate()
        {
            updating++;
            if (updating > 1) return;

            // store the selection
            selectionStart = RichTextBox.SelectionStart;
            selectionLength = RichTextBox.SelectionLength;
            selectionColor = RichTextBox.SelectionColor;

            // redraw and disable events
            this.updater.BeginUpdate(RichTextBox);
        }

        // get the previous selection and activate update of richtextbox
        private void EndUpdate()
        {
            updating--;
            if (updating > 0) return;

            // get selection 
            RichTextBox.SelectionLength = selectionLength;
            RichTextBox.SelectionStart = selectionStart;
            RichTextBox.SelectionColor = selectionColor;

            // Redraw and activate events
            this.updater.EndUpdate(RichTextBox);
            RichTextBox.Invalidate();
        }
    }

    /// <summary>
    /// Makes it possible to deactivate Redraw and events in richtextbox
    /// when changing text
    /// </summary>
    /// <remarks>
    /// Source: Pete's Weblog - Extending RichTextBox, Part I
    /// http://geekswithblogs.net/pvidler/archive/2003/10/14/182.aspx
    /// </remarks>
    class RichTextBoxUpdater
    {

        private const int EM_SETEVENTMASK = 1073;
        private const int WM_SETREDRAW = 11;

        private int updating;
        private int oldEventMask;

        /// <summary>
        /// Deactivate redraw and events
        /// </summary>
        /// <param name="rtb"></param>
        public void BeginUpdate(RichTextBox rtb)
        {

            // Deal with nested calls.
            updating++;
            if (updating > 1) return;

            // Prevent the control from raising any events.
            oldEventMask = SendMessage(
                new HandleRef(rtb, rtb.Handle),
                EM_SETEVENTMASK, 0, 0);

            // Prevent the control from redrawing itself.
            SendMessage(
                new HandleRef(rtb, rtb.Handle),
                WM_SETREDRAW, 0, 0);
        }

        /// <summary>
        /// activate redraw and events
        /// </summary>
        /// <param name="rtb"></param>
        public void EndUpdate(RichTextBox rtb)
        {

            // Deal with nested calls.
            updating--;
            if (updating > 0) return;

            // Allow the control to redraw itself.
            SendMessage(
                new HandleRef(rtb, rtb.Handle),
                WM_SETREDRAW, 1, 0);

            // Allow the control to raise event messages.
            SendMessage(
                new HandleRef(rtb, rtb.Handle),
                EM_SETEVENTMASK, 0, oldEventMask);

        }

        [DllImport("user32", CharSet = CharSet.Auto)]
        private static extern int SendMessage(
            HandleRef hWnd,
            int msg,
            int wParam,
            int lParam);
    }
}
