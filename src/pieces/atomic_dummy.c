

int atomic_increment(unsigned long *p)
{
	return (++(*p) != 0);
}

int atomic_decrement(unsigned long *p)
{
	return (--(*p) != 0);
}

