#ifndef CHARACTER_H
#define CHARACTER_H

#include "qgraphicsitem.h"
#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QList>
#include <QObject>

class Character : public QWidget
{
    Q_OBJECT
public:
    explicit Character(QWidget *parent = nullptr);
    // 开始向左移动动画
    void startMovingLeft();
    // 开始向右移动动画
    void startMovingRight();
    // 停止移动动画
    void stopMoving();

protected:
    void keyPressEvent(QKeyEvent *event) ;
    void keyReleaseEvent(QKeyEvent *event) ;
    void paintEvent(QPaintEvent *event) ;

private:
    int xPos;
    int yPos; // 某一时刻的坐标

    QPixmap characterPixmap;
    QPixmap scaledPixmap;
    QPixmap currentPixmap;
    bool isJumpling; // 判断是否跳起
    double Initail_V; // 重力方向的初速度
    double Current_V; // 重力方向的竖直速度
    double gravity; // 模拟重力加速度

    double speed;
    bool isMovingLeft;
    bool isMovingRight;
    double a;
    double horonzital_V;
    double jerk;

    QTimer *timer;

    QTimer *animationTimer;
    QList<QPixmap> leftFrames;
    QList<QPixmap> rightFrames;
    int currentFrameIndex;

private slots:
    //更新角色位置坐标
    void updatePosition();
    // 更新动画帧
    void updateAnimationFrame();
};

#endif // CHARACTER_H
