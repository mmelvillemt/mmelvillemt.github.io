#include "Pack.hpp"
#include "unit_test_framework.hpp"

#include <iostream>
#include <fstream> 

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

TEST(test_pack_ctor_fin){ 
    ifstream pack_input("pack.in");

    Pack pack(pack_input);
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());

    Card second = pack.deal_one(); 
    ASSERT_EQUAL(TEN, second.get_rank());
    ASSERT_EQUAL(SPADES, second.get_suit());

    pack.reset(); 

    Card first2 = pack.deal_one(); 
    ASSERT_EQUAL(NINE, first2.get_rank());
    ASSERT_EQUAL(SPADES, first2.get_suit());
}

TEST(pack_shuffle_20){ 
    ifstream pack_input("pack.in"); 
    ifstream pack_in("pack.in");
    Pack pack(pack_input); 
    Pack packns(pack_in); 

    for(int i = 0; i < 20; i++){ 
        pack.shuffle(); 
    } 
    for(int i = 0; i < 24; i++){ 
        ASSERT_EQUAL(pack.deal_one(), packns.deal_one());  
    }

    ASSERT_TRUE(pack.empty()); 
    

}

TEST(pack_reset){ 
    ifstream pack_input("pack.in"); 
    Pack pack(pack_input);

    ASSERT_EQUAL(pack.deal_one(), Card(NINE,SPADES)); 
    pack.reset(); 
    ASSERT_EQUAL(pack.deal_one(), Card(NINE,SPADES)); 
}



TEST_MAIN()
