## 1. Creating Window with SDL3.
- To create a window with *SDL3* firstly we need to initialize *SDL3*. We can use the *SDL_Init()* function, passing in initialization flags, such as *SDL_INIT_VIDEO*, *SDL_INIT_AUDIO*, etc. 

- Secondly we need a window itself. To get it we should use *SDL_CreateWindow()* function with relevant arguments.
  
- Next, we want to be able to handle any events, such as *SDL_EVENT_QUIT*, *SDL_EVENT_WINDOW_MOVED*, *SDL_EVENT_WINDOW_RESIZED*, etc. 
For example we want to handle an *SDL_EVENT_QUIT*. If user closed the window — break the event handle loop. 

# Code: 
```
SDL_Init(SDL_INIT_VIDEO);

SDL_Window* pWindow = SDL_CreateWindow("Window", 800, 600, NULL);

SDL_Event event;

bool quit = false;
while(!quit)
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_EVENT_QUIT) 
            quit = true; 
    }
}

SDL_DestroyWindow(pWindow);
SDL_Quit();
```

Congratulations! We have a window and event handle loop! Now we must terminate the program correctly. To do this we must destroy the window and free all *SDL3* allocated memory. Use the *SDL_DestroyWindow()* and *SDL_Quit()* functions for it 🎉

## 2. Termins and color-change window program.
# GLAD.
- GLAD is a function loader for OpenGL. Since there are many different versions of OpenGL drivers, the location of most of its functions is not known at compile-time and needs to be queried at run-time.
- GLAD must be loaded with *gladLoadGL()* function after creating and making current a context.

# Context.
- An OpenGL context is an object in the video driver that stores all the current OpenGL state and the set of supported GPU capabilities used for rendering: active shaders, buffers, textures, render objects, and graphics pipeline parameters.
- To create context firstly we should set OpenGL attributes, such as *SDL_GL_CONTEXT_MAJOR_VERSION*, *SDL_GL_CONTEXT_MINOR_VERSION*, *SDL_GL_CONTEXT_PROFILE_MASK*. We can use *SDL_GL_SetAttribute()* function for it.
- After setting up a context we can create it and make it current with *SDL_GL_CreateContext()* and *SDL_GL_MakeCurrent()* functions.

# Color-change program.
- Now we will try to create a program that changes a window color to another by pressing defined keys.
- key *'R'* changes to red, *'G'* key to green and *'B'* to blue. Default color is black.

# Code:
```
// INIT
SDL_Init(SDL_INIT_VIDEO);    

// SETTING UP
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

// WINDOW
SDL_Window* pWindow = SDL_CreateWindow("OpenGL", 800, 600, SDL_WINDOW_OPENGL);

// CONTEXT
SDL_GLContext context = SDL_GL_CreateContext(pWindow);
SDL_GL_MakeCurrent(pWindow, context);

// INIT
gladLoadGL();

SDL_Event event;

const bool* keys = SDL_GetKeyboardState(nullptr);

glClearColor(0, 0, 0, 1); // BLACK COLOR
SDL_GL_SetSwapInterval(1);

bool quit = false;
while(!quit) // MAIN LOOP
{
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_EVENT_QUIT:
                return EXIT_SUCCESS;
            break;

            case SDL_EVENT_KEY_DOWN:
                if(keys[SDL_SCANCODE_R]) 
                    glClearColor(1, 0, 0, 1);

                else if(keys[SDL_SCANCODE_G])
                    glClearColor(0, 1, 0, 1);

                else if(keys[SDL_SCANCODE_B])
                    glClearColor(0, 0, 1, 1);
            break;
        }
    }

    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(pWindow);
}
    
SDL_GL_DestroyContext(context);
SDL_DestroyWindow(pWindow);
SDL_Quit();
```

- After initialization of *SDL3* and setting up we create context and initialize *GLAD*.
- Next we should get a keyboard state, which is an array of *const bools** with *SDL_GetKeyboardState()* function.
- Then we set the default color (Black) with *glClearColor()* function.
- In main loop we check: is pressed *any* key? If true we check: is that key is R, G or B? If true we set the relevant color.
- Next we clear a window with *glClear()* function and swapping the buffers. The unfinished frame is in the back buffer, when it is ready, the back buffer swaps with the front buffer, displaying the finished frame, and the frame is built again behind it.
