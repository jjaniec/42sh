/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_details.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaspart <cgaspart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:23:00 by cgaspart          #+#    #+#             */
/*   Updated: 2018/10/30 17:15:39 by cgaspart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_DETAILS_H
# define PROMPT_DETAILS_H

# include <forty_two_sh.h>

# define PROMPT_PWD "\e[0;36m"
# define PROMPT_COLOR "\e[35;1m"
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

void	print_prompt_details(void);

char	*get_git_info(char **env);

#endif
