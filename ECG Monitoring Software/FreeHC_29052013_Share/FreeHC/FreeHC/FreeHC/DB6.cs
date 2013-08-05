using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
// Modified From: http://www.uni-stuttgart.de/gi/education/MSC/diplomarbeiten/wengert.pdf
namespace FreeHC
{
    public static class DB6
    {
        static double[] h =new double[6] { 0.3326705529500825,  0.8068915093110924, 0.4598775021184914, 
                                   -0.1350110200102546, -0.0854412738820267, 0.0352262918857095};
        static double[] g = new double[6] { 0,0,0,0,0,0 };

        private static void H(ref double[] sig,ref double[] Hsig,int length_sig)
        {
	        int k,l;
	        for(k=0;k<length_sig/2;k++) {
		        Hsig[k]=0.0;
		        for(l=0;l<6;l++) Hsig[k]+=h[l]*sig[(l+2*k)%length_sig];
	        }
        }

        private static void G(ref double[] sig,ref double[] Gsig,int length_sig)
        {
	        int k,l;
	        for(k=0;k<length_sig/2;k++) {
		        Gsig[k]=0.0;
		        for(l=0;l<6;l++) Gsig[k]+=g[l]*sig[(l+2*k)%length_sig];
	        }
        }

        private static void Had(ref double[] sig,ref double[] Hsig,int length_Hsig)
        {
	        int k,l;
	        for(k=0;k<2*length_Hsig;k+=2) {
		        sig[k]=0.0;
		        for(l=0;l<6;l+=2) sig[k]+=h[l]*Hsig[((k-l)/2+length_Hsig)%length_Hsig];
	        }
	        for(k=1;k<2*length_Hsig;k+=2) {
		        sig[k]=0.0;
		        for(l=1;l<6;l+=2) sig[k]+=h[l]*Hsig[((k-l)/2+length_Hsig)%length_Hsig];
	        }
        }

        private static void Gad(ref double[] sig,ref double[] Gsig,int length_Gsig)
        {
	        int k,l;
	        for(k=0;k<2*length_Gsig;k+=2) {
		        sig[k]=0.0;
		        for(l=0;l<6;l+=2) sig[k]+=g[l]*Gsig[((k-l)/2+length_Gsig)%length_Gsig];
	        }
	        for(k=1;k<2*length_Gsig;k+=2) { 
		        sig[k]=0.0; 
		        for(l=1;l<6;l+=2) sig[k]+=g[l]*Gsig[((k-l)/2+length_Gsig)%length_Gsig];
	        }
        }

        public static void decomp(ref double[] sig,int length_sig) {
          double sig_=-1;
          for(int ix=0;ix<6;ix++) {
            sig_*=-1;
	        g[ix]=sig_*h[6-1-ix];
          }

          int i;
          /*  allocation of buffer        */
          double[] Hsig= new double[length_sig/2];
          double[] Gsig= new double[length_sig/2];
          /*  Wavelet decomposition        */
          while (length_sig>=6)
          {
	        H(ref sig, ref Hsig,length_sig);
	        G(ref sig, ref Gsig,length_sig);
	        for(i=0;i<length_sig/2;i++) {
		        sig[i]=Hsig[i];
		        sig[length_sig/2+i]=Gsig[i];
	        }
	        length_sig/=2;
          }
          /*  release memory        */
        }

        public static void reconst(ref double[] spec, int length_spec)
        {
            int l, length;
            double[] Hsig = new double[length_spec / 2];
            double[] Gsig = new double[length_spec / 2];
            double[] buff = new double[length_spec];
            length = 4;
            while (length <= length_spec / 2)
            {
                for (l = 0; l < length; l++)
                {
                    Hsig[l] = spec[l];
                    Gsig[l] = spec[length + l];
                }
                Had(ref buff, ref Hsig, length);
                Gad(ref spec, ref Gsig, length);
                length *= 2;
                for (l = 0; l < length; l++) spec[l] += buff[l];
            }
        }

        public static void process(ref double[] data, bool reconstruct) {
            decomp(ref data, data.Length);
            if (reconstruct)
               reconst(ref data, data.Length);
        }


    }
}
