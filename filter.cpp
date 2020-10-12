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
  // for (
  //   unsigned char *p = image.get_data(), *pg = tmp;
  //   p != image.get_data() + image.size();
  //   p += channels, pg += channels
  // ) {
  //   // *pg = (*p + *(p + 1) + *(p + 2)) / 3.0;
  // }

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      *tmp = (data + i)[j];
    }
  }
  return new Image(tmp, width, height, channels);
}

// unsigned char * Filter::apply_matrix_to_pixel(unsigned char * pixel, unsigned char * data) {
//     for (int i; i < SIZE; i++) {
//       for (int j; j < SIZE; j++) {
//         kernel[i][j]
//       }
//     }
// }
