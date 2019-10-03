//
// Created by pouya on 2019-10-03.
//

#include "FileManager.cpp"

class myrm{

};

int main(int argc, char* argv[]){
    struct stat results;

    string temp;
    int i;
    i = 1;
    while (i < argc) {
        temp = argv[i];
        if(stat(temp.c_str(), &results)==0) {
            FileManager *object = new FileManager(argv[i]);
            object->myRemove(argv[i]);
        }
        else{
            cout<<"No Such File or Directory!\n";
        }
        i++;
    }
    return 0;
}

