// Personal library headers
#include <standard.h>

//----------------------------------------------------------------------------//
//- Forward declaration                                                      -//
//----------------------------------------------------------------------------//

void testSlist(void);
void testDlist(void);
void testMergesort(void);
bool compare(void *pOne, void *pTwo);

//----------------------------------------------------------------------------//
//- Public functions                                                         -//
//----------------------------------------------------------------------------//

void testSlist(void)
{
	Slist		list;
	uint32_t	data[16];
	uint32_t	res;

	slist_construct(&list, sizeof(uint32_t));

	for (size_t i = 1; i < ARRAY_SIZE(data); i++)
	{
		data[i] = i;
		slist_pushTail(&list, &data[i]);
	}

	for (size_t i = 1; i < ARRAY_SIZE(data); i++)
	{
		slist_pop(&list, &res);
		printf("%u\n", res);
	}
}

void testDlist(void)
{
	Dlist		list;
	Dlist		listB;
	uint32_t	data[16];
	uint32_t	res;

	dlist_construct(&list, sizeof(uint32_t));
	dlist_construct(&listB, sizeof(uint32_t));

	printf("\nlist A\n");
	for (size_t i = 1; i < ARRAY_SIZE(data); i++)
	{
		data[i] = i;
		dlist_pushTail(&list, &data[i]);
		printf("data[%lu]: %u\n", i, data[i]);
	}

	printf("\nnrNodes: %lu\n\n", list.nrNodes);

	dlist_split(&list, &listB);

	dlist_join(&list, &listB);

	printf("\nlist A\n");

	while (list.nrNodes)
	{
		dlist_popHead(&list, &res);
		printf("list: data: %u\n", res);
	}

	printf("\nlist B\n");

	while(listB.nrNodes)
	{
		dlist_popHead(&listB, &res);
		printf("listB: data: %u\n", res);
	}
}

bool compare(void *pOne, void *pTwo)
{
	if (*(uint32_t*)pOne >= *(uint32_t*)pTwo)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void testMergesort(void)
{
	Dlist		list;
	uint32_t	data[16];

	dlist_construct(&list, sizeof(uint32_t));

	printf("\nlist\n");
	for (size_t i = 1; i < ARRAY_SIZE(data); i++)
	{
		data[i] = i;
		dlist_pushTail(&list, &data[i]);
		printf("data[%lu]: %u\n", i, data[i]);
	}
	printf("\nnrNodes: %lu\n\n", list.nrNodes);

	//mergesort(&list, compare);
	
	printf("\nsorted list\n");
	for (size_t i = 1; i < ARRAY_SIZE(data); i++)
	{
		data[i] = i;
		dlist_pushTail(&list, &data[i]);
		printf("data[%lu]: %u\n", i, data[i]);
	}
	printf("\nnrNodes: %lu\n\n", list.nrNodes);

	dlist_destroy(&list);
}

int main(int argc, char **argv)
{
	(void)(argc);
	(void)(argv);

	//testSlist();

	testDlist();

	//testMergesort();

	system("pause");
	return 0;
}
