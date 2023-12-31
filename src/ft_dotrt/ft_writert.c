/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghupa <sanghupa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:22:35 by sanghupa          #+#    #+#             */
/*   Updated: 2023/12/31 01:53:20 by sanghupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dotrt.h"

// Temporary function to set dotrt
void	set_dotrt(t_dotrt *rt)
{
	// rt->a->type = AMBIENT;
	// rt->a->ratio = 0.15;
	// rt->a->color = (t_vec3){255/255, 255/255, 255/255};

	// rt->c->type = CAMERA;
	// rt->c->point = (t_vec3){0.0, 0.0, 70};
	// rt->c->vector = (t_vec3){0.0, 0.0, -1.0};
	// rt->c->value1 = 70;

	// rt->l->type = LIGHT;
	// rt->l->point = (t_vec3){30, 10, 40};
	// rt->l->ratio = 0.3;
	// rt->l->color = (t_vec3){255/255, 255/255, 255/255};

	// rt->sp[0] = init_subrt();
	// rt->sp[0]->type = SPHERE;
	// rt->sp[0]->point = (t_vec3){-10, -10, 0};
	// rt->sp[0]->value1 = 20 / 2;	// convert diameter into radius, 지름 to 반지름
	// rt->sp[0]->color = (t_vec3){255/255, 255/255, 255/255};
	// rt->cnt_sp++;
	// rt->sp[1] = init_subrt();
	// rt->sp[1]->type = SPHERE;
	// rt->sp[1]->point = (t_vec3){15, -10, 20};
	// rt->sp[1]->value1 = 5 / 2;	// convert diameter into radius, 지름 to 반지름
	// rt->sp[1]->color = (t_vec3){255/255, 0/255, 0/255};
	// rt->cnt_sp++;

	// rt->pl[0] = init_subrt();
	// rt->pl[0]->type = PLANE;
	// rt->pl[0]->point = (t_vec3){0.0, -20.0, 0.0};
	// rt->pl[0]->vector = (t_vec3){0, 1, 0};
	// // rt->pl[0]->color = (t_vec3){155/255, 155/255, 155/255};
	// rt->pl[0]->color = init_vector(0.48, 0.83, 0.53);
	// rt->cnt_pl++;

	// rt->cy[0] = init_subrt();
	// rt->cy[0]->type = CYLINDER;
	// rt->cy[0]->point = (t_vec3){33, -10, 10};
	// rt->cy[0]->vector = (t_vec3){0, 1, 0};
	// rt->cy[0]->value1 = 5;	// diameter
	// rt->cy[0]->value2 = 20;	// height
	// rt->cy[0]->color = (t_vec3){0/255, 0/255, 255/255};
	// rt->cnt_cy++;

	////////////////////

	rt->a->type = AMBIENT;
	rt->a->ratio = 0.1;
	rt->a->color = (t_vec3){255/255.0, 255/255.0, 255/255.0};

	rt->c->type = CAMERA;
	rt->c->point = (t_vec3){-10.0, 3.0, 40};
	rt->c->vector = (t_vec3){0.5, 0.0, -1.0};
	rt->c->value1 = 90;

	rt->l->type = LIGHT;
	rt->l->point = (t_vec3){-30, 5, 40};
	rt->l->ratio = 0.8;
	rt->l->color = (t_vec3){255/255.0, 255/255.0, 255/255.0};

	rt->sp[0] = init_subrt();
	rt->sp[0]->type = SPHERE;
	rt->sp[0]->point = (t_vec3){0, -5, 5};
	rt->sp[0]->value1 = 10 / 2;	// convert diameter into radius, 지름 to 반지름
	rt->sp[0]->color = (t_vec3){255/255.0, 0/255.0, 0/255.0};
	rt->cnt_sp++;

	rt->pl[0] = init_subrt();
	rt->pl[0]->type = PLANE;
	rt->pl[0]->point = (t_vec3){0.0, -10.0, 0.0};
	rt->pl[0]->vector = (t_vec3){0, 0, -1};
	rt->pl[0]->color = (t_vec3){0/255.0, 0/255.0, 255/255.0};
	rt->cnt_pl++;
	rt->pl[1] = init_subrt();
	rt->pl[1]->type = PLANE;
	rt->pl[1]->point = (t_vec3){0.0, -10.0, 0.0};
	rt->pl[1]->vector = (t_vec3){0, 1, 0};
	rt->pl[1]->color = (t_vec3){55/255.0, 55/255.0, 55/255.0};
	// rt->pl[1]->color = init_vector(0.48, 0.83, 0.53);
	rt->cnt_pl++;

	rt->cy[0] = init_subrt();
	rt->cy[0]->type = CYLINDER;
	rt->cy[0]->point = (t_vec3){-20, -5, 5};
	rt->cy[0]->vector = (t_vec3){0, 1, 0};
	rt->cy[0]->value1 = 10 / 2;	// diameter
	rt->cy[0]->value2 = 40;	// height
	rt->cy[0]->color = (t_vec3){0/255.0, 255/255.0, 0/255.0};
	rt->cnt_cy++;

	////////////////////

	// rt->a->type = AMBIENT;
	// rt->a->ratio = 0.5;
	// rt->a->color = (t_vec3){255/255, 255/255, 255/255};

	// rt->c->type = CAMERA;
	// rt->c->point = (t_vec3){0.0, 20.0, -15};
	// rt->c->vector = (t_vec3){0.0, -1.0, 0.5};
	// rt->c->value1 = 90;

	// rt->l->type = LIGHT;
	// rt->l->point = (t_vec3){-20, 50, -20};
	// rt->l->ratio = 1.0;
	// // rt->l->color = (t_vec3){128/255, 128/255, 128/255};
	// rt->l->color = (t_vec3){255/255, 255/255, 255/255};

	// rt->sp[0] = init_subrt();
	// rt->sp[0]->type = SPHERE;
	// rt->sp[0]->point = (t_vec3){20, 0, 20};
	// rt->sp[0]->value1 = 20 / 2;	// convert diameter into radius, 지름 to 반지름
	// rt->sp[0]->color = (t_vec3){255/255, 255/255, 255/255};
	// rt->cnt_sp++;
	// rt->sp[1] = init_subrt();
	// rt->sp[1]->type = SPHERE;
	// rt->sp[1]->point = (t_vec3){20, 0, -20};
	// rt->sp[1]->value1 = 20 / 2;	// convert diameter into radius, 지름 to 반지름
	// rt->sp[1]->color = (t_vec3){255/255, 0/255, 0/255};
	// rt->cnt_sp++;

	// rt->pl[0] = init_subrt();
	// rt->pl[0]->type = PLANE;
	// rt->pl[0]->point = (t_vec3){0.0, -5.0, 0.0};
	// rt->pl[0]->vector = (t_vec3){0, 1, 0};
	// rt->pl[0]->color = (t_vec3){200/255, 255/255, 100/255};
	// rt->cnt_pl++;

	// rt->cy[0] = init_subrt();
	// rt->cy[0]->type = CYLINDER;
	// rt->cy[0]->point = (t_vec3){0, 0, 0};
	// rt->cy[0]->vector = (t_vec3){0, 1, 0};
	// rt->cy[0]->value1 = 10 / 2;	// diameter
	// rt->cy[0]->value2 = 10;	// height
	// rt->cy[0]->color = (t_vec3){0/255, 0/255, 255/255};
	// rt->cnt_cy++;
}
