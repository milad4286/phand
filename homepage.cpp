#include "homepage.h"
#include <QFile>
#include<QString>
#include<QTextStream>
#include<QVBoxLayout>

homepage::homepage(QWidget *parent) : QWidget(parent) {

    this->setWindowTitle("Home");
    QVBoxLayout *layout = new QVBoxLayout(this);

    btngotologinpage = new QPushButton("ورود / ثبت‌نام");
    btngotologinpage->setMinimumSize(150, 50);
    layout->addWidget(btngotologinpage);

    btngototranslatepage = new QPushButton("صفحه ترجمه");
    btngototranslatepage->setMinimumSize(150, 50);
    layout->addWidget(btngototranslatepage);
    layout->addStretch();
    setLayout(layout);
    // connects
    connect(btngotologinpage , &QPushButton::clicked ,[=]() {
        emit gotologinpage();
    });
    connect(btngototranslatepage , &QPushButton::clicked ,[=](){
        emit gototrpage();
    });
}
