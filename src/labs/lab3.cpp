//
// Created by Alin Tcaci on 06.03.2024.
//
#include <lab3.hh>

void utcn::ip::Lab3::runLab() {
  int op;
  do {
    utcn::ip::Lab3::printMenu(LAB_MENU);
    std::cin >> op;
    switch (op) {
      case 0:
        break;
      case 1:
        testHistogramGrayscale();
      break;
      case 2:
        testComputePDF();
      break;
      case 3:
        testDisplayHistogram();
      break;
      case 4:
        testHistogramByBins();
      break;
      case 5:
        testMultilevelThresholding();
      break;
      case 6:
        testFloydSteinberg();
      break;
      case 7:
        testMultilevelThresholdingOnColorImage();
      break;
      default:
        std::cout << "Invalid selection" << std::endl;
    }
  } while (op != 0);
}

void utcn::ip::Lab3::testHistogramGrayscale() {

}

void utcn::ip::Lab3::testComputePDF() {

}

void utcn::ip::Lab3::testDisplayHistogram() {

}

void utcn::ip::Lab3::testHistogramByBins() {

}

void utcn::ip::Lab3::testMultilevelThresholding() {

}

void utcn::ip::Lab3::testFloydSteinberg() {

}

void utcn::ip::Lab3::testMultilevelThresholdingOnColorImage() {

}





