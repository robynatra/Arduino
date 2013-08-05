using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Media;
using System.Diagnostics;

namespace FreeHC
{
    public struct Olimexino328_packet
    {
        public byte sync0;		// = 0xa5
        public byte sync1;		// = 0x5a
        public byte version;	// = 2 (packet version)
        public byte count;		// packet counter. Increases by 1 each packet.
        public UInt16 d1;	// 10-bit sample (= 0 - 1023) in big endian (Motorola) format.
        public UInt16 d2;	// 10-bit sample (= 0 - 1023) in big endian (Motorola) format.
        public UInt16 d3;	// 10-bit sample (= 0 - 1023) in big endian (Motorola) format.
        public UInt16 d4;	// 10-bit sample (= 0 - 1023) in big endian (Motorola) format.
        public UInt16 d5;	// 10-bit sample (= 0 - 1023) in big endian (Motorola) format.
        public UInt16 d6;	// 10-bit sample (= 0 - 1023) in big endian (Motorola) format.
        public byte switches;	// State of PD5 to PD2, in bits 3 to 0.
    };

    public partial class RealTimeFilterView : UserControl
    {
        Timer RePaintTimer = null;
        const int icnt = 512; // signal count
        public string Caption = "[Untitled]";
        public int Channel = 0;
        public bool Active = false;
        public double[] Data = new double[icnt];
        public Color[] DataColor = new Color[icnt];


        public int butterworth_level = 1;

        public bool butterworth_use_lp = true;
        public int butterworth_freqlp = 170;
        public int butterworth_powerlp =  20;

        public bool butterworth_use_hp = true;
        public int butterworth_freqhp = 3;
        public int butterworth_powerhp =  57;

        public int haar_level = 0;
        public int db6_level = 0;

        public double scale = 0.35;

        public double Beat_Level1 = 0.84;
        public double Beat_Level2 = 0.35;
        public int Beat_Level1C = 6;
        public int Beat_Level2C = 8;
        public int beat_Width = 30;

        public RealTimeViewEditor editor = new RealTimeViewEditor();
        public bool beat = false;
        public Beater fBeater = new Beater();
        public bool AudioBeat = false;
        public int displaybeat = 0;
        public int _NormalHeight = -1;
        public bool EnterDiagnosticMode = false; // directly enter DiagnosticMode
        public int _DiagnosticExtraHeight = 200;
        public Diagnostics diag = new Diagnostics();

        private bool _DiagnosticMode = false;
        public bool DiagnosticMode {
            get
            {
                return _DiagnosticMode;
            }
            set
            {
                if (_DiagnosticMode != value)
                {
                    _DiagnosticMode = value;
                    if (value)
                    {
                        Height = _NormalHeight + _DiagnosticExtraHeight;
                        Parent.Height = _NormalHeight + _DiagnosticExtraHeight;
                    }
                    else
                    {
                        Height = _NormalHeight;
                        Parent.Height = _NormalHeight;
                    }
                }
            }
        }

        public void Pop(UInt16 b)
        {
            // shift Left
            for (int i = 0; i < Data.Length-1; i++)
            {
                Data[i] = Data[i+1];
                DataColor[i] = DataColor[i + 1];
            }
            // add new value
            Data[Data.Length-1] = -b * scale;
            DataColor[Data.Length - 1] = Color.White;
        }

        long Frame = 0;

        public RealTimeFilterView()
        {
            InitializeComponent();
            for (int i = 0; i < icnt; i++) Data[i] = 0;
            RePaintTimer = new Timer();
            RePaintTimer.Interval = 1000 / 20; // 10 fps should be ok ...
            RePaintTimer.Tick += new EventHandler(RePaintTimer_Tick);
            RePaintTimer.Enabled = true;
            editor.rtfv = this;
        }

        void RePaintTimer_Tick(object sender, EventArgs e)
        {            Invalidate();

        }

        // anti flicker
        protected override CreateParams CreateParams
        {
            get
            {
                CreateParams cp = base.CreateParams;
                cp.ExStyle |= 0x02000000;  // Turn on WS_EX_COMPOSITED
                return cp;
            }
        } 

        public static UInt16 ReverseBytes(UInt16 value)
        {
            return (UInt16)((value & 0xFFU) << 8 | (value & 0xFF00U) >> 8);
        }

        private Olimexino328_packet ReadNextPacket(BinaryReader BR, ref int iPosition)
        {
            Olimexino328_packet pk = new Olimexino328_packet();
            pk.sync0 = 0;
            pk.sync1 = 0;
            while ((pk.sync0 != 0xa5) && (pk.sync1 != 0x5a))
            {
                BR.BaseStream.Position = iPosition;
                if (iPosition > BR.BaseStream.Length-3)
                {
                    return pk;
                }
                pk.sync0 = BR.ReadByte();
                pk.sync1 = BR.ReadByte();
                iPosition++;
            }
            pk.version = BR.ReadByte();
            pk.count = BR.ReadByte();
            pk.d1 = ReverseBytes(BR.ReadUInt16());
            pk.d2 = ReverseBytes(BR.ReadUInt16());
            pk.d3 = ReverseBytes(BR.ReadUInt16());
            pk.d4 = ReverseBytes(BR.ReadUInt16());
            pk.d5 = ReverseBytes(BR.ReadUInt16());
            pk.d6 = ReverseBytes(BR.ReadUInt16());
            pk.switches = BR.ReadByte();
            return pk;
        }

        // Simple-Flattening 
        private void ProcessData(ref double[] Data)
        {
            // baseline correction and scaling (-150 ..0.. +150 )
            //baselinefixandscale(ref Data);

            // pre-filter noise
            for (int level = 0; level < butterworth_level; level++)
                ButterWorth.Process(ref Data,
                    butterworth_use_lp, butterworth_freqlp, butterworth_powerlp,
                    butterworth_use_hp, butterworth_freqhp, butterworth_powerhp); // 250, 70);

            // baseline correction and scaling (-150 ..0.. +150 )
            Baseline.baselinefixandscale(ref Data);

            // db6-filtering
            for (int level = 0; level < db6_level; level++)
                DB6.process(ref Data, true);

            // haar-filtering
            for (int level = 0; level < haar_level; level++)
                Haar.process(ref Data);

        }

        private void RealTimeFilterView_Paint(object sender, PaintEventArgs e)
        {
            if (_NormalHeight < 0)
            {
                _NormalHeight = Height;
                if (EnterDiagnosticMode)
                         DiagnosticMode = true;
                return;
            }
            // DoPaint
            double[] Data1 = new double[Data.Length];

            if (Active)
            {
                Data.CopyTo(Data1, 0);
                ProcessData(ref Data1);
            }
            else
            {
                for (int i = 0; i < icnt; i++) Data1[i] = 0;
            }

            Bitmap aBmp = new Bitmap(ClientSize.Width, ClientSize.Height);
            var gb = Graphics.FromImage(aBmp);
            gb.FillRectangle(Brushes.Black, ClientRectangle);
            int cx = (ClientSize.Width / 2) - (icnt / 2);
            SolidBrush br = new SolidBrush(Color.FromArgb(10,10,10));
            gb.FillRectangle(br, cx, 0, icnt, _NormalHeight);
            br.Dispose();
            gb.DrawRectangle(Pens.White, ClientRectangle);
            gb.DrawLine(Pens.White, 0, _NormalHeight, ClientSize.Width, _NormalHeight);
            gb.DrawLine(Pens.LightBlue, cx, 50, cx + icnt, 50);
            gb.DrawLine(Pens.LightGreen, cx - 1, 0, cx - 1, _NormalHeight);
            gb.DrawLine(Pens.LightGreen, cx + icnt, 0, cx + icnt, _NormalHeight);

            int beaty1 = _NormalHeight - (int)(_NormalHeight * Beat_Level1);
            int beaty2 = _NormalHeight - (int)(_NormalHeight * Beat_Level2);
            gb.DrawLine(Pens.Red, cx + icnt - beat_Width, beaty1, cx + icnt, beaty1);
            gb.DrawLine(Pens.Red, cx + icnt - beat_Width, beaty2, cx + icnt, beaty2);

            int ri = 1;
            int beatc1 = 0;
            int beatc2 = 0;
            for (int i = cx; i < cx + icnt; i++)
            {
                // find next packet
                if ((ri < Data1.Length) && (!Double.IsNaN(Data1[ri-1])))
                {
                    int y1 = (int)(Data1[ri - 1] / 3) + 50;
                    int y2 = (int)(Data1[ri] / 3) + 50;
                    Pen p = new Pen(DataColor[ri]);
                    gb.DrawLine(p, i - 1, y1, i, y2);
                    p.Dispose();
                    if ((y2 < beaty1) && (i>cx+icnt-beat_Width))
                    {
                        beatc1++;
                    }
                    if ((y2 > beaty2) && (i > cx + icnt - beat_Width))
                    {
                        beatc2++;
                    }
                }
                ri++;
            }
            SizeF aF = gb.MeasureString("$,", DefaultFont);
            bool aOldBeat = beat;

            beat = (beatc1 > 0) && (beatc1 < Beat_Level1C) && 
                   (beatc2 > 0) && (beatc2 < Beat_Level2C);
            if ((beat) && (!aOldBeat))
            {
                // mark beat ..
                for (int i = 0; i < beat_Width; i++)
                   if (Data[DataColor.Length-i-1] < beaty2)
                    DataColor[DataColor.Length-i-1] = Color.Lime;

                displaybeat = 10;
                fBeater.register_start();

                // Mark Arrhythmia
                if (fBeater.Arrhythmia)
                {
                    if (AudioBeat)
                        SystemSounds.Hand.Play();

                    for (int i = 0; i < beat_Width; i++)
                            DataColor[DataColor.Length - i - 1] = Color.Red;
                }

                if (AudioBeat)
                    SystemSounds.Beep.Play();
            }
            else
            {
                fBeater.register_end();
            }


            gb.DrawString(Caption, DefaultFont, Brushes.White, new PointF(2,2));
            gb.DrawString("Frame: " + Frame.ToString(), DefaultFont, Brushes.White, new PointF(2, 4 + aF.Height));
            gb.DrawString("Active: " + Active.ToString(), DefaultFont, Brushes.White, new PointF(2, 6 + (aF.Height * 2)));
            gb.DrawString("Audio: false", DefaultFont, Brushes.White, new PointF(2, 8+(aF.Height*3)));
            gb.DrawString("Beat", DefaultFont, Brushes.LightGray, new PointF(ClientSize.Width - 30, 17));

            gb.DrawString("BPM", DefaultFont, Brushes.LightGray, new PointF(ClientSize.Width - 60, 2));
            String s = Math.Round(fBeater.BPM).ToString();
            if (Math.Round(fBeater.BPM) > 100) s = "N/A";
            gb.DrawString(s, DefaultFont, Brushes.White, new PointF(ClientSize.Width - 60, 4 + aF.Height));
            if (fBeater.Arrhythmia)
            {
                gb.DrawString("Arrhythmia", DefaultFont, Brushes.Red, new PointF(ClientSize.Width - 60, 6 + (aF.Height * 2)));
            }
            else
            {
                gb.DrawString("Arrhythmia", DefaultFont, Brushes.DarkRed, new PointF(ClientSize.Width - 60, 6 + (aF.Height*2)));
            }

            if (displaybeat > 0)
            {
                displaybeat--;
                gb.FillEllipse(Brushes.Red, new Rectangle(ClientSize.Width - 20, 5, 10, 10));
            }

            if (DiagnosticMode) RunDiagnostics(Data1, DataColor, gb, _NormalHeight);

            Graphics g = e.Graphics;
            g.DrawImage(aBmp, 0, 0, ClientSize.Width, ClientSize.Height);
            aBmp.Dispose();
            if (Active)
                Frame++;
        }

        private void RunDiagnostics(double[] Data, Color[] DataColor, Graphics gb, int sx)
        {
            // Run Diagnostics View
            SolidBrush br = new SolidBrush(Color.FromArgb(10, 10, 10));
            Rectangle clientr = new Rectangle(0, sx, ClientSize.Width, _DiagnosticExtraHeight);
            gb.FillRectangle(br, clientr);
            br.Dispose();
            gb.DrawRectangle(Pens.White, clientr);
            diag.Run(fBeater, Data, DataColor, gb, clientr);
        }

        private void RealTimeFilterView_Load(object sender, EventArgs e)
        {

        }

        private void trackBar1_VisibleChanged(object sender, EventArgs e)
        {

        }

        private void trackBar1_ValueChanged(object sender, EventArgs e)
        {
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {

        }

        private void trackBar2_ValueChanged(object sender, EventArgs e)
        {
        }

        private void trackBar1_ValueChanged_1(object sender, EventArgs e)
        {
        }

        private void trackBar1_Scroll_1(object sender, EventArgs e)
        {

        }
    }
}

