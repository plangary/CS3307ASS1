//
// Created by pouya on 2019-10-03.
//

#include "FileManager.cpp"
class mycat{


};

int main(int argc, char* argv[]){

    struct stat results;

    string temp; //temporary string holder
        int i; //while loop counter
        i = 1;
        while (i < argc) { //loop through each argument
            temp = argv[i];
            if(stat(temp.c_str(), &results)==0) { //check if file exists
                ifstream file; //create file stream
                file.open(argv[i]); //open file
                cout << file.rdbuf() << "\n"; //output contents
            }
            else{
                cout<<"No Such File or Directory!\n";
            }
            i++;
            //FileManager *object = new FileManager(argv[i]);
        }
        return 0;
}
