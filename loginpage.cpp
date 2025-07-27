#include "loginpage.h"

#include<QGraphicsDropShadowEffect>

loginpage::loginpage(QWidget *parent) : QWidget(parent) {



    QLabel *userLabel = new QLabel("نام کاربری");
    QLabel *passLabel = new QLabel("رمز عبور");

    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);

    // تعریف دکمه ها و استاتوس بار

    QPushButton *loginButton = new QPushButton("ورود");
    loginButton->setObjectName("loginbutton");
    QPushButton *cansell = new QPushButton(" کنسل ");
    statusLabel = new QLabel(this);


    QVBoxLayout *verloglayout = new QVBoxLayout();

    // لایه لاین ادیت ها
    loggride = new QGridLayout();
    loggride->addWidget(userLabel    , 0  , 0);
    loggride->addWidget(usernameEdit , 0  , 1);
    loggride->addWidget(passLabel    , 1  , 0);
    loggride->addWidget(passwordEdit , 1  , 1);

    // لایه دکمه ها
    QHBoxLayout *buttonlayout = new QHBoxLayout();
    buttonlayout ->addWidget(cansell);
    buttonlayout ->addWidget(loginButton);



    //  ترتیب لایه ها برای نمایش
    verloglayout->addStretch(); // فاصله از بالا
    verloglayout->addLayout(loggride);

    verloglayout->addWidget(statusLabel);

    verloglayout->addLayout(buttonlayout);
    verloglayout->addStretch(); //  فاصله از پایین




    frame = new QFrame;
    frame->setFrameShape(QFrame::Box);
    frame->setLineWidth(2);
    frame->setLayout(verloglayout);
    frame->setMinimumSize(600, 400); //  اندازه دلخواه وسط صفحه
    ///////////////   سایه دور فرم
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor(0, 0, 0, 150));

    frame->setGraphicsEffect(shadow);


    // اضافه کردن لایه اصلی
    QVBoxLayout * vcentrallayout = new QVBoxLayout(this);


    QHBoxLayout *hcentrallayout = new QHBoxLayout();
    hcentrallayout->addStretch();
    hcentrallayout->addWidget(frame);
    hcentrallayout->addStretch();
    vcentrallayout->addStretch();
    vcentrallayout->addLayout(hcentrallayout);
    vcentrallayout->addStretch();

    setLayout(vcentrallayout);


    // کانکت ها

    connect(loginButton, &QPushButton::clicked, this, &loginpage::tryLogin);
    connect(cansell, &QPushButton::clicked, this, &loginpage::Cansell);


}

void loginpage::tryLogin() {
    QString user = usernameEdit->text();
    QString pass = passwordEdit->text();

    if (user == "admin" && pass == "1234") {
        emit loginSuccessful();
    } else {
        statusLabel->setText("ورود نامعتبر است.");
    }
}

///////////////////////////////////////////////////
void loginpage::Cansell(){

}

