//
// Created by pouya on 2019-10-03.
//
#include "FileManager.cpp"
#include "mycp.h"
class mycp{


};

int main(int argc, char* argv[]){
    if(argc==3){
        FileManager *object = new FileManager(argv[1]);
        object->myRename(argv[2]);
        return 0;
    }
    cout<<"Incorrect number of arguments. Provide 2 arguments only!\n Format: oldFile newFile\n";

    return -1;
}
