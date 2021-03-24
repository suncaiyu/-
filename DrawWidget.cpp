#include "DrawWidget.h"
#include "ui_DrawWidget.h"
#include <QPainter>
#define PI acos(-1)

double GetAngle(QPointF a, QPointF b, double r)
{
    // x1 = x0 + r * cos(a)   cosa = (x1-x0) / r
    double cosa = (b.x() - a.x()) / r;
    double angle = std::acos(cosa) * 180.0 / PI;
    if (b.y() - a.y() > 0) {
        return -angle;
    } else {
        return angle;
    }
}

DrawWidget::DrawWidget(QWidget *parent) :
      QWidget(parent),
      ui(new Ui::DrawWidget)
{
    ui->setupUi(this);
}

DrawWidget::~DrawWidget()
{
    delete ui;
}

void DrawWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    // 从界面x = 0， y = height / 2 初开始
    // 线
    int startY = height() / 2;
    QPen pen = painter.pen();
    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawLine(QPoint(0, startY), QPoint(100, startY));
    // 顺 圆
    pen.setColor(Qt::green);
    painter.setPen(pen);
    // 起点 100， starrtY 重点 200, startY  圆心 100 + 50  startY + 30
    // A: 200 - 100 / 2   B: 30   R =
    QRectF r = GetRect(QPointF(100, startY), QPointF(200, startY), QPointF(150, startY + 30));
    double startAngle1 = GetAngle(QPointF(150, startY + 30), QPointF(200, startY), r.width() / 2);
    double endAngle1 = GetAngle(QPointF(150, startY + 30), QPointF(100, startY), r.width() / 2);
    painter.drawArc(r, startAngle1 * 16, (endAngle1 - startAngle1) * 16);

    // 逆 圆

    pen.setColor(Qt::blue);
    painter.setPen(pen);
    QRectF rr = GetRect(QPointF(200, startY), QPointF(400, startY), QPointF(300, startY - 20));
    double startAngle2 = GetAngle(QPointF(300, startY - 20), QPointF(400, startY), rr.width() / 2);
    double endAngle2 = GetAngle(QPointF(300, startY - 20), QPointF(200, startY), rr.width() / 2);
    painter.drawArc(rr, startAngle2 * 16, (endAngle2 - startAngle2) * 16);
}

QRectF DrawWidget::GetRect(QPointF start, QPointF end, QPointF point)
{
    QRectF rect;
    // line  方程 y = ax + b   带入 start   end
    //    start.y = a * start.x + b;
    //  end.y = a * end.x + b
    // (start.y - end.y) = (startx - endx) * a;
    double a = (start.y() - end.y()) / (start.x() - end.x());
    double b = end.y() - a * end.x();
    // 两种情况 当a = 0(平行 x轴)  或者！=0
    if (a > -0.0000001 && a < 0.000001) {
        // x = end.x + start.x / 2
        double d1 = (std::abs(end.x() - start.x())) / 2;
        double d2 = std::abs(point.y() - start.y());
        double r = std::sqrt(std::pow(d1, 2) + std::pow(d2, 2));
        rect.setRect(point.x() - r, point.y() - r, 2 * r, 2 * r);
    } else {
        // 与之相对的另一条线 k * a = -1;
        double k = (-1 / a);
        // k 过圆心
        // y = kx + b
        double kb = point.y() - k * point.x();
        // 设 焦点 m n
        double m, n;
        // n = a * m + b
        // n = k * m + kb
        // 0 = (a - k) * m + b - kb
        m = (kb - b) / (a - k);
        n = a * m + b;
        // 点（m, n） 与point的距离
        double d1 = std::pow(std::abs(m - point.x()), 2) + std::pow(std::abs(n - point.y()), 2);
        // start end的距离
        double d2 = std::pow(std::abs(start.x() - end.x()), 2) + std::pow(start.y() - end.y(), 2);
        double r = std::sqrt(d1 + d2 / 4);
        rect.setRect(point.x() - r, point.y() - r, 2 * r, 2 * r);
    }
    return rect;
}
