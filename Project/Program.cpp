//===============================================================
// Author:  Mark Holden
// Course:  CS-330 Computer Graphics
// Date:    5/22/2022
// 
//===============================================================
#pragma once
#include <iostream>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM Math Header inclusions
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "GLMesh.h"
#include "Shader.h"
#include "Starship.h"
#include "Mechazilla.h"
#include "VertexService.h"
#include <vector>

using namespace std;

const char* const WINDOW_TITLE = "SpaceX Starship";
const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 1200;

GLFWwindow* mainWindow = nullptr;

GLMesh groundMesh;
GLMesh boosterSmoothSectionMesh;
GLMesh boosterReinforcedSectionMesh;
GLMesh starshipTiledSectionMesh;
GLMesh starshipSteelSectionMesh;
GLMesh boosterGridfinMesh;
GLMesh towerMesh;

GLuint shaderProgramId;
GLuint tilesTexture;
GLuint imageryTexture;
GLuint steelTexture;
GLuint reinforcementTexture;

glm::vec3 gObjectColor(1.f, 0.2f, 0.0f);
glm::vec3 gLightColor(1.0f, 1.0f, 1.0f);
glm::vec3 gLightPosition(-20.0f, 15.0f, 20.0f);

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
void SetGroundPlane();

/// <summary>
/// Loads all textures into global variables.
/// </summary>
/// <returns>Success.</returns>
bool LoadTextures();

/// <summary>
/// Creates a texture.
/// </summary>
/// <param name="filename">File from which to load texture.</param>
/// <param name="textureId">Id to assign the texture.</param>
/// <returns>Success.</returns>
bool UCreateTexture(const char* filename, GLuint& textureId);

int main(int argc, char* argv[])
{
    if (!UInitialize(argc, argv, &mainWindow))
        return EXIT_FAILURE;


    if (!Shader::UCreateShaderProgram(shaderProgramId))
        return EXIT_FAILURE;

    if (!LoadTextures())
        return EXIT_FAILURE;
    
    SetGroundPlane();

    starshipTiledSectionMesh.textureId = tilesTexture;
    Starship::SetStarshipTiledSection(starshipTiledSectionMesh);

    starshipSteelSectionMesh.textureId = steelTexture;
    Starship::SetStarshipSteelSection(starshipSteelSectionMesh);

    boosterSmoothSectionMesh.textureId = steelTexture;
    Starship::SetBoosterSmoothSection(boosterSmoothSectionMesh);

    boosterReinforcedSectionMesh.textureId = reinforcementTexture;
    Starship::SetBoosterReinforcedSection(boosterReinforcedSectionMesh);

    // TODO: actual gridfin texture
    boosterGridfinMesh.textureId = reinforcementTexture;
    //Starship::SetBoosterGridfins(boosterGridfinMesh);

    towerMesh.textureId = steelTexture;
    Mechazilla::SetTower(towerMesh);

    while (!glfwWindowShouldClose(mainWindow))
    {
        USetFrameTiming();

        UProcessInput();

        URenderFrame();

        glfwPollEvents();
    }

    groundMesh.UDestroyMesh();
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

    static const float mouseSensitivity = 0.5f;
    float xOffset = (xPosition - gLastX) * mouseSensitivity;
    float yOffset = (gLastY - yPosition) * mouseSensitivity; // reversed (y-coordinates go from bottom to top)

    gLastX = xPosition;
    gLastY = yPosition;

    gYaw += xOffset;
    gPitch += yOffset;

    // Constrain pitch from flipping over
    //if (gPitch > 89.0f)
    //    gPitch = 89.0f;
    //if (gPitch < -89.0f)
    //    gPitch = -89.0f;

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

bool LoadTextures()
{
    const char* texFilename = "./tiles.png";
    if (!UCreateTexture(texFilename, tilesTexture))
    {
        cout << "Failed to load texture " << texFilename << endl;
        return false;
    }

    texFilename = "./imagery.png";
    if (!UCreateTexture(texFilename, imageryTexture))
    {
        cout << "Failed to load texture " << texFilename << endl;
        return false;
    }

    texFilename = "./steel.png";
    if (!UCreateTexture(texFilename, steelTexture))
    {
        cout << "Failed to load texture " << texFilename << endl;
        return false;
    }

    texFilename = "./booster_reinforcements.png";
    if (!UCreateTexture(texFilename, reinforcementTexture))
    {
        cout << "Failed to load texture " << texFilename << endl;
        return false;
    }

    glUseProgram(shaderProgramId); // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUniform1i(glGetUniformLocation(shaderProgramId, "uTextureTiles"), 1);
    glUniform1i(glGetUniformLocation(shaderProgramId, "uTextureImagery"), 2);
    glUniform1i(glGetUniformLocation(shaderProgramId, "uTextureSteel"), 3);
    glUniform1i(glGetUniformLocation(shaderProgramId, "uTextureReinforcement"), 4);
}

bool UCreateTexture(const char* filename, GLuint& textureId)
{
    int width;
    int height;
    int channels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);
    if (image)
    {
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (channels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        else if (channels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        else
        {
            cout << "Not implemented to handle image with " << channels << " channels" << endl;
            return false;
        }

        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(image);
        glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture

        return true;
    }

    // Error loading the image
    return false;
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

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Reference matrix uniforms from the Object Shader program for the Object color, light color, light position, and camera position
    GLint objectColorLoc = glGetUniformLocation(shaderProgramId, "objectColor");
    GLint lightColorLoc = glGetUniformLocation(shaderProgramId, "lightColor");
    GLint lightPositionLoc = glGetUniformLocation(shaderProgramId, "lightPos");
    GLint viewPositionLoc = glGetUniformLocation(shaderProgramId, "viewPosition");

    // Pass color, light, and camera data to the Object Shader program's corresponding uniforms
    glUniform3f(objectColorLoc, gObjectColor.r, gObjectColor.g, gObjectColor.b);
    glUniform3f(lightColorLoc, gLightColor.r, gLightColor.g, gLightColor.b);
    glUniform3f(lightPositionLoc, gLightPosition.x, gLightPosition.y, gLightPosition.z);
    const glm::vec3 cameraPosition = gCameraPos;
    glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);

    GLint UVScaleLoc = glGetUniformLocation(shaderProgramId, "uvScale");
    glUniform2fv(UVScaleLoc, 1, glm::value_ptr(glm::vec2(1.0f, 1.0f)));

    groundMesh.Draw();
    starshipTiledSectionMesh.Draw();
    boosterSmoothSectionMesh.Draw();
    starshipSteelSectionMesh.Draw();
    boosterReinforcedSectionMesh.Draw();
    towerMesh.Draw();
 
    glfwSwapBuffers(mainWindow);
}

void SetGroundPlane()
{
    vector<GLfloat> vertices;
    vertices.clear();
    vector<GLushort> indices;
    indices.clear();
    groundMesh.textureId = imageryTexture;
    
    glm::vec3 southWest = glm::vec3(-50.0f, -5.0f, -50.0f);
    glm::vec2 swTexture = glm::vec2(0.0f, 0.0f);

    glm::vec3 northWest = glm::vec3(-50.0f, -5.0f, 50.0f);
    glm::vec2 nwTexture = glm::vec2(0.0f, 1.0f);
    
    glm::vec3 northEast = glm::vec3(50.0f, -5.0f, 50.0f);
    glm::vec2 neTexture = glm::vec2(1.0f, 1.0f);
    
    glm::vec3 southEast = glm::vec3(50.0f, -5.0f, -50.0f);
    glm::vec2 seTexture = glm::vec2(1.0f, 0.0f);

    VertexService::AddFace(vertices, indices, southWest, swTexture, northWest, nwTexture, northEast, neTexture);
    VertexService::AddFace(vertices, indices, southWest, swTexture, northEast, neTexture, southEast, seTexture);

    groundMesh.UCreateMesh(vertices, indices);
}
