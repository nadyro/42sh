#include "lexer.h"
#include "libft.h"
#include <stdio.h>

typedef struct	s_ast
{
	int						*tok;
	char					*arg;
	char					*address;
	int						split_by;
	int						depth;
	struct s_ast			*parent;
	struct s_ast			*left;
	struct s_ast			*right;
}				t_ast;

/** START libft functions needed for parser **/

int		ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 == *str2++)
	{
		if (*str1++ == '\0')
			return (0);
	}
	return (*(const unsigned char *)str1 - *(const unsigned char *)(str2 - 1));
}

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

char	*ft_strcat(char *s1, const char *s2)
{
	char *mem;

	mem = s1;
	while (*mem)
		mem++;
	while (*s2)
		*(mem++) = *(s2++);
	*mem = '\0';
	return (s1);
}

char	*ft_strcpy(char *dst, const char *src)
{
	char	*tmp;

	tmp = dst;
	while (*src)
		*(tmp++) = *(src++);
	*tmp = '\0';
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*new;

	if (!(new = (char *)malloc((ft_strlen(s1)) + 1)))
		return (NULL);
	return (ft_strcpy(new, s1));
}

char	*ft_strjoin(char const *name1, char const *name2)
{
	char	*mem;

	if (name1 == NULL || name2 == NULL)
		return (NULL);
	if (!(mem = malloc(sizeof(char) *
					(ft_strlen(name1) + ft_strlen(name2) + 1))))
		return (NULL);
	ft_strcpy(mem, name1);
	ft_strcat(mem, name2);
	return (mem);
}

char	*ft_strchr(const char *s, int c)
{
	while (*(s))
		if (*s++ == (char)c)
			return ((char *)s - 1);
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strstr(const char *big, const char *little)
{
	char	*mem;
	char	*mem2;

	if (*little == '\0')
		return ((char *)big);
	while (*big)
	{
		if (*little == *big)
		{
			mem = (char *)big;
			mem2 = (char *)little;
			while (*mem2 && *mem2 == *mem)
			{
				mem2++;
				mem++;
			}
			if (*mem2 == '\0')
				return ((char *)big);
		}
		big++;
	}
	return (NULL);
}
/** END libft functions needed for parser **/

static t_ast	*fill_leftast(t_ast *parent, int size)
{
	t_ast	*left = NULL;

	if (!(left = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	left->parent = parent;
	left->depth = parent->depth + 1;
	left->address = ft_strjoin(left->parent->address, "L");
	left->arg = ft_strndup(parent->arg, size);
	left->split_by = 0;
	left->tok = get_tokens(left->arg);
	left->left = NULL;
	left->right = NULL;
	printf("in fill_leftast, left->arg = %s\nleft->address = %s\nparent operator = %d\n", left->arg, left->address, parent->split_by);
	return (left);
}

static t_ast	*fill_rightast(t_ast *parent, int start, int size)
{
	t_ast	*right = NULL;
	char	*str;

	if (!(right = (t_ast *)malloc(sizeof(t_ast))))
		return (NULL);
	right->parent = parent;
	str = parent->arg + start;
	right->depth = parent->depth + 1;
	right->address = ft_strjoin(right->parent->address, "R");
	right->arg = ft_strndup(str, size);
	right->split_by = 0;
	right->tok = get_tokens(right->arg);
	right->left = NULL;
	right->right = NULL;
	printf("in fill_rightast, right->arg = %s\nright->address = %s\nparent operator = %d\n", right->arg, right->address, parent->split_by);
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
	head->address = ft_strdup("P");
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
	static int	order = 1;

	while (tmp->tok[i] != -1)
	{
		if (tmp->tok[i] == TK_PIPE)
		{
			tmp->split_by = tmp->tok[i];
			//printf("filling left from ast_loop_pipe\n");
			tmp->left = fill_leftast(tmp, tmp->tok[i+1]);
			i += 3;
			while (tmp->tok[i] == TK_SPACE)
				i += 3;
			if (tmp->tok[i] && tmp->tok[i] != 1 && tmp->tok[i] != TK_END)
			{
				//printf("filling right from ast_loop_pipe with:\ntmp->arg = %s\n", tmp->arg);
				tmp->right = fill_rightast(tmp, tmp->tok[i+1], ft_strlen(tmp->arg) - tmp->tok[i+1]);
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

	if (tmp && !(ft_strstr(tmp->arg, "&&") && !(ft_strstr(tmp->arg, "||"))))
		ast_loop_pipe(tmp);
	while (tmp->tok[i] != -1)
	{
		if (tmp->tok[i] == TK_AND_IF || tmp->tok[i] == TK_OR_IF)
		{
			tmp->split_by = tmp->tok[i];
			//printf("filling left from ast_loop_and_or\n");
			tmp->left = fill_leftast(tmp, tmp->tok[i+1]);
			ast_loop_pipe(tmp->left);
			i += 3;
			while (tmp->tok[i] == TK_SPACE)
				i += 3;
			if (tmp->tok[i] && tmp->tok[i] != 1 && tmp->tok[i] != TK_END)
			{
				//printf("filling right from ast_loop_and_or\n");
				tmp->right = fill_rightast(tmp, tmp->tok[i+1], ft_strlen(tmp->arg) - tmp->tok[i+1]);
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
//	if (!(tmp->left) && tmp->parent != NULL)
	//	ast_loop_pipe(tmp);
}

static void		ast_loop_semi(t_ast *head)
{
	int		i = 0;
	t_ast	*tmp = head;
	char	*str = tmp->arg;

	if (tmp && !(ft_strchr(tmp->arg, ';')))
		ast_loop_and_or(tmp);
	while (tmp->tok[i] != -1)
	{
		if (tmp->tok[i] == TK_SEMI)
		{
			//printf("filling left from ast_loop_semi\n");
			tmp->split_by = TK_SEMI;
			tmp->left = fill_leftast(tmp, tmp->tok[i+1]);
			ast_loop_and_or(tmp->left);
			i += 3;
			while (tmp->tok[i] == TK_SPACE)
				i += 3;
			if (tmp->tok[i] && tmp->tok[i] != 1 && tmp->tok[i] != 16)
			{
				//printf("filling right from ast_loop_semi sending: %s to fill_right\n", tmp->arg);
				tmp->right = fill_rightast(tmp, tmp->tok[i+1], ft_strlen(tmp->arg) - tmp->tok[i+1]);
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
	//if (!(tmp->left) && tmp->parent != NULL)	//so that first elements that were recursively filled don't add extra once branch is done
	//	ast_loop_and_or(tmp);
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

/*static void		execute_leaf_nodes(t_ast *leaf)
{
	t_ast	*tmp = NULL;
	t_ast	*parent = (leaf && leaf->parent) ? leaf->parent : NULL;

	if (leaf && leaf == leaf->parent->right)
		printf("command is on right node, do nothing after execution\n");
	while (tmp)
	{
		while (parent)
		{
			//this if clause is for when top of tree is reached and no && || | have to be accounted for
			//execute before
			if ((parent && parent->parent == NULL) || (parent->parent->split_by == TK_SEMI))
				return ;
			if (parent->parent && parent->parent->split_by == TK_OR_IF)
			{
				if (ft_execute(leaf) == 0)
					return ;
				else
				{

				}	
			}
			if (parent->parent && parent->parent->split_by == TK_AND_IF)
			{

			}
			if (parent->parent && parent->parent->split_by == TK_PIPE)
			{

			}
		}
	}
}
*/
static int ast_evaluate(t_ast *ast)
{
	int		op;
	int		v1;
	int		v2;

	if (ast == NULL)
	{
		printf("error, AST is null, nothing to evaluate\n");
		return (-1);
	}
	if (!(ast->left) && !(ast->right))
	{
		printf("execute %s and do not take next command value into account\n", ast->arg);
		if (ast->arg[0] == 'T')
			return (0);
		else if (ast->arg[0] == 'F')
			return (-1);
	}
	else
	{
		op = ast->split_by;
		if (op == TK_AND_IF)
		{
			v1 = ast_evaluate(ast->left);
			printf("in ANDIF, after evaluating left, left = %d\n", v1);
			if (v1 == 0)
			{
				printf("left branch of ANDIF returned 0\n");
				v2 = ast_evaluate(ast->right);
				if (v2 == 0)
				{
					printf("right branch returned of ANDIF returned 0\n");
					return (0);
				}
				else
				{
					printf("right branch of ANDIF returned %d\n", v2);
					return (-1);
				}
			}
			else
				return (-1);
		}
		else if (op == TK_OR_IF)
		{
			printf("ORIF found at : %s\n", ast->arg);
			v1 = ast_evaluate(ast->left);
			if (v1 == 0)
			{
				printf("left branch of ORIF returned 0\n");
				return v1;
			}
			else
			{
				printf("left branch of ORIF did not return 0, evaluate right branch\n");
				v2 = ast_evaluate(ast->right);
				if (v2 == 0)
					return (0);
				else
					return (-1);
			}
		}
		else if (op == TK_PIPE)
		{
			printf("PIPE found at : %s\n", ast->arg);
			printf("use ft_pipe_execution\n");
			v1 = ast_evaluate(ast->left);
			return (ast_evaluate(ast->right));
		}
		else if (op == TK_SEMI)
		{
			printf("SEMI found at : %s\n", ast->arg);
			v1 = ast_evaluate(ast->left);
			v2 = ast_evaluate(ast->right);
		}
	}
}

static void		print_leaf_nodes(t_ast *head)
{
	t_ast	*tmp = head;
	static int	order = 1;
	static int	split_by = 0;
	t_ast	*parent = NULL;

	if (!tmp)
		return ;
	if (!(tmp->left) && !(tmp->right))
	{
		printf("EXECUTE CMD %d with depth %d: %s\n", order++, tmp->depth, tmp->arg);
		(tmp->parent->split_by == TK_SEMI) ? printf("process with semi\n") :
		(tmp->parent->split_by == TK_AND_IF) ? printf("process with AND_IF\n") :
		(tmp->parent->split_by == TK_OR_IF) ? printf("process with OR_IF\n") :
		(tmp->parent->split_by == TK_PIPE) ? printf("process with PIPE\n") :
		printf("\n");
		return ;
	}
	if (tmp->left)
		print_leaf_nodes(tmp->left);
	if (tmp->split_by == TK_AND_IF)
		printf("verify all previous commands returned 0 before continuing, else STOP\nAlso verify all following commands NOT split by SEMI execute successfully or else stop");
	else if (tmp->split_by == TK_OR_IF)
		printf("if previous command return value != 0, execute other OR_IF commands until success, else stop\n");		
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
		ast_evaluate(head);
		//print_leaf_nodes(head);
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
