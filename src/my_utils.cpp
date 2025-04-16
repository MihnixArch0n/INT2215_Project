#include "my_utils.hpp"

#include <random>


namespace my_utils
{
    double to_seconds(int milliseconds)
    {
        return static_cast<double>(milliseconds) / 1000.0;
    }

    int weighted_random(const std::vector<double>& probabilities)
    {
        static std::random_device rd;
        static std::mt19937 genTwisterEngine(rd());

        std::discrete_distribution<> distribution(probabilities.begin(),
            probabilities.end());
        return distribution(genTwisterEngine);
    }
}
