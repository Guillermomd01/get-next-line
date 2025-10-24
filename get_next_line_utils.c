/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumunoz <gumunoz@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:37:15 by gumunoz           #+#    #+#             */
/*   Updated: 2025/10/21 15:37:23 by gumunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	size_t		len;
	char		*dup;

	if (!s)
		return (NULL);
	len = ft_strlen(s) +1;
	dup = malloc(len);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, len);
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL)
		s1 = "";
	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
		return (NULL);
	while (s1[j] != '\0')
		s3[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	real_len;
	size_t	j;
	char	*m;

	if (!s)
		return (NULL);
	real_len = ft_strlen(s);
	if (start >= real_len)
		return (ft_strdup(""));
	if (len > real_len - start)
		len = real_len - start;
	m = malloc(len + 1);
	if (!m)
		return (NULL);
	j = 0;
	while (s[start + j] && j < len)
	{
		m[j] = s[start + j];
		j++;
	}
	m[j] = '\0';
	return (m);
}
