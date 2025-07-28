#include "mainwindow.h"
#include<QString>
#include<QPushButton>
#include<QVBoxLayout>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {


    auto *centralw = new QWidget(this);
    stack          = new QStackedWidget();
    login_page     = new loginpage();
    home_page      = new homepage();
    translate_page = new translate();
    signup_page    = new signup();

    stack->addWidget(home_page);  // index 0
    stack->addWidget(login_page);   // index 1
    stack->addWidget(translate_page) ; // index 2
    stack->addWidget(signup_page) ; // index 3


    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stack);


    connect(login_page, &loginpage::loginSuccessful, this,[=](){stack->setCurrentIndex(0);});
    connect(login_page, &loginpage::Cansellsuccessful , this ,[=](){stack->setCurrentIndex(0);}) ;

    connect(home_page ,&homepage::gotologinpage , this , [=](){stack->setCurrentIndex(1);});
    connect(home_page, &homepage::gototrpage , this ,[=](){stack->setCurrentIndex(2);}) ;

    connect(login_page, &loginpage::signsuccessful , this ,[=](){stack->setCurrentIndex(3);}) ;



    connect(signup_page, &signup::signenter , this ,[=](){stack->setCurrentIndex(1);}) ;
    connect(signup_page, &signup::signback , this ,[=](){stack->setCurrentIndex(0);}) ;


    stack->setCurrentIndex(0); // set mainpage first


    centralw->setLayout(mainLayout);
    setCentralWidget(centralw) ;
}

