using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using Microsoft.Win32;
using System.IO;

namespace DotMatrixMaker
{
    /// <summary>
    /// DotMatrix.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class DotMatrix : Window
    {
        static string FileName;
        static string OpenPath;
        static string UploadPath = @"C:\MAHA3\";

        const byte BigWidth = 64, BigHeight = 32, SmallWidth = 48, SmallHeight = 16;        

        bool DotMouseLeftButtonDown = false, DotMouseEnter = false, SmallMode = false;

        UInt32[] CHeaderColorBit = new UInt32[4];
        UInt32[] DotMatrixBit = new UInt32[64];
        Rectangle[] CHeader = new Rectangle[64];
        Rectangle[,] Dots = new Rectangle[32, 64];

        public DotMatrix()
        {
            InitializeComponent();
            Dot_Binding();
        }

        private void Dot_Binding()
        {
            string DRow, DCol;

            for (int i = 0; i < 64; i++)
            {
                if (i < 10)
                    DCol = "0" + i.ToString();
                else
                    DCol = i.ToString();

                CHeader[i] = (Rectangle)(this.FindName("CH" + DCol));

                for (int j = 0; j < 32; j++)
                {                    
                    if (j < 10)
                        DRow = "0" + j.ToString();
                    else
                        DRow = j.ToString();

                    Dots[j, i] = (Rectangle)(this.FindName("D" + DRow + DCol));
                }
            }
        }

        private void CHeader_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            byte CHeaderNumber = Convert.ToByte(((Rectangle)e.Source).Name.ToString().Substring(2));
            byte height;

            if (SmallMode && (CHeaderNumber >= SmallWidth))
                return;

            UInt32 CHeaderColorNumber = (UInt32)((CHeaderColorBit[CHeaderNumber / 16] & (3 << (CHeaderNumber % 16 * 2))) >> ((CHeaderNumber % 16) * 2));

            SolidColorBrush CHeaderColor;

            if (CHeaderColorNumber == 0)
            {
                CHeaderColor = new SolidColorBrush(Colors.Yellow);
                CHeaderColorNumber = 1;
            }
            else if (CHeaderColorNumber == 1)
            {
                CHeaderColor = new SolidColorBrush(Colors.Blue);
                CHeaderColorNumber = 2;
            }
            else
            {
                CHeaderColor = new SolidColorBrush(Colors.Red);
                CHeaderColorNumber = 0;
            }

            CHeaderColorBit[CHeaderNumber / 16] &= ~(UInt32)(3 << ((CHeaderNumber % 16) * 2));
            CHeaderColorBit[CHeaderNumber / 16] |= (UInt32)(CHeaderColorNumber << ((CHeaderNumber % 16) * 2));
            ((Rectangle)e.Source).Fill = CHeaderColor;

            if (SmallMode)
                height = SmallHeight;
            else
                height = BigHeight;
            for (int i = 0; i < height; i++)
            {
                if((DotMatrixBit[CHeaderNumber] & (1 << i)) != 0)
                    Dots[i, CHeaderNumber].Fill = CHeaderColor;
            }
        }

        private void Dot_ColorChange(RoutedEventArgs e)
        {
            UInt16 DotNumber = Convert.ToUInt16(((Rectangle)e.Source).Name.ToString().Substring(1));
            byte DRow = (byte)(DotNumber / 100), DCol = (byte)(DotNumber % 100);

            if (SmallMode && ((DRow >= SmallHeight) || (DCol >= SmallWidth)))
                return;

            UInt32 CHeaderColorNumber = (UInt32)((CHeaderColorBit[DCol / 16] & (3 << (DCol % 16 * 2))) >> ((DCol % 16) * 2));
            SolidColorBrush DotColor;

            if ((DotMatrixBit[DCol] & (1 << DRow)) == 0)
            {
                if (CHeaderColorNumber == 0)
                {
                    DotColor = new SolidColorBrush(Colors.Red);
                }
                else if (CHeaderColorNumber == 1)
                {
                    DotColor = new SolidColorBrush(Colors.Yellow);
                }
                else if (CHeaderColorNumber == 2)
                {
                    DotColor = new SolidColorBrush(Colors.Blue);
                }
                else
                {
                    DotColor = new SolidColorBrush(Colors.White);
                }
                DotMatrixBit[DCol] |= (UInt32)(1 << DRow);
            }
            else
            {
                if (DotMouseEnter)
                {
                    if (CHeaderColorNumber == 0)
                    {
                        DotColor = new SolidColorBrush(Colors.Red);
                    }
                    else if (CHeaderColorNumber == 1)
                    {
                        DotColor = new SolidColorBrush(Colors.Yellow);
                    }
                    else if (CHeaderColorNumber == 2)
                    {
                        DotColor = new SolidColorBrush(Colors.Blue);
                    }
                    else
                    {
                        DotColor = new SolidColorBrush(Colors.White);
                    }
                }
                else
                {
                    DotColor = new SolidColorBrush(Colors.Black);
                    DotMatrixBit[DCol] &= ~(UInt32)(1 << DRow);
                }
            }

            ((Rectangle)e.Source).Fill = DotColor;
        }

        private void Dot_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            DotMouseLeftButtonDown = true;
            Dot_ColorChange(e);
        }

        private void Dot_MouseEnter(object sender, MouseEventArgs e)
        {
            if (DotMouseLeftButtonDown)
            {
                DotMouseEnter = true;
                Dot_ColorChange(e);
            }
        }

        private void Dot_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            DotMouseEnter = false;
            DotMouseLeftButtonDown = false;
        }

        private void Reset_Click(object sender, RoutedEventArgs e)
        {
            Reset_DotMatrix();

            if (SmallMode)
                ChangeToSmall_Click(sender, e);
            else
                ChangeToBig_Click(sender, e);
        }

        private void Reset_DotMatrix()
        {
            SolidColorBrush ResetColor = new SolidColorBrush(Colors.Black);

            for (int i = 0; i < 64; i++)
                DotMatrixBit[i] = 0;

            for (int i = 0; i < 32; i++)
                for (int j = 0; j < 64; j++)
                    Dots[i, j].Fill = ResetColor;
        }

        private void EditButton_Click(object sender, RoutedEventArgs e)
        {
            if (EditButton.Content.ToString().Equals("Edit"))
            {
                CommentBox.IsReadOnly = false;
                EditButton.Content = "Finish";
            }
            else
            {
                CommentBox.IsReadOnly = true;
                EditButton.Content = "Edit";
            }
        }

        private void Save_Click(object sender, RoutedEventArgs e)
        {
            if (FileName != null)
            {
                Save_DotMatrixInfo(OpenPath);
                return;
            }

            SaveAs_Click(sender, e);
        }

        private void SaveAs_Click(object sender, RoutedEventArgs e)
        {
            SaveFileDialog SaveDlg = new SaveFileDialog();
            SaveDlg.Title = "Save";

            if(SmallMode)
                SaveDlg.FileName = SmallWidth.ToString() + "X" + SmallHeight.ToString() + "_Noname";
            else
                SaveDlg.FileName = BigWidth.ToString() + "X" + BigHeight.ToString() + "_Noname"; ;

            SaveDlg.InitialDirectory = Directory.GetCurrentDirectory();
            SaveDlg.AddExtension = true;
            SaveDlg.DefaultExt = ".txt";
            SaveDlg.Filter = "Text Files(.txt)|*.txt";

            if (SaveDlg.ShowDialog() == true)
            {
                Save_DotMatrixInfo(SaveDlg.FileName);
            }
        }

        private void Save_DotMatrixInfo(string SavePath)
        {
            byte[] temp;
            byte length, height;
            StreamWriter SW = new StreamWriter(SavePath);

            FileName = SavePath.Trim().Split('\\').Last();
            FileName = FileName.Remove(FileName.Length - 4);
            this.Title += " - " + FileName + " - " + SavePath;

            if (SmallMode)
                SW.WriteLine("S");
            else
                SW.WriteLine("B");

            SW.WriteLine(CommentBox.Text);

            if (SmallMode)
                length = 3;
            else
                length = 4;

            for (int i = 0; i < length; i++)
            {
                temp = BitConverter.GetBytes(CHeaderColorBit[i]);
                for (int j = 0; j < temp.Length; j++)
                    SW.Write(get_SignedByteString(temp[j]) + ",");
            }

            SW.Write(SW.NewLine);

            if (SmallMode)
            {
                length = SmallWidth;
                height = 2;
            }
            else
            {
                length = BigWidth;
                height = 4;
            }

            for (int i = 0; i < length; i++)
            {
                temp = BitConverter.GetBytes(DotMatrixBit[i]);
                for (int j = 0; j < height; j++)
                    SW.Write(get_SignedByteString(temp[j]) + ",");
            }
            SW.Close();
        }

        private string get_SignedByteString(byte value)
        {
            string SignedByte;

            if (value > 127)
            {
                SignedByte = "-" + (value - 128).ToString();
            }
            else
            {
                SignedByte = value.ToString();
            }

            return SignedByte;
        }

        private byte get_UnsignedByteString(string value)
        {
            byte UnsignedByte;

            if (value[0].Equals('-'))
                UnsignedByte = (byte)(128 + Convert.ToByte(value.Substring(1)));
            else
                UnsignedByte = Convert.ToByte(value);

            return UnsignedByte;
        }

        private void Open_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog OpenDlg = new OpenFileDialog();

            OpenDlg.Filter = "Text Files(*.txt)|*txt|All Files(*.*)|*.*";
            OpenDlg.Title = "Open";

            CommentBox.Text = "";
            Reset_DotMatrix();

            if (OpenDlg.ShowDialog() == true)
            {
                string[] StrNumbers;
                byte[] ByteNumbers;

                OpenPath = OpenDlg.FileName;
                FileName = OpenDlg.FileName.Trim().Split('\\').Last();
                FileName = FileName.Remove(FileName.Length - 4);
                this.Title += " - " + FileName + " - " + OpenDlg.FileName;

                FileStream FS = File.OpenRead(OpenDlg.FileName);
                StreamReader SR = new StreamReader(FS, System.Text.Encoding.Default);

                SR.BaseStream.Seek(0, SeekOrigin.Begin);

                if (SR.ReadLine().Equals("S"))
                    SmallMode = true;
                else
                    SmallMode = false;

                CommentBox.Text = SR.ReadLine();

                StrNumbers = SR.ReadLine().Trim().Split(' ');
                ByteNumbers = new byte[StrNumbers.Length];
                
                for(int i = 0; i < StrNumbers.Length; i++)
                    ByteNumbers[i] = get_UnsignedByteString(StrNumbers[i]);

                for (int i = 0; i < (StrNumbers.Length / 4); i++)
                {
                    CHeaderColorBit[i] = BitConverter.ToUInt32(ByteNumbers, i * 4);
                }

                StrNumbers = SR.ReadLine().Trim().Split(' ');
                ByteNumbers = new byte[StrNumbers.Length];

                for (int i = 0; i < StrNumbers.Length; i++)
                    ByteNumbers[i] = get_UnsignedByteString(StrNumbers[i]);

                if(SmallMode)
                    for (int i = 0; i < (StrNumbers.Length / 2); i++)
                    {
                        DotMatrixBit[i] = (UInt32)BitConverter.ToUInt16(ByteNumbers, i * 2);
                    }
                else
                    for (int i = 0; i < (StrNumbers.Length / 4); i++)
                    {
                        DotMatrixBit[i] = BitConverter.ToUInt32(ByteNumbers, i * 4);
                    }

                SR.Close();
                FS.Close();

                Apply_Dots();

                if (SmallMode)
                    ChangeToSmall_Click(sender, e);
                else
                    ChangeToBig_Click(sender, e);
            }
        }

        private void Apply_Dots()
        {
            UInt32 CHeaderColorNumber;
            SolidColorBrush DotColor;

            for (int i = 0; i < 64; i++)
            {
                CHeaderColorNumber = (UInt32)((CHeaderColorBit[i / 16] & (3 << (i % 16 * 2))) >> ((i % 16) * 2));

                if (CHeaderColorNumber == 0)
                {
                    DotColor = new SolidColorBrush(Colors.Red);
                }
                else if (CHeaderColorNumber == 1)
                {
                    DotColor = new SolidColorBrush(Colors.Yellow);
                }
                else
                {
                    DotColor = new SolidColorBrush(Colors.Blue);
                }
                CHeader[i].Fill = DotColor;

                for (int j = 0; j < 32; j++)
                {
                    if ((DotMatrixBit[i] & (1 << j)) != 0)
                        Dots[j, i].Fill = DotColor;
                    else
                        Dots[j, i].Fill = new SolidColorBrush(Colors.Black);
                }
            }
        }

        private void Upload_Click(object sender, RoutedEventArgs e)
        {
            byte length, height;

            if (FileName == null)
            {
                MessageBox.Show("파일이 저장되지 않았습니다.");
                Save_Click(sender, e);
            }
            else
            {
                Save_DotMatrixInfo(OpenPath);
            }

            byte[] temp;
            StreamWriter SW = new StreamWriter(UploadPath + "title_comment\\" + FileName + ".txt");

            SW.WriteLine(FileName + "#" + CommentBox.Text);

            SW.Close();

            SW = new StreamWriter(UploadPath + "edit_image\\" + FileName + "_Data.txt");

            if (SmallMode)
                length = 3;
            else
                length = 4;

            for (int i = 0; i < length; i++)
            {
                temp = BitConverter.GetBytes(CHeaderColorBit[i]);
                for (int j = 0; j < temp.Length; j++)
                    SW.Write(get_SignedByteString(temp[j]) + ",");
            }

            SW.Write(SW.NewLine);

            if (SmallMode)
            {
                length = SmallWidth;
                height = 2;
            }
            else
            {
                length = BigWidth;
                height = 4;
            }

            for (int i = 0; i < length; i++)
            {
                temp = BitConverter.GetBytes(DotMatrixBit[i]);
                for (int j = 0; j < height; j++)
                    SW.Write(get_SignedByteString(temp[j]) + ",");
            }
            SW.Close();

            Make_Thumbnail((FrameworkElement)this.FindName("DotsGrid"), 0.3); 
        }

        private void Make_Thumbnail(FrameworkElement Source, double Scale)
        {
            ImageSave(ConverterBitmapImage(Source, Scale, SmallMode));
        }

        private static RenderTargetBitmap ConverterBitmapImage(FrameworkElement Element, double Scale, bool small)
        {
            double RenderHeight = Element.ActualHeight * Scale;
            double RenderWidth = Element.ActualWidth * Scale;

            DrawingVisual drawingVisual = new DrawingVisual();
            DrawingContext drawingContext = drawingVisual.RenderOpen();

            // 해당 객체의 그래픽요소로 사각형의 그림을 그립니다.
            drawingContext.DrawRectangle(new VisualBrush(Element), null, new Rect(new Point(0, 0), new Point(RenderWidth, RenderHeight)));

            drawingContext.Close();
            // 비트맵으로 변환합니다.

            if (small)
            {
                RenderHeight /= 2;
                RenderWidth = RenderWidth * 3 / 4;
            }

            RenderTargetBitmap target = new RenderTargetBitmap((int)RenderWidth, (int)RenderHeight, 96, 96, System.Windows.Media.PixelFormats.Pbgra32);
            target.Render(drawingVisual);

            return target;
        }

        private static void ImageSave(BitmapSource Source)
        {
            BitmapEncoder Encoder = new JpegBitmapEncoder();
            // 파일 생성
            FileStream stream = File.Create(UploadPath + "thumbnail\\" + FileName + ".jpg");

            // 인코더 프레임에 이미지 추가
            Encoder.Frames.Add(BitmapFrame.Create(Source));
            // 파일에 저장
            Encoder.Save(stream);

            stream.Close();
        }

        private void ChangeToSmall_Click(object sender, RoutedEventArgs e)
        {
            SmallMode = true;
            SolidColorBrush DotColor = new SolidColorBrush(Colors.White);

            for (int i = SmallWidth; i < BigWidth; i++)
                CHeader[i].Fill = DotColor;

            for (int i = 0; i < SmallHeight; i++)
                for (int j = SmallWidth; j < BigWidth; j++)
                    Dots[i, j].Fill = DotColor;

            for (int i = SmallHeight; i < BigHeight; i++)
                for (int j = 0; j < BigWidth; j++)
                    Dots[i, j].Fill = DotColor;
        }

        private void ChangeToBig_Click(object sender, RoutedEventArgs e)
        {
            SmallMode = false;
            Apply_Dots();
        }
    }
}
