#include "initwindow.h"
#include "ui_initwindow.h"
#include <string>
#include <vector>
#include <QString>
#include <qdebug.h>
#include "mainwindow.h"
using namespace std;
InitWindow::InitWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InitWindow)
{
    ui->setupUi(this);
    //QObject::connect()
}

InitWindow::~InitWindow()
{
    delete ui;
}

void InitWindow::on_pushButton_OK_clicked() //差：output 合法判斷
{
    int hor = ui->lineEdit_hor->text().QString::toInt(),ver = ui->lineEdit_ver->text().QString::toInt();
    QString input = ui->lineEdit_input->text();
    QString output = ui->lineEdit_output->text();
    bool wash = ui->wash_check_box->isChecked(); ///是這個？
    int input_len = input.length();
    //if(input_len數字是偶數個)合法
    vector<int> vec;
    int record = 0;
    QString temp;
    for(int i=0;i<input_len;i++){
      if(input[i]==','){
       temp = input.mid(record,i-record);

          //qDebug()<<"i="<<i<<" "<<"record = "<<record<<"temp= "<<temp;
          record = i+1;
          vec.push_back(temp.QString::toInt());
      }
    }
    temp = input.mid(record,input_len-record);
        vec.push_back(temp.QString::toInt());


    std::vector<int> vec_out;
    vec_out.push_back(output.mid(0,1).QString::toInt());vec_out.push_back(output.mid(2,1).QString::toInt());
    bool valid = 1;

    for(int i=0;i<vec.size();i+=2){
        //qDebug()<<vec[i]<<vec[i+1];
    if(!(vec[i]==1||vec[i]==hor||vec[i+1]==1||vec[i+1]==ver)){
        Error("Input not on the edge");
        //error
        valid=0;
    }else if(vec[i]<1||vec[i]>hor||vec[i+1]<1||vec[i+1]>ver){
        Error("Input out of range");
        //error
        valid=0;
    }
    }

    if(!in_range(vec_out[0],vec_out[1],hor,ver)){
       Error("Output out of range");
        valid=0;
    }
    if(!(vec_out[0]==1||vec_out[0]==hor||vec_out[1]==1||vec_out[1]==ver)){
        Error("Output not on the edge");
        //error
       valid=0;
    }

    if(valid){

            MainWindow *m = new MainWindow(hor,ver,vec,vec_out,wash);
            qDebug()<<5;
            this->hide();
    }

}
#include<QMessageBox>
    void InitWindow::Error(QString str){

        QMessageBox *msg = new QMessageBox(QMessageBox::NoIcon,"errorTest",str,QMessageBox::Ok,this);
        msg->show();

    }
