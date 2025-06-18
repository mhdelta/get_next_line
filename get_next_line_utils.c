/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenao-p <mhenao-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 04:16:03 by mhenao-p          #+#    #+#             */
/*   Updated: 2025/06/18 04:18:01 by mhenao-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(t_list *list);
t_list	find_last_node(t_list *list);
void	copy_str_until_newline(t_list *list, char *str);
int	len_to_newline(t_list *list);
void	clean(t_list **list, t_list *clean_node, char *buf);


