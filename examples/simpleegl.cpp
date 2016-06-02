#include <EGL/egl.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    EGLDisplay eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    printf("EGL Display: %p\n", eglDisplay);

    return 0;
}