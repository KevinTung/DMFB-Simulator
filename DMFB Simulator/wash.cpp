#include "wash.h"
#include "mainwindow.h"
#include "qdebug.h"
#include<QPainter>
void MainWindow::setmap(){
    QDebug out = qDebug();
    qDebug()<<"Entering setmap()";
    for(int i=1;i<=hor;i++){
        for(int j=1;j<=ver;j++){
            realmap[i][j]=0;

        }
    }
    qDebug()<<"current_time "<<current_time<<endl;
    for(int i=1;i<=hor;i++){
         qDebug()<<i;
        for(int j=1;j<=ver;j++){
              qDebug()<<"i "<<i<<" j "<<j;
            if(all_frame[current_time].block[i][j].have_liquid>0){
                realmap[i][j]=1;
                for(int k=0;k<9;k++){
                    if(k==4)k=5;
                    if(in_range(i+dirx[k],j+diry[k])){
                        realmap[i+dirx[k]][j+diry[k]]=1;
                    }
                }
            }
             qDebug()<<9;
            if(clickmap[i][j]){realmap[i][j]=1; qDebug()<<99999;}
        }
    }
    for(int i=1;i<=hor;i++){
        for(int j=1;j<=ver;j++){
            out<<realmap[i][j]<<" ";
        }
        out<<endl;
    }

}
#include <QTextStream>
int MainWindow::DFS(std::vector<int>&vec,int x,int y ,int &px, int &py){
    //QDebug out = qDebug();
     QTextStream outt(stdout);
   outt<<1<<" x "<<x<<" y "<<y<<" px "<<px<<" py "<<py<<endl;
    for(int i=1;i<=hor;i++){
        for(int j=1;j<=ver;j++){

           outt<<realmap[i][j]<<" ";
        }
        outt<<endl;
    }
    outt<<endl;
    bool all_blocked=1;
    qDebug()<<"REALMAPTEST  4 4"<<realmap[4][4];
     for(int i=1;i<9;i+=2){
         if(in_range(x+dirx[i],y+diry[i])){
             if(realmap[x+dirx[i]][y+diry[i]]==0){  //1 or 2 都不行
                all_blocked=0;
                vec.push_back(i);
                px+=dirx[i]; py+=diry[i];
                realmap[x+dirx[i]][y+diry[i]]=2;
                DFS(vec,x+dirx[i],y+diry[i],px,py);
                vec.push_back(8-i); //神！！！！
                 px-=dirx[i]; py-=diry[i];
             }
         }
     }
     return all_blocked;
}


int MainWindow::to_output(std::vector<int> &vec,int px,int py){
    qDebug()<<"ENtered to_output:";
    if(px==wastex&&py==wastey)return 1;
    qDebug()<<1;
    for(int i=1;i<8;i+=2){
        if(in_range(px+dirx[i],py+diry[i])){
            if(realmap[px+dirx[i]][py+diry[i]]==2){
                realmap[px+dirx[i]][py+diry[i]]=3;
                qDebug()<<px+dirx[i]<<py+diry[i];
                vec.push_back(i);
                if(to_output(vec,px+dirx[i],py+diry[i])==1)return 1;
                vec.push_back(8-i); //神！！！！
            }
        }
    }
    return 0;
}
void MainWindow::draw_Bubble(){
    if(in_range(bubblex,bubbley)){
    QPainter p(this);
    p.setBrush(Qt::blue);
    p.translate(y_start-block_size,x_start-block_size);
    p.drawEllipse(bubbley*block_size,bubblex*block_size,block_size,block_size);
    }
}

void MainWindow::advance(){ //從起始點的狀態 經過第iter步 到下一個狀態 並顯示這個狀態
     int dir = wash_vec[wash_iter];
     qDebug()<<"GET TIMER , iter = "<<wash_iter <<"currenttime"<<current_time<<"washvecsize"<<wash_vec.size()<<"bubx+dirx"<<bubblex+dirx[dir]<<"buby+diry"<<bubbley+diry[dir];

    bubblex+=dirx[dir]; bubbley+=diry[dir];
    if(int csize = all_frame[current_time].block[bubblex][bubbley].contaminate_id.size()){
        qDebug()<<"Cleaning contaminate"<<"csize"<<csize;
        for(int i=csize-1;i>=0;i--){
            int id = all_frame[current_time].block[bubblex][bubbley].contaminate_id[i];
            qDebug()<<"i="<<i<<"id"<<id;
            for(int p=current_time+1;p<=_maxtime;p++){
                int psize = all_frame[p].block[bubblex][bubbley].contaminate_id.size();

                for(int k=0;k<psize;k++){
                    qDebug()<<"p="<<p<<"k"<<k<<"psize"<<psize;
                    if(all_frame[p].block[bubblex][bubbley].contaminate_id[k]==id){
                        all_frame[p].block[bubblex][bubbley].contaminate_id.erase(
                           all_frame[p].block[bubblex][bubbley].contaminate_id.begin()+k);
                        qDebug()<<"erase";
                        psize--; k--;
                        //all_frame[p].block[bubblex][bubbley].contaminate_id.shrink_to_fit();
                        qDebug()<<"vecleft"<< all_frame[p].block[bubblex][bubbley].contaminate_id.size();
                    }


                }
            }
            all_frame[current_time].block[bubblex][bubbley].contaminate_id.pop_back();
        }
    }


    update();

    if(++wash_iter==wash_vec.size()){
        wash_timer->stop();
        cleaning = 0;
        bubblex = bubbley=0;
        qDebug()<<"WASH timer stopped";
        ui->nextButton->setEnabled(1);
        ui->prevButton->setEnabled(1);
        ui->allButton->setEnabled(1);
        ui->restartButton->setEnabled(1);
        /*if(current_time==_maxtime){
            all_end=1;
        }*/

    }
    qDebug()<<"advance ending";
}
