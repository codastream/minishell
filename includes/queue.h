#ifndef HASH_H
# define HASH_H

#include "../libft/includes/libft.h"

typedef struct s_queue
{
	void	**data;
	int		max_size;
	int		items_nb;
	int		front;
	int		rear;
}	t_queue;

t_queue	*ft_qnew(int max_size);
bool	ft_qis_empty(t_queue *queue);
bool	ft_qis_full(t_queue *queue);
void	*ft_qpeek(t_queue *queue);
void	ft_qadd(t_queue *queue, void *data);
void	*ft_qexit(t_queue *queue);
void	ft_qprint_as_string(t_queue *queue);

# endif
