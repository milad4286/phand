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

    // دکمه‌ها
    select_image = new QPushButton("انتخاب تصویر", this);
    gray_button  = new QPushButton("تبدیل به خاکستری", this);
    grid_button  = new QPushButton("گرید کردن", this);

    // استایل
    select_image->setObjectName("loginbutton");
    gray_button->setObjectName("loginbutton_cv");
    grid_button->setObjectName("loginbutton_cv");


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
    blur_button = new QPushButton(" تبدیل به بلور ", this) ;
    reset_button = new QPushButton ("ریست", this) ;

    connect(select_image, &QPushButton::clicked  , this , &translate::loadImage);
    connect(reset_button, &QPushButton::clicked  , this , &translate::reset);
    connect(gray_button , &QPushButton::clicked  , this , &translate::convertToGray);
    connect(blur_button , &QPushButton::clicked  , this , &translate::convertToBlur);
    connect(grid_button, &QPushButton::clicked, this, &translate::applyGrid);





    QHBoxLayout *buttonLayout = new QHBoxLayout();

    buttonLayout->addWidget(select_image);
    buttonLayout->addWidget(reset_button);

    QVBoxLayout *button_cv = new QVBoxLayout();
    button_cv->addWidget(gray_button);
    button_cv->addWidget(grid_button);
    button_cv->addWidget(gray_button);
    button_cv->addWidget(blur_button);

    QHBoxLayout *frameCenterLayout = new QHBoxLayout();
    frameCenterLayout->addStretch();
    frameCenterLayout->addLayout(button_cv);
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
    mainimage = img ;
    imageLabel->setPixmap(QPixmap::fromImage(currentImage).scaled(
        imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
//////////////////////////////////// reset

void translate::reset(){

    imageLabel->setPixmap(QPixmap::fromImage(mainimage).scaled(
        imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

}

void translate::convertToGray()
{

    if (currentImage.isNull())
        return;

    QImage grayImage = OpenCVUtils::convertToGray(currentImage);

    if (!grayImage.isNull()) {

        currentImage = grayImage;
        imageLabel->setPixmap(QPixmap::fromImage(currentImage).scaled(
            imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        qDebug() << "Gray image is null!";
    }
}


///////////////////////////// convert to blur

void translate::convertToBlur(){

    if (currentImage.isNull())
        return;
    QImage blurimage = OpenCVUtils::applyBlur(currentImage);
    if (!blurimage.isNull()) {

        currentImage = blurimage;
        imageLabel->setPixmap(QPixmap::fromImage(currentImage).scaled(
            imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        qDebug() << "blur image is null!";
    }


}

void translate::applyGrid()
{
    if (currentImage.isNull())
        return;

    cv::Mat inputMat = OpenCVUtils::QImageToCvMat(currentImage);
    cv::Mat outputMat;

    std::vector<cv::Rect> grid = OpenCVUtils::drawGridOnImage(inputMat, outputMat);

    QImage resultImage = OpenCVUtils::convertMatToQImage(outputMat);
    if (!resultImage.isNull()) {
        currentImage = resultImage;
        imageLabel->setPixmap(QPixmap::fromImage(currentImage).scaled(
            imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

