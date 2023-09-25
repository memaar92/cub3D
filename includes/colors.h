/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:05:18 by valmpani          #+#    #+#             */
/*   Updated: 2023/09/25 16:49:41 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

// Define color escape codes with invisible markers
# define RED        "\001\x1B[31;1m\002"
# define GREEN      "\001\x1B[32;1m\002"
# define YELLOW     "\001\x1B[33m\002"
# define BLUE       "\001\x1B[38;5;44;1m\002"
# define LIGHT_BLUE "\001\x1B[38;5;33;1m\002"
# define MAGENTA    "\001\x1B[35;1m\002"
# define CYAN       "\001\x1B[36m\002"
# define ESCAPE     "\001\x1B[0m\002"
# define GREY		"\001\x1B[38;5;255m\002"
# define WHITE      "\001\x1B[0;97m\002"
# define BLACK      "\001\x1B[0;30m\002"

#endif
