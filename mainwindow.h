#ifndef HANDELERPAGES_H
#define HANDELERPAGES_H
#include <QStackedWidget>
#include <QMainWindow>
#include "loginpage.h"
#include "homepage.h"
#include"translate.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
private:
    QStackedWidget *stack;
    loginpage      *login_page;
    homepage       *home_page;
    translate      *translate_page ;

};

#endif // HANDELERPAGES_H
