#include <iostream>
#include "encryption.h"
#include <iterator>
#include <vector>

class verify : EncryptDecrypt
{
    private:
        std::vector<int> ItoVerify;
        std::vector<std::vector<int>> vItems = startDecryption();
    
    private:
        bool isVerified();
        void setItoVerify(const int[]);
};

void verify::setItoVerify(const int newInput[])
{
    for(int i=0; i<proxykeyLength; i++)
    {
        ItoVerify.push_back(newInput[i]);
    }
}

bool verify::isVerified()
{
    bool verified;

    std::vector< std::vector<int> >::iterator row; 
    std::vector<int>::iterator col; 
    int xal, it;

    for (row = vItems.begin(); row != vItems.end(); row++) {

        xal = 0, it=0;
        for (col = row->begin(); col != row->end(); col++, it++) {
            if(ItoVerify[it] == *col)
            {
                xal++;
                // ++xal;
                if(xal == 4)
                {
                    verified = true;
                }
            }
        }
    }
    return verified;
}