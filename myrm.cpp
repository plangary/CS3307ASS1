//
// Created by pouya on 2019-10-03.
//

#include "FileManager.cpp"

class myrm {

};

int main(int argc, char *argv[]) {
    struct stat results;

    string temp; //temporary string
    int i; //while loop counter
    i = 1;
    while (i < argc) { //loop each argument
        temp = argv[i];
        if (stat(temp.c_str(), &results) == 0) { //check if file exists
            FileManager *object = new FileManager(argv[i]); //create filemanger object
            object->myRemove(argv[i]); //call remove method on file
        } else {
            cout << "No Such File or Directory!\n";
        }
        i++;
    }
    return 0;
}

