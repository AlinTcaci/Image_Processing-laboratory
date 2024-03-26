//
// Created by Alin Tcaci on 19.03.2024.
//

#ifndef LAB4_HH
#define LAB4_HH

#include <filesystem>


#include "lab.hh"

namespace utcn::ip {
    class Lab4: public Lab {
        static inline std::map<int, std::string> LAB_MENU = {
            {1,
                "For a specific object in a labeled image selected by a mouse click, compute the object’s area,"
                "center of mass, axis of elongation, perimeter, thinness ratio and aspect ratio."},
            {2,
                "Create a new processing function which takes as input a labeled image and keeps in the output image only the objects that:"
                "a. have their area < TH_area"
                "b. have a specific orientation phi, where phi_LOW < phi < phi_HIGH."},
          };

        static void testObjectSelected();

        static void testProcessingFunction();

        static void GeometricalFeaturesComputation(int event, int x, int y, int flags, void* param);

        static void GeometricalFeatures();


    public:
        void runLab() override;
    };
}

#endif //LAB4_HH
