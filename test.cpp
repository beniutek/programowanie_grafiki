#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

class Filter {
  int foo;
};

class Image {
  int width, height, channels;
  unsigned char *data;

  public:
    Image (std::string, int);
    Image (unsigned char *, int, int, int);
    size_t size();
    Image *to_gray();
    void save(std::string);
    void apply_filter(Filter);
};

Image::Image(std::string path, int req_comp = 0) {
  data = stbi_load(path.c_str(), &width, &height, &channels, req_comp);

  if (this->data == NULL) {
    std::cout << "error loading the image, data is null" << std::endl;
    exit(1);
  }
};

Image::Image(unsigned char *data, int width, int height, int channels) {
  this->width = width;
  this->height = height;
  this->channels = channels;
  this->data = data;
}

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

int main() {
  std::cout << "1" << std::endl;
  Image *img = new Image("ch.jpg");
  std::cout << "2" << std::endl;
  Image * gray_img = img->to_gray();
  std::cout << "3" << std::endl;
  gray_img->save("ch1.jpg");
  std::cout << "4" << std::endl;
}

