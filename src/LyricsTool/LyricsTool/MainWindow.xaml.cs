using ClassLibrary1;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Resources;
using System.Windows.Shapes;
using Win32;
using static Win32.User;

namespace LyricsTool
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        IntPtr windowHandle = IntPtr.Zero;
        IntPtr handle = IntPtr.Zero;
        public event PropertyChangedEventHandler PropertyChanged;
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            handle = new WindowInteropHelper(this).Handle;
        }
        private bool isMouseUp;

        public bool IsMouseUp
        {
            get { return isMouseUp; }
            set
            {
                isMouseUp = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("IsMouseUp"));
            }
        }
        int count = 0;
        private void Button_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            IsMouseUp = true;//鼠标左右键被按下
                             //Cursor = Cursors.Hand; //改变鼠标样式为十字架
                             //var vb = new VisualBrush(dd);
            Debug.WriteLine(IsMouseUp);
            StreamResourceInfo sri = Application.GetResourceStream(new Uri("/Icon/target.cur", UriKind.Relative));
            Cursor = new Cursor(sri.Stream, true);
            Debug.WriteLine("down");
        }
        StringBuilder sb = new StringBuilder();
        private void Button_PreviewMouseMove(object sender, MouseEventArgs e)
        {
            count++;
            //当鼠标移动时发生
            if (IsMouseUp)//左键是否被按下
            {
                //使用DragDrop的DoDragDrop方法开启拖动功能。拖动方式为拖动复制或移动
                //DragDrop.DoDragDrop(dd,"", DragDropEffects.All);
                try
                {
                    Win32.POINT pi;
                    User.GetCursorPos(out pi); //获取鼠标坐标值
                    var dd = User.GetDesktopWindow();
                    IntPtr intPtr = User.ChildWindowFromPointEx(dd, pi.x, pi.y, 0x0001 | 0x0002);
                    //Debug.WriteLine("FFF1   " + pi.x + "	" + pi.y + "    d" + dd + "    i" + intPtr);
                    if (intPtr != IntPtr.Zero && intPtr != handle)
                    {
                        try
                        {
                            sb.Clear();
                            User.GetWindowText(intPtr, sb, 256);

                            windowHandle = intPtr;


                        }
                        catch (Exception ex)
                        {

                        }
                    }
                }
                catch (Exception ex)
                {

                }
            }
        }
        private void Button_PreviewMouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            Debug.WriteLine("自身" + handle + "目标" + windowHandle);
            IsMouseUp = false;//鼠标左右键被弹起
            Debug.WriteLine(IsMouseUp);
            Cursor = Cursors.Arrow;//改变鼠标样式为默认
            Debug.WriteLine("up");


            //设置透明
            int exStyle = User.GetWindowLong(windowHandle, User.GWL_EXSTYLE);
            exStyle |= (int)User.WS_EX_LAYERED;
            //exStyle |= (int)User.WS_EX_APPWINDOW;
            //exStyle = exStyle&~((int)User.WS_EX_WINDOWEDGE);
            User.SetWindowLong(windowHandle, User.GWL_EXSTYLE, exStyle);



            Win32.RECT lprect = default(Win32.RECT);
            User.GetWindowRect(windowHandle, ref lprect);


            //查找地址框
            //IntPtr Text = IntPtr.Zero;
            //var enumWindowResult = (IntPtr)User.EnumChildWindows(windowHandle, new EnumWindowsProc((tophandle, topparamhandle) =>
            //{
            //    var strBuilder = new StringBuilder();
            //    User.GetWindowText(tophandle, strBuilder, 255);
            //    Debug.WriteLine(strBuilder.ToString());
            //    if (strBuilder.ToString().StartsWith("地址:"))
            //    {
            //        Text = tophandle;
            //        return 0;
            //    }
            //    return 1;
            //}), (int)IntPtr.Zero);

            Class1.winPtr = (IntPtr)Convert.ToInt32(txtPtr.Text);
            User.SetParent(windowHandle, Class1.winPtr);
            User.SetWindowPos(windowHandle, (IntPtr)(0), 0,0,800,150, User.SWP_SHOWWINDOW | User.SWP_NOACTIVATE);
            var bitmapImage = GetWindowShotCut(Class1.winPtr2);
            imgPic.Source = bitmapImage;
        }
        private BitmapImage GetWindowShotCut(IntPtr intPtr)
        {
            var image = WindowCaptureHelper.GetShotCutImage(intPtr);
            var bitmapImage = BitmapConveters.ConvertToBitmapImage(image);
            return bitmapImage;
        }

        private void ExitMenuItem_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }
    }
}
