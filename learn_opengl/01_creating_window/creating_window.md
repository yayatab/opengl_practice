# Creating a window

[link to book chapter - setup](https://learnopengl.com/Getting-started/Creating-a-window)<br>
[link to book chapter - hello_window](https://learnopengl.com/Getting-started/Hello-Window)

# Contents

* [But first](#but-first)
    * [GLFW](#glfw)
    * [GLAD](#glad)
* [Hello Window](#hello-window)
*

# But first...

We need to create context and a window for our application to draw on. Each operating system behaves differently, and
OpenGL is only an API for graphics. That means we'll need to handle this operation ourselves.
Thankfully, there are libraries for that:

* [GLFW](https://www.glfw.org/)
* [GLUT](https://www.opengl.org/resources/libraries/)
* [SDL](https://www.libsdl.org/)
* [SFML](https://github.com/SFML/SFML)

the book uses GLFW, so I will do too.

## GLFW

Library that provides us with the [bare necessities](https://www.youtube.com/watch?v=6BH-Rxd-NBo) for rendering stuff
and helps us avoid clutter like creating context, define window parameters, handle user input, and more.

### installment

I'm using wsl, so i made this [installment script](../../scripts/installments.sh) to install on windows.

### linking

```cmake 
target_link_libraries(your_target PRIVATE glfw GL)
```

## GLAD

a lot of the API is through functions and we can't know them at compilation time.
In order to do so, we'll have the following code:

```c
// define the function's prototype
typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
// find the function and assign it to a function pointer
GL_GENBUFFERS glGenBuffers  = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
// function can now be called as normal
unsigned int buffer;
glGenBuffers(1, &buffer);
```

That's annoying. So thankfully, we have [GLAD](https://github.com/Dav1dde/glad)! A library that does all these
declarations for us. We will generate the correct headers with [their website](https://glad.dav1d.de/).

#### Additional resources

* [GLFW: Window Guide](http://www.glfw.org/docs/latest/window_guide.html): official GLFW guide on setting up and
  configuring a GLFW window.
* [Building applications](http://www.opengl-tutorial.org/miscellaneous/building-your-own-c-application/): provides great
  info about the compilation/linking process of your application and a large list of possible errors (plus solutions)
  that may come up.
* [GLFW with Code::Blocks](http://wiki.codeblocks.org/index.php?title=Using_GLFW_with_Code::Blocks): building GLFW in
  Code::Blocks IDE.
* [Writing a build system under Linux](https://learnopengl.com/demo/autotools_tutorial.txt): an autotools tutorial by
  Wouter Verholst on how to write a build system in Linux.
* [Polytonic/Glitter](https://github.com/Polytonic/Glitter): a simple boilerplate project that comes pre-configured with
  all relevant libraries; great for if you want a sample project without the hassle of having to compile all the
  libraries yourself.

# Hello Window

Finally, after all this setup and installments, let's make a window!

## Viewport

we need to define the [vieport](../MySummeryAndUnderstanding.md#viewport), and handle resizing

## Starting the render loop

As programs go, they stop when they finish. so we put a loop that ends when we want it to end. each loop is called a
frame

##  Rendering

we want to render something, a colour!



