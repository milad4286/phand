#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QImage> // مناسب هم برای دخیره و هم برای پردازش تصویر بر خلاف pixmap

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
    QPushButton *loadButton;
    void displayImage(const QImage &image); // تابع برای نمایش عکس
};

#endif // TRANSLATE_H
