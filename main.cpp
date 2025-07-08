#include "ImageProcessor.h"
#include "UserUI.h"

int main () {
    ImageProcessor *processor = nullptr;
    UserUI ui;
    ImageManager mn(&processor);
    string name ,outputName;
    bool running = true;
    int choice ;

    cout << "Welcome to Mini Photoshop!\n";
    Image image = mn.loadImage(name);

    while (running) {
        Image result = image;
        ui.mainMenu();
        cin >> choice;

        while (cin.fail() || choice < 0 || choice > 17) {
            cout << "Invalid input. Please enter a valid number.\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }

        switch (choice) {
            case 1:
                ui.setImageName(outputName);
                processor = new GrayScale();
                mn.saveImg(result, outputName);
                break;
            case 2:
                ui.setImageName(outputName);
                processor = new BlackWhite();
                mn.saveImg(result, outputName);
                break;
            case 3:
                ui.setImageName(outputName);
                processor = new InfraRed();
                mn.saveImg(result, outputName);
                break;
            case 4:
                ui.setImageName(outputName);
                processor = new Brightness();
                mn.saveImg(result, outputName);
                break;
            case 5:
                ui.setImageName(outputName);
                processor = new Flip();
                mn.saveImg(result, outputName);
                break;
            case 6:
                ui.setImageName(outputName);
                processor = new Invert();
                mn.saveImg(result, outputName);
                break;
            case 7:
                ui.setImageName(outputName);
                processor = new Merge();
                mn.saveImg(result, outputName);
                break;
            case 8:
                ui.setImageName(outputName);
                processor = new Rotate();
                mn.saveImg(result, outputName);
                break;
            case 9:
                ui.setImageName(outputName);
                processor = new Crop();
                mn.saveImg(result, outputName);
                break;
            case 10:
                ui.setImageName(outputName);
                processor = new addFrame();
                mn.saveImg(result, outputName);
                break;
            case 11:
                ui.setImageName(outputName);
                processor = new EdgeDetect();
                mn.saveImg(result, outputName);
                break;
            case 12:
                ui.setImageName(outputName);
                processor = new Resize();
                mn.saveImg(result, outputName);
                break;
            case 13:
                ui.setImageName(outputName);
                processor = new Blur();
                mn.saveImg(result, outputName);
                break;
            case 14:
                ui.setImageName(outputName);
                processor = new Yellow();
                mn.saveImg(result, outputName);
                break;
            case 15:
                ui.setImageName(outputName);
                processor = new Purple();
                mn.saveImg(result, outputName);
                break;
            case 16:
                image = mn.loadImage(name);
                break;
            case 17:
                cout << "Exitting... Thank you for Using Mini Photoshop!";
                running = false;
                break;
            default:
                cout << "Invalid Choice. Try Again.";
        }

    }
    return 0;
}
