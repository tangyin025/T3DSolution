/**
 * File: T3DLIB2/t3dlib6.h
 */

#ifndef __T3DLIB6_H__
#define __T3DLIB6_H__

#include "t3dcommons.h"

#define SLIST_SIZE_INCREMENT			(10)

template <typename ELEM_T>
struct SLIST_NODE
{
	ELEM_T elem;
	size_t next_i;

};

template <typename ELEM_T>
struct SLIST
{
	struct SLIST_NODE<ELEM_T> * nodes;
	size_t size;
	size_t length;
	size_t head_i;
	size_t rear_i;

	_CTOR_DECLARE(SLIST);
	_DTOR_DECLARE(SLIST);

};

_CTOR_IMPLEMENT_T1(SLIST, ELEM_T);
_DTOR_IMPLEMENT_T1_W1(SLIST, ELEM_T, Destroy_SList, nodes);

template <typename ELEM_T>
bool Create_SList(SLIST<ELEM_T> * plist, const size_t msize)
{
	assert(plist->nodes == NULL);

	SLIST_NODE<ELEM_T> * p = NULL;
	if(NULL == (p = (SLIST_NODE<ELEM_T> *)malloc((msize + 1) * sizeof(*p))))
		ON_ERROR_GOTO("malloc memory for slist failed");

	plist->nodes = p;
	plist->size = msize + 1;
	plist->length = 1;
	plist->head_i = 0;
	plist->rear_i = 0;
	plist->nodes[plist->head_i].next_i = 0;
	return true;

ON_ERROR:
	SAFE_FREE(p);
	return false;
}

template <typename ELEM_T>
void Destroy_SList(SLIST<ELEM_T> * plist)
{
	SAFE_FREE(plist->nodes);
	memset(plist, 0, sizeof(*plist));
}

template <typename ELEM_T>
inline bool Append_SList(SLIST<ELEM_T> * plist, SLIST_NODE<ELEM_T> ** ppnode)
{
	SLIST_NODE<ELEM_T> * p = NULL;
	if(plist->length == plist->size)
	{
		if(NULL == (p = (SLIST_NODE<ELEM_T> *)realloc(plist->nodes, (plist->size + SLIST_SIZE_INCREMENT) * sizeof(*p))))
			ON_ERROR_GOTO("realloc memory for slist failed");

		plist->nodes = p;
		plist->size += SLIST_SIZE_INCREMENT;
	}

	plist->nodes[plist->rear_i].next_i = plist->length;
	plist->nodes[plist->length].next_i = 0;
	plist->rear_i = plist->length;
	*ppnode = &plist->nodes[plist->length++];
	return true;

ON_ERROR:
	SAFE_FREE(p);
	return false;
}

template <typename ELEM_T>
inline void Clear_SList(SLIST<ELEM_T> * plist)
{
	plist->length = 0;
	plist->head_i = 0;
	plist->rear_i = 0;
	plist->nodes[plist->head_i].next_i = 0;
}

template <typename ELEM_T>
inline SLIST_NODE<ELEM_T> * GetHead_SList(SLIST<ELEM_T> * plist)
{
	return &plist->nodes[plist->head_i];
}

template <typename ELEM_T>
inline SLIST_NODE<ELEM_T> * GetNext_SList(SLIST<ELEM_T> * plist, SLIST_NODE<ELEM_T> ** ppnode)
{
	return *ppnode = &plist->nodes[(*ppnode)->next_i];
}

template <typename ELEM_T>
inline void Remove_SNode(SLIST_NODE<ELEM_T> * plast, SLIST_NODE<ELEM_T> * pnode)
{
	assert(plast->next_i != 0);
	plast->next_i = pnode->next_i;
}

#endif // __T3DLIB6_H__
