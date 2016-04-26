int memcmp(void *s1, void *s2, int size)
{
    int i = 0;
    for (i=0;i<size;i++)
    {
	if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
	    return -1;
    }
    return 0;
}
