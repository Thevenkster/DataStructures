//Author: Karthik Venkat
//email: kv39@zips.uakron.edu
//AVL Binary Search Tree

#ifndef AVL_HPP
#define AVL_HPP

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
  Node(T key) :value(key)
  {}
};

template<typename T> struct Tree //tree root node
{
  Node<T> *root;

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
  }

  ~Tree()//destructor
  {
    clear(root);
  }

  void clear(Node<T> *root) //post order traversal to recursively delete nodes
  {
    if(root)
    {
      clear(root->left); //go left
      clear(root->right); //go right
      delete root; //delete node
    }
    return;
  }

  Node<T> * find(T value)
  {
    if(root->value == value) return root;//return pointer if value is found
    else if(root->value > value) return find(root->right->value);//greater=>go right
    else if(root->value < value) return find(root->left->value);//less=>, go left
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
    balance(p);
  }

Node<T> *successor(Node<T> *root) //finds leftmost right subchild node of tree
{
  Node<T> *p = root->right; //go to right subchild of root
  Node<T> *lmrs; //leftmost right subchild
  while (p)
    {
      lmrs = p;
      p = p->left; //keep going left until you're at null
    }
    return lmrs;
  }

  void erase(Node<T> *del)
  {
    Node<T> *p = del->parent;
		if (del->left && del->right) //when node has left and right subchildren
    {
			Node<T> *r = successor(del); //find successor of del
			del->value = r->value; //assign lmrs value to node of position del
			delete r; //delete node in lmrs position
		}
    else if(del->left) //when root node only has left subtree
    {
			if (p->left == del) p->left = del->left;
      else p->right = del->left;
		   del->left->parent = p;
			delete del;
		}
    else if(del->right) //when root node has only right subtree
    {
      if (p->left == del) p->left = del->right;
      else p->right = del->right;
      del->right->parent = p;
			delete del;
		}
    else //for leaf nodes
    {
			if (p->left == del) p->left = nullptr;
      else  p->right = nullptr;
			delete del;
		}
    balance(p);
  }

  int height (Node<T> *root) //returns height of tree
  {
      int hl = 0;
      int hr = 0;
      if (root)
      {
        hl = height(root->left); //get height of left subtree
        hr = height(root->right); //get height of right subtree
        return (1+std::max(hl, hr));
      }
      return 0; //empty tree
  }


  int balancefactor(Node<T> *root) //returns balance factor of tree
  {

    int hl = height(root -> left);
    int hr = height(root -> right);
    int bf = hr-hl;
    return bf;
  }

  void balance(Node<T> *p)
  {
    int bf = balancefactor(p);
    if (bf > 1)
    {
      if (balancefactor(p -> left) > 0) p = ll(p);
      else p = lr(p);
    }
    if (bf < -1)
    {
      if (balancefactor(p -> right) > 0) p = rl(p);
      else p = rr(p);
    }
  }

  Node<T> *ll(Node<T> *p) //left rotate
  {
    Node<T> * q = p -> right;
    p -> right = q-> left;
    if (!q -> left) q->left->parent = p;
    if (!p -> parent)
    {
      root = q;
      q->parent = nullptr;
    }
    else if (p -> parent -> left  == p) p -> parent -> left = q;
    else p -> parent -> right = q;
    q->left = p;
    p->parent = q;
  }

  Node<T> *rr(Node<T> *p) //right rotate
  {
    Node<T> * q = p -> left;
    p -> left = q-> right;
    if (q -> right) q->right->parent = p;
    if (!p -> parent)
    {
      root = q;
      q->parent = nullptr;
    }
    else if (p -> parent -> left  == p) p -> parent -> left = q;
    else p -> parent -> right = q;
    q->right = p;
    p->parent = q;
  }

  Node<T> *rl(Node<T> *p) //right left rotate
  {
    Node<T> *q = p -> left;
    p -> left = rr(q);
    return ll(p);
  }

  Node<T> *lr(Node<T> *p) //left right rotate
  {
    Node<T> *q = p -> right;
    p -> right = ll(q);
    return rr(p);
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
