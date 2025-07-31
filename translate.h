#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QImage>

class translate : public QWidget
{
    Q_OBJECT

public:
    explicit translate(QWidget *parent = nullptr);

private slots:
    void loadImage();
    void convertToGray();
    void convertToBlur();
    void reset();

private:
    QLabel *imageLabel;
    QPushButton *select_image;
    QPushButton *gray_button;
    QPushButton *blur_button;
    QPushButton *reset_button ;
    QImage currentImage;
    QImage mainimage;
};

#endif // TRANSLATE_H
