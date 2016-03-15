#include <iostream>
#include <cstddef>

using namespace std;

 struct binNode
{
   int info;
   binNode *lc;
   binNode *rc;
};

class binarySearchTree
{
public:
 binarySearchTree(); // default constructor

 bool isEmpty();  //returns true if tree is empty

 bool insertNode(int item);  //insert item left subtree < root OR right subtree > root

 void deleteNode(int item);  //delete item if it exists in tree

 void printRoot();  // print root of tree

 void printLength(); // print # of elements in tree

 void clear(); // clear all contents of the tree

 bool find(int item);  //search for a given item, return true if it is present

 void printInOrder();

 int getSmallest();

private:
  binNode *root;
  int nodeCnt;
  void removeall(binNode *ptr); // clear contents of the tree
  void printInOrderPrivate(binNode *ptr); //print contents of list smallest to largest
  void deleteNodePrivate(int item, binNode *parent); //find node to be deleted, calls deleteMatch/Root when necessary to delete node
  void deleteRoot(); //special function to delete the root
  void deleteMatch(binNode *parent, binNode *match, bool lc); //only called by deleteNodePrivate, actually deletes the node
  int getSmallestPrivate(binNode *ptr); //finds the smallest value of the right subtree given a pointer
};

int binarySearchTree::getSmallest(){ //user only has to call this function so they dont have to pass a root
  return getSmallestPrivate(root);
}

int binarySearchTree::getSmallestPrivate(binNode *ptr){ //search for the smallest value given some node and return the value
  if(root == NULL){
    cout << "The tree is empty" << endl;
    return -10000;
  }
  else{
    if(ptr->lc != NULL){
      return getSmallestPrivate(ptr->lc);
    }
    else{
      return ptr->info;
    }
 }
}

void binarySearchTree::deleteMatch(binNode *parent, binNode *match, bool lc){ //the parent and match are used as a 
  binNode *deletePtr;                                         //relatoinship to know if it is the left, or right child
  int infoMatch = match->info;                                //that needs to be deleted
  int smallestRight;
  if(match->lc == NULL && match->rc == NULL){           // caso 0 match has no children
     deletePtr = match;
     lc == true ? parent->lc = NULL : parent->rc = NULL; //if match is parents left/right child, set pointer to null
     delete deletePtr;
     nodeCnt--;
     cout << "The node containing " << infoMatch << " was removed" << endl;
  }
  else if(match->lc == NULL && match->rc != NULL){  //case 1 match has no left child, but has right child
     lc == true ? parent->lc = match->rc : parent->rc = match->rc; //if match is left child of parent, parents left child is now matches right child
     match->rc = NULL;  //otherwise match is the right child of parent, parents new right child is matches right child
     deletePtr = match;  //delete match
     delete deletePtr;
     nodeCnt--;
     cout << "The node containing " << infoMatch << " was removed" << endl;
  }
  else if(match->lc != NULL && match->rc == NULL){ //case 1 match has no right child, but has left child
     lc == true ? parent->lc = match->lc : parent->rc = match->lc; //if match is right child of parent, parents right child is now matches left child
     match->lc = NULL;  //otherwise match is the left child of parent, parents new left child is matches left child
     deletePtr = match;
     delete deletePtr;  //delete match
     nodeCnt--;
     cout << "The node containing " << infoMatch << " was removed" << endl;
  }
  else{
    smallestRight = getSmallestPrivate(match->rc); //the node to be removed has two children, find smallest in right subtree and save
    deleteNodePrivate(smallestRight, match);       //pass deleteNodePrivate smallestRight and match node location then delete smallestRight node
    match->info = smallestRight;                   //replaces the node to be deleted with smallestRight
  }
}

void binarySearchTree::deleteRoot(){ //function dedicated if user wants to delete root  
  if(root != NULL){                  //deletes smallest values node in right subtree
    binNode *deletePtr = root;       //and replaces roots value with the smallest value in the right subtree
    int item = root->info;           
    int smallestRight;               //save the item & save the smallest item in right subtree
    if(root->rc == NULL && root->lc == NULL){
       root = NULL;                             //root is the only item in the list, delete it 
       delete deletePtr;
     }
     else if(root->lc == NULL && root->rc != NULL){ //case right child full, left child empty
       root = root->rc;                             //new root is the old roots right child
       delete deletePtr;
       cout << "The root node was deleted. The new root is " << root->info << endl;
     }
     else if(root->lc != NULL && root->rc == NULL){ //case left child full, right child empty
       root = root->lc;                             //new root is the old roots right child
       delete deletePtr;
       cout << "The root node was deleted. The new root is " << root->info << endl;
     }
     else{
       smallestRight = getSmallestPrivate(root->rc); //root has 2 children, find smallest value in right subtree
       deleteNodePrivate(smallestRight, root);       //delete the smallest values node
       root->info = smallestRight;                   //replace the root value with smallest value
       cout << "The root node was replaced. The new root is " << root->info << endl;
     }
     nodeCnt--;
  }
}

void binarySearchTree::deleteNodePrivate(int item, binNode *parent){ // main routine for deleting a node in the tree
  if(root != NULL){
     if(root->info == item){  // if the item to be deleted is the root, use helper function dedicated to deleting root
        deleteRoot();
      }
      else{
        if(item < parent->info && parent->lc != NULL){ //item is in left subtree 
           parent->lc->info == item ?                  //is left child equal to item? if so call delete match
             deleteMatch(parent, parent->lc, true) :   //otherwise recurse this function to next node
             deleteNodePrivate(item, parent->lc);
         }
        else if(item >= parent->info && parent->rc != NULL){ //item is in right subtree 
           parent->rc->info == item ?                        //is right child equal to item? if so call delete match
             deleteMatch(parent, parent->rc, false) :        //otherwise recurse this function to next node
             deleteNodePrivate(item, parent->rc);
         }
        else{
           cout << "The item " << item << " is not in the tree." << endl; // item not present, display message
        }
      }
  }
  else{
    cout << "The tree is empty" << endl;  // tree empty message
  }
}

void binarySearchTree::deleteNode(int item){ // given item, calls function so user doesn't have to specify root location
  deleteNodePrivate(item, root);
} 

void binarySearchTree::clear(){  // calls a function so user doesnt specify root to clear all items in tree
 removeall(root);                // then set root to null, and node count to 0;
 root = NULL;
 nodeCnt = 0;
}

void binarySearchTree::removeall(binNode *ptr){ // completely clear the tree of all items
    if(ptr == NULL)
      return;
    removeall(ptr->lc);
    removeall(ptr->rc);
    delete ptr;
}


void binarySearchTree::printInOrderPrivate(binNode *ptr){ // recursively call itself by traversing the tree
 if(root !=NULL){                                         // completely, and then printing items in order from 
   if(ptr->lc !=NULL){                                    // smallest to largest.
     printInOrderPrivate(ptr->lc);
    }
   cout << ptr->info << " ";
   if(ptr->rc != NULL){
     printInOrderPrivate(ptr->rc);
    }
  } 
 else
 {
    cout << "The tree is empty" << endl;
 }
}

void binarySearchTree::printInOrder(){ //call private function so user doesn't have to specify root
printInOrderPrivate(root);
}

binarySearchTree::binarySearchTree(){root = NULL; nodeCnt = 0;}

bool binarySearchTree::insertNode(int item){  // function for inserting nodes as per binary search tree structure.
 if(root == NULL){                  // empty tree, create new item as root
   binNode *newNode;
   newNode = new binNode;
   newNode->info = item;
   root = newNode;
   nodeCnt++;
   return true;
 }
 binNode *temp, *prev, *newNode;
 temp = root;
 while(temp){  
   prev = temp;
   if(item < temp->info)        //search for the proper location to put the new item, save location
      temp = temp->lc;
   else if(item >= temp->info)
      temp = temp->rc;
 }
 if(prev->info <= item){   // if the item is larger, insert into right child location
   newNode = new binNode;
   newNode->info = item;
   prev->rc = newNode;
   nodeCnt++;
   return true;
  }
 else
   newNode = new binNode; //item is smaller, insert into left child
   newNode->info = item;
   prev->lc = newNode;
   nodeCnt++;
   return true;
}

bool binarySearchTree::find(int item){  //search for item in list, return true if present
  binNode *temp;
  temp = root;
  while(temp != NULL){
    if(temp->info == item)
      break;
    if(item >= temp->info)
      temp = temp->rc;
    else if(item < temp->info)
      temp = temp->lc;
   }
  if(temp == NULL)
     return false;
  if(temp->info == item)
     return true;
}   
  

bool binarySearchTree::isEmpty(){ //if list is empty return true
  if(root == NULL)
     return true;
  else return false;
} 

void binarySearchTree::printLength(){ // print the total number of items in the tree
  cout << "Number of elements in the tree: " << nodeCnt << endl;
}

void binarySearchTree::printRoot(){ // print the root of the tree
if(root != NULL)
  cout << "The root of the tree is: " << root->info << endl;
 else
   cout << "There is no root" << endl;
}

int main(){
binarySearchTree T1;
int x = 5;
if(T1.isEmpty())
cout << "The tree is empty" << endl;
T1.insertNode(8); T1.insertNode(12);
T1.insertNode(7); T1.insertNode(9);
T1.insertNode(5); T1.insertNode(11);
T1.insertNode(2); T1.insertNode(15);
T1.insertNode(1); T1.insertNode(25);
cout << endl << "After inserting items into the tree " << endl;
T1.printRoot();
cout << "The tree printed in order is: ";
T1.printInOrder();
cout << endl << endl;
cout << "The smallest value in the tree is: " << T1.getSmallest() << endl;
cout << endl;
T1.printLength();
cout << endl << "Deleting a node " << endl;
T1.deleteNode(7);
cout << "The updated list after deleting item: ";
T1.printInOrder();
cout << endl;
cout << endl;
T1.printLength();
cout << endl << "Attempting to delete an item not present in the list " << endl;
T1.deleteNode(100);
cout << endl << "Finding if an item is present in the tree " << endl;
if(T1.find(x))
  cout << "The number " << x << " is in the tree" << endl;
else cout << "The number " << x << " is not in the tree" << endl;
x = 32;
if(T1.find(x))
  cout << "The number " << x << " is in the tree" << endl;
else cout << "The number " << x << " is not in the tree" << endl;
T1.clear();
cout << endl << "After using the clear function contents of list: ";
T1.printInOrder();
cout << endl;
T1.printLength();

return 0;
}
