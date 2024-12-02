#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void display(int * A , int n){
	for(int i = 0 ; i<n ; i++){
		cout<<A[i]<<" ";
	}
	cout<<endl;
}

int random_partition(int * A , int p , int r){
	int pivot = p + rand() % (r-p+1);
	swap(A[pivot] , A[r]);
	
	int x = A[r];
	int i = p-1;
	
	for(int j = p ; j<r ; j++){
		if(A[j] < x){
			i++;
			swap(A[i] , A[j]);
		}
	}
	
	swap(A[i+1] , A[r]);
	return i+1;
}


int Select(int * A , int p ,int r , int i){
	if(p==r){
		return A[p];
	}
	
	int pivot = random_partition(A , p ,r);
	
	int a = pivot - p + 1;
	
	if (i == a){
		return A[pivot];
	}
	else if(i<a){
		return Select(A , p , pivot-1 , i);
	}
	else{
		return Select(A , pivot+1 , r , i-a);
	}
}

int main(){
	int n , i;
	cout<<"Enter the size of array : ";cin>>n;
	int * A = new int[n];
	for(int i=0 ; i<n ; i++){
		cin>>A[i];
	}
	display(A,n);
	cout<<"Enter the index : ";cin>>i;
	int elem = Select(A, 0 , n-1 , i);
	cout<<"Element at "<<i<<" th index : "<<elem<<endl;
	return 0;
}
