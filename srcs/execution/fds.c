#include "shell.h"

t_fds	*create_fds_node(int fd)
{
	t_fds	*new_node;

	new_node = malloc(sizeof(t_fds));
	if (!new_node)
		return (NULL);
  new_node->fd = fd;
  new_node->next = NULL;
	return (new_node);
}

void	fd_push_back(t_fds **head, int fd)
{
	t_fds	*new_node;
	t_fds	*current;

	new_node = create_fds_node(fd);
	if (!new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	pop_front_fd(t_fds **head)
{
	t_fds	*tmp;

	if (!*head)
		return ;
	tmp = *head;
		*head = tmp->next;
//  printf("================== %d\n", tmp->fd);
  if (tmp->fd >= 3)
  {
//    printf("================== %d\n", tmp->fd);
    pop_fd(&tmp, tmp->fd);
  }
  if (tmp)
    free(tmp);
  tmp = NULL;
}

void  pop_fd(t_fds **fds, int fd)
{
  t_fds *tmp;

  tmp = *fds;
  if (!tmp)
    return ;
  while (tmp && tmp->fd != fd)
    tmp = tmp->next;
  if (tmp && tmp->fd >= 3)
  {
    close(tmp->fd);
    tmp->fd = -1;
  }
  while (tmp)
  {
    if (tmp->fd >= 3 && tmp->fd == fd)
      tmp->fd = -1;
    tmp = tmp->next;
  }
}

void	pop_all_fd(t_fds **head)
{
	t_fds	*tmp;

	if (!*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		pop_front_fd(&tmp);
  }
  *head = NULL;
}
