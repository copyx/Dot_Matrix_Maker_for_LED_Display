using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Dot_Matrix_Maker_for_LED_Display
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();

            for(int i = 0; i < 32; i++)
                DotMatrix.Rows.Add();
        }
    }
}
