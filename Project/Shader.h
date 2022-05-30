#pragma once

#include <GL/glew.h>

/*Shader program Macro*/
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif

/* Vertex Shader Source Code*/
const GLchar* vertexShaderSource = GLSL(440,
    layout(location = 0) in vec3 position; // Vertex data from Vertex Attrib Pointer 0
    layout(location = 1) in vec4 color;    // Color data from Vertex Attrib Pointer 1
    //layout(location = 2) in vec2 coord;    // texture coordinates from Vertex Attrib Pointer 2

    out vec4 vertexColor;  // variable to transfer color data to the fragment shader
    //out vec2 textureCoord; // variable to transfer texture coordinate data to the fragment shader

    //Global variables for the  transform matrices
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(position, 1.0f); // transforms vertices to clip coordinates
        vertexColor = color; // references incoming color data
        //textureCoord = coord; // references incoming texture coordinate data
    }
);


/* Fragment Shader Source Code*/
const GLchar* fragmentShaderSource = GLSL(440,
    in vec4 vertexColor;   // Variable to hold incoming color data from vertex shader
    //in vec2 textureCoord;  // Variable to hold incoming texture coordinate data from vertex shader

    out vec4 fragmentColor;

    //uniform sampler2D tex0;

    void main()
    {
        //fragmentColor = texture(tex0, textureCoord);  //vec4(vertexColor);
        fragmentColor = vec4(vertexColor);
    }
);

class Shader {
public:
    /// <summary>
    /// Create a shader program.
    /// </summary>
    /// <param name="vtxShaderSource">Shader source code.</param>
    /// <param name="fragShaderSource">Fragment shader source code.</param>
    /// <param name="programId"></param>
    static bool UCreateShaderProgram(GLuint& programId)
    {
        // Compilation and linkage error reporting
        int success = 0;
        char infoLog[512];

        // Create a Shader program object.
        programId = glCreateProgram();

        // Create the vertex and fragment shader objects
        GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

        // Retrive the shader source
        glShaderSource(vertexShaderId, 1, &vertexShaderSource, nullptr);
        glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, nullptr);

        // compile the vertex shader
        glCompileShader(vertexShaderId);
        // check for shader compile errors
        glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

            return false;
        }

        glCompileShader(fragmentShaderId); // compile the fragment shader
        // check for shader compile errors
        glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

            return false;
        }

        // Attached compiled shaders to the shader program
        glAttachShader(programId, vertexShaderId);
        glAttachShader(programId, fragmentShaderId);

        glLinkProgram(programId);

        // check for linking errors
        glGetProgramiv(programId, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

            return false;
        }

        glUseProgram(programId);

        return true;
    }

    /// <summary>
    /// Destroy a shader program.
    /// </summary>
    /// <param name="programId"></param>
    static void UDestroyShaderProgram(GLuint& programId)
    {
        glDeleteProgram(programId);
    }
};
