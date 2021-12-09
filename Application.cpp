#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SOIL2.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

struct Vertex{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texcoord;
};

//Error Handling Macro
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError(){
    while (glGetError()!=GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line){
    while (GLenum error = glGetError()){
        std::cout<<"[OpenGL Error] {"<<error<<"}: "<<function<<" "<<file<<":"<<line<<std::endl;
        return false;
    }
    return true;
}

Vertex vertices[] = {
    //Position                     //Color                      //Texcoords
    glm::vec3(-0.5f, 0.5f, 0.0f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f),
    glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f),
    glm::vec3(0.5f, -0.5f, 0.0f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f),

    glm::vec3(0.5f, 0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f),
};
unsigned int nrOfVertices = sizeof(vertices)/sizeof(Vertex);

GLuint indices[] = {
    0, 1, 2,
    0, 2, 3
};
unsigned int nrOfIndices = sizeof(indices)/sizeof(GLuint);

void framebuffer_resize_callback(GLFWwindow* window, int fbw, int fbh){
    GLCall(glViewport(0, 0, fbw, fbh));
}

bool loadShaders(GLuint& program){
    bool loadSuccess = true;

    char infoLog[512];
    GLint success;

    std::string temp = "";
    std::string src = "";
    std::ifstream in_file;

    //Vertex
    in_file.open("src/vertex_core.glsl");

    if (in_file.is_open())
        while (std::getline(in_file, temp))
            src += temp+"\n";
    else{
        std::cout<<"ERROR:LOADSHADERS::COULD_NOT_OPEN_VERTEX_FILE"<<std::endl;
        loadSuccess = false;
    }
    in_file.close();

    GLCall(GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER));
    const GLchar* vertSrc = src.c_str();
    GLCall(glShaderSource(vertexShader, 1, &vertSrc, NULL));
    GLCall(glCompileShader(vertexShader));

    GLCall(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success));
    if (!success){
        GLCall(glGetShaderInfoLog(vertexShader, 512, NULL, infoLog));
        std::cout<<"ERROR:LOADSHADERS::COULD_NOT_COMPILE_VERTEX_SHADER"<<std::endl;
        std::cout<<infoLog<<std::endl;
        loadSuccess = false;
    }

    temp = "";
    src = "";

    //Fragment
    in_file.open("src/fragment_core.glsl");

    if (in_file.is_open())
        while (std::getline(in_file, temp))
            src += temp+"\n";
    else{
        std::cout<<"ERROR:LOADSHADERS::COULD_NOT_OPEN_FRAGMENT_FILE"<<std::endl;
        loadSuccess = false;
    }
    in_file.close();

    GLCall(GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
    const GLchar* fragSrc = src.c_str();
    GLCall(glShaderSource(fragmentShader, 1, &fragSrc, NULL));
    GLCall(glCompileShader(fragmentShader));

    GLCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success));
    if (!success){
        GLCall(glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog));
        std::cout<<"ERROR:LOADSHADERS::COULD_NOT_COMPILE_FRAGMENT_SHADER"<<std::endl;
        std::cout<<infoLog<<std::endl;
        loadSuccess = false;
    }

    //Program
    GLCall(program = glCreateProgram());

    GLCall(glAttachShader(program, vertexShader));
    GLCall(glAttachShader(program, fragmentShader));

    GLCall(glLinkProgram(program));

    GLCall(glGetProgramiv(program, GL_LINK_STATUS, &success));
    if (!success){
        GLCall(glGetProgramInfoLog(program, 512, NULL, infoLog));
        std::cout<<"ERROR::LOADSHADERS::COULD_NOT_LINK_PROGRAM"<<std::endl;
        std::cout<<infoLog<<std::endl;
        loadSuccess = false;
    }

    //END
    GLCall(glUseProgram(0));
    GLCall(glDeleteShader(vertexShader));
    GLCall(glDeleteShader(fragmentShader));

    return loadSuccess;
}

void updateInput(GLFWwindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    
    if (glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS)
        position.y += 0.01f;
    if (glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS)
        position.x -= 0.01f;
    if (glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS)
        position.y -= 0.01f;
    if (glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS)
        position.x += 0.01f;
    if (glfwGetKey(window, GLFW_KEY_Q)==GLFW_PRESS)
        rotation.y -= 1.0f;
    if (glfwGetKey(window, GLFW_KEY_E)==GLFW_PRESS)
        rotation.y += 1.0f;
    if (glfwGetKey(window, GLFW_KEY_Z)==GLFW_PRESS)
        scale += 0.1f;
    if (glfwGetKey(window, GLFW_KEY_X)==GLFW_PRESS)
        scale -= 0.1f;
}

int main(){

    //INIT GLFW
    glfwInit();

    //CREATE WINDOW
    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;
    int frameBufferWidth = 0;
    int frameBufferHeight = 0;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Window", NULL, NULL);

    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
    //glViewport(0, 0, frameBufferWidth, frameBufferHeight);

    glfwMakeContextCurrent(window); //IMPORTANT FOR GLEW

    glfwSwapInterval(1); //FPS

    //INIT GLEW (NEEDS WINDOW AND OPENGL CONTEXT)
    glewExperimental = GL_TRUE;

    //Error Test
    if (glewInit()!=GLEW_OK){
        std::cout<<"ERROR::MAIN.CPP::GLEW_INIT_FAILED"<<std::endl;
        glfwTerminate();
    }

    //OPENGL OPTIONS
    GLCall(glEnable(GL_DEPTH_TEST));
    //GLCall(glEnable(GL_CULL_FACE)); //NO DRAW BACK
    //GLCall(glCullFace(GL_BACK));
    GLCall(glFrontFace(GL_CCW));

    GLCall(glEnable(GL_BLEND)); //blends colors
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)); //OR GL_LINE FOR OUTLINE

    GLuint core_program;
    if(!loadShaders(core_program))
        glfwTerminate();

    //MODEL

    //VAO, VBO, EBO
    GLuint VAO;
    GLCall(glCreateVertexArrays(1, &VAO));
    GLCall(glBindVertexArray(VAO));

    GLuint VBO;
    GLCall(glGenBuffers(1, &VBO));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    GLuint EBO;
    GLCall(glGenBuffers(1, &EBO));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    //GLuint attribLoc = glGetAttribLocation(core_program, "vertex_position");
    //POSITION
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position)));
    GLCall(glEnableVertexAttribArray(0));

    //COLOR
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color)));
    GLCall(glEnableVertexAttribArray(1));

    //TEXCOORD
    GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord)));
    GLCall(glEnableVertexAttribArray(2));

    GLCall(glBindVertexArray(0));

    //TEXTURE0
    int image_width = 0;
    int image_height = 0;
    unsigned char* image = SOIL_load_image("src/worm.png", &image_width, &image_height, NULL, SOIL_LOAD_RGBA);

    GLuint texture0;
    glGenTextures(1, &texture0);
    glBindTexture(GL_TEXTURE_2D, texture0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    if (image){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout<<"ERROR::TEXTURE_LOADING_FAILED"<<std::endl;
    }

    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);

    //TEXTURE1
    int image_width1 = 0;
    int image_height1 = 0;
    unsigned char* image1 = SOIL_load_image("src/stone.png", &image_width1, &image_height1, NULL, SOIL_LOAD_RGBA);

    GLuint texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    if (image1){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width1, image_height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout<<"ERROR::TEXTURE_LOADING_FAILED"<<std::endl;
    }

    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image1);

    //INIT MATRICES
    glm::vec3 position(0.0f);
    glm::vec3 rotation(0.0f);
    glm::vec3 scale(1.0f);

    glm::mat4 ModelMatrix(1.0f);
    ModelMatrix = glm::translate(ModelMatrix, position);
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    ModelMatrix = glm::scale(ModelMatrix, scale);

    glm::vec3 camPosition(0.0f, 0.0f, 1.0f);
    glm::vec3 worldUp(0.0f, 1.0f, 0.0f);
    glm::vec3 camFront(0.0f, 0.0f, -1.0f);
    glm::mat4 ViewMatrix(1.0f);
    ViewMatrix = glm::lookAt(camPosition, camPosition+camFront, worldUp);

    float fov = 90.0f;
    float nearPlane = 0.1f;
    float farPlane = 1000.0f;
    glm::mat4 ProjectionMatrix(1.0f);

    ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(frameBufferWidth)/frameBufferHeight, nearPlane, farPlane);

    GLCall(glUseProgram(core_program));

    GLCall(glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix)));
    GLCall(glUniformMatrix4fv(glGetUniformLocation(core_program, "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(ViewMatrix)));
    GLCall(glUniformMatrix4fv(glGetUniformLocation(core_program, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix)));

    GLCall(glUseProgram(0));

    //MAIN LOOP
    while (!glfwWindowShouldClose(window)){
        //UPDATE INPUT
        GLCall(glfwPollEvents());
        updateInput(window, position, rotation, scale);

        //DRAW
        //Clear
        GLCall(glClearColor(1, 1, 0, 1));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

        //Draw
        GLCall(glUseProgram(core_program));

        GLCall(glUniform1i(glGetUniformLocation(core_program, "texture0"), 0));
        GLCall(glUniform1i(glGetUniformLocation(core_program, "texture1"), 1));
        
        //Move, rotate, and scale
        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::translate(ModelMatrix, position);
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        ModelMatrix = glm::scale(ModelMatrix, scale);

        GLCall(glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix)));

        glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
        ProjectionMatrix = glm::mat4(1.0f);
        ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(frameBufferWidth)/frameBufferHeight, nearPlane, farPlane);

        GLCall(glUniformMatrix4fv(glGetUniformLocation(core_program, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix)));

        GLCall(glActiveTexture(GL_TEXTURE0));
        GLCall(glBindTexture(GL_TEXTURE_2D, texture0));
        GLCall(glActiveTexture(GL_TEXTURE1));
        GLCall(glBindTexture(GL_TEXTURE_2D, texture1));
        
        GLCall(glBindVertexArray(VAO));

        GLCall(glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0));
        //End draw
        GLCall(glfwSwapBuffers(window));
        GLCall(glFlush());

        GLCall(glBindVertexArray(0));
        GLCall(glUseProgram(0));
        GLCall(glActiveTexture(GL_TEXTURE0));
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }

    //END OF PROGRAM
    glfwDestroyWindow(window);
    glfwTerminate();

    //DELETE PROGRAM
    glDeleteProgram(core_program);

    return 0;
}

/*//OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Generic Includes
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//Error Handling Macro
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError(){
    while (glGetError()!=GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line){
    while (GLenum error = glGetError()){
        std::cout<<"[OpenGL Error] {"<<error<<"}: "<<function<<" "<<file<<":"<<line<<std::endl;
        return false;
    }
    return true;
}

//Struct to store shader code
struct ShaderProgramSource{
    std::string VertexSource;
    std::string FragmentSource;
};

//Read in shader code
static ShaderProgramSource ParseShader(const std::string& filepath){
    std::ifstream stream(filepath);

    enum class ShaderType{
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (std::getline(stream, line)){
        if (line.find("#shader")!=std::string::npos){ //If reading a shader type
            if (line.find("vertex")!=std::string::npos) //Set shader type
                type = ShaderType::VERTEX;
            else if (line.find("fragment")!=std::string::npos)
                type = ShaderType::FRAGMENT;
        } else{
            ss[(int)type]<<line<<"\n"; //Read in code to specific type
        }
    }

    return {ss[0].str(), ss[1].str()}; //Return the source code
}

//Compile shaders from code
static unsigned int CompileShader(unsigned int type, const std::string& source){
    GLCall(unsigned int id = glCreateShader(type)); //Create a shader of type
    const char* src = source.c_str(); //Get source string type
    GLCall(glShaderSource(id, 1, &src, nullptr)); //Send source to shader
    GLCall(glCompileShader(id)); //Compile shader

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result)); //Get any shader compilation errors
    if (result==GL_FALSE){
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout<<"Failed to compile "<<(type==GL_VERTEX_SHADER ? "vertex" : "fragment")<<" shader!"<<std::endl;
        std::cout<<message<<std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

//Generate the compiled shader
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
    GLCall(unsigned int program = glCreateProgram()); //Setup shader program
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader); //Compile shaders
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs)); //Link shaders to program
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs)); //Delete shaders
    GLCall(glDeleteShader(fs));

    return program; //Return the program with linked shaders
}

int main(void)
{
    GLFWwindow* window; //Create window

    /* Initialize the library *//*
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context *//*
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current *//*
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1); //Link framerate with vsync

    if (glewInit()!=GLEW_OK)
        std::cout<<"Error!"<<std::endl;

    float positions[] = { //Vertex positions
        .5f, .5f,   //0
        .5f, -.5f,  //1
        -.5f, -.5f, //2
        -.5f, .5f,  //3
    };

    unsigned int indices[] = { //Triange vertex indices
        0,1,2,
        0,2,3
    };

    unsigned int buffer; //Create buffer data
    GLCall(glGenBuffers(1, &buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, 4*2*sizeof(float), positions, GL_STATIC_DRAW));

    GLCall(glEnableVertexAttribArray(0)); //Create vertex attributes
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0));

    unsigned int ibo; //Create index buffer
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2*3*sizeof(unsigned int), indices, GL_STATIC_DRAW));

    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader"); //Read in source for shaders
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource); //Generate shaders
    GLCall(glUseProgram(shader)); //Use shaders

    GLCall(int location = glGetUniformLocation(shader, "u_Color")); //Get location of u_Color data
    ASSERT(location!=-1);

    float g = 0.0f; //Animation stuff
    float increment = .05f;

    /* Loop until the user closes the window *//*
    while (!glfwWindowShouldClose(window))
    {
        /* Render here *//*
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glUniform4f(location, .5f, g, .5f, 1.0f)); //Set u_Color
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr)); //Draw

        if (g>1.0f) //Animate stuff
            increment = -.05f;
        else if (g<0)
            increment = .05f;

        g += increment;

        /* Swap front and back buffers *//*
        GLCall(glfwSwapBuffers(window));

        /* Poll for and process events *//*
        GLCall(glfwPollEvents());
    }

    GLCall(glDeleteProgram(shader));

    glfwTerminate();
    return 0;
}*/