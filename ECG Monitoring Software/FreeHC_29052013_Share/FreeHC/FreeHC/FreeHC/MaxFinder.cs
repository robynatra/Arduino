using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FreeHC
{
    public class MaxFinder
    {
        public readonly List<int> _peaks = new List<int>();
        // http://pastebin.com/8yHDPWXs

        public int[] GetPeaks(double[] buffer, int windowSize, bool reverse = false)
        {
            if (windowSize < 2)
            {
                windowSize = 2;
            }
            _peaks.Clear();
            for (var i = 0; i < buffer.Length; i++)
            {
                var isPeak = true;
                for (var j = 0; j < windowSize; j++)
                {
                    var k = i + j - windowSize / 2;
                    if (k >= 0 && k < buffer.Length && k != i)
                    {
                        if (reverse)
                        {
                            if (buffer[k] >= buffer[i])
                            {
                                isPeak = false;
                            }
                        }
                        else
                        {
                            if (buffer[k] <= buffer[i])
                            {
                                isPeak = false;
                            }
                        }
                    }
                }
                if (isPeak)
                {
                    _peaks.Add(i);
                }
            }

            return _peaks.ToArray();
        }
    }
}
