#include "character.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QPainter>

Character::Character(QWidget *parent) :QWidget(parent), xPos(0), yPos(460)
{
    // 设置该窗口可以接收键盘焦点
    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    // 加载角色图片资源
   // characterPixmap.load("E:/我的项目/Qt/Run_Fast/res/奶龙图片帧/nailong0.png");
    // 缩放角色图片
    if (!characterPixmap.load("E:/我的项目/Qt/Run_Fast/res/奶龙图片帧/nailong0.png")) {
        qDebug() << "Failed to load character image!";
    }

    // 初始化跳高有关的参数
    Initail_V = -40;
    Current_V = 0;
    gravity = 5;
    isJumpling = false;

    // 初始化水平运动有关参数
    horonzital_V = 20;
    speed = 0;
    a = 5;
    jerk = 2;
    isMovingLeft = false;
    isMovingRight = false;

    // 初始化定时器
    timer = new QTimer(this);
    // 关联定时器溢出信号和相应的槽函数
    connect(timer, &QTimer::timeout, this, &Character::updatePosition);
    timer->start(25);

    // 加载向左移动的动画帧
    for (int i = 1; i <= 5; ++i) {
        QString leftFramePath = QString("E:/我的项目/Qt/Run_Fast/res/奶龙图片帧/nailong_left%1.png").arg(i);
        //leftFrames.append(QPixmap(leftFramePath));
        QPixmap frame;
        if (frame.load(leftFramePath)) {
            leftFrames.append(frame);
        } else {
            qDebug() << "Failed to load left frame: " << leftFramePath;
        }
    }

    // 加载向右移动的动画帧
    for (int i = 1; i <= 5; ++i) {
        QString rightFramePath = QString("E:/我的项目/Qt/Run_Fast/res/奶龙图片帧/nailong_right%1.png").arg(i);
        //rightFrames.append(QPixmap(rightFramePath));
        QPixmap frame;
        if (frame.load(rightFramePath)) {
            rightFrames.append(frame);
        } else {
            qDebug() << "Failed to load right frame: " << rightFramePath;
        }
    }

    currentFrameIndex = 0;

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Character::updateAnimationFrame);

}


void Character::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        if (!isJumpling) {
            isJumpling = true;
            Current_V = Initail_V;
        }
        break;
    case Qt::Key_Left:
        startMovingLeft();
        isMovingLeft = true;
        isMovingRight=false;
        break;
    case Qt::Key_Right:
        startMovingRight();
        isMovingRight = true;
        isMovingLeft=false;
        break;
    default:
        QWidget::keyPressEvent(event);
    }
    // 触发重绘事件
    update();
}

void Character::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        isMovingLeft = false;
        speed = 0;
        a = 5;
        stopMoving();
        break;
    case Qt::Key_Right:
        isMovingRight = false;
        speed = 0;
        a = 5;
        stopMoving();
        break;
    default:
        QWidget::keyReleaseEvent(event);
    }
}

void Character::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    // 绘制角色图片
    if (!currentPixmap.isNull()) {
        QPixmap scaledPixmap = currentPixmap.scaled(currentPixmap.width() / 4, currentPixmap.height() / 4);
        painter.drawPixmap(xPos, yPos, scaledPixmap);
    }
}

void Character::updatePosition()
{
    // 处理竖直方向运动
    if (isJumpling) {
        Current_V += gravity;
        yPos += Current_V;

        if (yPos>=480) {
            yPos =480;
            isJumpling = false;
        }
    }

    // 处理水平方向运动
    if (isMovingLeft || isMovingRight) {
        a += jerk;
        speed += a;
        if (speed > horonzital_V) {
            a = 5;
            speed = horonzital_V;
        }

        if (isMovingLeft) {
            xPos -= speed;
            if (xPos <= 0) {
                xPos = 0;
            }
        }
        if (isMovingRight) {
            xPos += speed;
            if (xPos > 645) {
                xPos =645;
            }
        }
    }

    // 触发重绘事件
    update();
}

void Character::startMovingLeft() {
    if (!animationTimer->isActive()) {
        animationTimer->start(15); // 每15毫秒更新一帧
        currentPixmap=leftFrames[currentFrameIndex];
        update();
    }
}

void Character::startMovingRight() {
    if (!animationTimer->isActive()) {
        animationTimer->start(15); // 每15毫秒更新一帧
        currentPixmap=rightFrames[currentFrameIndex];
        update();
    }
}

void Character::stopMoving() {
    if (animationTimer->isActive()) {
        animationTimer->stop();
        currentPixmap=characterPixmap;
    }
}

void Character::updateAnimationFrame() {
    currentFrameIndex = (currentFrameIndex + 1) % (isMovingLeft ? leftFrames.size() : rightFrames.size());
    if (isMovingLeft) {
        currentPixmap=leftFrames[currentFrameIndex];
    } else if(isMovingRight) {
        currentPixmap=rightFrames[currentFrameIndex];
    }
}
