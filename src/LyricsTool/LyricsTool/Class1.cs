using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LyricsTool
{
    internal class CapTure
    {
        public void GetImg() 
        {
            Image img = new Bitmap(Screen.AllScreens[0].Bounds.Width, Screen.AllScreens[0].Bounds.Height);
            Graphics g = Graphics.FromImage(img);
            g.CopyFromScreen(new Point(0, 0), new Point(0, 0), Screen.AllScreens[0].Bounds.Size);
            
            //ScreenBody body = new ScreenBody();
            //body.BackgroundImage = img;
            //body.Show();
        }
    }
}
