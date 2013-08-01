#include "common.h"

int quick_one_pass(Sqlist *L, int low, int high)
{
	int i=low;
	int j=high;
	
	L->R[0].key=L->R[i].key;
	
	do
	{
		while (j>i && L->R[j].key > L->R[0].key)
			j--;
		
		if (j>i)
		{
			L->R[i].key=L->R[j].key;
			i++;
		}
		
		while (j>i && L->R[i].key < L->R[0].key)
			i++;
		
		if (j>i)
		{
			L->R[j].key = L->R[i].key;
			j--;
		}
	}while(i!=j);

	L->R[i].key=L->R[0].key;
	return i;
}

void quick_sort(Sqlist *L, int low, int high)
{
	int k;
	if (low < high)
	{
		k=quick_one_pass(L, low, high);
		quick_sort(L, low, k-1);
		quick_sort(L, k+1, high);		
	}		
}


int main()
{
	Sqlist *L=(Sqlist *)malloc(sizeof(Sqlist));
	initial(L);
	print(L);
	quick_sort(L, 1, L->length);
	print(L);
	return 0;		
}
