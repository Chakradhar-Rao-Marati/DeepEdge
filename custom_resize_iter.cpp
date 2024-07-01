#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

using namespace cv;
using namespace std;

// Custom resize function prototypes
void customResizeNearest(const Mat& src, Mat& dst);
void customResizeLinear(const Mat& src, Mat& dst);
void customResizeCubic(const Mat& src, Mat& dst);

// Helper function to measure time
void measureCustomResizeTime(void (*resizeFunc)(const Mat&, Mat&), const Mat& src, const string& method_name) {
    Mat dst;
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        resizeFunc(src, dst);
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Time taken for 1000 iterations using " << method_name << " : " << duration.count() << " ms" << endl;
}

// Main function
int custom_resize() {
    // Read the image
    Mat src = imread("G178_2 -1080.BMP");
    if (src.empty()) {
        cout << "Could not open or find the image!" << endl;
        return -1;
    }

    // Measure performance for custom resize functions
    measureCustomResizeTime(customResizeNearest, src, "Custom INTER_NEAREST");
    measureCustomResizeTime(customResizeLinear, src, "Custom INTER_LINEAR");
    measureCustomResizeTime(customResizeCubic, src, "Custom INTER_CUBIC");

    return 0;
}

// Implementations of custom resize functions

void customResizeNearest(const Mat& src, Mat& dst) {
    int newWidth = src.cols / 2;
    int newHeight = src.rows / 2;
    dst = Mat(newHeight, newWidth, src.type());

    for (int i = 0; i < newHeight; ++i) {
        for (int j = 0; j < newWidth; ++j) {
            int srcX = j * 2;
            int srcY = i * 2;
            dst.at<Vec3b>(i, j) = src.at<Vec3b>(srcY, srcX);
        }
    }
}

void customResizeLinear(const Mat& src, Mat& dst) {
    int newWidth = src.cols / 2;
    int newHeight = src.rows / 2;
    dst = Mat(newHeight, newWidth, src.type());

    for (int i = 0; i < newHeight; ++i) {
        for (int j = 0; j < newWidth; ++j) {
            float srcX = j * 2.0f;
            float srcY = i * 2.0f;
            int x = static_cast<int>(srcX);
            int y = static_cast<int>(srcY);
            float x_diff = srcX - x;
            float y_diff = srcY - y;

            Vec3b a = src.at<Vec3b>(y, x);
            Vec3b b = src.at<Vec3b>(y, x + 1);
            Vec3b c = src.at<Vec3b>(y + 1, x);
            Vec3b d = src.at<Vec3b>(y + 1, x + 1);

            for (int k = 0; k < 3; ++k) {
                dst.at<Vec3b>(i, j)[k] =
                    a[k] * (1 - x_diff) * (1 - y_diff) +
                    b[k] * x_diff * (1 - y_diff) +
                    c[k] * (1 - x_diff) * y_diff +
                    d[k] * x_diff * y_diff;
            }
        }
    }
}

void customResizeCubic(const Mat& src, Mat& dst) {
    // Implement custom cubic interpolation resize (a more complex task)
    // For simplicity, using OpenCV's implementation here as a placeholder
    resize(src, dst, Size(src.cols / 2, src.rows / 2), 0, 0, INTER_CUBIC);
}
