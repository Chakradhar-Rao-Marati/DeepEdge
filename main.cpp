#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

using namespace cv;
using namespace std;
using namespace chrono;

// Custom resize function (nearest-neighbor interpolation)
void customResize(const Mat& src, Mat& dst, Size newSize) {
    dst.create(newSize, src.type());

    for (int y = 0; y < newSize.height; ++y) {
        for (int x = 0; x < newSize.width; ++x) {
            int origX = static_cast<int>(round(x * static_cast<float>(src.cols) / newSize.width));
            int origY = static_cast<int>(round(y * static_cast<float>(src.rows) / newSize.height));
            dst.at<Vec3b>(y, x) = src.at<Vec3b>(origY, origX);
        }
    }
}

int main() {
    // Load the input image
    Mat src = imread("G178_2 -1080.BMP", IMREAD_COLOR);
    if (src.empty()) {
        cerr << "Error: Could not read the image.\n";
        return -1;
    }

    // Define the new size for resizing
    Size newSize(src.cols / 2, src.rows / 2);

    // Define variables to hold the resized images
    Mat dst_nearest, dst_linear, dst_cubic, dst_custom_nearest, dst_custom_linear, dst_custom_cubic;

    // Perform resizing using OpenCV's resize function for each interpolation method
    resize(src, dst_nearest, newSize, 0, 0, INTER_NEAREST);
    resize(src, dst_linear, newSize, 0, 0, INTER_LINEAR);
    resize(src, dst_cubic, newSize, 0, 0, INTER_CUBIC);

    // Save the resized images from OpenCV's resize function
    imwrite("resized_nearest.png", dst_nearest);
    imwrite("resized_linear.png", dst_linear);
    imwrite("resized_cubic.png", dst_cubic);

    // Measure timings for 1000 iterations using OpenCV's resize function
    auto start_nearest = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        resize(src, dst_nearest, newSize, 0, 0, INTER_NEAREST);
    }
    auto end_nearest = high_resolution_clock::now();
    auto duration_nearest = duration_cast<milliseconds>(end_nearest - start_nearest);

    auto start_linear = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        resize(src, dst_linear, newSize, 0, 0, INTER_LINEAR);
    }
    auto end_linear = high_resolution_clock::now();
    auto duration_linear = duration_cast<milliseconds>(end_linear - start_linear);

    auto start_cubic = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        resize(src, dst_cubic, newSize, 0, 0, INTER_CUBIC);
    }
    auto end_cubic = high_resolution_clock::now();
    auto duration_cubic = duration_cast<milliseconds>(end_cubic - start_cubic);

    // Output timings for OpenCV's resize function
    cout << "Time taken for 1000 iterations using INTER_NEAREST: " << duration_nearest.count() << " ms\n";
    cout << "Time taken for 1000 iterations using INTER_LINEAR: " << duration_linear.count() << " ms\n";
    cout << "Time taken for 1000 iterations using INTER_CUBIC: " << duration_cubic.count() << " ms\n";

    // Measure timings for 1000 iterations using custom resize function
    auto start_custom_nearest = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        customResize(src, dst_custom_nearest, newSize);
    }
    auto end_custom_nearest = high_resolution_clock::now();
    auto duration_custom_nearest = duration_cast<milliseconds>(end_custom_nearest - start_custom_nearest);

    auto start_custom_linear = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        customResize(src, dst_custom_linear, newSize);
    }
    auto end_custom_linear = high_resolution_clock::now();
    auto duration_custom_linear = duration_cast<milliseconds>(end_custom_linear - start_custom_linear);

    auto start_custom_cubic = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        customResize(src, dst_custom_cubic, newSize);
    }
    auto end_custom_cubic = high_resolution_clock::now();
    auto duration_custom_cubic = duration_cast<milliseconds>(end_custom_cubic - start_custom_cubic);

    // Output timings for custom resize function
    cout << "Time taken for 1000 iterations using custom resize function (INTER_NEAREST): " << duration_custom_nearest.count() << " ms\n";
    cout << "Time taken for 1000 iterations using custom resize function (INTER_LINEAR): " << duration_custom_linear.count() << " ms\n";
    cout << "Time taken for 1000 iterations using custom resize function (INTER_CUBIC): " << duration_custom_cubic.count() << " ms\n";

    return 0;
}
