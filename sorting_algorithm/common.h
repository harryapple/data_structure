#include <iostream>
#include <cstdlib>
using namespace std;
#define MAX_SIZE 100
#define RADIX 10
#define BIT_KEY 8


/////////////////////////////////////
//define struct

typedef int KeyType;

typedef struct RecType
{
	KeyType key;		
}RecType;

typedef struct Sqlist
{
	RecType R[MAX_SIZE];
	int length;		
}Sqlist;

typedef struct RList
{
	KeyType value;
	struct RList *next;		
}RList;

/////////////////////////////////////

void print(Sqlist *L);
void initial(Sqlist *L);
void radix_init(RList *&head);
