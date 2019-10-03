//
// Created by pouya on 2019-10-03.
//
#include "FileManager.cpp"


class mystat{


};

int main(int argc, char* argv[]){
    if(argc==2){
        FileManager *object = new FileManager(argv[1]);
        cout<<"Name:\t"<<object->getName()<<"\n";
        cout<<"File Type:\t"<<object->getType()<<"\n";
        cout<<"File Type ID:\t"<<object->getTypeID()<<"\n";
        cout<<"File Size:\t"<<object->getSize()<<"\n";
        cout<<"Block Size:\t"<<object->getBlckSize()<<"\n";
        cout<<"Owner ID:\t"<<object->getOwnerID()<<"\n";
        cout<<"Owner Name:\t"<<object->getOwnerName()<<"\n";
        cout<<"Group ID:\t"<<object->getGroupID()<<"\n";
        cout<<"Group Name:\t"<<object->getGroupName()<<"\n";
        cout<<"Permission:\t"<<object->getPermissions()<<"\n";
        cout<<"Acess Time:\t"<<object->getAccessTime()<<"\n";
        cout<<"Modification Time Time:\t"<<object->getModTime()<<"\n";
        cout<<"Status Change Time:\t"<<object->getStatChangeTime()<<"\n";






        return 0;
    }
    cout<<"Incorrect number of arguments. Provide 1 argument only!\n Format: fileName\n";

    return -1;
}
