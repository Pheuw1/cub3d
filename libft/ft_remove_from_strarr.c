#include "libft.h"

char **ft_remove_from_strarr(char **strings, int idx)
{
    int j;
    int i;
    char **ret;

    if (ft_strarrsize(strings) < idx)
        return (NULL);
    ret = (char **)malloc((ft_strarrsize(strings)) * sizeof(char *));
    i = -1;
    j = -1;
    while (++i < ft_strarrsize(strings))
        if (i != idx)
            ret[++j] = ft_strdup(strings[i]);
    ret[j + 1] = NULL;
    ft_freepp((void *)strings);
    return (ret);
}