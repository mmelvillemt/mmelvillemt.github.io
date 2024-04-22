#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <sstream>
using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);
  Matrix_print(mat,cout);
  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
    cout << endl;
  }

  delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.
TEST(test_print_basic) { 
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  // const int width = 3;
  // const int height = 5;
  // const int value = 42;
  Matrix_init(mat, 10, 4);
  Matrix_fill(mat, 69);
  Matrix_print(mat, cout);
  delete mat; 
}

TEST(test_matrix_print) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);

  *Matrix_at(mat, 0, 0) = 42;
  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}


TEST(test_border_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 5;
  const int height = 5;
  const int value = 3;
  Matrix_init(mat, width, height);
  Matrix_fill_border(mat, value);
  Matrix_print(mat,cout);

  for(int r = 0; r < height; r++){
    for(int c = 0; c < width; c++){ 
      if(r == 0 || r == height -1){ 
        ASSERT_EQUAL(*Matrix_at(mat,r,c),3);
      }
      if(c == 0 || c == width-1){ 
        ASSERT_EQUAL(*Matrix_at(mat,r,c),3); 
      }
    }
  } 

    
  

  delete mat; // delete the Matrix
}

TEST(test_border_edge) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 2;
  const int height = 2;
  const int value = 5;
  Matrix_init(mat, width, height);
  Matrix_fill_border(mat, value);
  Matrix_print(mat,cout);

  for(int r = 0; r < height; r++){
    for(int c = 0; c < width; c++){ 
      ASSERT_EQUAL(*Matrix_at(mat, r, c), 5); 
    }
  } 


  delete mat; // delete the Matrix
}


TEST(test_matrix_width) { 

  Matrix *mat = new Matrix; 
  Matrix_init(mat,7,9); 
  cout << Matrix_width(mat) << endl; 

  ASSERT_EQUAL(Matrix_width(mat), 7);

  delete mat;  
}

TEST(test_max_val) { 
  Matrix *mat = new Matrix; 
  Matrix_init(mat,7,9);
  Matrix_fill(mat, 5); 
  *Matrix_at(mat, 8 , 6) = 9; // sets value at (5,4) to 9 
  Matrix_print(mat, cout); 

 cout <<  Matrix_max(mat) << endl;

 ASSERT_EQUAL(Matrix_max(mat), 9);

 delete mat; 


}



TEST(test_min_val_column) { 
  Matrix *mat = new Matrix; 
  Matrix_init(mat,7,9);
  Matrix_fill(mat, 5); 
  *Matrix_at(mat, 6 , 4) = 1; // sets value at (6,4) to 1 
  Matrix_print(mat, cout); 

 cout <<  Matrix_column_of_min_value_in_row(mat, 6,0,6) << endl;

 ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 6, 0 ,6), 4); 

  delete mat; 
}

TEST(test_two_min_val_column) { 
  Matrix *mat = new Matrix; 
  Matrix_init(mat,7,9);
  Matrix_fill(mat, 5); 
  *Matrix_at(mat, 6 , 4) = 1; // sets value at (6,4) to 1 
  *Matrix_at(mat, 6 , 2) = 1; // sets value at (6,2) to 1 
  *Matrix_at(mat, 6 , 6) = 1; // sets value at (6,6) to 1 should exclude 
  Matrix_print(mat, cout); 

 cout <<  Matrix_column_of_min_value_in_row(mat, 6,0,6) << endl;

 ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 6, 0 ,6), 2); 

  delete mat; 
}

TEST(test_min_val_in_column) { 
  Matrix *mat = new Matrix; 
  Matrix_init(mat,5,5);
  Matrix_fill(mat, 3); 
  *Matrix_at(mat, 3 , 2) = 1; // sets value at (3,2) to 1 
  Matrix_print(mat, cout); 

 cout <<  Matrix_min_value_in_row(mat, 3,0,4) << endl;

 ASSERT_EQUAL(Matrix_min_value_in_row(mat, 3, 0 ,4), 1); 

  delete mat;
}

TEST(test_two_min_val_in_column) { 
  Matrix *mat = new Matrix; 
  Matrix_init(mat,7,11);
  Matrix_fill(mat, 3); 
  *Matrix_at(mat, 3 , 2) = 1; // sets value at (3,2) to 1 
  *Matrix_at(mat, 3 , 0) = 1; // sets value at (3,0) to 1
  *Matrix_at(mat, 3 , 4) = 0; // sets value at (3,4) to 0 
  Matrix_print(mat, cout); 

 cout <<  Matrix_min_value_in_row(mat, 3,0,4) << endl;

 ASSERT_EQUAL(Matrix_min_value_in_row(mat, 3, 0 ,4), 1); 

  delete mat;
}
// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
