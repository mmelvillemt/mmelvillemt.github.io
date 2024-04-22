#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <fstream> 

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);
  Image_print(img, cout); 

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

TEST(test_image_width_height) {
  Image *img = new Image; // create an Image in dynamic memory
  int width = 5; 
  int height = 6; 

  Image_init(img, width, height); 

  ASSERT_EQUAL(Image_width(img) , width);
  ASSERT_EQUAL(Image_height(img), height);  


  

  delete img; // delete the Image
}


TEST(test_image_get_set) {
  Image *img = new Image; // create an Image in dynamic memory
  
  Image_init(img, 2, 2);

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_set_pixel(img, 0 , 0, red);
  Image_set_pixel(img, 0 , 1, green);
  Image_set_pixel(img, 1 , 0, blue); 
  Image_set_pixel(img, 1 , 1, white);

  assert(Pixel_equal(Image_get_pixel(img, 0, 0), red));
  assert(Pixel_equal(Image_get_pixel(img, 0, 1), green)); 
  assert(Pixel_equal(Image_get_pixel(img, 1, 0), blue));
  assert(Pixel_equal(Image_get_pixel(img, 1, 1), white));



  

  delete img; // delete the Image
}




TEST(test_image_fill) {
  Image *img = new Image; // create an Image in dynamic memory
  
  const Pixel pix = {100, 45 , 3}; 
  int width = 3; 
  int height = 3; 

  Image_init(img, width, height); 

  Image_fill(img, pix); 

  for(int r=0; r < height; r++){
    for(int c = 0; c < width; c++ ) {
      Image_get_pixel(img, r, c); 
      ASSERT_EQUAL(pix.r, 100);
      ASSERT_EQUAL(pix.g, 45);
      ASSERT_EQUAL(pix.b, 3); 

      

    }
  }
 



  

  delete img; // delete the Image
}

TEST(test_input){ 
  Image *img = new Image; 

  string file = "dog.ppm";
  ifstream fin(file); 

  Image_init(img, fin);
  // Image_print(img,cout); 

  // Capture our output
  ostringstream s;
  Image_print(img, s);
  Image_print(img, cout); 

  // Correct output
  ostringstream correct;
  correct << "P3\n5 5\n255\n";
  correct << "0 0 0 0 0 0 255 255 250 0 0 0 0 0 0 \n";
  correct << "255 255 250 126 66 0 126 66 0 126 66 0 255 255 250 \n";
  correct << "126 66 0 0 0 0 255 219 183 0 0 0 126 66 0 \n";
  correct << "255 219 183 255 219 183 0 0 0 255 219 183 255 219 183 \n";
  correct << "255 219 183 0 0 0 134 0 0 0 0 0 255 219 183 \n";
  ASSERT_EQUAL(s.str(), correct.str());
  



  fin.close(); 
  delete img; 

}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
