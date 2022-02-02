/*  Name: George Calvert
    Class: CPSC 122, Section 1
    Date Submitted: 1/27/22
    Assignment: Project 3
    Description: Takes two digit strings and an output file names as command line arguments
        Converts the digit strings to variables of type int using atoiMy described below
        Multiplies the newly created int variables and writes their product to the output file name 
*/


#include <iostream> 
#include <fstream> 
#include <cstring>
#include <string>
#include <cmath>

using namespace std;

int atoiMy(char[]);


/*
Description: puts the two arguments from command line and calls the atoimy function
    to multiply them together and put them into a file
Input: cstring values
output: places product of two integers into a file 
*/
int main(int argc, char* argv[])
{
    // make out file variable
    ofstream outFile;

    // num 1 from command line
    int num1 = atoiMy(argv[1]);

    // num 2 from command line
    int num2 = atoiMy(argv[2]);

    // file name
    string fileName = argv[3];

    // print to file
    outFile.open(fileName);
    outFile << num1 * num2 << endl;
    outFile.close();

    return 0;

}
/*
Description: converts c-string values into integers
Input: character array of a cstring
output: returns integer value of the c-string
*/
int atoiMy(char str[])
{
    // get size of array passed to use as 10^size
    int size = strlen(str) - 1;

    // return value
    int result = 0;

    // initialize variable to hold the char digit 
    int num;
    
    /* 
    for loop going throug c_string array
    does (integer * 10^ size)
    size decreses by one each time since
    it starts at highest digit 
    */
    for(int i = 0; i < strlen(str); i++)
    {
        // convert character to integer using ASCII
        num = int(str[i]) - 48;
        result += num * pow(10, size);
        size -= 1;
    }

    return result;
}