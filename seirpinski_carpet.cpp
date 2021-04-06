#include <iostream>
#include <fstream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;

void seirpinskiCarpet();
char **makeCarpetFractal(int numLayers);
void copySubSquare(char **square, int numLayers, int x, int y);
void printCarpet(char **square, int numLayers);
void writeCarpetToFile(char **square, int numLayers);

// makes then prints a carpet fractal, the number of layers determined by user input
void seirpinskiCarpet()
{
    // prompt user for number of layers
    int numLayers;
    cout << "Welcome to the Carpet Fractal Maker." << endl;
    cout << "How many layers would you like? Please enter an integer between 0 and 7: ";
    cin >> numLayers;
    // validates user input
    while (numLayers < 0 || numLayers > 7) // enters infinite loop if non-integer value is given
    {
        cout << "Please enter a number between 0 and 7. How many layers would you like? ";
        cin >> numLayers;
    }
    // creates carpet
    char **square = makeCarpetFractal(numLayers);
    // outputs carpet (if number of layers is three or less)
    if (numLayers <= 3)
    {
        printCarpet(square, numLayers);
    }
    // saves carpet to .txt file called "carpet.txt"
    writeCarpetToFile(square, numLayers);

    // deallocate heap memory
    const int SIDE_LENGTH = pow(3, numLayers);
    for (int i = 0; i < SIDE_LENGTH; i++)
    {
        delete[] square[i];
    }
    delete[] square;
}

char **makeCarpetFractal(int numLayers)
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
    // calls helper function which recursively contructs carpet pattern
    copySubSquare(square, numLayers, 0, 0); // square is passed by pointer
    return square;
}

// recursive helper method for makeCarpetFractal()
void copySubSquare(char **square, int numLayers, int x, int y) // (x, y) describes the position of the upper-left corner where the sub-square will be copied
{
    if (numLayers == 0)
    { // base case
        square[y][x] = '#';
        return;
    }
    // recursive case
    const int PARTITION_SIZE = pow(3, numLayers - 1);
    for (int c = 0; c < 3; c++)
    {
        for (int d = 0; d < 3; d++)
        {
            if (c == 1 && d == 1)
            { // leave the middle of the square empty
                continue;
            }
            copySubSquare(square, numLayers - 1, x + c * PARTITION_SIZE, y + d * PARTITION_SIZE); // recursive call
        }
    }
}

// outputs carpet by iterating over "square" char by char
void printCarpet(char **square, int numLayers)
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

void writeCarpetToFile(char **square, int numLayers)
{
    // Create output file
    ofstream outfile;
    outfile.open("carpet.txt");
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