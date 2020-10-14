#include "image.h"
#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

Image::Image(std::string path, int req_comp) {
  data = stbi_load(path.c_str(), &width, &height, &channels, req_comp);

  if (this->data == NULL) {
    std::cout << "error loading the image "<< path << ", data is null" << std::endl;
    exit(1);
  }
};

Image::Image(unsigned char *data, int width, int height, int channels) {
  this->width = width;
  this->height = height;
  this->channels = channels;
  this->data = data;
}

Image::Image(Image *image) {
  width = image->get_width();
  height = image->get_height();
  channels = image->get_channel();
  data = image->get_data();
}

Image::~Image() {
  // stbi_image_free(data);
}


int Image::get_height() { return height; };
int Image::get_width() { return width; };
int Image::get_channel() { return channels; };
unsigned char * Image::get_data() { return data; };

size_t Image::size() {
  return width * height * channels;
}

Image *Image::to_gray() {
  int gray_channels = channels == 4 ? 2 : 1;
  size_t gray_image_size = width * height * gray_channels;
  unsigned char *gray_image = (unsigned char*) malloc(gray_image_size);

  if(gray_image == NULL) {
    printf("Unable to allocate memory for the gray image.\n");
    exit(1);
  }

  for (unsigned char *p = data, *pg = gray_image; p != data + size(); p += channels, pg += gray_channels) {
      *pg = (uint8_t)((*p + *(p + 1) + *(p + 2))/3.0);

      if(channels == 4) {
          *(pg + 1) = *(p + 3);
      }
  }

  return new Image(gray_image, width, height, gray_channels);
}

void Image::save(std::string path) {
  stbi_write_jpg(path.c_str(), width, height, channels, data, 100);
}
