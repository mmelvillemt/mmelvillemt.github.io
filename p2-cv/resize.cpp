#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <cassert>
#include <string>
#include "Image.hpp"
#include "Matrix.hpp"
#include "processing.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  if(argc < 4 || argc > 5){
    cout << "Usag: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n" 
    << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
  }
  
  string inFile = argv[1];
  string outFile = argv[2];

  ifstream fin(inFile);
  ofstream fout(outFile);
  if(!fin.is_open()){
    cout << "Error opening file: " << inFile << endl;
    return 1;
  }
  if (!fout.is_open()) {
    cout << "Error opening file:  " << outFile << endl;
    return 1;
  }

  Image *img = new Image;
  Image_init(img, fin);

  int width = atoi(argv[3]);
  int height;
  if(argc == 4){
    height = Image_height(img);
  }else if(argc == 5){
    height = atoi(argv[4]);
  }

  if(width <= 0 || width >  Image_width(img)){
      cout << "Usag: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n" 
    << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
  }

   if(height <= 0 || height > Image_height(img)){
    cout << "Usag: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n" 
    << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
  }

  seam_carve(img, width, height);
  Image_print(img, fout);

  fin.close();
  fout.close();

  delete img;
}

