#ifndef SIGNUP_H
#define SIGNUP_H
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

class signup : public QWidget
{
    Q_OBJECT
public:
    explicit signup(QWidget *parent = nullptr);

signals:
    void signenter();
    void signback();


private slots:
    void enters();
    void backs();

private:
    QLineEdit *sign_name;
    QLineEdit *sign_password;

    QPushButton *sign_enter;
    QPushButton *sign_back;

    QLabel *statusLabel;
    QVBoxLayout *verloglayout;

    QGridLayout *loggride;

    QHBoxLayout *buttonlayout;
    QHBoxLayout *signLayout;
    QHBoxLayout *hcentrallayout;
    QVBoxLayout *vcentrallayout;

    QFrame *frame;
    //QGraphicsDropShadowEffect *shadow;


};

#endif // SIGNUP_H
