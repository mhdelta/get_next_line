/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenao-p <mhenao-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 03:18:13 by mhenao-p          #+#    #+#             */
/*   Updated: 2025/06/18 04:10:04 by mhenao-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}	t_list;

int		get_next_line(int fd);
int		found_newline(t_list *list);
int		len_to_newline(t_list *list);
char	*get_line(t_list *list);
void	create_list(t_list **list, int fd);
void	append(t_list **list, char *buf);
void	copy_str_until_newline(t_list *list, char *str);
void	clean(t_list **list, t_list *clean_node, char *buf);
void	move_buffer_after_newline(t_list **list);
t_list	find_last_node(t_list *list);

#endif
