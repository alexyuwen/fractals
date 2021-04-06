#include <iostream>
#include <fstream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;

char **vicsekSnowflake(int numLayers);
char **makeVicsekSnowflake(int numLayers);
void copySubPattern(char **square, int numLayers, int x, int y);

// makes then prints a snowflake fractal, the number of layers determined by user input
char **vicsekSnowflake(int numLayers)
{
    // create snowflake
    char **square = makeVicsekSnowflake(numLayers);
    return square;
}

char **makeVicsekSnowflake(int numLayers)
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
    // calls helper function which recursively contructs snowflake pattern
    copySubPattern(square, numLayers, 0, 0); // square is passed by pointer
    return square;
}

// recursive helper method for makeVicsekSnowflake()
void copySubPattern(char **square, int numLayers, int x, int y) // (x, y) describes the position of the upper-left corner where the sub-square will be copied
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
            if ((c + d) % 2 == 1)
            { // leave every other square empty
                continue;
            }
            copySubPattern(square, numLayers - 1, x + c * PARTITION_SIZE, y + d * PARTITION_SIZE); // recursive call
        }
    }
}
