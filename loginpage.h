#ifndef LOGINPAGE_H
#define LOGINPAGE_H
#include<QGraphicsDropShadowEffect>

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QFrame>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>

class loginpage : public QWidget {
    Q_OBJECT

public:
    loginpage(QWidget *parent = nullptr);

signals:
    void loginSuccessful();
    void Cansellsuccessful();
    void signsuccessful();

private slots:
    void tryLogin();
    void Cansell();
    void sign_up();

private:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;

    QPushButton *loginButton;
    QPushButton *cansell;
    QPushButton *sign;

    QHBoxLayout *buttonlayout;
    QHBoxLayout *hcentrallayout;
    QHBoxLayout *signLayout;
    QVBoxLayout *vcentrallayout;
    QVBoxLayout *verloglayout;

    QLabel *statusLabel;
    QGridLayout * loggride ;
    QFrame *frame;

    QGraphicsDropShadowEffect *shadow;

};

#endif // LOGINPAGE_H
