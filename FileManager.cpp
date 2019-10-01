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
    string typeString;
    off_t size;

    uid_t ownerID;
    char *ownerName; //use getpwuid() function

    gid_t groupID;
    string groupName;

    mode_t permissions;
    string permString;

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
                typeString = "regular";
                  }
            else if  ((results.st_mode & S_IFMT) == S_IFSOCK){
                typeString = "socket";
            }
            else if ((results.st_mode & S_IFMT) == S_IFLNK){
                typeString = "symbolic";
            }
            else if ((results.st_mode & S_IFMT) == S_IFBLK){
                typeString = "block";
            }
            else if ((results.st_mode & S_IFMT) == S_IFDIR){
                typeString = "directory";
            }
            else if ((results.st_mode & S_IFMT) == S_IFCHR){
                typeString = "character";
            }
            else if  ((results.st_mode & S_IFMT) == S_IFIFO){
                typeString = "FIFO";

            }

            cout<<typeString;
            size = results.st_size;


            ownerID = results.st_uid;
            pwd = getpwuid(ownerID);
            ownerName = pwd->pw_name;

            groupID = results.st_gid;
            g = getgrgid(groupID);
            groupName = g->gr_name;



            if (results.st_mode & S_IRUSR){
                permString.append("r") ;
            }
            if (results.st_mode & S_IWUSR){
                permString.append("w");
            }
            if (results.st_mode & S_IXUSR){
                permString.append("x");
            }



            blockSize = results.st_blksize;


        }
    }




};
int main() {

    FileManager *test = new FileManager("text.txt");


    return 0;
}