#include <Windows.h>
#include <iostream>
#include "inputManager.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


using namespace glm;

int main(int argc, char** argv)
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	
	Vertex cube_vertices[] =
	{
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1),glm::vec3(0.970,0.394,0.945)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1),glm::vec3(0.970,0.394,0.945)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1),glm::vec3(0.970,0.394,0.945)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1),glm::vec3(0.970,0.394,0.945)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),

		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0),glm::vec3(0.906,0.915,0.075)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0),glm::vec3(0.906,0.915,0.075)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0),glm::vec3(0.906,0.915,0.075)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0),glm::vec3(0.906,0.915,0.075)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),

		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0),glm::vec3(0.410,0.112,0.374)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0),glm::vec3(0.410,0.112,0.374)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0),glm::vec3(0.410,0.112,0.374)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0),glm::vec3(0.410,0.112,0.374))
	};

	Vertex reference_frame_vertices[] =
	{
		Vertex(glm::vec3(-10, 0, 0), glm::vec2(1, 0), glm::vec3(0, 0, -1),glm::vec3(0, 0, 0)),
		Vertex(glm::vec3(10, 0, 0), glm::vec2(0, 0), glm::vec3(0, 0, -1),glm::vec3(0, 0, 0)),
		Vertex(glm::vec3(0, 10, 0), glm::vec2(0, 1), glm::vec3(0, 0, -1),glm::vec3(0, 0, 0)),
		Vertex(glm::vec3(0, -10, 0), glm::vec2(1, 1), glm::vec3(0, 0, -1),glm::vec3(0, 0, 0)),
		Vertex(glm::vec3(0, 0, 10), glm::vec2(1, 0), glm::vec3(0, 0, 1),glm::vec3(0, 0, 0)),
		Vertex(glm::vec3(0, 0, -10), glm::vec2(0, 0), glm::vec3(0, 0, 1),glm::vec3(0, 0, 0))
	};

	unsigned int cube_indices[] = {
							  0, 1, 2,
							  0, 2, 3,

							  6, 5, 4,
							  7, 6, 4,

							  10, 9, 8,
							  11, 10, 8,

							  12, 13, 14,
							  12, 14, 15,

							  16, 17, 18,
							  16, 18, 19,

							  22, 21, 20,
							  23, 22, 20
	                          };
	unsigned int reference_frame_indices[] = {
							  0, 1, 0,
							  0, 1, 0,

							  2, 3, 2,
							  2, 3, 2,

							  4, 5, 4,
							  4, 5, 4
	};
    Mesh cube_mesh(cube_vertices, sizeof(cube_vertices)/sizeof(cube_vertices[0]), cube_indices, sizeof(cube_indices)/sizeof(cube_indices[0]));
	Mesh referene_frame_mesh(reference_frame_vertices, sizeof(reference_frame_vertices) / sizeof(reference_frame_vertices[0]), reference_frame_indices, sizeof(reference_frame_indices) / sizeof(reference_frame_indices[0]));
	Shader shader("./res/shaders/basicShader");
	Shader picking_shader("./res/shaders/Picking");
	Texture tex_cube("./res/textures/plane.png");
	Texture tex_box("./res/textures/box0.bmp");
	Scene scene(&cube_mesh, &referene_frame_mesh, &shader, &picking_shader, &tex_cube, &tex_box);
	Data data(&scene, &display, &picking_shader);
	glfwSetWindowUserPointer(display.m_window, (void *)&data);
	glfwSetKeyCallback(display.m_window, key_callback);
	glfwSetMouseButtonCallback(display.m_window, mouse_callback);
	glfwSetCursorPosCallback(display.m_window, cursor_callback);
	glfwSetScrollCallback(display.m_window, scroll_callback);
	display.Clear(1.0f, 1.0f, 1.0f, 1.0f);
	scene.render();
	display.SwapBuffers();
	scene.updatePickingShader();
	glfwSetInputMode(display.m_window, GLFW_STICKY_KEYS, 0);
	int solver_softer = 1000;
	while (!glfwWindowShouldClose(display.m_window))
	{
		if (data._solve) {
			if (!scene.isDone() && solver_softer >= SOLVER_SOFTER) {
				display.Clear(1.0f, 1.0f, 1.0f, 1.0f);
				scene.solve();
				scene.changeJoint();
				scene.render();
				display.SwapBuffers();
				scene.updatePickingShader();
				solver_softer = 0;
			}
			solver_softer++;
		}
		glfwPollEvents();
	}
	return 0;
}



