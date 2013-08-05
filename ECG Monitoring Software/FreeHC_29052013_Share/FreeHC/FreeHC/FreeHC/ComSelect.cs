using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace FreeHC
{
    public partial class ComSelect : Form
    {
        public ComSelect()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {

        }

        public string comport { 
            get {
                if (comboBox1.SelectedIndex == 0)
                {
                    return "file:"+textBox1.Text;
                }
                else
                {
                    return comboBox1.Text;
                }
            } 
        }

        private void ComSelect_Load(object sender, EventArgs e)
        {
            string[] theSerialPortNames = System.IO.Ports.SerialPort.GetPortNames();
            comboBox1.Items.AddRange(theSerialPortNames);
            comboBox1.Items.Insert(0, "Replay File (From FreeHC-ComLogger)");
            comboBox1.Focus();
            if (comboBox1.Items.Count > 0)
                comboBox1.SelectedIndex = 0;
            textBox1.Enabled = (comboBox1.SelectedIndex == 0);
            button1.Enabled = textBox1.Enabled;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            textBox1.Enabled = (comboBox1.SelectedIndex == 0);
            button1.Enabled = textBox1.Enabled;
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            // select file
            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                textBox1.Text = openFileDialog1.FileName;   
            }
        }

        private void ComSelect_FormClosing(object sender, FormClosingEventArgs e)
        {
        }
    }
}
