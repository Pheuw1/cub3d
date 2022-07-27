#include "libft.h"

int ft_strarrsize(char **strings)
{  
    int i;

    if (!strings)
        return (0);
    i = 0;
    while(strings && strings[i])
        i++;
    return (i);
}