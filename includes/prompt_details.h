/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_details.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyfermie <cyfermie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:23:00 by cgaspart          #+#    #+#             */
/*   Updated: 2018/11/30 17:37:05 by cyfermie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_DETAILS_H
# define PROMPT_DETAILS_H

# include <forty_two_sh.h>

# define PROMPT_PWD "\e[0;36m"
# define PROMPT_COLOR_TRUE "\e[35;1m"
# define PROMPT_COLOR_FALSE "\e[31;1m"
# define PROMPT_BRANCH_COLOR	"\e[2;37m"
# define PROMPT_FETCH_ARROWS_COLOR "\e[34m"

# define PROMPT_BRANCH_PREFIX " "
# define PROMPT_BRANCH_SUFFIX "*"

# define COMMIT_HASH_MAX_LEN	7

typedef struct		s_prompt
{
	struct winsize	win;
	char			*pwd;
	char			*home;
}					t_prompt;

void				print_prompt_details(void);
char				*get_git_info(char **env, pid_t p);

#endif
