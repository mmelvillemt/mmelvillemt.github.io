#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  List(): list_size(0), first(nullptr), last(nullptr){}
  
  //EFFECTS:  returns true if the list is empty
  bool empty() const{
    return first == nullptr;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const { 
    return list_size; 
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front(){
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back(){
    assert(!empty()); 
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum){
    Node *p = new Node;
    p->datum = datum;
    p->prev = nullptr;
    if(size() == 0) { 
    last = p;
    first = p;
    p->next = nullptr;
    list_size++; 
    return;  
    }
    p->next = first;
    first->prev = p; 
    first = p; 
    list_size++; 

    
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum){
    Node *p = new Node;
    p->datum = datum;
    p->next = nullptr;

    if(empty()){
      first = last = p;
      p->prev = nullptr;
    } else {
      last->next = p;
      p->prev = last; 
      last = p;

    }
    list_size++;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front(){
    Node * to_delete = first;
    first = first->next;
    // if only one element, make both f and l null 
    if(size() == 1){ 
      last = first; 
    } else { 
      // else make prev null 
      first->prev = nullptr;
    }
    delete to_delete;
    list_size--;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back(){ 
    Node * to_delete = last; 
    last = last->prev;
    if(size() == 1){ 
      first = last; 
    } else { 
      // else make prev null 
      last->next = nullptr;
    } 
    delete to_delete;
    list_size--; 
    }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear(){
    while(!empty()){
      pop_front(); 
    }
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists
  ~List(){
    clear();
  }

  List(const List<T> &other)
    : first(nullptr), last(nullptr){
    copy_all(other);
    }

  List<T> & operator=(const List<T> &rhs){
    if(this == &rhs) { 
      return *this; 
    }
    clear(); 
    copy_all(rhs); 
    return *this; 
  }

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };
  int list_size; 

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &rhs){
    assert(empty()); 
    last = nullptr; 
    
    for (Node *p = rhs.first; p != nullptr; p = p->next) {
      Node *temp = new Node; 
      temp->datum = p->datum; 
      temp->next = nullptr; 
      temp->prev = last; 
      if(last == nullptr) { 
        first = last = temp; 
      } else {  
        last->next = temp; 
        last = temp;
         
      }
      list_size++; 
    }

  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

public:
  ////////////////////////////////////////
  class Iterator {
    friend class List; 
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    Iterator() 
      : node_ptr(nullptr) {}

    Iterator& operator++() {
      assert(node_ptr); 
      node_ptr = node_ptr->next; 
      return *this; 
    }

    bool operator==(Iterator rhs) const {
      return node_ptr == rhs.node_ptr; 
    }

    bool operator!=(Iterator rhs) const {
      return node_ptr != rhs.node_ptr;
     
    }

    T operator*() const{
      assert(node_ptr);
      return node_ptr->datum; 
    }

     // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here

    // construct an Iterator at a specific position
    Iterator(Node *p) 
      : node_ptr(p) {}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const { 
    return Iterator(); 
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i){
    if(i == begin()){
      pop_front();
      return; 
    } else if(i.node_ptr == last) {
      pop_back(); 
      return; 
    } 
    Iterator pi = i; 
    Iterator ni = i; 
    ++ni; 
    --pi;
    pi.node_ptr->next = ni.node_ptr;
    ni.node_ptr->prev = pi.node_ptr;
    delete i.node_ptr;
    --list_size;  
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum) { 
    if(i == begin()) { 
      push_front(datum); 
      return; 
    } else if ( i.node_ptr == nullptr) { 
      push_back(datum); 
      return; 
    }
    
    Node *temp = new Node;
    temp->datum = datum;
    Iterator pi = i;  
    --pi;
    temp->prev = pi.node_ptr->prev;
    temp->next = pi.node_ptr->next;
    pi.node_ptr->next = temp;
    i.node_ptr->prev = temp; 
    

    ++list_size; 
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
