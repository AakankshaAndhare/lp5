#include<iostream>
#include<algorithm>
#include<omp.h>
#include<ctime>

using namespace std;

 void merge(int arr1[],int l,int m,int r)
{
	int n1=m-l+1;
	int n2=r-m;
	int left[n1],right[n2];
	
	for(int i=0;i<n1;i++)
	{
		left[i]=arr1[l+i];
	}
		for(int j=0;j<n2;j++)
		{
			right[j]=arr1[m+1+j];
		}
		
		int i=0,j=0,k=l;
		
		while(i<n1 && j<n2)
		{
			if(left[i]<right[j])
			{
			arr1[k++]=left[i++];
			}
			else
			{
				arr1[k++]=right[j++];
			}
		}
		while(i<n1)
		{
			arr1[k++]=left[i++];
		}
		while(j<n2)
		{
			arr1[k++]=right[j++];
		}
	
}

void mergesortSequential(int arr1[],int l,int r)
{
	if(l<r)
	{
		int m = l+(r-l)/2;
		mergesortSequential(arr1,l,m);
		mergesortSequential(arr1,m+1,r);
		merge(arr1,l,m,r);
	}
}


void mergesortParallel(int arr1[],int l,int r)
{
	if(l<r)
	{
		int m = l+(r-l)/2;
		#pragma omp parallel sections 
		{
		#pragma omp section
		mergesortParallel(arr1,l,m);
		#pragma omp section
		mergesortParallel(arr1,m+1,r);
		}
	
		merge(arr1,l,m,r);
	}
}

int main()
{
	int arr1[]={1,2,3,0,6,8,4,5,9};
	int arr2[]={4,3,2,5,6,7,8,9,1};
	int N= sizeof(arr1)/sizeof(arr1[0]);
	
	double start=omp_get_wtime();
	mergesortSequential(arr1,0,N-1);
	double end=omp_get_wtime();
	cout<<"Seq"<<end-start<<endl;
	 
	start=omp_get_wtime();
	mergesortParallel(arr2,0,N-1);
    end=omp_get_wtime();
    cout<<"Parallel"<<end-start<<endl;
     
	return 0;
}
