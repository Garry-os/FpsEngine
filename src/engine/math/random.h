#pragma once
#include <random>

class RandomGenerator {
public:
    RandomGenerator(float seed) :engine(seed) {}
    RandomGenerator() :engine(std::random_device{}()) {}

    template <typename T>
    T value(T min, T max) {
        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<int> dist(min, max);
            return dist(engine);
        }
        else {
            std::uniform_real_distribution<float> dist(min, max);
            return dist(engine);
        }
    }

private:
    std::mt19937 engine;
};
