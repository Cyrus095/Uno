#include <cstdlib>         // rand()
#include <string>
#include "randomizer.hpp"

/*-----------------------------------------------------------*/

int randInt(int a, int b)
{
    if (a > b) {
        std::string errorMsg;
        errorMsg = "Error when calling randInt(";
        errorMsg += std::to_string(a) + ", " + std::to_string(b) + ")";
        throw errorMsg;
    }

    return (rand() % (b - a)) + a;
}
