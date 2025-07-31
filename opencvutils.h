#ifndef OPENCVUTILS_H
#define OPENCVUTILS_H

#include <QObject>
#include <QImage>
#include <opencv2/opencv.hpp>

class OpenCVUtils : public QObject
{
    Q_OBJECT

public:
    explicit OpenCVUtils(QObject *parent = nullptr);

    // متدهای استاتیک برای تبدیل و پردازش
    static cv::Mat QImageToCvMat(const QImage &image);
    static QImage convertMatToQImage(const cv::Mat &mat);
    static QImage convertToGray(const QImage &inputImage);
    static QImage applyBlur(const QImage &inputImage);
    static QImage detectEdges(const QImage &inputImage);
    static std::vector<cv::Rect> drawGridOnImage(const cv::Mat& inputImage, cv::Mat& outputImage);

};

#endif // OPENCVUTILS_H
