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

static std::list <int> &		glfw_singleton()
{
	static std::list <int>		keys;
	return (keys);
}

void		keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::list <int> &		keys = glfw_singleton();

	if (action == GLFW_PRESS)
		keys.push_back(key);
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
	glfwSetKeyCallback(this->_window, keyCallBack);
    this->centerWindow();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, height, 0.0f, 0.0f, 1.0f);
	return ;
}

void			Glib::centerWindow(void)
{
	   // Get window position and size
    int window_x, window_y;
    glfwGetWindowPos(this->_window, &window_x, &window_y);

    int window_width, window_height;
    glfwGetWindowSize(this->_window, &window_width, &window_height);

    // Halve the window size and use it to adjust the window position to the center of the window
    window_width *= 0.5;
    window_height *= 0.5;

    window_x += window_width;
    window_y += window_height;

    // Get the list of monitors
    int monitors_length;
    GLFWmonitor **monitors = glfwGetMonitors(&monitors_length);

    if(monitors == NULL) {
        // Got no monitors back
        return;
    }

    // Figure out which monitor the window is in
    GLFWmonitor *owner = NULL;
    int owner_x, owner_y, owner_width, owner_height;

    for(int i = 0; i < monitors_length; i++) {
        // Get the monitor position
        int monitor_x, monitor_y;
        glfwGetMonitorPos(monitors[i], &monitor_x, &monitor_y);

        // Get the monitor size from its video mode
        int monitor_width, monitor_height;
        GLFWvidmode *monitor_vidmode = (GLFWvidmode*) glfwGetVideoMode(monitors[i]);

        if(monitor_vidmode == NULL) {
            // Video mode is required for width and height, so skip this monitor
            continue;

        } else {
            monitor_width = monitor_vidmode->width;
            monitor_height = monitor_vidmode->height;
        }

        // Set the owner to this monitor if the center of the window is within its bounding box
        if((window_x > monitor_x && window_x < (monitor_x + monitor_width)) && (window_y > monitor_y && window_y < (monitor_y + monitor_height))) {
            owner = monitors[i];

            owner_x = monitor_x;
            owner_y = monitor_y;

            owner_width = monitor_width;
            owner_height = monitor_height;
        }
    }

    if(owner != NULL) {
        // Set the window position to the center of the owner monitor
        glfwSetWindowPos(this->_window, owner_x + (owner_width * 0.5) - window_width, owner_y + (owner_height * 0.5) - window_height);
    }
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

void			Glib::write(std::string str, int color)
{

}

std::list <std::pair <input, int> >		Glib::getInput(int id)
{
	std::list <std::pair <input, int> >		keys;
	std::list <int> &						pollKeys = glfw_singleton();
	int		state;

	if (glfwWindowShouldClose(this->_window))
	{
		glfwDestroyWindow(this->_window);
		glfwTerminate();
		keys.push_front(std::pair<input, int>(Exit, 4));
	}
	for (auto it = pollKeys.begin(); it != pollKeys.end(); ++it)
	{
		if (this->_input.count((*it)))
			keys.push_front(this->_input.at(*it));
		it = pollKeys.erase(it);
	}
	return (keys);
}

extern "C" Glib *		getGlib()
{
	return (new Glib());
}
