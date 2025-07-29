#include "loginpage.h"


loginpage::loginpage(QWidget *parent) : QWidget(parent) {


    this->setStyleSheet("QFrame#frameBox { background-color: #d0f0c0; }");


    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    usernameEdit->setObjectName("QLineEditt");
    passwordEdit->setObjectName("QLineEditt");
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
    sign = new QPushButton("ثبت نام کنید");
    sign->setObjectName("signbuttonn");


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

    signLayout = new QHBoxLayout();
    signLayout->addWidget(sign);
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
    ///////////////   سایه دور فرم
    shadow = new QGraphicsDropShadowEffect(this);
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
     //this->setStyleSheet("QWidget#loginpage { background-color: #d0f0c0; }");


    // کانکت ها

    connect(loginButton, &QPushButton::clicked, this, &loginpage::tryLogin);
    connect(cansell, &QPushButton::clicked, this, &loginpage::Cansell);
    connect(sign, &QPushButton::clicked, this, &loginpage::sign_up);


}

void loginpage::tryLogin() {
    QString user = usernameEdit->text();
    QString pass = passwordEdit->text();

    QFile file("userdata.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        statusLabel->setText("فایل اطلاعات پیدا نشد.");
        return;
    }

    QTextStream in(&file);
    bool found = false;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList part = line.split(',');
        if (part.size() == 2) {
            QString userr = part[0].trimmed();
            QString passs = part[1].trimmed();
            if (userr == user && passs == pass) {
                found = true;
                break;
            }
        }
    }
    file.close();

    if (found) {
        emit loginSuccessful(); // ورود موفق
    } else {
        statusLabel->setText("نام کاربری یا رمز عبور اشتباه است.");
    }
}


///////////////////////////////////////////////////
void loginpage::Cansell(){
    emit Cansellsuccessful();

}
//////////////////////////////////////////////////////
void loginpage::sign_up(){
    emit signsuccessful();

}


