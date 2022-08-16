using ClassLibrary1;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Image img = new Bitmap(Screen.AllScreens[0].Bounds.Width, Screen.AllScreens[0].Bounds.Height);
            Graphics g = Graphics.FromImage(img);
            // Screen.AllScreens[0].Bounds.Size
            g.CopyFromScreen(new Point(0, 0), new Point(-100, -100), Screen.AllScreens[0].Bounds.Size);
            //pictureBox1.BackgroundImage = img;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Task.Factory.StartNew(() =>
            {
                Thread.Sleep(1000);
                this.Invoke((Action)(() =>
                {
                    Console.WriteLine((int)this.panel1.Handle);
                    Class1.winPtr2 = this.Handle;
                }));
            });
        }
    }
}
