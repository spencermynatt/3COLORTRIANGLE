#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;
const char* vertex_shader =
"#version 430 core\n"
"layout(location = 0) in vec2 position;\n"
//in = input the location
"void main()\n"
"{\n"
"gl_Position = vec4(position, 0, 1.0);\n"
"}\n";
const char* fragment_shader =
"#version 430\n"
"out vec4 color;\n"
//out put information
"uniform vec4 newcolor;\n"
//uniforms are global variables
//work similarly to out variables
"void main()\n"
"{\n"
"color = newcolor;\n"

"}\n";
int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 600, "spencer's triangle", NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
	};
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, 800, 600);


	float points[]{
	  0.5f, -0.5f,
		-0.5f, -0.5f,
		 0.0f,  0.5f,
	

	};

	int vertex = glCreateShader(GL_VERTEX_SHADER);
	int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	const char* character_strings[1];
	character_strings[0] = vertex_shader;
	glShaderSource(vertex, 1, character_strings, 0);
	character_strings[0] = fragment_shader;
	glShaderSource(fragment, 1, character_strings, 0);
	glCompileShader(vertex);
	glCompileShader(fragment);
	int program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	glUseProgram(program);


	unsigned int space;
	glGenBuffers(1, &space);
	glGenVertexArrays(1, &space);
	glBindBuffer(GL_ARRAY_BUFFER, space);
	glBindVertexArray(space);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	

	while (!glfwWindowShouldClose(window)) {

		glUseProgram(program);
		
		//float time = glfwGetTime();
		//getting the running time

		//float greenvalue = cos(time) / 1.0f + 0.5;
		//the sin function in trig
		//divides the opposite side by the hypotenuse side
		//our triangle is an isosceles triangle 
		// we vary the color in the range of 0.0 - 1.0
		//by using the sin function
		//cos and sin are the same speed
		//tan removes the triangle much faster
		//time is stored in either sin, cos, tan,
		// function(x) / a + b
		//a determines the time it takes to go from nothing 
		//to a triangle
		//i think b determines how much it will
		//remove the triangle

		int vertex_color_location = glGetUniformLocation(program, "newcolor");
		//program is the shader
		//the next is the variable name
		//glUniform4f(vertex_color_location, 0.0f, greenvalue, 0.0f, 1.0f);
		//glUniform has 4 floats, 
		//glUniform4f(x, y, b, c, d);
		//x is the location of the uniform variable
		//y b c d, are just the colors
		//green value just changes one of the colors to change 
		//the whole thing
		
		//we have our original color
		//our uniform
		//code i wrote myself
		float r = 0.05f;
		while (r < 1)  //while 0.09 is less than 1
		{

			glUseProgram(program);
			glUniform4f(vertex_color_location, r, 0.4f, 0.3f, 0.0f);
			//change the 0.04 value to 0.09
			//after it repeats once, the r value will be
			//0.09 + 0.10 = 0.29
			//
			
			glBindVertexArray(space); //bind the vertices
			glDrawArrays(GL_TRIANGLES, 0, 3); //draw triangle
			glfwSwapBuffers(window);
			glfwPollEvents();
			r = r + 0.10; //then add 0.09 by 0.10
			//repeat until r equals 1
			//you can see that the color goes from green, yellow to orange
			//this is happening because  we're increasing the value each time
			glfwSwapInterval(20); 
		}
		
		
	}

	glfwTerminate();
	return 0;
}