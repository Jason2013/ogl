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

GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path)
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

    GLuint Result;
    GLint InfoLogLength;

    // Compiling vertex shader
    glShaderSource(VertexShaderID, 1, &VertexShaderCode.c_str(), nullptr);
    glCompileShader(VertexShaderID);

    // Checking vertex shader
    glShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glShaderInfoLog(VertexShaderID, VertexShaderErrorMessage.data());
        printf("%s\n", VertexShaderErrorMessage.data());
    }

    // Compiling fragment shader
    glShaderSource(FragmentShaderID, 1, &FragmentShaderCode.c_str(), nullptr);
    glCompileShader(FragmentShaderID);

    // Checking fragment shader
    glShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glShaderInfoLog(FragmentShaderID, FragmentShaderErrorMessage.data());
        printf("%s\n", FragmentShaderErrorMessage.data());
    }

    // Link the program
    GLuint ProgramID;
    ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glShaderInfoLog(ProgramID, ProgramErrorMessage.data());
        printf("%s\n", ProgramErrorMessage.data());
    }

    glDeteachShader(ProgramID, VertexShaderID);
    glDeteachShader(ProgramID, FragmentShaderID);

    glDeleteShader(ProgramID, VertexShaderID);
    glDeleteShader(ProgramID, FragmentShaderID);

    return ProgramID;

}
