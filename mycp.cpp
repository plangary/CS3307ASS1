//
// Created by pouya on 2019-10-03.
//
#include "FileManager.cpp"

class mycp {


};

int main(int argc, char *argv[]) {
    if (argc == 3) { //check if correct number of arguments are provided
        FileManager *object = new FileManager(argv[1]); //create filemanager object
        fstream output; //create file stream
        object->dump(output, argv[2]); //call dump method on object using fstream

        return 0;
    }
    cout << "Incorrect number of arguments. Provide 2 arguments only!\n Format: oldFile newFile\n";

    return -1;
}
