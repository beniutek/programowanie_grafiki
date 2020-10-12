// filter.h
#pragma once
#include "image.h"

class Filter {
  public:
    static const int SIZE = 3;

    Filter (int (*)[SIZE], double = 1.0, double = 0.0);
    Image apply_to(Image);
    void show();
  private:
    int kernel[SIZE][SIZE];
    double factor;
    double bias;
    Image apply_to_gray(Image);
    unsigned char * apply_matrix_to_pixel(unsigned char *, unsigned char *);
};
