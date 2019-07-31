#include <iostream>

namespace ariel
{


//Node class : signatures
class Node
{
//private fields of the Node
private:
  int value;
  Node *left;
  Node *right;
  Node *parent;

//All public functions required constructors,destructor
// setters&&getters
public:
  Node();
  Node(const int val);
  Node(const int val, Node *const l, Node *const r);

  ~Node();

  int get_value();
  Node *get_left();
  Node *get_right();
  Node *get_parent();

  void set_value(int val);
  void set_left(Node *const l);
  void set_right(Node *const r);
  void set_parent(Node *const p);
};

// Tree Class : signatures
class Tree
{
//private fields of the Tree 
//containing root,size
private:
  Node *_root;
  unsigned int _size;

  Node *find_predecessor(Node *n);
  Node *find_successor(Node *n);
  void print(Node *n);

//All public functions required constructors,destructor
// setters&&getters
public:
  // Constructor
  Tree();
  ~Tree();

  int calc_size(Node *tempNode); //TODO REMOVE (?)
  int mySize();
  int right(int i);
  int left(int i);
  int parent(int i);
  int root();
  unsigned int size();
  void insert(int value);
  bool contains(int i);
  void remove(int val);
  void print();
};
} // namespace ariel
