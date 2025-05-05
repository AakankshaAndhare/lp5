#include<iostream>
#include<omp.h>
#include<algorithm>
#include<ctime>

using namespace std;

void bubbleSortSequential(int arr1[],int n)
{
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(arr1[j]>arr1[j+1])
			{
				swap(arr1[j],arr1[j+1]);
			}
		}
		
	}
	
}


void bubbleSortParallel(int arr2[],int n)
{
		#pragma omp parallel for 
		
	for(int i=0;i<n-1;i++)
	{
	
		
		for(int j=0;j<n-i-1;j++)
		{
			if(arr2[j]>arr2[j+1])
			{
				swap(arr2[j],arr2[j+1]);
			}
		
	}
	}
	
}
int main()
{
	int arr1[]={1,4,5,2,3,6,9,8,7};
	int arr2[]={9,8,7,6,5,4,3,2,1};
	int N=sizeof(arr1)/sizeof(arr1[0]);
	
	double start= omp_get_wtime();
	bubbleSortSequential(arr1,N);
	double end=omp_get_wtime();
	cout<<"Sequential"<<end-start<<endl;
	
    start= omp_get_wtime();
	bubbleSortParallel(arr2,N);
	end=omp_get_wtime();
	cout<<"Parallel"<<end-start<<endl;
	
}
