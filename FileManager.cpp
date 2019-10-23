#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <string>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <dirent.h>

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

    vector<FileManager *> children;

    struct stat results;
    struct passwd *pwd;
    struct group *g;

public:
    FileManager(const string &fileName) {

        if (stat(fileName.c_str(), &results) == 0) {

            name = fileName;

            type = results.st_mode;
            if ((results.st_mode & S_IFMT) == S_IFREG) { //check if type is regular and set typeString accordingly
                typeString = "regular";
            } else if ((results.st_mode & S_IFMT) == S_IFSOCK) { //socket
                typeString = "socket";
            } else if ((results.st_mode & S_IFMT) == S_IFLNK) { //symbolic
                typeString = "symbolic";
            } else if ((results.st_mode & S_IFMT) == S_IFBLK) { //block
                typeString = "block";
            } else if ((results.st_mode & S_IFMT) == S_IFDIR) { //directory
                typeString = "directory";
            } else if ((results.st_mode & S_IFMT) == S_IFCHR) { //character
                typeString = "character";
            } else if ((results.st_mode & S_IFMT) == S_IFIFO) { //fifo
                typeString = "FIFO";

            }

            size = results.st_size;

            ownerID = results.st_uid;
            pwd = getpwuid(ownerID);
            ownerName = pwd->pw_name;

            groupID = results.st_gid;
            g = getgrgid(groupID);
            groupName = g->gr_name;


            if (results.st_mode & S_IRUSR) { //check read permissions
                permString.append("r");
            }
            if (results.st_mode & S_IWUSR) { //check write permissions
                permString.append("w");
            }
            if (results.st_mode & S_IXUSR) { //check execute permissions
                permString.append("x");
            }


            accessTime = results.st_atime;
            modTime = results.st_mtime;
            statusChangeTime = results.st_ctime;


            blockSize = results.st_blksize;
        } else {
            name = "failed";
        }
    }

    ~FileManager() = default; //deconstructor

    int dump(fstream &inFile, string newName) {
        if (stat(name.c_str(), &results) == 0) {  //check if file exists
            if (typeString == "regular") { //check if regular file
                inFile.open(name); //open filestream
                ofstream outFile; //create outfile stream
                outFile.open(newName);
                char *buffer = new char[size]; //create buffer with specified size
                inFile.read(buffer, size); //read
                cout << "WRITING\n";
                outFile.write(buffer, size); //write to buffer
                inFile.close(); //close file streams
                outFile.close();

                errNum = errno; //set error number
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
        if (stat(name.c_str(), &results) == 0) { //check if file exists
            result = rename(name.c_str(), newName.c_str()); //call rename on specified file
            name = newName; //set new name as name
            errNum = result;
            return 0;
        }

        cout << "file does not exist!\n";
        return errNum;
    }

    int myRemove(string fileName) {
        if ((unlink(fileName.c_str()) == 0)) { //remove file. check if successful
            errNum = errno; //set error number
            delete this; //delete object
            return 0;
        }
        errNum = errno;
        return -1;

    }

    int myCompare(FileManager *object) {
        if (typeString == "regular") { //check regular file
            if (object->getSize() == size) {
                int i;
                i = 0;
                fstream file1; //create fstreams
                fstream file2;

                file1.open(object->getName()); //open fstreams
                file2.open(name);

                char fileArray1[object->getSize()]; //create char arrays to old chars
                char fileArray2[size];

                while (!file1.eof()) { //iterate through file and compare each character
                    file1.getline(fileArray1, size);
                    file2.getline(fileArray2, size);
                    i++;
                    if (strcmp(fileArray1, fileArray2) !=
                        0) {
                        cout << "FILES NOT EQUAL!\n";
                        return errNum = -1;
                    }
                    cout << "FILES ARE EQUAL!\n";
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
            DIR *currDir;
            dirent *entry;
            FileManager *file;
            currDir = opendir(name.c_str());
            while ((entry = readdir(currDir)) != NULL) {
                if (strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0) {
                } else {
                    file = new FileManager(name + "/" + entry->d_name);
                    children.push_back(file);
                    file->myExpand();
                }
            }
            errNum = errno;
            closedir(currDir);
            return 0;
        } else {
            errNum = ENOTSUP;
            return -1;
        }
    }


    string getName() {
        return name;
    }

    string getType() {
        return typeString;
    }

    mode_t getTypeID() {
        return type;
    }

    off_t getSize() {
        return size;
    }


    char *getOwnerName() {
        return ownerName;
    }

    uid_t getOwnerID() {
        return ownerID;
    }

    string getGroupName() {
        return groupName;
    }

    gid_t getGroupID() {
        return groupID;
    }

    string getPermissions() {
        return permString;
    }

    char *getAccessTime() {
        return ctime(reinterpret_cast<const time_t *>(&results.st_atim));
    }

    char *getModTime() {
        return ctime(reinterpret_cast<const time_t *>(&results.st_mtim));
    }

    char *getStatChangeTime() {
        return ctime(reinterpret_cast<const time_t *>(&results.st_ctim));
    }

    blksize_t getBlckSize() {
        return blockSize;
    }

    vector<FileManager *> getChildren() {
        return children;

    }
};

