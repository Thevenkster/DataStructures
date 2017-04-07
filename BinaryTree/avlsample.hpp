#include <stack>
#include <queue>
#include <iostream>

template<typename T>
struct AVLNode {
	T Value;
	int Height = 1; //the height of the subtree
	AVLNode* Left;
	AVLNode* Right;
	AVLNode* Parent;

	AVLNode() = default;

	AVLNode(T v, AVLNode* l, AVLNode* r, AVLNode* p)
	:Value(v), Left(l), Right(r), Parent(p){}

	AVLNode & operator=(const AVLNode & N){
		Value = N.Value;
		Right = N.Right;
		Left = N.Left;
		Parent = N.Parent;
		Height = N.Height;
		return *this;
	}

	int SubTreeHeight()//I don't use this, but it's cool
	{
		if (this == nullptr){
	 		return 0;
		}
		std::queue<AVLNode<T> *> q;

		q.push(this);
		int height = 0;

		while (1){
	        int nodeCount = q.size();
	        if (nodeCount == 0){
	        	return height;
		}
	        height++;

	        while (nodeCount > 0){
	        	AVLNode<T>* node = q.front();
	        	q.pop();
	        	if (node->Left != nullptr){
	                	q.push(node->Left);
			}
	        	if (node->Right != nullptr){
	                	q.push(node->Right);
			}
        		nodeCount--;
	        }
	    }
	}
};

template<typename T>
struct AVLTree {
	AVLNode<T>* Head;

	AVLTree()
	:Head(nullptr){}

	/*
	AVLTree(T n){
		Head = new AVLNode<T>(n, nullptr, nullptr, nullptr);
	}*/

	 AVLTree(const AVLTree<T> & t){
                if (t.Head == nullptr){
			Head = nullptr;
                        return;
                }

		Head = new AVLNode<T>(*t.Head);
		AVLNode<T>* r = Head;
                AVLNode<T>* n;
		AVLNode<T>* temp;
                std::stack<AVLNode<T>*> Stack;
		std::stack<AVLNode<T>*> twoChild;

                 if (t.Head->Left){
                        Stack.push(t.Head->Left);
                 }
                 if (t.Head->Right){
                        Stack.push(t.Head->Right);
                 }

		twoChild.push(Head);
                while(!Stack.empty()){

                        n = Stack.top();
			//do visit
			AVLNode<T>* newAVLNode = new AVLNode<T>(*n);
			if (r->Value > n->Value){
				r->Left = newAVLNode;
			}else{
				r->Right = newAVLNode;
			}
			newAVLNode->Parent = r;
			r = newAVLNode;

			if (n->Left && n->Right){
				twoChild.push(r);
			}else if (!n->Left && !n->Right){
				//this resets r to the last node with two children so that our traversial of the new tree moves in step with our pre-order traversial
				if(!twoChild.empty()){
					r = twoChild.top();
                                	twoChild.pop();
				}
			}


                        Stack.pop();
                        if (n->Left){
                                Stack.push(n->Left);
                        }
                        if (n->Right){
                                Stack.push(n->Right);
                        }
                }
        }

	AVLTree & operator=(const AVLTree & t){
		AVLNode<T>* p = Head;
                AVLNode<T>* ThisParent;
                while (Head) {
			//erase(Head);

                        if (!p->Left && !p->Right){
                                ThisParent = p->Parent;
                                erase(p);
                                p = ThisParent;
                        } else if (!p->Left) {
                                p = p->Right;
                        } else {
                                p = p ->Left;
                        }
                }
		AVLTree newAVLTree = AVLTree(t);
		Head = newAVLTree->Head;
		return *this;

	}


	AVLNode<T>* find(T val) {
		AVLNode<T>* p = Head;
		while(p) {
                        if (val > p->Value) {
                                p = p->Right;
                        }else if (val < p->Value) {
                                p = p->Left;
                        }else{
				return p;
			}
                }
		return p;
	}

	void insert(T val) {
		if (Head == nullptr){
			AVLNode<T>* temp = new AVLNode<T>(val, nullptr, nullptr, nullptr);
			Head = temp;
			return;
		}
		AVLNode<T>* p = Head;
		AVLNode<T>* ThisParent;
		bool DidGoLeft;
		while(p) {
			ThisParent = p;
			if (val >=p->Value) {
				p = p->Right;
				DidGoLeft = false; //I'm not entirely happy with this
			}else {
				p = p->Left;
				DidGoLeft = true;
			}
		}
		AVLNode<T>* newAVLNode =  new AVLNode<T>(val, nullptr, nullptr, ThisParent);
		if (DidGoLeft){
			ThisParent->Left = newAVLNode;
		}else{
			ThisParent->Right = newAVLNode;
		}
		balance(newAVLNode);
	}

	void erase(AVLNode<T>* k){
		AVLNode<T>* p = k->Parent;
		if (k->Left && k->Right){
			AVLNode<T>* r = successor(k);
			k->Value = r->Value;
			erase(r); //r could have a right child
		}else if(k->Left){
			if (p->Left == k){
				p->Left = k->Left;
			}else{
				p->Right = k->Left;
			}
			k->Left->Parent = p;
			delete k;
		}else if(k->Right){
                        if (p->Left == k){
                                p->Left = k->Right;
                        }else{
                                p->Right = k->Right;
                        }
                        k->Right->Parent = p;
			delete k;
		}else{
			if (p->Left == k){
                                p->Left = nullptr;
                        }else{
                                p->Right = nullptr;
                       }
			delete k;
		}
	}

	AVLNode<T>* successor(AVLNode<T>* k){
		AVLNode<T>* p = k->Right;
		AVLNode<T>* ou                                Stack.push(n->Right)://gist.github.com/mibzman/d5bc6d29930f500c949a17bb29d6fc8btput;
		while (p){
			output = p;
			p = p->Left;
		}
		return output;
	}

	void print(){
		std::cout << "digraph G {" << std::endl;
		AVLNode<T>* n;
                std::stack<AVLNode<T>*> Stack;
		int counter = 0;
		int otherCounter = 0;

                Stack.push(Head);
                while(!Stack.empty()){
                        n = Stack.top();
                        //do visit
			if (!n->Parent){
				std::cout << "HEAD" << "->" << n->Value << ";" << std::endl;
			}else{
				std::cout << n->Parent->Value <<  "->" << n->Value  << ";" << std::endl;
			}
			if (!n->Left) {
				std::cout << n->Value << "->" << "Leftnull" << counter << ";" << std::endl;

			}
			if (!n->Right) {
                                std::cout << n->Value <<"->" << "Righttnull" << counter << ";" << std::endl;

                        }
			counter++;

                        Stack.pop();
                        if (n->Right){
                        }
                        if (n->Left){
                                Stack.push(n->Left);
                        }
        	}
		std::cout << "}";
	}

	//a convenience function because i'm that lazy
	void stitch(AVLNode<T>* parent, AVLNode<T>* child, bool IsLeft){
		if (IsLeft){
			parent->Left = child;
		}else{
			parent->Right = child;
		}
		if(child){
			child->Parent = parent;
		}
	}

	//assumes: https://upload.wikimedia.org/wikipedia/commons/2/23/Tree_rotation.png
	void rotateRight(AVLNode<T>* q, AVLNode<T>* p){
		if (q->Parent){
			AVLNode<T>* superRoot = q->Parent;
			if(superRoot->Left == q){
				stitch(superRoot, p, true);
			}else{
				stitch(superRoot, p, false);
			}
		}else{
			p->Parent = nullptr;
		}
		AVLNode<T>* a = p->Left;
		AVLNode<T>* b = p->Right;
		AVLNode<T>* c = q->Right;

		stitch(p, a, true);
		stitch(p, q, false);
		stitch(q, b, true);
		stitch(q, c, false);
	}

	void rotateLeft(AVLNode<T>* p, AVLNode<T>* q){
                if (p->Parent){
                        AVLNode<T>* superRoot = p->Parent;
                        if(superRoot->Left == p){
                                stitch(superRoot, q, true);
                        }else{
                                stitch(superRoot, q, false);
                        }
                }else{
                        q->Parent = nullptr;
                }

		AVLNode<T>* a = p->Left;
                AVLNode<T>* b = q->Left;
                AVLNode<T>* c = q->Right;

                stitch(q, p, true);
                stitch(q, c, false);
                stitch(p, a, true);
                stitch(p, b, false);
        }

	int getHeight(AVLNode<T>* p){//yet another lazy function
		if(p){
			return p->Height;
		}
		return 0;
	}

	void balance(AVLNode<T>* p){//where p is a newly inserted node
		if(!p){
			//breakpoint
		}
		if (p->Parent == nullptr){
			//std::cout <<"root";
			return;
		}
		//std::cout<<"balancing";

		int balance;
		AVLNode<T>* q = p->Parent;
		while(q){
			AVLNode<T> debug = *q;
			AVLNode<T> debug2 = *p;
			q->Height = std::max(getHeight(q->Left), getHeight(q->Right)) + 1;
			//std::cout << p->Height;
			balance = getHeight(q->Left) - getHeight(q->Right);
			if (balance == -2){
				//std::cout<< "rotate right";
				rotateRight(q, p);
				balance = 0;
				AVLNode<T>* temp = q;
				q = p;
				p = temp;
			}
			if (balance == 2){
				//std::cout<< "rotate left";
				rotateLeft(q, p);
                                balance = 0;
				AVLNode<T>* temp = q;
                                q = p;
                                p = temp;
			}

			p = p->Parent;
			q = q->Parent;
		}
	}


	~AVLTree(){
		AVLNode<T>* p = Head;
		AVLNode<T>* ThisParent;
		while (p) {
			if (!p->Left && !p->Right){
				ThisParent = p->Parent;
				if(ThisParent->Left == p){
					ThisParent->Left = nullptr;
				}else{
					ThisParent->Right = nullptr;
				}
				delete p;
				p = ThisParent;
			} else if (!p->Left) {
				p = p->Right;
			} else {
				p = p ->Left;
			}
		}
	}

};
