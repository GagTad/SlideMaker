#include <iostream>
#include "Editor.h"

int main(int argc, char* argv[]) {
    Editor editor;
    if (argc >= 2) {
        // File Mode
        std::string inputPath = argv[1];
        editor.run(inputPath);
    }
    else {
        editor.runInteractive();
    }
    return 0;
}
