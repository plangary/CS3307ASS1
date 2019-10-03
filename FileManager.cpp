#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <string>
#include <map>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include <cstring>

using namespace std;

class FileManager {

private:
    string name;
    mode_t type;
    string typeString;
    off_t size;

    int errNum = 0;
    uid_t ownerID;
    char *ownerName; //use getpwuid() function

    gid_t groupID;
    string groupName;

    mode_t permissions;
    string permString;

    time_t accessTime;
    time_t modTime, statusChangeTime;
    blksize_t blockSize;

    vector<int> children;

    struct stat results;
    struct passwd *pwd;
    struct group *g;

public:
    FileManager(const string &fileName) {

        if (stat(fileName.c_str(), &results) == 0) {

            name = fileName;

            type = results.st_mode;
            if ((results.st_mode & S_IFMT) == S_IFREG) {
                typeString = "regular";
            } else if ((results.st_mode & S_IFMT) == S_IFSOCK) {
                typeString = "socket";
            } else if ((results.st_mode & S_IFMT) == S_IFLNK) {
                typeString = "symbolic";
            } else if ((results.st_mode & S_IFMT) == S_IFBLK) {
                typeString = "block";
            } else if ((results.st_mode & S_IFMT) == S_IFDIR) {
                typeString = "directory";
            } else if ((results.st_mode & S_IFMT) == S_IFCHR) {
                typeString = "character";
            } else if ((results.st_mode & S_IFMT) == S_IFIFO) {
                typeString = "FIFO";

            }

            size = results.st_size;

            ownerID = results.st_uid;
            pwd = getpwuid(ownerID);
            ownerName = pwd->pw_name;

            groupID = results.st_gid;
            g = getgrgid(groupID);
            groupName = g->gr_name;


            if (results.st_mode & S_IRUSR) {
                permString.append("r");
            }
            if (results.st_mode & S_IWUSR) {
                permString.append("w");
            }
            if (results.st_mode & S_IXUSR) {
                permString.append("x");
            }


            accessTime = results.st_atime;
            modTime = results.st_mtime;
            statusChangeTime = results.st_ctime;

            //accessTime = ctime(reinterpret_cast<const time_t *>(&results.st_atim));
            //modTime = ctime(reinterpret_cast<const time_t *>(&results.st_mtim));
            //statusChangeTime = ctime(reinterpret_cast<const time_t *>(&results.st_ctim));


            blockSize = results.st_blksize;
        } else {
            name = "failed";
        }
    }

    ~FileManager() = default;

    int dump(fstream &inFile,string newName) {
        if(stat(name.c_str(), &results)==0){ //works for files and directories but doesnt when given path that ends in directory
        if (typeString == "regular") {
            inFile.open(name);
            ofstream outFile;
            outFile.open(newName);
            char *buffer = new char[size];
            inFile.read(buffer, size);
            cout << "WRITING\n";
            outFile.write(buffer, size);
            inFile.close();
            outFile.close();

            errNum = errno;
            return 0;
        }
        } else {
            cout << "IRREGULAR FILE OR FILE DOES NOT EXIST!\n";
            errNum = ENOTSUP;
            return ENOTSUP;
        }


    }

    int myRename(string newName) {
        int result;
        if(stat(name.c_str(),&results)==0) {
            result = rename(name.c_str(), newName.c_str());
            name = newName;
            errNum = result;
            return 0;
        }

        cout<<"file does not exist!\n";
        return errNum;
    }

    int myRemove(string fileName) {
        if ((unlink(fileName.c_str()) == 0)) {
            errNum = errno;
            delete this;
            return 0;
        }
        errNum = errno;
        return -1;

    }

    int myCompare(FileManager *object) {
        if (typeString == "regular") {
            if (object->getSize() == size) {
                int i;
                i = 0;
                fstream file1;
                fstream file2;

                file1.open(object->getName());
                file2.open(name);

                char fileArray1[object->getSize()];
                char fileArray2[size];

                while (!file1.eof()) {
                    file1.getline(fileArray1, size);
                    file2.getline(fileArray2, size);
                    i++;
                    if (strcmp(fileArray1, fileArray2) !=
                        0) { //not fully working. doesnt work when same amount of characters but different chars
                        cout << "FILES NOT EQUAL!\n";
                        return errNum = -1;
                    }
                    cout << "FILES ARE EQUAL!222\n";
                    return errNum = 0;
                }
            } else {
                cout << "FILES NOT EQUAL!\n";
                return -1;
            }

        } else {
            cout << "IRREGULAR FILE!";
            errNum = ENOTSUP;
            return errNum;
        }


    }

    int myExpand() {
        if (typeString == "directory") {

        }

        errNum = ENOTSUP;
        return -1;
    }


    string getName() {
        return name;
    }

    string getType() {
        return typeString;
    }

    mode_t getTypeID(){
        return type;
    }

    off_t getSize() {
        return size;
    }


    char *getOwnerName() {
        return ownerName;
    }

    uid_t getOwnerID(){
        return ownerID;
    }

    string getGroupName() {
        return groupName;
    }

    gid_t getGroupID(){
        return groupID;
    }

    string getPermissions() {
        return permString;
    }

    time_t getAccessTime() {
        return accessTime;
    }

    time_t getModTime() {
        return modTime;
    }

    time_t getStatChangeTime() {
        return statusChangeTime;
    }

    blksize_t getBlckSize() {
        return blockSize;
    }

};

/*int main() {

    FileManager *test = new FileManager("newFile");
    //FileManager *test2 = new FileManager("new");
    //test->myCompare(test2);

    test->myRename("/media/sf_VMSgaring/CS3307ASS1/dir/test");
    //test->myRemove("test");
    //cout<<test->getName();
    //fstream test2;
    //test->dump(test2);



    return 0;
}*/