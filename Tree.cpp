#include <iostream>
#include <stdexcept>
#include "Tree.hpp"

//using the namespace from the Tree.hpp
using ariel::Tree, ariel::Node;

//       ~~~Starting implementation of the functions~~~


//       ~~~Node implementaion~~~

//Constructors
ariel::Node::Node() : Node(0) {}
ariel::Node::Node(const int val) : Node(val, NULL, NULL) {}
ariel::Node::Node(const int val, Node *const l, Node *const r) : value(val), left(l), right(r), parent(NULL) {}

//Destructor
ariel::Node::~Node()
{
    if (left != NULL)
        delete left;

    if (right != NULL)
        delete right;
}

//Node's setters&&getters
int ariel::Node::get_value() { return this->value; }
Node *ariel::Node::get_left() { return left; }
Node *ariel::Node::get_right() { return right; }
Node *ariel::Node::get_parent() { return parent; }

void ariel::Node::set_value(int val) { value = val; }
void ariel::Node::set_left(Node *const l) { left = l; }
void ariel::Node::set_right(Node *const r) { right = r; }
void ariel::Node::set_parent(Node *const p) { parent = p; }


//    ~~~Tree implementation~~~


//Constructor
ariel::Tree::Tree() : _root(NULL), _size(0) {}

//Destructor
ariel::Tree::~Tree()
{
    if (_root != NULL)
        delete _root;
}

//Optional function for calculating the size of the tree 
int ariel::Tree::calc_size(Node *tempNode)
{
    if (tempNode == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + calc_size(tempNode->get_left()) + calc_size(tempNode->get_right());
    }
}
int ariel::Tree::mySize()
{
    if (_root != NULL)
    {
        Node *t = _root;
        return calc_size(t);
    }
    return 0;
}

//right function : returning the value of the right child
int ariel::Tree::right(int i)
{
    if (_root != NULL)
    {
        if (!contains(i))
        {
            throw std::invalid_argument("i value isnt found and thus doesnt have right child");
        }
        else
        { //i exsists , Lets find him!!!
            Node *t = _root;
            while (t->get_value() != i)
            {
                if (t->get_value() == i)
                    break;
                else if (t->get_value() < i)
                    t = t->get_right();
                else
                    t = t->get_left();
            }
            if (t->get_right() == NULL)
                throw std::invalid_argument("i was found but doesnt have a right child");
            else
                return t->get_right()->get_value(); 
        }
    }
    else
    {
        throw std::invalid_argument("The root is empty");
    }
}

//left function: returning the value of the left child
int ariel::Tree::left(int i)
{
    if (_root != NULL)
    {
        if (!contains(i))
        {
            throw std::invalid_argument("i value isnt found and thus doesnt have left child");
        }
        else
        { //i exsists , Lets find him!!!
            Node *t = _root;
            while (t->get_value() != i)
            {
                if (t->get_value() == i)
                    break;
                else if (t->get_value() < i)
                    t = t->get_right();
                else
                    t = t->get_left();
            }
            if (t->get_left() == NULL)
                throw std::invalid_argument("i was found but doesnt have a left child");
            else
                return t->get_left()->get_value(); 
        }
    }
    else
    {
        throw std::invalid_argument("The root is empty");
    }
}

//parent function : returning the value of the parent
int ariel::Tree::parent(int i)
{
    if (_root != NULL)
    {
        if (_root->get_value() == i)
        {
            //throw exception since i is the root
            //thus does not have a father
            throw std::invalid_argument("i is the root and thus doesnt have a father");
        }
        else if (!contains(i))
        {
            throw std::invalid_argument("i wasnt found");
        }
        else
        {
            Node *t = _root;
            while (t->get_value() != i)
            {
                if (t->get_value() == i)
                    break;
                else if (t->get_value() < i)
                    t = t->get_right();
                else
                    t = t->get_left();
            }
            return t->get_parent()->get_value();
        }
    }
    else
    {
        throw std::invalid_argument("The root is empty");
    }
}

//root function : returning the value of the root
int ariel::Tree::root()
{
    if (_root != NULL)
        return _root->get_value();
    else
        throw std::invalid_argument("The root is empty");

    return 0;
}
//size function : returning the size of the tree
unsigned int ariel::Tree::size()
{
    return _size;
}

//insert function : insertinng new Node to the tree for a given value
void ariel::Tree::insert(int value)
{
	//case 1: There is no root yet ,So the new Node will be the root
    if (_root == NULL)
    {
        _root = new Node(value);
        _size++;
        return; // exit
    }
	//case 2: if the value exists already we shall throw execption as asked
    if (contains(value))
    {
        throw std::invalid_argument("The value is already exists in the tree (value: " + std::to_string(value) + ")");
    }
	//case 3: finding the right spot for the new node
    else
    {
        Node *n = new Node(value);
        Node *i = _root;

        while (i != NULL)
        {
            if (value < i->get_value())
            {
                if (i->get_left() != NULL)
                {
                    i = i->get_left();
                }
                else
                {
                    n->set_parent(i);
                    i->set_left(n);
                    _size++;
                    break;
                }
            }
            else
            {
                if (i->get_right() != NULL)
                {
                    i = i->get_right();
                }
                else
                {
                    n->set_parent(i);
                    i->set_right(n);
                    _size++;
                    break;
                }
            }
        }
    }
}

//function for findind the predecessor to replace the deleted Node (related to the remove function) 
ariel::Node *ariel::Tree::find_predecessor(Node *n)
{
    if (n == NULL)
        return NULL;

    if (n->get_left() != NULL)
    {
        n = n->get_left();
        while (n->get_right() != NULL)
            n = n->get_right();

        return n;
    }
    else
        return NULL;
}
//function for findind the successor to replace the deleted Node (related to the remove function)
ariel::Node *ariel::Tree::find_successor(Node *n)
{
    if (n == NULL)
        return NULL;

    if (n->get_right() != NULL)
    {
        n = n->get_right();
        while (n->get_left() != NULL)
            n = n->get_left();

        return n;
    }
    else
        return NULL;
}

//contains function : searching if there is a Node exists with the given value
bool ariel::Tree::contains(int i)
{
    Node *t = _root;
    while (t != NULL)
    {
        if (t->get_value() == i)
            return true;
        else if (t->get_value() < i)
            t = t->get_right();
        else
            t = t->get_left();
    }
    return false;
}

//remove function : searching for a node with the given value for deletion
void ariel::Tree::remove(int val)
{
    if (!contains(val))
        throw std::invalid_argument("ERROR : trying to remove Node which doesn't exist");

    //if root is null - tree is empty then exit
    if (_root == NULL)
        return;

    // find the node in the tree
    Node *t = _root;          // temp
    bool orientation = false; // false = left, true = right;
    while (t != NULL)
    {
        if (val < t->get_value())
        {
            orientation = false;
            t = t->get_left();
        }
        else if (val > t->get_value())
        {
            orientation = true;
            t = t->get_right();
        }
        else if (val == t->get_value())
        {

            Node *p = t->get_parent(); // parent
            // if a leaf
            if (t->get_left() == NULL && t->get_right() == NULL)
            {
                if (p != NULL) // the only node without a parent is a root node.
                {
                    if (!orientation)
                        p->set_left(NULL);
                    else
                        p->set_right(NULL);

                    delete t;
                }
                else
                {

                    delete _root;
                    _root = NULL;
                }

                this->_size--;
                return; // exit
            }
            else if (t->get_left() != NULL && t->get_right() == NULL) // if have only left child
            {
                Node *pred = find_predecessor(t);
                Node *pred_p = pred->get_parent();

                int num = pred->get_value();
                remove(pred->get_value());
                t->set_value(num);

                return; // exit
            }
            else if (t->get_left() == NULL && t->get_right() != NULL) // if have only right child
            {
                Node *succ = find_successor(t);
                Node *succ_p = succ->get_parent();

                int num = succ->get_value();
                remove(succ->get_value());
                t->set_value(num);

                return; // exit
            }
            else if (t->get_left() != NULL && t->get_right() != NULL) // if have two childrens
            {
                Node *succ = find_successor(t);
                Node *succ_p = succ->get_parent();

                int num = succ->get_value();
                remove(succ->get_value());
                t->set_value(num);

                return; // exit
            }
        }
    }
}

//print function : recursive function for printing the Tree 
void ariel::Tree::print(Node *n)
{
    if (n == NULL)
        return;

    print(n->get_left());
    std::cout << n->get_value() << " ";
    print(n->get_right());
}

//initilaize the root and send him to the recursive function for printing
void ariel::Tree::print()
{
    if (_root == NULL)
    {
        std::cout << "The tree is empty.\n";
        return;
    }
    print(_root);
    std::cout << "\n";
}
