//
// Created by mario saber on 6/26/2025.
//

#ifndef USERUI_H
#define USERUI_H

#include <iostream>

using namespace std ;

class UserUI {
public:
    void frameColor() const;
    void mainMenu() const;
    void setImageName(string &outputName) const;
};

inline void UserUI::frameColor() const {

}
inline void UserUI::mainMenu() const {
    cout << "[1] Grayscale\n"
            "[2] Black and White\n"
            "[3] Infrared image\n"
            "[4] Brightness\n"
            "[5] Flip image\n"
            "[6] Invert image\n"
            "[7] Merge images\n"
            "[8] Rotate image\n"
            "[9] Crop image\n"
            "[10] Add a frame to image\n"
            "[11] Detect image edges\n"
            "[12] Resize image\n"
            "[13] Blur image\n"
            "[14] Natural sunlight image\n"
            "[15] Purple image\n"
            "[16] Load Image\n"
            "[17] Exit\n";

    cout << "Choose the filter: \n";
}
inline void UserUI::setImageName(string &outputName) const {
    cout << "Enter Name of Saved Image: ";
    cin >> outputName;
}



#endif //USERUI_H
