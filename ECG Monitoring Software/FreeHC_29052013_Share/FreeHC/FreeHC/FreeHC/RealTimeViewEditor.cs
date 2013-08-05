using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

namespace FreeHC
{
    [DefaultPropertyAttribute("Active")]
    public class RealTimeViewEditor
    {
        public RealTimeFilterView rtfv = null;

        [CategoryAttribute("Channel Settings"), DescriptionAttribute("Generic channel settings")]
        public bool Active { 
            get { return rtfv.Active; }
            set { rtfv.Active = value; } 
        }
        [CategoryAttribute("Channel Settings"), DescriptionAttribute("Generic channel settings")]
        public double Scale
        {
            get { return rtfv.scale; }
            set { rtfv.scale = value; }
        }
        [CategoryAttribute("Channel Settings"), DescriptionAttribute("Generic channel settings")]
        public int Channel
        {
            get { return rtfv.Channel; }
        }
        [CategoryAttribute("Beat Detector"), DescriptionAttribute("0..1 => 0% => 100%, Red Line")]
        public double Beat_LevelHigh
        {
            get { return rtfv.Beat_Level1; }
            set { rtfv.Beat_Level1 = value; }
        }
        [CategoryAttribute("Beat Detector"), DescriptionAttribute("0..1 => 0% => 100%, Red Line")]
        public int Beat_LevelHighLim
        {
            get { return rtfv.Beat_Level1C; }
            set { rtfv.Beat_Level1C = value; }
        }
        [CategoryAttribute("Beat Detector"), DescriptionAttribute("0..1 => 0% => 100%, Red Line")]
        public double Beat_LevelLow
        {
            get { return rtfv.Beat_Level2; }
            set { rtfv.Beat_Level2 = value; }
        }
        [CategoryAttribute("Beat Detector"), DescriptionAttribute("0..1 => 0% => 100%, Red Line")]
        public int Beat_LevelLowLim
        {
            get { return rtfv.Beat_Level2C; }
            set { rtfv.Beat_Level2C = value; }
        }
        [CategoryAttribute("Beat Detector"), DescriptionAttribute("Width in px, Red Line")]
        public int Beat_Width
        {
            get { return rtfv.beat_Width; }
            set { rtfv.beat_Width = value; }
        }
        [CategoryAttribute("Beat Detector"), DescriptionAttribute("Beep?!")]
        public bool Audio
        {
            get { return rtfv.AudioBeat; }
            set { rtfv.AudioBeat = value; }
        }


        [CategoryAttribute("Filter Haar"), DescriptionAttribute("!!! This Filter destroyes the Scale/mv Relation !!!")]
        public int Haar_Level
        {
            get { return rtfv.haar_level; }
            set { rtfv.haar_level = value; }
        }
        /*
        [CategoryAttribute("Filter Daubechies6"), DescriptionAttribute("Generic Filter settings")]
        public int Daubechies6_Level
        {
            get { return rtfv.db6_level; }
            set { rtfv.db6_level = value; }
        }
        */
        [CategoryAttribute("Filter Butterworth"), DescriptionAttribute("Generic Filter settings")]
        public int Butterworth_level
        {
            get { return rtfv.butterworth_level; }
            set { rtfv.butterworth_level = value; }
        }
        [CategoryAttribute("Filter Butterworth"), DescriptionAttribute("Generic Filter settings")]
        public bool Butterworth_UseLP
        {
            get { return rtfv.butterworth_use_lp; }
            set { rtfv.butterworth_use_lp = value; }
        }
        [CategoryAttribute("Filter Butterworth"), DescriptionAttribute("Generic Filter settings")]
        public int Butterworth_FreqLP
        {
            get { return rtfv.butterworth_freqlp; }
            set { rtfv.butterworth_freqlp = value; }
        }
        [CategoryAttribute("Filter Butterworth"), DescriptionAttribute("Generic Filter settings")]
        public int Butterworth_PowerLP
        {
            get { return rtfv.butterworth_powerlp; }
            set { rtfv.butterworth_powerlp = value; }
        }

        [CategoryAttribute("Filter Butterworth"), DescriptionAttribute("Generic Filter settings")]
        public bool Butterworth_UseHP
        {
            get { return rtfv.butterworth_use_hp; }
            set { rtfv.butterworth_use_hp = value; }
        }
        [CategoryAttribute("Filter Butterworth"), DescriptionAttribute("Generic Filter settings")]
        public int Butterworth_FreqHP
        {
            get { return rtfv.butterworth_freqhp; }
            set { rtfv.butterworth_freqhp = value; }
        }
        [CategoryAttribute("Filter Butterworth"), DescriptionAttribute("Generic Filter settings")]
        public int Butterworth_PowerHP
        {
            get { return rtfv.butterworth_powerhp; }
            set { rtfv.butterworth_powerhp = value; }
        }

        [CategoryAttribute("Diagnostic-Mode"), DescriptionAttribute("Diagnostic-Mode Settings")]
        public bool DiagnosticMode
        {
            get { return rtfv.DiagnosticMode; }
            set { rtfv.DiagnosticMode = value; }
        }

    }



}
