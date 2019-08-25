#ifndef INITWINDOW_H
#define INITWINDOW_H

#include <QMainWindow>
#include<QString>
#include "mainwindow.h"
namespace Ui {
class InitWindow;
}

class InitWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit InitWindow(QWidget *parent = 0);
    void Error(QString str);
    inline bool in_range(int x,int y,int hor,int ver){
        return x>=1&&x<=hor&&y>=1&&y<=ver;
    }
    ~InitWindow();


public slots:
    void on_pushButton_OK_clicked();

private:
    Ui::InitWindow *ui;
};

#endif // INITWINDOW_H
