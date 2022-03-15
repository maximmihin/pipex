#include "../includes/pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*arr;
	size_t	i;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
		len = 0;
	else if (len >= slen)
		len = slen - start;
	arr = (char *)malloc(sizeof(*s) * (len + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (len && s[start] && start < slen)
	{
		arr[i] = s[start];
		i++;
		start++;
		len--;
	}
	arr[i] = 0;
	return (arr);
}
