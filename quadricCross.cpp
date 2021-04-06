#include <iostream>
#include <fstream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;

void quadricCross();
char **makeQuadricCross(int numLayers);
void copySubCrossPattern(char **square, int numLayers, int x, int y);
void printQuadricCross(char **square, int numLayers);
void writeQuadricCrossToFile(char **square, int numLayers);

// makes then prints a quadric cross fractal, the number of layers determined by user input
void quadricCross()
{
    // prompt user for number of layers
    int numLayers;
    cout << "Welcome to the Quadric Cross Maker." << endl;
    cout << "How many layers would you like? Please enter an integer between 1 and 6: ";
    cin >> numLayers;
    // validates user input
    while (numLayers < 1 || numLayers > 6) // enters infinite loop if non-integer value is given
    {
        cout << "Please enter a number between 1 and 6. How many layers would you like? ";
        cin >> numLayers;
    }
    // creates quadric cross
    char **square = makeQuadricCross(numLayers);
    // outputs quadric cross (if number of layers is four or less)
    if (numLayers <= 6)
    {
        printQuadricCross(square, numLayers);
    }
    // saves quadric cross to .txt file called "quadric-cross.txt"
    writeQuadricCrossToFile(square, numLayers);

    // deallocate heap memory
    const int SIZE = pow(2, numLayers + 1) - 1;
    for (int i = 0; i < SIZE; i++)
    {
        delete[] square[i];
    }
    delete[] square;
}

char **makeQuadricCross(int numLayers)
{
    const int SIZE = pow(2, numLayers + 1) - 1; // 2^1 + 2^2 + ... + 2^{numLayers + 1}
    // create dynamic 2D array, initializing all elements to an empty space
    char **square = new char *[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        square[i] = new char[SIZE];
        for (int j = 0; j < SIZE; j++)
        {
            square[i][j] = ' ';
        }
    }
    // calls helper function which recursively contructs quadric cross pattern
    copySubCrossPattern(square, numLayers, SIZE / 2, SIZE / 2); // square is passed by pointer
    return square;
}

// recursive helper method for makeQuadricCross()
void copySubCrossPattern(char **square, int numLayers, int x, int y) // (x, y) describes the position of the upper-left corner where the sub-square will be copied
{
    square[y][x] = '#';
    // base case
    if (numLayers == 0)
    {
        return;
    }
    // recursive case: recursive calls on all four corners of middle square
    const int OFFSET = pow(2, numLayers - 1);                  // 2^0 + 2^1 + ... + 2^{numLayers - 1}
    copySubCrossPattern(square, numLayers - 1, x - OFFSET, y); // recursive call
    copySubCrossPattern(square, numLayers - 1, x, y - OFFSET); //
    copySubCrossPattern(square, numLayers - 1, x + OFFSET, y); //
    copySubCrossPattern(square, numLayers - 1, x, y + OFFSET); // recursive call
}

// outputs quadric cross by iterating over "square" char by char
void printQuadricCross(char **square, int numLayers)
{
    const int SIZE = pow(2, numLayers + 1) - 1;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
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

void writeQuadricCrossToFile(char **square, int numLayers)
{
    // Create output file
    ofstream outfile;
    outfile.open("quadric-cross.txt");
    const int SIZE = pow(2, numLayers + 1) - 1;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            outfile << square[i][j];
        }
        outfile << endl;
    }
}