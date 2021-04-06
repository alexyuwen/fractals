
char **makeT_square(int numLayers);
void copySubSquarePattern(char **square, int numLayers, int x, int y);

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
            square[y + i][x + j] = '#';
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