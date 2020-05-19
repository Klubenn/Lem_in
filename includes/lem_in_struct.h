/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 20:59:47 by gtapioca          #+#    #+#             */
/*   Updated: 2020/04/06 16:32:13 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_STRUCT_H
# define LEM_IN_STRUCT_H

struct s_lem1;

typedef struct			s_links
{
	int					weight;
	int					flag;
	int					ant_number;
	struct s_links		*next;
	struct s_links		*prev;
	struct s_lem1		*connection_room;
}						t_links;

/*
** each struct contains one path, path length and link to the first room from
** the start which defines the beginning of the path
** next and prev are links to other paths within the same solution
*/
typedef struct			s_sol_links
{
	int					length;
	int					ants_to_pass;
	int					ants_to_pass_num;
	t_links				*links;
	t_links				*links_end;
	struct s_sol_links	*prev;
	struct s_sol_links	*next;
}						t_sol_links;

/*
** main structure with links to several solutions. Each solution can contain
** several paths; moves is calculated as number of moves, needed for this
** solution to put through all ants
*/
typedef struct			s_solution
{
	int					moves;
	t_sol_links			*sol_links;
	struct s_solution	*prev;
	struct s_solution	*next;
}						t_solution;

typedef struct			s_parents
{
	struct s_parents	*prev;
	struct s_lem1		*vertex;
}						t_parents;

typedef struct			s_lem1
{
	int					flag;
	char				*room_name;
	int					position[2];
	int					room_type;
	struct s_lem1		*next;
	struct s_lem1		*prev;
	struct s_links		*links;
	t_parents			*parents;
	t_parents			*current;
}						t_lem1;

typedef struct			s_lem0
{
	int					ants;
	int					tmp_info;
	int					numbered;
	t_lem1				*start;
	t_lem1				*end;
	t_lem1				*lem1[10];
	t_list				*head_print;
	t_list				*print;
	t_solution			*solution;
}						t_lem0;

typedef struct			s_queue
{
	bool				state;
	t_lem1				*vertex;
	struct s_queue		*next;
}						t_queue;

typedef struct			s_way
{
	t_lem1				*vertex;
	struct s_way		*next;
}						t_way;

typedef struct			s_way_holder
{
	t_way				*way;
	struct s_way_holder *next;
}						t_way_holder;

#endif
