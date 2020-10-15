// filter.h
#pragma once
#include "image.h"

class Filter {
  public:
    static const int SIZE = 3;

    Filter (int (*)[SIZE], double = 1.0);
    Image apply_to(Image);
    void show();
  private:
    int kernel[SIZE][SIZE];
    double factor;
    Image apply_to_gray(Image);
    int get_new_pixel_value(int, int, unsigned char *);
    int normalize(int);
};
