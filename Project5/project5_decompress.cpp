#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <iterator>
using namespace std;


// Main Function
// Start of Program Logic
int main(int argc, char** argv)
{
    // Variables
    string filename;
    ifstream inputFile;
    string* wordArray = new string[100];
    int* freqArray = new int[100];
    multimap<int, string> freqToString;

    // Get the filename from the command line
    // Make sure there are two command line arguments
    if(argc != 2)
        return -1;

    filename = argv[1];

    // Initialize the input file stream
    inputFile = ifstream(filename);

    // Get each token and store into the wordArray
    string token;
    char aChar;
    int strCount = 0, intCount = 0;

    while(!inputFile.eof())
    {
        do
        {
            inputFile.get(aChar);
        }
        while((!inputFile.eof()) && ((aChar == ' ') || (aChar == '\n')));

        if(!inputFile.eof())
        {
            token.clear();
            while((!inputFile.eof()) && ((aChar != ' ') && (aChar != '\n')))
            {
                token += aChar;
                inputFile.get(aChar);
            }

            // Add the token to the appropriate array
            if(isdigit(stoi(token)))
            {
                // Is a string
                wordArray[strCount++] = token;
            }
            else
            {
                // Is an integer
                freqArray[intCount++] = stoi(token);
            }
        }
    }

    return 0;
}