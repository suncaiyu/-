#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>

namespace Ui {
class DrawWidget;
}

class DrawWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrawWidget(QWidget *parent = nullptr);
    ~DrawWidget();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::DrawWidget *ui;
    int mLineX;
    int mLineY;
    int mArc1X;
    int mArc1Y;
    int mArc2X;
    int mArc2Y;

    QRectF GetRect(QPointF start, QPointF end, QPointF point);
};

#endif // DRAWWIDGET_H
