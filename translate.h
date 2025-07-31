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

private:
    QLabel *imageLabel;
    QPushButton *select_image;
    QPushButton *gray_button;
    QImage currentImage;
};

#endif // TRANSLATE_H
