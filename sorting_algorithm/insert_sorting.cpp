#include "common.h"
#include <cstdlib>
using namespace std;

void insert_sorting(Sqlist *L)
{
	int i,j;
	for (i=2; i<=L->length;i++)
	{
		L->R[0].key=L->R[i].key;
		j=i-1;
		while (L->R[0].key < L->R[j].key)
		{
			L->R[j+1].key=L->R[j].key;
			j--;		
		}
		L->R[j+1].key=L->R[0].key;
	}

}

void binary_insert_sorting(Sqlist *L)
{
	int i,j;
	int low, high, mid;
	for (i=2; i<=L->length; i++)
	{
		L->R[0].key=L->R[i].key;
		low=1;
		high=i-1;

		while (low<=high)
		{
			mid=(low+high)/2;
			if (L->R[0].key < L->R[mid].key)
				high=mid-1;
			else
				low=mid+1;		
		}

		for (j=i; j>low; j--)
			L->R[j].key=L->R[j-1].key;
		L->R[low].key=L->R[0].key;
	}
}

int main()
{
	Sqlist *L=(Sqlist *)malloc(sizeof(Sqlist));
	//L->length=3;
	//L->R[0].key=0;
	//L->R[1].key=5;
	//L->R[2].key=1;
	//L->R[3].key=3;
	initial(L);
	print(L);
	binary_insert_sorting(L);
	print(L);
	return 0;		
}


