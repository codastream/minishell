#ifndef UTILS_H
# define UTILS_H

void	check_malloc(void *allocated, t_alloc **alloc);

// prompt.c
char	*update_prompt(t_alloc **alloc);

// errors.c
void	printerr(char *msg);

#endif
