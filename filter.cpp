#include "filter.h"
#include <iostream>
#include <math.h>

Filter::Filter(int (*x)[SIZE], double factor) {
  this->factor = factor;
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
  int width = image.get_width();
  int height = image.get_height();
  int channels = image.get_channel();
  int size = image.size();
  unsigned char *tmp = (unsigned char*) malloc(size);
  unsigned char *original = image.get_data();

  for (
    unsigned char *px = original, *px_tmp = tmp;
    px != original + size;
    px += channels, px_tmp += channels
  ) {
    *px_tmp = normalize(get_new_pixel_value(width, channels, px));
    if (channels == 3) {
      *(px_tmp + 1) = normalize(get_new_pixel_value(width, channels, px + 1));
      *(px_tmp + 2) = normalize(get_new_pixel_value(width, channels, px + 2));
    }
    if (channels == 4) {
      *(px_tmp + 3) = normalize(get_new_pixel_value(width, channels, px + 3));
    }
  }

  return new Image(tmp, width, height, channels);
}

int Filter::get_new_pixel_value(int width, int channels, unsigned char * px) {
  return (
    *(px - width * channels - channels)*kernel[0][0] + *(px - width * channels)*kernel[0][1] + *(px - width * channels + channels)*kernel[0][2] +
    *(px - channels)*kernel[1][0]                    + *(px)*kernel[1][1]                      + *(px + channels)*kernel[1][2] +
    *(px + width * channels - channels)*kernel[2][0] + *(px + width * channels)*kernel[2][1] + *(px + width * channels + channels)*kernel[2][2]
  )/factor;
}

bool out_of_RGB_bounds(int px) {
  return px > 255 || px < 0;
}

int Filter::normalize(int px) {
  if (px < 0) {
    return 0;
  } else if (px > 255) {
    return 255;
  } else {
    return px;
  }
}


