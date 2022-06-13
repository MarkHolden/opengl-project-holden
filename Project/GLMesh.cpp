#pragma once
#include "GLMesh.h"

using namespace std;

bool isWireframes = false;

void GLMesh::Draw()
{
    glBindVertexArray(vertexArrayObject);

    glBindTexture(GL_TEXTURE_2D, textureId);

    if (isWireframes) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframes for testing

    glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}

void GLMesh::UCreateMesh(vector<GLfloat>& vertices, vector<GLushort>& indices)
{
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    glGenBuffers(2, vertexBufferObjects);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjects[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    vertexCount = indices.size();//sizeof(indices) / sizeof(indices[0]); // Memory of indices array divided by the memory of the first element

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBufferObjects[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

    // Creates the Vertex Attribute Pointer
    const GLuint floatsPerVertex = 3; // Number of coordinates per vertex
    const GLuint floatsPerNormal = 3; // unit vector perpendicular to the face
    const GLuint floatsPerTexture = 2; // s, t
    // Strides between vertex coordinates is 8 (x, y, z, n1, n2, n3, s, t). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerTexture); // The number of floats before each

    // Creates the Vertex Attribute Pointer
    const int LOCATION_ATTRIBUTE = 0;
    glVertexAttribPointer(LOCATION_ATTRIBUTE, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(LOCATION_ATTRIBUTE);

    const int COLOR_ATTRIBUTE = 1;
    glVertexAttribPointer(COLOR_ATTRIBUTE, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(COLOR_ATTRIBUTE);

    const int TEXTURE_COORDINATE_ATTRIBUTE = 2;
    glVertexAttribPointer(TEXTURE_COORDINATE_ATTRIBUTE, floatsPerTexture, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
    glEnableVertexAttribArray(TEXTURE_COORDINATE_ATTRIBUTE);
}

void GLMesh::UDestroyMesh()
{
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(2, vertexBufferObjects);
}
