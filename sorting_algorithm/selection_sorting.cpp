#include "common.h"

void simple_selection_sort(Sqlist *L)
{
	int i, j;
	int min;
	for (i=1; i<L->length; i++)
	{
		min=i;
		L->R[0].key = L->R[i].key;
		for (j=i; j<=L->length; j++)
		{
			if(L->R[j].key < L->R[0].key)
			{
				L->R[0].key = L->R[j].key;
				min=j;		
			}
		}
		
		if (min!=i)
		{
			L->R[0].key = L->R[min].key;
			L->R[min].key = L->R[i].key;
			L->R[i].key = L->R[0].key;		
		}		
	}
}

int main()
{
	Sqlist *L = (Sqlist *)malloc(sizeof(Sqlist));
	initial(L);
	print(L);
	simple_selection_sort(L);
	print(L);
	return 0;		
}
