#include <iostream>
#include "load_frame.hpp"
#include "GLFW/glfw3.h"
using namespace std;
int main(){
    const char *filename = "/home/masoud/Programming/Looking For Love - Pornhub.com.mp4";
    GLFWwindow *window;
    if (!glfwInit())
    {
        printf("unable to initialize glfw\n");
        return -1;
    }

    window = glfwCreateWindow(640,480,"hello masoud",NULL, NULL);
    if (!window)
    {
        printf("unable to show window\n");
        return -1;
    }
    
    unsigned char * data = new unsigned char [100*100*3];
    for (size_t y = 0; y < 100; y++)
    {
        for (size_t x = 0; x < 100; x++)
        {
            data[y*100*3 + x*3   ] = 0xff;
            data[y*100*3 + x*3 +1] = 0x00;
            data[y*100*3 + x*3 +2] = 0x00;
        }
        
    }
    

    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
        /* code */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawPixels(100,100,GL_RGB,GL_UNSIGNED_BYTE,data);
        glfwSwapBuffers(window);
        glfwWaitEvents();

    }
    
    /*
    if (!load_frame(filename))
    {
        cout<<"something bad happened"<<endl;
    }
    */
    cout<<"hello masoud"<<endl;
    return 0;
}