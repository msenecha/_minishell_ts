
#include "minishell.h"

int check_for_pipe(t_list *sub_list)
{
    t_node  *current;

    current = sub_list->head;
    while(current)
    {
        if (current->type == PIPE)
            return (1);
        current = current->next;
    }
    return (0);
}

void    build_exec_line(t_list *sub_list, t_env *env)
{
    t_node  *node;
    char    **argv;

    node = sub_list->head;
    while (node && node->type != PIPE)
    {
        if (node->type)
    }
}

int	is_builtin(char *command)
{
	if (strcmp(command, "echo") == 0)
		return (1);
	if (strcmp(command, "cd") == 0)
		return (1);
	if (strcmp(command, "pwd") == 0)
		return (1);
	if (strcmp(command, "env") == 0)
		return (1);
	if (strcmp(command, "export") == 0)
		return (1);
	if (strcmp(command, "unset") == 0)
		return (1);
	return (0);
}

void execute_command(t_parser *data, t_env *env)
{
    char    *built;
    t_list   *cmd;
    (void)env;
    
    cmd = data->command_list->head;
    while (cmd)
    {
        if (check_for_pipe(cmd))
            printf("------------------> has pipe\n");
            //setup_pipe(data, env);
        built = strdup(cmd->head->value);
        if (is_builtin(built))
        {
            free(built);
            //execute_builtin(data, env);
        }
        else
        {
        //build_exec_line(cmd, env);
        }
        cmd = cmd->next;
    }
}