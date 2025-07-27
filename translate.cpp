#include "translate.h".h"
#include<QWidget>
#include <QVBoxLayout>

translate::translate(QWidget *parent) : QWidget(parent) {

    auto *centralwig = new QWidget(this) ;

    auto *vmainlayout = new QVBoxLayout() ;
    vmainlayout->addWidget(centralwig);
    this->setLayout(vmainlayout);











}
