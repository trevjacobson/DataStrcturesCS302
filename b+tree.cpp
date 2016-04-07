#include<iostream>
using namespace std;

struct BplusTreeNode
{
    int *data;				//data items in node
    BplusTreeNode **childPtr;		//pointers to other nodes
    bool leaf;				//leaf node boolean
    int n;				//number of data in the node
}

*root = NULL, *newNode = NULL, *x = NULL;

BplusTreeNode * init()					//initialize a node
{
    newNode = new BplusTreeNode;
    newNode->data = new int[5];				//5 internal data items
    newNode->childPtr = new BplusTreeNode *[6];		//6 possible pointers
    newNode->leaf = true;				//just initialized, so is a leaf
    newNode->n = 0;					//contains 0 items
    for (int i = 0; i < 6; i++)	
    {
        newNode->childPtr[i] = NULL;			//set all pointers null
    }
    return newNode;					//return initialized B+ tree node
}

void traverse(BplusTreeNode *p)			//in order traversal of the function to print it.
{
    int i;
    cout << endl;
    for (i = 0; i<p->n; i++)			//loop number of data items in node times
    {
        if (p->leaf == false)
        {
            traverse(p->childPtr[i]);		//traverse next child
        }
        cout << " " << p->data[i];		//print the data
    } 
    if (p->leaf == false)
    {
        traverse(p->childPtr[i]);
    }
    cout << endl;
}

void sort(int *p, int n)		//bubblesort to order the items within the current node
{
    int temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            if (p[i] > p[j])
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int split_child(BplusTreeNode *x, int i)	//function to split the child when it has too many items to be inserted into data
{
    int j, mid;
    BplusTreeNode *newNode1, *newNode3, *y;
    newNode3 = init();
    newNode3->leaf = true;
    if (i == -1)				//dealing with the root node
    {
        mid = x->data[2];		
        x->data[2] = 0;
        x->n--;
        newNode1 = init();
        newNode1->leaf = false;			
        x->leaf = true;				//x is now a leaf node
        for (j = 3; j < 5; j++)
        {
            newNode3->data[j - 3] = x->data[j];		//offset 3, newNode3 data equals x data
            newNode3->childPtr[j - 3] = x->childPtr[j]; //also set the pointers 
            newNode3->n++;				//increase data total in newNode3
            x->data[j] = 0;				//data in position j is gone
            x->n--;					//decrease data total in x
        }
        for(j = 0; j < 6; j++)
        {
            x->childPtr[j] = NULL;			//make all pointers in x null since transferred to newNode3
        }
        newNode1->data[0] = mid;			//newNode1 first item equals old middle value of x
        newNode1->childPtr[newNode1->n] = x;		//now points to node x
        newNode1->childPtr[newNode1->n + 1] = newNode3; //next pointer to newNode 3
        newNode1->n++;					//increased data items in newNode1
        root = newNode1;				//newNode 1 is the root
    }
    else
    {							//child to split is NOT a root node
        y = x->childPtr[i];				//node y equals the full node
        mid = y->data[2];				//break up in middle
        y->data[2] = 0;			
        y->n--;
        for (j = 3; j < 5; j++)
        {
            newNode3->data[j - 3] = y->data[j];		//offset 3, newNode3 equals y data
            newNode3->n++;				//increase data total
            y->data[j] = 0;				//erase data in y
            y->n--;					//decrease data total in y
        }
        x->childPtr[i] = y;				//now points to y
        x->childPtr[i + 1] = newNode3; 			//next pointer to newNode3
    }
    return mid;
}

void insert(int a)
{
    int i, temp;
    x = root;
    if (x == NULL)		//tree doesn't exist, make one
    {
        root = init();
        x = root;
    }
    else
    {
        if (x->leaf == true && x->n == 5)	//the root node is a leaf, and has 5 items (it is full) split into a child
        {
            split_child(x, -1);		//split the root node function call
            x = root;
            for (i = 0; i < (x->n); i++)
            {
                if ((a > x->data[i]) && (a < x->data[i + 1])) //found breakpoint, increase i and break from loop
                {
                    i++;
                    break;
                }
                else if (a < x->data[0])			//a is smallest, break loop
                {
                    break;
                }
                else	
                {
                    continue;					//keep looking
                }
            }
            x = x->childPtr[i];				//x is the next level, item gets inserted from pointer at location [i]
        }
        else
        {
            while (x->leaf == false)			//while not a leaf node
            {
            for (i = 0; i < (x->n); i++)
            {
                if ((a > x->data[i]) && (a < x->data[i + 1])) // found insertion point, break
                {
                    i++;
                    break;
                }
                else if (a < x->data[0])		//a is smallest, break loop
                {
                    break;
                }
                else
                {
                    continue;
                }
            }
                if ((x->childPtr[i])->n == 5)		//if node to be inserted into is full, split it at pointer location i
                {
                    temp = split_child(x, i);
                    x->data[x->n] = temp;		//data location is x->n and now equals temp value
                    x->n++;				//increase total data items in x
                    continue;
                }
                else
                {
                    x = x->childPtr[i];
                }
            }
        }
    }
    x->data[x->n] = a;				//store new inserted value
    sort(x->data, x->n);			//sort the data in node x
    x->n++;					//increase data total in x
}

int main()
{
    int i;
    int values[20] = {6, 12, 1, 21, 3, 19, 13, 9, 32, 8, 18, 5, 44, 22, 11, 33, 15, 4, 2, 10};
    cout << endl << "List of items to be inserted: " << endl;
    for(i = 0; i<20; i++)
	{
	     cout << values[i] << " " ;
	     insert(values[i]);
	}	
    cout << endl << endl << "In order traversal of constructed tree:" << endl;
    traverse(root);
    cout << endl << endl;
}
