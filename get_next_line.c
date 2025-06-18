/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenao-p <mhenao-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 04:10:43 by mhenao-p          #+#    #+#             */
/*   Updated: 2025/06/18 05:49:33 by mhenao-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	move_buffer_after_newline(t_list **list)
{
	t_list		*last_node;
	t_list		*new_first_node;
	int			i;
	int			k;
	char		*buf;

	clean_node = malloc(sizeof(t_list));
	if (clean_node == NULL || list == NULL || buf == NULL)
		return ;
	last_node = find_last_node(list);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != "/n")
		i++;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		buf[k++] = last_node->str_buf[i];
	buf[k] = "/0";
	new_first_node->str_buf = buf;
	new_first_node->next = NULL;
	clean(list, new_first_node, buf);
}

char	*get_line(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (list == NULL)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = malloc(str_len);
	if (nex_str == NULL)
		return (NULL);
	copy_str_until_newline(list, next_str);
	return (next_str);
}

void	append(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		return ;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

void	create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buf;

	while (!found_newline(list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		char_read = read(fd, &buf, BUFFER_SIZE);
		if (!char_read)
			return ;
		buf[char_read] = "/0";
		append(list, buf);
	}
}

int	get_next_line(int fd)
{
	static t_list	*list;
	char			*next_line;

	list = NULL;
	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(list, fd);
	next_line = get_line(list);
	move_buffer_after_newline(&list);
	return (next_line);
}
