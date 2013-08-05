using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace FreeHC
{
    public class Beater {
        // Messure last 6 beats to call BPM
        DateTime[] Events = new DateTime[8];
        public double BPM = 0;
        public bool Arrhythmia = false;
        public long Beat = 0;

        public void ReCalc()
        {
            // Calculate BPM

            // Calc TimeDiffs
            TimeSpan[] Diffs = new TimeSpan[Events.Count()-1];
            for (int i = 0; i < Events.Count() - 1; i++)
                Diffs[i] = Events[i + 1] - Events[i];

            // Calc. BPMs + Avg. Diff
            double AvgDiff = 0;
            double[] _bpm = new double[Events.Count()-1];
            for (int i = 0; i < Events.Count() - 1; i++)
            {
                AvgDiff = AvgDiff + Diffs[i].TotalMilliseconds;
                _bpm[i] = (60*1000) / Diffs[i].TotalMilliseconds;
            }
            AvgDiff /= Diffs.Count();

            // Calc Average BPM
            double __bpm = 0;
            for (int i = 0; i < _bpm.Count(); i++)
            {
                __bpm += _bpm[i];
            }
            __bpm /= _bpm.Count();
            BPM = __bpm;

            // Detect Arrhythmia
            // Last Avg <> AvgDiff ... Arrythmia
            double ad = (AvgDiff / 5); //
            Arrhythmia = Math.Abs(AvgDiff - Diffs[Diffs.Count() - 1].TotalMilliseconds) > ad;
            //if (Arrhythmia)
            //{
            //    Debug.WriteLine("Arrythmia detected");
            //}
        }

        public void register_end()
        {
        }

        public void register_start()
        {
            Beat++;
            // Shift Everthing
            for (int i = 0; i < Events.Count() - 1; i++)
                Events[i] = Events[i + 1];
            // Set LAst Event
            Events[Events.Count()-1] = DateTime.Now;
            ReCalc();

        }

    }
}
