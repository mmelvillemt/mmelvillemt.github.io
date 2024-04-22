#include "Pack.hpp"
#include <cassert>
#include <iostream>
#include <array>
#include <string>


Pack::Pack() :next(0) {
    int count = 0; 
    
    for (int s = SPADES; s <= DIAMONDS; ++s) {
        Suit suit = static_cast<Suit>(s);
        for(int r = NINE; r <= ACE; ++r){ 
            Rank rank = static_cast<Rank>(r);
            Card c(rank, suit); 
            cards[count] = c; 
            count++;
        }
    }
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) :next(0){ 
    Card c;  
    for(int i = 0; i < PACK_SIZE; i++){ 
        pack_input >> c; 
        cards[i] = c; 
    }
}

// REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one(){
    assert(next<24); 
    Card c = cards[next]; 
    next = next+ 1; 
    return c; 
}

// EFFECTS: Resets next index to first card in the Pack
  void Pack::reset(){
    next = 0;
  }

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle(){ 
    int count = 0;
    next = 0; 
    Card first_half[PACK_SIZE/2]; 
    Card second_half[PACK_SIZE/2];  

    while(count < 7){
        for(int i = 0; i < PACK_SIZE; ++i){
            if(i < 12){
                first_half[i] = cards[i];  
            } else { 
                second_half[i-12] = cards[i]; 
            }
        }
        int even = 0; 
        int odd = 0; 
        for(int i = 0; i < PACK_SIZE; i++){
        
            if(i % 2 == 0){ 
                cards[i] = second_half[odd]; 
                odd++;
            } else{ 
                cards[i] = first_half[even];
                even++; 
            }
        }
        count++;
    }
} 
// EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const{ 
    return (next >= 24); 
}