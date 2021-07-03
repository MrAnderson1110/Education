using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Reflection;

namespace kr1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            this.label1.Text = "Контрольная работа.\nВариант " + ((81 % 15) + 1).ToString();
            Trapeze = new PointF[4]
            {
                new PointF( -50,  50),
                new PointF(  50,  50),
                new PointF( 100, -50),
                new PointF(-100, -50),
            };
        }
        protected void OnPaint(object sender, PaintEventArgs e)
        {
            // Получаем объект Graphics через идентификатор окна
            Graphics g = Graphics.FromHwnd(this.Handle);
            // А также ширину и высоту области для рисования
            int w = ClientSize.Width;
            int h = ClientSize.Height;
            // Очистка формы с помощью закрашенного прямоугольника
            g.FillRectangle(Brushes.White, 0, 0, w, h);      
            // Многоугольник
            PointF[] points = new PointF[4]
            {
                new PointF(Trapeze[0].X + w/2, Trapeze[0].Y + h/2),
                new PointF(Trapeze[1].X + w/2, Trapeze[1].Y + h/2),
                new PointF(Trapeze[2].X + w/2, Trapeze[2].Y + h/2),
                new PointF(Trapeze[3].X + w/2, Trapeze[3].Y + h/2)
            };
            g.DrawPolygon(Pens.Green, points);
        }

        private void OnKeyPress(object sender, KeyPressEventArgs e)
        {
            //Получаем значение клавиша, которая была нажата
            switch (e.KeyChar)
            {
                case 'a':
                    Trapeze[0].X *= 1.1f;
                    Trapeze[1].X *= 1.1f;
                    Trapeze[2].X *= 1.1f;
                    Trapeze[3].X *= 1.1f;
                    break;
                case 'd':
                    Trapeze[0].X *= 0.9f;
                    Trapeze[1].X *= 0.9f;
                    Trapeze[2].X *= 0.9f;
                    Trapeze[3].X *= 0.9f;
                    break;
                case 'w':
                case 's':
                    Trapeze[0].Y *= -1;
                    Trapeze[1].Y *= -1;
                    Trapeze[2].Y *= -1;
                    Trapeze[3].Y *= -1;
                    break;
                default:
                    break;
            }
            Invalidate();
        }

        private PointF[] Trapeze;
    }
}
