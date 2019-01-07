#include "Data.h"
#pragma once   //maybe should be static class
#include "GLFW\glfw3.h"
#include <stdio.h>      
#include <stdlib.h> 
#include <vector>
using namespace std;

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Data *data;
		data = (Data *)glfwGetWindowUserPointer(window);
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			if(action == GLFW_PRESS)
				glfwSetWindowShouldClose(window,GLFW_TRUE);
			break;
		case GLFW_KEY_SPACE:
			if (action == GLFW_PRESS) {
				data->_solve = !data->_solve;
			}
			break;
		case GLFW_KEY_E:
			if (action == GLFW_PRESS) {
				data->_scene->setEuler();
			}
			break;
		case GLFW_KEY_RIGHT:
			if (action == GLFW_PRESS) {
				data->_picked->rotateZ(true, 20);
				data->_display->Clear(1.0f, 1.0f, 1.0f, 1.0f);
				data->_scene->render();
				data->_display->SwapBuffers();
				data->_scene->updatePickingShader();
				Sleep(10);
			}
			break;
		case GLFW_KEY_LEFT:
			if (action == GLFW_PRESS) {
				data->_picked->rotateZ(false, 20);
				data->_display->Clear(1.0f, 1.0f, 1.0f, 1.0f);
				data->_scene->render();
				data->_display->SwapBuffers();
				data->_scene->updatePickingShader();
				Sleep(10);
			}
			break;
		case GLFW_KEY_UP:
			if (action == GLFW_PRESS) {
				data->_picked->rotateX(true, 20);
				data->_display->Clear(1.0f, 1.0f, 1.0f, 1.0f);
				data->_scene->render();
				data->_display->SwapBuffers();
				data->_scene->updatePickingShader();
				Sleep(10);
			}
			break;
		case GLFW_KEY_DOWN:
			if (action == GLFW_PRESS) {
				data->_picked->rotateX(false, 20);
				data->_display->Clear(1.0f, 1.0f, 1.0f, 1.0f);
				data->_scene->render();
				data->_display->SwapBuffers();
				data->_scene->updatePickingShader();
				Sleep(10);
			}
			break;
		case GLFW_KEY_P:
			if (action == GLFW_PRESS) {
				data->_picked->printEulerEngles();
				Sleep(10);
			}
			break;
		case GLFW_KEY_B:
			if (action == GLFW_PRESS) {
				//data->_rcube->rotateBWall();
				data->_display->Clear(1.0f, 1.0f, 1.0f, 1.0f);
				data->_scene->render();
				data->_display->SwapBuffers();
				Sleep(10);
			}
			break;
		case GLFW_KEY_F:
			if (action == GLFW_PRESS) {
				//data->_rcube->rotateFWall();
				data->_display->Clear(1.0f, 1.0f, 1.0f, 1.0f);
				data->_scene->render();
				data->_display->SwapBuffers();
				Sleep(10);
			}
			break;
		case GLFW_KEY_Z:
			if (action == GLFW_PRESS) {
				//data->_rcube->halfAngle();
			}
			break;
		case GLFW_KEY_A:
			if (action == GLFW_PRESS) {
				//data->_rcube->doubleAngle();
			}
			break;
		default:
			break;
		}
	}
	void cursor_position_callback(GLFWwindow* window, double xpos,double ypos)
	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) ==GLFW_PRESS)
		{
			//updatePosition(xpos, ypos);
			//mouseProccessing(GLFW_MOUSE_BUTTON_RIGHT);
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) ==GLFW_PRESS )
		{
			Data *data = (Data *)glfwGetWindowUserPointer(window);
			data->_scene->updatePickingShader();
			unsigned char buff[4];
			glReadPixels(xpos, DISPLAY_HEIGHT - ypos, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, buff);
			int pickedID =
				buff[0] +
				buff[1] * 256 +
				buff[2] * 256 * 256;
			/*cout << "cursor_position_callback" << endl;
			cout<< xpos<<endl;
			cout << ypos << endl;
			cout << pickedID << endl;*/
			//data->_picked = data->_scene->getPickedObject(pickedID);
		}
	}

	static void mouse_callback(GLFWwindow* window, int button, int action, int mods)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		Data *data;
		data = (Data *)glfwGetWindowUserPointer(window);
		if (button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT) {
			Data *data = (Data *)glfwGetWindowUserPointer(window);
			data->_scene->updatePickingShader();
			unsigned char buff[4];
			glReadPixels(xpos, DISPLAY_HEIGHT - ypos, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, buff);
			int pickedID =
				buff[0] +
				buff[1] * 256 +
				buff[2] * 256 * 256;
			data->_picked = data->_scene->getPickedObject(pickedID);
		}
		if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			if (GLFW_PRESS == action)
				data->_r_button = true;
			else if (GLFW_RELEASE == action)
				data->_r_button = false;
		}
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			if (GLFW_PRESS == action)
				data->_l_button = true;
			else if (GLFW_RELEASE == action)
				data->_l_button = false;
		}
		
		
	}
	static void cursor_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Data *data;
		data = (Data *)glfwGetWindowUserPointer(window);
		GLfloat winZ;
		glReadPixels(xpos, DISPLAY_HEIGHT - ypos, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
		double factor = (data->unit_factor*winZ)/data->unit_depth;
		double move_x = data->_curr_x - xpos;
		double move_y = data->_curr_y - ypos;
		data->_curr_x = xpos;
		data->_curr_y = ypos;
		
		if (data->_r_button) {
			data->_picked->translate(vec3(move_x*factor, 0, -move_y*factor));
			data->_display->Clear(1.0f, 1.0f, 1.0f, 1.0f);
			data->_scene->render();
			data->_display->SwapBuffers();
			data->_scene->updatePickingShader();
		}
		if (data->_l_button) {
			//bool right = move_x > 0 ? true : false;
			data->_picked->rotateX(true, move_y);
			data->_picked->rotateZ(true , move_x);
			data->_display->Clear(1.0f, 1.0f, 1.0f, 1.0f);
			data->_scene->render();
			data->_display->SwapBuffers();
			data->_scene->updatePickingShader();
		}
	}
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		double factor = 0.2;
		Data *data;
		data = (Data *)glfwGetWindowUserPointer(window);
		bool in = yoffset > 0 ? true: false;
		data->_picked->zoom(in, yoffset*factor);
		data->_display->Clear(1.0f, 1.0f, 1.0f, 1.0f);
		data->_scene->render();
		data->_display->SwapBuffers();
		data->_scene->updatePickingShader();
	}



