#pragma once

#include <iostream>
#include <assert.h>
#include "GL/glew.h"
#include <string>

class   GLSLProgram{

public:
    typedef GLint   attribute;
    typedef GLint   uniform;

public:
    GLint           _vHandle;
    GLint           _fHandle;
    GLint           _program;

public:
    GLSLProgram();
    virtual ~GLSLProgram(){};
    virtual void    initialize(std::string v, std::string f)=0;//! ��ʼ��
    virtual void    begin()=0;//! ʹ��shader
    virtual void    end()=0;//! ����

protected:
    bool createProgram(const std::string vs, const std::string fs);//!����GPU����
};

GLSLProgram::GLSLProgram() {
    _vHandle    =   -1;
    _fHandle    =   -1;
    _program    =   -1;
}
bool GLSLProgram::createProgram(const std::string vs, const std::string fs){

    bool    result = false;
    do{
        //! ����shader
        _vHandle = glCreateShader(GL_VERTEX_SHADER);
        _fHandle = glCreateShader(GL_FRAGMENT_SHADER);
        //! ָ��shader��Դ����
        glShaderSource(_vHandle, 1, (const GLchar**)&vs, 0);
        glShaderSource(_fHandle, 1, (const GLchar**)&fs, 0);
        //! ����shader
        glCompileShader(_vHandle);
        GLint   status = 0;
        char    compileLog[1024] = { 0 };
        glGetShaderiv(_vHandle, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE){
            glGetShaderInfoLog(_vHandle, sizeof(compileLog), 0, compileLog);
            std::cout<<"VS ERROR!"<<std::endl<<compileLog<<std::endl;
            assert(false && compileLog);
            break;
        }

        glCompileShader(_fHandle);
        glGetShaderiv(_fHandle, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE){
            glGetShaderInfoLog(_fHandle, sizeof(compileLog), 0, compileLog);
            std::cout<<"FS ERROR!"<<std::endl<<compileLog<<std::endl;
            assert(false && compileLog);
            break;
        }
        //! 4��������
        _program = glCreateProgram();
        glAttachShader(_program, _vHandle);
        glAttachShader(_program, _fHandle);
        //! 5���ӳ���
        glLinkProgram(_program);
        glGetProgramiv(_program, GL_LINK_STATUS, &status);
        if (status == GL_FALSE){
            glGetProgramInfoLog(_program, sizeof(compileLog), 0, compileLog);
            break;
        }
        result = true;

    } while (false);

    if (!result){
        if (_vHandle != -1){
            glDeleteShader(_vHandle);
        }
        if (_fHandle != -1){
            glDeleteShader(_fHandle);
        }
        if (_program != -1){
            glDeleteProgram(_program);
        }
        _vHandle = -1;
        _fHandle = -1;
        _program = -1;
    }

    return  result;
}
