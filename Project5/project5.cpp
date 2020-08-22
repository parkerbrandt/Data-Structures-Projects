// Preprocessor Directives
// Includes
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;


// Main Function
// Start of Program Logic
int main(int argc, char* argv[])
{
    // Variables
    string filename;
    ifstream inputFile;
    unordered_map<string, int> rawMap;
    multimap<int, string> firstMap;
    unordered_multimap<string, int> finalMap;

    // Check main parameters
    if(argc != 2)
        return -1;

    // Get the name of the file and initialize ifstream object
    filename = argv[1];
    inputFile = ifstream(filename);

    // Get each token and store in a map or unordered map
    // and increment the frequencies
    string token;
    char aChar;

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

            // Add the token to the map and increment
            rawMap[token]++;
        }
    }

    // Close the file
    inputFile.close();

    // Sort the map into descending order of values
    // First put into a multimap and sort by the integer value
    for(const auto& x : rawMap)
        firstMap.insert(pair<int, string>(x.second, x.first));

    // Put into a new map in descending order
    // To sort the strings we can put them into a temporary ordered map and then put those entries into an unordered map
    map<string, int> tempMap;
    unordered_map<string, int> positionMap;
    int tempValue = 0, newValue;
    int count = 0;

    for(multimap<int, string>::reverse_iterator values = firstMap.rbegin(); values != firstMap.rend(); values++)
    {
        // Need to sort the string entries
        newValue = (*values).first;
        if(newValue != tempValue)
        {
            // Need to put all previous entries in tempMap into finalMap
            for(multimap<string, int>::iterator tempValues = tempMap.begin(); tempValues != tempMap.end(); tempValues++)
            {
                finalMap.insert(pair<string, int>((*tempValues).first, (*tempValues).second));
                positionMap[(*tempValues).first] = count++;

                // Output values so they will output in descending order
                cout << (*tempValues).first << " ";
            }

            // Empty tempMap
            tempMap.clear();

            // Update tempValue
            tempValue = newValue;
        }

        // Add new pair into tempMap
        tempMap.insert(pair<string,int>((*values).second, (*values).first));
    }

    // Need to do one more for loop afterwards to account for last value (typically 1)
    for(multimap<string, int>::iterator tempValues = tempMap.begin(); tempValues != tempMap.end(); tempValues++)
    {
        finalMap.insert(pair<string, int>((*tempValues).first, (*tempValues).second));
        positionMap[(*tempValues).first] = count++;
        cout << (*tempValues).first << " ";
    }
    cout << endl;

    // Open file again for reading
    inputFile.open(filename, ifstream::in);

    // Read each token again
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

            // Find position in map and print position
            cout << (positionMap[token] + 1) << " ";
        }
    }

    cout << endl;

    return 0;
}