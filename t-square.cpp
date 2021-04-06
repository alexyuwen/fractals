#include <iostream>
#include <fstream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;

void t_square();
char **makeT_square(int numLayers);
void copySubSquarePattern(char **square, int numLayers, int x, int y);
void printT_square(char **square, int numLayers);
void writeT_squareToFile(char **square, int numLayers);

// makes then prints a T-square fractal, the number of layers determined by user input
void t_square()
{
    // prompt user for number of layers
    int numLayers;
    cout << "Welcome to the T-Square Maker." << endl;
    cout << "How many layers would you like? Please enter an integer between 0 and 5: ";
    cin >> numLayers;
    // validates user input
    while (numLayers < 0 || numLayers > 5) // enters infinite loop if non-integer value is given
    {
        cout << "Please enter a number between 0 and 5. How many layers would you like? ";
        cin >> numLayers;
    }
    // creates T-square
    char **square = makeT_square(numLayers);
    // outputs T-square (if number of layers is four or less)
    if (numLayers <= 5)
    {
        printT_square(square, numLayers);
    }
    // saves T-square to .txt file called "t-square.txt"
    writeT_squareToFile(square, numLayers);

    // deallocate heap memory
    const int SIZE = pow(2, numLayers + 2) - 2; // 2^1 + 2^2 + ... + 2^{numLayers + 1}
    for (int i = 0; i < SIZE; i++)
    {
        delete[] square[i];
    }
    delete[] square;
}

char **makeT_square(int numLayers)
{
    const int SIZE = pow(2, numLayers + 2) - 2;      // 2^1 + 2^2 + ... + 2^{numLayers + 1}
    const int initialOffset = pow(2, numLayers) - 1; // 2^0 + 2^1 + ... + 2^{numLayers - 1}
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
    // calls helper function which recursively contructs T-square pattern
    copySubSquarePattern(square, numLayers, initialOffset, initialOffset); // square is passed by pointer
    return square;
}

// recursive helper method for makeT_square()
void copySubSquarePattern(char **square, int numLayers, int x, int y) // (x, y) describes the position of the upper-left corner where the sub-square will be copied
{
    const int MIDDLE_SQUARE_SIZE = pow(2, numLayers + 1);
    for (int i = 0; i < MIDDLE_SQUARE_SIZE; i++)
    {
        for (int j = 0; j < MIDDLE_SQUARE_SIZE; j++)
        {
            square[x + i][y + j] = '#';
        }
    }
    // base case
    if (numLayers == 0)
    {
        return;
    }
    // recursive case: recursive calls on all four corners of middle square
    const int OFFSET = pow(2, numLayers - 1);                                                                      // 2^0 + 2^1 + ... + 2^{numLayers - 1}
    copySubSquarePattern(square, numLayers - 1, x - OFFSET, y - OFFSET);                                           // recursive call
    copySubSquarePattern(square, numLayers - 1, x + MIDDLE_SQUARE_SIZE - OFFSET, y - OFFSET);                      //
    copySubSquarePattern(square, numLayers - 1, x - OFFSET, y + MIDDLE_SQUARE_SIZE - OFFSET);                      //
    copySubSquarePattern(square, numLayers - 1, x + MIDDLE_SQUARE_SIZE - OFFSET, y + MIDDLE_SQUARE_SIZE - OFFSET); // recursive call
}

// outputs T-square by iterating over "square" char by char
void printT_square(char **square, int numLayers)
{
    const int SIZE = pow(2, numLayers + 2) - 2; // 2^1 + 2^2 + ... + 2^{numLayers + 1}
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

void writeT_squareToFile(char **square, int numLayers)
{
    // Create output file
    ofstream outfile;
    outfile.open("t-square.txt");
    const int SIZE = pow(2, numLayers + 2) - 2; // 2^1 + 2^2 + ... + 2^{numLayers + 1}
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            outfile << square[i][j];
        }
        outfile << endl;
    }
}