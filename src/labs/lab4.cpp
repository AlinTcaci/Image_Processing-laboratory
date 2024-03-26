//
// Created by Alin Tcaci on 19.03.2024.
//
#include <lab4.hh>

void utcn::ip::Lab4::runLab() {
    int op;
    do {
        utcn::ip::Lab4::printMenu(LAB_MENU);
        std::cin >> op;
        switch (op) {
            case 0:
                break;
            case 1:
                GeometricalFeatures();
            break;
            case 2:
                testProcessingFunction();
            break;
            default:
                std::cout << "Invalid selection" << std::endl;
        }
    } while (op != 0);
}

void utcn::ip::Lab4::GeometricalFeaturesComputation(int event, int x, int y, int flags,
                                    void *param) {
    // More examples:
    // http://opencvexamples.blogspot.com/2014/01/detect-mouse-clicks-and-moves-on-image.html
    auto *src = (cv::Mat *)param;
    if (event == cv::EVENT_LBUTTONDOWN) {
        cv::Vec3b color = (*src).at<cv::Vec3b>(y,x);
        printf("Pos(x,y): %d,%d  Color(RGB): %d,%d,%d\n", x, y,
               (int)(*src).at<cv::Vec3b>(y, x)[2],
               (int)(*src).at<cv::Vec3b>(y, x)[1],
               (int)(*src).at<cv::Vec3b>(y, x)[0]);

        int area = 0;
        int r = 0;
        int c = 0;
        int Cmax = -1, Rmax = -1;
        int Cmin = 999999, Rmin = 999999;
        for(int i = 0; i < src->rows; i++) {
            for(int j = 0; j < src->cols; j++) {
                if(src->at<cv::Vec3b>(i,j) == color) {
                    area++;
                    r = r + i;
                    c = c + j;
                    if(Cmax < j) Cmax = j;
                    if(Cmin > j) Cmin = j;
                    if(Rmax < i) Rmax = i;
                    if(Rmin > i) Rmin = i;
                }
            }
        }

        printf("Area with color(RGB) %d,%d,%d is %d\n",
                (int)color[2],
                (int)color[1],
                (int)color[0],
                area);

        int R = 1 / (float)area * r;
        int C = 1 / (float)area * c;

        printf("Center of mass is (%d,%d)\n", R,C);

        float sum1 = 0, sum2 = 0, sum3 = 0;

        for(int i = 0; i < src->rows; i++)
            for(int j = 0; j < src->cols; j++) {
                if(src->at<cv::Vec3b>(i,j) == color) {
                    int x_diff = j - C;
                    int y_diff = i - R;
                    sum1 += x_diff * x_diff;
                    sum2 += y_diff * y_diff;
                    sum3 += x_diff * y_diff;
                }
            }

        float theta = 0.5 * atan2(2 * sum3, sum1 - sum2);
        if(theta < 0)
            theta += CV_PI;

        printf("Angle of elongation (in degrees): %.3f\n", theta * (180.0 / CV_PI));

        int p = 0;
        for(int i = 0; i < src->rows; i++) {
            for(int j = 0; j < src->cols; j++) {
                if(src->at<cv::Vec3b>(i,j) == color) {
                    if(src->at<cv::Vec3b>(i - 1, j) != color) p++;
                    else if(src->at<cv::Vec3b>(i + 1, j) != color) p++;
                    else if(src->at<cv::Vec3b>(i, j + 1) != color) p++;
                    else if(src->at<cv::Vec3b>(i, j - 1) != color) p++;
                    else if(src->at<cv::Vec3b>(i - 1, j + 1) != color) p++;
                    else if(src->at<cv::Vec3b>(i - 1, j - 1) != color) p++;
                    else if(src->at<cv::Vec3b>(i + 1, j + 1) != color) p++;
                    else if(src->at<cv::Vec3b>(i + 1, j - 1) != color) p++;
                }
            }
        }

        int P =  p * CV_PI / 4;
        printf("Perimeter is %d\n", P);

        float T = 4 * CV_PI * area / (P * P);
        printf("Thickness ration is %f\n", T);

        float aspectRatio = (float)(Cmax - Cmin + 1) / (float)(Rmax - Rmin + 1);
        printf("Aspect ratio is %f\n", aspectRatio);

        // Projection
        cv::Mat LeftProjection = cv::Mat(src->rows, src->cols,CV_8UC3);
        cv::Mat DownProjection = cv::Mat(src->rows, src->cols,CV_8UC3);

        for(int i = 0; i < LeftProjection.rows; i++)
            for(int j = 0; j < LeftProjection.cols; j++) {
                LeftProjection.at<cv::Vec3b>(i,j) = {0,0,0};
                DownProjection.at<cv::Vec3b>(i,j) = {0,0,0};

            }

        for(int i = 0; i < src->rows; i++) {
            int j_LeftProjection = 0;
            for(int j = 0; j < src->cols; j++) {
                if(src->at<cv::Vec3b>(i,j) == color) {
                    LeftProjection.at<cv::Vec3b>(i,j_LeftProjection++) = color;
                }
            }
        }
        cv::imshow("LeftProjection", LeftProjection);

        for(int j = 0; j < src->cols; j++) {
            int i_DownProjection = src->rows;
            for(int i = 0; i < src->rows; i++) {
                if(src->at<cv::Vec3b>(i,j) == color) {
                    DownProjection.at<cv::Vec3b>(i_DownProjection--,j) = color;
                }
            }
        }
        cv::imshow("DownProjection", DownProjection);

        // Drawing - axis of elongation
        cv::Mat srcAxis = src->clone();
        int Ca = Cmin;
        int Cb = Cmax;
        int Ra = R + tan(theta) * (Cmin - C);
        int Rb = R + tan(theta) * (Cmax - C);

        cv::Point A(Ca, Ra);
        cv::Point B(Cb, Rb);
        line(srcAxis, A, B, cv::Scalar(0,0,0), 2);

        cv::imshow("Line", srcAxis);

        printf("\n");
    }
}

void utcn::ip::Lab4::GeometricalFeatures() {
    //const std::string abs_image_path = fileutil::getSingleFileAbsPath();
    const std::string abs_image_path = ASSETS_DIR "Geometric_Images/Obiecte multiple/trasaturi_geometrice.bmp";
    if (!abs_image_path.empty()) {
        cv::Mat src = cv::imread(abs_image_path);
        // Create a window
        cv::namedWindow("My Window", 1);

        // set the callback function for any mouse event
        cv::setMouseCallback("My Window", GeometricalFeaturesComputation, &src);

        // show the image
        cv::imshow("My Window", src);

        // Wait until user press some key
        ImageUtil::macOsWaitKey();
    }
}

void utcn::ip::Lab4::testObjectSelected() {
    // For a specific object in a labeled image selected by a mouse click, compute the object’s area,
    // center of mass, axis of elongation, perimeter, thinness ratio and aspect ratio.
    // a. Display the results in the standard output
    // b. In a separate image (source image clone):
    //      o Draw the contour points of the selected object
    //      o Display the center of mass of the selected object
    //      o Display the axis of elongation of the selected object by using the line function from OpenCV.
    // c. Compute and display the projections of the selected object in a separate image (source image clone).

}

void utcn::ip::Lab4::testProcessingFunction() {
    // Create a new processing function which takes as input a labeled image and keeps in the output
    // image only the objects that:
    //      a. have their area < TH_area
    //      b. have a specific orientation phi, where phi_LOW < phi < phi_HIGH
    // where TH_area, phi_LOW, phi_HIGH are given by the user.

}

