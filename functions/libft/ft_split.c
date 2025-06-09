/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-ghab <zel-ghab@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:05:09 by zel-ghab          #+#    #+#             */
/*   Updated: 2025/05/31 21:42:03 by zel-ghab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_strings_already_malloced(char **split, size_t index)
{
	while (index > 0)
		free(split[--index]);
}

static char	**ft_filling(char **split, char const *s, char c)
{
	size_t	index;
	size_t	i;
	size_t	j;

	index = 0;
	i = 0;
	j = 0;
	while (s[index])
	{
		if (s[index] != c)
		{
			split[i][j++] = s[index];
		}
		if (s[index] != c && (s[index + 1] == c || s[index + 1] == '\0'))
		{
			split[i][j] = '\0';
			i++;
			j = 0;
		}
		index++;
	}
	return (split);
}

static char	**ft_word(char **split, char const *s, char c)
{
	size_t	i;
	size_t	index;
	size_t	nb_char;

	i = 0;
	index = 0;
	nb_char = 0;
	while (s && s[i])
	{
		if (s[i] != c)
			nb_char++;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			split[index] = malloc(nb_char + 1);
			if (split[index] == NULL)
				return (ft_free_strings_already_malloced(split, index), NULL);
			nb_char = 0;
			index++;
		}
		i++;
	}
	return (split);
}

static size_t	ft_countstring(char const *s, char c)
{
	size_t	i;
	size_t	nb_string;

	i = 0;
	nb_string = 0;
	while (s && s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			nb_string++;
		i++;
	}
	return (nb_string);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	nb_strings;

	if (!s || *s == '\0')
	{
		split = malloc(sizeof(char *));
		if (!split)
			return (NULL);
		split[0] = NULL;
		return (split);
	}
	nb_strings = ft_countstring(s, c);
	split = malloc(sizeof(char *) * (nb_strings + 1));
	if (!split)
		return (NULL);
	split[nb_strings] = NULL;
	if (!ft_word(split, s, c))
		return (free(split), NULL);
	if (!ft_filling(split, s, c))
	{
		ft_free_strings_already_malloced(split, nb_strings);
		return (free(split), NULL);
	}
	return (split);
}
/*
int	main(void)
{
	char	**split;

	split = ft_split("Zakaria-El-Ghabri", '-');
	return (0);
}
*/
