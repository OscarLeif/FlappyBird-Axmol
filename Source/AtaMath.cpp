//
// Created by oscar on 3/31/2024.
//

#include "AtaMath.h"

#include <iostream>


float AtaMath::interpolate(float minValue, float maxValue, float interpolation) {
    // Ensure interpolation is between 0 and 1
    interpolation = std::max(0.0f, std::min(1.0f, interpolation));

    // Interpolate between minValue and maxValue
    return minValue + (maxValue - minValue) * interpolation;
}
