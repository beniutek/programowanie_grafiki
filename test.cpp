#include <iostream>
#include <string>
#include "image.h"
#include "filter.h"

int main() {
  std::cout << "START..." << std::endl;
  Image img = new Image("original.jpg");
  std::cout << "Image to gray" << std::endl;
  Image gray_img = img.to_gray();
  std::cout << "Save image" << std::endl;
  gray_img.save("gray.jpg");
  std::cout << "END..." << std::endl;

  int m[Filter::SIZE][Filter::SIZE] = {
    { 0, -1, 0 },
    { -1, 9, -1 },
    { 0, -1, 0 },
  };

  Filter *filter = new Filter(m);

  filter->show();
  // filter->apply_to(gray_img);
  std::cout << img.get_data()[0] << " ffff";
};
