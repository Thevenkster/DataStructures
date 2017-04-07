//Author: Karthik Venkat
//email: kv39@zips.uakron.edu
//Unbalanced Binary Search Tree

#ifndef UNBALANCED_HPP
#define UNBALANCED_HPP

#include <stack>
#include <iostream>

template<typename T> struct Node
{
  T value;
  Node *left;
  Node *right;
  Node *parent;
  Node()
  :value(nullptr), left(nullptr), right(nullptr), parent(nullptr)
  {} //Default constructs the node
  Node(T& key) :value(key)
  {}
};

template<typename T> struct Tree //tree root node
{
  Node<T> *root;

  //Tree member functions
  Tree() :root(nullptr) //default constructor
  {}

    Tree(const Tree& x)//designed in collaboration with Adam Browne & Sam Borick
    {
      if (x.root == nullptr)
      {
        root = nullptr;
        return;
      }
     root = new Node<T>(x.root->key);
     Node<T> *current = root; //the node in new tree you are currently on
     Node<T> *st; //top of stack pointer

     std::stack<Node<T>*> treestack; //holds pointers of to-be inserted nodes
     std::stack<Node<T>*> twosub; //holds pointers to nodes with 2 children

     //push elements in order of insertion
     if (x.root->Left) treestack.push(x.root->Left);
     if (x.root->Right) treestack.push(x.root->Right);
     //push root to twosub if it has 2 children
     if ((x.root->Right) && (x.root->Left)) twosub.push(root);

      while(!treestack.empty())
      {
       st = treestack.top(); //top element of stack to be inserted
       Node<T> *newNode = new Node<T>(*st);
       if (current->Value > st->Value) current->Left = newNode;
       else current->Right = newNode;
       newNode->Parent = current;
       current = newNode;

       if (st->Left && st->Right) //if top has two children
         twosub.push(current);

       else if (!st->Left && !st->Right && !twosub.empty())
       {
           current = twosub.top();
           twosub.pop();
        }
        treestack.pop();
        if (st->Left) treestack.push(st->Left);
        if (st->Right) treestack.push(st->Right);
        }
      }

    Tree &operator=(const Tree &t) //copy assign
    {
      if (this == &t) return *this; //self assign guard
      clear(root); //delete old tree
      *this = Tree<T>(t);
      return *this;
    }

  ~Tree()
  {
    clear(root);
  }

  void clear(Node<T> &root)
  {
    if(root) //post order traversal to recursively delete node
    {
      clear(root->left); //go left
      clear(root->right); //go right
      delete root; //delete node
    }
    return;
  }

  Node<T> *find(T value)
  {
    if(root->value == value) return root;//return pointer if value is found
    else if(root->value > value) return find(root->right);//if greater, go right
    else if(root->value < value) return find(root->left);//if less, go left
    return nullptr; //if not found, return nullptr.
  }

  void insert(T value)
  {
    Node <T> *p = new Node <T>(value);
    if (!root) //for an empty tree
    {
      root = p;
      return;
    }
    Node <T> *q = root; //pointer to track parent node
    while(q) //to keep from walking off tree
    {
      if(value < q->value) //if key less than current node
      {
        if(!q->left) //if there are no left children, insert to left
        {
          q->left = p;
          p->parent = q;
          return;
        }
        else
        q = q->left; //keep going left
      }
      else //if key greater than or equal to current node
      {
        if(!q->right) //if there are no right children, insert to right
        {
          q->right = p;
          p->parent = q;
          return;
        }
        else q = q->right; //keep going right
      }
    }
  }

Node<T> *successor(Node<T> *root) //finds leftmost right subchild node of tree
{
  Node<T> *p = root->Right; //go to right subchild of root
  Node<T> *lmrs; //leftmost right subchild
  while (p)
    {
      lmrs = p;
      p = p->Left; //keep going left until you're at null
    }
    return lmrs;
  }

  void erase(Node<T> *del)
  {
    Node<T> *p = del->Parent;
		if (del->Left && del->Right) //when node is a "root" with 2 subtrees
    {
			Node<T> *r = successor(del); //find successor of del
			del->Value = r->Value; //assign lmrs value to node of position del
			delete r; //delete node in lmrs position
		}
    else if(del->Left) //when node only has left subtree
    {
			if (p->Left == del) p->Left = del->Left;
      else p->Right = del->Left;
		   del->Left->Parent = p;
			delete del;
		}
    else if(del->Right) //when node has only right subtree
    {
      if (p->Left == del) p->Left = del->Right;
      else p->Right = del->Right;
      del->Right->Parent = p;
			delete del;
		}
    else //for leaf nodes
    {
			if (p->Left == del) p->Left = nullptr;
      else  p->Right = nullptr;
			delete del;
		}
  }


  void print() //function to print the binary tree for graphwiz
  {
   std::cout << "digraph G" << std::endl << "{" << std::endl;
   Node<T> *x;
   std::stack<Node<T> *> s;
   int c1 = 0;
   s.push(root);
   while (!s.empty())
   {
     x = s.top();
     if (!(x -> parent)) std::cout << "Root" << "->" << x -> data << ";"
                                   << std::endl;
     else std::cout << (x -> parent) -> data << "->" << x -> data << ";"
                    << std::endl;
     if (!(x -> left)) std::cout << x -> data << "->" << "LnL" << c1 << ";"
                                 << std::endl;
     else std::cout << x -> data << "->" << "RnL" << c1 << ";" << std::endl;
     ++c1;
     s.pop();
     if (x -> right) s.push(x -> right);
     if (x -> left) s.push(x -> left);
   }
   std::cout << std::endl << "}" << std::endl;
 }
};



#endif
