#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"wash.h"
#include <QPainter>
#include<vector>
#include<QString>
#include<QStringList>
#include<QFile>
#include<QTextStream>
#include<qdebug.h>
#include<QRectF>
#include<QColor>
#include <Qtime>
#include<QBrush>
#include<QSound>
#include <QMediaPlayer>
#include <QUrl>
#include<QRect>
#include<QMessageBox>
#include<QMouseEvent>
 int dirx[9]={-1,-1,-1,0,0,0,1,1,1};
int diry[9]={-1,0,1,-1,0,1,-1,0,1};
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
//set_fixed_size
MainWindow::MainWindow(int _hor,int _ver,std::vector<int>&_input,std::vector<int>&_output,bool _want_to_clean,QWidget *parent) :
    QMainWindow(parent),
    //MainWindow(QWidget *parent,int _hor,int _ver, std::vector<int>&_input,std::vector<int>&_output,bool _want_to_clean);
    ui(new Ui::MainWindow),hor(_hor),ver(_ver),input(_input),output(_output),wash(_want_to_clean)
{

    input.push_back(output[0]);input.push_back(output[1]);
    for(int i=0;i<input.size();i+=2){   //上下左右 ,  lt,rt,lb,rb
        if(input[i]==1&&input[i+1]>1&&input[i+1]<ver){
           occupied[std::make_pair(input[i],input[i+1])]=1;
        }else if(input[i]==hor&&input[i+1]>1&&input[i+1]<ver){
            occupied[std::make_pair(input[i],input[i+1])]=2;
        }else if(input[i+1]==1&&input[i]>1&&input[i]<hor){
           occupied[std::make_pair(input[i],input[i+1])]=3;
        }else if(input[i+1]==ver&&input[i]>1&&input[i]<hor){

            occupied[std::make_pair(input[i],input[i+1])]=4;
        }
        else if(input[i]==1&&input[i+1]==1){

            if(corup[1][1]==0){
                corup[1][1]=1;
                occupied[std::make_pair(input[i],input[i+1])]=1;
            }else if(corup[1][1]==1){
                corup[1][1]=2;
                occupied[std::make_pair(input[i],input[i+1])]=5;
            }
        }else if(input[i]==1&&input[i+1]==ver){
            if(corup[0][1]==0){
                corup[0][1]=1;
                occupied[std::make_pair(input[i],input[i+1])]=1;
            }else if(corup[0][1]==1){
                corup[0][1]=2;
                occupied[std::make_pair(input[i],input[i+1])]=6;
            }
        }else if(input[i]==hor&&input[i+1]==1){
            if(corup[1][0]==0){
                corup[1][0]=1;
                occupied[std::make_pair(input[i],input[i+1])]=2;
            }else if(corup[1][0]==1){
                corup[1][0]=2;
                occupied[std::make_pair(input[i],input[i+1])]=7;
            }
        }else if(input[i]==hor&&input[i+1]==ver){
            if(corup[0][0]==0){
                corup[0][0]=1;
                occupied[std::make_pair(input[i],input[i+1])]=2;
            }else if(corup[0][0]==1){
                corup[0][0]=2;
                occupied[std::make_pair(input[i],input[i+1])]=8;
            }
        }

    }
    /*
    for(int i=2;i<hor;i++){
        occupied[std::make_pair(i,1)]=1;  //左右上下
        occupied[std::make_pair(i,ver)]=2;
    }
    for(int i=2;i<ver;i++){
        occupied[std::make_pair(1,i)]=3;
        occupied[std::make_pair(hor,i)]=4;
    }*/

    //occupied[std::make_pair(1,1)]=occupied[std::make_pair(1,ver)]=occupied[std::make_pair(hor,1)]=occupied[std::make_pair(hor,ver)]=2;
    C = new QSound("/Users/kevintung/Desktop/7thQTapp/C.wav");
    D = new QSound("/Users/kevintung/Desktop/7thQTapp/D.wav");
    E = new QSound("/Users/kevintung/Desktop/7thQTapp/E.wav");
    F = new QSound("/Users/kevintung/Desktop/7thQTapp/F.wav");
    G = new QSound("/Users/kevintung/Desktop/7thQTapp/G.wav");
    A = new QSound("/Users/kevintung/Desktop/7thQTapp/A.wav");
    //D = new QSound("/Users/kevintung/Desktop/7thQTapp/B.wav");
    C2 = new QSound("/Users/kevintung/Desktop/7thQTapp/C2.wav");


    timer = new QTimer(this);
    timer->setInterval(200);

    wash_timer = new QTimer(this);
    connect(wash_timer,SIGNAL(timeout()),this,SLOT(advance()));
    wash_timer->setInterval(100);


    connect(timer,SIGNAL(timeout()),this,SLOT(autoplay()));
    //init_frame();
    getInput();
    calculate();
    show();
    ui->setupUi(this);
    //QSound D("/Users/kevintung/Desktop/7thQTapp.D.wav");

    /*QSound F("/Users/kevintung/Desktop/7thQTapp.F.wav");
    QSound G("/Users/kevintung/Desktop/7thQTapp.G.wav");
    QSound A("/Users/kevintung/Desktop/7thQTapp.A.wav");
    QSound B("/Users/kevintung/Desktop/7thQTapp.B.wav");
    QSound C2("/Users/kevintung/Desktop/7thQTapp.C2.wav");*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

\
void MainWindow::on_plainTextEdit_textChanged()
{
    
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{

}


void MainWindow::drawRec(int rs,int posx, int posy){
    QPainter p(this);
        p.translate(posx-rs,posy-rs);

        for(int i=1;i<=hor;i++){
            for(int j=1;j<=ver;j++){
                 QRect qr(j*rs, i*rs,rs,rs);
                 p.drawRect(qr);
                if(clickmap[i][j]){p.setBrush(Qt::lightGray); p.drawRect(j*rs,i*rs,rs,rs); p.setBrush(Qt::transparent);}

                if(current_time==_maxtime)p.drawText(qr,QString::number(all_frame[_maxtime].block[i][j].contaminate_id.size()));
            }
        }
}
void MainWindow::draw_Input_Output(int rs,int x,int y,int posx, int posy){
    qDebug()<<"OOOOOOOO";
    QPainter p(this);
    p.setBrush(Qt::cyan);
    p.translate(posx-rs,posy-rs);
    QString q = "Input";
    QRect qr;
    int size = input.size();
    for(int i=0;i<size;i+=2){
        if(i==size-2){ //output
            p.setBrush(Qt::green);
            q = "Output";
        }
        int x=input[i],y=input[i+1];

    switch (occupied[std::make_pair(x,y)]) {
    case 1:
        qr.setRect(y*rs,x*rs-2*rs,rs,2*rs);p.drawRect(qr);p.drawText(qr,q);

        break;
    case 2:
        qr.setRect(y*rs,x*rs+rs,rs,2*rs);p.drawRect(qr);p.drawText(qr,q);
        break;
    case 3:
        qr.setRect(y*rs-2*rs,x*rs,2*rs,rs);p.drawRect(qr);p.drawText(qr,q);
        break;
    case 4:
        qr.setRect(y*rs+rs,x*rs,2*rs,rs);p.drawRect(qr);p.drawText(qr,q);
        break;
    case 5://tl
        qr.setRect(y*rs,x*rs-2*rs,rs,2*rs);p.drawRect(qr);p.drawText(qr,q);
        qr.setRect(y*rs-2*rs,x*rs,2*rs,rs);p.drawRect(qr);p.drawText(qr,q);
        break;
    case 6://tr
        qr.setRect(y*rs,x*rs-2*rs,rs,2*rs);
        p.drawRect(qr);p.drawText(qr,q);
        qr.setRect(y*rs+rs,x*rs,2*rs,rs);p.drawRect(qr);p.drawText(qr,q);
        break;
    case 7://bl
        qr.setRect(y*rs,x*rs+rs,rs,2*rs);
         p.drawRect(qr);p.drawText(qr,q);
         qr.setRect(y*rs-2*rs,x*rs,2*rs,rs);
        p.drawRect(qr); p.drawText(qr,q);
        break;
    case 8://br
         qr.setRect(y*rs,x*rs+rs,rs,2*rs);
        p.drawRect(qr); p.drawText(qr,q);
        qr.setRect(y*rs+rs,x*rs,2*rs,rs);
        p.drawRect(qr);
        p.drawText(qr,q);
        break;
    default:
        break;
    }
    }

    p.setBrush(Qt::magenta);
    q = "Clean";
    qr.setRect(cleany*rs-2*rs,cleanx*rs,2*rs,rs);
    p.drawRect(qr); p.drawText(qr,q);

    p.setBrush(Qt::lightGray);
    q = "Waste";
    qr.setRect(wastey*rs+rs,wastex*rs,2*rs,rs);
    p.drawRect(qr); p.drawText(qr,q);

}
void MainWindow::getInput(){

    qDebug()<<"entered getInput";
    QString displayString;
    std::vector<Movement> vec;
        QFile file("/Users/kevintung/Desktop/Week1/Input/testcasewash.txt");
         if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             qDebug()<<"MainWindow::getInput readfile error";
         QTextStream in(&file);
         QString line = in.readLine();
        bool isMix = 0;
         while (!line.isNull())
         {
             isMix=0;
             line = line.left(line.length() - 1);
             QStringList parse = line.split(' ');
             Movement mv ;
             mv.mvtime = parse[1].section(',',0,0).QString::toInt();
             mv.mvname=parse[0];
             if(parse[0]=="Input"){
                 mv.have_topos=0;
                 mv.mvposx=parse[1].section(',',1,1).QString::toInt();
                 mv.mvposy=parse[1].section(',',2,2).QString::toInt();
             }else if(parse[0]=="Output"){
                 mv.have_topos=0;
                 mv.mvposx=parse[1].section(',',1,1).QString::toInt();
                 mv.mvposy=parse[1].section(',',2,2).QString::toInt();
             }else if(parse[0]=="Move"){
                 mv.mvposx=parse[1].section(',',1,1).QString::toInt();
                 mv.mvposy=parse[1].section(',',2,2).QString::toInt();
                 mv.toposx=parse[1].section(',',3,3).QString::toInt();
                 mv.toposy=parse[1].section(',',4,4).QString::toInt();
             }else if(parse[0]=="Merge"){
                 mv.mvposx=parse[1].section(',',1,1).QString::toInt();
                 mv.mvposy=parse[1].section(',',2,2).QString::toInt();
                 mv.toposx=parse[1].section(',',3,3).QString::toInt();
                 mv.toposy=parse[1].section(',',4,4).QString::toInt();
                 all_movement.push_back(mv);
                 mv.mvtime++;
                 mv.mvname="Merge2";
             }else if(parse[0]=="Mix"){
                 isMix = 1;
                 //int len = parse[1].length();
                 mv.mvposx=parse[1].section(',',1,1).QString::toInt();
                 mv.mvposy=parse[1].section(',',2,2).QString::toInt();
                 mv.toposx=parse[1].section(',',3,3).QString::toInt(); //假設mix涵蓋至少有兩個位置
                 mv.toposy=parse[1].section(',',4,4).QString::toInt();
                 all_movement.push_back(mv);
                 mv.mvtime++;
                 int i=6;
                 while(!parse[1].section(',',i,i).isNull()){
                 mv.mvposx=parse[1].section(',',i-3,i-3).QString::toInt();
                 mv.mvposy=parse[1].section(',',i-2,i-2).QString::toInt();

                 mv.toposx=parse[1].section(',',i-1,i-1).QString::toInt();
                 mv.toposy=parse[1].section(',',i,i).QString::toInt();
                 all_movement.push_back(mv);
                 mv.mvtime++;
                 i+=2;
                 }

             }else if(parse[0]=="Split"){
                 mv.mvposx=parse[1].section(',',1,1).QString::toInt();
                 mv.mvposy=parse[1].section(',',2,2).QString::toInt();
                 mv.toposx=parse[1].section(',',3,3).QString::toInt();
                 mv.toposy=parse[1].section(',',4,4).QString::toInt();
                 all_movement.push_back(mv);
                 mv.mvtime++;
                 mv.mvname="Split2";

                 //要考慮到另一邊
             }
             //qDebug()<<parse;
             //////
             if(!isMix)all_movement.push_back(mv);
             line = in.readLine();
             displayString.append(line);
         }
      /*for(int i=0;i<all_movement.size();i++){
           qDebug()<<all_movement[i].mvtime<<all_movement[i].mvname<<all_movement[i].mvposx<<all_movement[i].mvposy;
           if(all_movement[i].have_topos)qDebug()<<all_movement[i].toposx<<all_movement[i].toposy;
qDebug()<<endl;
       }*/

         /*for(int i=0;i<all_movement.size();i++){
             if(all_movement[i].have_topos>0)
             qDebug()<<all_movement[i].mvname<<all_movement[i].toposx<<all_movement[i].toposy;
         }*/
         qDebug()<<"leaving getInput";
}

void MainWindow::calculate(){
    qDebug()<<"entered calculate";
    int maxtime=-100;
    int maxpos=-1;
    int allmvsize = all_movement.size();

    for(int i=0;i<allmvsize;i++){
        //qDebug()<<all_movement[i].mvtime;
        int x = all_movement[i].mvtime+
                (all_movement[i].mvname=="Input"||all_movement[i].mvname=="Output"||all_movement[i].mvname=="Mix"||all_movement[i].mvname=="Move"? 1:2);
       //qDebug()<<"x= "<<x;
        if(x>maxtime){maxtime=x;maxpos=i;}

    }

    _maxtime=maxtime; //maxtime 是 最後一步的時間再加1
    lf.maxtime=maxtime;
    //qDebug()<<_maxtime;
//初始化all_frame的所有frame
    //all_frame.resize(_maxtime+2);
   /* for(int i=0;i<=maxtime;i++){
        Frame _frame(i,hor,ver);
        all_frame.push_back(_frame);
    }
    */
    qDebug()<<"initializing frame";
    Frame _frame(0,hor,ver);
    qDebug()<<1;
    all_frame.push_back(_frame);
    qDebug()<<2;
    mv.resize(_maxtime+2);
    qDebug()<<3;
    mv_size.resize(maxtime+2);
    qDebug()<<4;
    //////////
    for(int i=0;i<_maxtime+2;i++){
        mv_size[i]=0;
    }
    //把動作壓進每個frame的棧
    qDebug()<<"pushing all mvment";
    for(int i=0;i<allmvsize;i++){
        //qDebug()<<1;
        int t = all_movement[i].mvtime;
        //qDebug()<<all_frame.size()<<"t="<<t<<" "<<all_movement.size()<<" i= "<<i;
        mv[t].push_back(all_movement[i]);
       // qDebug()<<3;
        mv_size[t]++;
        qDebug()<<mv_size[t]<<"ooooo";
    }

    for(int i=1;i<=_maxtime;i++){
        Frame _f = all_frame[i-1];
        _f.time = i;
        _f.input=_f.output=_f.merge=_f.mix=_f.split=_f.move=0;
        for(int j=0;j<mv_size[i-1];j++){
            qDebug()<<"I="<<i<<"j= "<<j;
            alter_state(_f,mv[i-1][j]);
            _f.printFrame();
        }
        if(i==1||frame_valid(all_frame[i-1],_f)){
        all_frame.push_back(_f);
        }else {
            all_frame.push_back(_f);
            break;
        }
       // printFrame(i);
    }

    //printAllFrame();

}
/*
 *污染：只在merge1,mix,move,split2有設置；剩下在draw函數判斷：是否cshow以及是否have_liquid
 *
 * type只在block存
 */
void MainWindow::alter_state(Frame &f, Movement m){

qDebug()<<"MVNAME="<<m.mvname;
if(m.mvname=="Input"){
    bool input_valid = 0;
    for(int i=0;i<input.size();i+=2){
        if(m.mvposx==input[i]&&m.mvposy==input[i+1])input_valid=1;
    }
    qDebug()<<"Input VALID"<<input_valid;
    if(!input_valid){
        Error("Input Fail");
    }
    f.input=1;
    liquid_number++;
    lf.make_liquid(liquid_number,m.mvposx,m.mvposy,f.time);
    qDebug()<<"AfterInput"<<lf.all_liquid.size();
   f.block[m.mvposx][m.mvposy].liquid = lf.all_liquid[liquid_number];
   qDebug()<<"KKKKKK"<<f.block[m.mvposx][m.mvposy].liquid<<lf.all_liquid[liquid_number];
    //合法性
    f.block[m.mvposx][m.mvposy].have_liquid=liquid_number;
    f.block[m.mvposx][m.mvposy].type=1;

}else if(m.mvname=="Output"){
    bool output_valid = 0;
    if(m.mvposx==output[0]&&m.mvposy==output[1])output_valid=1;
    qDebug()<<"Output VALID"<<output_valid;
    if(!output_valid){
        Error("Output Fail");
    }
    f.block[m.mvposx][m.mvposy].output=1;
    f.output=1;
    //qDebug()<<3;
    //合法性
    f.block[m.mvposx][m.mvposy].contaminate_id.push_back(f.block[m.mvposx][m.mvposy].have_liquid);
    f.block[m.mvposx][m.mvposy].have_liquid=-1;
     f.block[m.mvposx][m.mvposy].liquid->setpos(f.time,-1,-1);
    //f.block[m.mvposx][m.mvposy].liquid->posx[f.time]=-1;
    //f.block[m.mvposx][m.mvposy].liquid->posy[f.time]=-1;
    f.block[m.mvposx][m.mvposy].liquid = nullptr;
    f.block[m.mvposx][m.mvposy].type=0;

}else if(m.mvname=="Merge"){
    f.merge=1;
    //qDebug()<<4;
  liquid_number++;
   f.block[(m.mvposx+m.toposx)/2][(m.mvposy+m.toposy)/2].liquid =
           lf.make_liquid(liquid_number,(m.mvposx+m.toposx)/2,(m.mvposy+m.toposy)/2,f.time);

   all_frame[f.time-1].block[(m.mvposx+m.toposx)/2][(m.mvposy+m.toposy)/2].merge=all_frame[f.time-1].block[m.mvposx][m.mvposy].merge=all_frame[f.time-1].block[m.toposx][m.toposy].merge=1;
   f.block[(m.mvposx+m.toposx)/2][(m.mvposy+m.toposy)/2].merge= f.block[m.mvposx][m.mvposy].merge=f.block[m.toposx][m.toposy].merge=1;


   //污染：壓入污染->把污染顯示設為0->下一步Merge2再打開
    f.block[m.mvposx][m.mvposy].contaminate_id.push_back(f.block[m.mvposx][m.mvposy].have_liquid);
    f.block[m.mvposx][m.mvposy].cshow=0;
   f.block[m.mvposx][m.mvposy].have_liquid=-1;
   f.block[m.mvposx][m.mvposy].liquid->setpos(f.time,-1,-1);
   //f.block[m.mvposx][m.mvposy].liquid->posy[f.time]=-1;
   f.block[m.mvposx][m.mvposy].liquid=nullptr;
  f.block[m.mvposx][m.mvposy].type=0;


  f.block[m.toposx][m.toposy].contaminate_id.push_back(f.block[m.toposx][m.toposy].have_liquid);
  f.block[m.toposx][m.toposy].cshow=0;
  f.block[m.toposx][m.toposy].have_liquid=-1;
   f.block[m.toposx][m.toposy].liquid->setpos(f.time,-1,-1);
 // f.block[m.toposx][m.toposy].liquid->posx[f.time]=-1;
  //f.block[m.toposx][m.toposy].liquid->posy[f.time]=-1;
  f.block[m.toposx][m.toposy].liquid=nullptr;
  f.block[m.toposx][m.toposy].type=0;


  f.block[(m.mvposx+m.toposx)/2][(m.mvposy+m.toposy)/2].have_liquid=liquid_number;
  f.block[(m.mvposx+m.toposx)/2][(m.mvposy+m.toposy)/2].type=(m.mvposx==m.toposx?3:2);

}else if(m.mvname=="Merge2"){
    f.block[(m.mvposx+m.toposx)/2][(m.mvposy+m.toposy)/2].merge= f.block[m.mvposx][m.mvposy].merge=f.block[m.toposx][m.toposy].merge=1;
    f.merge=1;
    f.block[m.mvposx][m.mvposy].cshow=1;
    f.block[m.toposx][m.toposy].cshow=1;
    //qDebug()<<5;

f.block[(m.mvposx+m.toposx)/2][(m.mvposy+m.toposy)/2].type=1;
}else if(m.mvname=="Mix"||m.mvname=="Move"){ //目前暫時沒有區別
f.move=1;
qDebug()<<3;
    f.block[m.toposx][m.toposy].have_liquid=f.block[m.mvposx][m.mvposy].have_liquid;
    f.block[m.toposx][m.toposy].liquid= f.block[m.mvposx][m.mvposy].liquid;
    f.block[m.toposx][m.toposy].type=1;
qDebug()<<4;
 f.block[m.mvposx][m.mvposy].liquid->setpos(f.time,m.toposx,m.toposy);
   // f.block[m.toposx][m.toposy].liquid->posx[f.time]=m.toposx;
    //f.block[m.toposx][m.toposy].liquid->posy[f.time]=m.toposy;
qDebug()<<5;
    f.block[m.mvposx][m.mvposy].contaminate_id.push_back(f.block[m.mvposx][m.mvposy].have_liquid);
    f.block[m.mvposx][m.mvposy].have_liquid=-1;
    f.block[m.mvposx][m.mvposy].liquid= nullptr;
    f.block[m.mvposx][m.mvposy].type=0;

}else if(m.mvname=="Split"){
    f.split=1;
   // qDebug()<<7;
    f.block[m.mvposx][m.mvposy].type=(m.mvposx==m.toposx?3:2);
     f.block[m.mvposx][m.mvposy].split=f.block[m.toposx][m.toposy].split=f.block[2*m.mvposx-m.toposx][2*m.mvposy-m.toposy].split=1;
}else if(m.mvname=="Split2"){
    f.block[m.mvposx][m.mvposy].split=f.block[m.toposx][m.toposy].split=f.block[2*m.mvposx-m.toposx][2*m.mvposy-m.toposy].split=1;
    f.split=1;

    qDebug()<<"mvpos:"<<m.mvposx<<m.mvposy;
    f.block[m.mvposx][m.mvposy].contaminate_id.push_back(f.block[m.mvposx][m.mvposy].have_liquid);
    f.block[m.mvposx][m.mvposy].have_liquid=-1;
     f.block[m.mvposx][m.mvposy].liquid->setpos(f.time,-1,-1);
    //f.block[m.mvposx][m.mvposy].liquid->posx[f.time]=-1;
    //f.block[m.mvposx][m.mvposy].liquid->posy[f.time]=-1;
     f.block[m.mvposx][m.mvposy].liquid=nullptr;
    f.block[m.mvposx][m.mvposy].type=0;


    liquid_number++;
    f.block[m.toposx][m.toposy].liquid = lf.make_liquid(liquid_number,m.toposx,m.toposy,f.time);
    qDebug()<<"topos:"<<m.toposx<<m.toposy;
    f.block[m.toposx][m.toposy].have_liquid=liquid_number;
    f.block[m.toposx][m.toposy].type=1;

    liquid_number++;
    f.block[2*m.mvposx-m.toposx][2*m.mvposy-m.toposy].liquid = lf.make_liquid(liquid_number,2*m.mvposx-m.toposx,2*m.mvposy-m.toposy,f.time);
    qDebug()<<"anotherpos:"<<2*m.mvposx-m.toposx<<2*m.mvposy-m.toposy;
    qDebug()<<liquid_number;
    f.block[2*m.mvposx-m.toposx][2*m.mvposy-m.toposy].have_liquid=liquid_number;
    f.block[2*m.mvposx-m.toposx][2*m.mvposy-m.toposy].type=1;


    }else{//no mvmnt
        //qDebug()<<0;
    }

}

void MainWindow::Cch(){
    C->play();
    E->play();
    G->play();
    C2->play();
}
void MainWindow::Dch(){
    D->play();
    F->play();
    A->play();
    C2->play();
}
void MainWindow::Gch(){
    D->play();
    F->play();
    G->play();
}

void MainWindow::draw_frame(int time,int rs,int posx, int posy){
    qDebug()<<"time"<<time;
int es = 30;
for(int i=1;i<=hor;i++){
    for(int j=1;j<=ver;j++){
        //liquid類
        es=30;
        if(all_frame[time].block[i][j].have_liquid>0){
           // qDebug()<<i<<j;
            QPainter p(this);
            p.setBrush(all_frame[time].block[i][j].liquid->color);
qDebug()<<p.brush().color().red()<<p.brush().color().green()<<p.brush().color().blue();
            if(all_frame[time].block[i][j].type==1){
            p.drawEllipse(posy+(j-1)*rs+(rs-es)/2,posx+(i-1)*rs+(rs-es)/2,es,es);
            }else if(all_frame[time].block[i][j].type==2){
                p.drawEllipse(posy+(j-1)*rs+(rs-es)/2, posx+(i-1)*rs-es  , es,2*es+rs);
            }else if(all_frame[time].block[i][j].type==3){
                 p.drawEllipse( posy+(j-1)*rs-es,posx+(i-1)*rs+(rs-es)/2, 2*es+rs,es);
            }
        }else if(all_frame[time].block[i][j].cshow==1){
            QPainter p(this);
            for(int k=0;k<all_frame[time].block[i][j].contaminate_id.size();k++){
            p.setBrush(lf.all_liquid[all_frame[time].block[i][j].contaminate_id[k]]->color.lighter(200));
            es=20;
            p.drawEllipse(posy+(j-1)*rs+(rs-es)/2,posx+(i-1)*rs+(rs-es)/2,es,es);
            }

        }
    }
}
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    qDebug()<<"IN MOUSE EVENT";
    int x_pix = event->QMouseEvent::x() ,y_pix =event->QMouseEvent::y();
    int m = (x_pix-x_start)/block_size + 1 , n =(y_pix-y_start)/block_size + 1;
    qDebug()<<"m"<<m<<"n"<<n;
    if(in_range(n,m)){
        clickmap[n][m]=(clickmap[n][m]==0?1:0);
    }
    update();
}


void MainWindow::paintEvent(QPaintEvent *){//draw_WASTE!!!
    int spx = x_start ,spy= y_start ;

    qDebug()<<"current_time=<"<<current_time;
    drawRec(block_size,spx,spy);
    draw_Input_Output(block_size,0,0,spx,spy);

    //draw_WASTE!!!
    draw_frame(current_time,block_size,spx,spy);
    if(cleaning){
        qDebug()<<"drawing Bubble";
        draw_Bubble();
    }

    qDebug()<<"paintevent ending";

}

/*
 * 注意：
 */
void MainWindow::printAllFrame(){
    for(int i=0;i<=_maxtime;i++){
        qDebug()<<"t= "<<all_frame[i].time;
        printFrame(i);
    }
}
void Frame::printFrame(){

    QDebug out = qDebug();

        for(int k=1;k<=hor;k++){
            for(int m=1;m<=ver;m++){
                out<<block[k][m].have_liquid;
            }
            out<<endl;
        }

}
void MainWindow::printFrame(int i){
    qDebug()<<"i="<<i;
    QDebug out = qDebug();

        for(int k=1;k<=hor;k++){
            for(int m=1;m<=ver;m++){
                out<<all_frame[i].block[k][m].have_liquid;
            }
            out<<endl;
        }

}

void MainWindow::Error(QString str){

    QMessageBox *msg = new QMessageBox(QMessageBox::NoIcon,"errorTest",str,QMessageBox::Ok,this);
    msg->show();

}
bool MainWindow::frame_valid(Frame f1,Frame f2){
    qDebug()<<"entering frame_valid, time: "<<f1.time<<f2.time;
    for(int i=1;i<=liquid_number;i++){
        Liquid *l = lf.all_liquid[i];
        qDebug()<<"i="<<i;qDebug()<<"id="<<l->id;
        if(l->posx[f2.time]!=-1){ //代表f2.time(後者時間)時這個液滴在上面
            for(int j=0;j<9;j++){
                if(j==4)j=5;
                qDebug()<<"j="<<j;
                int prevx = l->posx[f2.time]+dirx[j],prevy=l->posy[f2.time]+diry[j];
                 //qDebug()<<;
                 int nowx = l->posx[f2.time]+dirx[j], nowy=l->posy[f2.time]+diry[j];
                if(in_range(prevx,prevy)&&in_range(nowx,nowy)){
                    int prev=f1.block[prevx][prevy].have_liquid;
                    int now = f2.block[nowx][nowy].have_liquid;
                     qDebug()<<"now="<<now;
                    if(  ((prev>0 && prev!=l->id) //九宮格在上一張圖有液體，且是其他液體
                            ||(now>0&&now!=l->id))  //現在的周圍有液滴
                                 &&(!(f1.block[prevx][prevy].merge&&f2.block[nowx][nowy].merge)&&!(f1.block[prevx][prevy].split&&f2.block[nowx][nowy].split)&&!(f2.block[nowx][nowy].output)  ))
                        { qDebug()<<"pre?"<<(prev>0 && prev!=l->id)<<"now??"<<(now>0);
                         qDebug()<<"prev"<<prev<<"prex"<<prevx<<"nowy"<<nowy<<"l_id"<<l->id;
                        //qDebug()<<"now"<<now<<"nowx"<<nowx<<"nowy"<<nowy<<"l_id"<<l->id;

                        return 0; }
                }
            }
        }
    }
    return 1;
}
#include <QTextStream>

void MainWindow::play(){
   // bubblex=bubbley
     QTextStream outt(stdout);
    qDebug()<<"Entering Play()";
    if(current_time>1&&!frame_valid(all_frame[current_time-1],all_frame[current_time])){
        Error("Frame Invalid");
    }
    if(current_time>0){
        //qDebug()<<all_frame[9].merge<<all_frame[10].merge<<"LLL";
        if(all_frame[current_time].move||all_frame[current_time].mix)C->play();
        if(all_frame[current_time].split)E->play();
        if(all_frame[current_time].input)Dch();
        if(all_frame[current_time].output)Cch();
        if(all_frame[current_time].merge)G->play();
    }

    update();
    ui->lcdNumber->display(current_time);
    qDebug()<<1;
    ///////
    qDebug()<<"Entering if(wash)";
    if(wash){
       setmap();
       qDebug()<<2;
       int posx=cleanx,posy=cleany;
       wash_vec.clear();
       if(realmap[posx][posy]!=1&&realmap[wastex][wastey]!=1){
           realmap[posx][posy]=2;
           qDebug()<<posx<<posy;
           DFS(wash_vec,cleanx,cleany,posx,posy);
       }
       qDebug()<<3;
       QDebug outt = qDebug();
       //for(int i=0;i<wash_vec.size();i++)outt<<wash_vec[i]<<" "<<endl;

       if(realmap[wastex][wastey]==2){
           qDebug()<<4;
           std::vector<int> vec2 ;
           qDebug()<<wash_vec.size()<<posx<<posy;
           qDebug()<<"Entering to_output";
           realmap[posx][posy]=3;
           to_output(vec2,posx,posy);
           qDebug()<<vec2.size()<<"LL";
           for(int k=0;k<vec2.size();k++)wash_vec.push_back(vec2[k]);
           wash_iter=0;
           bubblex = cleanx;
           bubbley = cleany;

           draw_Bubble(); update();

           wash_timer->start(5);
           qDebug()<<wash_timer->isActive()<<"POIU";
       }else{
           ui->nextButton->setEnabled(1);
           ui->prevButton->setEnabled(1);
           ui->allButton->setEnabled(1);
           ui->restartButton->setEnabled(1);
       }
       qDebug()<<5;
    }
    qDebug()<<"WASHVEC";
for(int p=0;p<wash_vec.size();p++)qDebug()<<wash_vec[p];
    qDebug()<<"RRRRRR";
}
void MainWindow::autoplay(){

    if(current_time<_maxtime){
        ui->nextButton->setEnabled(0);
        ui->prevButton->setEnabled(0);
        ui->allButton->setEnabled(0);
        ui->restartButton->setEnabled(0);
        current_time++;
        play();

    }else{
        timer->stop();
        ui->nextButton->setEnabled(1);
        ui->prevButton->setEnabled(1);
        ui->allButton->setEnabled(1);
        ui->restartButton->setEnabled(1);
    }
}

void MainWindow::on_nextButton_clicked() //限制其他點擊
{

    if(current_time<_maxtime){//不能讓他大於maxtime
        if(wash){
            cleaning = 1;
        ui->nextButton->setDisabled(1);
        ui->prevButton->setDisabled(1);
        ui->allButton->setDisabled(1);
        ui->restartButton->setDisabled(1);
        }
    current_time++;
    play();
    } //else??

}

void MainWindow::on_prevButton_clicked()
{
    if(current_time>0){
    current_time--;
play();

    } //else?

}

void MainWindow::on_allButton_clicked()
{
    timer->start();
}

void MainWindow::on_restartButton_clicked()
{

    current_time=0;
    play();
}
/*void MainWindow::init_frame(){
    Frame frame(0,hor,ver);
    std::vector<Block> tempvec;
    frame.block.resize(hor+2);
    for(int i=0;i<=hor;i++){
        frame.block.push_back(tempvec); //空的0號vector
    }

    for(int i=0;i<=hor;i++){

        for(int j=0;j<=ver;j++){
            Block tempblock(i,j);
            frame.block[i].push_back(tempblock);
        }
    }

    all_frame.push_back(frame);

}
*/
