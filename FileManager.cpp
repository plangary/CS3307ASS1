#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <string>
#include <map>
using namespace std;

class FileManager {

public:
    string name;
    mode_t type;
    int errorNum;
    off_t size;
    blksize_t blockSize;
    string statChangeTime, accessTime,modificationTime;
    map<string,int> owner;
    map<string,int> group;
    string permissions;
    vector<int> children;
    struct stat results;

    FileManager(const string& fileName) {

        if(stat(fileName.c_str(), &results)==0) {
            cout<<"File exists";
            name = fileName;
            blockSize = results.st_blksize;
            size = results.st_size;
            type = results.st_mode;




        }
    }



     int main() {

        FileManager *test = new FileManager("");
        cout << test->size;
        cout<<"\nTEST";


        return 0;
    }
};