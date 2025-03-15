#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "character.h"
#include "tile.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Character *character;

    Tile *m_tile;
};
#endif // MAINWINDOW_H
