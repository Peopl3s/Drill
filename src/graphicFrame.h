#ifndef GRAPHICFRAME_H
#define GRAPHICFRAME_H

#include <QWidget>
#include <QFrame>
#include <QPainter>

#include <string>

class GraphicFrame : public QFrame
{
    Q_OBJECT
public:
    explicit GraphicFrame(QWidget *parent = nullptr);
    void clear();
    void draw(const double &phi = 0);
    void setPhi(const double &phi = 0);
protected:
    void paintEvent(QPaintEvent *);
private:
    bool isDraw = false;
    double phi = 0;
};

#endif
