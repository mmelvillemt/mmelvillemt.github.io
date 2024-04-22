#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_ctor_1) {
    List<int> list; 
    ASSERT_TRUE(list.empty());
}

TEST(test_size_init) { 
    List<int> list; 
    ASSERT_EQUAL(list.size(), 0);
    list.push_back(5);
    ASSERT_FALSE(list.empty());  
    ASSERT_EQUAL(list.size(), 1);
}

TEST(test_front_1){ 
    List<int> list; 
    list.push_front(25); 
    ASSERT_EQUAL(list.size(), 1 ); 
    ASSERT_EQUAL(list.front(), 25); 
    ASSERT_EQUAL(list.back(), list.front()); 
}

//Testing push with multiple additions along with front and back 
TEST(test_front_multiple){ 
    List<int> list; 
    list.push_front(65); 
    list.push_front(2); 
    list.push_front(3); 
    list.push_front(99); 
    list.push_front(12); 
    ASSERT_EQUAL(list.size(), 5 ); 
    auto i = list.begin(); 
    for(List<int>::Iterator ptr = list.begin(); ptr != list.end(); ++ptr){
        ASSERT_EQUAL(*ptr, *i); 
        ++i; 
    } 
    ASSERT_EQUAL(list.front(), 12); 
    ASSERT_EQUAL(list.back(), 65);
 

}

TEST(test_push_back) { 
    List<int> list; 

    list.push_back(2); 
    list.push_back(17); 
    list.push_back(78); 
    list.push_back(100); 
    list.push_back(-7); 

    ASSERT_EQUAL(list.front(), 2); 
    ASSERT_EQUAL(list.back(), -7); 
    ASSERT_EQUAL(list.size(), 5); 

}


TEST(test_push_f_b) { 
    List<int> list; 

    list.push_back(2); 
    list.push_front(17); 
    list.push_front(78); 
    list.push_back(100); 
    list.push_front(-7); 

    ASSERT_EQUAL(list.front(), -7); 
    ASSERT_EQUAL(list.back(), 100); 


}

TEST(test_pop_front_1) { 
    List<int> list; 

    list.push_front(78);
    ASSERT_EQUAL(list.size(), 1); 
    list.pop_front(); 
    ASSERT_TRUE(list.empty()); 
}

TEST(test_pop_front_many){
    List<int> list; 

    list.push_back(2); 
    list.push_back(17); 
    list.push_back(78); 
    list.push_back(100); 
    list.push_back(-7);

    list.pop_front(); 
    ASSERT_EQUAL(list.front(),17)
    ASSERT_EQUAL(list.size(), 4); 
    

}

TEST(test_pop_back_1) { 
    List<int> list; 

    list.push_front(78);
    ASSERT_EQUAL(list.size(), 1); 
    list.pop_back(); 
    ASSERT_TRUE(list.empty()); 
}

TEST(test_pop_back_many){
    List<int> list; 

    list.push_back(2); 
    list.push_back(17); 
    list.push_back(78); 
    list.push_back(100); 
    list.push_back(-7);

    list.pop_back(); 
    ASSERT_EQUAL(list.back(), 100)
    ASSERT_EQUAL(list.size(), 4); 
    list.pop_back(); 
    ASSERT_EQUAL(list.back(), 78)
    ASSERT_EQUAL(list.size(), 3); 

}

TEST(test_pop_b_f){
    List<int> list; 

    list.push_back(2); 
    list.push_back(100);
    list.push_back(17); 
    list.push_back(78); 

    list.pop_back(); 
    ASSERT_EQUAL(list.back(), 17)
    ASSERT_EQUAL(list.size(), 3); 
    list.pop_front(); 
    ASSERT_EQUAL(list.front(), 100)
    ASSERT_EQUAL(list.size(), 2); 
    list.pop_front(); 
    ASSERT_EQUAL(list.back(), 17)
    ASSERT_EQUAL(list.size(), 1); 
    list.pop_back(); 
    ASSERT_TRUE(list.empty());

}

TEST(test_equals_op){ 
    List<int> list; 
    List<int> copy; 

    list.push_back(2); 
    list.push_back(17); 
    list.push_back(78); 
    list.push_back(100); 
    list.push_back(-7);
    //2,17,78,100,-7

    copy = list; 
    auto i = copy.begin(); 
    for(List<int>::Iterator ptr = list.begin(); ptr != list.end(); ++ptr){
        ASSERT_EQUAL(*ptr, *i); 
        ++i; 
    } 
    ASSERT_EQUAL(copy.front(), list.front()); 
    ASSERT_EQUAL(copy.back(), list.back()); 

}

TEST(test_equals_same) {
    List<int> list; 

    list.push_back(2); 
    list.push_back(17); 
    list.push_back(78); 
    list.push_back(100); 
    list.push_back(-7);

    list = list;
    auto i = list.begin();

    for(List<int>::Iterator ptr = list.begin(); ptr != list.end(); ++ptr){
        ASSERT_EQUAL(*ptr, *i); 
        ++i; 
    }  
    ASSERT_EQUAL(list.front(), list.front()); 
    ASSERT_EQUAL(list.back(), list.back()); 


}


// 12/21

// ITERATOR TESTS 

TEST(test_operator_plus_minus) {
    List<int> list; 

    list.push_back(2); 
    list.push_back(17); 
    list.push_back(78); 
    list.push_back(100); 
    list.push_back(-7);

    auto i = list.begin(); 
    ++i; 
    ASSERT_EQUAL(*i, 17); 
    ++i; 
    ++i; 
    --i; 
    ASSERT_EQUAL(*i, 78);
}

TEST(test_operator_equality) {
    List<int> list; 

    list.push_back(2); 
    list.push_back(17); 
    list.push_back(78); 
    list.push_back(100); 
    list.push_back(-7);

    auto i = list.begin(); 
    ++i;
    auto j = list.begin(); 
    ++j; 
    ASSERT_TRUE( j == i); 
    ASSERT_FALSE (j != i); 
    ++j; 
    ASSERT_FALSE(i == j); 
    ASSERT_TRUE( j!=i); 

    
}



TEST(test_erase_front) {
    List<int> list; 

    list.push_back(2); 
    list.push_back(17); 
    list.push_back(78); 
    list.push_back(100); 
    list.push_back(-7);
    auto i = (list.begin()); 

    list.erase(i); 
    ASSERT_EQUAL(list.front(), 17);  


}

TEST(test_erase_back) {
    List<int> list; 

    list.push_back(2); 
    list.push_back(17); 
    list.push_back(78); 
    list.push_back(100); 
    list.push_back(-7);
    auto i = (list.begin()); 
    ++i; 
    ++i;
    ++i;
    ++i;

    list.erase(i); 
    ASSERT_EQUAL(list.back(), 100);  


}

TEST(test_erase) {
    List<int> list; 

    list.push_back(2); 
    list.push_back(17); 
    list.push_back(78);  
    list.push_back(100); 
    list.push_back(-7); 
    auto i = list.begin(); 
    ++i; 
    ++i; 
    

    list.erase(i); 
    auto j = list.begin(); 
    ++j; 
    ++j; 
    ++j;
    ASSERT_EQUAL(*j, -7);  


}

TEST(test_insert) {
    List<int> list; 

    list.push_back(2); 
    list.push_back(17); 
    list.push_back(78);  
    list.push_back(100); 
    list.push_back(-7); 
    auto i = list.begin(); 
    ++i; 
    ++i; 
    

    list.insert(i, -4); 

    auto j = list.begin(); 
    ++j; 
    ++j; 
    ASSERT_EQUAL(*j, -4);  


}
// checks that iterator still points to the same element after insertion 
TEST(test_iterator_same_point) {
    List<int> list; 

    list.push_back(2); 
    list.push_back(17); 
    list.push_back(78);  
    list.push_back(100); 
    list.push_back(-7); 
    auto i = list.begin(); 
    ++i; 
    ++i; 
    // 2,17,78,100,-7
    // i points to 78
    

    list.insert(i, -4); 
    // 2,17,-4,78,100,-7
    auto j = list.begin(); 
    ++j; 
    ++j; 
    // j points to -4
    ASSERT_EQUAL(list.size(), 6); 
    ASSERT_EQUAL(*j, -4); 
    ASSERT_EQUAL(*i, 78);

    auto k = list.begin(); // k points to 2
    list.erase(k); 
    // 17,-4,78,100,-7
    ASSERT_EQUAL(list.front(), 17);
    ASSERT_EQUAL(list.size(), 5); 
    ASSERT_EQUAL(*j, -4); 
    ASSERT_EQUAL(*i, 78);

    list.clear(); 
    ASSERT_TRUE(list.empty()); 
}

TEST(test_iterator_plus_end) { 
    List<int> list;

    list.push_back(2); 
    list.push_back(17); 
    list.push_back(78);  
    list.push_back(100); 
    list.push_back(-7); 
    auto i = list.begin(); 
    ++i; //17
    ++i; //78
    ++i; //100 
    ++i; // -7 
    ASSERT_EQUAL(*i, -7); 
    ++i; // past end (null)
    ASSERT_EQUAL(i,list.end()); 



}

TEST(test_iterator_minus_begin) { 
    List<int> list;

    list.push_back(2); 
    list.push_back(17); 
    list.push_back(78);  
    list.push_back(100); 
    list.push_back(-7); 
    auto i = list.begin(); 
    ASSERT_EQUAL(*i, 2); 
    --i; // before start (null)
    ASSERT_EQUAL(i,list.end()); 



}

TEST(test_popf_1_same) { 
    List<int> list; 

    list.push_back(-5);
    list.push_back(90); 

    list.pop_front(); 
    ASSERT_EQUAL(list.front(),90);
    ASSERT_EQUAL(list.front(), list.back()); 

}

TEST(test_popb_1_same) { 
    List<int> list; 

    list.push_back(-5);
    list.push_back(90); 

    list.pop_back(); 
    ASSERT_EQUAL(list.front(),-5);
    ASSERT_EQUAL(list.front(), list.back()); 

}



// TEST INSERT FUNCTIONS
TEST(test_insert_end) { 
    List<int> list;

    list.push_back(2); 
    list.push_back(17); 
    list.push_back(78);  
    list.push_back(100); 
    list.push_back(-7);

    auto i = list.end(); 

    list.insert(i,69); 

    ASSERT_EQUAL(list.back(), 69); 



}


TEST(test_insert_empty) { 
    List<int> list;

    auto i = list.end(); 

    list.insert(i,69); 

    ASSERT_EQUAL(list.back(), 69);
    ASSERT_EQUAL(list.back(), list.front()); 




}

TEST(test_insert_last) { 
    List<int> list;

    list.push_back(2); 
    list.push_back(17); 
    list.push_back(78);  
    list.push_back(100); 
    list.push_back(-7);

    auto i = list.begin();
    ++i;
    ++i; 
    ++i; 
    ++i; 
    list.insert(i,69); 

    ASSERT_EQUAL(list.back(), -7);
    ASSERT_EQUAL(*i, -7);
    --i;
    ASSERT_EQUAL(*i, 69);




}





TEST_MAIN()
