#ifndef FRAME_H
#define FRAME_H
#include <vector>
#include<QString>
#include<QColor>
#include<QTime>
#include<qdebug.h>
#define TRANSPARENCY 150
QColor getRandColor(int transparency);
struct Movement{
    Movement(int t,QString name,int x,int y);
    Movement();
int mvtime;
QString mvname;
int mvposx,mvposy;
bool have_topos=1;
int toposx,toposy;
};
QColor getHSVRandColor(int s,int v,int transparency);
class Liquid{
public:
    int id;
    void move(int down, int right);
    void moveto(int x,int y);
    void merge(Liquid &obj);
    void split(int down,int right);
    QColor color;
    int possize=0;
    inline void setpos(int t,int x,int y){
        qDebug()<<1;
        if(possize<=t){
            posx.resize(t+10);
            posy.resize(t+10);
            for(int i=possize;i<t;i++)posx[i]=posy[i]=-1;
        }
         qDebug()<<2;
        posx[t]=x;
        posy[t]=y;
    }

    std::vector<int>posx;std::vector<int>posy;
    Liquid(int _id,int _posx,int _posy,int time,int maxtime):id(_id){
        color = getRandColor(TRANSPARENCY);
        posx.resize(time+10);
        posy.resize(time+10);
         qDebug()<<3;
        for(int i=0;i<time;i++)posx[i]=posy[i]=-1;
        posx[time]=_posx;
        posy[time]=_posy;
         qDebug()<<4;
       // color = getHSVRandColor(150,150,TRANSPARENCY);
        //qDebug()<<"id="<<id<<"";
        //qDebug()<<"RGB "<<color.red()<<color.green()<<color.blue();
    }
};

class Block{
public:
    bool split=0,merge=0,output=0;
    Liquid* liquid;
    Block();
    Block(int _posx,int _posy);
    int posx,posy,have_liquid=-1;
    int type=0;//0 blank, 1,haveliquid, 2 horizontally pulled 3 vertically pulled
    std::vector<int> contaminate_id;
    bool cshow=1;
};
class Frame{
public:
    int time,ver,hor;
bool merge=0,split=0,move=0,mix=0,input=0,output=0;
    int mvsize=0;
    Frame();
    Frame(int x,int hor,int ver);

   //Frame(const Frame &f);
    void printFrame();
    std::vector<std::vector<Block> > block;
};

class Liquid_Factory{
public:
int maxtime=0;
    int liquid_count=0;
    std::vector<Liquid*> all_liquid;
    Liquid* make_liquid(const int & id,const int & posx, const int &posy,int time){
        Liquid * liq = new Liquid(id,posx,posy,time,maxtime);
         qDebug()<<6;
        all_liquid.push_back(liq);
        qDebug()<<"LLLLL"<<all_liquid.size()<<id;
        liquid_count++;
        return liq;
    }
    Liquid_Factory(){
        make_liquid(0,0,0,0);
        liquid_count++;
        qDebug()<<"after Liq_fac construct all_liq size"<<all_liquid.size();
    }
    ~Liquid_Factory(){
        for(int i=0;i<liquid_count;i++){
            if(all_liquid[i]!=nullptr)
            delete all_liquid[i];
        }
    }

};




#endif // FRAME_H
