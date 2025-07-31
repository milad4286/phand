#include "translate.h"
#include "opencvutils.h"

#include <QFileDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>

translate::translate(QWidget *parent)
    : QWidget(parent)
{
    // قاب اصلی
    QFrame *mainframe = new QFrame(this);
    mainframe->setFrameShape(QFrame::Box);
    mainframe->setStyleSheet("QFrame { border: 2px solid gray; }");
    mainframe->setFixedSize(400, 400);

    // لیبل نمایش تصویر
    imageLabel = new QLabel(mainframe);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setText("هیچ تصویری بارگذاری نشده");

    QVBoxLayout *frameInnerLayout = new QVBoxLayout(mainframe);
    frameInnerLayout->addWidget(imageLabel);
    frameInnerLayout->setContentsMargins(0, 0, 0, 0);

    // دکمه‌ها
    select_image = new QPushButton("انتخاب تصویر", this);
    gray_button  = new QPushButton("تبدیل به خاکستری", this);

    connect(select_image, &QPushButton::clicked, this, &translate::loadImage);
    connect(gray_button, &QPushButton::clicked, this, &translate::convertToGray);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(gray_button);
    buttonLayout->addWidget(select_image);

    QHBoxLayout *frameCenterLayout = new QHBoxLayout();
    frameCenterLayout->addStretch();
    frameCenterLayout->addWidget(mainframe);
    frameCenterLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addLayout(frameCenterLayout);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);
}

void translate::loadImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "انتخاب تصویر", "", "Images (*.png *.jpg *.bmp)");
    if (fileName.isEmpty()) return;

    QImage img(fileName);
    if (img.isNull()) return;

    currentImage = img;
    imageLabel->setPixmap(QPixmap::fromImage(currentImage).scaled(
        imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}


void translate::convertToGray()
{
    if (currentImage.isNull())
        return;

    QImage grayImage = OpenCVUtils::convertToGray(currentImage);

    // اضافه کردن تست دیباگ
    qDebug() << "Gray Image Size:" << grayImage.size();
    qDebug() << "Format:" << grayImage.format();

    if (!grayImage.isNull()) {
        currentImage = grayImage;
        imageLabel->setPixmap(QPixmap::fromImage(currentImage).scaled(
            imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        qDebug() << "Gray image is null!";
    }
}
