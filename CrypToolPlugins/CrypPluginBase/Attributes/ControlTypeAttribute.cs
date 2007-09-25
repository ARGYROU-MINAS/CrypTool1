using System;

namespace CrypTool.PluginBase
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ControlTypeAttribute : Attribute
    {
        public readonly ControlType ControlType;
        public readonly bool Enabled;
        public readonly string CaptionID;
        public readonly object DefaultValue;
        public readonly string RegularExpression;
        public readonly string[] ControlValues;

        public ControlTypeAttribute(ControlType controlType, bool enabled, string captionID, object defaultValue, string regularExpression, string[] controlValues)
        {
            this.ControlType = controlType;
            this.Enabled = enabled;
            this.CaptionID = captionID;
            this.DefaultValue = defaultValue;
            this.RegularExpression = regularExpression;
            this.ControlValues = controlValues;
        }
    }
}
