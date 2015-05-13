#include <cstdlib>         // rand()
#include "randomizer.hpp"

/*-----------------------------------------------------------*/

int randInt(int a, int b)
{
    return (rand() % (b - a)) + a;
}
