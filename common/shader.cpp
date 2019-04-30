#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include "shader.hpp"

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
{
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    string VertexShaderCode;
    ifstream VertexShaderStream(vertex_file_path);
    if (VertexShaderStream.is_open()) {
        VertexShaderCode = string(istreambuf_iterator<char>(VertexShaderStream), istreambuf_iterator<char>());
    } else {
        printf("Impossible to open %s. Are you in the right directory? Don't forget to read the FAQ!\n", vertex_file_path);
        getchar();
        return -1;
    }

    string FragmentShaderCode;
    ifstream FragmentShaderStream(fragment_file_path);
    if (FragmentShaderStream.is_open()) {
        FragmentShaderCode = string(istreambuf_iterator<char>(FragmentShaderStream), istreambuf_iterator<char>());
    } else {
        printf("Impossible to open %s. Are you in the right directory? Don't forget to read the FAQ!\n", fragment_file_path);
        getchar();
        return -1;
    }

    GLint Result;
    GLint InfoLogLength;

    // Compiling vertex shader
    const char* VertexShaderPointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexShaderPointer, nullptr);
    glCompileShader(VertexShaderID);

    // Checking vertex shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, VertexShaderErrorMessage.size(), nullptr, VertexShaderErrorMessage.data());
        printf("%s\n", VertexShaderErrorMessage.data());
    }

    // Compiling fragment shader
    const char* FragmentShaderPointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentShaderPointer, nullptr);
    glCompileShader(FragmentShaderID);

    // Checking fragment shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, FragmentShaderErrorMessage.size(), nullptr, FragmentShaderErrorMessage.data());
        printf("%s\n", FragmentShaderErrorMessage.data());
    }

    // Link the program
    GLuint ProgramID;
    ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, ProgramErrorMessage.size(), nullptr, ProgramErrorMessage.data());
        printf("%s\n", ProgramErrorMessage.data());
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;

}
