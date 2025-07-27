#include "mainwindow.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //centralwidget   only in Qmainwindow

    auto *Centralwidget = new QWidget(this) ;
    Centralwidget->setObjectName("mainwidget");

    // layouts

    QVBoxLayout *vcentral = new QVBoxLayout(this);
    QHBoxLayout *hcentral = new QHBoxLayout(this);
    QGridLayout *gcentrl  = new QGridLayout(this);

    //buttons

    loginbtn = new QPushButton( "ثبت نام") ;
    loginbtn->setObjectName("loginbutton");












    gcentrl->addWidget(loginbtn,0,0);
    hcentral->addStretch();
    hcentral->addLayout(gcentrl);
    hcentral->addStretch();
    vcentral->addStretch();
    vcentral->addLayout(hcentral);
    vcentral->addStretch();

    Centralwidget->setLayout(vcentral);
    setCentralWidget(Centralwidget);

}

MainWindow::~MainWindow() {}
