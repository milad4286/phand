#ifndef LOGINPAGE_H
#define LOGINPAGE_H
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QFrame>

class loginpage : public QWidget {
    Q_OBJECT

public:
    loginpage(QWidget *parent = nullptr);

signals:
    void loginSuccessful();

private slots:
    void tryLogin();
    void Cansell();

private:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *cansell;
    QVBoxLayout *verloglayout;
    QHBoxLayout *buttonlayout;
    QVBoxLayout * vcentrallayout;
    QHBoxLayout *hcentrallayout;
    QLabel *statusLabel;
    QGridLayout * loggride ;
    QFrame *frame;
};

#endif // LOGINPAGE_H
