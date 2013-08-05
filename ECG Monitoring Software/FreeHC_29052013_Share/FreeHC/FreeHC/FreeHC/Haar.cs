using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
// Modified from: http://en.verysource.com/code/6802496_1/simple_haar.java.html
namespace FreeHC
{
    public static class Haar
    {
        static List<double[]> coefs = new List<double[]>();
        public static void inverse(double haar_value, ref double[] Data)
        {
            Data[0] = haar_value;
            byte log = (byte)Math.Log(Data.Length, 2);
            int len = (int)Math.Pow(2, log);

            int vec_ix = 0;
            int last_p = 0;
            byte p_adj = 1;

            for (int l = (byte)(log - 1); l >= 0; l--)
            {
                int p = (int)Math.Pow(2, l);
                double[] c = coefs[vec_ix];
                int coef_ix = 0;
                for (int j = 0; j < len; j++)
                {
                    int a_1 = p * (2 * j);
                    int a_2 = p * ((2 * j) + 1);
                    if (a_2 < len)
                    {
                        double tmp = Data[a_1];
                        Data[a_1] = tmp + c[coef_ix];
                        Data[a_2] = tmp - c[coef_ix];
                        coef_ix++;
                    }
                    else
                    {
                        break;
                    }
                } // for j
                last_p = p;
                p_adj++;
                vec_ix++;
            } // for l

        }

        public static double calc(ref double[] Data, bool first = true)
        {
            if (first) coefs.Clear();
            double rv = 0;
            double[] DataA = new double[Data.Length / 2];
            double[] DataC = new double[Data.Length / 2];
            int j = 0;
            for (int i = 0; i < Data.Length; i += 2)
            {
                DataA[j] = (Data[i] + Data[i + 1]) / 2;
                DataC[j] = (Data[i] - DataA[j]) / 2;
                j++;
            }
            coefs.Add(DataC);
            if (DataA.Length == 1)
            {
                rv = DataA[0];
            }
            else
            {
                rv = calc(ref DataA, false);
            }
            if (first)
            {
                // reverse coef's
                coefs.Reverse();
            }
            return rv;
        }

        public static void process(ref double[] data)
        {
            double aRes = calc(ref data);
            inverse(aRes, ref data);
        }

    }
}
