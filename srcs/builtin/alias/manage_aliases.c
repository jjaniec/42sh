/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_aliases.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 17:10:30 by cgaspart          #+#    #+#             */
/*   Updated: 2018/12/10 17:19:49 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <twenty_one_sh.h>

static bool			save_aliases_in_file(struct s_alias *alias)
{
	int						fd;
	const char				*aliases_file_path = get_parsed_aliases_file_path();

	if (check_backup_file(aliases_file_path) == false)
		return (false);
	if ((fd = open(aliases_file_path, O_WRONLY | O_TRUNC)) == -1
	&& write(2, SH_NAME": error with file ."SH_NAME"_aliases\n", 36))
		return (false);
	if (alias->key == NULL)
		return (close(fd) ? (true) : (true));
	while (alias != NULL)
	{
		if (ft_strlen(alias->key) > 0U)
			if (write(fd, alias->key, ft_strlen(alias->key)) == (ssize_t)(-1)
			|| write(fd, " ", sizeof(char)) == (ssize_t)(-1)
			|| write(fd, alias->value, ft_strlen(alias->value)) == (ssize_t)(-1)
			|| write(fd, "\n", sizeof(char)) == (ssize_t)(-1))
			{
				ft_putstr_fd("."SH_NAME"_aliases: error writing in file\n", 2);
				return (close(fd) ? (false) : (false));
			}
		alias = alias->next;
	}
	return (close(fd) ? (true) : (true));
}

static void			add_next_tmp_alias(struct s_alias *alias, \
											char *new_key, \
											char *new_value)
{
	while (alias->next != NULL)
	{
		if (ft_strequ(alias->key, new_key))
		{
			free(alias->value);
			free(new_key);
			alias->value = new_value;
			return ;
		}
		alias = alias->next;
	}
	if (ft_strequ(alias->key, new_key))
	{
		free(alias->value);
		free(new_key);
		alias->value = new_value;
		return ;
	}
	alias->next = ft_xmalloc(sizeof(struct s_alias));
	alias->next->key = new_key;
	alias->next->value = new_value;
	alias->next->next = NULL;
}

static bool			add_tmp_alias(const char *key, const char *value, \
												struct s_alias *alias)
{
	char			*new_key;
	char			*new_value;
	unsigned int	i;

	i = 0;
	while (key[i] != '\0')
		if (is_separator(key[i++]) || key[0] == '=')
		{
			ft_putstr_fd(SH_NAME": "ERR_INVALID_ALIAS_NAME, STDERR_FILENO);
			return (false);
		}
	new_key = ft_xstrdup(key);
	new_value = ft_xstrdup(value);
	if (alias->key == NULL && "aliases linked list is empty")
	{
		alias->key = new_key;
		alias->value = new_value;
		return (true);
	}
	else if ("aliases linked list is not empty - and because of the norminette")
		add_next_tmp_alias(alias, new_key, new_value);
	return (true);
}

static void			delete_alias(const char *key, struct s_alias *alias)
{
	if (alias->key == NULL && "list is empty")
		return ;
	if (ft_strlen(key) == 0)
		return ;
	while (alias != NULL)
	{
		if (ft_strequ(key, alias->key))
		{
			alias->key[0] = '\0';
			alias->value[0] = '\0';
			return ;
		}
		alias = alias->next;
	}
}

void				manage_aliases(char **argv, struct s_alias *alias,
									t_exec *exe, unsigned int nb_args)
{
	if (nb_args == 1)
	{
		if (!ft_strequ("--save", argv[1]) && (exe->ret = 1))
			ft_putstr_fd(BUILTIN_ALIAS_USAGE, STDERR_FILENO);
		else
			exe->ret = save_aliases_in_file(alias) == true ? (0) : (1);
	}
	else if (nb_args == 2)
	{
		if (ft_strequ(argv[1], "-d"))
			delete_alias(argv[2], alias);
		else
			exe->ret = add_tmp_alias(argv[1], argv[2], alias) == true ? 0 : 1;
	}
}
