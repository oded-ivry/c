
/*swpa two data pointers, used for Insert and Remove*/
static void Swap(void **a, void **b)
{
	void *temp = *a;
	*a = *b;
	*b = temp;
}

