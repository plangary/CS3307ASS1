//
// Created by pouya on 2019-10-02.
//

#include "FileManager.cpp"

class mymv {

};

int main(int argc, char *argv[]) {
    if (argc == 3) { //check if correct number of arguments are provided
        FileManager *object = new FileManager(argv[1]); //create file manager object
        object->myRename(argv[2]); //call rename method on object
        return 0;
    }
    cout << "Incorrect number of arguments. Provide 2 arguments only!\n Format: oldFile newFile\n";

    return -1;
}
