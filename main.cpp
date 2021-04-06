/*
 * Author: Alex Yuwen
 * Date: April 1, 2021
 * Description: This program contains algorithms to create three different fractals: the Seirpinski Carpet, Vicsek Snowflake, and Vicsek Cross.
 *              Note that if the fractal is sufficiently large, it will not be printed to the Terminal. A new .txt file
 *              will be created, containing the fractal pattern.
 * Usage: To run the Seirpinski Carpet algorithm, uncomment "seirpinskiCarpet();" in the main() function
 *        To run the Vicsek Snowflake algorithm, uncomment "vicsekSnowflake();" in the main() function
 *        To run the Vicsek Cross algorithm, uncomment "vicsekCross();" in the main() function
 *        To run the T-square algorithm, uncomment "t_square();" in the main() function
 */

#include "seirpinski_carpet.cpp"
#include "vicsek_snowflake.cpp"
#include "vicsek_cross.cpp"
#include "t-square.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    // seirpinskiCarpet();
    // vicsekSnowflake();
    // vicsekCross();
    t_square();
    return 0;
}
