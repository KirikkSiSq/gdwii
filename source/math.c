#include "math.h"
#include <math.h>

float positive_fmod(float n, float divisor) {
    float value = fmod(n, divisor);
    return value + (value < 0 ? divisor : 0);
}