//
// Created by Alin Tcaci on 02.04.2024.
//

#include "lab6.hh"

void utcn::ip::Lab6::runLab() {
    int op;
    do {
        utcn::ip::Lab6::printMenu(LAB_MENU);
        std::cin >> op;
        switch (op) {
            case 0:
                break;
            case 1:
                function();
                break;
            case 2:
                reconstruct();
                break;
            default:
                std::cout << "Invalid selection" << std::endl;
        }
    }while (op != 0);
}

void utcn::ip::Lab6::function() {

    cv::Mat_<uchar> img = cv::imread("/Users/alintcaci/CLionProjects/ip-laboratory/assets/files_border_tracing/triangle_up.bmp",0);
    cv::Mat_<uchar> dst = cv::Mat(img.rows, img.cols, CV_8UC1, cv::Scalar(255));
    int di[] = {0, -1, -1, -1, 0, 1, 1, 1};
    int dj[] = {1, 1, 0, -1, -1, -1, 0, 1};

    std::vector<int> dirs; //vector de directii
    std::vector<std::pair<int, int>> pts; //vector pt punctele de pe contur
    std::vector<int> derivatives;

    for(int i = 0; i < img.rows; i++){
        for(int j = 0; j < img.cols; j++){
            if(img(i,j) == 0) {
                pts.push_back({i,j});
                goto et;
            }
        }
    }

    et:
        int dir = 7;
        while(1) { // parcurgem punctele de pe contur
            if(dir % 2 == 0)
                dir = (dir + 7) % 8;
            else
                dir = (dir + 6) % 8;

            for(int k = 0; k < 8; k++){ // parcurgem vecinii inepand de la dir
                int dirnow = (dir + k) % 8;
                int i2 = pts.back().first + di[dirnow];
                int j2 = pts.back().second + dj[dirnow];
                if(img(i2, j2) == 0){
                    pts.push_back({i2,j2});
                    dir = dirnow;
                    dst(i2, j2) = 0;
                    break;
                }
            }

            dirs.push_back(dir);

            int n = pts.size() - 1;
            if(n>=2 && pts[n] == pts[1] && pts[n-1] == pts[0]){
                goto et2;
            }

        }

    et2:
        printf("\nDirections: \n");
        for(int dir : dirs){
            printf("%d ", dir);
        }

        printf("\nDerivatives: \n");
        for(int i = 1; i < dirs.size(); i++){
                derivatives.push_back((dirs[i] - dirs[i - 1] + 8) % 8);
        }

        for(int der : derivatives){
            printf("%d ", der);
        }

    cv::imshow("Original", img);
    cv::imshow("Contur", dst);
    ImageUtil::macOsWaitKey();

}

void utcn::ip::Lab6::reconstruct() {
    // ------------ READ DATA FROM .TXT --------------
    std::ifstream file("/Users/alintcaci/CLionProjects/ip-laboratory/assets/files_border_tracing/reconstruct.txt");

    // height & width coordonatele punctului de plecare
    int height;
    int width;
    int n;
    file >> height >> width >> n;

    std::vector<int> dirs;
    int dir;
    for (int i = 0; i < n; ++i) {
        file >> dir;
        dirs.push_back(dir);
    }

    printf("Height; %d\n", height);
    printf("Width; %d\n", width);
    printf("Code chain length; %d\n", n);
    printf("Directions: \n");
    for (int dir : dirs) {
        printf("%d ", dir);
    }
    printf("\n");


    // --------------- RECONSTRUCT SHAPE -------------------
    cv::Mat_<uchar> img = cv::imread("/Users/alintcaci/CLionProjects/ip-laboratory/assets/files_border_tracing/gray_background.bmp",0);

    int di[] = {0, -1, -1, -1, 0, 1, 1, 1};
    int dj[] = {1, 1, 0, -1, -1, -1, 0, 1};
    std::vector<std::pair<int, int>> pts; //vector pt punctele de pe contur

    for(int dir: dirs) {
         height = height + di[dir];
         width = width + dj[dir];
        img(height, width) = 0;
    }

    cv::imshow("Original",img);
    ImageUtil::macOsWaitKey();
}


