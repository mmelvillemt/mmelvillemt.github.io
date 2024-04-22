#include <cassert>
#include "Matrix.hpp"
#include <iostream>

using namespace std;

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {
  assert(0 < width && width <= MAX_MATRIX_WIDTH);
  assert(0 < height && height <= MAX_MATRIX_HEIGHT); 
  mat->width = width; 
  mat->height = height;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
  int height = mat->height; 
  int width = mat->width;
  os << width << " " << height << endl;
  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      os << *Matrix_at(mat, r, c) << " "; 
    }
    os << endl;
  }
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  int mwidth = mat->width;
  return mwidth;  
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  int mheight = mat->height;
  return mheight; 
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
  // finds the number of spaces between the element we want
  //and the first element in the matrix 
  int index = ptr - mat->data; 
  // returns int value, bascially if index is less than width 
  // then the row will be 0 , 
  // if greater by 1 times, will return 1 and so on
  int row = index / (mat->width); 

  return row; 
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
  // finds the number of spaces between the element we want 
  // and the first element in the matrix 
  int index = ptr - mat->data; 
  // returns remainder, representing the column of the element, 
  // ex. 15/10 returns 5, 
  // meaning the element is in column 5 
  int column = index % (mat->width); 

  return column; 
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
 assert((0 <= row && row < Matrix_height(mat)));
 assert((0 <= column) && (column < Matrix_width(mat)));
  
  int index = (row * mat->width) + column;
  int *ptr = &mat->data[index];
  return ptr; 
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  assert((0 <= row && row < Matrix_height(mat)));
  assert((0 <= column && column < Matrix_width(mat)));
  
  int index = (row * mat->width) + column;
  const int *ptr = &mat->data[index];
  return ptr; 
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  int rowsize = mat->width; 
  int height = mat->height;
  int *end = Matrix_at(mat, height-1, rowsize-1);  

  for(int *ptr = mat->data; ptr <= end; ptr++){
    *ptr = value; 
  }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  int rowsize = mat->width; 
  int height = mat->height;
  int *ptrlastrow = Matrix_at( mat, height-1 ,0); // ptr to first element in the last row 
  int *ptrlastcolumn = Matrix_at(mat,0,rowsize-1); // ptr to last element in row 0 
  int *ptrlastval = Matrix_at(mat,height-1,rowsize-1); 

// Setting rows 
  for(int *ptrrow0 = mat->data; ptrrow0 < ptrlastcolumn; ptrrow0++){ 
    *ptrrow0 = value; 
  }
  for(int *ptrrowend = ptrlastrow; ptrrowend <= ptrlastval; ptrrowend++){ 
   
   *ptrrowend = value; 
  }

// setting columns 
  for(int *ptrcol0 = mat->data; ptrcol0 < ptrlastrow; ptrcol0+= rowsize){ 
    *ptrcol0 = value; 
  } 
   for(int *ptrcolend = mat->data + rowsize -1; 
   ptrcolend < ptrlastval; ptrcolend+= rowsize){ 
    *ptrcolend = value; 
  } 
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  int rowsize = mat->width; 
  int height = mat->height;
  int const *end = Matrix_at(mat, height-1, rowsize-1);
 
  int maxval = *mat->data;   

  for(int const *ptr = mat->data; ptr <= end; ptr++){
    if(*ptr > maxval) { 
      maxval = *ptr; 
    }
  }
  return maxval;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));

  
  int const *end = Matrix_at(mat, row, column_end); // last value in region
 
  int minval = *Matrix_at(mat, row, column_start); 
  int const *minptr = Matrix_at(mat, row, column_start) ; 

  for(int const *ptr = minptr; ptr < end; ptr++){
    if(*ptr < minval) { 
      minval = *ptr;
      minptr = ptr; 

    }
  }
  int minValColumn = Matrix_column(mat, minptr);
  return minValColumn; 

}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
 assert(0 <= row && row < Matrix_height(mat));
 assert(0 <= column_start && column_end <= Matrix_width(mat));

  int min_val_column = Matrix_column_of_min_value_in_row
  (mat, row, column_start, column_end);

  int minval = *Matrix_at(mat,row,min_val_column);
  
  
  
  return minval; 

}







