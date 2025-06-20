#include "Road.h"
#include "tigl.h"
#include "stb_image.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using tigl::Vertex;
using namespace tigl;

Road::Road(const glm::vec3& position, const glm::vec2& size)
    : position(position), size(size) {
    texture = loadTexture("Resource Files/Road/road.jpg");
    if (texture == 0) {
        std::cerr << "Failed to load road texture!" << std::endl;
    }
    else {
        std::cout << "Road texture loaded successfully!" << std::endl;
    }
}

void Road::update(float) {
}

GLuint Road::loadTexture(const char* filepath) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); 
    unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format = GL_RGB;
        if (nrChannels == 4)
            format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cerr << "Failed to load texture: " << filepath << std::endl;
    }
    stbi_image_free(data);

    return textureID;
}

void Road::draw() {
    shader->setModelMatrix(glm::translate(glm::mat4(1.0f), position));
    shader->enableTexture(true);
    glBindTexture(GL_TEXTURE_2D, texture);

    float repeatX = size.y / 10.0f; 
    float repeatY = size.x / 10.0f; 
    begin(GL_QUADS);
    addVertex(Vertex::PT(glm::vec3(-size.x / 2, 0, -size.y / 2), glm::vec2(0.0f, 0.0f)));
    addVertex(Vertex::PT(glm::vec3(size.x / 2, 0, -size.y / 2), glm::vec2(0.0f, repeatY)));
    addVertex(Vertex::PT(glm::vec3(size.x / 2, 0, size.y / 2), glm::vec2(repeatX, repeatY)));
    addVertex(Vertex::PT(glm::vec3(-size.x / 2, 0, size.y / 2), glm::vec2(repeatX, 0.0f)));
    end();

    shader->enableTexture(false);
}

