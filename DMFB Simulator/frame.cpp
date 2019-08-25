#include "frame.h"
#include<qdebug.h>
#include<mainwindow.h>
QColor getRandColor(int transparency){
    qDebug()<<"entered getrand";
    int r,g,b;
    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
    r = rand() % 256;
    g = rand() % 256;
    b = rand() % 256;
    QColor c(r,g,b,transparency);
    qDebug()<<r<<g<<b;
    return c;
}
QColor getHSVRandColor(int s,int v,int transparency){
    qDebug()<<"entered getHSVrand";
    int h;
    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
    h = rand() % 360;
    QColor c(h,s,v,transparency);
    qDebug()<<h<<s<<v;
    return c;
}
Frame::Frame()
{

}
Frame::Frame(int x,int _hor,int _ver):time(x),hor(_hor),ver(_ver)
{
    qDebug()<<"entering Frame()";

    std::vector<Block> bvec;
    Block b;
for(int i=0;i<=hor;i++){
    block.push_back(bvec);
    for(int j=0;j<=ver;j++){
        block[i].push_back(b);
    }
}

//qDebug()<<hor<<ver;
//qDebug()<<"time = "<<time<<"size= "<<block.size();
//Movement m;
//mv.push_back(m);


}

Movement::Movement(int t,QString name,int x,int y):mvtime(t),mvname(name),mvposx(x),mvposy(y){

}
Movement::Movement(){

}

Block::Block(){

}
Block::Block(int _posx, int _posy):posx(_posx),posy(_posy){

}
/*MainWindow::move(int time,Liquid* liq ,int down,int right){
    all_frame[time].block[liq->posx+down][liq->posy+right].liquid

}

void moveto(int x,int y);
void merge(Liquid &obj);
void split(int down,int right);
*/
/*
if(m.mvname=="Input"){

    liquid_number++;

    lf.make_liquid(liquid_number,m.mvposx,m.mvposy);

   f.block[m.mvposx][m.mvposy].liquid = lf.all_liquid[liquid_number];
   qDebug()<<"KKKKKK"<<f.block[m.mvposx][m.mvposy].liquid<<lf.all_liquid[liquid_number];
    //合法性
    f.block[m.mvposx][m.mvposy].have_liquid=liquid_number;
    f.block[m.mvposx][m.mvposy].type=1;

}else if(m.mvname=="Output"){
    //qDebug()<<3;
    //合法性
    f.block[m.mvposx][m.mvposy].contaminate_id.push_back(f.block[m.mvposx][m.mvposy].have_liquid);
    f.block[m.mvposx][m.mvposy].have_liquid=-1;
    f.block[m.mvposx][m.mvposy].liquid->posx=-1;
    f.block[m.mvposx][m.mvposy].liquid->posy=-1;
    f.block[m.mvposx][m.mvposy].liquid = nullptr;
    f.block[m.mvposx][m.mvposy].type=0;

}else if(m.mvname=="Merge"){
    //qDebug()<<4;
  liquid_number++;
   f.block[(m.mvposx+m.toposx)/2][(m.mvposy+m.toposy)/2].liquid =
           lf.make_liquid(liquid_number,(m.mvposx+m.toposx)/2,(m.mvposy+m.toposy)/2);

   //污染：壓入污染->把污染顯示設為0->下一步Merge2再打開
    f.block[m.mvposx][m.mvposy].contaminate_id.push_back(f.block[m.mvposx][m.mvposy].have_liquid);
    f.block[m.mvposx][m.mvposy].cshow=0;
   f.block[m.mvposx][m.mvposy].have_liquid=-1;
   f.block[m.mvposx][m.mvposy].liquid->posx=-1;
   f.block[m.mvposx][m.mvposy].liquid->posy=-1;
   f.block[m.mvposx][m.mvposy].liquid=nullptr;
  f.block[m.mvposx][m.mvposy].type=0;


  f.block[m.toposx][m.toposy].contaminate_id.push_back(f.block[m.toposx][m.toposy].have_liquid);
  f.block[m.toposx][m.toposy].cshow=0;
  f.block[m.toposx][m.toposy].have_liquid=-1;
  f.block[m.toposx][m.toposy].liquid->posx=-1;
  f.block[m.toposx][m.toposy].liquid->posy=-1;
  f.block[m.toposx][m.toposy].liquid=nullptr;
  f.block[m.toposx][m.toposy].type=0;


  f.block[(m.mvposx+m.toposx)/2][(m.mvposy+m.toposy)/2].have_liquid=liquid_number;
  f.block[(m.mvposx+m.toposx)/2][(m.mvposy+m.toposy)/2].type=(m.mvposx==m.toposx?3:2);

}else if(m.mvname=="Merge2"){
    f.block[m.mvposx][m.mvposy].cshow=1;
    f.block[m.toposx][m.toposy].cshow=1;
    //qDebug()<<5;

f.block[(m.mvposx+m.toposx)/2][(m.mvposy+m.toposy)/2].type=1;
}else if(m.mvname=="Mix"||m.mvname=="Move"){ //目前暫時沒有區別


    f.block[m.toposx][m.toposy].have_liquid= f.block[m.mvposx][m.mvposy].have_liquid;
    f.block[m.toposx][m.toposy].liquid= f.block[m.mvposx][m.mvposy].liquid;
    f.block[m.toposx][m.toposy].type=1;

    f.block[m.toposx][m.toposy].liquid->posx=m.toposx;
    f.block[m.toposx][m.toposy].liquid->posy=m.toposy;

    f.block[m.mvposx][m.mvposy].contaminate_id.push_back(f.block[m.mvposx][m.mvposy].have_liquid);
    f.block[m.mvposx][m.mvposy].have_liquid=-1;
    f.block[m.mvposx][m.mvposy].liquid= nullptr;
    f.block[m.mvposx][m.mvposy].type=0;

}else if(m.mvname=="Split"){
   // qDebug()<<7;
    f.block[m.mvposx][m.mvposy].type=(m.mvposx==m.toposx?3:2);

}else if(m.mvname=="Split2"){
    qDebug()<<"mvpos:"<<m.mvposx<<m.mvposy;
    f.block[m.mvposx][m.mvposy].contaminate_id.push_back(f.block[m.mvposx][m.mvposy].have_liquid);
    f.block[m.mvposx][m.mvposy].have_liquid=-1;
    f.block[m.mvposx][m.mvposy].liquid->posx=-1;
    f.block[m.mvposx][m.mvposy].liquid->posy=-1;
     f.block[m.mvposx][m.mvposy].liquid=nullptr;
    f.block[m.mvposx][m.mvposy].type=0;


    liquid_number++;
    f.block[m.toposx][m.toposy].liquid = lf.make_liquid(liquid_number,m.toposx,m.toposy);
    qDebug()<<"topos:"<<m.toposx<<m.toposy;
    f.block[m.toposx][m.toposy].have_liquid=liquid_number;
    f.block[m.toposx][m.toposy].type=1;

    liquid_number++;
    f.block[2*m.mvposx-m.toposx][2*m.mvposy-m.toposy].liquid = lf.make_liquid(liquid_number,2*m.mvposx-m.toposx,2*m.mvposy-m.toposy);
    qDebug()<<"anotherpos:"<<2*m.mvposx-m.toposx<<2*m.mvposy-m.toposy;
    qDebug()<<liquid_number;
    f.block[2*m.mvposx-m.toposx][2*m.mvposy-m.toposy].have_liquid=liquid_number;
    f.block[2*m.mvposx-m.toposx][2*m.mvposy-m.toposy].type=1;


    }else{//no mvmnt
        //qDebug()<<0;
    }
*/
