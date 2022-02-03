/*  Name: George Calvert
    Class: CPSC 122, Section 1
    Date Submitted: 2/2/22
    Assignment: Project 4
    Description: generates a random key for a caeser cypher 
        then either decrypts or encrypts text from a file 
        then puts the result in a new file based on command arguments
*/

#include <iostream> 
#include <fstream> 

using namespace std;

int keyGen(void);

char encrypt(char, int);

void readWrite(fstream&, fstream&, fstream&, int);

char decrypt(char, int);


void fileOpen(fstream&, string, char);

/*
Description: takes in command line arguments 
    of whetherit is encrypting, decrypting 
    or it is generating the key, 
    then the file names of the reading and 
    writing files
Input: command line arguments of file names and wheter it 
    it is decrypting or encrypting
Output: puts key encryption or decryption into a file
*/ 
int main(int argc, char* argv[])
{
    fstream fin;
    fstream fout;
    int type = atoi(argv[1]);

    // write key to file
    if(type == 0)
    {
        int key = keyGen();
        fileOpen(fout, argv[2], 'w');
        fout << key << endl; 
    }
    // encrypt or decrypt
    else
    {
        // FILE OPEN
        fstream keyFile;
        fileOpen(keyFile, argv[2], 'r');
        fileOpen(fin, argv[3], 'r');
        fileOpen(fout, argv[4], 'w');

        // call readWrite function
        readWrite(fin, fout, keyFile, type);
        keyFile.close();
    }
    

    // close files
    fin.close();
    fout.close();
}
/*
Description: generates a random number 
    that will be the key for the caeser cypher 
Input: none
Output: random int
*/ 
int keyGen() 
{
    srand(time(0));
    return rand() % 25 + 1;
}
/*
Description: While loop that goes through a file if it is not doing
    just keyfile then either encrypts or decrypts
Input: 3 fstreams pass by refrences for input file output file 
    and keyfile then an int that tells to encrypt/decrypt
Output: puts either encrypted or decrypted character into file
*/ 
void readWrite(fstream& fin, fstream& fout, fstream& keyFile, int type) 
{
    char ch;
    int key;
    keyFile >> key;
    // encrypt or decrypt file and put into a dif file
    // go through in file and write to out file
    while(fin.peek() != EOF)
    {
        ch = fin.get();
        // is a letter
        if(isalpha(ch))
        {
            ch = toupper(ch);
            // encrypt or decrypt
            if(type == 1)
            {
                ch = encrypt(ch, key);
            }
            else 
            {
                ch = decrypt(ch, key);
            }
            
        }
        fout.put(ch);
    }

}
/*
Description: Encrypts using ceaser cypher, 
    using ascii table
Input: Key for cypher and character
Output: Encrypted character
*/
char encrypt(char ch, int key)
{
    char encryptChar = ((ch - 65 + key) % 26) + 65;
    return encryptChar;
}

/*
Description: Decrypts using ceaser cypher, 
    using ascii table
Input: Key for cypher and character
Output: Decrypted character
*/
char decrypt(char ch, int key)
{
    char decryptChar = ((ch - 65 - key + 26) % 26) + 65;
    return decryptChar;
}

/*
Description: function opens a file 
Input: file stream object reference, name of the file, mode of open
Output: void function, but at exit, file stream object is tied to 
the input file name. 
*/ 
void fileOpen(fstream& file, string name, char mode)
{
    string fileType;

    if (mode == 'r')
        fileType = "input";
    if (mode == 'w')
        fileType = "output";
    if (mode == 'r')
        file.open(name, ios::in);  //available thorugh fstream
    if (mode == 'w')
        file.open(name, ios::out);  //available through fstream;
    if (file.fail()) //error condition 
    {
        cout << "Error opening " << fileType << " file" << endl; 
        exit(EXIT_FAILURE);
    }
}
