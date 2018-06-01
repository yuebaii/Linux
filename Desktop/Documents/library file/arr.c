#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#define N 10
typedef struct Ds
{
   int *arr;
   int length;
   int lensize;
}Ds,*Dps;

void Initial(Dps ps)
{
    assert(ps != NULL);
    if(ps == NULL)
    {
        return ;
    }
    ps->arr = (int *)malloc(sizeof(int)*N);
    ps->length = 0;
    ps->lensize = N;
}

static int Full(Dps ps)
{
    return ps->length == ps->lensize;
}

static void kuorong(Dps ps)
{
    int *s = (int*)malloc(sizeof(int)*N*2);
	int i = 0;
    for(; i < ps->lensize; i++)
    {
       s[i] = ps-> arr[i];
    }
    free(ps->arr);
    ps->arr = s;
    ps->lensize = N*2;
}

int Insert(Dps ps, int pos, int val)
{
    if(pos<0 || pos>ps->lensize+1)
    {
          return -1;
     }
     if(Full(ps))
     {
         kuorong(ps);
     }
	 int i = 0;
     for(i = ps->lensize-1; i >= pos; i--)
     {
         ps->arr[i+1] = ps->arr[i];
      }
     ps->arr[pos] = val;
     ps->length++;
      return 0;
}

int Delete(Dps ps, int pos)
{
    if(pos<0 || pos>ps->lensize)
    {
        return -1;
     }
	int i = 0;
     for(i = pos; i < ps->length-1; i++)
     {
         ps->arr[i] = ps->arr[i+1];
      }
      ps->length--;
     return 0;
}

void main()
{
     Ds s;
    Initial(&s);
	int i = 0;
     for(i = 0; i < 12; i++)
     {
    Insert(&s,i,i);
    }
}
     
