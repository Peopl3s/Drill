#include "graphicFrame.h"

#include <cmath>
#include <fstream>

#include <QTimer>
#include <QString>
#include <QApplication>

#include "utils.h"
#include "point.h"

GraphicFrame::GraphicFrame(QWidget *parent) : QFrame(parent)
{
}

void GraphicFrame::clear()
{
    isDraw = false;
    update();
}
void GraphicFrame::setPhi(const double &phi)
{
    this->phi = phi;
}

void GraphicFrame::draw(const double &phi)
{
    isDraw = true;

    if(phi == this->phi)
    {
        this->update();
        return;
    }

    const double minute = 0.0174; // 1minute = 0.00029 = 1degree / 60 // 1degree = 0.0174
    const double step = phi - this->phi >= 0 ? minute : -minute;

    while(fabs(phi - this->phi) > minute)
    {
        this->phi += step;
        this->update();

        QTimer::singleShot(3, [this] {
            this->update();
        });
        QApplication::processEvents();
    }

    this->phi = phi;
    this->update();
}

void GraphicFrame::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);
    painter.eraseRect(this->rect());

    if(!this->isDraw)
    {
        QFrame::paintEvent(paintEvent);
        return;
    }


    const int topMargin = 40;

    double sy = (this->height() - 2 * topMargin) / Utils::getInstance().getHeight();
    double sx = (this->width() / 2 - 2 * topMargin) / Utils::getInstance().getWidth();

    const qreal scale = sy < sx ? sy : sx;

    qreal h = 30 / scale;
    int k = 10;
    while(static_cast<int>(h / k) > 0) k += 10;

    if(k == 10)
        k = 1;

    const int stepLabel = ceil(h / k) * k;
    const qreal step = stepLabel * scale;
    const int n = (this->height() - topMargin) / step;
    const int m = this->width() / 2 / step;

    //axis
    painter.setPen(QPen(QColor::fromRgb(0, 64, 128) , 2));

    painter.drawLine(0, topMargin, this->width(), topMargin);
    painter.drawLine(this->width() / 2, 0, this->width() / 2, this->height());

    painter.setTransform(QTransform().translate(this->width() / 2, topMargin));

    painter.setPen(QPen(QColor::fromRgb(0, 64, 128), 1));
    painter.drawText(5, -5, "0");
    for(int y = 1; y <= n; ++y)
    {
        painter.drawText(5, y * step - 5, QString::number(y * stepLabel));
        painter.drawLine(-this->width() / 2, y * step, this->width() / 2, y * step);
    }
    for(int x = 1; x <= m; ++x)
    {
        painter.drawText(x * step + 5, -5, QString::number(x * stepLabel));
        painter.drawLine(x * step, -10, x * step, this->height());

        painter.drawText(-x * step + 5, -5, QString::number(-x * stepLabel));
        painter.drawLine(-x * step, -10, -x * step, this->height());
    }

    painter.setTransform(QTransform().translate(this->width() / 2, topMargin).scale(scale, scale));

    painter.setRenderHint(QPainter::Antialiasing);

    //graphic
    painter.setPen(QPen(Qt::red, 2 / scale));

    std::ifstream inputTempFile(Utils::getInstance().getTempfile());

    std::unique_ptr<Point> point1 = std::make_unique<Point>();
    std::unique_ptr<Point> point2 = std::make_unique<Point>();

    inputTempFile >> *point1;
    if(!inputTempFile.fail())
    {
        point1->rotateZ(phi);
        inputTempFile >> *point2;
        while (!inputTempFile.fail())
        {
            point2->rotateZ(phi);
            painter.drawLine(point1->getX(), point1->getZ(), point2->getX(), point2->getZ());
            point1.reset(new Point(*point2));
            inputTempFile >> *point2;
        }
    }

    inputTempFile.close();

    QFrame::paintEvent(paintEvent);
}
