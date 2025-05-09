#ifndef MY_UTILS_HPP
#define MY_UTILS_HPP


#include <vector>


namespace my_utils
{
    double to_seconds(int milliseconds);

    int weighted_random(const std::vector<double>& probabilities);

    int uniform_random(int min, int max);
}

#endif //MY_UTILS_HPP
