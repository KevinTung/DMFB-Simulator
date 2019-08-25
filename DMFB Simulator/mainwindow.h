#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<vector>
#include"frame.h"
#include<QSound>
#include<QTimer>
#include<map>
#include"ui_mainwindow.h"

#define cleanx 1
#define cleany 1
#define wastex hor
#define wastey ver
#define x_start 150
#define y_start 150
#define block_size 50

extern int dirx[9];
extern int diry[9];
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int hor,ver;
    std::vector<int>input;
    int corup[2][2]={{}};
    bool hoplt=0,hoprt=0,hoplb=0,hoprb=0;
    std::map<std::pair<int,int>,int>occupied;
    std::map<std::pair<int,int>,int>outoccupied;
    std::vector<int>output;
    std::vector<Movement> all_movement;
    std::vector<Movement> zeromv;
   // bool want_to_clean;
    std::vector<Frame> all_frame;
    std::vector<std::vector<Movement> > mv;
    std::vector<int>mv_size;
    int liquid_number=0;
    int current_time=0;
    int _maxtime;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //func
    MainWindow(int _hor,int _ver, std::vector<int>&_input,std::vector<int>&_output,bool _want_to_clean=0,QWidget *parent=0);
    void drawRec(int rs,int posx, int posy);
    void draw_Input_Output(int rs,int x,int y,int posx, int posy);

    void draw_frame(int time,int rs,int posx, int posy);
    void init_frame();
    void getInput();
    void calculate();
    void alter_state(Frame &f, Movement m);
    void printAllFrame();
    void printFrame(int x);
    inline bool in_range(int x,int y){
        return x>=1&&x<=hor&&y>=1&&y<=ver;
    }
     Liquid_Factory lf; //static 小心
    void move(int time,int id ,int down,int right);
QSound *C,*D,*E,*F,*G,*A,*B,*C2;
void Cch(); void Dch();void Gch();
void play();
void Error(QString str);
bool frame_valid(Frame f1,Frame f2);
QTimer *timer;

//wash ///////////////
bool wash; //一開始要被設置
QTimer *wash_timer; //未被初始
bool clickmap[14][14]={{}};
int realmap[14][14]={{}};
void setmap();
//std::vector<int>is_accessable(int &px, int &py);
int to_output(std::vector<int> &vec,int px,int py);

bool cleaning = false;
 void draw_Bubble();
 std::vector<int> wash_vec;
 int wash_iter, bubblex,bubbley;
int DFS (std::vector<int>&vec,int x,int y ,int &px, int &py);

bool all_end = 0;



 private slots:
    void on_tableWidget_cellClicked(int row, int column);


private slots:
    void on_plainTextEdit_textChanged();
    void on_nextButton_clicked();

    void on_prevButton_clicked();

    void on_allButton_clicked();

    void on_restartButton_clicked();
    void autoplay();
    void advance();

protected:
void paintEvent(QPaintEvent *);
void mousePressEvent(QMouseEvent *event);
private:
    Ui::MainWindow *ui;


};



#endif // MAINWINDOW_H
