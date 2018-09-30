/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:38:39 by jjaniec           #+#    #+#             */
/*   Updated: 2018/09/30 21:53:52 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static void	exec_fd_test(char *filename_sh, char *filename_21sh, int redirected_fd, char *str, char *custom_sh_cmd)
{
	char	*cmd_sh;
	int		tmp_fd;
	int		dup_redirected_fd;

	dup_redirected_fd = dup(redirected_fd);
	tmp_fd = open(filename_sh, O_WRONLY | O_CREAT, DEFAULT_OUTPUT_REDIR_FILE_MODE);
	dup2(tmp_fd, redirected_fd);
	if (custom_sh_cmd)
		cmd_sh = custom_sh_cmd;
	else
		asprintf(&cmd_sh, "{ %s ; }", (str));
	system(cmd_sh);
	close(tmp_fd);
	tmp_fd = open(filename_21sh, O_WRONLY | O_CREAT, DEFAULT_OUTPUT_REDIR_FILE_MODE);
	dup2(tmp_fd, redirected_fd);
	asprintf(&cmd_sh, SH_EXEC_CMD_PREFIX"\"%s\"", str);
	system(cmd_sh);
	close(tmp_fd);
	dup2(dup_redirected_fd, redirected_fd);
	close(dup_redirected_fd);
}

static void	exec_diff_fd(char *test_name, char *str, int redirected_fd, char *custom_sh_cmd)
{
	int		ret;

	exec_fd_test("/tmp/exec_sh.txt", "/tmp/exec_21sh.txt", redirected_fd, str, custom_sh_cmd);
	//system("cat /tmp/exec_21sh.txt");
	//system("cat /tmp/exec_sh.txt");
	ret = system("diff /tmp/exec_21sh.txt /tmp/exec_sh.txt");
	ok(!ret, test_name);
	remove("/tmp/exec_sh.txt");
	remove("/tmp/exec_21sh.txt");
}

static void	exec_diff(char *test_name, char *str, char *custom_sh_cmd)
{
	int		test_name_str_len;
	char	*new_test_name;
	int		tmp;

	if (!(*MODE == 'L' && ft_strstr(str, "<<<")))
	{
		test_name_str_len = ft_strlen(test_name);
		new_test_name = malloc(test_name_str_len * sizeof(char) + 10);
		ft_strcpy(new_test_name, test_name);

		ft_strcpy(new_test_name + test_name_str_len, " - stdout");
		tmp = dup(STDERR_FILENO);
		freopen("/dev/null", "w", stderr);
		exec_diff_fd(new_test_name, str, STDOUT_FILENO, custom_sh_cmd);
		dup2(tmp, STDERR_FILENO);

		ft_strcpy(new_test_name + test_name_str_len, " - stderr");
		tmp = dup(STDOUT_FILENO);
		freopen("/dev/null", "w", stdout);
		exec_diff_fd(new_test_name, str, STDERR_FILENO, custom_sh_cmd);
		dup2(tmp, STDOUT_FILENO);
		free(new_test_name);
	}
}

static void	env_builtins_tests(t_environ *env)
{
	(void)env;
	/*
	char		**env;

	env = *envp_ptr;
	exec_diff("Builtin 17 - setenv basic", "env | grep test____ || setenv test____ tmp && env | grep test____", \
		"{ env | grep test____ || export test____=tmp && env | grep test____ ;}");
	*envp_ptr = NULL;
	exec_diff("Builtin 18 - setenv basic without env", "env | grep test____ || setenv test____ tmp && env | grep test____", \
		"{ env | grep test____ || export test____=tmp && env | grep test____ ;}");
	*envp_ptr = NULL;
	system(SH_EXEC_CMD_PREFIX"\"unsetenv tmp && env\"");
	ok((*envp_ptr == NULL), "Builtin 19 - unsetenv without env");*/
	/* 15/09: does not work
	*envp_ptr = (char **)cp_envp((const char *[3]){"tmp=LOL", "tmp2=LOL", NULL});
	system(SH_EXEC_CMD_PREFIX"\"unsetenv tmp\"");
	ok((envp_ptr[1] == NULL), "Builtin 20 - unsetenv basic");
	*envp_ptr = (char **)cp_envp((const char *[3]){"tmp=LOL", "tmp2=LOL", NULL});
	system(SH_EXEC_CMD_PREFIX"\"unsetenv tmp tmp2\"");
	ok((envp_ptr[0] == NULL), "Builtin 21 - unsetenv basic multiple elems");
	*envp_ptr = (char **)cp_envp((const char *[3]){"tmp=LOL", "tmp2=LOL", NULL});
	system(SH_EXEC_CMD_PREFIX"\"unsetenv tmp tmp2 wwwww\"");
	ok((envp_ptr[0] == NULL), "Builtin 21 - unsetenv basic multiple elems w/ non-existant");
	*envp_ptr = (char **)cp_envp((const char *[3]){"tmp=LOL", "tmp2=LOL", NULL});
	system(SH_EXEC_CMD_PREFIX"\"unsetenv tmp tmp tmp tmp\"");
	ok((envp_ptr[1] == NULL), "Builtin 21 - unsetenv basic already deleted");*/
/*	*envp_ptr = env; //restore env*/
}

void		builtins_tests(t_environ *env)
{
	(void)env;

	int		ret;
	ret = system(SH_EXEC_CMD_PREFIX"exit");
	ok((ret == 0), "Builtin exit 1 - no args");
	ret = system(SH_EXEC_CMD_PREFIX"\"exit 42\"");
	ok((ret / 256 == 42), "Builtin exit 2 - passed exit value");
	ret = system(SH_EXEC_CMD_PREFIX"\"exit 42 43 44\"");
	ok((ret / 256 == 0), "Builtin exit 3 - too many args err");
	ret = system(SH_EXEC_CMD_PREFIX"\"exit 42w\"");
	ok((ret / 256 == 255), "Builtin exit 4 - arg not numeric");
	ret = system(SH_EXEC_CMD_PREFIX"\"exit 42w 45 12\"");
	ok((ret / 256 == 255), "Builtin exit 5 - arg not numeric w/ too many args");
	env_builtins_tests(env);

	exec_diff("Builtin echo 1 - echo", "echo ls", NULL);
	exec_diff("Builtin echo 2 - echo multi args", "echo ls ls ls ls ls ls", NULL);
	exec_diff("Builtin echo 3 - echo no args", "echo", NULL);
	exec_diff("Builtin echo 4 - Pipes (w/ echo)", "echo ls | cat", NULL);
	exec_diff("Builtin echo 5 - Redirs (w/ echo)", "echo ls > /tmp/a && cat < /tmp/a", NULL);
	exec_diff("Builtin echo 6 - Pipes & redirs (w/ echo)", "echo ls / /abc 2> /tmp/a; cat < /tmp/a", NULL);

	exec_diff("Builtin cd 1 - cd", "cd / && pwd", NULL);
	exec_diff("Builtin cd 2 - cd", "cd / && cd dev && pwd", NULL);
	exec_diff("Builtin cd 3 - cd", "cd ~ && cd /dev && pwd", NULL);
	exec_diff("Builtin cd 4 - cd", "cd ~ && cd /dev && cd .. && pwd", NULL);
	exec_diff("Builtin cd 5 - cd -", "cd && cd - && cd /dev && cd - && cd .. && pwd", NULL);
	exec_diff("Builtin cd 6 - cd -", "cd / && cd / && cd - && cd && cd - && cd - && echo \"/\" | cd && pwd", NULL);

	exec_diff("Builtin env 1 - env w/o args", "env | grep -v", NULL);
	//exec_diff("Builtin env 2 - env w/ T_ENV_ASSIGN", "TMP=test env | grep TMP", NULL); // 15/09: Not implemented
	exec_diff("Builtin env 3 - env w/ valid args", "env TEST1=TEST__ TEST2=TEST______ | grep -v _", NULL);
	exec_diff("Builtin env 4 - env -i w/ valid args", "env -i A=B TEST1=TEST__ TEST2=TEST______", NULL);
	// test env execution ex: env A=B ls - not implemented
	/*
	exec_diff("Builtin env 5 - env -i w/ valid args & execution", "env -i A=B TEST1=TEST__ TEST2=TEST______ ls", NULL);
	exec_diff("Builtin env 6 - env -i w/o valid args", "env -i A", NULL);
	exec_diff("Builtin env 7 - env -i w/o valid args", "env -i ls", NULL);
	*/

	exec_diff("Builtin setenv 1 - w/o args", "setenv", NULL);
	exec_diff("Builtin setenv 2 - w/o valid args 1", "setenv a", NULL);
	exec_diff("Builtin setenv 3 - w/o valid args 2", "setenv a=b b=c d=e f=g h=", NULL);
	exec_diff("Builtin setenv 4 - w/o valid args 3", "setenv a=b b=c d=e f=g =i", NULL);
	exec_diff("Builtin setenv 5 - w/o valid args 4", "setenv a=b b=c d=e f=g h =i", NULL);
	exec_diff("Builtin setenv 6 - w/o valid args 5", "setenv a=b b=c d=e f=g h= i", NULL);
	exec_diff("Builtin setenv 7 - w/o valid args 6", "setenv a=b b=c d=e f=gh=i", NULL);
	exec_diff("Builtin setenv 8 - w/ valid args", "setenv a=b c=d", NULL);
	exec_diff("Builtin setenv 9 - w/ many valid args", "setenv a=b c=d e=f g=h i=j k=l m=n o=p q=r s=t u=v x=y z=a1 a1=b b1=c c1=d d1=e e1=f f1=g g1=h h1=i i1=j j1=k k1=l l1=m m1=n n1=o o1=p p1=q q1=r && env | grep -v _", NULL);
	exec_diff("Builtin setenv 10 - valid args w/ re-assignations", "setenv a=b c=d e=f g=h i=j k=l m=n o=p q=r s=t u=v x=y z=a a=b b=c c=d d=e e=f f=g g=h h=i i=j j=k k=l l=m m=n n=o o=p p=q q=r && env | grep -v _", NULL);
}
