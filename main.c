/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmatias <tmatias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:57:56 by tmatias           #+#    #+#             */
/*   Updated: 2021/07/05 18:30:40 by tmatias          ###   ########.fr       */
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

typedef struct s_numbers
{
	float	z_real;
	float	z_imaginary;
	float	c_real;
	float	c_imaginary;
	int	x_max;
	int	y_max;
}			t_numbers;

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
	void		*mlx;
	void		*mlx_win;
	t_data		imgage;
	t_numbers	numbers;
	int			iteration;
	float		temp;

	numbers.x_max = 2550;
	numbers.y_max = 1400;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, numbers.x_max, numbers.y_max, "Hello world!");
	imgage.img = mlx_new_image(mlx, numbers.x_max, numbers.y_max);
	imgage.addr = mlx_get_data_addr(imgage.img, &imgage.bits_per_pixel,
			&imgage.line_length, &imgage.endian);
	numbers.c_real = 0 - (numbers.x_max / 2);
	while (numbers.c_real < numbers.x_max / 2)
	{
		numbers.c_imaginary = 0 - (numbers.y_max / 2);
		while (numbers.c_imaginary < numbers.y_max / 2)
		{
			numbers.z_real = 0;
			numbers.z_imaginary = 0;
			iteration = 0;
			while (pow(numbers.z_real, 2) + pow(numbers.z_imaginary, 2) < 4
				&& iteration < 500)
			{
				temp = pow(numbers.z_real, 2) - pow(numbers.z_imaginary, 2)
					+ (numbers.c_real / (numbers.y_max / 3.5));
				numbers.z_imaginary = 2 * numbers.z_real * numbers.z_imaginary
					+ (numbers.c_imaginary / (numbers.y_max / 3.5));
				numbers.z_real = temp;
				iteration++;
			}
			if (iteration < 500)
			{
				my_mlx_pixel_put(&imgage, numbers.c_real + (numbers.x_max / 2),
					numbers.c_imaginary + (numbers.y_max / 2), (0x00000000 + (iteration * 5000)));
			}
			numbers.c_imaginary++;
		}
		numbers.c_real++;
	}
	mlx_put_image_to_window(mlx, mlx_win, imgage.img, 0, 0);
	mlx_loop(mlx);
}
