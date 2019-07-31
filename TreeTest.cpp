/**
 * Examples of automatic tests for the exercise on binary trees.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include "badkan.hpp"
#include "Tree.hpp"
using std::cout, std::endl;
const int m=1000;

int main() {
  ariel::Tree emptytree;
  ariel::Tree threetree;  
  ariel::Tree tree3; 

  threetree.insert(5);
  threetree.insert(7);
  threetree.insert(3);
  
  badkan::TestCase tc("Binary tree");
  tc
  .CHECK_EQUAL (emptytree.size(), 0)
  .CHECK_OK    (emptytree.insert(5))
  .CHECK_EQUAL (emptytree.size(), 1)
  .CHECK_EQUAL (emptytree.contains(5), true)
  .CHECK_OK    (emptytree.remove(5))
  .CHECK_THROWS(emptytree.remove(5))
  .CHECK_EQUAL (emptytree.size() ,0)
  
  .CHECK_EQUAL (threetree.size(), 3)
  .CHECK_EQUAL (threetree.root(), 5)
  .CHECK_EQUAL (threetree.parent(3), 5)
  .CHECK_EQUAL (threetree.parent(7), 5)
  .CHECK_EQUAL (threetree.left(5), 3)
  .CHECK_EQUAL (threetree.right(5), 7)
  .CHECK_THROWS(threetree.insert(3))
  .CHECK_OK    (threetree.print())
  
  // ---- STUDENT'S EXTRA TESTS: 207206947 -----
  // check that "insert" works correctly.
  .CHECK_OK(tree3.insert(3.1*m))
  .CHECK_EQUAL(tree3.contains(3.1*m), true)
  .CHECK_EQUAL(tree3.size(), 1)
  .CHECK_THROWS(tree3.insert(3.1*m))
  .CHECK_OK(tree3.insert(-1.132*m))
  .CHECK_EQUAL(tree3.contains(-1.132*m), true)
  .CHECK_EQUAL(tree3.size(), 2)
  .CHECK_OK(tree3.insert(5.44*m))
  .CHECK_OK(tree3.insert(5.84*m))
  .CHECK_OK(tree3.insert(5.11*m))
  // check that subsequent inserts dont mess up with existing elements
  .CHECK_EQUAL(tree3.contains(5.44*m), true) 
  .CHECK_EQUAL(tree3.contains(5.84*m), true)
  .CHECK_EQUAL(tree3.contains(5.11*m), true)
  .CHECK_EQUAL(tree3.contains(3.1*m), true)
  .CHECK_EQUAL(tree3.contains(-1.132*m), true)
  .CHECK_EQUAL(tree3.size(), 5)
  .CHECK_OK(tree3.insert(1*m))
  .CHECK_OK(tree3.insert(0.2*m))
  .CHECK_EQUAL(tree3.size(), 7)
   // check that "contains" function works correctly.
  .CHECK_EQUAL(tree3.contains(66.6*m), false)
  .CHECK_EQUAL(tree3.contains(-5.6*m), false)
  // check that "root" works correctly.
  .CHECK_EQUAL(tree3.root(), 3.1*m)
  // check that "parent" works correctly.
  .CHECK_THROWS(tree3.parent(tree3.root())) // ROOT have no parent
  .CHECK_EQUAL(tree3.parent(5.11*m), 5.44*m)
  // check that "left" works correctly.
  .CHECK_THROWS(tree3.left(0.2*m)) // leaf node have no childrens.
  .CHECK_EQUAL(tree3.left(1*m), 0.2*m)
  .CHECK_EQUAL(tree3.left(5.44*m), 5.11*m)
  // check that "right" works correctly.
  .CHECK_THROWS(tree3.right(0.2*m)) // leaf node have no childrens.
  .CHECK_THROWS(tree3.right(1*m)) 
  .CHECK_EQUAL(tree3.right(5.44*m), 5.84*m)
  // check that "remove" works correctly. - first case: remove node with two childrens.
  .CHECK_OK(tree3.remove(5.44*m))
  .CHECK_EQUAL(tree3.contains(5.44*m), false)
  .CHECK_EQUAL(tree3.size(), 6)
  .CHECK_THROWS(tree3.remove(5.44*m))
  .CHECK_THROWS(tree3.remove(21.44*m))
  // check that "remove" works correctly. - second case: remove node with single child.
  .CHECK_OK(tree3.remove(-1.132*m))
  .CHECK_EQUAL(tree3.contains(-1.132*m), false)
  .CHECK_EQUAL(tree3.size(), 5)
  .CHECK_THROWS(tree3.remove(-1.132*m))
  // check that "remove" works correctly. - third case: remove a leaf node
  .CHECK_OK(tree3.remove(0.2*m))
  .CHECK_EQUAL(tree3.contains(0.2*m), false)
  .CHECK_EQUAL(tree3.size(), 4)
  .CHECK_THROWS(tree3.remove(0.2*m))
  // check other stuff
  .CHECK_THROWS(emptytree.root()) // check that after removing the root isnt pointing anywhere. and should be null.
  .CHECK_OK(tree3.print())

  .print();
  
  cout << "You have " << tc.right() << " right answers and " << tc.wrong() << " wrong answers so your grade is " << tc.grade() << ". Great!" << endl;
}
