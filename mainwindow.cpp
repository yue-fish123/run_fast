#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    character = new Character(this); // 创建 Character 对象
    character->setGeometry(0, 0, this->width(), this->height()); // 设置 Character 的大小和位置
    character->show(); // 显示 Character

}

MainWindow::~MainWindow()
{
    delete ui;
}
