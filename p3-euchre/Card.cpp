#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
  return {};
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  if(is >> str) {
    rank = string_to_rank(str);
  }
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
  return {};
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  if (is >> str) {
    suit = string_to_suit(str);
  }
  return is;
}


/////////////// Write your implementation for Card below ///////////////

//EFFECTS Initializes Card to the Two of Spades
Card::Card()
: rank(TWO), suit(SPADES) { 
}

//EFFECTS Initializes Card to specified rank and suit
Card::Card(Rank rank_in, Suit suit_in)
: rank(rank_in), suit(suit_in) { 
}

//EFFECTS Returns the rank
Rank Card::get_rank() const {
  return rank; 
}

//EFFECTS Returns the suit.  Does not consider trump.
Suit Card::get_suit() const{ 
  return suit; 
}

//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
Suit Card :: get_suit(Suit trump) const{
  if(rank == JACK){
    if(trump == SPADES){
      if(suit == CLUBS){
        return SPADES;
      }
    } else if(trump == CLUBS){
        if(suit == SPADES){
          return CLUBS;
        }
    } else if(trump == HEARTS){
        if(suit == DIAMONDS){
         return HEARTS;
        }
    } else{
        if(suit == HEARTS){
          return DIAMONDS;
        }
    }
  }  
  return suit; 
}

bool Card::is_face_or_ace() const{
  if(rank >= 9){
    return true; 
  } else { 
    return false; 
  }
}


bool Card::is_right_bower(Suit trump) const { 
  if(suit == trump && rank == JACK){ 
    return true; 
  }else { 
    return false;
  }
}

bool Card::is_left_bower(Suit trump) const { 
   if(rank == JACK){
    if(trump == SPADES){
      if(suit == CLUBS){
        return true;
      }
    } else if(trump == CLUBS){
        if(suit == SPADES){
          return true;
        }
    } else if(trump == HEARTS){
        if(suit == DIAMONDS){
         return true;
        }
    } else{
        if(suit == HEARTS){
          return true;
        }
    }
  }  
  return false; 


}

bool Card::is_trump(Suit trump) const{ 
  if(get_suit(trump) == trump){ 
    return true; 
  }
  
  return false; 

}

std::istream & operator>>(std::istream &is, Card &card){ 
  string junk; 
  is >> card.rank; 
  is >> junk;
  is >> card.suit;   
  return is; 
}


std::ostream &operator<<(std::ostream &os, const Card &card){
  os << card.get_rank();
  os << " of ";
  os << card.get_suit();
  return os;
}

bool operator<(const Card &lhs, const Card &rhs){
  if(lhs.get_rank() == rhs.get_rank()){
    bool test = lhs.get_suit() < rhs.get_suit();
    return test;
  }
  return lhs.get_rank() < rhs.get_rank();
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
bool operator<=(const Card &lhs, const Card &rhs){
  return lhs.get_rank() <= rhs.get_rank();
}

//EFFECTS Returns true if lhs is higher value than rhs.
bool operator>(const Card &lhs, const Card &rhs){
  if(lhs.get_rank() == rhs.get_rank()){
    return lhs.get_suit() > rhs.get_suit();
  }
  return lhs.get_rank() > rhs.get_rank();
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
bool operator>=(const Card &lhs, const Card &rhs){
  return lhs.get_rank() >= rhs.get_rank();
}

//EFFECTS Returns true if lhs is same card as rhs.
bool operator==(const Card &lhs, const Card &rhs){
  if( (lhs.get_rank() == rhs.get_rank()) && (lhs.get_suit() == rhs.get_suit()) ){
    return true;
  }else{
    return false;
  }
}

//EFFECTS Returns true if lhs is not the same card as rhs.
bool operator!=(const Card &lhs, const Card &rhs){
  if( (lhs.get_rank() != rhs.get_rank()) || (lhs.get_suit() != rhs.get_suit()) ){
    return true;
  }else{
    return false;
  }
}

//EFFECTS returns the next suit, which is the suit of the same color
Suit Suit_next(Suit suit){
  if(suit == SPADES){
    return CLUBS; 
    
  } else if(suit == CLUBS){
    return SPADES; 
    
  } else if(suit == HEARTS){
    return DIAMONDS; 
    
  } else{
    return HEARTS;  
  }
} 
  

//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, Suit trump){
  if(!a.is_trump(trump) && !b.is_trump(trump)){
    return a < b;
  }else if(a.is_trump(trump) && !b.is_trump(trump)){
    return false;
  }else if(!a.is_trump(trump) && b.is_trump(trump)){
    return true;
  }else if (a.is_right_bower(trump)){
    return false;
  }else if (b.is_right_bower(trump)){
    return true;
  }else if (a.is_left_bower(trump)){
    return false;
  }else if (b.is_left_bower(trump)){
    return true;
  }else{
    return a < b;
  }
}

//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump){ 
  Suit asuit = a.get_suit(); 
  Suit bsuit = b.get_suit();
  if(a.is_trump(trump)){ 
    asuit = trump; 
  }
  if(b.is_trump(trump)){ 
    bsuit = trump; 
  }
  Suit led = led_card.get_suit(); 
  
  if(asuit != led && bsuit != led){ 
    return Card_less(a, b, trump); 
  } else if( asuit == led && bsuit != led ){ 
    if(bsuit != trump){ 
      return false; 
    } else {
      return Card_less(a,b,trump); 
    } 
  } else if( asuit != led && bsuit == led){ 
    if(asuit != trump){ 
      return true; 
    } else if(bsuit == trump) {
      return Card_less(a,b,trump); 
    } else { 
      return false; 
    }
  } else if(asuit == led && bsuit == led){
    if(led == trump){ 
      return Card_less(a, b, trump);
    } else { 
      return (a < b);
    }
  } 
   return -1;
}



