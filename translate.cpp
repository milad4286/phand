#include "translate.h"
#include <QFileDialog>
#include <QPixmap>
#include "translate.h"
#include <QFileDialog>
#include <QPixmap>
#include <QHBoxLayout>
#include <QSize>

translate::translate(QWidget *parent)
    : QWidget(parent)
{
    // ایجاد فریم و تنظیمات آن
    mainframe = new QFrame(this);
    mainframe->setFrameShape(QFrame::Box);
    mainframe->setLineWidth(2);
    mainframe->setStyleSheet("QFrame { border: 2px solid gray; }");
    mainframe->setFixedSize(400, 400); // اندازه ثابت

    // تصویر
    imageLabel = new QLabel(mainframe);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setText("هیچ تصویری بارگذاری نشده");

    // لی‌اوت داخلی فریم (برای وسط‌چین کردن لیبل در فریم)
    QVBoxLayout *frameInnerLayout = new QVBoxLayout(mainframe);
    frameInnerLayout->addWidget(imageLabel);
    frameInnerLayout->setContentsMargins(0, 0, 0, 0);

    // دکمه‌ها
    select_image = new QPushButton("انتخاب تصویر", this);
    select_vedio = new QPushButton("انتخاب ویدئو", this);
    select_cam   = new QPushButton("انتخاب دوربین", this);
    connect(select_image, &QPushButton::clicked, this, &translate::loadImage);

    // دکمه‌ها در یک لایه افقی
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(select_image);
    buttonLayout->addWidget(select_vedio);
    buttonLayout->addWidget(select_cam);

    // لایه مرکزی برای قرار دادن فریم در وسط
    QHBoxLayout *frameCenterLayout = new QHBoxLayout();
    frameCenterLayout->addStretch();
    frameCenterLayout->addWidget(mainframe);
    frameCenterLayout->addStretch();

    // لایه اصلی
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addLayout(frameCenterLayout);  // مرکز کردن فریم
    mainLayout->addSpacing(10);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);
}


// privat slots
void translate::loadImage()
{
    QString filePath = QFileDialog::getOpenFileName(this, "انتخاب تصویر", "", "Images (*.png *.jpg *.bmp)");

    if (!filePath.isEmpty()) {
        QImage image(filePath);
        if (!image.isNull()) {
            loadedImage = image; // ذخیره برای پردازش بعدی
            displayImage(loadedImage);
        } else {
            imageLabel->setText("خطا در بارگذاری تصویر!");
        }
    }
}

void translate::displayImage(const QImage &image)
{
    QPixmap pixmap = QPixmap::fromImage(image);
    QSize labelSize = imageLabel->size(); // گرفتن اندازه لیبل
    imageLabel->setPixmap(pixmap.scaled(labelSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

}
