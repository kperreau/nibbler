/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Glib.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:20:49 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/05 22:35:47 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Glib.class.hpp"
#include <iostream>

Glib::Glib()
{
	this->_input[0][GLFW_KEY_UP] = Top;
	this->_input[0][GLFW_KEY_DOWN] = Bottom;
	this->_input[0][GLFW_KEY_LEFT] = Left;
	this->_input[0][GLFW_KEY_RIGHT] = Right;
	this->_input[1][GLFW_KEY_W] = Top;
	this->_input[1][GLFW_KEY_S] = Bottom;
	this->_input[1][GLFW_KEY_A] = Left;
	this->_input[1][GLFW_KEY_D] = Right;
	this->_input[4][GLFW_KEY_ESCAPE] = Exit;
	this->_input[4][GLFW_KEY_SPACE] = Pause;
	this->_input[4][GLFW_KEY_F1] = F1;
	this->_input[4][GLFW_KEY_F2] = F2;
	this->_input[4][GLFW_KEY_F3] = F3;
	return ;
}

Glib::~Glib(void)
{
	return ;
}

Glib::Glib(Glib const & src)
{
	//*this = src;
	return ;
}

void			Glib::init(int width, int height, int square)
{
	this->_width = width;
	this->_height = height;
	this->_square = square;
	
	if (!glfwInit())
        return ;

    this->_window = glfwCreateWindow(width, height, "Nibbler GLFW", NULL, NULL);
    if (!this->_window)
    {
        glfwTerminate();
        return ;
    }
    glfwMakeContextCurrent(this->_window);
	return ;
}

GLFWwindow*		Glib::getWindow(void)
{
	return (this->_window);
}

void			Glib::exit(void)
{
	glfwDestroyWindow(this->_window);
	glfwTerminate();
	return ;
}

void			Glib::display(void)
{
	glfwSwapBuffers(this->_window);
	glfwGetFramebufferSize(this->_window, &this->_width, &this->_height);
    glViewport(0, 0, this->_width, this->_height);
	/*SDL_RenderPresent(this->_renderer);
	SDL_SetRenderDrawColor( this->_renderer, 0, 0, 0, 0 );
	SDL_RenderClear( this->_renderer );*/
	return ;
}

void			Glib::clear(void)
{
	//SDL_RenderClear( this->_renderer );
	return ;
}

int			Glib::getColor(int color, int type)
{
	return ((color >> (type * 8)) & 0xff);
}

void			Glib::draw(int x, int y, int color)
{
	glTranslatef(0.0f,0.0f,-6.0f);  
	const GLfloat quadVertices[] = { -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 
        1.0f,-1.0f, 0.0f,
        -1.0f,-1.0f, 0.0f
    };
    glVertexPointer(3, GL_FLOAT, 0, quadVertices);
    glDrawArrays(GL_QUADS, 0, 4);
	/*SDL_Rect r;
    r.x = x * this->_square;
    r.y = y * this->_square;
    r.w = this->_square;
    r.h = this->_square;
    SDL_SetRenderDrawColor( this->_renderer, this->getColor(color, 0), this->getColor(color, 1), this->getColor(color, 2), 0 );
	SDL_RenderFillRect( this->_renderer, &r );
    r.x = x * this->_square-1;
    r.y = y * this->_square-1;
    r.w = this->_square+2;
    r.h = this->_square+2;
    SDL_SetRenderDrawColor(this->_renderer, 0xff, 0xff, 0xff, 0);
    SDL_RenderDrawRect( this->_renderer, &r );*/
	return ;
}

input			Glib::getInput(int id)
{
	if (glfwWindowShouldClose(this->_window)) {
		glfwDestroyWindow(this->_window);
		glfwTerminate();
		return (Exit);
	}
	for (auto it = this->_input[id].begin(); it != this->_input[id].end(); ++it)
	{
		if (glfwGetKey(this->_window, it->first) == GLFW_PRESS)
			return (it->second);
	}
	return (None);
}

/*IGlib &			Glib::operator=(IGlib const & rhd)
{
	return (*this);
}
*/

extern "C" Glib *		getGlib()
{
	return (new Glib());
}
