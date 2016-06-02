#include <EGL/egl.h>

#include <assert.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    EGLDisplay eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    printf("EGL Display: %p\n", eglDisplay);
    assert(eglGetError() == EGL_SUCCESS);

    printf(" - EGL_CLIENT_APIS: %s\n", eglQueryString(eglDisplay, EGL_CLIENT_APIS));
    printf(" - EGL_VENDOR:      %s\n", eglQueryString(eglDisplay, EGL_VENDOR));
    printf(" - EGL_VERSION:     %s\n", eglQueryString(eglDisplay, EGL_VERSION));
    printf(" - EGL_EXTENSIONS:  %s\n", eglQueryString(eglDisplay, EGL_EXTENSIONS));
    assert(eglGetError() == EGL_SUCCESS);

    int configCount;
    eglChooseConfig(eglDisplay, 0, 0, 0, &configCount);
    assert(eglGetError() == EGL_SUCCESS);

    printf("Number of available EGLConfigs: %d\n", configCount);

    EGLConfig configs[256];
    EGLint attributes[] = {
        EGL_NONE
    };
    eglChooseConfig(eglDisplay, attributes, configs, 256, &configCount);
    printf("   cfg: BS -  R  G  B  A -  D  S\n");
    for (int i=0; i<configCount; ++i) {
        int bufferSize, red, green, blue, alpha, depth, stencil;
        eglGetConfigAttrib(eglDisplay, configs[i], EGL_BUFFER_SIZE, &bufferSize);
        eglGetConfigAttrib(eglDisplay, configs[i], EGL_RED_SIZE, &red);
        eglGetConfigAttrib(eglDisplay, configs[i], EGL_GREEN_SIZE, &green);
        eglGetConfigAttrib(eglDisplay, configs[i], EGL_BLUE_SIZE, &blue);
        eglGetConfigAttrib(eglDisplay, configs[i], EGL_ALPHA_SIZE, &alpha);
        eglGetConfigAttrib(eglDisplay, configs[i], EGL_DEPTH_SIZE, &depth);
        eglGetConfigAttrib(eglDisplay, configs[i], EGL_STENCIL_SIZE, &stencil);
        printf("   %03d: %2d - %2d %2d %2d %2d - %2d %2d\n",
               i,
               bufferSize,
               red, green, blue, alpha,
               depth, stencil);
    }

    return 0;
}