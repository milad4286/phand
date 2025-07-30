#include "translate.h"                     // فایل هدر مربوط به کلاس translate
#include <QFileDialog>                     // برای باز کردن دیالوگ انتخاب فایل
#include <QPixmap>                         // برای تبدیل QImage به Pixmap برای نمایش
#include <QHBoxLayout>                     // لایه‌چینی افقی
#include <QSize>                           // کار با اندازه‌ها
#include <QDebug>                          // برای چاپ دیباگ در console
#include <opencv2/imgproc.hpp>             // توابع پردازش تصویر OpenCV (مثل cvtColor)
#include <opencv2/highgui.hpp>             // (اختیاری) برای نمایش تصویر با OpenCV
#include <opencv2/core.hpp>                // اجزای پایه OpenCV

// تابع کمکی برای تبدیل QImage به cv::Mat با فرض اینکه تصویر از قبل به RGB888 تبدیل شده
cv::Mat QImageToCvMat(const QImage &image)
{
    // ابتدا تصویر را به فرمت 24بیتی RGB تبدیل می‌کنیم تا با ساختار OpenCV هماهنگ باشد
    QImage formatted = image.convertToFormat(QImage::Format_RGB888);

    // ساختن شیء cv::Mat با استفاده از اطلاعات تصویر (عرض، ارتفاع، نوع داده، اشاره‌گر به بیت‌ها، و stride)
    return cv::Mat(formatted.height(), formatted.width(), CV_8UC3,
                   (void*)formatted.bits(), formatted.bytesPerLine()).clone();
    // clone() باعث می‌شود داده‌ها کپی شوند و پس از خروج از تابع از بین نروند
}

// سازنده کلاس translate
translate::translate(QWidget *parent)
    : QWidget(parent)  // فراخوانی سازنده کلاس والد
{
    // === ساخت و تنظیم قاب مرکزی برای نمایش تصویر ===
    mainframe = new QFrame(this);
    mainframe->setFrameShape(QFrame::Box);            // شکل قاب: مستطیل ساده
    mainframe->setLineWidth(2);                       // ضخامت خط
    mainframe->setStyleSheet("QFrame { border: 2px solid gray; }"); // استایل قاب
    mainframe->setFixedSize(400, 400);                // اندازه ثابت قاب

    // === لیبل برای نمایش تصویر ===
    imageLabel = new QLabel(mainframe);               // داخل قاب
    imageLabel->setAlignment(Qt::AlignCenter);        // تراز وسط
    imageLabel->setText("هیچ تصویری بارگذاری نشده");  // متن پیش‌فرض

    // === لایه داخلی قاب (برای قرار دادن لیبل در وسط قاب) ===
    QVBoxLayout *frameInnerLayout = new QVBoxLayout(mainframe);
    frameInnerLayout->addWidget(imageLabel);          // افزودن لیبل به قاب
    frameInnerLayout->setContentsMargins(0, 0, 0, 0);  // حذف حاشیه‌های داخلی

    // === دکمه‌ها ===
    select_image = new QPushButton("انتخاب تصویر", this);
    select_vedio = new QPushButton("انتخاب ویدئو", this);
    select_cam   = new QPushButton("انتخاب دوربین", this);
    gray_button  = new QPushButton("تبدیل به خاکستری", this);

    // اتصال سیگنال کلیک دکمه‌ها به توابع مربوطه
    connect(gray_button, &QPushButton::clicked, this, &translate::convertToGray);
    connect(select_image, &QPushButton::clicked, this, &translate::loadImage);

    // === لایه افقی برای قرار دادن دکمه‌ها در یک ردیف ===
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(gray_button);
    buttonLayout->addWidget(select_image);
    buttonLayout->addWidget(select_vedio);
    buttonLayout->addWidget(select_cam);

    // === لایه برای مرکز کردن قاب تصویر در وسط پنجره ===
    QHBoxLayout *frameCenterLayout = new QHBoxLayout();
    frameCenterLayout->addStretch();                  // فضای خالی از چپ
    frameCenterLayout->addWidget(mainframe);          // قاب تصویر
    frameCenterLayout->addStretch();                  // فضای خالی از راست

    // === لایه اصلی کل پنجره ===
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();                         // فضای خالی از بالا
    mainLayout->addLayout(frameCenterLayout);         // قاب تصویر در مرکز
    mainLayout->addSpacing(10);                       // کمی فاصله بین قاب و دکمه‌ها
    mainLayout->addLayout(buttonLayout);              // ردیف دکمه‌ها
    mainLayout->addStretch();                         // فضای خالی از پایین

    setLayout(mainLayout);                            // ست کردن layout نهایی برای ویجت
}

// === تابع اسلات برای انتخاب تصویر توسط کاربر ===
void translate::loadImage()
{
    // نمایش دیالوگ انتخاب فایل برای گرفتن مسیر تصویر
    QString filePath = QFileDialog::getOpenFileName(this, "انتخاب تصویر", "", "Images (*.png *.jpg *.bmp)");

    // بررسی اینکه کاربر فایلی انتخاب کرده یا خیر
    if (!filePath.isEmpty()) {
        QImage image(filePath);              // بارگذاری تصویر از مسیر انتخاب‌شده
        if (!image.isNull()) {
            loadedImage = image;            // ذخیره تصویر برای پردازش بعدی
            displayImage(loadedImage);      // نمایش تصویر در UI
        } else {
            imageLabel->setText("خطا در بارگذاری تصویر!"); // پیام خطا
        }
    }
}

// === تابع برای نمایش تصویر در لیبل UI ===
void translate::displayImage(const QImage &image)
{
    QPixmap pixmap = QPixmap::fromImage(image); // تبدیل QImage به QPixmap
    QSize labelSize = imageLabel->size();       // اندازه لیبل فعلی
    imageLabel->setPixmap(pixmap.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    // نمایش تصویر با حفظ نسبت و کیفیت مناسب
}

// === تابع اسلات برای تبدیل تصویر به خاکستری ===
void translate::convertToGray()
{
    // اگر تصویری هنوز بارگذاری نشده
    if (loadedImage.isNull()) {
        imageLabel->setText("ابتدا یک تصویر بارگذاری کنید.");
        return;
    }

    // تبدیل تصویر به فرمت RGB888 (برای اطمینان از سازگاری با OpenCV)
    QImage preparedImage = loadedImage.convertToFormat(QImage::Format_RGB888);

    // تبدیل به cv::Mat
    cv::Mat mat = QImageToCvMat(preparedImage);

    if (mat.empty()) {
        imageLabel->setText("تبدیل به فرمت OpenCV ناموفق بود.");
        return;
    }

    // پردازش OpenCV: تبدیل به تصویر خاکستری
    cv::Mat grayMat;
    cv::cvtColor(mat, grayMat, cv::COLOR_BGR2GRAY); // تبدیل از BGR به GRAY

    // تبدیل خروجی OpenCV به QImage برای نمایش
    QImage grayQImage(grayMat.data, grayMat.cols, grayMat.rows, grayMat.step, QImage::Format_Grayscale8);

    // کپی کردن تصویر (برای اطمینان از باقی ماندن داده‌ها پس از پایان تابع)
    loadedImage = grayQImage.copy();

    // نمایش تصویر خاکستری
    displayImage(loadedImage);
}
