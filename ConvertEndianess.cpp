#include <cstdio>
//#include <conio>
#include <iostream>
#include <fstream>

using namespace std;

unsigned short swapByteOrder(const unsigned short& us)
{
    return (us >> 8) |
    (us << 8);
}

unsigned int swapByteOrder(const unsigned int& ui)
{
    return (ui >> 24) |
    ((ui<<8) && 0x00FF0000) |
    ((ui>>8) && 0x0000FF00) |
    (ui << 24);
}

unsigned long long swapByteOrder(const unsigned long long& ull)
{
    return (ull >> 56) |
    ((ull<<40) && 0x00FF000000000000) |
    ((ull<<24) && 0x0000FF0000000000) |
    ((ull<<8) &&  0x000000FF00000000) |
    ((ull>>8) &&  0x00000000FF000000) |
    ((ull>>24) && 0x0000000000FF0000) |
    ((ull>>40) && 0x000000000000FF00) |
    (ull <<56);
    }
    
unsigned int change_endian(unsigned int x)
{
    unsigned char *ptr = (unsigned char *)&x;
    return (ptr[0] << 24) | (ptr[1] << 16) | (ptr[2] << 8) | ptr[3];
}

main (int argc, char**argv)
{

        ifstream stream;
        unsigned int ch =0;
        string filename;

        //first parameter is the file to read
        if(2<=argc)
        {
         filename = argv[1];
        }

        stream.open(filename.c_str(), ios_base::binary);


        if (stream.bad())
        {
         cout << "Kann Datei nicht öffnen" << endl;
        }
        unsigned int newCh  = 0;
        while(stream.good())
        {
                ch = stream.get();
                //convert to big/little endian
                newCh= change_endian(ch);
                cout << newCh;
        }

        cout << endl;

        return 0;
}




