/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

   * File Name : BridgePattern.cpp

   * Purpose :

   * Creation Date : 11-01-2015

   * Last Modified : Mon, Jan 12, 2015  9:20:39 AM

   * Created By : Atul_Das

   * Bridge between implementation and interfaces
   _._._._._._._._._._._._._._._._._._._._._.*/
#include <stdio.h>
#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;

class FileInfoImp             {
    public:
         virtual              ~FileInfoImp () {}
         virtual int          getSize ()       = 0;
         virtual string       getName ()       = 0;
         virtual int          getPermission () = 0;
};

class UnixFileInfoImp : public FileInfoImp {
         virtual int getSize () {
             printf ("return size for Unix file\n");
             return 1;
         }

         virtual string getName () {
             printf ("return name for Unix file\n");
             return "Unix file Name";
         }

         virtual int getPermission () {
             printf ("return permission for Unix file\n");
             return 1;
         }
};

class WinFileInfoImp : public FileInfoImp {
         virtual int getSize () {
             printf ("return size for Win file\n");
             return 1;
         }

         virtual string getName () {
             printf ("return name for Win file\n");
             return "Unix file Name";
         }

         virtual int getPermission () {
             printf ("return permission for Win file\n");
             return 1;
         }
};

class File {
    public:

         virtual int    getSize ()       { return _fileInfoImp->getSize (); }
         virtual string getName ()       { return _fileInfoImp->getName (); }
         virtual int    getPermission () { return _fileInfoImp->getPermission (); }

    protected:
        FileInfoImp * _fileInfoImp;
};


class UnixFile : public File {
    public:
    UnixFile () {
        _fileInfoImp = new UnixFileInfoImp ();
    }

    ~UnixFile () {
        delete _fileInfoImp;
    }

    private:
        int _inode;
};

class WinFile : public File {
    public:
    WinFile () {
        _fileInfoImp = new WinFileInfoImp ();
    }

    ~WinFile () {
        delete _fileInfoImp;
    }

    private:
        int _fileHandle;
};

int main () {

    vector<File *> filevector;

    filevector.push_back (new UnixFile ());
    filevector.push_back (new UnixFile ());
    filevector.push_back (new UnixFile ());


    filevector.push_back (new WinFile ());
    filevector.push_back (new WinFile ());
    filevector.push_back (new WinFile ());

    for (vector<File *>::iterator it = filevector.begin (); it != filevector.end (); it++ ) {
        (*it)->getName ();
        (*it)->getSize ();
        (*it)->getPermission ();
    }

    // free the memorymory allocated during insertion
    while (!filevector.empty ()) {
        File * temp = filevector.back ();
        delete temp;
        filevector.pop_back ();
    }

    printf ("%d size of vector\n", static_cast<int> (filevector.size ()));
    return 0;
}


