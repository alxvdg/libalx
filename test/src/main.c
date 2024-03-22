// Personal library headers
#include <standard.h>

//----------------------------------------------------------------------------//
//- Forward declaration                                                      -//
//----------------------------------------------------------------------------//

void test_slist(void);
void test_dlist(void);
void test_dlist_mergesort(DListCmpFn cmp);
int compare(const void *pOne, const void *pTwo);

//----------------------------------------------------------------------------//
//- Public functions                                                         -//
//----------------------------------------------------------------------------//

void test_slist(void)
{
	slist		*pList;
	uint32_t	*res;
	uint32_t	data[] = { 1, 17, 6, 9, 198, 184, 1, 6, 0, 4896, 49746, 4154 };

	pList = slist_init();

	for (size_t i = 0; i < ARRAY_SIZE(data); i++)
	{
		if (i%2 == 0)
		{
			slist_pushTail(pList, &data[i]);
		}
		else
		{
			slist_pushHead(pList, &data[i]);
		}
	}

	while ((res = slist_pop(pList)) != NULL)
	{
		printf("%u\n", *res);
	}

	slist_destroy(pList);
}

void test_dlist(void)
{
	dlist		*pList;
	dlist		*pListB;
	uint32_t	data[] = { 1, 17, 6, 9, 198, 184, 1, 6, 0, 4896, 49746, 4154 };
	uint32_t	data2[] = { 18, 19, 487, 648, 3, 55, 41, 69, 154, 964, 841, 57, 12 };
	uint32_t	*res;

	pList = dlist_init();
	pListB = dlist_init();

	printf("\nlist A\n");
	for (size_t i = 0; i < ARRAY_SIZE(data); i++)
	{
		dlist_pushTail(pList, &data[i]);
		printf("data[%lu]: %u\n", i, data[i]);
	}

	printf("\nnrNodes: %lu\n\n", pList->nrNodes);

	dlist_split(pList, pListB);

	printf("\nlist A\n");

	while ((res = dlist_popHead(pList)) != NULL)
	{
		printf("list: data: %u\n", *res);
	}

	printf("\nlist B\n");

	while ((res = dlist_popHead(pListB)) != NULL)
	{
		printf("listB: data: %u\n", *res);
	}
	
	printf("\njoined list \n");

	for (size_t i = 0; i < ARRAY_SIZE(data); i++)
	{
		dlist_pushHead(pList, &data[i]);
	}

	for (size_t i = 0; i < ARRAY_SIZE(data2); i++)
	{
		dlist_pushHead(pListB, &data2[i]);
	}

	dlist_join(pListB, pList);

	while ((res = dlist_popTail(pListB)) != NULL)
	{
		printf("joined list: data: %u\n", *res);
	}

	while ((res = dlist_popHead(pList)) != NULL)
	{
		printf("joined list2: data: %u\n", *res);
	}

	dlist_destroy(pList);
	dlist_destroy(pListB);
}

void test_dlist_mergesort(DListCmpFn cmp)
{
	dlist		*pList;
	uint32_t	data[] = { 1, 17, 6, 9, 198, 184, 1, 6, 0, 4896, 49746, 4154 , 18, 19, 487, 648, 3, 55, 41, 69, 154, 964, 841, 57, 12 };

	pList = dlist_init();

	printf("\nlist\n");
	for (size_t i = 0; i < ARRAY_SIZE(data); i++)
	{
		dlist_pushTail(pList, &data[i]);
		printf("data[%lu]: %u\n", i, data[i]);
	}
	
	dlist_sort(pList, cmp);

	printf("\nsorted list: head:0x%x: %d\t tail:0x%x: %d\t nr:%d\n", pList->pHead, *(uint32_t*)pList->pHead->pData, pList->pTail, *(uint32_t*)pList->pTail->pData, pList->nrNodes);
	printList(pList);

	dlist_destroy(pList);
}

int compare(const void *pOne, const void *pTwo)
{
	if (*(uint32_t*)pOne < *(uint32_t*)pTwo)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

int main(int argc, char **argv)
{
	(void)(argc);
	(void)(argv);

	test_slist();

	test_dlist();

	test_dlist_mergesort(compare);

	system("pause");
	return 0;
}
