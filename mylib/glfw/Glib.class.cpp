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

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

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
	glfwPollEvents();
	glfwGetFramebufferSize(this->_window, &this->_width, &this->_height);
    glViewport(0, 0, this->_width, this->_height);
	return ;
}

void			Glib::clear(void)
{
	return ;
}

int			Glib::getColor(int color, int type)
{
	return ((color >> (type * 8)) & 0xff);
}

void			Glib::draw(int x, int y, int color)
{
	glClearColor(0.0F,0.0F,0.0F,0.0F) ;
	glClear(GL_COLOR_BUFFER_BIT) ;
	glColor3f(1.0F,1.0F,1.0F) ;
	glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0) ;
	glBegin(GL_POLYGON) ;
	glVertex2f(-0.5F,-0.5F) ;
	glVertex2f(-0.5F,0.5F) ;
	glVertex2f(0.5F,0.5F) ;
	glVertex2f(0.5F,-0.5F) ;
	glEnd() ;
	glFlush() ;
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
