//
// Created by mario saber on 6/26/2025.
//

#ifndef USERUI_H
#define USERUI_H

#include <iostream>
#include "Headers/Image_Class.h"
#include "ImageProcessor.h"
using namespace std ;

class UserUI {
public:
    ImageProcessor *processor;
    UserUI(ImageProcessor *proc) {
        proc = processor;
    }
    virtual ~UserUI() = default;
    void mainMenu() const;
    Image loadImage(string name) const;
    void frameColor() const;
    void setImageName(string &outputName) const;
    void saveImage();
};

inline void UserUI::frameColor() const {

}
inline void UserUI::mainMenu() const {
    cout << "[1] Grayscale\n"
            "[2] Black and White\n"
            "[3] Invert image\n"
            "[4] Merge images\n"
            "[5] Flip image\n"
            "[6] Rotate image\n"
            "[7] Brightness\n"
            "[8] Crop image\n"
            "[9] Add a frame to image\n"
            "[10] Detect image edges\n"
            "[11] Resize image\n"
            "[12] Blur image\n"
            "[13] Natural sunlight image\n"
            "[14] Purple image\n"
            "[15] Infrared image\n"
            "[16] Load Image\n"
            "[17] Exit\n";

    cout << "Choose the filter: \n";
}
inline Image UserUI::loadImage(string name) const {
    cout << "Please Enter Name of the Image which you want to apply a filter on followed with (.png, .jpeg, .jpg, .bmp):";

    cin >> name;
    Image image;

    while(true) {
        try {
            image.loadNewImage(name);
            return image;
        }
        catch (invalid_argument) {
            cout << "Please enter a valid name: ";
            cin >> name;
        }
    }
}
inline void UserUI::setImageName(string &outputName) const {
    cout << "Enter Name of Saved Image: ";
    cin >> outputName;
}
inline void UserUI::saveImage() {

}




#endif //USERUI_H
