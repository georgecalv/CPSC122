/*  Name: George Calvert
    Class: CPSC 122, Section 1
    Date Submitted: January 19, 2021
    Assignment: Project 1
    Description: prints however many prime numbers user wants then displays them into however many columns the user would like
*/

#include <iostream> /// incude input output
#include <math.h> ///sqrt function
using namespace std;

// determine if an integer is a prime number
bool isPrime(int);

// prints out the first n primes into how ever many columns 
void display(int, int);

// error checking
void error(int);

// Main takes in two arguments from the command line
int main(int argc, char* argv[])
{
    // gets rows and columns from command line and converts them to integers
    int num = atoi(argv[1]);  
    int col = atoi(argv[2]); 

    // error catching
    // cant have less than 1 prime number
    if (num < 1)
        error(1);
    // cant have less than 1 column
    if(col < 1)
        error(2);


    // calls display which in turn calls isPrime
    display(num, col);

}

// determine if an integer is a prime number 
// returns true if prime then false if not prime
bool isPrime(int num)
{
     // 0 and 1 are not prime
    if(num <= 1) 
    {
        return false;
    }
    else 
    {
        // trial division. given input num if num is divisable by any number between 2 to sqrt(num) then it is not prime
        for(int i = 2; i <= sqrt(num); i++) 
        {
            // number is divisable by something other than itself and 1 so not prime
            if (num % i == 0) 
            {
                return false;
            }
        }
    }
    // number is prime
    return true;
}

// prints out the number of primes sepcified by the user then into how ever many columns the user wnats as well
void display(int totalPrimes, int cols)
{
    string output = "";

    // starts at number 0, number to be tested if prime goes up by one each loop
    int nums = 0;
    // times tracks how many prime numbers have been found 
    int times = 0;
    // loops until the number of primes found is equal to however many the user wanted
    while(times < totalPrimes) 
    {
        // if number is prime
        if(isPrime(nums)) 
        {
            times++;
            // goes to new line depending on how many columns user wants
            if(times % cols == 0) 
            {
                output += to_string(nums) + "\n";
            }
            // non new line
            else 
            {
                output += to_string(nums) + "\t";
            }
            
        }  
        nums++;
    }
    // prints string output
    cout << output << endl;
}
// error catching
void error(int code)
{
    // error for numbers
    if (code == 1)
    {
        cout <<  "Numbers displayed must be >= 1" << endl;
        exit(EXIT_FAILURE);
    }
    // error for columns
    if (code == 2)
    {
        cout <<  "Columns must be >= 1" << endl;
        exit(EXIT_FAILURE);
    }
}