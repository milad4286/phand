#include "opencvutils.h"

OpenCVUtils::OpenCVUtils(QObject *parent) : QObject(parent) {}

cv::Mat OpenCVUtils::QImageToCvMat(const QImage &image)
{
    // تبدیل تصویر به فرمت RGB888 که OpenCV به خوبی پشتیبانی می‌کند
    QImage conv = image.convertToFormat(QImage::Format_RGB888);
    // ساخت ماتریس OpenCV از داده‌های QImage
    cv::Mat mat(conv.height(), conv.width(), CV_8UC3, const_cast<uchar*>(conv.bits()), conv.bytesPerLine());
    // کپی کامل داده‌ها (مهم برای جلوگیری از مشکلات طول عمر داده)
    return mat.clone();
}

QImage OpenCVUtils::convertMatToQImage(const cv::Mat &mat)
{
    // اگر ماتریس 3 کاناله رنگی بود
    if (mat.type() == CV_8UC3) {
        // ساخت QImage از داده BGR ماتریس OpenCV
        QImage img(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_RGB888);
        return img.rgbSwapped(); // تبدیل BGR به RGB
    }
    // اگر ماتریس تک کاناله (خاکستری) بود
    else if (mat.type() == CV_8UC1) {
        QImage img(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_Grayscale8);
        return img.copy();  // کپی برای تضمین عمر داده
    }
    else {
        return QImage();
    }
}

QImage OpenCVUtils::convertToGray(const QImage &inputImage)
{
    cv::Mat mat = QImageToCvMat(inputImage);
    if (mat.empty()) return QImage();

    cv::Mat gray;
    // تبدیل رنگ از RGB به خاکستری
    cv::cvtColor(mat, gray, cv::COLOR_RGB2GRAY);

    return convertMatToQImage(gray);
}

QImage OpenCVUtils::applyBlur(const QImage &inputImage)
{
    cv::Mat mat = QImageToCvMat(inputImage);
    if (mat.empty()) return QImage();

    cv::Mat blurred;
    cv::GaussianBlur(mat, blurred, cv::Size(7, 7), 1.5);

    return convertMatToQImage(blurred);
}

QImage OpenCVUtils::detectEdges(const QImage &inputImage)
{
    cv::Mat mat = QImageToCvMat(inputImage);
    if (mat.empty()) return QImage();

    cv::Mat gray, edges;
    cv::cvtColor(mat, gray, cv::COLOR_RGB2GRAY);
    cv::Canny(gray, edges, 100, 200);

    return convertMatToQImage(edges);
}
