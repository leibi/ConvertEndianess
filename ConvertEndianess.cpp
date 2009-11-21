#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

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


int main (int argc, char**argv)
{

	enum tType
	{
        eUndefined =0,
        eInt,
        eShort,
        eLongLong
	};


        ifstream stream;
        ofstream oStream;
        unsigned int ch =0;
        string filename;
        string outfilename;
        string Type = "int";

        //first parameter is the file to read
        if(2<=argc)
        {
         filename = argv[1];
        }
        if(3<=argc)
        {
         outfilename = argv[2];
        }
        if(4<=argc)
        {
         Type = argv[3];
        }

        enum tType MyType = eUndefined;
        if(0 == Type.compare("int"))
           MyType = eInt;
        else if(0 == Type.compare("short"))
           MyType = eShort;
        else if(0 == Type.compare("long"))
           MyType = eLongLong;

        if(eUndefined == MyType)
        {
                cout << "Could not determine correct type out of " << Type << endl;
                return 3;
        }

        stream.open(filename.c_str(), ios_base::binary);
        oStream.open(outfilename.c_str(), ios_base::binary);
        
        if (stream.bad())
        {
         cout << "Kann Datei " << filename << " nicht öffnen" << endl;
         return 1;
        }
        if (oStream.bad())
        {
         cout << "Kann Datei " << outfilename << " nicht öffnen" << endl;
         return 2;
        }

        

        cout << endl << "Converting byte order from File " << filename << " and writing it to " << outfilename << " using type "<<  Type << endl;

        unsigned int newChUi  = 0;
        unsigned short newChUs  = 0;
        unsigned long long newChUll  = 0;




        while(stream.good())
        {
                ch = stream.get();
                //convert to big/little endian
                //newCh= change_endian(ch);
                switch(MyType)
                {
                  case eInt: newChUi = swapByteOrder(ch); oStream << newChUi;break;
                  case eShort: newChUs = swapByteOrder(ch); oStream << newChUs;break;
                  case eLongLong: newChUll = swapByteOrder(ch); oStream << newChUll;break;
                  default: cout << "Unknown Type Enum: " << MyType << endl;
                }
        }

        cout << endl;

        return 0;
}




