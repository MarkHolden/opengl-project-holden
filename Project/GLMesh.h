#pragma once
#include <GL/glew.h>
#include <vector>

/// <summary>
/// Stores the GL data relative to a given mesh.
/// </summary>
class GLMesh
{
public:
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

    /// <summary>
    /// Texture to render on this object.
    /// </summary>
    GLuint textureId;

    /// <summary>
    /// Draw the mesh.
    /// </summary>
    void Draw();

    /// <summary>
    /// You Create a Mesh!
    /// <para>Function to create the Vertex Buffer Object</para>
    /// </summary>
    /// <param name="mesh">Mesh to create.</param>
    /// <param name="vertices">Vector containing the vertices.</param>
    /// <param name="indices">Vector containing the indices.</param>
    void UCreateMesh(std::vector<GLfloat>& vertices, std::vector<GLushort>& indices);

    /// <summary>
    /// You Destroy a Mesh!
    /// </summary>
    /// <param name="mesh"></param>
    void UDestroyMesh();    
};