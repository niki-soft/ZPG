//
// Created by Jan Mikulenka on 29.11.2021.
//

#ifndef ZPG_GAME_SHADERLOADER_H
#define ZPG_GAME_SHADERLOADER_H


#pragma once
//GLEW - The OpenGL Extension Wrangler Library
#include </usr/local/Cellar/glew/2.2.0_1/include/GL/glew.h> // include GLEW and new version of GL on Windows

#include <string.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class ShaderLoader
{
    GLuint vertexID = 0;
    GLuint fragmentID = 0;
    string loadFile(const char *fname);
protected:
    GLuint	shaderProgramID=0;
public:
    GLuint loadShader(const char *vertexFile, const char *fragmentFile);
    void deleteShader();
    ShaderLoader();
    ShaderLoader(const char *vertexFile, const char *fragmentFile, GLuint *shaderID);
    ~ShaderLoader();
};

#endif //ZPG_GAME_SHADERLOADER_H
