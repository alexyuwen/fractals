
char **makeSeirpinskiCarpet(int numLayers);
void copySubSquare(char **square, int numLayers, int x, int y);

char **makeSeirpinskiCarpet(int numLayers)
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

// recursive helper method for makeSeirpinskiCarpet()
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