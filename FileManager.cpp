#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <string>
#include <map>
#include <errno.h>
#include <pwd.h>
#include <grp.h>

using namespace std;

class FileManager {

public:
    string name;
    mode_t type;
    off_t size;

    uid_t ownerID;
    char *ownerName; //use getpwuid() function

    gid_t groupID;
    string groupName;

    mode_t permissions;
    time_t accessTime, modTime, statusChangeTime;
    blksize_t blockSize;

    vector<int> children;

    struct stat results;
    struct passwd *pwd;
    struct group *g;
    FileManager(const string& fileName) {

        if(stat(fileName.c_str(), &results)==0) {

            cout<<"File exists\n";
            name = fileName;
            type = results.st_mode;
            if ((results.st_mode & S_IFMT) == S_IFREG){
                cout<<"TRUE";
            }
            cout<<type;
            size = results.st_size;


            ownerID = results.st_uid;
            pwd = getpwuid(ownerID);
            ownerName = pwd->pw_name;

            groupID = results.st_gid;
            g = getgrgid(groupID);
            groupName = g->gr_name;



            blockSize = results.st_blksize;

        }
    }




};
int main() {

    FileManager *test = new FileManager("text.txt");


    return 0;
}