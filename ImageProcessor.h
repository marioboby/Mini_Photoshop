//
// Created by mario saber on 6/26/2025.
//

#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <iostream>
#include "Headers/Image_Class.h"
using namespace std ;

class ImageProcessor {
public:
    virtual ~ImageProcessor() = default;
    virtual Image processImage(Image& image, const string& outputName) = 0;
    virtual string getFilterName() const = 0;
};

class GrayScale : public ImageProcessor {
public:
    Image processImage(Image &image, const string &outputName) override;
    string getFilterName() const override;
};

class BlackWhite : public ImageProcessor {
public:
    Image processImage(Image &image, const string &outputName) override;
    string getFilterName() const override;
};

class Rotate : public ImageProcessor {
    void rotate90(Image& image, const string& outputname);
    void rotate180(Image& image, const string& outputname);
    void rotate270(Image& image, const string& outputname);
public:
    Image processImage(Image &image, const string &outputName) override;
    string getFilterName() const override;
};

class Flip : public ImageProcessor {
public:
    Image processImage(Image &image, const string &outputName) override;
    string getFilterName() const override;
};

class Blur : public ImageProcessor {
public:
    Image processImage(Image &image, const string &outputName) override;
    string getFilterName() const override;
};

class Brightness : public ImageProcessor {
    Image processImage(Image &image, const string &outputName) override;
    string getFilterName() const override;
};

class invert : public ImageProcessor {
public:
    Image processImage(Image &image, const string &outputName) override;
    string getFilterName() const override;
};

class Crop : public ImageProcessor {
public:
    Image processImage(Image &image, const string &outputName) override;
    string getFilterName() const override;
};

class addFrame : public ImageProcessor {
    void createFrame(Image& framedImage, int newWidth, int newHeight, int scale, int red, int green, int blue);
    void placeImageInMiddle(Image& framedImage, Image& originalImage, int newWidth, int newHeight, int scale);
    void insideFrame(Image& image, int scale, int red, int green, int blue);
public:
    Image processImage(Image &image, const string &outputName) override;
    string getFilterName() const override;
};

class Yellow : public ImageProcessor {
public:
    Image processImage(Image &image, const string &outputName) override;
    string getFilterName() const override;
};

class Purple : public ImageProcessor {
public:
    Image processImage(Image &image, const string &outputName) override;
    string getFilterName() const override;
};

class InfraRed : public ImageProcessor {
public:
    Image processImage(Image &image, const string &outputName) override;
    string getFilterName() const override;
};

class EdgeDetect : public ImageProcessor {
public:
    Image processImage(Image &image, const string &outputName) override;
    string getFilterName() const override;
};

class Resize : public ImageProcessor {
public:
    Image processImage(Image &image, const string &outputName) override;
    string getFilterName() const override;
};

class Merge : public ImageProcessor {
    void Merge_only (Image& imageA,Image& imageB, const string& outputname);
    void merge_resize(Image& imageA,Image& imageB, const string& outputname);
public:
    Image processImage(Image &image, const string &outputName) override;
    string getFilterName() const override;
};

/**
 * FILTER IMPLEMENTATION
*/

/** @details there're two main functions for each filter,
 * 1- Getting filter's name
 * 2- processing an image using this flter
 */

inline string GrayScale::getFilterName() const {
    return "Gray Scale";
}

inline Image GrayScale::processImage(Image &image, const string &outputName) {
    for (int i =0 ; i < image.width; i++){
        for (int j =0 ; j< image.height; j++){
            unsigned int average = 0;

            for (int k = 0 ; k < image.channels; k++){
                average += image( i ,j ,k);
            }

            average /= 3 ;

            for (int m = 0 ; m < image.channels; m++){
                image(i ,j ,m)= average ;
            }
        }
    }
    return image;
}

inline string BlackWhite::getFilterName() const {
    return "Black and White";
}

inline Image BlackWhite::processImage(Image &image, const string &outputName) {
    for (int i =0 ; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int average;

            for (int k = 0; k < image.channels; k++) {
                average += image(i, j, k);

            }
            average /= 3;

            for (int m = 0; m < image.channels; m++) {
                if (average > 127) {
                    image(i, j, m) = 255;
                } else {
                    image(i, j, m) = 0;
                }
            }
        }
    }
    return image;
}

inline string InfraRed::getFilterName() const {
    return "Infra Red";
}

inline Image InfraRed::processImage(Image &image, const string &outputName) {
    ImageProcessor *processor = new GrayScale();
    image =  processor->processImage(image,outputName);

    for (int i =0 ; i < image.width; i++)
    {
        for (int j =0 ; j< image.height; j++)
        {
            image(i ,j ,0)= 255 ;
            image(i ,j ,1)= 255 - image(i ,j ,1);
            image(i ,j ,2)= 255 - image(i ,j ,2);
        }
    }
    return image;
}

inline string Brightness::getFilterName() const {
    return "Brightness";
}

inline Image Brightness::processImage(Image &image, const string &outputName) {
    while (true)
    {
        cout<<"what do you want to make the image \n[1] Lighter \n[2] Darker \n";

        int choice ;
        cin >> choice ;

        if (cin.fail())
        {
            cout << "Invalid input. Please enter an integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (choice ==1){

            for (int i = 0 ; i < image.width; i++){
                for (int j = 0 ; j< image.height; j++) {
                    int final ;
                    for (int k = 0; k < image.channels; k++) {
                        final = image(i, j, k)*1.5;
                        final = min(max(final,0),255);
                        image (i,j,k) = final;
                    }
                }
            }
            image.saveImage(outputName);
            cout << "Image brightened.\n";
            system(outputName.c_str());
            break;
        }
        else if (choice ==2){
            for (int i =0 ; i < image.width; i++){
                for (int j =0 ; j< image.height; j++) {
                    int final2;
                    for (int k = 0; k < image.channels; k++) {

                        final2 = image(i, j, k) * 0.5;
                        final2 = min(max(final2,0),255);
                        image (i,j,k)=final2;

                    }
                }
            }
            image.saveImage(outputName);
            cout << "Image darkened.\n";
            system(outputName.c_str());
            break;
        }
        else {
            cout << "Invalid Choice\n";
        }
    }
    return image;
}

inline string Flip::getFilterName() const {
    return "Flip";
}

inline Image Flip::processImage(Image &image, const string &outputName) {
    string new_name;
    cout << "enter the new image name"<< endl ;
    cin >> new_name;
    int flip_direction;
    cout << "Choose the flip direction: " << endl;
    cout << "1. Horizontal\n2. Vertical" << endl;
    cin >> flip_direction;

    // Create a new Image object for the flipped version
    Image flippedImage(image.width, image.height);

    while (true)
    {

        // Flip horizontally
        if (flip_direction == 1) {
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    int flippedColumn = image.width - 1 - i;
                    for (int k = 0; k < image.channels; ++k) {
                        flippedImage(flippedColumn, j, k) = image(i, j, k);
                    }
                }
            }
            flippedImage.saveImage(outputName);
            system(outputName.c_str());
            cout << "Image flipped horizontally.\n ";
            break;
        }
        // Flip vertically
         if (flip_direction == 2) {
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    int flippedRow = image.height - 1 - j;
                    for (int k = 0; k < image.channels; ++k) {
                        flippedImage(i, flippedRow, k) = image(i, j, k);
                    }
                }
            }

            flippedImage.saveImage(outputName);
            system(outputName.c_str());
            cout << "Image flipped vertically.\n ";
            break;

        }
        cout<< "please enter valid flip direction \n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> flip_direction ;
    }
    return image;
}

inline string Blur::getFilterName() const {
    return "Blur";
}

inline Image Blur::processImage(Image &image, const string &outputName) {
    return image;
}

inline string Rotate::getFilterName() const {
    return "Rotate";
}

inline Image Rotate::processImage(Image &image, const string &outputName) {
    return image;
}



#endif //IMAGEPROCESSOR_H
