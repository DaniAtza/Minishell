/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagredan <dagredan@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:39:55 by dagredan          #+#    #+#             */
/*   Updated: 2025/08/05 03:10:53 by dagredan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_parameter(t_segm *segment, t_data *data)
{
	char	*name;

	name = segment->string;
	if (name[1] == '?')
		segment->string = ft_itoa(data->last_exit_status);
	else
	{
		segment->string = search_env(name + 1, data->env_list);
		if (!segment->string)
			segment->string = ft_strdup("");
		else
			segment->string = ft_strdup(segment->string);
	}
	free(name);
	if (!segment->string)
		return (perror_return("expand_parameter: malloc", -1));
	return (0);
}

int	expand_parameters(t_word *word, t_data *data)
{
	t_segm	*current;

	current = word->segments;
	while (current)
	{
		if (current->type == PARAMETER && !current->single_quoted)
		{
			if (expand_parameter(current, data) != 0)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
