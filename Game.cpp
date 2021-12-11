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

    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::initMatrices(){
    std::cout<<"Initializing Matrices"<<std::endl;
    this->ViewMatrix = glm::mat4(1.0f);
    ViewMatrix = glm::lookAt(this->camPosition, this->camPosition+this->camFront, this->worldUp);

    this->ProjectionMatrix = glm::mat4(1.0f);
    this->ProjectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->framebufferWidth)/this->framebufferHeight, this->nearPlane, this->farPlane);

}

void Game::initShaders(){
    std::cout<<"Initializing Shaders"<<std::endl;
    this->shaders.push_back(new Shader(
        this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
        (char*)("src/vertex_core.glsl"), (char*)("src/fragment_core.glsl"))
    );
}

void Game::initTextures(){
    std::cout<<"Initializing Textures"<<std::endl;
    this->textures.push_back(new Texture("src/weight1.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("src/weight2.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("src/weight3.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("src/weight4.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("src/worm.png", GL_TEXTURE_2D));


    /*//TEXTURE0
    this->textures.push_back(new Texture("src/worm.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("src/worm_specular.png", GL_TEXTURE_2D));

    //TEXTURE1
    this->textures.push_back(new Texture("src/stone.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("src/stone_specular.png", GL_TEXTURE_2D));*/
}

void Game::initMaterials(){
    std::cout<<"Initializing Materials"<<std::endl;
    this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 0, 1, 0.1f));
    this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f), 0, 1, 1.0f));
}

void Game::initMeshes(){
    
    //std::cout<<std::endl<<"PATH SIZE: "<<this->path.size()<<std::endl;

    std::cout<<"Init Meshes"<<std::endl;

    /*Quad tempQuad;
    this->meshes.push_back(
        new Mesh(
            &tempQuad,
            1,
            glm::vec3(0.0f, 0.0f, -5.0f),
            glm::vec3(0.0f, 90.0f, 0.0f),
            glm::vec3(1.0f)
        ));

    //Quad tempQuad;
    this->meshes.push_back(
        new Mesh(
            &tempQuad,
            2,
            glm::vec3(1.0f, 0.0f, -5.0f),
            glm::vec3(0.0f, -90.0f, 0.0f),
            glm::vec3(1.0f)
        ));*/

    Cube tempCube;
    Quad tempQuad;

    /*for (int i = 0; i<10000; i++){
        Quad tempQuad;

        if (walls[i]->f==0)
            this->meshes.push_back(
                new Mesh(
                    &tempQuad,
                    walls[i]->w,
                    glm::vec3((float)walls[i]->x+.5f, (float)walls[i]->y, -(float)walls[i]->z),
                    glm::vec3(0.0f, 90.0f, 0.0f),
                    glm::vec3(1.0f)
                ));
        if (walls[i]->f==1)
            this->meshes.push_back(
                new Mesh(
                    &tempQuad,
                    walls[i]->w,
                    glm::vec3((float)walls[i]->x-.5f, (float)walls[i]->y, -(float)walls[i]->z),
                    glm::vec3(0.0f, -90.0f, 0.0f),
                    glm::vec3(1.0f)
                ));

        if (walls[i]->f==3)
            this->meshes.push_back(
                new Mesh(
                    &tempQuad,
                    walls[i]->w,
                    glm::vec3((float)walls[i]->x, (float)walls[i]->y-.5f, -(float)walls[i]->z),
                    glm::vec3(90.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f)
                ));
        if (walls[i]->f==2)
            this->meshes.push_back(
                new Mesh(
                    &tempQuad,
                    walls[i]->w,
                    glm::vec3((float)walls[i]->x, (float)walls[i]->y+.5f, -(float)walls[i]->z),
                    glm::vec3(-90.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f)
                ));

        if (walls[i]->f==5)
            this->meshes.push_back(
                new Mesh(
                    &tempQuad,
                    walls[i]->w,
                    glm::vec3((float)walls[i]->x, (float)walls[i]->y, -(float)walls[i]->z-.5f),
                    glm::vec3(0.0f, 180.0f, 0.0f),
                    glm::vec3(1.0f)
                ));
        if (walls[i]->f==4)
            this->meshes.push_back(
                new Mesh(
                    &tempQuad,
                    walls[i]->w,
                    glm::vec3((float)walls[i]->x, (float)walls[i]->y, -(float)walls[i]->z+.5f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f)
                ));
    }*/

    this->wormMeshes.push_back(
        new Mesh(
            &tempCube,
            5,
            glm::vec3(9.0f, 9.5f, -9.0f),
            glm::vec3(0.0f),
            glm::vec3(0.5f, 1.5f, 0.5f)
        )
    );

    int xC = 0, yC = 0, zC = 0, xCN = 0, yCN = 0, zCN = 0;

    for (int i = 0; i < path.size()-1; i++){

        zC = path[i]/100;
        yC = (path[i]%100)/10;
        xC = (path[i]%100)%10;
        zCN = path[i+1]/100;
        yCN = (path[i+1]%100)/10;
        xCN = (path[i+1]%100)%10;

        //std::cout<<"Path "<<i<<": "<<xC<<", "<<yC<<", "<<zC<<std::endl;

        glm::vec3 diff = glm::vec3(xC, yC, zC)-glm::vec3(xCN, yCN, zCN);

        if (diff.y==1){
            this->wormMeshes.push_back(
                new Mesh(
                    &tempCube,
                    5,
                    glm::vec3((float)xC, (float)yC-.5f, -(float)zC),
                    glm::vec3(0.0f),
                    glm::vec3(0.5f, 1.5f, 0.5f)
                )
            );
        }
        else if (diff.y==-1){
            this->wormMeshes.push_back(
                new Mesh(
                    &tempCube,
                    5,
                    glm::vec3((float)xC, (float)yC+.5f, -(float)zC),
                    glm::vec3(0.0f),
                    glm::vec3(0.5f, 1.5f, 0.5f)
                )
            );
        }

        if (diff.x==-1){
            this->wormMeshes.push_back(
                new Mesh(
                    &tempCube,
                    5,
                    glm::vec3((float)xC+0.5f, (float)yC, -(float)zC),
                    glm::vec3(0.0f),
                    glm::vec3(1.5f, 0.5f, 0.5f)
                )
            );
        }
        else if (diff.x==1){
            this->wormMeshes.push_back(
                new Mesh(
                    &tempCube,
                    5,
                    glm::vec3((float)xC-0.5f, (float)yC, -(float)zC),
                    glm::vec3(0.0f),
                    glm::vec3(1.5f, 0.5f, 0.5f)
                )
            );
        }

        if (diff.z==-1){
            this->wormMeshes.push_back(
                new Mesh(
                    &tempCube,
                    5,
                    glm::vec3((float)xC, (float)yC, -((float)zC+.5f)),
                    glm::vec3(0.0f),
                    glm::vec3(0.5f, 0.5f, 1.5f)
                )
            );
        }
        else if (diff.z==1){
            this->wormMeshes.push_back(
                new Mesh(
                    &tempCube,
                    5,
                    glm::vec3((float)xC, (float)yC, -((float)zC-.5f)),
                    glm::vec3(0.0f),
                    glm::vec3(0.5f, 0.5f, 1.5f)
                )
            );
        }
    }

    this->wormMeshesFinal.push_back(
        new Mesh(
            &tempCube,
            5,
            glm::vec3(0.0f, -0.5f, 0.0f),
            glm::vec3(0.0f),
            glm::vec3(0.5f, 1.5f, 0.5f)
        )
    );

    for (int i = 0; i<pathFinal.size()-1; i++){

        zC = pathFinal[i]/100;
        yC = (pathFinal[i]%100)/10;
        xC = (pathFinal[i]%100)%10;
        zCN = pathFinal[i+1]/100;
        yCN = (pathFinal[i+1]%100)/10;
        xCN = (pathFinal[i+1]%100)%10;

        //std::cout<<"Path "<<i<<": "<<xC<<", "<<yC<<", "<<zC<<std::endl;

        glm::vec3 diff = glm::vec3(xC, yC, zC)-glm::vec3(xCN, yCN, zCN);

        if (diff.y==1){
            this->wormMeshesFinal.push_back(
                new Mesh(
                    &tempCube,
                    5,
                    glm::vec3((float)xC, (float)yC-.5f, -(float)zC),
                    glm::vec3(0.0f),
                    glm::vec3(0.5f, 1.5f, 0.5f)
                )
            );
        }
        else if (diff.y==-1){
            this->wormMeshesFinal.push_back(
                new Mesh(
                    &tempCube,
                    5,
                    glm::vec3((float)xC, (float)yC+.5f, -(float)zC),
                    glm::vec3(0.0f),
                    glm::vec3(0.5f, 1.5f, 0.5f)
                )
            );
        }

        if (diff.x==-1){
            this->wormMeshesFinal.push_back(
                new Mesh(
                    &tempCube,
                    5,
                    glm::vec3((float)xC+0.5f, (float)yC, -(float)zC),
                    glm::vec3(0.0f),
                    glm::vec3(1.5f, 0.5f, 0.5f)
                )
            );
        }
        else if (diff.x==1){
            this->wormMeshesFinal.push_back(
                new Mesh(
                    &tempCube,
                    5,
                    glm::vec3((float)xC-0.5f, (float)yC, -(float)zC),
                    glm::vec3(0.0f),
                    glm::vec3(1.5f, 0.5f, 0.5f)
                )
            );
        }

        if (diff.z==-1){
            this->wormMeshesFinal.push_back(
                new Mesh(
                    &tempCube,
                    5,
                    glm::vec3((float)xC, (float)yC, -((float)zC+.5f)),
                    glm::vec3(0.0f),
                    glm::vec3(0.5f, 0.5f, 1.5f)
                )
            );
        }
        else if (diff.z==1){
            this->wormMeshesFinal.push_back(
                new Mesh(
                    &tempCube,
                    5,
                    glm::vec3((float)xC, (float)yC, -((float)zC-.5f)),
                    glm::vec3(0.0f),
                    glm::vec3(0.5f, 0.5f, 1.5f)
                )
            );
        }
    }

    this->wormMeshesFinal.push_back(
        new Mesh(
            &tempCube,
            5,
            glm::vec3(0.0f, -0.5f, 0.0f),
            glm::vec3(0.0f),
            glm::vec3(0.5f, 1.5f, 0.5f)
        )
    );

    this->aMeshes.push_back(
        new Mesh(
            &tempCube,
            5,
            glm::vec3(0.0f, -0.5f, 0.0f),
            glm::vec3(0.0f),
            glm::vec3(0.5f, 1.5f, 0.5f)
        )
    );

    for (int i = 0; i<aPath.size()-1; i++){

        zC = aPath[i]/100;
        yC = (aPath[i]%100)/10;
        xC = (aPath[i]%100)%10;
        zCN = aPath[i+1]/100;
        yCN = (aPath[i+1]%100)/10;
        xCN = (aPath[i+1]%100)%10;

        //std::cout<<"Path "<<i<<": "<<xC<<", "<<yC<<", "<<zC<<std::endl;

        glm::vec3 diff = glm::vec3(xC, yC, zC)-glm::vec3(xCN, yCN, zCN);

        if (diff.y==1){
            this->aMeshes.push_back(
                new Mesh(
                    &tempCube,
                    5,
                    glm::vec3((float)xC, (float)yC-.5f, -(float)zC),
                    glm::vec3(0.0f),
                    glm::vec3(0.5f, 1.5f, 0.5f)
                )
            );
        }
        else if (diff.y==-1){
            this->aMeshes.push_back(
                new Mesh(
                    &tempCube,
                    5,
                    glm::vec3((float)xC, (float)yC+.5f, -(float)zC),
                    glm::vec3(0.0f),
                    glm::vec3(0.5f, 1.5f, 0.5f)
                )
            );
        }

        if (diff.x==-1){
            this->aMeshes.push_back(
                new Mesh(
                    &tempCube,
                    5,
                    glm::vec3((float)xC+0.5f, (float)yC, -(float)zC),
                    glm::vec3(0.0f),
                    glm::vec3(1.5f, 0.5f, 0.5f)
                )
            );
        }
        else if (diff.x==1){
            this->aMeshes.push_back(
                new Mesh(
                    &tempCube,
                    5,
                    glm::vec3((float)xC-0.5f, (float)yC, -(float)zC),
                    glm::vec3(0.0f),
                    glm::vec3(1.5f, 0.5f, 0.5f)
                )
            );
        }

        if (diff.z==-1){
            this->aMeshes.push_back(
                new Mesh(
                    &tempCube,
                    5,
                    glm::vec3((float)xC, (float)yC, -((float)zC+.5f)),
                    glm::vec3(0.0f),
                    glm::vec3(0.5f, 0.5f, 1.5f)
                )
            );
        }
        else if (diff.z==1){
            this->aMeshes.push_back(
                new Mesh(
                    &tempCube,
                    5,
                    glm::vec3((float)xC, (float)yC, -((float)zC-.5f)),
                    glm::vec3(0.0f),
                    glm::vec3(0.5f, 0.5f, 1.5f)
                )
            );
        }
    }

    this->aMeshes.push_back(
        new Mesh(
            &tempCube,
            5,
            glm::vec3(0.0f, -0.5f, 0.0f),
            glm::vec3(0.0f),
            glm::vec3(0.5f, 1.5f, 0.5f)
        )
    );

    /*for (auto v:path){
        //std::cout<<"Building Cube at "<<v->xPos<<" "<<v->yPos<<" "<<v->zPos<<std::endl;
        this->meshes.push_back(
            new Mesh(
                &tempCube,
                5,
                glm::vec3((float)v->xPos, (float)v->yPos, -(float)v->zPos),
                glm::vec3(0.0f),
                glm::vec3(0.3f)
            )
        );
    }*/

    /*this->meshes.push_back(
        new Mesh(
            &tempCube,
            5,
            glm::vec3(0.0f),
            glm::vec3(0.0f),
            glm::vec3(0.3f)
        )
    );*/

    std::cout<<"Cube Meshes Built"<<std::endl;

    for (auto v:walls){

        if (v->f==0)
            this->meshes.push_back(
                new Mesh(
                    &tempQuad,
                    v->w,
                    glm::vec3((float)v->x+.5f, (float)v->y, -(float)v->z),
                    glm::vec3(0.0f, 90.0f, 0.0f),
                    glm::vec3(1.0f)
                ));
        if (v->f==1)
            this->meshes.push_back(
                new Mesh(
                    &tempQuad,
                    v->w,
                    glm::vec3((float)v->x-.5f, (float)v->y, -(float)v->z),
                    glm::vec3(0.0f, -90.0f, 0.0f),
                    glm::vec3(1.0f)
                ));

        if (v->f==3)
            this->meshes.push_back(
                new Mesh(
                    &tempQuad,
                    v->w,
                    glm::vec3((float)v->x, (float)v->y-.5f, -(float)v->z),
                    glm::vec3(90.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f)
                ));
        if (v->f==2)
            this->meshes.push_back(
                new Mesh(
                    &tempQuad,
                    v->w,
                    glm::vec3((float)v->x, (float)v->y+.5f, -(float)v->z),
                    glm::vec3(-90.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f)
                ));

        if (v->f==5)
            this->meshes.push_back(
                new Mesh(
                    &tempQuad,
                    v->w,
                    glm::vec3((float)v->x, (float)v->y, -(float)v->z-.5f),
                    glm::vec3(0.0f, 180.0f, 0.0f),
                    glm::vec3(1.0f)
                ));
        if (v->f==4)
            this->meshes.push_back(
                new Mesh(
                    &tempQuad,
                    v->w,
                    glm::vec3((float)v->x, (float)v->y, -(float)v->z+.5f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f)
                ));
    }

    /*Pyramid tempPyramid;
    this->meshes.push_back(
        new Mesh(
            &tempPyramid,
            glm::vec3(0.0f),
            glm::vec3(0.0f),
            glm::vec3(1.0f)
        ));*/

    /*Cube tempCube;
    this->meshes.push_back(
        new Mesh(
            &tempCube,
            glm::vec3(0.5f, 0.0f, -1.0f),
            glm::vec3(0.0f),
            glm::vec3(1.0f)
        ));

    this->meshes.push_back(
        new Mesh(
            &tempCube,
            glm::vec3(-0.5f, 0.0f, -1.0f),
            glm::vec3(0.0f),
            glm::vec3(1.0f)
        ));*/
}

void Game::initLights(){
    std::cout<<"Initializing Lights"<<std::endl;
    this->lights.push_back(new glm::vec3(0.0f, 0.0f, 5.0f));
}

void Game::initUniforms(){
    std::cout<<"Initializing Uniforms"<<std::endl;
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");

    this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
}

void Game::updateUniforms(){
    //std::cout<<"Updating Uniforms"<<std::endl;
    //Update View Matrix (camera)
    this->ViewMatrix = this->camera.getViewMatrix();

    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
    this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "cameraPos");

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
    std::vector<wallToBuild*> walls,
    std::vector<int> path,
    std::vector<int> pathFinal,
    std::vector<int> aPath,
    const char* title,
    const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
    const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
    bool resizable
)
    : WINDOW_WIDTH(WINDOW_WIDTH), WINDOW_HEIGHT(WINDOW_HEIGHT),
    GL_VERSION_MAJOR(GL_VERSION_MAJOR), GL_VERSION_MINOR(GL_VERSION_MINOR),
    camera(glm::vec3(0.0f, 0.f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f))
{
    //Init Variables

    //std::cout<<std::endl<<"From Game, path.size(): "<<path.size()<<std::endl;
    this->path = path;
    this->pathFinal = pathFinal;
    this->aPath = aPath;

    this->window = nullptr;
    this->framebufferWidth = this->WINDOW_WIDTH;
    this->framebufferHeight = this->WINDOW_HEIGHT;
    
    this->walls = walls;

    this->camPosition = glm::vec3(0.0f, 0.0f, 5.0f);
    this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->camFront = glm::vec3(0.0f, 0.0f, -1.0f);

    this->fov = 90.0f;
    this->nearPlane = 0.1f;
    this->farPlane = 1000.0f;

    this->dt = 0.0f;
    this->curTime = 0.0f;
    this->lastTime = 0.0f;

    this->lastMouseX = 0.0;
    this->lastMouseY = 0.0;
    this->mouseX = 0.0;
    this->mouseY = 0.0;
    this->mouseOffsetX = 0.0;
    this->mouseOffsetY = 0.0;
    this->firstMouse = true;

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

    for (auto v:walls)
        delete v;
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
void Game::updateDt(){
    this->curTime = static_cast<float>(glfwGetTime());
    this->dt = this->curTime-this->lastTime;
    this->lastTime = this->curTime;
}

void Game::updateMouseInput(){
    glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

    if (this->firstMouse){
        this->lastMouseX = this->mouseX;
        this->lastMouseY = this->mouseY;
        this->firstMouse = false;
    }

    //calc offset
    this->mouseOffsetX = this->mouseX-this->lastMouseX;
    this->mouseOffsetY = this->mouseY-this->lastMouseY;

    //Set last x and y
    this->lastMouseX = this->mouseX;
    this->lastMouseY = this->mouseY;
}

void Game::updateKeyboardInput(){
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE)==GLFW_PRESS)
        glfwSetWindowShouldClose(this->window, GLFW_TRUE);
    if (glfwGetKey(this->window, GLFW_KEY_W)==GLFW_PRESS)
        this->camera.move(this->dt, FORWARD);
    if (glfwGetKey(this->window, GLFW_KEY_S)==GLFW_PRESS)
        this->camera.move(this->dt, BACK);
    if (glfwGetKey(this->window, GLFW_KEY_A)==GLFW_PRESS)
        this->camera.move(this->dt, LEFT);
    if (glfwGetKey(this->window, GLFW_KEY_D)==GLFW_PRESS)
        this->camera.move(this->dt, RIGHT);
    if (glfwGetKey(this->window, GLFW_KEY_E)==GLFW_PRESS)
        this->camPosition.y += 0.05f;
    if (glfwGetKey(this->window, GLFW_KEY_Q)==GLFW_PRESS)
        this->camPosition.y -= 0.05f;
    if (glfwGetKey(this->window, GLFW_KEY_ENTER)==GLFW_PRESS){
        this->countToRender++;
    }

    if (glfwGetKey(this->window, GLFW_KEY_P)==GLFW_PRESS){
        this->aCount++;
    }

    if (glfwGetKey(this->window, GLFW_KEY_SPACE)==GLFW_PRESS){
        this->showFinal = true;
    }
}

void Game::updateInput(){
    glfwPollEvents();
    this->updateKeyboardInput();
    this->updateMouseInput();

    this->camera.updateInput(dt, -1, this->mouseOffsetX, this->mouseOffsetY);
}

void Game::update(){
    this->updateDt();
    this->updateInput();
    //std::cout<<"DT: "<<this->dt<<std::endl;
    //std::cout<<"Mouse offsetx: "<<this->mouseOffsetX<<" Mouse offsetY: "<<this->mouseOffsetY<<std::endl;
}

void Game::render(){
    //DRAW
    //Clear
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

    //Update uniforms
    this->updateUniforms();

    //this->materials[0]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);
    this->shaders[SHADER_CORE_PROGRAM]->use();
    this->materials[1]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);

    if (aCount>0){
        showFinal = false;
        countToRender = 0;

        for (int i = 0; i<aCount; i++){
            if (i<aMeshes.size()){
                this->textures[4]->bind(0);
                this->textures[4]->bind(1);
                aMeshes[i]->render(this->shaders[SHADER_CORE_PROGRAM]);
            }
        }
    }

    if (showFinal){
        countToRender = 0;

        for (int i = 0; i<wormMeshesFinal.size(); i++){
            this->textures[4]->bind(0);
            this->textures[4]->bind(1);
            wormMeshesFinal[i]->render(this->shaders[SHADER_CORE_PROGRAM]);
        }
    }

    for (int i = 0; i<countToRender; i++){
        if (i<wormMeshes.size()){
            this->textures[4]->bind(0);
            this->textures[4]->bind(1);
            wormMeshes[i]->render(this->shaders[SHADER_CORE_PROGRAM]);
        }
    }


    this->materials[0]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);

    for (auto v:meshes){
        this->textures[v->weight-1]->bind(0);
        this->textures[v->weight-1]->bind(1);
        v->render(this->shaders[SHADER_CORE_PROGRAM]);
    }

    //Activate Textures
    /*this->textures[TEX_WEIGHT1]->bind(0);
    this->textures[TEX_WEIGHT1]->bind(1);

    //Draw
    this->meshes[0]->render(this->shaders[SHADER_CORE_PROGRAM]);*/

    //this->textures[TEX_WORM]->bind(0);
    //this->textures[TEX_WORM_SPECULAR]->bind(1);

    //this->meshes[1]->render(this->shaders[SHADER_CORE_PROGRAM]);

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

/*void Game::updateInput(GLFWwindow* window, Mesh& mesh){
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
}*/