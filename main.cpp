#include "ImageProcessor.h"
#include "UserUI.h"

int main () {
    ImageProcessor *processor;
    UserUI ui(processor);
    string name ,outputName;
    bool running = true;
    int choice ;

    cout << "Welcome to Mini Photoshop!\n";
    Image image = ui.loadImage(name);
    Image result = image;

    while (running) {
        ui.mainMenu();
        cin >> choice;

        while (cin.fail() || choice < 0 || choice > 17) {
            cout << "Invalid input. Please enter a valid number.\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }

        ui.setImageName(outputName);

        switch (choice) {
            case 1:
                processor = new GrayScale();
                break;
            case 2:
                processor = new BlackWhite();
                break;
            case 3:
                processor = new InfraRed();
                break;
            case 17:
                cout << "Exitting... Thank you for Using Mini Photoshop!";
                running = false;
                break;
            default:
                cout << "Invalid Choice. Try Again.";
        }

        result = processor->processImage(result, outputName);
        cout << "Image Processed Successfully By Filter " << processor->getFilterName() << endl;
        result.saveImage(outputName);
        system(outputName.c_str());
    }

    return 0;
}
