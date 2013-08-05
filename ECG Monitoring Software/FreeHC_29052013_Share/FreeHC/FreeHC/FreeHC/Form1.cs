using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace FreeHC
{
    public partial class Form1 : Form
    {
        RealTimeFilterView rtfv = null;

        public Form1()
        {
            InitializeComponent();
        }

        private void quitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        RealTimeFilterView rtfv1 = null;
        RealTimeFilterView rtfv2 = null;
        RealTimeFilterView rtfv3 = null;
        RealTimeFilterView rtfv4 = null;
        RealTimeFilterView rtfv5 = null;
        RealTimeFilterView rtfv6 = null;

        private void Form1_Load(object sender, EventArgs e)
        {
            for (int i = 1; i < 7; i++)
            {
                rtfv = new RealTimeFilterView();
                if (i == 1) rtfv.Parent = panel1;
                if (i == 2) rtfv.Parent = panel3;
                if (i == 3) rtfv.Parent = panel4;
                if (i == 4) rtfv.Parent = panel5;
                if (i == 5) rtfv.Parent = panel6;
                if (i == 6) rtfv.Parent = panel7;
                rtfv.Dock = DockStyle.Fill;
                rtfv.Caption = "Channel "+i;
                rtfv.Channel = i;
                rtfv.Active = i == 1;
                rtfv.Click += new EventHandler(rtfv_Click);

                if (i == 1)
                {
                    rtfv1 = rtfv;
                    rtfv1.EnterDiagnosticMode = true;
                }
                if (i == 2) rtfv2 = rtfv;
                if (i == 3) rtfv3 = rtfv;
                if (i == 4) rtfv4 = rtfv;
                if (i == 5) rtfv5 = rtfv;
                if (i == 6) rtfv6 = rtfv;
            }
            propertyGrid1.SelectedObject = rtfv1.editor;
        }

        void rtfv_Click(object sender, EventArgs e)
        {
            RealTimeFilterView rtfv = (RealTimeFilterView)sender;
            propertyGrid1.SelectedObject = rtfv.editor;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            rtfv.Dispose();
        }

        private void panel1_Click(object sender, EventArgs e)
        {

        }

        private void OpenComPort(string comport)
        {
            serialPort1.PortName = comport;
            try
            {
                serialPort1.Open();
            }
            catch (Exception e)
            {
                MessageBox.Show("Error: " + e.Message);
                Close();
            }
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
            ComSelect cs = new ComSelect();
            if (cs.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                if (cs.comport.StartsWith("file:"))
                {
                    String aFile = cs.comport;
                    aFile = aFile.Remove(0, 5); // remove file:
                    if (File.Exists(aFile))
                    {
                        ReplayFile(aFile);
                    }
                    else
                    {
                        MessageBox.Show("Unable to open "+aFile+" ...");
                        Close();
                    }
                }
                else
                {
                    OpenComPort(cs.comport);
                }
            }
            else
            {
                Close();
            }
        }

        List<byte> Buffer = new List<byte>();

        private void ParseBuffer()
        {
            while ((1 == 1) && (Buffer.Count > 0))
            {

                // packet header available and one packet available
                while ((Buffer.Count > 0) && (Buffer[0] != 0xa5)) Buffer.RemoveAt(0);

                if ((Buffer.Count >= 17) && (Buffer[0] == 0xa5))
                {
                    // read packet
                    byte[] pkg = new byte[17];
                    Olimexino328_packet pk = new Olimexino328_packet();

                    for (int i = 0; i < 17; i++) {
                        pkg[i] = Buffer[0];
                        Buffer.RemoveAt(0);
                    }

                    if ((pkg[0] == 0xa5) && (pkg[1] == 0x5a))
                    {
                        pk.sync0 = pkg[0];
                        pk.sync1 = pkg[1];
                        pk.version = pkg[2];
                        pk.count = pkg[3];
                        pk.d1 = (UInt16)(pkg[5] + (pkg[4] << 8));
                        pk.d2 = (UInt16)(pkg[7] + (pkg[6] << 8));
                        pk.d3 = (UInt16)(pkg[9] + (pkg[8] << 8));
                        pk.d4 = (UInt16)(pkg[11] + (pkg[10] << 8));
                        pk.d5 = (UInt16)(pkg[13] + (pkg[12] << 8));
                        pk.d6 = (UInt16)(pkg[15] + (pkg[14] << 8));
                        pk.switches = pkg[16];

                        rtfv1.Pop(pk.d1);
                        rtfv2.Pop(pk.d2);
                        rtfv3.Pop(pk.d3);
                        rtfv4.Pop(pk.d4);
                        rtfv5.Pop(pk.d5);
                        rtfv6.Pop(pk.d6);
                    }
                    else
                    {
                        Debug.WriteLine("Invalid packet received!");
                    }
                }
                else
                {
                    break;
                }

            }
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            int dataLength = serialPort1.BytesToRead;
            byte[] data = new byte[dataLength];
            int nbrDataRead = serialPort1.Read(data, 0, dataLength);
            if (nbrDataRead == 0)
                return;
            // add to buffer ...
            for (int i = 0; i < data.Length; i++)
                Buffer.Add(data[i]);            

            // parse the buffer ...
            ParseBuffer();
        }


        int fFilePos = 0;
        string fFileName = "";

        private void ReplayFile(string _File)
        {
            fFilePos = 0;
            fFileName = _File;
            timer1.Interval = 25;
            timer1.Enabled = true;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            // file replay timer
            // inject a bit of the file data ...
            FileStream aFS = File.OpenRead(fFileName);
            try
            {
                byte[] aData = new byte[17*7];
                aFS.Seek(fFilePos, SeekOrigin.Begin);
                int aRR = aFS.Read(aData, 0, aData.Length);

                // add to buffer ...
                for (int i = 0; i < aData.Length; i++)
                    Buffer.Add(aData[i]);
                ParseBuffer();
                fFilePos += aRR;

                // loop playback
                if (aRR < aData.Length) fFilePos = 0;
            }
            finally
            {
                aFS.Dispose();
            }            
        }

        private void panel8_Paint(object sender, PaintEventArgs e)
        {

        }

    }
}
