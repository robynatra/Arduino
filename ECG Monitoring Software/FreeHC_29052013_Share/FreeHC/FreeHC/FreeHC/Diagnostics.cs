using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Diagnostics;
using System.Drawing;

namespace FreeHC
{
    public class Diagnostics
    {
        Bitmap fFrame = new Bitmap(1, 1);

        public void CalcDiag(double[] Data, Color[] DataColor)
        {
            int centerd = Data.Length / 2;
            // Find a Beat
            int beatcnt = 0;
            List<int> beatp = new List<int>();
            bool a = true;
            for (int i = 0; i < Data.Length; i++)
            {
                if (((DataColor[i] == Color.Red) || (DataColor[i] == Color.Lime)) && a)
                {
                    beatp.Add(i);
                    beatcnt++;
                    a = false;
                }

                if ((DataColor[i] != Color.Red) && (DataColor[i] != Color.Lime))
                {
                    a = true;
                }
            }

            // Found 3 beats ...
            if (beatp.Count > 2)
            {
                int len1 = beatp[1] - beatp[0];
                int len2 = beatp[2] - beatp[1];
                int len = (len1 + len2) / 2;
                int lenh = len / 2;
                double[] beatarea = new double[len];
                Color[] bcol = new Color[len];

                // clear
                for (int i = 0; i < len; i++)
                {
                    beatarea[i] = 0;
                    bcol[i] = Color.White;
                }

                // copy
                double[] Data2 = new double[Data.Length];
                Data.CopyTo(Data2, 0);

//                Haar.process(ref Data2);

                for (int i = 0; i < len; i++)
                {
                    int bp = beatp[1] - (lenh / 2) + i;
                    if ((bp > -1) && (bp < Data2.Length))
                        beatarea[i] = Data2[bp];
                }

                // fix and scale (cause of haar)
                // store scale-factor to recalculate Scale/MV
                double usedscale = Baseline.baselinefixandscaleex(ref beatarea, 0, beatarea.Length, true);

                MaxFinder mf = new MaxFinder();

                mf.GetPeaks(beatarea, beatarea.Length/5, false);
                int[] aPeaks = new int[mf._peaks.Count];
                mf._peaks.CopyTo(aPeaks);

                mf.GetPeaks(beatarea, beatarea.Length/3, true);
                int[] aMinPeaks = new int[mf._peaks.Count];
                mf._peaks.CopyTo(aMinPeaks);

                
                // grrgrg  g->r->r->g->r->g
                //              /\     .
                //         _/\_/  \  _/ \_
                //                 \/
                //            p  q  s  t

                string searchword = "grrgrg";
                int[] complex = new int[6] { -1, -1, -1, -1, -1, -1 };
                // enough data?
                if ((aPeaks.Length >= 3) && (aMinPeaks.Length >= 3))
                {
                    // data in correct order ?!
                    
                    string s = "";
                    int[] spos = new int[aPeaks.Length + aMinPeaks.Length];
                    int j = 0;
                    // construct data-string
                    for (int i = 0; i < beatarea.Length; i++)
                    {
                        if (aPeaks.Contains(i))
                        {
                            s += "r";
                            spos[j] = i;
                            j++;
                        }
                        if (aMinPeaks.Contains(i))
                        {
                            s += "g";
                            spos[j] = i;
                        }
                    }
                    // search for searchword data-string
                    if (s.Contains(searchword))
                    {
                        // okay we are having a grrgrg-komplex ... :-)
                        int sw = s.IndexOf(searchword);
                        if (sw > -1)
                        {
                            complex[0] = spos[sw + 0];
                            complex[1] = spos[sw + 1];
                            complex[2] = spos[sw + 2];
                            complex[3] = spos[sw + 3];
                            complex[4] = spos[sw + 4];
                            complex[5] = spos[sw + 5];
                        }
                    }
                }

                // Draw Colored ECG
                Graphics g = Graphics.FromImage(fFrame);
                int scalex = 3;
                g.FillRectangle(Brushes.Black, new Rectangle(0,0,fFrame.Width, fFrame.Height));
                int cx = (fFrame.Width / 2) - ((beatarea.Length * scalex) / 2);
                g.DrawLine(Pens.White, cx, 125, cx+beatarea.Length * scalex, 125);
                for (int i = 0; i < beatarea.Length - 1; i++)
                {
                    int y1 = (int)(beatarea[i]);
                    int y2 = (int)(beatarea[i+1]);
                    Pen pn = new Pen(bcol[i]);
                    g.DrawLine(pn, cx+i * scalex, 125 + y1, cx+(i + 1) * scalex, 125 + y2);
                    pn.Dispose();
                }

                // Draw Maximas
                foreach (int Peak in aPeaks)
                {
                    int y1 = (int)(beatarea[Peak]);
                    g.DrawEllipse(Pens.Red, new Rectangle(cx + Peak * scalex - 3, 125 + y1 -3, 6, 6));
                }

                // Draw Minimas
                foreach (int Peak in aMinPeaks)
                {
                    int y1 = (int)(beatarea[Peak]);
                    g.DrawEllipse(Pens.LimeGreen, new Rectangle(cx + Peak * scalex - 3, 125 + y1 - 3, 6, 6));
                }
                // render complex (-1)
                if (complex[0] != -1)
                {
                    for (int i = 0; i < 6; i++)
                    {
                        g.DrawLine(Pens.White, cx + complex[i] * scalex, 125 - 70,
                                               cx + complex[i] * scalex, 125 + 70);
                    }
                }

                g.Dispose();
            }
        }

        long fLastBeat = 0;
        internal void Run(Beater aBeater, double[] Data, Color[] DataColor, System.Drawing.Graphics gb, System.Drawing.Rectangle clientr)
        {
            // Draw Diagnostic Mode stuff ...
            // run only every 10th heart beat
            if ((aBeater.Beat % 10 == 0) && (fLastBeat != aBeater.Beat))
            {
                fLastBeat = aBeater.Beat;
                if ((fFrame.Width != clientr.Width) || (fFrame.Height != clientr.Height)) {
                    fFrame.Dispose();
                    fFrame = new Bitmap(clientr.Width, clientr.Height, System.Drawing.Imaging.PixelFormat.Format24bppRgb);
                }
                CalcDiag(Data, DataColor);
            }
            gb.DrawImage(fFrame, new Point(0, 100));
        }
    }
}
