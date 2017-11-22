
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;


#ifndef SHADER_H
#define SHADER_H



struct shader
{
	GLuint vertShaderHandle, fragShaderHandle, programHandle;

	~shader()
	{
		glDeleteShader(vertShaderHandle);
		glDeleteShader(fragShaderHandle);
		glDeleteProgram(programHandle);
	}


	void setShaders(char*  vertShaderFileName, char* fragShaderFileName)
	{
		// WRITE ALL OF YOUR QUESTION 1 CODE IN HERE! 
		// (it should be approximately 20 lines of code)
		// (Note: you can use the utility function "readTxtFile" to load the 
		// shader code from a text file into a C_string)


		//*** Step 1: load and compile the vertex and fragment shaders ***//

	GLuint vertShaderHandle(glCreateShader(GL_VERTEX_SHADER)); 
	GLuint fragShaderHandle(glCreateShader(GL_FRAGMENT_SHADER)); 
	
	char* vertShaderSource(readTxtFile("student_code/toon.vert"));
	char* fragShaderSource(readTxtFile("student_code/toon.frag"));
	
	glShaderSource(vertShaderHandle, 1, (const char**) &vertShaderSource, NULL);
	glShaderSource(fragShaderHandle, 1, (const char**) &fragShaderSource, NULL);
	if (vertShaderSource != NULL) free(vertShaderSource);
	if (fragShaderSource != NULL) free(fragShaderSource);
	
	glCompileShader(vertShaderHandle);
	glCompileShader(fragShaderHandle);

	if (!glVerifyHandle(vertShaderHandle))
		throw runtime_error("Failed to compile vertex shader");
	if (!glVerifyHandle(fragShaderHandle))
		throw runtime_error("Failed to compile fragment shader");



		//*** Step 2: link and install the shading program ***//
	
	GLuint programHandle(glCreateProgram()); 

	glAttachShader(programHandle, vertShaderHandle);
	glAttachShader(programHandle, fragShaderHandle);

	glLinkProgram(programHandle);

	if (!glVerifyHandle(programHandle))
		throw runtime_error("Failed to link program");

	glDetachShader(programHandle, vertShaderHandle);
	glDetachShader(programHandle, fragShaderHandle);

	glUseProgram(programHandle);

	} // NO MORE CHANGES PAST THIS POINT!


	char* readTxtFile(char* fileName) // reads a text file into a C string
	{
		ifstream infile(fileName, ios::binary);
		if (!infile) throw runtime_error(string("Cannot open file ") + fileName);
		infile.seekg(0, ios::end);
		size_t length(infile.tellg());
		char* data(new char[length + 1]);
		infile.seekg(0, ios::beg);
		infile.read(data, length);
		data[length] = '\0'; // end of string
		infile.close();
		return data;
	}


	int glVerifyHandle(GLuint handle) // verifies program attached to handle
	{
		int logLen, checkLen;
		glGetObjectParameterivARB(handle, GL_OBJECT_INFO_LOG_LENGTH_ARB, &logLen);
		char* infoLog(new char[logLen]);
		glGetInfoLogARB(handle, logLen, &checkLen, &infoLog[0]);
		if (checkLen > 0) {
			cerr << "Error:" << endl << infoLog << endl;
			return 0; // failed
		}
		return 1; // okay
	}

};

#endif
