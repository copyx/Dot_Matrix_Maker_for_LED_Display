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

        private void DotMatrix_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (DotMatrix.Rows[e.RowIndex].Cells[e.ColumnIndex].Style.BackColor.Equals(Color.Black))
                DotMatrix.Rows[e.RowIndex].Cells[e.ColumnIndex].Style.BackColor = Color.Red;
            else if (DotMatrix.Rows[e.RowIndex].Cells[e.ColumnIndex].Style.BackColor.Equals(Color.Red))
                DotMatrix.Rows[e.RowIndex].Cells[e.ColumnIndex].Style.BackColor = Color.Yellow;
            else if (DotMatrix.Rows[e.RowIndex].Cells[e.ColumnIndex].Style.BackColor.Equals(Color.Yellow))
                DotMatrix.Rows[e.RowIndex].Cells[e.ColumnIndex].Style.BackColor = Color.Blue;
            else
                DotMatrix.Rows[e.RowIndex].Cells[e.ColumnIndex].Style.BackColor = Color.Black;
        }

        private void DotMatrix_CellStyleContentChanged(object sender, DataGridViewCellStyleContentChangedEventArgs e)
        {
        }
    }
}
