#include <iostream>
#include <string>
#include "image.h"
#include "filter.h"

int main(int argc, char* argv[]) {
  std::string filename = (std::string)argv[1] + ".jpg";
  std::string filtername = (std::string)argv[2];
  bool operate_on_gray = !!argv[3];
  std::cout << "START..." << std::endl;
  std::cout << "Searching for jpg file: " << argv[1] << ".jpg" << std::endl;
  Image img = new Image(filename);
  Filter *filter;

  if (filtername == "sharp") {
    int m_sharp[Filter::SIZE][Filter::SIZE] = {
      { 0, -1, 0 },
      { -1, 5,-1 },
      { 0, -1, 0 },
    };
    filter = new Filter(m_sharp);
  }

  if (filtername == "box_blur") {
    int m_box_blur[Filter::SIZE][Filter::SIZE] = {
      { 1, 1, 1 },
      { 1, 1, 1 },
      { 1, 1, 1 },
    };
    filter = new Filter(m_box_blur, 9);
  }

  if (filtername == "edge") {
    int m_edge[Filter::SIZE][Filter::SIZE] = {
      { -1, -1, -1 },
      { -1,  8, -1 },
      { -1, -1, -1 },
    };
    filter = new Filter(m_edge);
  }

  std::cout << "Filtering..." << std::endl;
  filter->show();
  std::cout << "after show" << std::endl;

  if (operate_on_gray) {
    std::cout << "Image to gray" << std::endl;
    Image gray_img = img.to_gray();
    std::cout << "Save image" << std::endl;
    gray_img.save("gray.jpg");
    Image sharp_img = filter->apply_to(gray_img);
    std::cout << "Filter applied, saving"<< std::endl;
    sharp_img.save("filtered.jpg");
  } else {
    Image sharp_img = filter->apply_to(img);
    std::cout << "Filter applied, saving"<< std::endl;
    sharp_img.save("filtered.jpg");
  }

  std::cout << "END..." << std::endl;
  return 0;
};
