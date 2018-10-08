/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 15:06:12 by cyfermie          #+#    #+#             */
/*   Updated: 2018/10/08 17:00:18 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <forty_two_sh.h>

static bool			save_aliases_in_file(struct s_alias *alias)
{
	int						fd;
	const char				*aliases_file_path = get_parsed_aliases_file_path();

	if (check_backup_file(aliases_file_path) == false)
		return (false);
	if ((fd = open(aliases_file_path, O_WRONLY | O_TRUNC)) == -1)
	{
		ft_putstr_fd("42sh: error with file .42sh_aliases\n", STDERR_FILENO);
		return (false);
	}
	if (alias->key == NULL)
		return (true);
	while (alias != NULL)
	{
		if (write(fd, alias->key, ft_strlen(alias->key)) == (ssize_t)(-1)
		|| write(fd, " ", sizeof(char)) == (ssize_t)(-1)
		|| write(fd, alias->value, ft_strlen(alias->value)) == (ssize_t)(-1)
		|| write(fd, "\n", sizeof(char)) == (ssize_t)(-1))
		{
			ft_putstr_fd(".42sh_aliases: error writing in file\n", 2);
			return (close(fd) ? (false) : (false));
		}
		alias = alias->next;
	}
	return (close(fd) ? (true) : (true));
}

static void			add_next_tmp_alias(struct s_alias *alias, \
										const char *new_key, \
										const char *new_value)
{
	while (alias->next != NULL)
	{
		if (ft_strequ(alias->key, new_key))
		{
			free((void *)(alias->value));
			alias->value = new_value;
			return ;
		}
		alias = alias->next;
	}
	if (ft_strequ(alias->key, new_key))
	{
		free((void *)(alias->value));
		alias->value = new_value;
		return ;
	}
	if ((alias->next = malloc(sizeof(struct s_alias))) == NULL)
		exit(MALLOC_ERROR);
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
		if (is_separator(key[i++]))
		{
			ft_putstr_fd("42sh: alias: invalid alias name\n", STDERR_FILENO);
			return (false);
		}
	new_key = ft_strdup(key);
	new_value = ft_strdup(value);
	if (new_key == NULL || new_value == NULL)
		exit(MALLOC_ERROR);
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

static void			print_aliases(struct s_alias *alias)
{
	if (alias->key == NULL && "list is empty")
		return ;
	while (alias != NULL)
	{
		ft_printf("'%s' = '%s'\n", alias->key, alias->value);
		alias = alias->next;
	}
}

void				builtin_alias(char **argv, char **envp, t_exec *exe)
{
	unsigned int	nb_args;
	struct s_alias	*alias;

	exe->ret = ((envp) ? (0) : (0));
	alias = access_alias_datas();
	nb_args = count_elem_2d_array(argv + 1);
	if (nb_args != 0 && nb_args != 1 && nb_args != 2)
	{
		ft_putstr_fd(BUILTIN_ALIAS_USAGE, STDERR_FILENO);
		exe->ret = 1;
	}
	if (nb_args == 0)
		print_aliases(alias);
	else if (nb_args == 1)
	{
		if (!ft_strequ("--save", argv[1]))
		{
			ft_putstr_fd(BUILTIN_ALIAS_USAGE, STDERR_FILENO);
			exe->ret = 1;
		}
		else
			exe->ret = save_aliases_in_file(alias) == true ? (0) : (1);
	}
	else if (nb_args == 2)
		exe->ret = add_tmp_alias(argv[1], argv[2], alias) == true ? (0) : (1);
}
