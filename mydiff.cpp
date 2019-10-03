//
// Created by pouya on 2019-10-03.
//


#include "FileManager.cpp"

class mydiff{

};

int main(int argc, char* argv[]){
    if(argc==3){
        FileManager *object = new FileManager(argv[1]);
        FileManager *object2 = new FileManager(argv[2]);
        object->myCompare(object2);

        return 0;
    }
    cout<<"Incorrect number of arguments. Provide 2 arguments only!\n Format: oldFile newFile\n";

    return -1;
}
