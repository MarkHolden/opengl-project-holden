#pragma once
#include <GL/glew.h>

bool isWireframes = false;

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

    void Draw()
    {
        glBindVertexArray(vertexArrayObject);

        glBindTexture(GL_TEXTURE_2D, textureId);

        if (isWireframes) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframes for testing

        glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_SHORT, nullptr);
        glBindVertexArray(0);
    }
};