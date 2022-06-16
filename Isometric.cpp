#include "Utilities.h"

namespace Isometric {
    void ConvertToIsometricCoord(int x, int y, int * i, int * j, int width, int height){
        *i = x * 0.5 * width + y * -0.5 * height;
        *j = x * 0.25 * width + y * 0.25 * height;
    }
    void ConvertFromIsometricCoord(int i, int j, int * x, int * y, int width, int height){
        *x = i * 1 / width + j * 2 / height;
        *y = i * -1 / width + j *  2 / height;
    }
};