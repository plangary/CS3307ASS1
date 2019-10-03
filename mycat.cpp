//
// Created by pouya on 2019-10-03.
//

#include "FileManager.cpp"
class mycat{


};

int main(int argc, char* argv[]){

    struct stat results;

    string temp;
        int i;
        i = 1;
        while (i < argc) {
            temp = argv[i];
            if(stat(temp.c_str(), &results)==0) {
                ifstream file;
                file.open(argv[i]);
                cout << file.rdbuf() << "\n";
            }
            else{
                cout<<"No Such File or Directory!\n";
            }
            i++;
            //FileManager *object = new FileManager(argv[i]);
        }
        return 0;
}
