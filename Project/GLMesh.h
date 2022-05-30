#pragma once
#include <GL/glew.h>

/// <summary>
/// Stores the GL data relative to a given mesh.
/// </summary>
struct GLMesh
{
    /// <summary>
    /// Handle for the vertex array object.
    /// </summary>
    GLuint vertexArrayObject;

    /// <summary>
    /// Handle for the vertex buffer object.
    /// </summary>
    GLuint vertexBufferObjects[2];

    /// <summary>
    /// Number of vertices of the mesh.
    /// </summary>
    GLuint vertexCount;
};