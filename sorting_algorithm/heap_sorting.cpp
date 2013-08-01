#include "common.h"

void heap_adjust(Sqlist *L, int s, int n)
{
	int j=s*2;
	L->R[0].key = L->R[s].key;
	
	while (j<=n)
	{
		if (j<n && L->R[j+1].key > L->R[j].key)
		{
			j++;		
		}

		if (L->R[j].key > L->R[0].key)
		{
			L->R[j/2].key = L->R[j].key;
			j=j*2;		
		}
		else
			break;
	}

	L->R[j/2].key = L->R[0].key;

}

void heap_sort(Sqlist *L)
{
	int k;

	for (k=L->length/2; k>=1; k--)
	{
		heap_adjust(L, k, L->length);		
	}

	for (k=L->length; k>1; k--)
	{
		L->R[0].key = L->R[k].key;
		L->R[k].key = L->R[1].key;
		L->R[1].key = L->R[0].key;
		
		heap_adjust(L, 1, k-1);
			
	}
}

int main()
{
	Sqlist *L=(Sqlist *)malloc(sizeof(Sqlist));
	initial(L);
	print(L);
	heap_sort(L);
	print(L);
	return 0;		
}
