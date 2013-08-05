using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FreeHC
{
    public static class Baseline
    {
        public static double baselinefixandscaleex(ref double[] data, int start, int cnt, bool scale = false)
        {
            double y = data[0];
            double mi = +100000;
            double ma = -100000;
            for (int i = start; (i < start + cnt) && (i < data.Length); i++)
            {
                y = y + data[i];
                mi = Math.Min(mi, data[i]);
                ma = Math.Max(ma, data[i]);
            }
            y = y / cnt;
            double aScale = 150 / Math.Abs(ma - mi);
            for (int i = start; (i < start + cnt) && (i < data.Length); i++)
            {
                // baseline fix
                data[i] = data[i] - y;
                // scaling stört ...
                if (scale)
                {
                    //data[i] = (data[i] / Math.Abs(ma - mi)) * 150; // scale to -150..+150
                    data[i] = (data[i] * aScale); // scale to -150..+150
                }
            }
            return aScale;
        }

        public static double baselinefixandscale(ref double[] data)
        {
            for (int ix = 0; ix < data.Length; ix++)
            {
                if (data[ix] > 10000) data[ix] = 10000;
                if (data[ix] < -10000) data[ix] = -10000;
            }
            int iv = 512;
            int i = 0;
            double aScale = 0;
            while (i < data.Length)
            {
                int mc = Math.Min(iv, data.Length - i);
                aScale = baselinefixandscaleex(ref data, i, mc);
                i += iv;
            }
            return aScale;
        }
    }
}
