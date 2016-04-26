/* $Id: argvize.c,v 1.1.1.1 2006/05/25 02:11:24 cpu Exp $ */
#define MAX_AC 10

/** int argvize(av,s) place address of each word in s into the array av */
int argvize (char *av[], char *s)
{
    char          **pav = av, c;
    int             ac;

    for (ac = 0; ac < MAX_AC; ac++) {
	/* step over cntrls and spaces */
	while (*s && *s <= ' ')
	    ++s;

	/* if eos quit */
	if (!*s)
	    break;

	c = *s;
	/* if it's a quote skip forward */
	if (c == '\'' || c == '"') {
	    if (pav)
		*pav++ = ++s;
	    while (*s && *s != c)
		++s;
	    if (*s)
		*s++ = 0;
	} else {		/* find end of word */
	    if (pav)
		*pav++ = s;
	    while (' ' < *s)
		++s;
	}

	/* not eos inc ptr */
	if (*s)
	    *s++ = 0;
    }
    return (ac);
}
