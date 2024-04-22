#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_card_get_suit_trump_bower){
    Card c1(JACK, DIAMONDS); 
    Card c2(JACK, HEARTS); 
    Card c3(JACK, CLUBS); 
    Card c4(JACK, SPADES); 

    ASSERT_EQUAL(HEARTS, c1.get_suit(HEARTS));
    ASSERT_EQUAL(DIAMONDS, c2.get_suit(DIAMONDS));
    ASSERT_EQUAL(SPADES, c3.get_suit(SPADES));
    ASSERT_EQUAL(CLUBS, c4.get_suit(CLUBS));
    


}
// Tests functions with no left bower but a jack 
TEST(test_card_get_suit_trump_bower_2){
    Card c1(JACK, DIAMONDS); 
    Card c2(JACK, HEARTS); 
    Card c3(JACK, CLUBS); 
    Card c4(JACK, SPADES); 

    ASSERT_EQUAL(DIAMONDS, c1.get_suit(DIAMONDS));
    ASSERT_EQUAL(HEARTS, c2.get_suit(HEARTS));
    ASSERT_EQUAL(CLUBS, c3.get_suit(CLUBS));
    ASSERT_EQUAL(SPADES, c4.get_suit(SPADES));
    


}

TEST(test_face_or_ace){
    Card j(JACK, DIAMONDS);
    Card q(QUEEN, CLUBS); 
    Card k(KING, HEARTS); 
    Card a(ACE, SPADES);
    Card t; 

    ASSERT_TRUE(j.is_face_or_ace()); 
    ASSERT_TRUE(q.is_face_or_ace());
    ASSERT_TRUE(k.is_face_or_ace());
    ASSERT_TRUE(a.is_face_or_ace());
    ASSERT_FALSE(t.is_face_or_ace());
}

TEST(test_is_right_bower){
    Card rb(JACK,CLUBS); 
    Card lb(JACK,SPADES);
    Card t; 

    ASSERT_TRUE(rb.is_right_bower(CLUBS)); 
    ASSERT_FALSE(lb.is_right_bower(CLUBS)); 
    ASSERT_FALSE(t.is_right_bower(CLUBS)); 


}

TEST(test_is_left_bower){
    Card rb(JACK,CLUBS); 
    Card lb(JACK,SPADES);
    Card rj(JACK, HEARTS); 
    Card t; 

    ASSERT_FALSE(rb.is_left_bower(CLUBS)); 
    ASSERT_TRUE(lb.is_left_bower(CLUBS)); 
    ASSERT_FALSE(t.is_left_bower(CLUBS)); 
    ASSERT_FALSE(rj.is_left_bower(HEARTS));


}

TEST(test_is_trump){
    Card rb(JACK,CLUBS); 
    Card lb(JACK,SPADES);
    Card five(FIVE,CLUBS); 
    Card rseven(SEVEN, HEARTS);  

    ASSERT_TRUE(rb.is_trump(CLUBS)); 
    ASSERT_TRUE(lb.is_trump(CLUBS)); 
    ASSERT_TRUE(five.is_trump(CLUBS)); 
    ASSERT_FALSE(rseven.is_trump(SPADES)); 


}

TEST(test_card_input) {
    istringstream iss("Seven of Hearts");
    istringstream iss2("Jack of Diamonds");
    Card c;
    Card d; 
    iss >> c;
    iss2 >> d;
    ASSERT_EQUAL(c.get_suit(), HEARTS);
    ASSERT_EQUAL(c.get_rank(), SEVEN);
    ASSERT_EQUAL(d.get_suit(), DIAMONDS);
    ASSERT_EQUAL(d.get_rank(), JACK); 
}

TEST(test_card_output) { 
    Card c(NINE, DIAMONDS); 
    cout << c << endl;  

    ostringstream oss;
    oss << c;
    ASSERT_EQUAL(oss.str(), "Nine of Diamonds");



}

TEST(test_less_than) { 
    Card lhs(KING, CLUBS); 
    Card rhs(SEVEN, DIAMONDS); 
    
    ASSERT_FALSE(lhs < rhs); 
}

TEST(test_less_than_edge) { 
    Card lhs(KING, CLUBS); 
    Card rhs(KING, DIAMONDS); 
    
    ASSERT_TRUE(lhs < rhs); 
}

TEST(test_greater_than) { 
    Card lhs(QUEEN, SPADES); 
    Card rhs(SEVEN, HEARTS); 
    
    ASSERT_TRUE(lhs > rhs); 
}

TEST(test_greater_than_edge) { 
    Card lhs(QUEEN, CLUBS); 
    Card rhs(QUEEN, HEARTS); 
    
    ASSERT_TRUE(lhs > rhs); 
}

TEST(test_less_equal) { 
    Card lhs(KING, CLUBS); 
    Card rhs(SEVEN, DIAMONDS); 
    Card lhs2(JACK, HEARTS); 
    Card rhs2(JACK,HEARTS); 
    ASSERT_FALSE(lhs <= rhs); 
    ASSERT_TRUE(lhs2 <= rhs2); 
}

TEST(test_less_equal_edge) { 
    Card lhs(KING, CLUBS); 
    Card rhs(KING, DIAMONDS); 
    
    ASSERT_TRUE(lhs <= rhs); 
}

TEST(test_greater_equal) { 
    Card lhs(QUEEN, SPADES); 
    Card rhs(SEVEN, HEARTS);
    Card lhs2(JACK, SPADES); 
    Card rhs2(JACK, SPADES); 
    
    ASSERT_TRUE(lhs > rhs); 
    ASSERT_TRUE(lhs >= rhs); 
}

TEST(test_greater_equal_edge) { 
    Card lhs(QUEEN, CLUBS); 
    Card rhs(QUEEN, HEARTS); 
    
    ASSERT_TRUE(lhs >= rhs); 
}

TEST(test_suit_next) {
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES); 
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS); 
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS); 
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS); 
}

TEST(test_card_less) { 
    Card rb(JACK, SPADES); 
    Card lb(JACK,CLUBS); 
    Card ace(ACE, SPADES); 
    Card n(NINE, SPADES); 
    Card oj(JACK, HEARTS); 

    ASSERT_TRUE(Card_less(lb,rb,SPADES)); 
    ASSERT_TRUE(Card_less(ace,lb,SPADES)); 
    ASSERT_TRUE(Card_less(ace,rb,SPADES)); 
    ASSERT_TRUE(Card_less(n,rb,SPADES)); 
    ASSERT_TRUE(Card_less(oj,n,SPADES)); 

}

TEST(test_card_less_led) { 
    Card js(JACK, SPADES); 
    Card as(ACE, SPADES);

    Card nd(NINE, DIAMONDS); 
    Card nh(NINE, HEARTS); 

    

    ASSERT_TRUE(Card_less(js,as,as,HEARTS)); 
    ASSERT_TRUE(Card_less(js,as,as,HEARTS)); 

    ASSERT_TRUE(Card_less(nh,nd,as,SPADES));
    ASSERT_FALSE(Card_less(nd,nh,as,SPADES));
    
    

}





// Add more test cases here

TEST_MAIN()
