//===============================================================
// Author:  Mark Holden
// Course:  CS-330 Computer Graphics
// Date:    5/22/2022
// 
//===============================================================

#include <iostream>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

#include "GLMesh.h"
#include "Shader.h"
#include "Starship.h"
#include <vector>

using namespace std;

const char* const WINDOW_TITLE = "SpaceX Starship";
const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 1200;

GLFWwindow* mainWindow = nullptr;
GLMesh mesh;
GLuint shaderProgramId;
GLuint tilesTexture;

/// <summary>
/// Speed of camera movment
/// </summary>
GLfloat speed = 5.0f;

// Camera direction and position
const glm::vec3 gWorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 gCameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 gCameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 gCameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 gCameraRight = glm::normalize(glm::cross(gCameraFront, gCameraUp));

// Mouse input
float gLastX = WINDOW_WIDTH / 2.0f;
float gLastY = WINDOW_HEIGHT / 2.0f;
bool gFirstMouse = true;
GLfloat gYaw = -90.0f;
GLfloat gPitch = 0.0f;

/// <summary>
/// Toggle for orthographic or perspective views.
/// </summary>
bool isOrthographic = false;

// Timing
double gDeltaTime = 0.0f; // time between current frame and last frame.
double gLastFrame = 0.0f; // time of the last frame (used to calculate delta).
//double previousTime = glfwGetTime();
//float rotationDegrees = 0.0f;

/// <summary>
/// Main entry point for the application.
/// </summary>
/// <param name="argc">Argument count.</param>
/// <param name="argv">Argument values.</param>
/// <returns>Exit code.</returns>
int main(int argc, char* argv[]);

/// <summary>
/// You Initialize!
/// </summary>
/// <param name="">Argument count.</param>
/// <param name="">Argument values.</param>
/// <param name="window">GLFW Window to initialize.</param>
/// <returns>Bool of if the operation was successful or not.</returns>
bool UInitialize(int, char* [], GLFWwindow** window);

/// <summary>
/// You Resize the Window!
/// </summary>
/// <param name="window">Window to resize.</param>
/// <param name="width">New window width.</param>
/// <param name="height">New window height.</param>
void UResizeWindow(GLFWwindow* window, int width, int height);

/// <summary>
/// You Process Input (from key presses)!
/// </summary>
/// <param name="window">GLFW Window to process input.</param>
void UProcessInput();

/// <summary>
/// You Create a Mesh!
/// <para>Function to create the Vertex Buffer Object</para>
/// </summary>
/// <param name="mesh"></param>
void UCreateMesh(GLMesh& mesh);

/// <summary>
/// You Destroy a Mesh!
/// </summary>
/// <param name="mesh"></param>
void UDestroyMesh(GLMesh& mesh);

/// <summary>
/// You Render the current frame!
/// </summary>
void URenderFrame();

/// <summary>
/// Sets the times for the current frame.
/// </summary>
void USetFrameTiming();

/// <summary>
/// Callback to handle mouse movement events.
/// <para>Mostly borrowed from LearnOpenGL.com implementation of Camera class.</para>
/// </summary>
/// <param name="window">The window where the mouse position event occured.</param>
/// <param name="xPosition">The new X position of the mouse cursor.</param>
/// <param name="yPosition">The new Y position of the mouse cursor.</param>
void UMousePositionCallback(GLFWwindow* window, double xPosition, double yPosition);

/// <summary>
/// Callback to handle mouse scroll events.
/// </summary>
/// <param name="window">The window where the mouse scroll event occured.</param>
/// <param name="xOffset">Distance scrolled in the X direction.</param>
/// <param name="yOffset">Distance scrolled in the Y direction.</param>
void UMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

/// <summary>
/// Adds the vertices and indices for the ground plane to the vectors.
/// </summary>
/// <param name="vertices">Vector containing the vertices.</param>
/// <param name="indices">Vector containing the indices.</param>
void SetGroundPlane(vector<GLfloat>& verts, vector<GLushort>& indices);

int main(int argc, char* argv[])
{
    if (!UInitialize(argc, argv, &mainWindow))
        return EXIT_FAILURE;

    UCreateMesh(mesh);

    if (!Shader::UCreateShaderProgram(shaderProgramId))
        return EXIT_FAILURE;

    while (!glfwWindowShouldClose(mainWindow))
    {
        USetFrameTiming();

        UProcessInput();

        URenderFrame();

        glfwPollEvents();
    }

    UDestroyMesh(mesh);
    Shader::UDestroyShaderProgram(shaderProgramId);
    glDeleteTextures(1, &tilesTexture);
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

bool UInitialize(int, char* [], GLFWwindow** window)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);

    if (*window == nullptr)
    {
        cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(*window);
    glfwSetFramebufferSizeCallback(*window, UResizeWindow);
    glfwSetScrollCallback(*window, UMouseScrollCallback);
    glfwSetCursorPosCallback(*window, UMousePositionCallback);

    glewExperimental = GL_TRUE;
    GLenum glewInitResult = glewInit();
    if (glewInitResult != GLEW_OK)
    {
        cerr << glewGetErrorString(glewInitResult) << endl;
        return false;
    }
    cout << "INFO: GLEW Version: " << glewGetString(GLEW_VERSION) << endl;
    cout << "INFO: OpenGl Version: " << glGetString(GL_VERSION) << endl;

    glEnable(GL_DEPTH_TEST); // lets it figure out which shape should be in front

    return true;
}

void UResizeWindow(GLFWwindow*, int width, int height)
{
    glViewport(0, 0, width, height);
}

void USetFrameTiming()
{
    double currentFrame = glfwGetTime();
    gDeltaTime = currentFrame - gLastFrame;
    gLastFrame = currentFrame;
}

void UMousePositionCallback(GLFWwindow* window, double xPosition, double yPosition)
{
    if (gFirstMouse)
    {
        gLastX = xPosition;
        gLastY = yPosition;
        gFirstMouse = false;
    }

    static const float mouseSensitivity = 0.1f;
    float xOffset = (xPosition - gLastX) * mouseSensitivity;
    float yOffset = (gLastY - yPosition) * mouseSensitivity; // reversed (y-coordinates go from bottom to top)

    gLastX = xPosition;
    gLastY = yPosition;

    gYaw += xOffset;
    gPitch += yOffset;

    // Constrain pitch from flipping over
    if (gPitch > 89.0f)
        gPitch = 89.0f;
    if (gPitch < -89.0f)
        gPitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(gYaw)) * cos(glm::radians(gPitch));
    front.y = sin(glm::radians(gPitch));
    front.z = sin(glm::radians(gYaw)) * cos(glm::radians(gPitch));
    gCameraFront = glm::normalize(front);

    // also re-calculate the Right and Up vector
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    gCameraRight = glm::normalize(glm::cross(gCameraFront, gWorldUp));
    gCameraUp = glm::normalize(glm::cross(gCameraRight, gCameraFront));

}

void UMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    static const GLfloat maxSpeed = 10.0f;
    static const GLfloat minSpeed = 0.1f;
    static const GLfloat increment = 0.1f;

    GLfloat tempSpeed = speed + (GLfloat)(increment * yOffset);

    if (tempSpeed > maxSpeed)
    {
        speed = maxSpeed;
    }
    else if (tempSpeed < minSpeed)
    {
        speed = minSpeed;
    }
    else
    {
        speed = tempSpeed;
    }
}

void UProcessInput()
{
    if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(mainWindow, true);

    float cameraOffset = speed * (GLfloat)gDeltaTime;

    // Press W (forward)
    if (glfwGetKey(mainWindow, GLFW_KEY_W) == GLFW_PRESS)
        gCameraPos += gCameraFront * cameraOffset;
    // Press A (strafe left)
    if (glfwGetKey(mainWindow, GLFW_KEY_A) == GLFW_PRESS)
        gCameraPos -= gCameraRight * cameraOffset;
    // Press S (backward)
    if (glfwGetKey(mainWindow, GLFW_KEY_S) == GLFW_PRESS)
        gCameraPos -= gCameraFront * cameraOffset;
    // Press D (strafe right)
    if (glfwGetKey(mainWindow, GLFW_KEY_D) == GLFW_PRESS)
        gCameraPos += gCameraRight * cameraOffset;

    // Press Q (up)
    if (glfwGetKey(mainWindow, GLFW_KEY_Q) == GLFW_PRESS)
        gCameraPos += gCameraUp * cameraOffset;
    // Press E (down)
    if (glfwGetKey(mainWindow, GLFW_KEY_E) == GLFW_PRESS)
        gCameraPos -= gCameraUp * cameraOffset;

    // Press P (toggle between Orthographic and Perspective views
    if (glfwGetKey(mainWindow, GLFW_KEY_P) == GLFW_PRESS)
        isOrthographic = !isOrthographic;
}

void UCreateMesh(GLMesh& mesh)
{
    vector<GLfloat> verts;
    verts.clear();
    vector<GLushort> indices;
    indices.clear();
    SetGroundPlane(verts, indices);
    Starship::SetStarship(verts, indices);
    
    glGenVertexArrays(1, &mesh.vertexArrayObject);
    glBindVertexArray(mesh.vertexArrayObject);

    glGenBuffers(2, mesh.vertexBufferObjects);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vertexBufferObjects[0]);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), verts.data(), GL_STATIC_DRAW);

    mesh.vertexCount = indices.size();//sizeof(indices) / sizeof(indices[0]); // Memory of indices array divided by the memory of the first element

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vertexBufferObjects[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

    // Creates the Vertex Attribute Pointer
    const GLuint floatsPerVertex = 3; // Number of coordinates per vertex
    const GLuint floatsPerColor = 4; // R, G, B, A
    // Strides between vertex coordinates is 7 floats (x, y, r, g, b, a). A tightly packed stride is 0.
    GLint stride = sizeof(float) * (floatsPerVertex + floatsPerColor);// The number of floats before each

    // Creates the Vertex Attribute Pointer
    const int LOCATION_ATTRIBUTE = 0;
    glVertexAttribPointer(LOCATION_ATTRIBUTE, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(LOCATION_ATTRIBUTE);

    const int COLOR_ATTRIBUTE = 1;
    glVertexAttribPointer(COLOR_ATTRIBUTE, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
    glEnableVertexAttribArray(COLOR_ATTRIBUTE);
}

void UDestroyMesh(GLMesh& mesh)
{
    glDeleteVertexArrays(1, &mesh.vertexArrayObject);
    glDeleteBuffers(2, mesh.vertexBufferObjects);
}

void URenderFrame()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.65f, 0.70f, 0.74f, 1.0f); // set background color to a grayish sky
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 1. Scales the object by 2
    glm::mat4 scale = glm::scale(glm::vec3(0.1f, 0.1f, 0.1f));
    // 2. Rotates shape by ?? degrees in the ? axis
    glm::mat4 rotation = glm::rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f)); // Vertical
    // 3. Place object at the origin
    glm::mat4 translation = glm::translate(glm::vec3(0.0f, -8.7f, -5.0f));
    // Model matrix: transformations are applied right-to-left order
    glm::mat4 model = translation * rotation * scale;

    // Make it spiiiiinn!!!
    //double currentTime = glfwGetTime();
    //if (currentTime - previousTime >= 1 / 60)
    //{
    //    rotation += 0.5f;
    //    previousTime = currentTime;
    //}
    //model = glm::rotate(model, glm::radians(rotationDegrees), glm::vec3(0.0f, 1.0f, 0.0f));

    // Transforms the camera: move the camera
    glm::mat4 view = glm::lookAt(gCameraPos, gCameraPos + gCameraFront, gCameraUp);
    //glm::mat4 view = glm::translate(glm::vec3(0.0f, 0.0f, -50.0f));

    // Creates a projection
    glm::mat4 projection;
    if (isOrthographic)
    {
        projection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 1.0f, 100.0f); // orthographic
    }
    else
    {
        projection = glm::perspective(glm::radians(45.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.0f); // perspective
    }

    glUseProgram(shaderProgramId);

    // Sends transform information to the Vertex shader
    // Retrieves and passes transform matrices to the Shader program
    GLint modelLoc = glGetUniformLocation(shaderProgramId, "model");
    GLint viewLoc = glGetUniformLocation(shaderProgramId, "view");
    GLint projLoc = glGetUniformLocation(shaderProgramId, "projection");
        
    


    // Texture
    //int imgWidth, imgHeight, imgColorChannels;
    //stbi_set_flip_vertically_on_load(true);
    //unsigned char* bytes = stbi_load("tiles.png", &imgWidth, &imgHeight, &imgColorChannels, 0);
    //glGenTextures(1, &tilesTexture);
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, tilesTexture);
    //
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    //
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
    //glGenerateMipmap(GL_TEXTURE_2D);

    //stbi_image_free(bytes); // free up memory
    //glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture to prevent changes

    //GLint textureLoc = glGetUniformLocation(shaderProgramId, "tex0");
    //glUniform1i(textureLoc, 0);



    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(mesh.vertexArrayObject);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframes for testing
    glDrawElements(GL_TRIANGLES, mesh.vertexCount, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
 
    glfwSwapBuffers(mainWindow);
}

void SetGroundPlane(vector<GLfloat>& verts, vector<GLushort>& indices)
{
    auto sand = glm::vec3(0.91f, 0.72f, 0.30f);  // looks like sand for now.
    GLushort currentIndex = 0;
    VertexService::AddCoordinate(verts, -50.0f, -5.0f, -50.0f); // south west corner
    VertexService::AddColor(verts, sand);
    VertexService::AddCoordinate(verts, -50.0f, -5.0f,  50.0f); // north west corner
    VertexService::AddColor(verts, sand);
    VertexService::AddCoordinate(verts,  50.0f, -5.0f,  50.0f); // north east corner
    VertexService::AddColor(verts, sand);
    VertexService::AddCoordinate(verts,  50.0f, -5.0f, -50.0f); // south east corner
    VertexService::AddColor(verts, sand);

    indices.push_back(currentIndex);
    indices.push_back(currentIndex + 1);
    indices.push_back(currentIndex + 2);
    indices.push_back(currentIndex);
    indices.push_back(currentIndex + 2);
    indices.push_back(currentIndex + 3);
}
