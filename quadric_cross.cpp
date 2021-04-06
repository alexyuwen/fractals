#include <iostream>
#include <fstream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;

char **quadricCross(int numLayers);
char **makeQuadricCross(int numLayers);
void copySubCrossPattern(char **square, int numLayers, int x, int y);

// makes then prints a quadric cross fractal, the number of layers determined by user input
char **quadricCross(int numLayers)
{
    // create quadric cross
    char **square = makeQuadricCross(numLayers);
    return square;
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