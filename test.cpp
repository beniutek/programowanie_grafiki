#include <iostream>
#include <string>
#include "image.h"
#include "filter.h"

int main() {
  std::cout << "START..." << std::endl;
  // Image img = new Image("original.jpg");
  Image img = new Image("lenna.jpg");
  std::cout << "Image to gray" << std::endl;
  Image gray_img = img.to_gray();
  std::cout << "Save image" << std::endl;
  gray_img.save("gray.jpg");

  int m_sharp[Filter::SIZE][Filter::SIZE] = {
    { 0, -1, 0 },
    { -1, 5, -1 },
    { 0, -1, 0 },
  };

  int m_box[Filter::SIZE][Filter::SIZE] = {
    { 0, -1, 0 },
    { -1, 5, -1 },
    { 0, -1, 0 },
  };

  Filter *sharp_filter = new Filter(m_sharp);
  // Filter *filter = new Filter(m_box);

  sharp_filter->show();
  Image sharp_img = sharp_filter->apply_to(gray_img);
  sharp_img.save("filtered.jpg");
  std::cout << "END..." << std::endl;
};
