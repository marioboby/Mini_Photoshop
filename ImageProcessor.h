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
    virtual Image processImage(Image& image) = 0;
    virtual string getFilterName() const = 0;
};

class ImageManager {
    ImageProcessor **processor;
public:
    ImageManager();
    ImageManager(ImageProcessor **proc);
    void saveImg(Image &image, string &outputName);
    Image loadImage(string name) const;
};

class GrayScale : public ImageProcessor {
public:
    Image processImage(Image &image) override;
    string getFilterName() const override;
};

class BlackWhite : public ImageProcessor {
public:
    Image processImage(Image &image) override;
    string getFilterName() const override;
};

class Rotate : public ImageProcessor {
    Image rotate90(Image& image);
    Image rotate180(Image& image);
    Image rotate270(Image& image);
public:
    Image processImage(Image &image) override;
    string getFilterName() const override;
};

class Flip : public ImageProcessor {
    Image flipVertical(Image &image);
    Image flipHorizontal(Image &image);
public:
    Image processImage(Image &image) override;
    string getFilterName() const override;
};

class Blur : public ImageProcessor {
public:
    Image processImage(Image &image) override;
    string getFilterName() const override;
};

class Brightness : public ImageProcessor {
    void darken (Image &image);
    void brighten (Image &image);
public:
    Image processImage(Image &image) override;
    string getFilterName() const override;
};

class Invert : public ImageProcessor {
public:
    Image processImage(Image &image) override;
    string getFilterName() const override;
};

class Crop : public ImageProcessor {
public:
    Image crop(Image &image, int x, int y, int wdth, int hght);
    Image processImage(Image &image) override;
    string getFilterName() const override;
};

class addFrame : public ImageProcessor {
    void createFrame(Image& framedImage, int newWidth, int newHeight, int red, int green, int blue);
    void placeImageInMiddle(Image& framedImage, Image& originalImage, int newWidth, int newHeight, int scale);
    void insideFrame(Image& image, int scale, int red, int green, int blue);
public:
    Image processImage(Image &image) override;
    string getFilterName() const override;
};

class Yellow : public ImageProcessor {
public:
    Image processImage(Image &image) override;
    string getFilterName() const override;
};

class Purple : public ImageProcessor {
public:
    Image processImage(Image &image) override;
    string getFilterName() const override;
};

class InfraRed : public ImageProcessor {
public:
    Image processImage(Image &image) override;
    string getFilterName() const override;
};

class EdgeDetect : public ImageProcessor {
public:
    Image processImage(Image &image) override;
    string getFilterName() const override;
};

class Resize : public ImageProcessor {
public:
    Image resize(Image& image, int new_width, int new_height);
    Image processImage(Image &image) override;
    string getFilterName() const override;
};

class Merge : public ImageProcessor {
    Image Merge_only(Image &imageA, Image &imageB);
    Image mergeAndResize(Image &imageA, Image &imageB);
public:
    Image processImage(Image &image) override;
    string getFilterName() const override;
};


inline ImageManager::ImageManager() {
    processor = nullptr;
}

inline ImageManager::ImageManager(ImageProcessor **proc) {
    processor = proc;
}

inline Image ImageManager::loadImage(string name) const {
    cout << "Please Enter Name of the Image which you want to apply a filter on followed with (.png, .jpeg, .jpg, .bmp): ";

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

inline void ImageManager::saveImg(Image &image, string &outputName) {
    if (!processor) {
        cerr << "Processor not set! Please select a filter first.\n";
        return;
    }
    image = (*processor)->processImage(image);
    cout << "Image Processed Successfully By Filter " << (*processor)->getFilterName() << endl;
    image.saveImage(outputName);
    system(outputName.c_str());
}

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

inline Image GrayScale::processImage(Image &image) {
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

inline Image BlackWhite::processImage(Image &image) {
    for (int i =0 ; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int average = 0;

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

inline Image InfraRed::processImage(Image &image) {
    ImageProcessor *processor = new GrayScale();
    image =  processor->processImage(image);

    for (int i =0 ; i < image.width; i++)
    {
        for (int j =0 ; j< image.height; j++)
        {
            image(i ,j ,0)= 255 ;
            image(i ,j ,1)= 255 - image(i ,j ,1);
            image(i ,j ,2)= 255 - image(i ,j ,2);
        }
    }
    delete processor;
    return image;
}

inline string Brightness::getFilterName() const {
    return "Brightness";
}

inline string Invert::getFilterName() const {
    return "Invert";
}

inline Image Invert::processImage(Image &image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            image(i, j, 0) = 255 - image(i, j, 0);
            image(i, j, 1) = 255 - image(i, j, 1);
            image(i, j, 2) = 255 - image(i, j, 2);
        }
    }

    return image;
}

inline void Brightness::darken(Image &image) {
    for (int i =0 ; i < image.width; i++){
        for (int j =0 ; j< image.height; j++) {
            int final2;
            for (int k = 0; k < image.channels; k++) {

                final2 = image(i, j, k) * 0.5;
                final2 = min(max(final2,0),255);
                image (i,j,k) = final2;

            }
        }
    }
}

inline void Brightness::brighten(Image &image) {
    for (int i = 0 ; i < image.width; i++){
        for (int j = 0 ; j< image.height; j++) {
            int final ;
            for (int k = 0; k < image.channels; k++) {
                final = image(i, j, k)* 1.5;
                final = min(max(final,0),255);
                image (i,j,k) = final;
            }
        }
    }
}

inline Image Brightness::processImage(Image &image) {
    while (true)
    {
        cout<<"what do you want to make the image \n[1] Lighter \n[2] Darker\n";

        int choice ;
        cin >> choice ;

        if (cin.fail())
        {
            cout << "Invalid input. Please enter an integer.\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        else if (choice == 1){
            brighten(image);
            cout << "Image brightened.\n";
            break;
        }
        else if (choice == 2){
            darken(image);
            cout << "Image darkened.\n";
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

inline Image Flip::flipVertical(Image &image) {
    Image flippedImage(image.width, image.height);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int flippedRow = image.height - 1 - j;
            for (int k = 0; k < image.channels; ++k) {
                flippedImage(i, flippedRow, k) = image(i, j, k);
            }
        }
    }
    return flippedImage;
}

inline Image Flip::flipHorizontal(Image &image) {
    Image flippedImage(image.width, image.height);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int flippedColumn = image.width - 1 - i;
            for (int k = 0; k < image.channels; ++k) {
                flippedImage(flippedColumn, j, k) = image(i, j, k);
            }
        }
    }
    return flippedImage;
}

inline Image Flip::processImage(Image &image) {
    int flip_direction;
    cout << "1. Horizontal\n2. Vertical\n";
    cout << "Choose the Flip Direction: " << endl;
    cin >> flip_direction;

    while (true)
    {
        // Flip horizontally
        if (flip_direction == 1) {
            image = flipHorizontal(image);
            cout << "Image flipped horizontally.\n ";
            break;
        }
        // Flip vertically
         if (flip_direction == 2) {
            image = flipVertical(image);
            cout << "Image flipped vertically.\n ";
            break;

        }
        cout<< "Please enter a valid flip direction\n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> flip_direction ;
    }
    return image;
}

inline string Blur::getFilterName() const {
    return "Blur";
}

inline Image Blur::processImage(Image &image) {
    int kernelSize; // Adjust the kernel size as needed
    cout << "Enter the kernal size (blur intensity) between 1 and 25:\n";
    cin >> kernelSize;

    while (cin.fail() || kernelSize < 0 || kernelSize > 25) {
        cout << "Invalid input. Please input a valid positive integer." << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> kernelSize;
    }

    // Create a temporary image to store the blurred result
    Image blurredImage(image.width, image.height);

    // Calculate half of the kernel size
    int halfKernel = (kernelSize - 1) / 2;

    for (int i = halfKernel; i < image.width - halfKernel; ++i) {
        for (int j = halfKernel; j < image.height - halfKernel; ++j) {
            // Accumulate RGB values for each channel
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;

            // Iterate over the kernel
            for (int kx = -halfKernel; kx <= halfKernel; ++kx) {
                for (int ky = -halfKernel; ky <= halfKernel; ++ky) {
                    sumRed += image(i + kx, j + ky, 0); // Red channel
                    sumGreen += image(i + kx, j + ky, 1); // Green channel
                    sumBlue += image(i + kx, j + ky, 2); // Blue channel
                }
            }

            // Calculate the average RGB values
            int avgRed = sumRed / (kernelSize * kernelSize);
            int avgGreen = sumGreen / (kernelSize * kernelSize);
            int avgBlue = sumBlue / (kernelSize * kernelSize);

            // Set the average values to the corresponding pixel in the blurred image
            blurredImage(i, j, 0) = (avgRed >= 255 ? 255 : avgRed);
            blurredImage (i, j, 1) = (avgGreen >= 255 ? 255 : avgGreen);
            blurredImage (i, j, 2) = (avgBlue >= 255 ? 255 : avgBlue);
        }
    }
    return blurredImage;
}

inline string Rotate::getFilterName() const {
    return "Rotate";
}

inline Image Rotate::rotate90(Image &image) {
    Image rotatedImage(image.height, image.width);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                rotatedImage(image.height - j - 1, i, k) = image(i, j, k);
            }
        }
    }

    return rotatedImage;
}

inline Image Rotate::rotate180(Image &image) {
    Image rotatedImage(image.width, image.height);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                rotatedImage(image.width - i - 1, image.height - j - 1, k) = image(i, j, k);
            }
        }
    }

    return rotatedImage;
}

inline Image Rotate::rotate270(Image &image) {
    Image rotatedImage(image.height, image.width);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                rotatedImage(j, image.width - i - 1, k) = image(i, j, k);
            }
        }
    }

    return rotatedImage;
}

inline Image Rotate::processImage(Image &image) {
    cout << "1. Rotate the image 90 degrees\n";
    cout << "2. Rotate the image 180 degrees\n";
    cout << "3. Rotate the image 270 degrees\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    while (cin.fail() || choice < 1 || choice > 4) {
        cout << "Invalid input. Please enter a valid number: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> choice;
    }

    switch (choice) {
        case 1:
            image = rotate90(image);
            break;
        case 2:
            image = rotate180(image);
            break;
        case 3:
            image = rotate270(image);
            break;
        default:
            cout << "Invalid choice, try again\n";
    }
    return image;
}

inline string Purple::getFilterName() const {
    return "Purple";
}

inline Image Purple::processImage(Image &image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j += 1) {
            image(i, j, 1) *= 0.75;
        }
    }

    return image;
}

inline string Yellow::getFilterName() const {
    return "Yellow";
}

inline Image Yellow::processImage(Image &image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j += 1) {
            for (int k = 0; k < image.channels; k++) {
                image(i, j, 2) *= 0.9;
            }
        }
    }

    return image;
}

inline string Merge::getFilterName() const {
    return "Merge";
}

inline Image Merge::Merge_only(Image &imageA, Image &imageB) {
    Image image1  ;
    Image image2  ;
    // determining which image is the bigger
    if(imageA.width >= imageB.width && imageA.height >= imageB.height){
        image1 = imageB ;
        image2 = imageA ;
    }
    else if(imageA.width <= imageB.width && imageA.height <= imageB.height){
        image1 = imageA ;
        image2 = imageB ;
    }

    Image newimage(image1.width, image1.height);

    for (int i = 0; i < newimage.width; i++) {
        for (int j = 0; j < newimage.height; j += 2) {
            for (int k = 0; k < newimage.channels; k++) {
                newimage(i, j, k) = image2(i, j, k);
                newimage(i, j + 1, k) = image1(i, j, k);
            }
        }
    }

    return newimage;
}

inline Image Merge::mergeAndResize(Image &imageA, Image &imageB) {
    Image image1  ;
    Image image2  ;
    Resize resizer;
    // determining which imager is the bigger
    if(imageA.width >= imageB.width && imageA.height >= imageB.height){
        image1 =imageB ;
        image2 =imageA ;
    }
    else if(imageA.width <= imageB.width && imageA.height <= imageB.height){
        image1 =imageA ;
        image2 =imageB ;
    }
    // Resize the larger image to match the smaller one
    Image resized_image =  resizer.resize(image2, image1.width, image1.height);
    Image newimage(resized_image.width, resized_image.height);

    for (int i = 0; i < newimage.width; i++) {
        for (int j = 0; j < newimage.height; j += 2) {
            for (int k = 0; k < newimage.channels; k++) {
                newimage(i, j, k) = resized_image(i, j, k);
                newimage(i, j + 1, k) = image1(i, j, k);
            }
        }
    }

    return newimage;
}

inline Image Merge::processImage(Image &image) {
    ImageManager mn;
    string name2;
    int choice;
    Image image2 = mn.loadImage(name2);

    cout << "[1]Resize & Merge\n[2]Merge Only\n";
    cout << "Enter your choice: ";
    cin >> choice;

    while (cin.fail() || choice < 1 || choice > 2) {
        cout << "Invalid input. Please enter a valid number: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> choice;
    }

    switch (choice) {
        case 1:
            image = mergeAndResize(image,image2);
            break;
        case 2:
            image = Merge_only(image,image2);
            break;
        default:
            cout << "Invalid choice, try again\n";
    }

    return image;
}

inline string Resize::getFilterName() const {
    return "Resize";
}

inline Image Resize::resize(Image &image, int new_width, int new_height) {
    Image resized_image(new_width, new_height);

    int width_ratio = (image.width << 16) / new_width;
    int height_ratio = (image.height << 16) / new_height;

    for (int y = 0; y < new_height; ++y) {
        for (int x = 0; x < new_width; ++x) {
            int orig_x = (x * width_ratio) >> 16;
            int orig_y = (y * height_ratio) >> 16;

            for (int c = 0; c < image.channels; ++c) {
                resized_image.setPixel(x, y, c, image.getPixel(orig_x, orig_y, c));
            }
        }
    }

    return resized_image;
}

inline Image Resize::processImage(Image &image) {
    int new_width, new_height;
    string output_filename;
    cout << "Enter the new width and height for resizing: ";
    cin >> new_width >> new_height;

    while(cin.fail()) {
        cout << "Invalid input. Please input integers: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> new_width >> new_height;
    }

    return resize(image, new_width, new_height);
}

inline string EdgeDetect::getFilterName() const {
    return "Edge Detect";
}

inline Image EdgeDetect::processImage(Image &image) {
    Image result = image;
    // Iterate over each pixel in the image (excluding border pixels)
    for (int y = 1; y <  image.height - 1; ++y) {
        for (int x = 1; x < image.width - 1; ++x) {
            // Calculate gradients using Sobel operator
            int gradiant_x = (-1 * image(x - 1, y - 1, 0)) + (0 * image(x, y - 1, 0)) + (1 * image(x + 1, y - 1, 0)) +
                     (-2 * image(x - 1, y, 0)) + (0 * image(x, y, 0)) + (2 * image(x + 1, y, 0)) +
                     (-1 * image(x - 1, y + 1, 0)) + (0 * image(x, y + 1, 0)) + (1 * image(x + 1, y + 1, 0));

            int gradiant_y = (-1 * image(x - 1, y - 1, 0)) + (-2 * image(x, y - 1, 0)) + (-1 * image(x + 1, y - 1, 0)) +
                     (0 * image(x - 1, y, 0)) + (0 * image(x, y, 0)) + (0 * image(x + 1, y, 0)) +
                     (1 * image(x - 1, y + 1, 0)) + (2 * image(x, y + 1, 0)) + (1 * image(x + 1, y + 1, 0));


            // Calculate magnitude of gradient
            int magnitude = sqrt(gradiant_x * gradiant_x +  gradiant_y *  gradiant_y);
            for (int k = 0 ;k < 3;k++) {
                // Set pixel value in output image based on magnitude (thresholding)
                if (magnitude > 127) { // Adjust threshold as needed
                    result(x, y, 0) = 0; // Set edge pixel to black
                } else {
                    result(x, y, k) = 255; // Set non-edge pixel to white
                }
            }
        }
    }

    return result;
}

inline string Crop::getFilterName() const {
    return "Crop";
}

inline Image Crop::crop(Image &image, int x, int y, int wdth, int hght) {
    // Create a new image for the cropped region
    Image cropped_image(wdth, hght);

    // Copy pixels from the original image to the cropped image within the specified region
    for (int i = 0; i < wdth; ++i) {
        for (int j = 0; j < hght; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                // Retrieve pixel from original image and set it in the cropped image
                cropped_image.setPixel(i, j, k, image.getPixel(x + i, y + j, k));
            }
        }
    }

    return cropped_image;
}

inline Image Crop::processImage(Image &image) {
    int x, y, width, height;

    // Input coordinates and dimensions for cropping
    cout << "Enter x, y, width, height to crop (x, y are coordinates of upper left corner): ";
    cin >> x >> y >> width >> height;

    while (cin.fail() || !(x >= 0 && y >= 0 && width > 0 && height > 0 &&
            (x + width) <= image.width && (y + height) <= image.height)) {
        // Invalid dimensions message
        cout << "Invalid cropping dimensions. Please ensure the region is within the image bounds: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> x >> y >> width >> height;
    }

   return crop(image,x,y,width,height);
}

inline string addFrame::getFilterName() const {
    return "Add Frame";
}

inline void addFrame::createFrame(Image &framedImage, int newWidth, int newHeight, int red, int green, int blue) {
    for (int i = 0; i < newWidth; i++) {
        for (int j = 0; j < newHeight; j++) {
            framedImage(i, j, 0) = red;
            framedImage(i, j, 1) = green;
            framedImage(i, j, 2) = blue;
        }
    }
}

inline void addFrame::placeImageInMiddle(Image &framedImage, Image &originalImage, int newWidth, int newHeight, int scale) {
    for (int i = scale; i < newWidth - scale; ++i) {
        for (int j = scale; j < newHeight - scale; ++j) {
            for (int k = 0; k < originalImage.channels; ++k) {
                framedImage(i, j, k) = originalImage(i - scale, j - scale, k);
            }
        }
    }
}

inline void addFrame::insideFrame(Image &image, int scale, int red, int green, int blue) {
for(int i = scale; i < image.width - scale ; ++i){
        for (int j = scale ; j < scale + scale / 4 ; ++j){
            image(i,j,0)= red;
            image(i,j,1)= green;
            image(i,j,2)= blue;
        }
    }
    for(int i = scale ; i < image.width - scale ; ++i){
        for (int j=image.height - scale ; j >= image.height - (scale + scale / 4) ;--j){
            image(i,j,0)= red;
            image(i,j,1)= green;
            image(i,j,2)= blue;
        }
    }
    for(int i= scale; i < scale + scale/4 ;++i){
        for (int j = scale ; j < image.height- scale ;++j){
            image(i,j,0)= red;
            image(i,j,1)= green;
            image(i,j,2)= blue;
        }
    }
    for(int i=image.width-scale ; i >= image.width - (scale + scale/4) ; --i){
        for (int j= scale ; j < image.height-scale ; ++j){
            image(i,j,0)= red;
            image(i,j,1)= green;
            image(i,j,2)= blue;
        }
    }

    for(int i = scale + scale/4 + scale/2 ; i < image.width - (scale + scale/4 + scale/2) ; ++i){
        for (int j = scale + scale/4 + scale/2; j < 2 * scale  ;++j){
            image(i,j,0)= red;
            image(i,j,1)= green;
            image(i,j,2)= blue;
        }
    }
    for(int i = scale + scale/4 + scale/2 ; i < image.width - (scale + scale/4 + scale/2) ; ++i){
        for (int j = image.height - (scale + scale/4 + scale/2); j >= image.height - 2*scale ;--j){
            image(i,j,0)= red;
            image(i,j,1)= green;
            image(i,j,2)= blue;
        }
    }
    for(int i = scale + scale/4 + scale/2 ; i < 2*scale ; ++i){
        for (int j = scale + scale/4 + scale/2; j < image.height - (scale + scale/4 + scale/2) ; ++j){
            image(i,j,0)= red;
            image(i,j,1)= green;
            image(i,j,2)= blue;
        }
    }
    for(int i=image.width - (scale + scale/4 + scale/2) ; i >= image.width - 2*scale ; --i){
        for (int j = scale + scale/4 + scale/2; j < image.height - (scale + scale/4 + scale/2) ; ++j){
            image(i,j,0)= red;
            image(i,j,1)= green;
            image(i,j,2)= blue;
        }
    }
}

inline Image addFrame::processImage(Image &image) {
    int maxDimension = max(image.width, image.height);
    int scale = maxDimension / 40; // Adjust 40 to change the thickness of the frame


    // Calculate new dimensions for the framed image
    int newWidth = image.width + 2 * scale; // Add frame width on both sides
    int newHeight = image.height + 2 * scale; // Add frame height on both sides

    int Red, Green, Blue;
    int choice;

    // Create a new image for the framed image
    Image framedImage(newWidth, newHeight);

    // Loop until a valid choice is made
    while (true) {
        // Menu for choosing frame color
        cout << "Choose frame color:" << endl;
        cout << "1. Red" << endl;
        cout << "2. Green" << endl;
        cout << "3. Blue" << endl;
        cout << "4. Gray" << endl;
        cout << "5. Yellow" << endl;
        cout << "6. Another colour" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        // Create frame based on user's choice
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            switch (choice) {
                case 1:
                    createFrame(framedImage, newWidth, newHeight, 255, 0, 0); // Red frame
                    break;
                case 2:
                    createFrame(framedImage, newWidth, newHeight, 0, 255, 0); // Green frame
                    break;
                case 3:
                    createFrame(framedImage, newWidth, newHeight, 0, 0, 255); // Blue frame
                    break;
                case 4:
                    createFrame(framedImage, newWidth, newHeight, 128, 128, 128); // Gray frame
                    break;
                case 5:
                    createFrame(framedImage, newWidth, newHeight, 255, 255, 0); // Yellow frame
                    break;
                case 6:
                    cout << "Enter RGB values separated by spaces:" << endl;
                    cin >> Red >> Green >> Blue;
                    createFrame(framedImage, newWidth, newHeight, Red, Green, Blue); // Custom frame
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
                    continue; // Continue the loop to prompt the user again
            }
            break; // Break out of the loop if a valid choice is made
        }
    }

    // Place the original image in the middle
    placeImageInMiddle(framedImage, image, newWidth, newHeight, scale);

    while (true){
        char yn;
        cout << "Do you want a fancy frame? (an insider one) (Y/N) \n";
        cin >> yn;

        if ( tolower(yn) != 'y' && tolower(yn) != 'n' )
        {
            cout << "Invalid input. Please enter a character.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        else if (tolower(yn) == 'y')
        {
            while (true) {
                // Menu for choosing frame color
                cout << "Choose frame color:" << endl;
                cout << "1. Red" << endl;
                cout << "2. Green" << endl;
                cout << "3. Blue" << endl;
                cout << "4. Gray" << endl;
                cout << "5. Yellow" << endl;
                cout << "6. Another colour" << endl;

                cout << "Enter your choice: ";
                cin >> choice;

                // Create frame based on user's choice
                if (cin.fail()) {
                    cout << "Invalid input. Please enter a number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else {
                    switch (choice) {
                        case 1:
                            insideFrame(framedImage, scale, 255, 0, 0); // Red frame
                            break;
                        case 2:
                            insideFrame(framedImage, scale, 0, 255, 0); // Green frame
                            break;
                        case 3:
                            insideFrame(framedImage, scale, 0, 0, 255); // Blue frame
                            break;
                        case 4:
                            insideFrame(framedImage, scale, 128, 128, 128); // Gray frame
                            break;
                        case 5:
                            insideFrame(framedImage, scale, 255, 255, 0); // Yellow frame
                            break;
                        case 6:
                            cout << "Enter RGB values separated by spaces:" << endl;
                            cin >> Red >> Green >> Blue;
                            insideFrame(framedImage, scale, Red, Green, Blue); // Custom frame
                            break;
                        default:
                            cout << "Invalid choice. Try again." << endl;
                            continue; // Continue the loop to prompt the user again
                    }

                    break; // Break out of the loop if a valid choice is made
                }

            }
            break;
        }
        else if (tolower(yn == 'n')){
            break;
        }
    }

    return framedImage;
}








#endif //IMAGEPROCESSOR_H
