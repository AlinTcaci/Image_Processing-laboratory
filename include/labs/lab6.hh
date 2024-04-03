//
// Created by Alin Tcaci on 02.04.2024.
//

#ifndef IP_LABS_MACOS_LAB6_HH
#define IP_LABS_MACOS_LAB6_HH

#include <filesystem>
#include <fstream>
#include <lab.hh>

namespace utcn::ip {
    class Lab6: public Lab {
        static inline std::map<int, std::string> LAB_MENU = {
                {1, "function"},
                {2, "reconstruct"}
        };

        static void function();

        static void reconstruct();

        public:
            void runLab() override;
    };
}

#endif //IP_LABS_MACOS_LAB6_HH
