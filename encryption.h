#include <iostream>
#include <fstream>
#include <iterator>
#include<time.h> 
#include <vector>

class EncryptDecrypt {
    private: //DATA TYPES
        const int keyLength = 4;
        const std::string keyFile = "keys.dat";
        
    private: //METHODS
        std::string encrypt(int, int);
        std::vector<int> decrypt(std::string);
        
    protected:
        std::vector<std::string> pullETF();
        const int proxykeyLength = keyLength;
        void sendETF(std::string);  
        void truncateKeyFile();
    
    public: 
        void createEncryption(int[]);
        std::vector< std::vector<int> > startDecryption();
};




/*
    ######### MAKES AND RETURNS ARRAY OF DECRYPTED ITEMS ############
    ######      CREATE ENCRYPTION + START DECRYPTION           ######
    #################################################################
*/


//This method takes an array of int, casts it to a string
//of random chars, then sends the encrypted string to a file.
void EncryptDecrypt::createEncryption(int arr[])
{
    std::string encryptedKey;
    srand(time(0)); 
    for(int i=0; i<keyLength; i++)
    {
        std::string newEncr;
        int eNum = rand() % 93 + 33;
        newEncr = encrypt(arr[i], eNum);
        encryptedKey += newEncr;
    }
    sendETF(encryptedKey);
}

//this method returns a nested vector of integers.
//pulls the items from a file and assigns them to a vector
//loops through the vector and decrypts each item
//returns the decrypted item as a nested vector of ints inside,
//the main vector.
std::vector< std::vector<int> > EncryptDecrypt::startDecryption()
{
    std::vector< std::vector<int> > decryptedItems;
    std::vector<std::string> items = pullETF();
    std::vector<std::string>::iterator ptr; 

    for (ptr = items.begin(); ptr < items.end(); ptr++) {
        std::vector<int> decodeItem = decrypt(*ptr); 
        decryptedItems.push_back(decodeItem);
    }
    
    return decryptedItems;
}





/*
    ########################
    ### FILE HANDINGLING ###
    ########################
*/





//Sends each Encrypted string to file;
void EncryptDecrypt::sendETF(std::string item)
{
    std::ofstream file;
    file.open(keyFile, std::ios::app);
    
    if(file.is_open())
    {
        file << item << std::endl ;
    }
    file.close();
}

//Pulls each enrypted item from file
//and adds it to a vector
std::vector<std::string> EncryptDecrypt::pullETF()
{
    std::vector<std::string> item;
    std::ifstream file;
    
    file.open(keyFile, std::ios::in);
    if(file.is_open())
    {
        std::string acts;
        while(getline(file, acts))
        {
            item.push_back(acts);
        }
    }
    file.close();
    return item;
}

void EncryptDecrypt::truncateKeyFile()
{
    std::ofstream file;
    file.open(keyFile, std::ios::trunc);
    std::cout << "DONE";
    file.close();
}



/*
    ################ USED IN A LOOP ############
    ### ITEM ENRYPTION + DECRYPTION METHODS ###
    ###########################################
*/


//Decrypts each item and assigns it to a vector.
//takes a string argument, loops through the string like
// an array. Takes each odd indexs element. casts to char and
//assigns each element to a new vector.
//returns the vector of integers
std::vector<int> EncryptDecrypt::decrypt(std::string item)
{
    std::vector<int> deCode;
    for(int i=0; i<(keyLength)*2; i++)
    {
        deCode.push_back(item[i++]);
    }
    return deCode;
}

//Encrypts each number from the array.
//Made to run in a loop
std::string EncryptDecrypt::encrypt(int item, int encrNum)
{
    std::string eItem;
    char c1 = (char) item; 
    char c2 = (char) encrNum;
    
    eItem += c1;
    eItem += c2;
    return eItem;
}