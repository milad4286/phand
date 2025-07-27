#include "loginpage.h"

#include<QGraphicsDropShadowEffect>

loginpage::loginpage(QWidget *parent) : QWidget(parent) {


    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    QFont font;
    font.setPointSize(18);
    usernameEdit->setFont(font);
    passwordEdit->setFont(font);
    usernameEdit->setPlaceholderText("نام کاربری");
    passwordEdit->setPlaceholderText("رمز عبور");
    // usernameEdit->setAlignment(Qt::AlignRight);
    // passwordEdit->setAlignment(Qt::AlignRight);
    passwordEdit->setEchoMode(QLineEdit::Password);

    // تعریف دکمه ها و استاتوس بار

    loginButton = new QPushButton("ورود");
    loginButton->setObjectName("loginbutton");
    cansell = new QPushButton(" کنسل ");
    cansell->setObjectName("loginbutton");
    statusLabel = new QLabel(this);


    verloglayout = new QVBoxLayout();

    // لایه لاین ادیت ها
    loggride = new QGridLayout();
    loggride->addWidget(usernameEdit , 0  , 1);
    loggride->addWidget(passwordEdit , 1  , 1);

    // لایه دکمه ها
    buttonlayout = new QHBoxLayout();
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
    vcentrallayout = new QVBoxLayout(this);


    hcentrallayout = new QHBoxLayout();
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

