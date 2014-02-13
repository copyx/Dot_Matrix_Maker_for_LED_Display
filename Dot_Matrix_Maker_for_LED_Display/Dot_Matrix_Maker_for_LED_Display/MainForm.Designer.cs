namespace Dot_Matrix_Maker_for_LED_Display
{
    partial class MainForm
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다.
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            this.DotMatrix = new System.Windows.Forms.DataGridView();
            ((System.ComponentModel.ISupportInitialize)(this.DotMatrix)).BeginInit();
            this.SuspendLayout();
            // 
            // DotMatrix
            // 
            this.DotMatrix.AllowUserToAddRows = false;
            this.DotMatrix.AllowUserToDeleteRows = false;
            this.DotMatrix.AllowUserToResizeColumns = false;
            this.DotMatrix.AllowUserToResizeRows = false;
            this.DotMatrix.BackgroundColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.DotMatrix.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.DotMatrix.ClipboardCopyMode = System.Windows.Forms.DataGridViewClipboardCopyMode.Disable;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("굴림", 7F);
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.DotMatrix.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.DotMatrix.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            

            for (int i = 0; i < 32; i++)
            {
                this.Lines[i] = new System.Windows.Forms.DataGridViewTextBoxColumn();
                this.Lines[i].AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.None;
                this.Lines[i].HeaderText = "";
                this.Lines[i].MaxInputLength = 0;
                this.Lines[i].Name = "Line_0" + i.ToString();
                this.Lines[i].ReadOnly = true;
                this.Lines[i].Resizable = System.Windows.Forms.DataGridViewTriState.False;
                this.Lines[i].SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
                this.Lines[i].Width = 18;
            }
            for(int i = 0; i < 32; i++)
                this.DotMatrix.Columns.Add(this.Lines[i]);
           
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("굴림", 5F);
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.DotMatrix.DefaultCellStyle = dataGridViewCellStyle2;
            this.DotMatrix.GridColor = System.Drawing.Color.FromArgb(((int)(((byte)(70)))), ((int)(((byte)(70)))), ((int)(((byte)(70)))));
            this.DotMatrix.Location = new System.Drawing.Point(12, 12);
            this.DotMatrix.Name = "DotMatrix";
            this.DotMatrix.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.DisableResizing;
            this.DotMatrix.RowTemplate.DefaultCellStyle.BackColor = System.Drawing.Color.Black;
            this.DotMatrix.RowTemplate.Height = 18;
            this.DotMatrix.RowTemplate.ReadOnly = true;
            this.DotMatrix.RowTemplate.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.DotMatrix.Size = new System.Drawing.Size(617, 594);
            this.DotMatrix.StandardTab = true;
            this.DotMatrix.TabIndex = 0;
            
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(818, 618);
            this.Controls.Add(this.DotMatrix);
            this.Name = "MainForm";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.DotMatrix)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView DotMatrix;
        private System.Windows.Forms.DataGridViewTextBoxColumn[] Lines = new System.Windows.Forms.DataGridViewTextBoxColumn[32];
    }
}

