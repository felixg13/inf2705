
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "window.h"
#include "shader_program.h"
#include "vertices_data.h"
#include "shapes.h"


void printGLInfo();

#define GL_CHECK_ERROR checkGLError(__FILE__, __LINE__)
void checkGLError(const char* file, int line);

void changeRGB(GLfloat* color);
void changePos(GLfloat* pos, float& cx, float& cy, float& dx, float& dy);

std::string readFile(const char* path);

int main(int argc, char* argv[])
{
    Window w;
    if (!w.init())
        return -1;
    
    GLenum rev = glewInit();
    if ( rev != GLEW_OK )
    {
        std::cout << "Could not initialize glew! GLEW_Error: " << glewGetErrorString(rev) << std::endl;
        return -2;
    }
    
    printGLInfo();
    
    // DONE Partie 1: Instancier les shader programs ici.
    ShaderProgram basic;
    { // Les accolades vont permettre de détruire le code des shaders plus rapidement
        // Vous devez lire le code des shaders dans "shaders/"
        // avec la fonction "readFile".
		std::string vertexShaderSource = readFile("shaders/basic.vs.glsl");
        std::string fragmentShaderSource = readFile("shaders/basic.fs.glsl");

        // Vous pouvez par la suite instancier vos shaders, les attacher et les lier
        // au programme.
        Shader vertexShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
        Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

        basic.attachShader(vertexShader);
        basic.attachShader(fragmentShader);
        basic.link();
    }
    
    ShaderProgram color;
    {
        std::string vertexShaderSource = readFile("shaders/color.vs.glsl");
        std::string fragmentShaderSource = readFile("shaders/color.fs.glsl");
        // Vous pouvez par la suite instancier vos shaders, les attacher et les lier
        // au programme.
        Shader vertexShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
        Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());
        color.attachShader(vertexShader);
        color.attachShader(fragmentShader);
        color.link();
    }
    
    // DONE Partie 2: Shader program de transformation.
    ShaderProgram transform;
    {
        std::string vertexShaderSource = readFile("shaders/transform.vs.glsl");
        Shader vertexShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());

        std::string fragmentShaderSource = readFile("shaders/transform.fs.glsl");
        Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

        transform.attachShader(vertexShader);
        transform.attachShader(fragmentShader);
        transform.link();
    }
    
    // Variables pour la mise à jour, ne pas modifier.
    float cx = 0, cy = 0;
    float dx = 0.019;
    float dy = 0.0128;
    
    float angleDeg = 0.0f;
    
    // Tableau non constant de la couleur
    GLfloat onlyColorTriVertices[] = {
        // DONE Partie 1: Rempliser adéquatement le tableau.
        // Vous pouvez expérimenter avec une couleur uniforme
        // de votre choix ou plusieurs différentes en chaque points.
        1.0F, 0.0F, 0.0F,
        0.0F, 1.0F, 0.0F,
        0.0F, 0.0F, 1.0F,
    };
    
    // DONE Partie 1: Instancier vos formes ici.
    // BasicShapeArrays triangleSimple(triVertices, sizeof(triVertices));
    // triangleSimple.enableAttribute(0, 3, 0, 0);

    // BasicShapeArrays squareSimple(squareVertices, sizeof(squareVertices));
    // squareSimple.enableAttribute(0, 3, 0, 0);

    // BasicShapeArrays triangleColored(colorTriVertices, sizeof(colorTriVertices));
    // triangleColored.enableAttribute(0, 3, sizeof(GLfloat)*6, 0);
    // triangleColored.enableAttribute(1, 3, sizeof(GLfloat)*6, sizeof(GLfloat)*3);

    // BasicShapeArrays squareColored(colorSquareVertices, sizeof(colorSquareVertices));
    // squareColored.enableAttribute(0, 3, sizeof(GLfloat)*6, 0);
    // squareColored.enableAttribute(1, 3, sizeof(GLfloat)*6, sizeof(GLfloat)*3);

    // BasicShapeMultipleArrays triangleMultiple(triVertices, sizeof(triVertices), onlyColorTriVertices, sizeof(onlyColorTriVertices));
    // triangleMultiple.enablePosAttribute(0, 3, 0, 0);
    // triangleMultiple.enableColorAttribute(1, 3, 0, 0);


    BasicShapeElements squareElement(colorSquareVerticesReduced, sizeof(colorSquareVerticesReduced), indexes, sizeof(indexes));
    squareElement.enableAttribute(0, 3, sizeof(GLfloat)*6, 0);
    squareElement.enableAttribute(1, 3, sizeof(GLfloat)*6, sizeof(GLfloat)*3);

    // // DONE Partie 2: Instancier le cube ici.
    // BasicShapeElements cube(cubeVertices, sizeof(cubeVertices), cubeIndexes, sizeof(cubeIndexes));
    // cube.enableAttribute(0, 3, sizeof(GLfloat)*6, 0);
    // cube.enableAttribute(1, 3, sizeof(GLfloat)*6, sizeof(GLfloat)*3);

    
    // DONE Partie 1: Donner une couleur de remplissage aux fonds.
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    // DONE Partie 2: Activer le depth test.
    glEnable(GL_DEPTH_TEST);
    
    
    int selectShape = 0;
    bool isRunning = true;
    while (isRunning)
    {
        if (w.shouldResize())
            glViewport(0, 0, w.getWidth(), w.getHeight());
        
        // DONE Partie 1: Nettoyer les tampons appropriées.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if (w.getKey(Window::Key::T))
        {
            selectShape = ++selectShape < 7 ? selectShape : 0;
            std::cout << "Selected shape: " << selectShape << std::endl;
        }
        
        // DONE Partie 1: Mise à jour des données du triangle
        // changeRGB(&onlyColorTriVertices[0]);
        // changeRGB(&onlyColorTriVertices[3]);
        // changeRGB(&onlyColorTriVertices[6]);
        // triangleMultiple.updateColorData(onlyColorTriVertices, sizeof(onlyColorTriVertices));
        // GLfloat* posPtr = triangleMultiple.mapPosData();
        // changePos(posPtr, cx, cy, dx, dy);
        // triangleMultiple.unmapPosData();

        // DONE Partie 1: Utiliser le bon shader programme selon la forme.
        // N'hésiter pas à utiliser le fallthrough du switch case.
        switch (selectShape)
        {
            case 0:
                basic.use();
                break;
            case 1: 
                basic.use();
                break;
            case 2:
                color.use();
                break;
            case 3:
                color.use();
                break;
            case 4: 
                color.use();
                break;
            case 5: 
                color.use();
                break;
            case 6:
                transform.use();
                break;
        }
        
        // TODO Partie 2: Calcul des matrices et envoyer une matrice résultante mvp au shader.
        if (selectShape == 6)
        {
            angleDeg += 0.5f;
            // Utiliser glm pour les calculs de matrices.
            // glm::mat4 matrix;
        }
        
        // DONE Partie 1: Dessiner la forme sélectionnée.
        switch (selectShape)
        {
            case 0:
                //triangleSimple.draw(GL_TRIANGLES, 3);
                break;
            case 1: 
                //squareSimple.draw(GL_TRIANGLES, 6);
                break;
            case 2:
                //triangleColored.draw(GL_TRIANGLES, 3);
                break;
            case 3:
                squareColored.draw(GL_TRIANGLES, 6);
                break;
            case 4: 
                //triangleMultiple.draw(GL_TRIANGLES, 3);
                break;
            case 5: 
                squareElement.draw(GL_TRIANGLES, 6);
                break;
            case 6:
                //cube.draw(GL_TRIANGLES, 36);
                break;
        }
        
        w.swap();
        w.pollEvent();
        isRunning = !w.shouldClose() && !w.getKey(Window::Key::ESC);
    }

    return 0;
}



void checkGLError(const char* file, int line)
{
    GLenum error;
    while ( ( error = glGetError() ) != GL_NO_ERROR )
    {
        std::cerr << "GL_ERROR, File " << file << " (Line " << line << "): ";
        switch ( error )
        {
        case GL_INVALID_ENUM:
            std::cerr << "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            std::cerr << "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            std::cerr << "GL_INVALID_OPERATION";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            std::cerr << "GL_OUT_OF_MEMORY";
            break;
        case GL_STACK_UNDERFLOW:
            std::cerr << "GL_STACK_UNDERFLOW";
            break;
        case GL_STACK_OVERFLOW:
            std::cerr << "GL_STACK_OVERFLOW";
            break;
        default:
            std::cerr << "Unknown gl error occured!";
            break;
        }
        std::cerr << std::endl;
    }    
}

void printGLInfo()
{
    std::cout << "OpenGL info:" << std::endl;
    std::cout << "    Vendor: "   << glGetString(GL_VENDOR)   << std::endl;
    std::cout << "    Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "    Version: "  << glGetString(GL_VERSION)  << std::endl;
    std::cout << "    Shading version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}


void changeRGB(GLfloat* color)
{
    unsigned char r = color[0]*255;
    unsigned char g = color[1]*255;
    unsigned char b = color[2]*255;
    
    if(r > 0 && b == 0)
    {
        r--;
        g++;
    }
    if(g > 0 && r == 0)
    {
        g--;
        b++;
    }
    if(b > 0 && g == 0)
    {
        r++;
        b--;
    }
    color[0] = r/255.0f;
    color[1] = g/255.0f;
    color[2] = b/255.0f;
}

void changePos(GLfloat* pos, float& cx, float& cy, float& dx, float& dy)
{
    if ((cx < -1 && dx < 0) || (cx > 1 && dx > 0))
        dx = -dx;
    pos[0] += dx;
    pos[3] += dx;
    pos[6] += dx;
    cx += dx;
    if ((cy < -1 && dy < 0) || (cy > 1 && dy > 0))
        dy = -dy;
    pos[1] += dy;
    pos[4] += dy;
    pos[7] += dy;
    cy += dy;
}


std::string readFile(const char* path)
{
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
