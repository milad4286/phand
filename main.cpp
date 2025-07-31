#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>

QString loadStyleSheet(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qWarning("نمی‌تونم فایل QSS رو باز کنم.");
        return "";
    }
    QTextStream in(&file);
    return in.readAll();
}



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    // لود کردن QSS

    // لود کردن QSS
    QString path = QCoreApplication::applicationDirPath() + "/style.qss";
    QString qss = loadStyleSheet(path);

    if (!qss.isEmpty()) {
        a.setStyleSheet(qss); // ✅ فقط این کافی‌ست
    }

    MainWindow w;
    w.setWindowTitle(" مترجم زبان اشاره ");
    w.resize(800 , 600);
    w.show();
    return a.exec();
}

