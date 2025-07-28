#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QImage> // مناسب هم برای دخیره و هم برای پردازش تصویر بر خلاف pixmap
#include<QFrame>
class translate : public QWidget
{
    Q_OBJECT

public:
    explicit translate(QWidget *parent = nullptr);

private slots:
    void loadImage(); // بارگذاری عکس از کاربر

private:
    QLabel *imageLabel; //  لیبل برای نمایش عکس
    QImage loadedImage; // تصویر اصلی برای پردازش
     QPushButton *select_image;
     QPushButton *select_vedio;
     QPushButton *select_cam;
    QFrame * mainframe ;
    void displayImage(const QImage &image); // تابع برای نمایش عکس
};

#endif // TRANSLATE_H
