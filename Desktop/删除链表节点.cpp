offer18

#include<iostream>
using namespace std;

void DeleteNode(ListNode **pListHead, ListNode*pToBeDeleted)//O(1)
{
	if(pListHead==NULL && pToBeDeleted==NULL)
	{
		return;
	}
	//删除非尾节点
	if(pToBeDeleted->next != NULL)
	{
		ListNode *pNode = pToBeDeleted->next;
		*pToBeDeleted = *pNode;
		pToBeDeleted->next = pNode->next;
		delete pNode;
	}
	else if(pToBeDeleted == *pListHead)//删除头（尾）结点，链表只有一个元素
	{
		delete pListHead;
		pToBeDeleted = NULL;
		pListHead = NULL;
	}
	else{								//删除尾节点
		ListNode *pNode = *pListHead;
		while(pNode->next != pToBeDeleted)
		{
			pNode = pNode->next;
		}
		
		pNode->next = NULL;
		delete pToBeDeleted;
		pToBeDeleted = NULL;
	}
}