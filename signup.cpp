#include "signup.h"



signup::signup(QWidget *parent) : QWidget(parent){

    QLineEdit *sign_name = new QLineEdit;
    QLineEdit *sign_password = new QLineEdit;

    QPushButton *sign_enter = new QPushButton("ثبت نام");
    QPushButton *sign_back = new QPushButton("صفحه ورود");

    QFont font;
    font.setPointSize(18);
    sign_name->setFont(font);
    sign_password->setFont(font);
    sign_name->setPlaceholderText("نام کاربری");
    sign_password->setPlaceholderText("رمز عبور");

    sign_enter->setObjectName("loginbutton");
    sign_back->setObjectName("loginbutton");

    sign_password->setEchoMode(QLineEdit::Password);


    statusLabel = new QLabel(this);


    verloglayout = new QVBoxLayout();

    // لایه لاین ادیت ها
    loggride = new QGridLayout();
    loggride->addWidget(sign_name , 0  , 1);
    loggride->addWidget(sign_password , 1  , 1);

    // لایه دکمه ها
    buttonlayout = new QHBoxLayout();
    buttonlayout ->addWidget(sign_back);
    buttonlayout ->addWidget(sign_enter);

    verloglayout->addStretch(); // فاصله از بالا
    verloglayout->addLayout(loggride);

    signLayout = new QHBoxLayout();
    // signLayout->addWidget(sign);
    signLayout->addStretch();
    verloglayout->addLayout(signLayout);

    verloglayout->addWidget(statusLabel);

    verloglayout->addLayout(buttonlayout);
    verloglayout->addStretch(); //  فاصله از پایین

    frame = new QFrame;
    frame->setFrameShape(QFrame::Box);
    frame->setLineWidth(2);
    frame->setLayout(verloglayout);
    frame->setMinimumSize(600, 400); //  اندازه دلخواه وسط صفحه

    shadow = new QGraphicsDropShadowEffect(this);
    frame->setGraphicsEffect(shadow);

    vcentrallayout = new QVBoxLayout(this);


    hcentrallayout = new QHBoxLayout();
    hcentrallayout->addStretch();
    hcentrallayout->addWidget(frame);
    hcentrallayout->addStretch();
    vcentrallayout->addStretch();
    vcentrallayout->addLayout(hcentrallayout);
    vcentrallayout->addStretch();

    setLayout(vcentrallayout);

    connect(sign_enter, &QPushButton::clicked, this, &signup::enters);
    connect(sign_back, &QPushButton::clicked, this, &signup::backs);


}

//////////////////////////////////////////////////////
void signup::enters(){
    emit signenter();

}

//////////////////////////////////////////////////////
void signup:: backs(){
    emit signback();

}
