#include <iostream>
#include <cstddef>

using namespace std;

struct nodeType
{
  int info;
  nodeType *next;
  nodeType *back;
};

class OrderedDoublyLinkedList
{
public:
  //This method returns true if the list is empty; otherwise false
  bool isEmpty();

  //insert x in the appropriate place in this lsit to keep it sorted
  void insertNode(int x);

  //delete one node(first occurence) from the list containing x
  void deleteNode(int x);

  OrderedDoublyLinkedList();

  //print contents of the list
  void print();


private:
  nodeType *first;
};



void OrderedDoublyLinkedList::deleteNode(int x){
  nodeType *prevPtr, *currPtr, *deletePtr;
  prevPtr = NULL;
  currPtr = first;
  while(currPtr != NULL && currPtr->info != x){
    prevPtr = currPtr;
    currPtr = currPtr->next;
  }
  if(currPtr != NULL){
    deletePtr = currPtr;        //node to be deleted
    if(currPtr == first){
      first = currPtr->next;
      first->back = NULL;
    }
    else  prevPtr->next = currPtr->next;   //prev points past deleted node
    if(currPtr->next == NULL){          //if currPtr is last item in list delete and return
      delete deletePtr;
      return;
    }
    else {                            //else node isn't last item in list 
      currPtr = currPtr->next;
      currPtr->back = prevPtr;       //node past deleted node points back to prevPtr 
    }
    delete deletePtr;
  }
}


void OrderedDoublyLinkedList::insertNode(int x){
  nodeType *currPtr, *prevPtr, *newNodePtr;
  newNodePtr = new nodeType;
  newNodePtr->info = x;             //newNode for the one being inserted
  if(first == NULL)
    first = newNodePtr;            //if list empty newNode = first ndoe

  else{
    currPtr = first;
    prevPtr = NULL;
    newNodePtr->next = currPtr;
    if(prevPtr == NULL)
      first = newNodePtr;
    else{
      prevPtr->next = newNodePtr;
      newNodePtr->back = prevPtr;        //if prevPtr != null then link back and forward
    }
  }

}

bool OrderedDoublyLinkedList::isEmpty(){  //if empty return true, else false
  if(first == NULL)
    return true;
  else return false;
}

OrderedDoublyLinkedList::OrderedDoublyLinkedList(){ //default constructor
  first = NULL;
}

void OrderedDoublyLinkedList::print(){
  nodeType *newNodePtr;
  newNodePtr = first;
  while(newNodePtr != NULL){
    cout << newNodePtr->info << " ";
    newNodePtr = newNodePtr->next;
  }
}

int main(){
	int val1 = 2, val2= 3, val3 = 5, val4 = 8, val5 = 12;
  OrderedDoublyLinkedList L1, L2, L3;     //two variables of OrderedDoublyLinkedList type
L1.insertNode(val3);
L1.insertNode(val2);
L1.insertNode(val1);
L1.insertNode(val5);
L1.insertNode(val4);

  cout << "List: ";  // print L1
  L1.print();
  cout << endl;

  cout << endl;
  return 0;
}
