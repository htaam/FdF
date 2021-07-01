/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatias <tmatias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:57:56 by tmatias           #+#    #+#             */
/*   Updated: 2021/07/01 18:17:30 by tmatias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_distance(int x1, int y1, int x2, int y2)
{
	int	c;

	c = sqrt(pow((x1 - x2), 2) + (pow((y1 - y2), 2)));
	return (c);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	imgage;
	int		i;
	int		j;
	int		c;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	imgage.img = mlx_new_image(mlx, 1920, 1080);
	imgage.addr = mlx_get_data_addr(imgage.img, &imgage.bits_per_pixel,
			&imgage.line_length, &imgage.endian);
	i = 1;
	while (i < 1920)
	{
		j = 1;
		while (j < 1080)
		{
			c = get_distance(500, 500, i, j);
			if (c >= 200)
				my_mlx_pixel_put(&imgage, i, j, 0x00FF0000);
			else
				my_mlx_pixel_put(&imgage, i, j, 0x00FFFFFF);
			if (i == j)
				my_mlx_pixel_put(&imgage, i, j, 0x000F0F0F);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx, mlx_win, imgage.img, 0, 0);
	mlx_loop(mlx);
}
