/*  Name: George Calvert
    Class: CPSC 122, Section 1
    Date Submitted: 2/7/22
    Assignment: Project 5
    Description: generates a random key for a affine cypher 
        then either decrypts or encrypts text from a file 
        then puts the result in a new file based on command arguments
*/

#include <iostream> 
#include <fstream> 

using namespace std;

void keyGen(string);

char encrypt(char, int, int);

void readWrite(fstream&, fstream&, fstream&, int, int, int);

char decrypt(char, int, int, int[]);

void fileOpen(fstream&, string, char);

int MI[] = {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};

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
        keyGen(argv[2]);
    }
    // encrypt or decrypt
    else
    {
        // FILE OPEN
        fstream keyFile;
        fileOpen(keyFile, argv[2], 'r');
        fileOpen(fin, argv[3], 'r');
        fileOpen(fout, argv[4], 'w');

        // read alpha and beta keys
        int alpha;
        int beta;
        keyFile >> alpha;
        keyFile >> beta;
        cout << alpha << endl;
        cout << beta << endl; 
        

        // call readWrite function
        readWrite(fin, fout, keyFile, type, alpha, beta);
        keyFile.close();
    }
    

    // close files
    fin.close();
    fout.close();
}
/*
Description: generates a random number [1 - 25]
    that will be the beta values for the affine cypher 
    then a randomly selected value from the global
    array
Input: string of the keyFile name
Output: none
*/ 
void keyGen(string name) 
{
    fstream keyFile;
    fileOpen(keyFile, name, 'w');
    srand(time(0));
    int alp = MI[rand() % 12];
    int bet = rand() % 25 + 1;
    keyFile << alp << endl;
    keyFile << bet << endl;
    keyFile.close();
}
/*
Description: While loop that goes through a file if it is not doing
    just keyfile then either encrypts or decrypts
Input: 3 fstreams pass by refrences for input file output file 
    and keyfile then an int that tells to encrypt/decrypt
Output: puts either encrypted or decrypted character into file
*/ 
void readWrite(fstream& fin, fstream& fout, fstream& keyFile, int type, int alpha, int beta)
{
    char ch;
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
                ch = encrypt(ch, alpha, beta);
            }
            else 
            {
                ch = decrypt(ch, alpha, beta, MI);
            }
            
        }
        fout.put(ch);
    }

}
/*
Description: Encrypts using affine cypher, 
    using ascii table
Input: Key for cypher, character, alpha, and beta
Output: Encrypted character
*/
char encrypt(char ch, int alpha, int beta)
{
    char encryptChar = ((((ch - 65) * alpha) + beta) % 26) + 65;
    return encryptChar;
}

/*
Description: Decrypts using affine cypher, 
    using ascii table and global array
Input: Key for cypher, character, alpha, and beta
Output: Encrypted character
*/
char decrypt(char ch, int alpha, int beta, int arr[])
{
    char decryptChar = ((ch - 65 - alpha + 26) % 26) + 65;
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