#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <string>
#include <QSignalMapper>
#include "board.h"
#include <QIcon>
#include <typeinfo>
#include <iostream>
#include <QRadioButton>
static Board board;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    buttons(80),backGround(80),
    chessPic(20),issetboard(11),
    kingAppear(2,0),moved(true),
    moveable(":/new/picture/src/picture/moveable.png"),
    select(":/new/picture/src/picture/select.png"),
    danger(":/new/picture/src/picture/danger.png"),
    dark(":/new/picture/src/picture/dark.png"),
    white(":/new/picture/src/picture/white.png")
{
    ui->setupUi(this);
    /*for(int i = 0;i<9;++i){
        QPushButton *bar = new QPushButton(QString().sprintf("che%d",i));
        bar->setParent(ui->board);
        bar->setGeometry(450,50*i,50,50);
        connect(bar, &QPushButton::clicked, [=](){
            chess_pressed(110+i);
        });
    }*/

    checkConnect->setInterval(1000);
    checkConnect->start();
    tcpServer = new QTcpServer;
    tcpSocket = NULL;
    tcpServer->listen();
    QList<QHostAddress> ipList = QNetworkInterface::allAddresses();
    qDebug()<<"ip:";
    for(int i = 0; i<ipList.count(); ++i){
        if(ipList.at(i).toIPv4Address()){
            qDebug()<<ipList.at(i).toString()<<"\n";
        }else{}
    }

    QSignalMapper* signalMapper = new QSignalMapper(this);
    connect(ui->chess00, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess01, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess02, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess03, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess04, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess05, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess06, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess07, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess10, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess11, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess12, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess13, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess14, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess15, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess16, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess17, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess20, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess21, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess22, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess23, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess24, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess25, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess26, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess27, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess30, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess31, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess32, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess33, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess34, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess35, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess36, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess37, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess40, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess41, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess42, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess43, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess44, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess45, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess46, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess47, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess50, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess51, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess52, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess53, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess54, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess55, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess56, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess57, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess60, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess61, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess62, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess63, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess64, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess65, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess66, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess67, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess70, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess71, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess72, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess73, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess74, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess75, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess76, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->chess77, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch00, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch01, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch02, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch03, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch04, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch05, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch06, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch07, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch10, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch11, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch12, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch13, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch14, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch15, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch16, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch17, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch20, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch21, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch22, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch23, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch24, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch25, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch26, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch27, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch30, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch31, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch32, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch33, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch34, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch35, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch36, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch37, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch40, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch41, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch42, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch43, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch44, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch45, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch46, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch47, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch50, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch51, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch52, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch53, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch54, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch55, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch56, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch57, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch60, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch61, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch62, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch63, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch64, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch65, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch66, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch67, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch70, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch71, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch72, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch73, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch74, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch75, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch76, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->ch77, SIGNAL(clicked()), signalMapper, SLOT(map()));

    signalMapper->setMapping(ui->chess00, 0);
    signalMapper->setMapping(ui->chess01, 1);
    signalMapper->setMapping(ui->chess02, 2);
    signalMapper->setMapping(ui->chess03, 3);
    signalMapper->setMapping(ui->chess04, 4);
    signalMapper->setMapping(ui->chess05, 5);
    signalMapper->setMapping(ui->chess06, 6);
    signalMapper->setMapping(ui->chess07, 7);
    signalMapper->setMapping(ui->chess10, 10);
    signalMapper->setMapping(ui->chess11, 11);
    signalMapper->setMapping(ui->chess12, 12);
    signalMapper->setMapping(ui->chess13, 13);
    signalMapper->setMapping(ui->chess14, 14);
    signalMapper->setMapping(ui->chess15, 15);
    signalMapper->setMapping(ui->chess16, 16);
    signalMapper->setMapping(ui->chess17, 17);
    signalMapper->setMapping(ui->chess20, 20);
    signalMapper->setMapping(ui->chess21, 21);
    signalMapper->setMapping(ui->chess22, 22);
    signalMapper->setMapping(ui->chess23, 23);
    signalMapper->setMapping(ui->chess24, 24);
    signalMapper->setMapping(ui->chess25, 25);
    signalMapper->setMapping(ui->chess26, 26);
    signalMapper->setMapping(ui->chess27, 27);
    signalMapper->setMapping(ui->chess30, 30);
    signalMapper->setMapping(ui->chess31, 31);
    signalMapper->setMapping(ui->chess32, 32);
    signalMapper->setMapping(ui->chess33, 33);
    signalMapper->setMapping(ui->chess34, 34);
    signalMapper->setMapping(ui->chess35, 35);
    signalMapper->setMapping(ui->chess36, 36);
    signalMapper->setMapping(ui->chess37, 37);
    signalMapper->setMapping(ui->chess40, 40);
    signalMapper->setMapping(ui->chess41, 41);
    signalMapper->setMapping(ui->chess42, 42);
    signalMapper->setMapping(ui->chess43, 43);
    signalMapper->setMapping(ui->chess44, 44);
    signalMapper->setMapping(ui->chess45, 45);
    signalMapper->setMapping(ui->chess46, 46);
    signalMapper->setMapping(ui->chess47, 47);
    signalMapper->setMapping(ui->chess50, 50);
    signalMapper->setMapping(ui->chess51, 51);
    signalMapper->setMapping(ui->chess52, 52);
    signalMapper->setMapping(ui->chess53, 53);
    signalMapper->setMapping(ui->chess54, 54);
    signalMapper->setMapping(ui->chess55, 55);
    signalMapper->setMapping(ui->chess56, 56);
    signalMapper->setMapping(ui->chess57, 57);
    signalMapper->setMapping(ui->chess60, 60);
    signalMapper->setMapping(ui->chess61, 61);
    signalMapper->setMapping(ui->chess62, 62);
    signalMapper->setMapping(ui->chess63, 63);
    signalMapper->setMapping(ui->chess64, 64);
    signalMapper->setMapping(ui->chess65, 65);
    signalMapper->setMapping(ui->chess66, 66);
    signalMapper->setMapping(ui->chess67, 67);
    signalMapper->setMapping(ui->chess70, 70);
    signalMapper->setMapping(ui->chess71, 71);
    signalMapper->setMapping(ui->chess72, 72);
    signalMapper->setMapping(ui->chess73, 73);
    signalMapper->setMapping(ui->chess74, 74);
    signalMapper->setMapping(ui->chess75, 75);
    signalMapper->setMapping(ui->chess76, 76);
    signalMapper->setMapping(ui->chess77, 77);
    signalMapper->setMapping(ui->ch00, 0);
    signalMapper->setMapping(ui->ch01, 1);
    signalMapper->setMapping(ui->ch02, 2);
    signalMapper->setMapping(ui->ch03, 3);
    signalMapper->setMapping(ui->ch04, 4);
    signalMapper->setMapping(ui->ch05, 5);
    signalMapper->setMapping(ui->ch06, 6);
    signalMapper->setMapping(ui->ch07, 7);
    signalMapper->setMapping(ui->ch10, 10);
    signalMapper->setMapping(ui->ch11, 11);
    signalMapper->setMapping(ui->ch12, 12);
    signalMapper->setMapping(ui->ch13, 13);
    signalMapper->setMapping(ui->ch14, 14);
    signalMapper->setMapping(ui->ch15, 15);
    signalMapper->setMapping(ui->ch16, 16);
    signalMapper->setMapping(ui->ch17, 17);
    signalMapper->setMapping(ui->ch20, 20);
    signalMapper->setMapping(ui->ch21, 21);
    signalMapper->setMapping(ui->ch22, 22);
    signalMapper->setMapping(ui->ch23, 23);
    signalMapper->setMapping(ui->ch24, 24);
    signalMapper->setMapping(ui->ch25, 25);
    signalMapper->setMapping(ui->ch26, 26);
    signalMapper->setMapping(ui->ch27, 27);
    signalMapper->setMapping(ui->ch30, 30);
    signalMapper->setMapping(ui->ch31, 31);
    signalMapper->setMapping(ui->ch32, 32);
    signalMapper->setMapping(ui->ch33, 33);
    signalMapper->setMapping(ui->ch34, 34);
    signalMapper->setMapping(ui->ch35, 35);
    signalMapper->setMapping(ui->ch36, 36);
    signalMapper->setMapping(ui->ch37, 37);
    signalMapper->setMapping(ui->ch40, 40);
    signalMapper->setMapping(ui->ch41, 41);
    signalMapper->setMapping(ui->ch42, 42);
    signalMapper->setMapping(ui->ch43, 43);
    signalMapper->setMapping(ui->ch44, 44);
    signalMapper->setMapping(ui->ch45, 45);
    signalMapper->setMapping(ui->ch46, 46);
    signalMapper->setMapping(ui->ch47, 47);
    signalMapper->setMapping(ui->ch50, 50);
    signalMapper->setMapping(ui->ch51, 51);
    signalMapper->setMapping(ui->ch52, 52);
    signalMapper->setMapping(ui->ch53, 53);
    signalMapper->setMapping(ui->ch54, 54);
    signalMapper->setMapping(ui->ch55, 55);
    signalMapper->setMapping(ui->ch56, 56);
    signalMapper->setMapping(ui->ch57, 57);
    signalMapper->setMapping(ui->ch60, 60);
    signalMapper->setMapping(ui->ch61, 61);
    signalMapper->setMapping(ui->ch62, 62);
    signalMapper->setMapping(ui->ch63, 63);
    signalMapper->setMapping(ui->ch64, 64);
    signalMapper->setMapping(ui->ch65, 65);
    signalMapper->setMapping(ui->ch66, 66);
    signalMapper->setMapping(ui->ch67, 67);
    signalMapper->setMapping(ui->ch70, 70);
    signalMapper->setMapping(ui->ch71, 71);
    signalMapper->setMapping(ui->ch72, 72);
    signalMapper->setMapping(ui->ch73, 73);
    signalMapper->setMapping(ui->ch74, 74);
    signalMapper->setMapping(ui->ch75, 75);
    signalMapper->setMapping(ui->ch76, 76);
    signalMapper->setMapping(ui->ch77, 77);

    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(chess_pressed(int)));

    buttons[0] = ui->ch00;	backGround[0] = ui->chess00;
    buttons[1] = ui->ch01;	backGround[1] = ui->chess01;
    buttons[2] = ui->ch02;	backGround[2] = ui->chess02;
    buttons[3] = ui->ch03;	backGround[3] = ui->chess03;
    buttons[4] = ui->ch04;	backGround[4] = ui->chess04;
    buttons[5] = ui->ch05;	backGround[5] = ui->chess05;
    buttons[6] = ui->ch06;	backGround[6] = ui->chess06;
    buttons[7] = ui->ch07;	backGround[7] = ui->chess07;
    buttons[10] = ui->ch10;	backGround[10] = ui->chess10;
    buttons[11] = ui->ch11;	backGround[11] = ui->chess11;
    buttons[12] = ui->ch12;	backGround[12] = ui->chess12;
    buttons[13] = ui->ch13;	backGround[13] = ui->chess13;
    buttons[14] = ui->ch14;	backGround[14] = ui->chess14;
    buttons[15] = ui->ch15;	backGround[15] = ui->chess15;
    buttons[16] = ui->ch16;	backGround[16] = ui->chess16;
    buttons[17] = ui->ch17;	backGround[17] = ui->chess17;
    buttons[20] = ui->ch20;	backGround[20] = ui->chess20;
    buttons[21] = ui->ch21;	backGround[21] = ui->chess21;
    buttons[22] = ui->ch22;	backGround[22] = ui->chess22;
    buttons[23] = ui->ch23;	backGround[23] = ui->chess23;
    buttons[24] = ui->ch24;	backGround[24] = ui->chess24;
    buttons[25] = ui->ch25;	backGround[25] = ui->chess25;
    buttons[26] = ui->ch26;	backGround[26] = ui->chess26;
    buttons[27] = ui->ch27;	backGround[27] = ui->chess27;
    buttons[30] = ui->ch30;	backGround[30] = ui->chess30;
    buttons[31] = ui->ch31;	backGround[31] = ui->chess31;
    buttons[32] = ui->ch32;	backGround[32] = ui->chess32;
    buttons[33] = ui->ch33;	backGround[33] = ui->chess33;
    buttons[34] = ui->ch34;	backGround[34] = ui->chess34;
    buttons[35] = ui->ch35;	backGround[35] = ui->chess35;
    buttons[36] = ui->ch36;	backGround[36] = ui->chess36;
    buttons[37] = ui->ch37;	backGround[37] = ui->chess37;
    buttons[40] = ui->ch40;	backGround[40] = ui->chess40;
    buttons[41] = ui->ch41;	backGround[41] = ui->chess41;
    buttons[42] = ui->ch42;	backGround[42] = ui->chess42;
    buttons[43] = ui->ch43;	backGround[43] = ui->chess43;
    buttons[44] = ui->ch44;	backGround[44] = ui->chess44;
    buttons[45] = ui->ch45;	backGround[45] = ui->chess45;
    buttons[46] = ui->ch46;	backGround[46] = ui->chess46;
    buttons[47] = ui->ch47;	backGround[47] = ui->chess47;
    buttons[50] = ui->ch50;	backGround[50] = ui->chess50;
    buttons[51] = ui->ch51;	backGround[51] = ui->chess51;
    buttons[52] = ui->ch52;	backGround[52] = ui->chess52;
    buttons[53] = ui->ch53;	backGround[53] = ui->chess53;
    buttons[54] = ui->ch54;	backGround[54] = ui->chess54;
    buttons[55] = ui->ch55;	backGround[55] = ui->chess55;
    buttons[56] = ui->ch56;	backGround[56] = ui->chess56;
    buttons[57] = ui->ch57;	backGround[57] = ui->chess57;
    buttons[60] = ui->ch60;	backGround[60] = ui->chess60;
    buttons[61] = ui->ch61;	backGround[61] = ui->chess61;
    buttons[62] = ui->ch62;	backGround[62] = ui->chess62;
    buttons[63] = ui->ch63;	backGround[63] = ui->chess63;
    buttons[64] = ui->ch64;	backGround[64] = ui->chess64;
    buttons[65] = ui->ch65;	backGround[65] = ui->chess65;
    buttons[66] = ui->ch66;	backGround[66] = ui->chess66;
    buttons[67] = ui->ch67;	backGround[67] = ui->chess67;
    buttons[70] = ui->ch70;	backGround[70] = ui->chess70;
    buttons[71] = ui->ch71;	backGround[71] = ui->chess71;
    buttons[72] = ui->ch72;	backGround[72] = ui->chess72;
    buttons[73] = ui->ch73;	backGround[73] = ui->chess73;
    buttons[74] = ui->ch74;	backGround[74] = ui->chess74;
    buttons[75] = ui->ch75;	backGround[75] = ui->chess75;
    buttons[76] = ui->ch76;	backGround[76] = ui->chess76;
    buttons[77] = ui->ch77;	backGround[77] = ui->chess77;
    QPixmap pixmap110(":/new/picture/src/picture/110.png");
    chessPic[0] = pixmap110;
    QPixmap pixmap111(":/new/picture/src/picture/111.png");
    chessPic[1] = pixmap111;
    chessPic[8] = pixmap111;
    QPixmap pixmap112(":/new/picture/src/picture/112.png");
    chessPic[2] = pixmap112;
    QPixmap pixmap113(":/new/picture/src/picture/113.png");
    chessPic[3] = pixmap113;
    QPixmap pixmap114(":/new/picture/src/picture/114.png");
    chessPic[4] = pixmap114;
    QPixmap pixmap115(":/new/picture/src/picture/115.png");
    chessPic[5] = pixmap115;
    chessPic[7] = pixmap115;
    QPixmap pixmap116(":/new/picture/src/picture/116.png");
    chessPic[6] = pixmap116;
    chessPic[9] = pixmap116;
    QPixmap pixmap121(":/new/picture/src/picture/121.png");
    chessPic[11] = pixmap121;
    chessPic[18] = pixmap121;
    QPixmap pixmap122(":/new/picture/src/picture/122.png");
    chessPic[12] = pixmap122;
    QPixmap pixmap123(":/new/picture/src/picture/123.png");
    chessPic[13] = pixmap123;
    QPixmap pixmap124(":/new/picture/src/picture/124.png");
    chessPic[14] = pixmap124;
    QPixmap pixmap125(":/new/picture/src/picture/125.png");
    chessPic[15] = pixmap125;
    chessPic[17] = pixmap125;
    QPixmap pixmap126(":/new/picture/src/picture/126.png");
    chessPic[16] = pixmap126;
    chessPic[19] = pixmap126;

    for(int i = 2;i<6;++i){     // buttons for level up.
        QLabel *lab = new QLabel(QString().sprintf("levelB1%d",i));
        QLabel *lab2 = new QLabel(QString().sprintf("levelB2%d",i));
        QPushButton *bar = new QPushButton(QString().sprintf("level1%d",i));
        QPushButton *bar2 = new QPushButton(QString().sprintf("level2%d",i));
        level.push_back(bar);   levelBackground.push_back(lab);
        level.push_back(bar2);  levelBackground.push_back(lab2);
        lab->setParent(ui->board);  bar->setParent(ui->board);
        lab2->setParent(ui->board); bar2->setParent(ui->board);
        bar->setFlat(true); bar2->setFlat(true);
        bar->setGeometry(300+50*i,0,50,50);   lab->setGeometry(300+50*i,0,50,50);
        bar2->setGeometry(300+50*i,350,50,50);    lab2->setGeometry(300+50*i,350,50,50);
        bar->setText("");   bar2->setText("");
        bar->setIcon(chessPic[i]);      lab->setPixmap(moveable);
        bar2->setIcon(chessPic[10+i]);  lab2->setPixmap(moveable);
        bar->setIconSize(QSize(35,35)); bar2->setIconSize(QSize(35,35));
        connect(bar, &QPushButton::clicked, [=](){
            chess_pressed(110+i);
        });
        connect(bar2, &QPushButton::clicked, [=](){
            chess_pressed(120+i);
        });

    }
    for(int i = 0; i<8; ++i){
        level[i]->setVisible(false);
        levelBackground[i]->setVisible(false);
    }
    shoow(900);
    possiblePressed = false;

    // ui part
    ui->start->setGeometry(30,30,ui->start->width(),ui->start->height());
    ui->setMap->setGeometry(430,30,ui->setMap->width(),ui->setMap->height());
    ui->setMapButton->setVisible(false);
    ui->exitSetting->setVisible(true);  // exit button on board. ignore this variable name.
    ui->setMap->setVisible(false);
    ui->board->setVisible(false);
    ui->netWidget->setVisible(false);

        // net widget
    {QLabel* titleText = new QLabel("title",ui->netWidget);
    titleText->setGeometry(300,0,100,50);
    QPushButton *hostBut = new QPushButton("host",ui->start);
    hostBut->setGeometry(400,100,50,50);
    QPushButton *clientBut = new QPushButton("client",ui->start);
    clientBut->setGeometry(400,150,50,50);
    QTextEdit* ipEdit = new QTextEdit("127.0.0.1",ui->netWidget);
    ipEdit->setGeometry(300,200,200,50);
    QTextEdit* portEdit = new QTextEdit("enter port here",ui->netWidget);
    portEdit->setGeometry(300,250,200,50);
    QPushButton* okBut = new QPushButton("ok",ui->netWidget); // for connection
    okBut->setGeometry(500,200,100,100);
    QPushButton* cancelBut = new QPushButton("cancel",ui->netWidget);
    cancelBut->setGeometry(50,300,100,50);
    int counter = 0;
    for (int i = 0; i<ipList.count(); ++i){
        if (ipList.at(i).toIPv4Address()){
            ++counter;
            QLabel* tmpText = new QLabel("ip",ui->netWidget);
            tmpText->setGeometry(300,50*counter,100,50);
            tmpText->setText(ipList.at(i).toString());
        }
    }
    ++counter;
    QLabel* portText = new QLabel("port",ui->netWidget);
    portText->setGeometry(300,50*counter,100,50);
    portText->setText(QString::number(tcpServer->serverPort()));
    connect(hostBut, &QPushButton::clicked,[=](){
        uiManage(5);
        titleText->setText("host");
        ipEdit->setVisible(false);
        portEdit->setVisible(false);
        okBut->setVisible(false);
        id = 1;
    });
    connect(clientBut,&QPushButton::clicked,[=](){
        uiManage(5);
        titleText->setText("client");
        ipEdit->setVisible(true);
        portEdit->setVisible(true);
        okBut->setVisible(true);
    });
    connect(okBut,&QPushButton::clicked,[=](){
        tcpSocket = new QTcpSocket;
        if(ipEdit->toPlainText().isEmpty()||portEdit->toPlainText().isEmpty()){
            return;
        }
        qDebug()<<"ipEdit: "<<ipEdit->toPlainText();
        qDebug()<<"portEdit: "<<portEdit->toPlainText();
        tcpSocket->connectToHost(QHostAddress(ipEdit->toPlainText()),
                                              quint16(portEdit->toPlainText().toUInt()));
        if(tcpSocket->state()==QAbstractSocket::UnconnectedState){
            qDebug()<<"connection failed";
            delete tcpSocket;
            tcpSocket = NULL;
            return;     // connect fail
        }
        uiManage(1);
        issetboard = -1;
        connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(printOut()));
    });
    connect(cancelBut,&QPushButton::clicked,[=](){
        uiManage(4);
    });
    }
        // ^^ net widget
    {QPushButton *startBut = new QPushButton("Start", ui->start);
    startBut->setGeometry(200,100,200,50);
    startBut->setFont(QFont("Ubuntu",35));
    connect(startBut, &QPushButton::clicked,[=](){
        uiManage(1);
        issetboard = -1;
        board.setBoard();
        shoow();
    });}
    {QPushButton *setBut = new QPushButton("Set Map", ui->start);
    setBut->setGeometry(200,175,200,50);
    setBut->setFont(QFont("Ubuntu",35));
    connect(setBut, &QPushButton::clicked,[=](){
        uiManage(2);
        issetboard = 11;
    });}
    {QPushButton *quitBut = new QPushButton("Quit", ui->start);
    quitBut->setGeometry(200,250,200,50);
    quitBut->setFont(QFont("Ubuntu",35));
    connect(quitBut, &QPushButton::clicked,[=](){
        uiManage(0);
    });}
        // set map
    {QPushButton *okBut = new QPushButton("ok", ui->setMap);
    okBut->setGeometry(20,320,70,30);
    okBut->setFont(QFont("Ubuntu",15));
    connect(okBut, &QPushButton::clicked,[=](){
        issetboard = -1;
        uiManage(3);
    });
    QCheckBox *checkbox = new QCheckBox("has moved",ui->setMap);
    checkbox->setGeometry(30,250,200,30);
    checkbox->setFont(QFont("Ubuntu",15));
    checkbox->setChecked(true);
    connect(checkbox, &QCheckBox::clicked,[=](){
        moved = checkbox->isChecked();
    });
    QRadioButton *whiterad = new QRadioButton("white turns",ui->setMap);
    whiterad->setGeometry(30,270,200,30);
    whiterad->setFont(QFont("Ubuntu",15));
    whiterad->setChecked(true);
    connect(whiterad, &QRadioButton::clicked, [=](){
        board.setBoard(100,1);
    });
    QRadioButton *blackrad = new QRadioButton("black turns",ui->setMap);
    blackrad->setGeometry(30,290,200,30);
    blackrad->setFont(QFont("Ubuntu",15));
    blackrad->setChecked(false);
    connect(blackrad, &QRadioButton::clicked, [=](){
        board.setBoard(100,2);
    });
    QLabel *lab = new QLabel("",ui->setMap);
    lab->setGeometry(30,0,150,200);
    lab->setPixmap(QPixmap(":/new/picture/src/picture/back.png"));
    for(int i = 0; i<2; ++i){       // buttons for chess choosing.
        for(int j = 1; j<7; ++j){
            QPushButton *bar = new QPushButton("", ui->setMap);
            if (j<4){
                bar->setGeometry(50*j-20,100*i,50,50);
            }else{
                bar->setGeometry(50*j-170,100*i+50,50,50);
            }
            bar->setIcon(chessPic[i*10+j]);
            bar->setIconSize(QSize(35,35));
            connect(bar, &QPushButton::clicked,[=](){
                issetboard = i*10+j+10;
            });
        }
    }
    QPushButton *cancel = new QPushButton("",ui->setMap);
    cancel->setGeometry(30,200,50,50);
    cancel->setIcon(QPixmap(":/new/picture/src/picture/cancel.png"));
    cancel->setIconSize(QSize(49,49));
    connect(cancel, &QPushButton::clicked,[=](){
        issetboard = 0;
    });
    QPushButton *resetBut = new QPushButton("",ui->setMap);
    resetBut->setGeometry(80,200,50,50);
    resetBut->setIcon(QPixmap(":/new/picture/src/picture/reset.png"));
    resetBut->setIconSize(QSize(49,49));
    connect(resetBut, &QPushButton::clicked,[=](){
        board.setBoard();
        shoow();
    });
    QPushButton *blank = new QPushButton("",ui->setMap);
    blank->setGeometry(130,200,50,50);
    blank->setIcon(chessPic[0]);
    connect(blank, &QPushButton::clicked,[=](){
        board.setBoard(200,0);
        shoow();
    });
    QPushButton *bar = new QPushButton("exit",ui->setMap);
    bar->setGeometry(100,320,70,30);
    bar->setFont(QFont("Ubuntu",15));
    connect(bar, &QPushButton::clicked, [=](){
        uiManage(4);
    });
    connect(ui->setMapButton, &QPushButton::clicked,[=](){
        uiManage(2);
        issetboard = 11;
        ui->setMapButton->setVisible(false);
    });
    connect(ui->exitSetting, &QPushButton::clicked,[=](){
        uiManage(4);
        ui->setMapButton->setVisible(false);
        if (id > 0){
            id = 0;
            board.setBoard();
            tcpSocket->disconnectFromHost();
            delete tcpSocket;
            clientId.clear();
        }
        issetboard = -1;
    });
    }
    // victory
    {QLabel *whiteVic = new QLabel("white win",ui->board);
    victoryLabel.push_back(whiteVic);
    whiteVic->setGeometry(420,200,200,100);
    whiteVic->setFont(QFont("Ubuntu",30));
    whiteVic->setVisible(false);
    QLabel *blackVic = new QLabel("black win", ui->board);
    victoryLabel.push_back(blackVic);
    blackVic->setGeometry(420,200,200,100);
    blackVic->setFont(QFont("Ubuntu",30));
    blackVic->setVisible(false);
    }

    connect(checkConnect,SIGNAL(timeout()),this,SLOT(connectSuccess()));
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(prepareStart()));

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::chess_pressed(int in){
    if (id==board.getTurns()){      // you want to move
        QByteArray byte;
        QDataStream stream(&byte,QIODevice::WriteOnly);
        stream<<"2";
        if (id == 1){stream<<"1";}
        else if (id == 2){stream<<"2";}
        else{}
        dataStreamInt(stream,byte,in);
        tcpSocket->write(byte);
    }else if (who){who = false;}        // oponent want to move
    else if(id){return;}    // you are playing online and you can't move
    if (issetboard+1){
        if (moved){}        // get from check box
        else if (issetboard%10 == 1){       // not moved
            issetboard = issetboard+7;
        }else if (issetboard%10 == 5){
            issetboard = issetboard+2;
        }else if (issetboard%10 == 6){
            issetboard = issetboard+3;
        }else{}
        board.setBoard(in,issetboard);
        if (issetboard%10 == 1 || issetboard%10 == 8){
            board.setBoard(board.getLocate()[7+issetboard/10],0);
            board.setBoard(7+issetboard/10,in);
        }else{}
        shoow();
        return;
    }
    /*if (possiblePressed){
        qDebug()<<board.getLocate()[in];
        qDebug()<<board.getPossible()[in];
        return;
    }else{}
    qDebug() <<"input is"<<in;
    debugg.push_back(in);
    qDebug()<<debugg;*/
    shoow(board.manage(in));

}
void MainWindow::shoow(int in){
    //qDebug()<<"shoow("<<in<<")";
    switch (in/100){
    case 0:         // show chess
        for(int i = 0; i<8; ++i){
            for(int j = 0; j<8; ++j){
                if (!board.getLocate()[i*10+j]){
                    buttons[i*10+j]->setIcon(chessPic[0]);
                }else{
                    buttons[i*10+j]->setIcon(chessPic[board.getLocate()[i*10+j]-10]);
                }
            }
        }
        for(int i = 0; i<8; ++i){
            for(int j = 0; j<8; ++j){
                if ((i+j)%2 == 1){
                    backGround[i*10+j]->setIcon(dark);
                }else{
                    backGround[i*10+j]->setIcon(white);
                }
            }
        }
        backGround[in]->setIcon(select);
        break;
    case 1:
        for(int i = 0; i<8; ++i){
            level[i]->setVisible(false);
            levelBackground[i]->setVisible(false);
        }
        shoow(0);
        break;
    case 2:         // show background but no possible
        for(int i = 0; i<8; ++i){
            for(int j = 0; j<8; ++j){
                if ((i+j)%2 == 1){
                    backGround[i*10+j]->setIcon(dark);
                }else{
                    backGround[i*10+j]->setIcon(white);
                }
            }
        }
        backGround[in-200]->setIcon(select);
        break;
    case 3:         // show background and possible
        for(int i = 0; i<8; ++i){
            for(int j = 0; j<8; ++j){
                if ((i+j)%2 == 1){
                    backGround[i*10+j]->setIcon(dark);
                }else{
                    backGround[i*10+j]->setIcon(white);
                }
            }
        }
        backGround[in-300]->setIcon(select);
        for(int i = 0; i<21; ++i){      // show possible
            if (board.getPossible()[in-300][i] == -1){}
            else {
                backGround[board.getPossible()[in-300][i]]->setIcon(moveable);
            }
        }
        break;
    case 4:     // white level up
        for(int i = 0; i<8; i = i+2){
            level[i]->setVisible(true);
            levelBackground[i]->setVisible(true);
        }
        break;
    case 5:     // black level up
        for(int i = 1; i<8; i = i+2){
            level[i]->setVisible(true);
            levelBackground[i]->setVisible(true);
        }
        break;
    case 6:
        //qDebug()<<"white win";
        victoryLabel[0]->setVisible(true);
        shoow(in%100);
        break;
    case 7:
        victoryLabel[1]->setVisible(true);
        //qDebug()<<"black win";
        shoow(in%100);
        break;
    case 9:
        for(int i = 0; i<8; ++i){       // chess
            for(int j = 0; j<8; ++j){
                if (!board.getLocate()[i*10+j]){
                    buttons[i*10+j]->setIcon(chessPic[0]);
                }else{
                    buttons[i*10+j]->setIcon(chessPic[board.getLocate()[i*10+j]-10]);
                }
            }
        }
        for(int i = 0; i<8; ++i){       // background
            for(int j = 0; j<8; ++j){
                if ((i+j)%2 == 1){
                    backGround[i*10+j]->setIcon(dark);
                }else{
                    backGround[i*10+j]->setIcon(white);
                }
            }
        }
        break;
    }
}

void MainWindow::on_showPossible_clicked()
{
    possiblePressed = !possiblePressed;
}

void MainWindow::uiManage(int in){
    switch (in){
    case 0:     // quit button
        //MainWindow::~MainWindow();
        exit(0);
    case 1:     // start button
        ui->start->setVisible(false);
        ui->board->setVisible(true);
        ui->netWidget->setVisible(false);
        victoryLabel[0]->setVisible(false);
        victoryLabel[1]->setVisible(false);
        break;
    case 2:     // set map button
        ui->start->setVisible(false);
        ui->board->setVisible(true);
        ui->setMap->setVisible(true);
        ui->netWidget->setVisible(false);
        victoryLabel[0]->setVisible(false);
        victoryLabel[1]->setVisible(false);
        break;
    case 3:     // ok button in set map
        ui->setMap->setVisible(false);
        ui->setMapButton->setVisible(true);
        ui->exitSetting->setVisible(true);
        break;
    case 4:     // exit
        ui->start->setVisible(true);
        ui->board->setVisible(false);
        ui->setMap->setVisible(false);
        ui->netWidget->setVisible(false);
        break;
    case 5:     // host, client button in start
        ui->start->setVisible(false);
        ui->netWidget->setVisible(true);
        break;
    }
}

void MainWindow::printOut(){
    QDataStream in(tcpSocket);
    in.startTransaction();
    if(!in.commitTransaction())return;
    QByteArray data;
    in>>data;       ////////// first data in //////////
    qDebug()<<"first data:"<<data;
    if(!data.isEmpty())
        data = data.left(data.size()-1);
    switch(data.toInt()){       // first argument recieve
    case 1:     // send id to client (only client can get it)
        if (id == 1) break;     // it means you are a host!!
        in>>data;   // second data in //
        if(!data.isEmpty())
            data = data.left(data.size()-1);
        id = data.toInt();
        break;
    case 2:     // send the chess movement
        in>>data;   // second data in (send turns) //
        if (!data.isEmpty())
            data = data.left(data.size()-1);
        else break;
        qDebug()<<"second data:"<<data.toInt();
        if(data.toInt() == board.getTurns()){     // host turns (white turns)
            in>>data;   // third data in (button locate)
            if (!data.isEmpty())
                data = data.left(data.size()-1);
            qDebug()<<"third data:"<<data.toInt();
            who = true;
            chess_pressed(data.toInt());
        }else if (board.getTurns()==2 && data.toInt()==clientId[0]){
            in>>data;   // third data in (button locate)
            if (!data.isEmpty())
                data = data.left(data.size()-1);
            qDebug()<<"third data:"<<data.toInt();
            who = true;
            chess_pressed(data.toInt());
        }
        break;
    case 3:     // send the whole chess
        break;
    }
}

QDataStream &MainWindow::dataStreamInt(QDataStream& stream,QByteArray& arr,int in){
    // stream and arr must be a pair
    // -99 <= in <=999
    // input integer can be only three byte here
    // three bytes are enough for me here
    int abs;
    if (in>=0){abs = in;}
    else{
        abs = -in;
    }
    if (abs>=100 || (abs>=10 && in<0)){     // three byte
        stream<<"\x05\x05\x05";
        char tmp;
        if (abs>=100){
            tmp = abs/100 + '0';
            arr.replace(arr.indexOf("\x05"),1,"\x06");
            arr.replace('\x06',tmp);
        }else{
            arr.replace(arr.indexOf("\x05"),1,"-");
        }
        tmp = (abs/10)%10 + '0';
        arr.replace(arr.indexOf("\x05"),1,"\x06");
        arr.replace('\x06',tmp);
    }else if (abs-10>=0 || in<0){                // two byte
        stream<<"\x05\x05";
        char tmp;
        if (in>0){
            tmp = abs/10 + '0';
            arr.replace(arr.indexOf("\x05"),1,"\x06");
            arr.replace('\x06',tmp);
        }else{
            arr.replace(arr.indexOf("\x05"),1,"-");
        }
    }else{
        stream<<"\x05";
    }
    char tmp;
    tmp = abs%10 + '0';
    arr.replace(arr.indexOf("\x05"),1,"\x06");
    arr.replace('\x06',tmp);
    return stream;
}
void MainWindow::prepareStart(){
    qDebug()<<"catch";
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(printOut()));
    QByteArray byte;
    QDataStream stream(&byte,QIODevice::WriteOnly);
    stream<<"1";
    if (clientId.isEmpty()){
        clientId.append(2);
        stream<<"2";
    }else {
        stream<<"3";
    }
    tcpSocket->write(byte);
    uiManage(1);
    issetboard = -1;
}
void MainWindow::connectSuccess(){
    if (id == 2){
        qDebug()<<tcpSocket->state();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    bool ok;
    if (event->key() == Qt::Key_S){
        QString inText = QInputDialog::getText(this,tr("Save"),tr("File name to save:"),QLineEdit::Normal,tr(""),&ok);
        if (ok && !inText.isEmpty()){
            QFile file(inText+".txt");      // file name.
            if (file.exists()){
                qDebug()<<"file overwrite!";
            }
            if (!file.open(QIODevice::WriteOnly|QIODevice::Text)){return;}
            QTextStream out(&file);
            out<<board.getTurns()<<"\n";
            for(int i = 0; i<80; ++i){
                out<<board.getLocate()[i]<<"\n";
            }
        }
    }else if(event->key() == Qt::Key_L){
        QString inText = QInputDialog::getText(this,tr("Load"),tr("File name to load:"),QLineEdit::Normal,tr(""),&ok);
        if (ok && !inText.isEmpty()){
            QFile file(inText+".txt");      // file name.
            if (!file.exists()){
                qDebug()<<"file not exist!";
            }
            if (!file.open(QIODevice::ReadOnly|QIODevice::Text)){return;}
            QTextStream in(&file);
            //int counter = 0;
            QVector<int> v(81);
            int counter = 1;
            v[0] = in.readLine().toInt();
            while(!in.atEnd()){
                if (counter>80){
                    qDebug()<<"file not match!";
                    return;
                }
                v[counter] = in.readLine().toInt();
                //qDebug()<<v[counter];
                ++counter;
            }
            board.setBoard(v.mid(1));
            board.setBoard(100,v[0]);
            shoow();
        }
    }
}
