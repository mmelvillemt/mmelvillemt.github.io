#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <sstream>

using namespace std;
// Tests functs on an empty tree
TEST(test_empty_true) {
    BinarySearchTree<int> b; 

    ASSERT_TRUE(b.empty()); 
    ASSERT_EQUAL(b.size(), 0); 
    ASSERT_EQUAL(b.height(), 0); 
    BinarySearchTree<int> c = b; 
    ASSERT_TRUE(c.empty()); 
    ASSERT_EQUAL(c.size(), 0); 
    ASSERT_EQUAL(c.height(), 0); 
    ASSERT_EQUAL(b.find(6),b.end());
    ASSERT_EQUAL(b.max_element(), b.end());  
    ASSERT_EQUAL(b.min_element(), b.end()); 
    ASSERT_TRUE(b.check_sorting_invariant()); 
    ASSERT_EQUAL(b.min_greater_than(6), b.end()); 
}

TEST(test_min_max_full) { 
    BinarySearchTree<int> b; 

    b.insert(6);
    b.insert(12);
    b.insert(3);
    b.insert(10);



    ASSERT_FALSE(b.empty()); 
    ASSERT_EQUAL(b.size(), 4); 
    ASSERT_EQUAL(b.height(), 3); 
    ASSERT_EQUAL(*(b.max_element()), 12); 
    ASSERT_EQUAL(*(b.min_element()), 3);
    ASSERT_TRUE(b.check_sorting_invariant());
    ASSERT_EQUAL(*(b.min_greater_than(5)), 6);


    
}
TEST(test_min_max_one) { 
    BinarySearchTree<int> b; 

    b.insert(6);




    ASSERT_FALSE(b.empty()); 
    ASSERT_EQUAL(b.size(), 1); 
    ASSERT_EQUAL(b.height(), 1); 
    ASSERT_EQUAL(*(b.max_element()), 6); 
    ASSERT_EQUAL(*(b.min_element()), *(b.max_element()) );


    
}

TEST(test_break_invar) { 
    BinarySearchTree<int> b;
    b.insert(1);
    b.insert(0);
    // change first datum to 2, resulting in the first broken tree above
    *b.begin() = 2;
    ASSERT_FALSE(b.check_sorting_invariant());

}

TEST(test_inorder){
    BinarySearchTree<int> b;

    b.insert(10); 
    b.insert(17); 
    b.insert(5); 
    b.insert(12); 
    b.insert(6); 

   ostringstream oss_inorder;
  b.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "5 6 10 12 17 ");
}

TEST(test_inorder_empty){
    BinarySearchTree<int> b;


   ostringstream oss_inorder;
  b.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "");
}

TEST(test_preorder){
    BinarySearchTree<int> b;

    b.insert(10); 
    b.insert(17); 
    b.insert(5); 
    b.insert(12); 
    b.insert(6); 

   ostringstream oss_preorder;
  b.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "10 5 6 17 12 ");
}

TEST(test_preorder_empty){
    BinarySearchTree<int> b;


   ostringstream oss_preorder;
  b.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "");
}

TEST(test_copy_full){ 
    BinarySearchTree<int> b;

    b.insert(10); 
    b.insert(17); 
    b.insert(5); 
    b.insert(12); 
    b.insert(6); 
    BinarySearchTree<int> c = b; 

   ostringstream oss_inorder;
  c.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "5 6 10 12 17 ");

}

TEST(test_find) { 
    BinarySearchTree<int> b;

    b.insert(10); 
    b.insert(17); 
    b.insert(5); 
    b.insert(12); 
    b.insert(6); 

    ASSERT_EQUAL(*(b.find(5)), 5);
    ASSERT_EQUAL(*(b.find(10)), 10);
    ASSERT_EQUAL(*(b.find(17)), 17); 
    ASSERT_EQUAL(*(b.find(12)), 12);
    ASSERT_EQUAL(*(b.find(6)), 6);
    ASSERT_EQUAL((b.find(25)), b.end());
    cout<< b.to_string(); 
}


TEST(test_min_greater_than_special){ 
    BinarySearchTree<int> b;

    b.insert(3); 
    b.insert(1); 
    b.insert(2);

    ASSERT_EQUAL(*(b.min_greater_than(1)),2);
    ASSERT_EQUAL(*(b.min_greater_than(2)),3);  
    ASSERT_EQUAL((b.min_greater_than(4)),b.end());  
}



TEST_MAIN()
