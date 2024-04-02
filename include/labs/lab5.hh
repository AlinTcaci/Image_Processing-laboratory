//
// Created by Alin Tcaci on 26.03.2024.
//

#ifndef LAB5_HH
#define LAB5_HH

#include <filesystem>
#include <lab.hh>

namespace utcn::ip {
    class Lab5: public Lab {
        static inline std::map<int, std::string> LAB_MENU = {
            {1, "Labeling_BFS"},
            {2, "Labeling_two_pass"}
        };

        static void labeling_BFS();

        static void labeling_two_pass();

        public:
            void runLab() override;
    };
}

#endif //LAB5_HH
