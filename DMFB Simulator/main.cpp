#include "mainwindow.h"
#include <QApplication>
#include"initwindow.h"
//#include<QGraphicsScene>
//#include<QGraphicsView>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    InitWindow *init = new InitWindow(0);
    //MainWindow w;
    /*QGraphicsScene scene;
        scene.addLine(0, 0, 150, 150);

        QGraphicsView view(&scene);
        view.setWindowTitle("Graphics View");
        view.resize(500, 500);
        view.show();
*/
    init->show();
    return a.exec();
}
