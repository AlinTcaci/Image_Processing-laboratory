//
// Created by Alin Tcaci on 26.03.2024.
//
#include <lab5.hh>

void utcn::ip::Lab5::runLab() {
    int op;
    do {
        utcn::ip::Lab5::printMenu(LAB_MENU);
        std::cin >> op;
        switch (op) {
            case 0:
                break;
            case 1:
                labeling_BFS();
                break;
            case 2:
                labeling_two_pass();
                break;
            default:
                std::cout << "Invalid selection" << std::endl;
        }
    }while (op != 0);
}

void utcn::ip::Lab5::labeling_BFS() {
    const std::string abs_image_path = fileutil::getSingleFileAbsPath();
    if(!abs_image_path.empty()) {
        cv::Mat src = cv::imread(abs_image_path, cv::IMREAD_GRAYSCALE);
        int height = src.rows;
        int width = src.cols;
        int label = 0;

        int neighbours_i[8] = {0, -1, -1, -1, 0, 1, 1, 1};
        int neighbours_j[8] = {1, 1, 0, -1, -1, -1, 0, 1};
        std::map<int, cv::Vec3b> labelColors;

        cv::Mat labels(height, width, CV_32FC1, cv::Scalar(0,0,0));
        cv::Mat dst(height, width, CV_8UC3, cv::Scalar(0));

        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                cv::Vec3b color = cv::Vec3b(rand() % 256, rand() % 256, rand() % 256);
                if(src.at<uchar>(i,j) == 0  && labels.at<int>(i,j) == 0) {

                    label++;
                    std::queue<cv::Point> Q;
                    labels.at<int>(i,j) = label;
                    Q.push(cv::Point(i,j));
                    while(!Q.empty()) {
                        cv::Point q = Q.front();
                        Q.pop();
                        for(int k = 0 ; k < 8; k++) {
                            if(src.at<uchar>(q.x + neighbours_i[k], q.y + neighbours_j[k]) == 0 && labels.at<int>(q.x + neighbours_i[k], q.y + neighbours_j[k]) == 0) {
                                labels.at<int>(q.x + neighbours_i[k], q.y + neighbours_j[k]) = label;
                                Q.push(cv::Point(q.x + neighbours_i[k],q.y + neighbours_j[k]));

                            }
                        }
                        dst.at<cv::Vec3b>(q.x, q.y) = color;
                    }
                }
            }
        }

        cv::imshow("Original", src);
        cv::imshow("Labels", dst);
        ImageUtil::macOsWaitKey();
    }

}

void utcn::ip::Lab5::labeling_two_pass() {
    const std::string abs_image_path = fileutil::getSingleFileAbsPath();
    cv::Mat src = cv::imread(abs_image_path, cv::IMREAD_GRAYSCALE);
    if(!abs_image_path.empty()) {
        int height = src.rows;
        int width = src.cols;
        int label = 0;

        cv::Mat labels = cv::Mat(height, width, CV_32FC1, cv::Scalar(0));
        std::vector<std::vector<int>> edges(1000);

        int di[4] = {-1, 0, 1, 0};
        int dj[4] = {0, -1, 0, 1};

        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                if(src.at<uchar>(i,j) == 0 && labels.at<int>(i,j) == 0) {
                    std::vector<int> L;

                    for(int k = 0; k < 4; k++) {
                        if(labels.at<int>(i + di[k], j + dj[k]) > 0) {
                            L.push_back(labels.at<int>(i + di[k], j + dj[k]));
                        }
                    }

                    if(L.empty()) {
                        label++;
                        labels.at<int>(i,j) = label;
                    } else {
                        int x = *std::ranges::min_element(L.begin(), L.end());
                        labels.at<int>(i,j) = x;
                        for(int y = 0; y < L.size(); y++) {
                            if(L[y] != x) {
                                edges[x].push_back(L[y]);
                                edges[L[y]].push_back(x);
                            }
                        }

                    }


                }
            }
        }

        int newlabel = 0;
        std::vector<int> newlabels(label + 1, 0);
        for(int i = 0; i <= label; i++) {
            if(newlabels[i] == 0) {
                newlabel++;
                std::queue<int> Q;
                newlabels[i] = newlabel;
                Q.push(i);
                while(!Q.empty()) {
                    int x = Q.front();
                    Q.pop();
                    for(int y : edges[x]) {
                        if(newlabels[y] == 0) {
                            newlabels[y] = newlabel;
                            Q.push(y);
                        }
                    }
                }
            }
        }

        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                labels.at<int>(i,j) = newlabels[labels.at<int>(i,j)];
            }
        }

        std::vector<cv::Scalar> colors(newlabel + 1);
        for (int i = 1; i <= newlabel; i++) {
            colors[i] = cv::Scalar(rand() % 256, rand() % 256, rand() % 256);
        }

        cv::Mat coloredLabels = cv::Mat(height, width, CV_8UC3);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int label = labels.at<int>(i, j);
                if (label > 0) {
                    coloredLabels.at<cv::Vec3b>(i, j) = cv::Vec3b(colors[label][0], colors[label][1], colors[label][2]);
                } else {
                    coloredLabels.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 0);
                }
            }
        }

        cv::imshow("Labeled Image", coloredLabels);

        cv::imshow("Original", src);
        ImageUtil::macOsWaitKey();
    }
}