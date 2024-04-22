#include <iostream>
#include "csvstream.hpp"
#include <map>
#include <fstream>
#include <set> 
#include <string>
#include <iostream> 
#include <cmath>



using namespace std;
set<string> unique_words(const string &str); 

int main(int argc, char *argv[]) {
  // Sets Floating Point Accuracy 
  cout.precision(3);
  
  //Checks if the correct amount of command line arguments
  //was entered
  if(argc < 3 || (argc > 4 && static_cast<string>(argv[3]) == "--debug")){
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
    return 1;
  } 
  string train_name = argv[1]; 
  string test_name = argv[2]; 
  string output;
  bool isdebug = false;  
 
  try {
  csvstream train_in(train_name);
  csvstream test_in(test_name);
  }
  catch(const csvstream_exception &e){ 
    cout << e.what() << endl;
    return 1; 
  }
  csvstream train_in(train_name);
  csvstream test_in(test_name);

   if(argc == 4){
      isdebug = true;    
      output = test_name + "_debug.out.txt";
    } 
  
// CLASS DECLARATION
  class Classifier {
    private:
     csvstream &train_file;  
     csvstream &test_file;
     bool debugon; 
     
     int numposts;
     int num_unique_words;
     //For each word w the number of posts in 
     //the entire training set that contain w
     map<string, int> word_posts;
     //For each label C the number of posts with that label.
     map<string,int> label_posts;
     //For each label C and word w the number of posts with 
     //label C that contain w
     map< pair<string,string> , int> wl_posts;

     // EFFECTS: Return a set of unique whitespace delimited words.x
    set<string> unique_words(const string &str) {
      istringstream source(str);
      set<string> words;
      string word;
      while (source >> word) {
        words.insert(word);
      }
      return words;
    }
  

    public:
    
    Classifier(csvstream &train_file_in, csvstream &test_file_in, 
                bool debug_in)
    : train_file(train_file_in), test_file(test_file_in), 
      debugon(debug_in),numposts(0) {}
    
    void readInData(){ 
      map<string,string> row;
      if(debugon){ 
        cout << "training data:" << endl; 
      } 

      while(train_file >> row){
        label_posts[row["tag"]] += 1;
        string post_words = row["content"];
        if(debugon) { 
          cout << "  label = " << row["tag"];
          cout << ", content = " << post_words << endl;
        }
        
        
        set<string> post = unique_words(post_words);
        for(auto it = post.begin(); it != post.end(); it++) { 
          word_posts[*it] += 1; 
          pair<string, string> tuple;
          tuple.first = row["tag"];
          tuple.second = *it;
          wl_posts[tuple] += 1;   
            
        }
        numposts += 1;    
      }
      num_unique_words = word_posts.size();
      // FOUT vocab and trained
      cout << "trained on " << numposts << " examples" << endl; 
      if(debugon){ 
        cout << "vocabulary size = " << num_unique_words << endl; 
      }
    }

    //Computes the log prior for a label
    double logPriorLabel(string label_in){ 
      double num_post_w_label = label_posts[label_in]; 
      double log_prior_val = log(num_post_w_label/numposts);
      return log_prior_val; 
    }


    //Computes the log likelyhood for a word and label
    double logLikelyhoodWL(pair<string,string> tuple_in) {
      
      if(wl_posts.find(tuple_in) != wl_posts.end()) { 
        double num_post_w_WL = wl_posts[tuple_in];
        double num_p_w_L = label_posts[tuple_in.first];
        return log( num_post_w_WL / num_p_w_L);

      } else if(word_posts.find(tuple_in.second) != word_posts.end()){ 
        double num_post_W = word_posts[tuple_in.second]; 
        return log(num_post_W/numposts); 
      
      } else{
        return log(1.0/numposts);
      } 
    }

     //Compute the log probability for a post and label
    //Log probability for a label: the sum of the log prior for the label + the log 
    //likelyhood of each word in the post given that label
    double logProbabilityPL(string label_in, string post_words) { 
      double LPL =  logPriorLabel(label_in);
      double log_like_total = 0; 
      map<string,string> row;

       
      set<string> post = unique_words(post_words);

      for(auto it = post.begin(); it != post.end(); it++) { 
        pair<string, string> tuple = {label_in,*it}; 
        log_like_total += logLikelyhoodWL(tuple);   
      }
      return LPL + log_like_total;
    }
      //Computes the log probablity for a post for every label 
    map<string, double> logProbabilityALL(string post_words) { 
      map<string, double> prob_p_is_l; 
      for(const auto &kv : label_posts){ 
        double temp = logProbabilityPL(kv.first, post_words);
        prob_p_is_l[kv.first] = temp; 
      }
      
      return prob_p_is_l;
    }


    void predictLabel() { 
      map<string,string> row;
      cout << "" << endl;
      cout << "test data:" << endl;
      int num_test_posts = 0; 
      int correct_predict = 0;  
      while(test_file >> row) { 
        string post_words = row["content"]; // post_words 
        map<string,double> prob_p_is_l = logProbabilityALL(post_words);

        string prediction = (*(prob_p_is_l.begin())).first;
        double prob = (*(prob_p_is_l.begin())).second;
        for(const auto &kv : prob_p_is_l){ 
          if(kv.second > prob){ 
            prob = kv.second; 
            prediction = kv.first; 
          }
        }
        
        cout << "  correct = " << row["tag"];
        cout << ", predicted = " << prediction;

        cout << ", log-probability score = " << prob << endl; 
        cout << "  content = " << post_words << endl; 
        cout << endl; 
        num_test_posts += 1; 
        if(prediction == row["tag"]){ 
          correct_predict += 1; 
        }
      }
      cout << "performance: " << correct_predict << " / "; 
      cout << num_test_posts << " posts predicted correctly" << endl; 
    }

    void printClasses() { 
      if(debugon){ 
      cout << "" << endl; 
      cout << "classes:" << endl;
      for(const auto &kv : label_posts){ 
        cout << "  " << kv.first << ", " << kv.second << " examples, ";  
        cout << "log-prior = " << logPriorLabel(kv.first) << endl; 
      }
      cout << "classifier parameters:" << endl; 
      for(const auto &kv : wl_posts){ 
        cout << "  " << kv.first.first << ":" << kv.first.second; 
        cout << ", count = " << kv.second << ", log-likelihood = "; 
        cout << logLikelyhoodWL(kv.first)<< endl;
      }
      
    }

      
        
    }

  };

  Classifier c(train_in, test_in, isdebug); 
  c.readInData(); 
  // cout << c.logPriorLabel("euchre") << endl; 
  
  c.printClasses();
  c.predictLabel(); 
  
  

   



 
  // EFFECTS: Return a set of unique whitespace delimited words.x
  // set<string> unique_words(const string &str) {
  //   istringstream source(str);
  //   set<string> words;
  //   string word;
  //   while (source >> word) {
  //     words.insert(word);
  //   }
  //   return words;
  // }
  
return 0;
}
