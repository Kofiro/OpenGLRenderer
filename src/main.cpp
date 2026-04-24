/**
 * 
 * clear bin folder contents to remove old openglrenderer.exe
 * run mingw32-make clean
 * then after that run mingw32-make to run the makefile and build the exe again
 * then finally run the exe with ./openglrenderer.exe
 */
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "shader.h"
#include "camera.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


const unsigned int WIDTH = 800;
const unsigned int HEIGHT { 600 };

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f; // time of last frame
// camera offsetsince last frame
float lastX = WIDTH/2.0f, lastY = HEIGHT/2.0f; // initialize to place mouse at center of screen (800, 600) screen size
bool firstMouse = true;



int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Opengl Renderer", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << '\n';
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // hide cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);   // moue movement input (tell glfw to listen to events)
    // scroll
    glfwSetScrollCallback(window, scroll_callback);


    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << '\n';
        return -1;
    }

    //glViewport(0,0,WIDTH,HEIGHT);

    Shader ourShader("shaders/vert.vs", "shaders/frag.fs");
    
    
    

    // vertex input
    float vertices[] = {
       // first triangle
       // positions         // colors                   // texture coords
    //    0.5f, 0.5f, 0.0f,    /*0.0f, 0.0f, 1.0f,*/           1.0f, 1.0f,     // top right 
    //    0.5f, -0.5f, 0.0f,   /*0.0f, 1.0f, 0.0f,*/           1.0f, 0.0f,     // bottom right
    //    -0.5f, -0.5f, 0.0f,  /*1.0f, 0.0f, 0.0f,*/           0.0f, 0.0f,     // bottom left
    //    -0.5f, 0.5f, 0.0f,   /*1.0f, 1.0f, 0.0f,*/           0.0f, 1.0f      // top left

       // 3 -- 0
       // 2 -- 1
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
        
    };


    
    

    unsigned int VBO;
    glGenBuffers(1, &VBO); // generates 1 buffer object and stores it's reference ID in VBO (the buffer object is instantiated behind the scenes)
   
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
  
    // // EBO
    // unsigned int EBO;
    // glGenBuffers(1, &EBO);

   
    // bind vertex array object
    glBindVertexArray(VAO);
    // bind buffer object to buffer type target
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // any calls to the buffer type target will be used to configure the currently bound buffer in our case VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   
    // EBO Binding
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //next we specify how Opengl should interpret the vertex buffer data (i.e, vertex input data currently in memory)
    // the 0 index here in the first param is 0 because we set the layout (location = 0) in the vertex shader for the position location
    // a vec3 hence the 3 for the second param (size of the vertex attribute)
    // 3rd attrib param specifies the type (vec3 are made of floats)
    // 4th param is if we want the data to be normalized (no in this case)
    // 5th param is stride (space between consecutive vertex attributes, since we know the array is tightly packed, we could've used 0 which auto determine's stride from opengl)
    // 6th param is an offset of where the position data begins in the buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);   // this enables the vertex attribute at index we set at the layout (location = ?) to be active

    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture
    // texture object
    unsigned int texture, texture2;
    glGenTextures(1, &texture);
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture);


    // set texture wrapping and filtering options on currently bound texture object
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("textures/container.jpg", &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


    // second texture
    glBindTexture(GL_TEXTURE_2D, texture2);

    // set texture wrapping params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // reset texture image data
   
    stbi_set_flip_vertically_on_load(true);
    
    data = stbi_load("textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    
    stbi_image_free(data);
    
    ourShader.use();
    ourShader.setInt("texture1", 0);
    //glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
    ourShader.setInt("texture2", 1);

    glEnable(GL_DEPTH_TEST);

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.0f, -2.2f, -2.5f), 
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(-2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f),
        glm::vec3(3.0f, 4.0f, 4.5f),
        glm::vec3(5.0f, -5.0f, 10.0f),
        glm::vec3(-4.0f, -0.7f, 3.9f),
        glm::vec3(2.5f, -1.3f, 6.5f),
        glm::vec3(-6.0f, 1.5f, 3.0f)
       
    };

    // render loop
    while(!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
         // input
        processInput(window);



        glClearColor(0.2f, 0.3f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // rendering commands here
        //glUseProgram(shaderProgram);
        ourShader.use();
        

        // view matrix
        glm::mat4 view = glm::mat4(1.0f);
        // translate scene in reverse direction of where we want to move
        //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        //view = glm::lookAt(cameraPos, cameraPos + cameraFront, worldUp);
        view = camera.GetViewMatrix();

        // projection matrix
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH/(float) HEIGHT, 0.1f, 100.0f);
        
       // ourShader.setMatrix4("model", model);
        ourShader.setMatrix4("view", view);
        ourShader.setMatrix4("projection", projection);

        // ourShader.setMatrix4("transform", trans);
        
        glBindVertexArray(VAO);
        for(unsigned int i = 0; i < 15; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMatrix4("model", model);
            glDrawArrays(GL_TRIANGLES,0, 36);
        }
       
        //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        // check and call event
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // de-allocate resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}



void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;   // reversed since y coords range from bottom to top
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    camera.ProcessMoueScroll(static_cast<float>(yoffset));
    
}
