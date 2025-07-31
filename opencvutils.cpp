#include "opencvutils.h"

OpenCVUtils::OpenCVUtils(QObject *parent) : QObject(parent) {}

cv::Mat OpenCVUtils::QImageToCvMat(const QImage &image)
{
    QImage formatted = image.convertToFormat(QImage::Format_RGB888);
    return cv::Mat(formatted.height(), formatted.width(), CV_8UC3,
                   const_cast<uchar*>(formatted.bits()), formatted.bytesPerLine()).clone();
}

QImage OpenCVUtils::convertMatToQImage(const cv::Mat &mat)
{
    if (mat.type() == CV_8UC3) {
        QImage img(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_RGB888);
        return img.rgbSwapped(); // از BGR به RGB
    } else if (mat.type() == CV_8UC1) {
        QImage img(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_Grayscale8);
        return img;
    } else {
        return QImage();
    }
}

QImage OpenCVUtils::convertToGray(const QImage &inputImage)
{
    cv::Mat mat = QImageToCvMat(inputImage);
    if (mat.empty()) return QImage();

    cv::Mat gray;
    cv::cvtColor(mat, gray, cv::COLOR_RGB2GRAY);  // ⚠️ حتما RGB

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
