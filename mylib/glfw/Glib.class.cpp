/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Glib.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kperreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:20:49 by kperreau          #+#    #+#             */
/*   Updated: 2017/05/08 19:12:39 by kperreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Glib.class.hpp"
#include <iostream>

Glib::Glib()
{
	this->_input[GLFW_KEY_UP] = std::pair<input, int>(Top, 0);
	this->_input[GLFW_KEY_DOWN] = std::pair<input, int>(Bottom, 0);
	this->_input[GLFW_KEY_LEFT] = std::pair<input, int>(Left, 0);
	this->_input[GLFW_KEY_RIGHT] = std::pair<input, int>(Right, 0);
	this->_input[GLFW_KEY_Z] = std::pair<input, int>(Top, 1);
	this->_input[GLFW_KEY_S] = std::pair<input, int>(Bottom, 1);
	this->_input[GLFW_KEY_Q] = std::pair<input, int>(Left, 1);
	this->_input[GLFW_KEY_D] = std::pair<input, int>(Right, 1);
	this->_input[GLFW_KEY_ESCAPE] = std::pair<input, int>(Exit, 4);
	this->_input[GLFW_KEY_SPACE] = std::pair<input, int>(Pause, 4);
	this->_input[GLFW_KEY_F1] = std::pair<input, int>(F1, 4);
	this->_input[GLFW_KEY_F2] = std::pair<input, int>(F2, 4);
	this->_input[GLFW_KEY_F3] = std::pair<input, int>(F3, 4);
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

	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed

    this->_window = glfwCreateWindow(width, height, "Nibbler GLFW", NULL, NULL);
    if (!this->_window)
    {
        glfwTerminate();
        return ;
    }

    glfwMakeContextCurrent(this->_window);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, height, 0.0f, 0.0f, 1.0f);
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
	glClear(GL_COLOR_BUFFER_BIT);
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
	x *= this->_square;
	y *= this->_square;
	int tx = x - 1;
    int ty = y - 1;
	glColor3ub(0xff, 0xff, 0xff);
	glBegin(GL_QUADS);
		glVertex2f((GLfloat)tx, (GLfloat)ty);
		glVertex2f((GLfloat)tx + this->_square + 2, (GLfloat)ty);
		glVertex2f((GLfloat)tx + this->_square + 2, (GLfloat)ty + this->_square + 2);
		glVertex2f((GLfloat)tx, (GLfloat)ty + this->_square + 2);
	glEnd();
	glColor3ub(this->getColor(color, 0), this->getColor(color, 1), this->getColor(color, 2));
	glBegin(GL_QUADS);
		glVertex2f((GLfloat)x, (GLfloat)y);
		glVertex2f((GLfloat)x + this->_square, (GLfloat)y);
		glVertex2f((GLfloat)x + this->_square, (GLfloat)y + this->_square);
		glVertex2f((GLfloat)x, (GLfloat)y + this->_square);
	glEnd();
	return ;
}

/*void		Glib::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static std::list <std::pair <input, int> >		keys;

	if (action == GLFW_PRESS
		&& this->_input.count(key))
		this->_pollKeys.push_front(this->_input.at(key));
	return ;
}

std::list <std::pair <input, int> >		Glib::getInput(int id)
{
	std::list <std::pair <input, int> >		keys = this->_pollKeys;

	if (glfwWindowShouldClose(this->_window))
	{
		glfwDestroyWindow(this->_window);
		glfwTerminate();
		keys.push_front(std::pair<input, int>(Exit, 4));
	}
	for (auto it = pollKeys.begin(); it != pollKeys.end(); ++it)
	{
		if (this->_input.count(key))
			keys.push_front(this->_input.at(*it));
	}
	pollKeys.clear();
	return (keys);
}*/

std::list <std::pair <input, int> >		Glib::getInput(int id)
{
	std::list <std::pair <input, int> >		keys;
	int		state;

	if (glfwWindowShouldClose(this->_window))
	{
		glfwDestroyWindow(this->_window);
		glfwTerminate();
		keys.push_front(std::pair<input, int>(Exit, 4));
	}
	for (auto it = this->_input.begin(); it != this->_input.end(); ++it)
	{
		state = glfwGetKey(this->_window, (*it).first);
		if (state == GLFW_PRESS)
			keys.push_front((*it).second);
	}
	return (keys);
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
