// image.h
#pragma once
#include <string>

class Image {
  int width, height, channels;
  unsigned char *data;

  public:
    Image (std::string, int = 0);
    Image (unsigned char *, int, int, int);
    Image (Image *);
    size_t size();
    Image *to_gray();
    int *get_region(int, int = 3, int = 3);
    void save(std::string);
    int get_height();
    int get_width();
    int get_channel();
    unsigned char * get_data();
};
