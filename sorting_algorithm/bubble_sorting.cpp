#include "common.h"
#include <cstdlib>
using namespace std;

void bubble_sort(Sqlist *L)
{
	int i,k;
	bool flag;
	for (i=0; i<L->length; i++)
	{
		flag=true;
		
		for (k=1; k<L->length-i; k++)
		{
			if (L->R[k+1].key < L->R[k].key)
			{
				flag=false;
				L->R[0].key = L->R[k+1].key;
				L->R[k+1].key = L->R[k].key;
				L->R[k].key = L->R[0].key;		
			}		
		}

		if (flag==true)
			break;
	}
}

int main()
{
	Sqlist *L = (Sqlist *)malloc(sizeof(Sqlist));
	initial(L);
	print(L);
	bubble_sort(L);
	print(L);
	return 0;		
}
