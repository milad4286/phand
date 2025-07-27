#ifndef MAINPAGE_H
#define MAINPAGE_H
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include<QPushButton>

class homepage : public QWidget {
    Q_OBJECT
public:
    homepage(QWidget *parent = nullptr);

signals :
    void gotologinpage();
    void gototrpage();

private :
    QPushButton *btngotologinpage ;
    QPushButton *btngototranslatepage ;
};


#endif // MAINPAGE_H
