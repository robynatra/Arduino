namespace FreeHC
{
    partial class Form1
    {
        /// <summary>
        /// Erforderliche Designervariable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Verwendete Ressourcen bereinigen.
        /// </summary>
        /// <param name="disposing">True, wenn verwaltete Ressourcen gelöscht werden sollen; andernfalls False.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Vom Windows Form-Designer generierter Code

        /// <summary>
        /// Erforderliche Methode für die Designerunterstützung.
        /// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.pnlMain = new System.Windows.Forms.Panel();
            this.panel7 = new System.Windows.Forms.Panel();
            this.panel6 = new System.Windows.Forms.Panel();
            this.panel5 = new System.Windows.Forms.Panel();
            this.panel4 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.propertyGrid1 = new System.Windows.Forms.PropertyGrid();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.pnlMain.SuspendLayout();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(813, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // statusStrip1
            // 
            this.statusStrip1.Location = new System.Drawing.Point(0, 646);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(813, 22);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // pnlMain
            // 
            this.pnlMain.AutoScroll = true;
            this.pnlMain.Controls.Add(this.panel7);
            this.pnlMain.Controls.Add(this.panel6);
            this.pnlMain.Controls.Add(this.panel5);
            this.pnlMain.Controls.Add(this.panel4);
            this.pnlMain.Controls.Add(this.panel3);
            this.pnlMain.Controls.Add(this.panel1);
            this.pnlMain.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlMain.Location = new System.Drawing.Point(0, 24);
            this.pnlMain.Name = "pnlMain";
            this.pnlMain.Size = new System.Drawing.Size(613, 622);
            this.pnlMain.TabIndex = 2;
            // 
            // panel7
            // 
            this.panel7.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel7.Location = new System.Drawing.Point(0, 500);
            this.panel7.Name = "panel7";
            this.panel7.Size = new System.Drawing.Size(613, 100);
            this.panel7.TabIndex = 4;
            // 
            // panel6
            // 
            this.panel6.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel6.Location = new System.Drawing.Point(0, 400);
            this.panel6.Name = "panel6";
            this.panel6.Size = new System.Drawing.Size(613, 100);
            this.panel6.TabIndex = 3;
            // 
            // panel5
            // 
            this.panel5.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel5.Location = new System.Drawing.Point(0, 300);
            this.panel5.Name = "panel5";
            this.panel5.Size = new System.Drawing.Size(613, 100);
            this.panel5.TabIndex = 0;
            // 
            // panel4
            // 
            this.panel4.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel4.Location = new System.Drawing.Point(0, 200);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(613, 100);
            this.panel4.TabIndex = 2;
            // 
            // panel3
            // 
            this.panel3.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel3.Location = new System.Drawing.Point(0, 100);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(613, 100);
            this.panel3.TabIndex = 1;
            // 
            // panel1
            // 
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(613, 100);
            this.panel1.TabIndex = 0;
            this.panel1.Click += new System.EventHandler(this.panel1_Click);
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.propertyGrid1);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Right;
            this.panel2.Location = new System.Drawing.Point(613, 24);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(200, 622);
            this.panel2.TabIndex = 3;
            // 
            // propertyGrid1
            // 
            this.propertyGrid1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.propertyGrid1.Location = new System.Drawing.Point(0, 0);
            this.propertyGrid1.Name = "propertyGrid1";
            this.propertyGrid1.Size = new System.Drawing.Size(200, 622);
            this.propertyGrid1.TabIndex = 0;
            // 
            // serialPort1
            // 
            this.serialPort1.BaudRate = 57600;
            this.serialPort1.ReadBufferSize = 1024;
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(813, 668);
            this.Controls.Add(this.pnlMain);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "FreeHC";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.Shown += new System.EventHandler(this.Form1_Shown);
            this.pnlMain.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.Panel pnlMain;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.PropertyGrid propertyGrid1;
        private System.Windows.Forms.Panel panel7;
        private System.Windows.Forms.Panel panel6;
        private System.Windows.Forms.Panel panel5;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Panel panel1;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Timer timer1;
    }
}

