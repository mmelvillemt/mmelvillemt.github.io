#include <iostream>
#include <fstream>
#include "Card.hpp"
#include <vector>
#include "Player.hpp"
#include "Pack.hpp"
using namespace std;

class Game { 
  public: 
  Game(Pack pack_in, bool shuff, int ptw, 
  vector<Player*> playersin)

   : pack(pack_in), shuffle(shuff), ptsw(ptw), 
   players(playersin), teamevenpts(0), teamoddpts(0),
    hand(0), dealer(0) {
  } 
  void play(){
    while(teamoddpts < ptsw && teamevenpts < ptsw){
      pack.reset(); 
      shufflep(); 
      check_index(); 
      deal(3);
      deal(2);
      deal(3);
      deal(2);
      check_index();
      deal(2);
      deal(3);
      deal(2);
      deal(3);
      upcard = pack.deal_one();

      cout << "Hand " << hand << endl; 
      cout << *players[dealer]  << " deals" << endl; 
      cout << upcard;
      cout << " turned up" << endl;
      
      make_trump();

      play_hand(); 
      hand = hand +1;
      if(dealer + 1 == 4) { 
        dealer = 0; 
      }else { 
        dealer = dealer + 1;
      }
      


    }
    if(teamevenpts >= ptsw) { 
      cout << *players[0] << " and " << *players[2] 
    << " win!" << endl; 
    } else  { 
      cout << *players[1] << " and " << *players[3] 
    << " win!" << endl; 
    }

    for (size_t i = 0; i < players.size(); ++i) {
      delete players[i];
    }
  }
  
  

  private:

  Pack pack;
  bool shuffle; 
  int ptsw;  
  vector<Player*> players;
  int teamevenpts; 
  int teamoddpts; 
  int hand;
  int dealer;
  int nextplay;
  Card upcard;  
  bool maketrump;
  Suit trump; 
  int called; 
  int eventricks = 0; 
  int oddtricks = 0;  

  void check_index() {
    if(dealer + 1 == 4) { 
        nextplay = 0; 
      }else { 
        nextplay = dealer + 1;
      }
  }
  void print_winners(){ 
    if(eventricks > oddtricks){
      cout << *players[0] << " and " << *players[2] 
      << " win the hand" << endl; 
      if(eventricks == 5 && (called % 2 == 0)) { 
        cout << "march!" << endl;
        teamevenpts = teamevenpts + 2;  
      } else if(called % 2 == 1){ 
        cout << "euchred!" << endl;
        teamevenpts = teamevenpts + 2;  
      } else { 
        teamevenpts++;
      }
    } else { 
      cout << *players[1] << " and " << *players[3] 
      << " win the hand" << endl; 
      if(oddtricks == 5 && (called % 2 == 1)) { 
        cout << "march!" << endl;
        teamoddpts = teamoddpts + 2;  
      } else if(called % 2 == 0){ 
        cout << "euchred!" << endl;
        teamoddpts = teamoddpts + 2;  
      } else { 
        teamoddpts++; 
      }
    }
  }
  void shufflep() { 
    if(shuffle) { 
      pack.shuffle();
    } 
  }

  void deal(int num){ 
    if(nextplay < 4){
      Player * temp = players[nextplay]; 
      for(int i  = 0; i < num; i++){
          Card c = pack.deal_one();
          temp->add_card(c);
        }
    } else{
      nextplay = 0; 
      Player * temp = players[nextplay]; 
      for(int i  = 0; i < num; i++){
        Card c = pack.deal_one();
        temp->add_card(c);
      }  
    }
    ++nextplay;
  }

  void make_trump(){
    bool order_up; 
    bool is_dealer;
    int count = 0; 
    int round = 1;
    if(nextplay == 4) { 
      nextplay = 0; 
    }
    Player *temp = players[nextplay];  
    while(!order_up) { 
      if(nextplay == 4){ 
        nextplay = 0; 
      }
      temp = players[nextplay];
      if(nextplay == dealer) {
        is_dealer = true; 
      } else { 
        is_dealer = false; 
      }
      if(count > 3) {
        round = 2; 
      }
      order_up = temp->make_trump(upcard, is_dealer, round, trump);
      if(order_up == false){ 
        cout << *temp << " passes" << endl;
      }
      called = nextplay;
      nextplay++;
      count++; 
    }
    cout << *temp << " orders up " << trump << endl;
    temp = players[dealer];
    if(round == 1){ 
      temp->add_and_discard(upcard);
    }
    cout << endl;  
  } 

  void play_hand(){  
    Card lead; Card winning; Card played;    
    oddtricks = 0; eventricks = 0;   
    check_index();
    int windex = nextplay; Player * lead_player;  
    for(int i = 0; i < 5; i++ ){
      lead_player = players[windex];
      lead = lead_player->lead_card(trump); 
      cout << lead << " led by " << *lead_player << endl;  
      winning = lead; nextplay = windex + 1; 
      if(nextplay == 4) {
        nextplay = 0; 
      }
      for(int j = 0; j < 3; j++){
        played = players[nextplay]->play_card(lead,trump);
        cout << played << " played by " << *players[nextplay] << endl;
       if(Card_less(winning,played,lead,trump)) {
          winning = played; windex = nextplay;
        }
        if(nextplay + 1 == 4) { 
          nextplay = 0; 
        }else { 
         nextplay = nextplay + 1;
        }
      }
      cout << *players[windex] << " takes the trick" << endl;
      cout << endl;  
      if(windex % 2 == 0){
        eventricks++;
      } else { 
        oddtricks++; 
      }
    } 
    print_winners(); 
    cout << *players[0] << " and " << *players[2]
    << " have " << teamevenpts << " points" << endl; 
    cout << *players[1] << " and " << *players[3]
    << " have " << teamoddpts << " points" << endl;
    cout << endl;  
  }
};





int main(int argc, char *argv[]) {
  if(argc != 12) {
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
    << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
    << "NAME4 TYPE4" << endl;

    return 1; 
  }
  // Reading in Pack 
  ifstream fin(argv[1]);
  string filename = argv[1]; 
  if(!(fin.is_open())){ 
    cout << "Error opening " << filename << endl;
    return 1;
  }
  Pack pack_in(fin);

  // Checking Shuffle Operator 
  string shuffop = argv[2];
  bool shuff = true; 
  if(shuffop == "noshuffle"){
    shuff = false; 
  } else if(shuffop == "shuffle"){
    shuff = true; 
  } else { 
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
    << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
    << "NAME4 TYPE4" << endl;
    return 1; 

  }
  // Points to win 
  int ptw = atoi(argv[3]);
  if(ptw < 1 || ptw > 100) {
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
    << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
    << "NAME4 TYPE4" << endl;
    return 1; 
  } 
  // Reading in Players 
  vector<Player*> playersin; 
  for( int i = 4; i < 12; i++){
    string tempname =  argv[i]; 
    string temptype = argv[i+1];
   
    // Checks condition 
    if(temptype != "Simple" && temptype != "Human"){ 
      cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
      << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
      << "NAME4 TYPE4" << endl;
      return 1; 
    } 

    playersin.push_back(Player_factory(tempname, temptype));
    i++;  
  }

  Game game(pack_in, shuff, ptw, playersin);
  for(int i = 0; i < argc; i++) { 
    cout<< argv[i] << " "; 
  }
  cout << endl; 
  game.play(); 

}