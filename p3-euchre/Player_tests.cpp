#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_player_make_trump_1) { 
    Player * matt = Player_factory("Matt", "Simple"); 

    matt->add_card(Card(NINE, HEARTS));
    matt->add_card(Card(TEN, DIAMONDS));  
    matt->add_card(Card(ACE, SPADES)); 
    matt->add_card(Card(KING, CLUBS)); 
    matt->add_card(Card(JACK, SPADES));
    Suit trump; 
    bool order_up = matt->make_trump(Card(NINE,CLUBS), false, 1, trump);

    ASSERT_TRUE(order_up);
    ASSERT_EQUAL(trump, CLUBS);

    delete matt;   
} 

TEST(test_player_make_trump_2) { 
    Player * matt = Player_factory("Matt", "Simple"); 

    matt->add_card(Card(NINE, HEARTS));
    matt->add_card(Card(TEN, DIAMONDS));  
    matt->add_card(Card(ACE, SPADES)); 
    matt->add_card(Card(KING, CLUBS)); 
    matt->add_card(Card(JACK, SPADES));
    Suit trump; 
    bool order_up = matt->make_trump(Card(NINE,SPADES), false, 2, trump);

    ASSERT_TRUE(order_up);
    ASSERT_EQUAL(trump, CLUBS);  

    delete matt;
}

TEST(test_player_make_trump_pass_1) { 
    Player * matt = Player_factory("Matt", "Simple"); 

    matt->add_card(Card(NINE, HEARTS));
    matt->add_card(Card(TEN, DIAMONDS));  
    matt->add_card(Card(ACE, SPADES)); 
    matt->add_card(Card(KING, CLUBS)); 
    matt->add_card(Card(QUEEN, SPADES));
    Suit trump; 
    bool order_up = matt->make_trump(Card(NINE,CLUBS), false, 1, trump);

    ASSERT_FALSE(order_up); 

    delete matt; 
}

TEST(test_player_make_trump_pass_2) { 
    Player * matt = Player_factory("Matt", "Simple"); 

    matt->add_card(Card(NINE, HEARTS));
    matt->add_card(Card(TEN, DIAMONDS));  
    matt->add_card(Card(ACE, SPADES)); 
    matt->add_card(Card(KING, CLUBS)); 
    matt->add_card(Card(QUEEN, SPADES));
    Suit trump; 
    bool order_up = matt->make_trump(Card(NINE,DIAMONDS), false, 2, trump);

    ASSERT_FALSE(order_up); 

    delete matt; 
}

TEST(test_player_make_trump_dealer_1) { 
    Player * matt = Player_factory("Matt", "Simple"); 

    matt->add_card(Card(NINE, HEARTS));
    matt->add_card(Card(TEN, DIAMONDS));  
    matt->add_card(Card(ACE, SPADES)); 
    matt->add_card(Card(KING, CLUBS)); 
    matt->add_card(Card(QUEEN, SPADES));
    Suit trump; 
    bool order_up = matt->make_trump(Card(NINE,SPADES), true, 1, trump);

    ASSERT_TRUE(order_up); 
    ASSERT_EQUAL(trump, SPADES);

    delete matt; 
}

TEST(test_player_make_trump_dealer_screw) { 
    Player * matt = Player_factory("Matt", "Simple"); 

    matt->add_card(Card(NINE, HEARTS));
    matt->add_card(Card(TEN, DIAMONDS));  
    matt->add_card(Card(TEN, SPADES)); 
    matt->add_card(Card(TEN, CLUBS)); 
    matt->add_card(Card(TEN, HEARTS));
    Suit trump; 
    bool order_up = matt->make_trump(Card(NINE,SPADES), true, 2, trump);

    ASSERT_TRUE(order_up); 
    ASSERT_EQUAL(trump, CLUBS);

    delete matt; 
}

TEST(test_player_make_trump_dealer_pass) { 
    Player * matt = Player_factory("Matt", "Simple"); 

    matt->add_card(Card(NINE, HEARTS));
    matt->add_card(Card(TEN, DIAMONDS));  
    matt->add_card(Card(ACE, SPADES)); 
    matt->add_card(Card(KING, CLUBS)); 
    matt->add_card(Card(QUEEN, SPADES));
    Suit trump; 
    bool order_up = matt->make_trump(Card(NINE,CLUBS), true, 1, trump);

    ASSERT_FALSE(order_up); 
    
    delete matt; 
}

// ADD_DISCARD TESTS
TEST(test_player_add_discard_1) { 
    Player * matt = Player_factory("Matt", "Simple"); 

    matt->add_card(Card(NINE, HEARTS));
    matt->add_card(Card(NINE, DIAMONDS));  
    matt->add_card(Card(ACE, SPADES)); 
    matt->add_card(Card(NINE, CLUBS)); 
    matt->add_card(Card(QUEEN, SPADES));
    Card upcard(JACK, SPADES);
    Suit trump; 
    matt->make_trump(upcard, true, 1, trump);

    matt->add_and_discard(upcard); 

    Card led_card = matt->lead_card(trump);
    Card led_card2 = matt->lead_card(trump); 
    Card led_card3 = matt->lead_card(trump);
    Card led_card4 = matt->lead_card(trump);
    Card led_card5 = matt->lead_card(trump);

    ASSERT_EQUAL(led_card, Card(NINE,DIAMONDS));
    ASSERT_EQUAL(led_card2, Card(NINE,CLUBS));
    ASSERT_EQUAL(led_card3, Card(JACK,SPADES));
    ASSERT_EQUAL(led_card4, Card(ACE,SPADES));
    ASSERT_EQUAL(led_card5, Card(QUEEN,SPADES));


    delete matt; 
}

TEST(test_player_add_discard_all_trump) { 
    Player * matt = Player_factory("Matt", "Simple"); 

    matt->add_card(Card(QUEEN, SPADES));
    matt->add_card(Card(KING, SPADES));  
    matt->add_card(Card(ACE, SPADES)); 
    matt->add_card(Card(JACK, CLUBS)); 
    matt->add_card(Card(JACK, SPADES));
    Card upcard(TEN, SPADES);
    Suit trump; 
    matt->make_trump(upcard, true, 1, trump);

    matt->add_and_discard(upcard); 

    Card led_card = matt->lead_card(trump);
    Card led_card2 = matt->lead_card(trump); 
    Card led_card3 = matt->lead_card(trump);
    Card led_card4 = matt->lead_card(trump);
    Card led_card5 = matt->lead_card(trump);

    ASSERT_EQUAL(led_card, Card(JACK,SPADES));
    ASSERT_EQUAL(led_card2, Card(JACK,CLUBS));
    ASSERT_EQUAL(led_card3, Card(ACE,SPADES));
    ASSERT_EQUAL(led_card4, Card(KING,SPADES));
    ASSERT_EQUAL(led_card5, Card(QUEEN,SPADES));


    delete matt; 
}

TEST(test_player_add_discard_bowers) { 
    Player * matt = Player_factory("Matt", "Simple"); 

    matt->add_card(Card(NINE, HEARTS));
    matt->add_card(Card(ACE, DIAMONDS));  
    matt->add_card(Card(NINE, SPADES)); 
    matt->add_card(Card(JACK, DIAMONDS)); 
    matt->add_card(Card(JACK, HEARTS));
    Card upcard(NINE, DIAMONDS);
    Suit trump; 
    matt->make_trump(upcard, true, 1, trump);

    matt->add_and_discard(upcard); 

    Card led_card = matt->lead_card(trump); 
    Card led_card2 = matt->lead_card(trump); 
    Card led_card3 = matt->lead_card(trump);
    Card led_card4 = matt->lead_card(trump);
    Card led_card5 = matt->lead_card(trump);

    ASSERT_EQUAL(led_card, Card(NINE,HEARTS));
    ASSERT_EQUAL(led_card2, Card(JACK,DIAMONDS));
    ASSERT_EQUAL(led_card3, Card(JACK,HEARTS));
    ASSERT_EQUAL(led_card4, Card(ACE,DIAMONDS));
    ASSERT_EQUAL(led_card5, Card(NINE,DIAMONDS));

    delete matt; 
}

TEST(test_player_play_card_1) { 
    Player * matt = Player_factory("Matt", "Simple"); 

    matt->add_card(Card(NINE, HEARTS));
    matt->add_card(Card(TEN, DIAMONDS));  
    matt->add_card(Card(ACE, CLUBS)); 
    matt->add_card(Card(KING, DIAMONDS)); 
    matt->add_card(Card(QUEEN, DIAMONDS));
    Card upcard(ACE, DIAMONDS);
    Suit trump; 
    matt->make_trump(upcard, true, 1, trump);

    matt->add_and_discard(upcard);
    Card led_card(JACK, SPADES); 

    Card played_card = matt->play_card(led_card,trump); 

    ASSERT_EQUAL(played_card, Card(ACE,CLUBS));

    led_card = Card(JACK, DIAMONDS);

    played_card = matt->play_card(led_card,trump);

    ASSERT_EQUAL(played_card, Card(ACE,DIAMONDS));



    delete matt; 
}

TEST(test_player_play_card_no_suit) { 
    Player * matt = Player_factory("Matt", "Simple"); 

    matt->add_card(Card(NINE, SPADES));
    matt->add_card(Card(NINE, CLUBS));  
    matt->add_card(Card(ACE, SPADES)); 
    matt->add_card(Card(TEN, CLUBS)); 
    matt->add_card(Card(QUEEN, SPADES));
    Card upcard(TEN, HEARTS);
    Suit trump = HEARTS; 


    Card led_card(JACK, DIAMONDS); 

    Card played_card = matt->play_card(led_card,trump); 

    ASSERT_EQUAL(played_card, Card(NINE,SPADES));

    led_card = Card(JACK, CLUBS); 

    played_card = matt->play_card(led_card,trump); 
    ASSERT_EQUAL(played_card, Card(TEN,CLUBS));
    delete matt; 
}

TEST(test_player_play_card_bower_suit) { 
    Player * matt = Player_factory("Matt", "Simple"); 

    matt->add_card(Card(NINE, SPADES));
    matt->add_card(Card(ACE, DIAMONDS));  
    matt->add_card(Card(ACE, HEARTS)); 
    matt->add_card(Card(KING, CLUBS)); 
    matt->add_card(Card(QUEEN, SPADES));
    Card upcard(TEN, HEARTS);
    Suit trump = HEARTS; 


    Card led_card(JACK, DIAMONDS); 

    Card played_card = matt->play_card(led_card,trump); 

    ASSERT_EQUAL(played_card, Card(ACE,HEARTS));


    delete matt; 
}

TEST(test_player_play_card_lowest) { 
    Player * matt = Player_factory("Matt", "Simple"); 

    matt->add_card(Card(NINE, SPADES));
    matt->add_card(Card(NINE, DIAMONDS));  
    matt->add_card(Card(NINE, HEARTS)); 
    matt->add_card(Card(TEN, DIAMONDS)); 
    matt->add_card(Card(QUEEN, SPADES));
    Suit trump = CLUBS; 


    Card led_card(JACK, CLUBS); 

    Card played_card = matt->play_card(led_card,trump); 

    ASSERT_EQUAL(played_card, Card(NINE,SPADES));


    delete matt; 
}

TEST(test_player_play_card_bowers_compare) { 
    Player * matt = Player_factory("Matt", "Simple"); 

    matt->add_card(Card(NINE, SPADES));
    matt->add_card(Card(NINE, SPADES));  
    matt->add_card(Card(NINE, SPADES));
    matt->add_card(Card(JACK, CLUBS)); 
    matt->add_card(Card(JACK, SPADES));
    Suit trump = SPADES; 


    Card led_card(TEN, SPADES); 

    Card played_card = matt->play_card(led_card,trump); 

    ASSERT_EQUAL(played_card, Card(JACK,SPADES));

    led_card = Card(TEN, SPADES); 

    played_card = matt->play_card(led_card,trump); 

     ASSERT_EQUAL(played_card, Card(JACK,CLUBS));


    delete matt; 
}

TEST(test_player_play_card_lowest_suit) { 
    Player * matt = Player_factory("Matt", "Simple"); 

    matt->add_card(Card(NINE, SPADES));
    matt->add_card(Card(NINE, SPADES));  
    matt->add_card(Card(NINE, SPADES));
    matt->add_card(Card(JACK, CLUBS)); 
    matt->add_card(Card(JACK, SPADES));
    Suit trump = SPADES; 


    Card led_card(TEN, CLUBS); 

    Card played_card = matt->play_card(led_card,trump); 

    ASSERT_EQUAL(played_card, Card(NINE,SPADES));


    delete matt; 
}

TEST(test_player_play_card_trump_suit) { 
    Player * matt = Player_factory("Matt", "Simple"); 

    matt->add_card(Card(NINE, SPADES));
    matt->add_card(Card(JACK, CLUBS));  
    matt->add_card(Card(JACK, CLUBS));
    matt->add_card(Card(JACK, CLUBS)); 
    matt->add_card(Card(JACK, CLUBS));
    Suit trump = SPADES; 


    Card led_card(TEN, CLUBS); 

    Card played_card = matt->play_card(led_card,trump); 

    ASSERT_EQUAL(played_card, Card(NINE,SPADES));


    delete matt; 
}



// Add more tests here

TEST_MAIN()
