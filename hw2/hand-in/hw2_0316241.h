#include <iostream>
using namespace std;

class node{
public:
	node();
	node(int value);
	~node();
	friend void gothrough(node *p);

private:
	node *left, *right; // the left child and the right child pointer
	int number; // record the node's number
	int is_threadl, is_threadr; //the flag to record whether the pointer is a thread or not

	friend class op_tree_totum;//you could access all valuables in class op_tree_totum
};

//ctor
node::node(){
	left = right = NULL;
	is_threadl = 1;
	is_threadr = 1;
}

//ctor
node::node(int value){
	number = value;
	left = right = NULL;
	is_threadl = 1;
	is_threadr = 1;
}

//dtor
node::~node(){

}

class op_tree_totum{

public:
	op_tree_totum();
	~op_tree_totum();
	void insertion(int s);
	void deletion(int s);
	void inorder_run();
	void reverseorder_run();
	int size();

private:
	node *root, *head, *tail;
	int num;//caculate how many nodes in the totum
};

//ctor
op_tree_totum::op_tree_totum(){
	head = new node();
	tail = new node();
	head->right = tail; //initialize the head node to connect to the tail node
	tail->left = head;
	root = NULL;
	num = 0;
}

//dtor
op_tree_totum::~op_tree_totum(){
	node *p = root;
	gothrough(p); // walk through the tree from the root node to delete all nodes connected
	num = 0;
	if (head != NULL)delete head;
	if (tail != NULL)delete tail;
}

void gothrough(node *p){
	if (p->left) gothrough(p->left);
	if (p->right) gothrough(p->right);
	if (p->left == NULL && p->right == NULL)delete p;
}

void op_tree_totum::insertion(int s){
	//TODO: fill in the code to do the insertion of the node with number s
    num++;
    if(root == NULL) {
    	root = new node(s);
    	root -> right = root;
    	root -> left = root;
    	head -> left = root;
    	tail -> right = root;
    }
    else {
    	node* current = root;
    	while (1) {
    		if(s > current -> number) {
    		    if(current ->is_threadr == 1) break;
				else current = current -> right;
    		}
    		else {
    		    if(current -> is_threadl == 1) break;
				else current = current -> left;
    		}
        }
        node* a = new node(s);
    	if(s < current -> number){
    	    if(head -> left == current) head -> left = a;
			    a -> left = current -> left;
			    current -> left = a;
    		    current -> is_threadl = 0;
    		    a -> right = current;
		    
		}
    	else{
    		if(tail -> right == current) tail -> right = a;
			    a -> right = current -> right;
			    current -> right = a;
    		    current -> is_threadr = 0;
    		    a -> left = current;  
		}
    }
    
}

void op_tree_totum::deletion(int s){
	//TODO: fill in the code to do the deletion of the node with number s
    int find;
    if(!root);
    else {
    	node* current = root;
    	node* parent ;
		while(1){
    		if(current -> number == s){
    			find = 1;
    			break;
    		}
    		else {
				parent = current;
    			if(s > current -> number) {
    		        if(current ->is_threadr == 1) break;
				    else current = current -> right;
    		    }
    		    else {
    		        if(current -> is_threadl == 1)break;
				    else current = current -> left;
    		    }
    		}
    	}
    	if(!find);
    	else{
    		num--;
    		if(current == root) {
    			node* tmp ;
    			node* tmp1 = root;
    			node* tmp2 ;
				if(current -> is_threadr == 1){
					tmp = root -> left;
					while (tmp -> is_threadr == 0) {
					    tmp1 = tmp;
					    tmp = tmp -> right;
				    }
    			    current -> number = tmp -> number;
    			    if(tmp -> is_threadl == 0) {
    				    tmp1 -> right = tmp -> left;
    				    tmp2 = tmp -> left;
    				    while(tmp2 -> is_threadr == 0) tmp2 = tmp2 -> right;
					    tmp2 -> right = root;
					    if(tail -> right == tmp) tail -> right = tmp2;
    			    }
    			    else {
    				    if(tmp == current -> left) {
    					    tmp1 -> left = root;
    					    tmp1 -> is_threadl = 1;
    					
    				    }
					    else{
						    tmp1 -> right = root;
    				        tmp1 -> is_threadr = 1;
					    }
    				    if(tail -> right == tmp) tail -> right = tmp1;
    			    }
    			delete tmp;
				}
				else {
				    tmp = root -> right;
				    while (tmp -> is_threadl == 0) {
					    tmp1 = tmp;
					    tmp = tmp -> left;
				    }
    			    current -> number = tmp -> number;
    			    if(tmp -> is_threadr == 0) {
    				    tmp1 -> left = tmp -> right;
    				    tmp2 = tmp -> right;
    				    while(tmp2 -> is_threadl == 0) tmp2 = tmp2 -> left;
					    tmp2 -> left = root;
					    if(tail -> right == tmp) tail -> right = tmp2;
    			    }
    			    else {
    				    if(tmp == current -> right) {
    					    tmp1 -> right = root;
    					    tmp1 -> is_threadr = 1;
    					
    				    }
					    else{
						    tmp1 -> left = root;
    				        tmp1 -> is_threadl = 1;
					    }
    				    if(tail -> right == tmp) tail -> right = tmp1;
    			    }
    			delete tmp;
    		    }
    		}
			else if(current -> is_threadl == 1 && current -> is_threadr == 1){
    			if(head -> left == current) head -> left = parent;
				if(tail -> right == current) tail -> right = parent;
				if(parent -> right == current) {
    					parent -> is_threadr = 1;
    					parent -> right = current -> right;
    					delete current;
    			}
    			else {
    				parent -> is_threadl = 1;
    				parent -> left = current -> left;
					delete current;
    			}
    		}
			else if((current -> is_threadl == 1 && current -> is_threadr == 0) || (current -> is_threadl == 0 && current -> is_threadl == 1)){
    			if(head -> left == current) {
    			    	node* tmp = current -> right;
    			    	while(tmp -> is_threadl == 0) tmp = tmp -> left;
						head -> left = tmp ;
    			    }
    		    if(tail -> right == current) {
    				node* tmp = current -> left;
    				while(tmp -> is_threadr == 0) tmp = tmp -> right;
					tail -> right = tmp ;
    			}
				if(current -> is_threadl == 1 && current -> is_threadr == 0){
    			    
					if(parent -> right == current){
    					parent -> right = current -> right;
						node* b = current -> right;
						while(b -> is_threadl == 0) b = b -> left;
						b -> left = current -> left; 
						delete current; 
    				}
    				else{
    					parent -> left = current -> right;
    					node* b = current -> right;
    					while(b -> is_threadl == 0) b = b -> left;
						b -> left = current -> left;
						delete current;
    				}
    			}
    			else{
    				
					if(parent -> right == current){
						parent -> right = current -> left;
						node* b = current ->left;
						while(b -> is_threadr == 0) b = b -> right;
						b -> right = current -> right;
						delete current; 
    				}
    				else{
						parent -> left = current ->left;
						node* b = current -> left;
						while(b -> is_threadr == 0) b = b -> right;
						b -> right = current -> right;
						delete current;
    				}
    			}
    		}
    		else if(current -> is_threadl == 0 && current -> is_threadr == 0){
    			node* tmp = NULL;
    			tmp = current -> right;
				
    			if(tmp -> is_threadr == 1 && tmp -> is_threadl ==1){
    				if(tail -> right == tmp) tail -> right = current;
					current -> number = tmp -> number;
    				current -> right = tmp -> right;
    				current -> is_threadr = tmp -> is_threadr;
					delete tmp;
    			}
    			else {
    			    if(tmp -> is_threadl == 0){
    				    node* tmp1 = NULL;
    				    
    				    
    				    while(tmp -> is_threadl == 0){
    				    	 tmp1 = tmp;
							 tmp = tmp -> left;
						} 
    				    tmp1 -> left = tmp -> left;
    				    tmp1 -> is_threadl = tmp -> is_threadl;
						current -> number = tmp -> number;
    				    
						delete tmp; 
    		        }
    		        else{
    		        	if(tail -> right == tmp) tail -> right = current;
						current -> number = tmp -> number;
    		        	current -> right = tmp -> right;
    		        	current -> is_threadr = tmp -> is_threadr;
						delete tmp;
    		        }
    			}
    		}
    	}
    }
}

void op_tree_totum::inorder_run(){
	//TODO: travel the tree from the head node to the tail node and output the values
	//You should NOT use stack or recurtion 
    node* tmp = head->left;
	while(tmp != tail -> right ){
		    if(tmp -> is_threadr == 0) {
				cout<<tmp->number<<" ";
				tmp = tmp -> right;
				while(tmp -> is_threadl == 0) tmp = tmp -> left;
			}
			else {
				cout<<tmp->number<<" ";
				tmp = tmp -> right;
			}
    }
    cout<<tmp->number<<" ";
}

void op_tree_totum::reverseorder_run(){
	//TODO: travel the tree from the tail node to the head node and output the values
	//You should NOT use stack or recurtion 
    node* tmp = tail->right;
		while(tmp != head -> left ){
			if(tmp -> is_threadl == 0) {
				cout<<tmp->number<<" ";
				tmp = tmp -> left;
				while(tmp -> is_threadr == 0) tmp = tmp -> right;
			}
			else {
				cout<<tmp->number<<" ";
				tmp = tmp -> left;
			}
        }
		cout<<tmp->number<<" "; 
}

int op_tree_totum::size(){
	return num;
}
