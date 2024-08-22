#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void applyGrayscale(Mat &image) {
    cvtColor(image, image, COLOR_BGR2GRAY);
}

void applyBlur(Mat &image) {
    GaussianBlur(image, image, Size(15, 15), 0);
}

void applySharpen(Mat &image) {
    Mat kernel = (Mat_<float>(3, 3) <<  0, -1,  0, -1,  5, -1,0, -1,  0);
    filter2D(image, image, image.depth(), kernel);
}

void adjustColor(Mat &image, double alpha, int beta) {
    image.convertTo(image, -1, alpha, beta);
}

void cropAndResize(Mat &image, Rect roi) {
    image = image(roi);
    resize(image, image, Size(400, 400)); // Resize to 400x400 for simplicity
}

void saveImage(const Mat &image, const string &filename) {
    imwrite(filename, image);
}

void displayImage(const Mat &image) {
    imshow("Image", image);
    waitKey(0);
}

int main() {
    string filename = "input.jpg"; // Input image file
    Mat image = imread(filename);

    if (image.empty()) {
        cout << "Could not open or find the image!" << endl;
        return -1;
    }

    int choice;
    cout << "Choose an option:\n1. Grayscale\n2. Blur\n3. Sharpen\n4. Adjust Color\n5. Crop and Resize\n6. Save Image\n";
    cin >> choice;

    switch (choice) {
        case 1:
            applyGrayscale(image);
            break;
        case 2:
            applyBlur(image);
            break;
        case 3:
            applySharpen(image);
            break;
        case 4: {
            double alpha;
            int beta;
            cout << "Enter alpha (contrast) and beta (brightness): ";
            cin >> alpha >> beta;
            adjustColor(image, alpha, beta);
            break;
        }
        case 5: {
            int x, y, width, height;
            cout << "Enter x, y, width, height for cropping: ";
            cin >> x >> y >> width >> height;
            cropAndResize(image, Rect(x, y, width, height));
            break;
        }
        case 6: {
            string saveFilename;
            cout << "Enter filename to save the image: ";
            cin >> saveFilename;
            saveImage(image, saveFilename);
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
            return -1;
    }

    displayImage(image);
    return 0;
}
