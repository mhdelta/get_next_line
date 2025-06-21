/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenao-p <mhenao-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 04:10:43 by mhenao-p          #+#    #+#             */
/*   Updated: 2025/06/19 06:28:16 by mhenao-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	move_buffer_after_newline(t_list **list)
{
	t_list		*last_node;
	t_list		*new_first_node;
	int			i;
	int			k;
	char		*buf;

	buf = malloc(BUFFER_SIZE + 1);
	// buf = NULL;
	if (buf == NULL)
		return (1); 
	new_first_node = malloc(sizeof(t_list));
	// new_first_node = NULL;
	if (new_first_node == NULL)
	{
		free(buf);
		return (1);
	}
	last_node = find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		++i;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		buf[k++] = last_node->str_buf[i];
	buf[k] = '\0';
	new_first_node->str_buf = buf;
	new_first_node->next = NULL;
	clean(list, new_first_node, buf);
	return 0;
}

char	*get_line_test(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (list == NULL)
		return (NULL);
	str_len = len_to_newline(list);
	// next_str = malloc(str_len + 1);
	next_str = malloc(str_len + 1);
	if (next_str == NULL)
	{
		return (NULL);
	}
	copy_str_until_newline(list, next_str);
	return (next_str);
}

int	append(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	// new_node = malloc(sizeof(t_list));
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (1);
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
	return (0);
}

int	create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buf;

	while (!found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
		{
			// printf("here");
			return (1);
		}
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read)
		{
			free(buf);
			return (0);
		}
		buf[char_read] = '\0';
		if (append(list, buf))
		{
			free(buf);
			return (1);
		}
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;
	int	result;

	if (fd < 0 || BUFFER_SIZE < 0)
	{
		return (NULL);
	}
	if (read(fd, &next_line, 0) < 0)
	{
		clean(&list, NULL, NULL);
		return (NULL);
	}
	result = create_list(&list, fd);
	if (list == NULL || result)
	{
		clean(&list, NULL, NULL);
		return (NULL);
		// printf("create list\n");
		// printf("result: %lu", sizeof(list));
	}
	next_line = get_line_test(list);
	if (next_line == NULL)
	{
		clean(&list, NULL, NULL);
		return (NULL);
		// printf("cleaning\n");
	}
	result = move_buffer_after_newline(&list);
	if (result)
	{
		clean(&list, NULL, NULL);
		free(next_line);
		return (NULL);
	}
	return (next_line);
}

// int main ()
// {
// 	int lines = 1;
// 	char *line;
// 	int fd = open("t.txt", O_RDONLY);

// 	while((line = get_next_line(fd)))
// 	{
// 		printf("%d -> %s\n", lines++, line);
// 		free(line);
// 	}
// }