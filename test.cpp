#include <iostream>
#include <string>
#include "image.h"
#include "filter.h"

int main(int argc, char* argv[]) {
  std::string filename = (std::string)argv[1] + ".jpg";
  std::string filtername = (std::string)argv[2];
  std::cout << "START..." << std::endl;
  std::cout << "Searching for jpg file: " << argv[1] << ".jpg" << std::endl;
  Image img = new Image(filename);
  std::cout << "Image to gray" << std::endl;
  Image gray_img = img.to_gray();
  std::cout << "Save image" << std::endl;
  gray_img.save("gray.jpg");

  int m_sharp[Filter::SIZE][Filter::SIZE] = {
    { 0, -1, 0 },
    { -1, 5,-1 },
    { 0, -1, 0 },
  };

  int m_box_blur[Filter::SIZE][Filter::SIZE] = {
    { 1, 1, 1 },
    { 1, 1, 1 },
    { 1, 1, 1 },
  };

  int m_edge[Filter::SIZE][Filter::SIZE] = {
    { -1, -1, -1 },
    { -1,  8, -1 },
    { -1, -1, -1 },
  };


  Filter *filter;

  if (filtername == "sharp") {
    filter = new Filter(m_sharp);
  }

  if (filtername == "box_blur") {
    filter = new Filter(m_box_blur, 9);
  }

  if (filtername == "edge") {
    filter = new Filter(m_edge);
  }

  filter->show();
  Image sharp_img = filter->apply_to(img);
  sharp_img.save("filtered.jpg");
  std::cout << "END..." << std::endl;
};
