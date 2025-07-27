#include "translate.h"
#include <QFileDialog>
#include <QPixmap>

translate::translate(QWidget *parent)
    : QWidget(parent)
{
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter); // وسط چین کردن لیبل
    imageLabel->setText("هیچ تصویری بارگذاری نشده"); // متن پیش فرض برای کاربر

    loadButton = new QPushButton("انتخاب تصویر", this);
    connect(loadButton, &QPushButton::clicked, this, &translate::loadImage);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(imageLabel);
    layout->addWidget(loadButton);
    setLayout(layout);
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
    imageLabel->setPixmap(pixmap.scaled(400, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
