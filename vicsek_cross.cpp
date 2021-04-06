#include <iostream>
#include <fstream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;

char **vicsekCross(int numLayers);
char **makeVicsekCross(int numLayers);
void copySubCross(char **square, int numLayers, int x, int y);

// makes then prints a cross fractal, the number of layers determined by user input
char **vicsekCross(int numLayers)
{
    // create cross
    char **square = makeVicsekCross(numLayers);
    return square;
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
        square[y][x] = '#';
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
