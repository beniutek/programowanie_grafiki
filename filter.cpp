#include "filter.h"
#include <iostream>
#include <math.h>

Filter::Filter(int (*x)[SIZE], double factor, double bias) {
  this->factor = factor;
  this->bias = bias;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      kernel[i][j] = x[i][j];
    }
  }
}

void Filter::show() {
  std::cout << "========" << std::endl;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      std::cout << " " << kernel[i][j];
    }
    std::cout << std::endl;
  }
  std::cout << "========" << std::endl;
}

Image Filter::apply_to(Image image) {
  if (image.get_channel() < 3) {
    return apply_to_gray(image);
  } else {
    std::cout << "not wokring yet";
    return apply_to_gray(image);
  }
}

Image Filter::apply_to_gray(Image image) {
  int width = image.get_width();
  int height = image.get_height();
  int channels = image.get_channel();
  int tmp_channels = channels;
  int offset = (int) ceil(SIZE / 2.0);
  unsigned char *tmp = (unsigned char*) malloc(image.size());
  unsigned char *data = image.get_data();

  for (
    unsigned char *px = image.get_data(), *pxg = tmp;
    px != image.get_data() + image.size();
    px += channels, pxg += channels
  ) {
    *pxg = get_new_pixel_value(width, channels, px);
  }


  return new Image(tmp, width, height, channels);
}

int Filter::get_new_pixel_value(int width, int channels, unsigned char * px) {
  return (
    *(px - width * channels - channels)*kernel[0][0] + *(px - width * channels)*kernel[0][1] + *(px - width * channels + channels)*kernel[0][2] +
    *(px - channels)*kernel[1][0]                    + *(px)*kernel[1][1]                      + *(px + channels)*kernel[1][2] +
    *(px + width * channels - channels)*kernel[2][0] + *(px + width * channels)*kernel[2][1] + *(px + width * channels + channels)*kernel[2][2]
  );
}

