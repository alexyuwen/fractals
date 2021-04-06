#include <iostream>
#include <fstream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;

void vicsekCross();
char **makeVicsekCross(int numLayers);
void copySubCross(char **square, int numLayers, int x, int y);
void printCross(char **square, int numLayers);
void writeCrossToFile(char **square, int numLayers);

// makes then prints a cross fractal, the number of layers determined by user input
void vicsekCross()
{
    // prompt user for number of layers
    int numLayers;
    cout << "Welcome to the Vicsek Cross Maker." << endl;
    cout << "How many layers would you like? Please enter an integer between 1 and 4: ";
    cin >> numLayers;
    // validates user input
    while (numLayers < 1 || numLayers > 4) // enters infinite loop if non-integer value is given
    {
        cout << "Please enter a number between 1 and 4. How many layers would you like? ";
        cin >> numLayers;
    }
    // creates cross
    char **square = makeVicsekCross(numLayers);
    // outputs cross (if number of layers is four or less)
    if (numLayers <= 4)
    {
        printCross(square, numLayers);
    }
    // saves cross to .txt file called "cross.txt"
    writeCrossToFile(square, numLayers);

    // deallocate heap memory
    const int SIDE_LENGTH = pow(3, numLayers);
    for (int i = 0; i < SIDE_LENGTH; i++)
    {
        delete[] square[i];
    }
    delete[] square;
}

char **makeVicsekCross(int numLayers)
{
    const int SIDE_LENGTH = pow(3, numLayers);
    // create dynamic 2D array, initializing all elements to an empty space
    char **square = new char *[SIDE_LENGTH];
    for (int i = 0; i < SIDE_LENGTH; i++)
    {
        square[i] = new char[SIDE_LENGTH];
        for (int j = 0; j < SIDE_LENGTH; j++)
        {
            square[i][j] = ' ';
        }
    }
    // calls helper function which recursively contructs cross pattern
    copySubCross(square, numLayers, 0, 0); // square is passed by pointer
    return square;
}

// recursive helper method for makeVicsekCross()
void copySubCross(char **square, int numLayers, int x, int y) // (x, y) describes the position of the upper-left corner where the sub-square will be copied
{
    if (numLayers == 0)
    { // base case
        square[x][y] = '#';
        return;
    }
    // recursive case
    const int PARTITION_SIZE = pow(3, numLayers - 1);
    for (int c = 0; c < 3; c++)
    {
        for (int d = 0; d < 3; d++)
        {
            if (c % 2 == 0 && d % 2 == 0)
            { // leave corner squares empty
                continue;
            }
            copySubCross(square, numLayers - 1, x + c * PARTITION_SIZE, y + d * PARTITION_SIZE); // recursive call
        }
    }
}

// outputs cross by iterating over "square" char by char
void printCross(char **square, int numLayers)
{
    const int SIDE_LENGTH = pow(3, numLayers);
    for (int i = 0; i < SIDE_LENGTH; i++)
    {
        for (int j = 0; j < SIDE_LENGTH; j++)
        {
            if (isspace(square[i][j]))
            {
                cout << " ";
            }
            else
            {
                cout << square[i][j];
            }
        }
        cout << endl;
    }
}

void writeCrossToFile(char **square, int numLayers)
{
    // Create output file
    ofstream outfile;
    outfile.open("cross.txt");
    const int SIDE_LENGTH = pow(3, numLayers);
    for (int i = 0; i < SIDE_LENGTH; i++)
    {
        for (int j = 0; j < SIDE_LENGTH; j++)
        {
            outfile << square[i][j];
        }
        outfile << endl;
    }
}