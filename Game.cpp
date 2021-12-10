#include "Game.h"

//Private Functions

void Game::initGLFW(){
    //INIT GLFW
    if (glfwInit()==GLFW_FALSE){
        std::cout<<"ERROR::GLFW_INIT_FAILED"<<std::endl;
        glfwTerminate();
    }
}

void Game::initWindow(
    const char* title,
    bool resizable
){
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
    glfwWindowHint(GLFW_RESIZABLE, resizable);

    this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);

    if (this->window==nullptr){
        std::cout<<"ERROR::GLFW_WINDOW_INIT_FAILED"<<std::endl;
        glfwTerminate();
    }

    glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
    glfwSetFramebufferSizeCallback(this->window, Game::framebuffer_resize_callback);

    glfwMakeContextCurrent(this->window); //IMPORTANT FOR GLEW
}

void Game::initGLEW(){
    //INIT GLEW (NEEDS WINDOW AND OPENGL CONTEXT)
    glewExperimental = GL_TRUE;

    //Error Test
    if (glewInit()!=GLEW_OK){
        std::cout<<"ERROR::GLEW_INIT_FAILED"<<std::endl;
        glfwTerminate();
    }
}

void Game::initOpenGLOptions(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); //NO DRAW BACK
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND); //blends colors
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //OR GL_LINE FOR OUTLINE
}

void Game::initMatrices(){
    this->ViewMatrix = glm::mat4(1.0f);
    ViewMatrix = glm::lookAt(this->camPosition, this->camPosition+this->camFront, this->worldUp);

    this->ProjectionMatrix = glm::mat4(1.0f);
    this->ProjectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->framebufferWidth)/this->framebufferHeight, this->nearPlane, this->farPlane);

}

void Game::initShaders(){
    this->shaders.push_back(new Shader(
        this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
        (char*)("src/vertex_core.glsl"), (char*)("src/fragment_core.glsl"))
    );
}

void Game::initTextures(){
    //TEXTURE0
    this->textures.push_back(new Texture("src/worm.png", GL_TEXTURE_2D));

    //TEXTURE1
    this->textures.push_back(new Texture("src/stone.png", GL_TEXTURE_2D));
}

void Game::initMaterials(){
    this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), TEX_WORM0, TEX_STONE1));
}

void Game::initMeshes(){
    Quad tempQuad;
    this->meshes.push_back(
        new Mesh(
            &tempQuad,
            glm::vec3(0.0f),
            glm::vec3(0.0f),
            glm::vec3(1.0f)
    ));
}

void Game::initLights(){
    this->lights.push_back(new glm::vec3(0.0f, 0.0f, 1.0f));
}

void Game::initUniforms(){
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");

    this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
    this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camPosition, "cameraPos");
}

void Game::updateUniforms(){
    this->materials[MAT_1]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);

    //Update Frame Buffer Size and projection matrix
    glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

    this->ProjectionMatrix = glm::perspective(
        glm::radians(this->fov),
        static_cast<float>(this->framebufferWidth)/this->framebufferHeight,
        this->nearPlane,
        this->farPlane
    );

    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix");
}

//Constructors / Destructors
Game::Game(
    const char* title,
    const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
    const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
    bool resizable
)
    : WINDOW_WIDTH(WINDOW_WIDTH), WINDOW_HEIGHT(WINDOW_HEIGHT),
    GL_VERSION_MAJOR(GL_VERSION_MAJOR), GL_VERSION_MINOR(GL_VERSION_MINOR)
{
    //Init Variables
    this->window = nullptr;
    this->framebufferWidth = this->WINDOW_WIDTH;
    this->framebufferHeight = this->WINDOW_HEIGHT;

    this->camPosition = glm::vec3(0.0f, 0.0f, 1.0f);
    this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->camFront = glm::vec3(0.0f, 0.0f, -1.0f);

    this->fov = 90.0f;
    this->nearPlane = 0.1f;
    this->farPlane = 1000.0f;

    this->initGLFW();
	this->initWindow(title, resizable);
    this->initGLEW();
    this->initOpenGLOptions();
    this->initMatrices();
    this->initShaders();
    this->initTextures();
    this->initMaterials();
    this->initMeshes();
    this->initLights();
    this->initUniforms();

    glfwSwapInterval(1);
}

Game::~Game(){
    glfwDestroyWindow(this->window);
    glfwTerminate();

    for (size_t i = 0; i<this->shaders.size(); i++)
        delete this->shaders[i];
    for (size_t i = 0; i<this->textures.size(); i++)
        delete this->textures[i];
    for (size_t i = 0; i<this->materials.size(); i++)
        delete this->materials[i];
    for (size_t i = 0; i<this->meshes.size(); i++)
        delete this->meshes[i];
    for (size_t i = 0; i<this->lights.size(); i++)
        delete this->lights[i];
}

//Accessors
int Game::getWindowShouldClose(){
    return glfwWindowShouldClose(this->window);
}

//Modifiers
void Game::setWindowShouldClose(){
    glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

//Functions
void Game::update(){
    //Update input
    glfwPollEvents();
    updateInput(this->window, *this->meshes[MESH_QUAD]);
}

void Game::render(){

    //updateInput(this->window);

    //DRAW
    //Clear
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

    //Update uniforms
    this->updateUniforms();

    //Use a program
    this->shaders[SHADER_CORE_PROGRAM]->use();

    //Activate Textures
    this->textures[TEX_WORM0]->bind(0);
    this->textures[TEX_STONE1]->bind(1);

    //Draw
    this->meshes[MESH_QUAD]->render(this->shaders[SHADER_CORE_PROGRAM]);

    //End draw
    glfwSwapBuffers(this->window);
    glFlush();

    //Reset
    glBindVertexArray(0);
    glUseProgram(0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

//Static Functions
void Game::framebuffer_resize_callback(GLFWwindow* window, int fbw, int fbh){
    glViewport(0, 0, fbw, fbh);
}

void Game::updateInput(GLFWwindow* window, Mesh& mesh){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS)
        mesh.move(glm::vec3(0, 0.01f, 0));
    if (glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS)
        mesh.move(glm::vec3(-.01f, 0, 0));
    if (glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS)
        mesh.move(glm::vec3(0, -0.01f, 0));
    if (glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS)
        mesh.move(glm::vec3(.01f, 0, 0));
    if (glfwGetKey(window, GLFW_KEY_U)==GLFW_PRESS)
        mesh.move(glm::vec3(0, 0, -.01f));
    if (glfwGetKey(window, GLFW_KEY_I)==GLFW_PRESS)
        mesh.move(glm::vec3(0, 0, .01f));
    if (glfwGetKey(window, GLFW_KEY_Q)==GLFW_PRESS)
        mesh.rotate(glm::vec3(0, -1.0f, 0));
    if (glfwGetKey(window, GLFW_KEY_E)==GLFW_PRESS)
        mesh.rotate(glm::vec3(0, 1.0f, 0));
    if (glfwGetKey(window, GLFW_KEY_Z)==GLFW_PRESS)
        mesh.scaleScale(glm::vec3(.1f));
    if (glfwGetKey(window, GLFW_KEY_X)==GLFW_PRESS)
        mesh.scaleScale(glm::vec3(-.1f));
}