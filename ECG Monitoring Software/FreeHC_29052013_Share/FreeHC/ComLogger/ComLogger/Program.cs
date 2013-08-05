using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.IO.Ports;
using System.Threading;

namespace ComLogger
{
    class Program
    {
        static SerialPort aComP = null;
        static string fLogFile = "";
        static void Main(string[] args)
        {
            bool fClose = false;
            string aCom = "";
            if (args.Count() > 0) aCom = args[0];
            Console.WriteLine("Opening com-port: "+aCom+"...");
            if (aCom == "") return;
            aComP = new SerialPort(aCom, 57600);
            aComP.DataReceived += new SerialDataReceivedEventHandler(aComP_DataReceived);
            try
            {
                aComP.Open();
                Console.WriteLine("com-port opened.");
                string apath = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
                fLogFile = Path.Combine(apath, "_" + aCom + ".log");
                Console.WriteLine("recording to \"" + fLogFile + "\"...");
                File.Delete(fLogFile);
                try
                {
                    Console.WriteLine("press \"q\" to quit.");
                    while (Console.ReadKey().KeyChar != 'q')
                    {                        
                    }
                    fClose = true;
                    Console.WriteLine("closing comport...");
                    aComP.Close();
                    while (aComP.IsOpen)
                    {
                        Thread.Sleep(100); 
                    }
                    Console.WriteLine("comport closed.");
                }
                finally
                {
                    if (aComP.IsOpen) aComP.Close();
                    aComP.Dispose();
                }

            }
            catch (Exception e)
            {
                Console.WriteLine("Error: " + e.Message);
            }
        }

        static void aComP_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            int dataLength = aComP.BytesToRead;
            byte[] data = new byte[dataLength];
            int nbrDataRead = aComP.Read(data, 0, dataLength);
            if (nbrDataRead == 0)
                return;
            BinaryWriter aOut = null;
            if (File.Exists(fLogFile)) {
                aOut = new BinaryWriter(File.Open(fLogFile, FileMode.Append, FileAccess.Write));
            } else {
                aOut = new BinaryWriter(File.Open(fLogFile, FileMode.Create, FileAccess.Write));
            }
            aOut.Write(data, 0, nbrDataRead);
            aOut.Flush();
            aOut.Dispose();
            Console.Write(".");
        }
    }
}
