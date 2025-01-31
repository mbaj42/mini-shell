/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaj <mbaj@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:42:17 by mbaj              #+#    #+#             */
/*   Updated: 2024/12/21 16:41:59 by mbaj             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

/*int	main(int argc, t_data *minishell, char **ev)
{
	t_env	tmp;
	bool	is_crush;
	int		i;

	(*minishell).env = malloc((strlen(ev) + 1) * sizeof(char **));
	if (!((*minishell).env))
		return (ft_free_minishell((*minishell), is_crush));
	i = 0;
	tmp = (*minishell).env[i];
	for (int i = 0; &(*minishell).env[i]; i++)
	{ // dst   // src        // Adres 8    -  4
		// alloc key i val
		strncpy((*minishell).env[i].key, ev[i], strchr(ev[i], '=') - ev[i]);
		strcpy((*minishell).env[i].value, strchr(ev[i], '=') + 1);
		(*minishell).env = (*minishell).env->next;
	}
	(*minishell).env[i] = tmp;
}*/
void free_env(t_env *env)
{
    int i = 0;
    if (!env)
        return;
    while (env[i].key)
    {
        free(env[i].key);
        free(env[i].value);
        i++;
    }
    free(env);
}
static int	malloc_env(t_data **minishell, char **ev, int i, char *delimiter)
{
	int		key_length;

	if (!(*minishell) || !((*minishell)->env))
		return (1);
	if (delimiter)
	{
		key_length = delimiter - ev[i];
		(*minishell)->env[i].key = malloc((key_length + 1) * sizeof(char));
		if (!((*minishell)->env[i].key))
		{
			free_env((*minishell)->env);
			return (2);
		}
		(*minishell)->env[i].value = malloc((ft_strlen(delimiter + 1) + 1)
				* sizeof(char));
		if (!((*minishell)->env->value))
		{
			free_env((*minishell)->env);
			return (3);
		}
		ft_strncpy((*minishell)->env[i].key, ev[i], key_length);
		(*minishell)->env[i].key[key_length] = '\0';
		ft_strcpy((*minishell)->env[i].value, delimiter + 1);
	}
	return (0);
}

int	copy_env(t_data **minishell, char **ev)
{
	int		ev_count;
	char	*delimiter;
	int		i;

	ev_count = 0;
	if (!ev || !(*ev))
		return (3);
	while (ev[ev_count])
		ev_count++;
	(*minishell)->env = malloc((ev_count + 1) * sizeof(t_env));
	if (!(*minishell)->env)
	{
		free_env((*minishell)->env);
		return (1);
	}
	i = 0;
	while (i < ev_count)
	{
		delimiter = ft_strchr(ev[i], '=');
		malloc_env(&minishell, ev, i, delimiter);
		i++;
	}
	(*minishell)->env[ev_count].key = NULL;
	(*minishell)->env[ev_count].value = NULL;
	return (0);
}
