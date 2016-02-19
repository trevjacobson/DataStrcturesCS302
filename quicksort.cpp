#include <iostream>
using namespace std;

int partition(int *A, int begin, int end) {		//functions sets the partition
	int pivot = A[end];
	int indexPartition = begin;      		//partition index set to beginning initially
	for(int i=begin; i<end; i++){
		if(A[i] <= pivot) {
			swap(A[i], A[indexPartition]);	//if the element is less than pivot, swap
			indexPartition++;
		}
	}
	swap(A[indexPartition], A[end]);		//swap the pivot with item at partition index
	return indexPartition;
}

void Qsort(int *A, int begin, int end){
	if(begin < end){
		int indexPartition = partition(A, begin, end);    //call the partition function
		Qsort(A, begin, indexPartition-1);
		Qsort(A, indexPartition+1, end);
	}
}

int main() {
	int A[] = {25, 12, 5, 39, 21, 9, 14, 29, 30, 2, 0, 40, 18};
	cout << "The initial list is: ";
	for(int i=0; i<13; i++)
		cout << A[i] << " ";
	cout << endl << "The list after being quicksorted is: ";
	Qsort(A, 0, 12);
	for(int j=0; j<13; j++)
		cout << A[j] << " ";
	cout << endl;
}
