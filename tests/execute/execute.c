#include "minishell.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
	{
		printf("Usage: %s <command>\n", argv[0]);
		return (1);
	}
	ft_memset(&data, 0, sizeof(t_data));
	data.tokens = tokenize_line(argv[1]);
	if (data.tokens)
	{
		printf("Error: tokenize_tokens: Returned NULL\n");
		return (1) 
	}
	if (validate_syntax(&data) != 0)
	{
		printf("Error: validate_syntax: Syntax error\n");
		return (1) 
	}
	data.processes = parse_tokens(data.tokens);
	if (!data.processes)
	{
		printf("Error: parse_tokens: Returned NULL\n");
		return (1) 
	}
    
	// Execution goes here
	return (0);
}