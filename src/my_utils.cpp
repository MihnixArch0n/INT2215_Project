#include "my_utils.hpp"

namespace my_utils
{
    double to_seconds(int milliseconds)
    {
        return static_cast<double>(milliseconds) / 1000.0;
    }
}
