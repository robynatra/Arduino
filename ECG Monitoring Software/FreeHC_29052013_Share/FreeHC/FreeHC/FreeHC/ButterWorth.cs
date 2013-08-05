using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SciMark2;

namespace FreeHC
{
    // From : http://www.csce.uark.edu/~jgauch/5683/notes/ch04b.pdf
	public static class ButterWorth
	{

        public static void Process(ref double[] data, bool useLP, double lpfreq, double lppower,
                                                        bool useHP, double hpfreq, double hppower)
        {
            // Perform FFT 
            FFT.transform(data);

            // Perform filtering 
            int xdim = data.Length;
            for (int u = 0; u < xdim; u++)
            {
                // Calculate distance to origin 
                int du = (u < xdim / 2) ? u : u - xdim;
                float dist = (float)(du * du);

                // Apply LP filter 
                if (useLP)
                {
                    double filter = 1 / (1 + Math.Pow(dist / (lpfreq * lpfreq), lppower));
                    data[u] *= filter;
                }

                // Apply HP filter
                if (useHP)
                {
                    double filter = 1 / (1 + Math.Pow(dist / (hpfreq * hpfreq), hppower));
                    data[u] *= (1 - filter);
                }

            }

            // Perform inverse FFT 
            FFT.inverse(data);
        }


    }
}
