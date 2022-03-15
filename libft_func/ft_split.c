#include "../includes/pipex.h"

int	wordnum(char const *s, char c)
{
	int	i;
	int	countword;

	i = 0;
	countword = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			i++;
		if (s[i] || s[i - 1] != c)
			countword++;
	}
	return (countword);
}

void	*allfree(char **masofmas)
{
	int	i;

	i = 0;
	while (masofmas[i])
	{
		free (masofmas[i]);
		i++;
	}
	free (masofmas);
	return (NULL);
}

void	fillmasofmas(char const *s, char **masofmas, int words, char c)
{
	int		wstart;
	int		wlen;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < words)
	{
		while (s[i] == c)
			i++;
		wstart = i;
		while (s[i] && s[i] != c)
			i++;
		wlen = i - wstart;
		masofmas[j] = ft_substr(s, wstart, wlen);
		if (!masofmas[j])
			allfree(masofmas);
		j++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**masofmas;
	int		words;

	if (!s)
		return (NULL);
	words = wordnum(s, c);
	masofmas = (char **) malloc(sizeof (char *) * (words + 1));
	if (!masofmas)
		return (NULL);
	masofmas[words] = NULL;
	fillmasofmas(s, masofmas, words, c);
	return (masofmas);
}
