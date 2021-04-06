/*
 * Author: Alex Yuwen
 * Description: This program contains algorithms to create three different fractals: the Seirpinski Carpet, Vicsek Snowflake, and Vicsek Cross.
 *              Note that if the fractal is sufficiently large, it will not be printed to the Terminal. A new .txt file
 *              will be created, containing the fractal pattern.
 */

#include "seirpinski_carpet.cpp"
#include "vicsek_snowflake.cpp"
#include "vicsek_cross.cpp"
#include "t-square.cpp"
#include "quadric_cross.cpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void printFractal(char **fractal, int fractalSize);
void writeFractalToFile(char **fractal, int fractalSize, string filename);
int getFractalSize(int choiceOfFractal, int numLayers);

struct FractalType
{
    const int MIN_LAYERS;
    const int MAX_LAYERS;
    char **(*functionPtr)(int);
    const string OUTPUT_FILE_NAME;
    const int MAX_LAYERS_FOR_PRINTING;
};

int main(int argc, char *argv[])
{
    FractalType fractals[] = {
        {0, 7, &seirpinskiCarpet, "seirpinski_carpet.txt", 3}, // Seirpinski Carpet
        {1, 4, &vicsekSnowflake, "vicsek_snowflake.txt", 4},   // Vicsek Snowflake
        {1, 4, &vicsekCross, "vicsek_cross.txt", 4},           // Vicsek Cross
        {0, 5, &t_square, "t-square.txt", 5},                  // T-square
        {1, 6, &quadricCross, "quadric_cross.txt", 6}};        // quadric cross
    int choiceOfFractal;
    cout << "Welcome to the Fractal Factory." << endl;
    cout << "Which fractal pattern would you like to create?" << endl;
    cout << "\tEnter \"0\" for Seirpinski Carpet\n";
    cout << "\tEnter \"1\" for Vicsek Snowflake\n";
    cout << "\tEnter \"2\" for Vicsek Cross\n";
    cout << "\tEnter \"3\" for T-square\n";
    cout << "\tEnter \"4\" for quadric cross\n";
    cin >> choiceOfFractal;
    while (choiceOfFractal < 0 || choiceOfFractal > 4) // enters infinite loop if non-integer is entered
    {
        cout << "Please enter a number between 0 and 4: ";
        cin >> choiceOfFractal;
    }
    // prompt user for number of layers
    int numLayers = -1;
    const int MIN_LAYERS = fractals[choiceOfFractal].MIN_LAYERS;
    const int MAX_LAYERS = fractals[choiceOfFractal].MAX_LAYERS;
    cout << "How many layers would you like? ";
    do
    {
        cout << "Please enter a number between " << MIN_LAYERS << " and " << MAX_LAYERS << ": ";
        cin >> numLayers;
    } while (numLayers < MIN_LAYERS || numLayers > MAX_LAYERS);

    const int FRACTAL_SIZE = getFractalSize(choiceOfFractal, numLayers);
    // create fractal
    char **fractal = fractals[choiceOfFractal].functionPtr(numLayers);
    // save fractal to .txt file
    writeFractalToFile(fractal, FRACTAL_SIZE, fractals[choiceOfFractal].OUTPUT_FILE_NAME);
    // output fractal if sufficiently small
    if (numLayers <= fractals[choiceOfFractal].MAX_LAYERS_FOR_PRINTING)
    {
        printFractal(fractal, FRACTAL_SIZE);
    }

    // deallocate heap memory
    const int SIZE = pow(3, numLayers);
    for (int i = 0; i < SIZE; i++)
    {
        delete[] fractal[i];
    }
    delete[] fractal;
    return 0;
}

// outputs fractal by iterating over it char by char
void printFractal(char **fractal, int fractalSize)
{
    for (int i = 0; i < fractalSize; i++)
    {
        for (int j = 0; j < fractalSize; j++)
        {
            if (isspace(fractal[i][j]))
            {
                cout << " ";
            }
            else
            {
                cout << fractal[i][j];
            }
        }
        cout << endl;
    }
}

void writeFractalToFile(char **fractal, int fractalSize, string filename)
{
    // Create output file
    ofstream outfile;
    outfile.open("seirpinski_carpet.txt");
    for (int i = 0; i < fractalSize; i++)
    {
        for (int j = 0; j < fractalSize; j++)
        {
            outfile << fractal[i][j];
        }
        outfile << endl;
    }
}

int getFractalSize(int choiceOfFractal, int numLayers)
{
    int size;
    if (choiceOfFractal == 0 || choiceOfFractal == 1 || choiceOfFractal == 2)
    {
        size = pow(3, numLayers);
    }
    else if (choiceOfFractal == 3)
    {
        size = pow(2, numLayers + 2) - 2;
    }
    else
    { // choiceOfFractal == 4
        size = pow(2, numLayers + 1) - 1;
    }
    return size;
}