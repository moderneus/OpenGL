## 1. Creating Window with SDL3.
- To create a window with *SDL3* firstly we need to initialize *SDL3*. We can use the *SDL_Init()* function, passing in initialization flags, such as *SDL_INIT_VIDEO*, *SDL_INIT_AUDIO*, etc. 

- Secondly we need a window themself. To got it we should use *SDL_CreateWindow()* function with relevant arguments. After we wanna be able to handle any events, such as *SDL_EVENT_QUIT*, *SDL_EVENT_WINDOW_MOVED*, *SDL_EVENT_WINDOW_RESIZED*, etc. 
For example we want to handle an *SDL_EVENT_QUIT*. If user closed the window — break the event handle loop. 

Code example: 
```
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
```

Congratulations! We have a window and event handle loop! Now we must terminate the program correctly. To do this we must destroy the window and free all *SDL3* allocated memory. Use the *SDL_DestroyWindow()* and *SDL_Quit()* functions for it. 
