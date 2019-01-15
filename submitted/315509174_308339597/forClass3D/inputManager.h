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
			data->_scene->curr_joint = 3;
			if (action == GLFW_PRESS) {
				if (data->_scene->cannotReach()) {
					cout<<"Cannot reach"<<endl;
				}
				else {
					data->_solve = !data->_solve;
				}
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
		GLint viewport[4];
		GLfloat winZ;
		glGetIntegerv(GL_VIEWPORT, viewport);
		if (data->_r_button || data->_l_button) {
			winZ = data->curr_depth;
		}
		else {
			glReadPixels(xpos, DISPLAY_HEIGHT - ypos, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
			data->curr_depth = winZ;
		}
		glm::vec3 screen = glm::vec3(xpos, viewport[3] - ypos, winZ);
		glm::mat4 view = data->_scene->getCamera()->getLookAt2();
		glm::mat4 projection = data->_scene->getCamera()->getPerspective();
		vec3 projected = glm::unProject(screen, view, projection, glm::vec4(0, 0, viewport[2], viewport[3]));
		double factor = 0.05;
		vec3 cursing_delta(projected - data->curr_cursor);
		data->curr_cursor = projected;
		double move_x = data->_curr_x - xpos;
		double move_y = data->_curr_y - ypos;
		data->_curr_x = xpos;
		data->_curr_y = ypos;
		cursing_delta.y = 0;
		
		if (data->_r_button) {
			if (data->_picked == data->_scene) {
				data->_picked->translate(0.1f*cursing_delta);
			}
			else {
				data->_picked->translate(cursing_delta);
			}
			data->_display->Clear(1.0f, 1.0f, 1.0f, 1.0f);
			data->_scene->render();
			data->_display->SwapBuffers();
			data->_scene->updatePickingShader();
		}
		if (data->_l_button) {
			data->_picked->rotateX(true, move_y * 0.7);
			data->_picked->rotateZ(true , -move_x*0.7);
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



