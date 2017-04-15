#include<iostream>
#include<cmath>
using namespace std;


class Person{
public:
	Person();
	Person(int i, int e);
	~Person();

private:
	Person *parent, *child, *sibling; // the pointers to his parent, child, sibling
	int id; // record Person's id
	int energy; // record Person's energy
	int degree;// record how many levels of this Person's children
	friend class Promenade;//you could access all valuables in class Promenade
};

//ctor
Person::Person(){
	parent = child = sibling = NULL;
	id = 0;
	energy = 0;
	degree = 0;
}

//ctor
Person::Person(int i, int e){// define a new Person with id = i and energy = e
	parent = child = sibling = NULL;
	id = i;
	energy = e;
	degree = 0;
}

//dtor
Person::~Person(){

}

class Promenade{

public:
	Promenade();
	~Promenade();
	void one_person_joined(int id, int energy);
	void one_group_joined(Promenade *g);
	void absorb_energy(int id, int energy);
	int  calculate_people_below(int energy);
	int  get_weakest_person();
	int  size();
	//void merge(Person* ,Person* );
	void Union(Promenade *);
	void Merge(Promenade *);
	Person* Search(Person*,int);
	void deletemin();
	
private:
	Person *head;
	int num;//caculate how many people in the promenade
};

//ctor
Promenade::Promenade(){
	head = NULL;
	num = 0;
}

//dtor
Promenade::~Promenade(){

}
/*
void Promenade::merge(Person* y,Person* z){
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
}*/

void Promenade::Union(Promenade *A){
	
    Merge(A);  
    Person* pre = NULL;
    Person* x = head;
    Person* next = x -> sibling;
    while(next){
        if( (x->degree != next->degree) || (next->sibling && next->sibling->degree == x->degree)){
            pre = x;  
            x = next;  
        }
        else if( x -> energy <= next -> energy){ 
            x -> sibling = next -> sibling; 
            //merge(next,x);
			next -> parent = x;
			next -> sibling = x -> child;
			x -> child = next;
			x -> degree++;             
        }
        else{
            if(!pre) head = next;           
            else pre->sibling = next;       
            //merge(x,next);
			x -> parent = next;
			x -> sibling = next -> child;
			next -> child = x;
			next -> degree++;           
            x = next;                    
        }
        next = next->sibling;           
    }
}


void Promenade::Merge(Promenade *A){
	Person* head1 = head;
	Person* head2 = A -> head;
	Person* newhead;
	Person* cur;
	if(!head1){          
	    head = head2;
	    return ;
	}
	else if(!head2) return ;
	  

	if(head1 -> degree > head2 -> degree){
	        newhead = cur = head2;
	        head2 = head2->sibling;
	}
	else {
	        newhead = cur = head1;
	        head1 = head1->sibling;
	}

	while(head1 && head2){
	    if(head1->degree < head2->degree){
	        cur->sibling = head1;
	        cur = head1;
	        head1 = head1 -> sibling;
	    }
	    else {
		    cur -> sibling = head2;
	        cur = head2;
	        head2 = head2 -> sibling;
	    }
	}
	while(head1){
	    cur -> sibling = head1;
	    cur = head1;
	    head1 = head1 -> sibling;
	}
	while(head2){
	    cur -> sibling = head2;
	    cur = head2;
	    head2 = head2->sibling;
	}
    head = newhead;
}

Person* Promenade::Search(Person* h,int key)
{
    Person* tmp= h;
    Person* p = NULL;
    if (tmp -> id == key){
        p = tmp;
        return p;
    }
    if (tmp -> child && !p )
        p = Search(tmp -> child, key);
    if (tmp -> sibling  && !p )
        p = Search(tmp -> sibling, key);
    return p;
}
	
void Promenade::deletemin(){
    int min = head -> energy;
    Person* tmp = head;
    Person* mpre = NULL;
    Person* mnext = head;
   	
     while(tmp->sibling){
        if(tmp -> sibling -> energy < min){
            min = tmp -> sibling -> energy;
            mpre = tmp;
            mnext = tmp -> sibling;
        }
        tmp = tmp -> sibling;
    }
    if(!mpre && mnext)
     head = mnext -> sibling;
    else if(mpre && mnext)
        mpre -> sibling = mnext -> sibling;
    

    Person *pre,*cur;
    
     pre = tmp = NULL;
    cur = mnext -> child; 
    while(cur){
        tmp = cur -> sibling;
        cur -> sibling = pre;
        cur -> parent = NULL;
        pre = cur;
        cur = tmp;
    }
  Promenade *A=new Promenade();
  A -> head = pre;
  Union(A);
}
	


void Promenade::one_person_joined(int id, int energy){
	//TODO: fill in the code to simulate a person with his id and energy to join the Promenade
	Promenade *h = new Promenade();
	Person* newnode = new Person(id,energy);
	h -> head = newnode;
	Union(h);
	num++;
}

void Promenade::one_group_joined(Promenade *g){
	//TODO: fill in the code to simulate one group to join the full promenade
    Person* tmp = g -> head;
    int n;
    while(tmp){
        n = pow(2,tmp -> degree);
		num += n; 
        tmp = tmp->sibling;
    }
	Union(g);	
}

void Promenade::absorb_energy(int id, int energy){
	//TODO: Elizabeth absord the energy of the person with this id, this Person's energy will decrease by this number.
	//If his energy becomes lower than or equal to zero, he will die and should be thrown out automatically
	
	Person *key = Search(head,id);
	if(!key)return;
	else   {
	    key -> energy -= energy;
	    if(key -> energy <= 0){
	    	
	        Person* parent = key -> parent;;
		    while(parent){
			    int temp = parent -> energy;
			    int name = parent -> id;
				parent -> energy = key -> energy;
			    key -> energy = temp;
			    parent -> id = key -> id;
			    key -> id = name;
			    key = parent;
			    parent = parent -> parent;			    
		    }
		    if(num == 1) head = NULL;
		    else  deletemin();
			num--;
			return;
	    }
	    else if(key -> energy > 0)
	    {
		    Person* parent = key -> parent;
			while(  (parent) && key -> energy < parent -> energy ){
			    int t1 = parent -> energy;
			    parent -> energy = key -> energy;
			    key -> energy = t1;
			    int t2 = parent -> id;
			    parent -> id = key->id;
			    key->id = t2;
			    key = parent;
				parent = parent -> parent;	
		    }
		    return;
	    }
	    
	  }	
}

int Promenade::calculate_people_below(int energy){
	//TODO: You should calculate how many people's energy are below the number (include the number) and return it
	int n = 0;
	Person* a = head;
	Person* tmp;
	while(a){
	    if(a -> energy <= energy){
			n++;
	        if(a -> child) a = a -> child;
		    else if(a -> sibling) a = a -> sibling;
		    else if(a -> parent) a = a -> parent -> sibling;
		    else return n;
	    }
	    else if(a -> sibling) a = a -> sibling;
	    else if(a -> parent) a = a -> parent -> sibling;	
	    else return n;		
	}
	return n;
}

int Promenade::get_weakest_person(){
	//TODO: return the id of the one with the least energy left. If there are more than one solution, just return one of them
     Person* tmp = head;
     Person* weak = NULL;
     int min = 1000000; 
     if(tmp == NULL) return 0;
	 while(tmp != NULL){
           if(tmp -> energy < min){
               min = tmp -> energy;
   	           weak = tmp;
		    }
           tmp = tmp -> sibling;
    }
    return weak -> id;
}

int Promenade::size(){
	return num;

}

