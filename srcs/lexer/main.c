#include "lexer.h"
#include "libft.h"
#include <stdio.h>

typedef struct	s_ast
{
	int						*tok;
	char					*arg;
	int						split_by;
	int						depth;
	struct s_ast			*parent;
	struct s_ast			*left;
	struct s_ast			*right;
}				t_ast;

static char		*ft_strndup(const char *s1, size_t n)
{
	char		*str;
	size_t		i;

	i = 0;
	if (str)
	{
		if (!(str = (char *)malloc(sizeof(char) * n + 1)))
			return (NULL);
		while (s1[i] && i < n)
		{
			str[i] = s1[i];
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (*(s++))
		len++;
	return (len);
}

static t_ast	*fill_leftast(t_ast *parent, int size, int split_by)
{
	t_ast	*left = NULL;

	if (!(left = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	left->parent = parent;
	left->depth = parent->depth + 1;
	left->arg = ft_strndup(parent->arg, size);
	left->split_by = split_by;
	left->tok = get_tokens(left->arg);
	left->left = NULL;
	left->right = NULL;
//	printf("in fill_leftast, left->arg = %s\n", left->arg);
	return (left);
}

static t_ast	*fill_rightast(t_ast *parent, int start, int size, int split_by)
{
	t_ast	*right = NULL;
	char	*str;

	if (!(right = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	right->parent = parent;
	str = parent->arg + start;
	right->depth = parent->depth + 1;
	right->arg = ft_strndup(str, size);
	right->split_by = split_by;
	right->tok = get_tokens(right->arg);
	right->left = NULL;
	right->right = NULL;
//	printf("in fill_rightast, right->arg = %s\n", right->arg);
	return (right);
}

static t_ast	*init_ast(char ***argv)
{
	t_ast	*head;
	char	**tab = *argv;
	if (!(head = (t_ast *)malloc(sizeof(t_ast))))
			return (NULL);	
	head->parent = NULL;
	head->split_by = 0;
	head->depth = 0;
	head->arg = (tab[1]) ? ft_strndup(tab[1], ft_strlen(tab[1])) : NULL;
	head->tok = get_tokens(head->arg);
	head->left = NULL;
	head->right = NULL;	
	return (head);
}

static void		ast_loop_pipe(t_ast *head)
{
	int		i = 0;
	t_ast	*tmp = head;
	char	*str = tmp->arg;
	int		split_by = 0;
	static int	order = 1;

	while (tmp->tok[i] != -1)
	{
		if (tmp->tok[i] == TK_PIPE)
		{
			split_by = tmp->tok[i];
			//printf("filling left from ast_loop_pipe\n");
			tmp->left = fill_leftast(tmp, tmp->tok[i+1], split_by);
			i += 3;
			while (tmp->tok[i] == TK_SPACE)
				i += 3;
			if (tmp->tok[i] && tmp->tok[i] != 1 && tmp->tok[i] != TK_END)
			{
				//printf("filling right from ast_loop_pipe with:\ntmp->arg = %s\n", tmp->arg);
				tmp->right = fill_rightast(tmp, tmp->tok[i+1], ft_strlen(tmp->arg) - tmp->tok[i+1], split_by);
				//printf("\nrecursively calling ast_loop_PIPE\n");
				ast_loop_pipe(tmp->right);
				break ;
			}
			else
				tmp->right = NULL;
		}
		else
			i += 3;
		while (tmp->tok[i] == TK_SPACE)	//skips spaces in token table to find proper starting point before recreating another token table later
			i += 3;
	}
}

static void		ast_loop_and_or(t_ast *head)
{
	int		i = 0;
	t_ast	*tmp = head;
	char	*str = tmp->arg;
	int		split_by = 0;

	while (tmp->tok[i] != -1)
	{
		if (tmp->tok[i] == TK_AND_IF || tmp->tok[i] == TK_OR_IF)
		{
			split_by = tmp->tok[i];
			//printf("filling left from ast_loop_and_or\n");
			tmp->left = fill_leftast(tmp, tmp->tok[i+1], split_by);
			ast_loop_pipe(tmp->left);
			i += 3;
			while (tmp->tok[i] == TK_SPACE)
				i += 3;
			if (tmp->tok[i] && tmp->tok[i] != 1 && tmp->tok[i] != TK_END)
			{
				//printf("filling right from ast_loop_and_or\n");
				tmp->right = fill_rightast(tmp, tmp->tok[i+1], ft_strlen(tmp->arg) - tmp->tok[i+1], split_by);
				//printf("\nrecursively calling ast_loop_and_or\n");
				ast_loop_and_or(tmp->right);
				break ;
			}
			else
				tmp->right = NULL;
		}
		else
			i += 3;
		while (tmp->tok[i] == TK_SPACE)	//skips spaces in token table to find proper starting point before recreating another token table later
			i += 3;
	}
	if (!(tmp->left) && tmp->parent != NULL)
		ast_loop_pipe(tmp);
}

static void		ast_loop_semi(t_ast *head)
{
	int		i = 0;
	t_ast	*tmp = head;
	char	*str = tmp->arg;

	while (tmp->tok[i] != -1)
	{
		if (tmp->tok[i] == TK_SEMI)
		{
			//printf("filling left from ast_loop_semi\n");
			tmp->left = fill_leftast(tmp, tmp->tok[i+1], TK_SEMI);
			ast_loop_and_or(tmp->left);
			i += 3;
			while (tmp->tok[i] == TK_SPACE)
				i += 3;
			if (tmp->tok[i] && tmp->tok[i] != 1 && tmp->tok[i] != 16)
			{
				//printf("filling right from ast_loop_semi sending: %s to fill_right\n", tmp->arg);
				tmp->right = fill_rightast(tmp, tmp->tok[i+1], ft_strlen(tmp->arg) - tmp->tok[i+1], TK_SEMI);
				//printf("\nrecursively calling ast_loop_semi\n");
				if (tmp->right)
					ast_loop_semi(tmp->right);
				break ;
			}
			else
				tmp->right = NULL;
		}
		else
			i += 3;
		while (tmp->tok[i] == TK_SPACE)	//skips spaces in token table to find proper starting point before recreating another token table later
			i += 3;
	}
	if (!(tmp->left) && tmp->parent != NULL)	//so that first elements that were recursively filled don't add extra once branch is done
		ast_loop_and_or(tmp);
}

static t_ast	*get_ast(int **tab, char ***argv)
{
	char	*str = NULL;
	t_ast	*head;
	t_ast	*tmp;

	head = (*tab[0] && *tab[0] != 16) ? init_ast(argv) : NULL;
	tmp = head;
	ast_loop_semi(tmp);
	return (head);
}

static void		print_leaf_nodes(t_ast *head)
{
	t_ast	*tmp = head;
	static int	order = 1;

	if (!tmp)
		return ;
	if (!(tmp->left) && !(tmp->right))
	{
		printf("EXECUTE CMD %d with depth %d: %s\n", order++, tmp->depth, tmp->arg);
		(tmp->split_by == TK_SEMI) ? printf("process with semi\n") :
		(tmp->split_by == TK_AND_IF) ? printf("process with AND_IF\n") :
		(tmp->split_by == TK_OR_IF) ? printf("process with OR_IF\n") :
		(tmp->split_by == TK_PIPE) ? printf("process with PIPE\n") :
		printf("\n");
		return ;
	}
	if (tmp->left)
		print_leaf_nodes(tmp->left);
	if (tmp->right)
		print_leaf_nodes(tmp->right);
}

int				main(int argc, char **argv)
{
	int *tab;
	int i = 0;
	t_ast	*head = NULL;

	if (argc == 2)
	{
		printf("%s\n", argv[1]);
		tab = get_tokens(argv[1]);
		head = get_ast(&tab, &argv);
		printf("TREE COMPILED, SENDING TO printLeafNodes\n\n\n");
		print_leaf_nodes(head);
//		printf("trying to call traverse_ast to analyze pipes\n");
//		traverse_ast(head, 3);
	/*	while (tab[i] != -1)
		{
			switch(tab[i])
			{
				case TK_WORD:
					printf("WORD \n");
					break;
				case TK_NEWLINE:
					printf("NEWLINE \n");
					break;
				case TK_IO_NUMBER:
					printf("IO_NUMBER \n");
					break;
				case TK_GREAT:
					printf("GREAT \n");
					break;
				case TK_DGREAT:
					printf("DGREAT \n");
					break;
				case TK_GREATAND:
					printf("GREATAND \n");
					break;
				case TK_LESS:
					printf("LESS \n");
					break;
				case TK_DLESS:
					printf("DLESS \n");
					break;
				case TK_LESSAND:
					printf("LESSAND \n");
					break;
				case TK_PIPE:
					printf("PIPE \n");
					break;
				case TK_SEMI:
					printf("SEMI \n");
					break;
				case TK_COMMENT:
					printf("COMMENT \n");
					break;
				//case TK_SPACE:
				//	printf("SPACE ");
				//	break;
				case TK_AND:
					printf("AND \n");
					break;
				case TK_AND_IF:
					printf("AND_IF \n");
					break;
				case TK_OR_IF:
					printf("OR_IF \n");
					break;
				case TK_END:
					printf("END \n");
					break;
				case TK_PROGRAM:
					printf("PROGRAM \n");
					break;
				case TK_QUOTED_WORD:
					printf("QUOTED_WORD \n");
					break;
				case TK_DQUOTED_WORD:
					printf("DQUOTED_WORD \n");
					break;
			}
			i += 3;
		}
		*/printf("\n");
	} 
	return (0);
}
