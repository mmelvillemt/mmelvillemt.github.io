#include "Player.hpp"
#include <cassert>
#include <string> 
#include <array>
#include <vector> 
#include <iostream>
#include <algorithm>




class SimplePlayer : public Player {
    public:  
  
    // CTOR 
    SimplePlayer(std::string name): Player() {
        player_name = name;
        hand_size = 0;
    }


  //EFFECTS returns player's name
  const std::string & get_name() const override{
    return player_name; 
  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  void add_card(const Card &c) override{
    if(hand_size < MAX_HAND_SIZE){ 
        hand.push_back(c); 
        hand_size = hand_size + 1; 
    }
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump(const Card &upcard, bool is_dealer, int round, 
                    Suit &order_up_suit) const override{
    int count = 0; 
    Suit trump = upcard.get_suit();
      
    if(round == 1){
        for(int i = 0; i < MAX_HAND_SIZE; i++){
            if(hand[i].is_face_or_ace() && hand[i].is_trump(trump)){ 
                count = count + 1; 
            }  
        }
        if(count >= 2){
            order_up_suit = trump; 
            return true; 
        } else{ 
            return false; 
        }
    }

    if(round == 2 && !(is_dealer)){ 
        for(int i = 0; i < MAX_HAND_SIZE; i++){
            if(hand[i].is_face_or_ace() && (hand[i].get_suit() == Suit_next(trump))){ 
                order_up_suit = Suit_next(trump); 
                return true;  
            }
        } 
        return false;   
    }
    order_up_suit = Suit_next(trump); 
    return true; 
    
}

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard) override{
    Card lc = hand[0];
    int index = 0;  
    Suit trump = upcard.get_suit();
    for(int i = 1; i < MAX_HAND_SIZE; i++){
        if(Card_less(hand[i], lc, trump)) {
            lc = hand[i];
            index = i;  
        }
    }
    if(Card_less(lc, upcard, trump)){
        hand[index] = upcard; 
    }

  }

  //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(Suit trump) override{
    if(hand_size < 1){
        assert(false);
    }
    int num_trump = 0;
    Card max_trump;
    Card max_not_trump;
    int index_trump = 0;
    int index_not_trump = 0;  
    for(int i = 0; i < hand_size; ++i){
        if(hand[i].is_trump(trump)){ 
            num_trump++;
            if(Card_less(max_trump, hand[i], trump)){
                max_trump = hand[i];
                index_trump = i;
            }
        }else { 
            if(max_not_trump < hand[i]){
                max_not_trump = hand[i];
                index_not_trump = i;  
            }
        }
    }
    if(num_trump == hand_size){
        hand.erase(hand.begin() + index_trump);
        hand_size = hand_size - 1;
        return max_trump;
    } else{
        hand.erase(hand.begin() + index_not_trump);
        hand_size = hand_size - 1;
        return max_not_trump;
    }
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  Card play_card(const Card &led_card, Suit trump) override{
    if(hand_size < 1){
        assert(false);
    } 
    Suit led = led_card.get_suit(trump);
    // Card max_led_card; 
    index_max_led = 0;
    led_count = 0; 
    ntcount = 0; 
    ntindex = 0; 
    // Card minnt; 
    // Card mintrump; 
    trump_count = 0; 
    trumpind= 0; 
    review_hand(trump, led , led_card);
    // for(int i = 0; i < hand_size; ++i){
    //     if(hand[i].get_suit(trump) == led) {
    //         if(led_count == 0){ 
    //         reassign(hand[i], max_led_card, index_max_led, i);
    //         //max_led_card = hand[i]; 
    //         //index_max_led = i;
    //         } else if(Card_less(max_led_card,hand[i],led_card, trump)) {
    //         reassign(hand[i], max_led_card, index_max_led, i);
    //         //max_led_card = hand[i]; 
    //         //index_max_led = i;
    //         } led_count++;
    //     }else if(!(hand[i].is_trump(trump))){ 
    //         if(ntcount == 0){ 
    //             reassign(hand[i], minnt, ntindex, i);
    //             //minnt = hand[i]; 
    //             //ntindex = i;
    //         } else if( hand[i] < minnt){
    //             reassign(hand[i], minnt, ntindex, i);
    //             //minnt= hand[i]; 
    //             //ntindex = i;
    //         } 
    //         ntcount++; 
    //     } else if(hand[i].is_trump(trump)){ 
    //         if(trump_count == 0) { 
    //             reassign(hand[i], mintrump, trumpind, i);
    //             //mintrump = hand[i]; 
    //             //trumpind = i; 
    //         } else if(Card_less(hand[i],mintrump,trump)){ 
    //            reassign(hand[i], mintrump, trumpind, i);
    //            //mintrump = hand[i]; 
    //            //trumpind = i; 
    //         }
    //         trump_count++; 
    //     }
    // }
    if(led_count == 0){
        if(ntcount != 0){ 
            hand.erase(hand.begin() + ntindex);
            hand_size = hand_size - 1; 
            return minnt;
        } else { 
            hand.erase(hand.begin() + trumpind);
            hand_size = hand_size - 1; 
            return mintrump;
        }
    } else{
        hand.erase(hand.begin() + index_max_led);
        hand_size = hand_size - 1; 
        return max_led_card;
    }
}
  
    
  // Needed to avoid some compiler errors
  //DTOR
  ~SimplePlayer() {} 
  private: 
    std::vector<Card> hand; 
    //Card hand[MAX_HAND_SIZE];  
    int hand_size;
    std::string player_name; 
    Card max_led_card; 
    int index_max_led = 0;
    int led_count = 0; 
    int ntcount = 0; 
    int ntindex = 0; 
    Card minnt; 
    Card mintrump; 
    int trump_count = 0; 
    int trumpind= 0; 
    

    void reassign(Card newcard, Card &mcard, int &mindex, int ind ) {
        mcard = newcard; 
        mindex = ind;
    }

    void review_hand(Suit trump, Suit led , Card led_card) { 
        for(int i = 0; i < hand_size; ++i){
        if(hand[i].get_suit(trump) == led) {
            if(led_count == 0){ 
            reassign(hand[i], max_led_card, index_max_led, i);
            //max_led_card = hand[i]; 
            //index_max_led = i;
            } else if(Card_less(max_led_card,hand[i],led_card, trump)) {
            reassign(hand[i], max_led_card, index_max_led, i);
            //max_led_card = hand[i]; 
            //index_max_led = i;
            } led_count++;
        }else if(!(hand[i].is_trump(trump))){ 
            if(ntcount == 0){ 
                reassign(hand[i], minnt, ntindex, i);
                //minnt = hand[i]; 
                //ntindex = i;
            } else if( hand[i] < minnt){
                reassign(hand[i], minnt, ntindex, i);
                //minnt= hand[i]; 
                //ntindex = i;
            } 
            ntcount++; 
        } else if(hand[i].is_trump(trump)){ 
            if(trump_count == 0) { 
                reassign(hand[i], mintrump, trumpind, i);
                //mintrump = hand[i]; 
                //trumpind = i; 
            } else if(Card_less(hand[i],mintrump,trump)){ 
               reassign(hand[i], mintrump, trumpind, i);
               //mintrump = hand[i]; 
               //trumpind = i; 
            }
            trump_count++; 
        }
    }
    }


    
};

class HumanPlayer : public Player {
 public: 

    HumanPlayer(std::string name): Player() {
        Human_Player_name = name;
        hand_size = 0;
    }
    //EFFECTS returns player's name
    const std::string &get_name() const override{
        return Human_Player_name;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override{
        if(hand_size < MAX_HAND_SIZE){ 
        hand.push_back(c); 
        hand_size = hand_size + 1; 
        } 
        std::sort(hand.begin(), hand.end());

    }
    

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                            int round, Suit &order_up_suit) const override{
        print_hand();

        std::cout << "Human player " << Human_Player_name 
        << ", please enter a suit, or \"pass\":\n";
        std::string decision;
        std::cin >> decision;

        if (decision != "pass") {
            order_up_suit = string_to_suit(decision);
            return true;
        } else {
            return false;
        }
    }
    
    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override{
        if(hand_size < 1){
            assert(false);
        }
        int card_index; 
        print_hand();
        std::cout << "Discard upcard: [-1]\n";
        std::cout << "Human player " << Human_Player_name 
        << ", please select a card to discard:\n";
        std::cin >> card_index; 
        if(card_index != -1){
            hand.erase(hand.begin()+card_index); 
            hand.push_back(upcard); 
        }
        
        std::sort(hand.begin(), hand.end());

    }

    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(Suit trump) override{
        if(hand.size() < 1) {
            assert(false); 
        }
        int card_index;
        Card choosen_card; 
        print_hand();
        std::cout << "Human player " << Human_Player_name << ", please select a card:\n";
        std::cin >> card_index;
        choosen_card = hand[card_index]; 
        hand.erase(hand.begin()+card_index); 
        hand_size = hand_size -1; 
        return choosen_card; 


        
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, Suit trump) override{
        if(hand.size() < 1) {
            assert(false); 
        }
        int card_index;
        Card choosen_card; 
        print_hand();
        std::cout << "Human player " << Human_Player_name << ", please select a card:\n";
        std::cin >> card_index;
        choosen_card = hand[card_index]; 
        hand.erase(hand.begin()+card_index); 
        hand_size = hand_size -1; 
        return choosen_card;
    }

 private:
    std::vector<Card> hand; 
    int hand_size;
    std::string Human_Player_name; 

    void print_hand() const {
        for (size_t i=0; i < hand.size(); ++i)
            std::cout << "Human player " << Human_Player_name << "'s hand: "
            << "[" << i << "] " << hand[i] << "\n";
    }


}; 

Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
//   Repeat for each other type of Player
  if(strategy == "Human") {
    return new HumanPlayer(name);
  }
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}


std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name(); 
  return os;
}




