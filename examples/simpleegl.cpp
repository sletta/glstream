#include <EGL/egl.h>
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>

#include <assert.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    EGLDisplay eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    printf("EGL Display: %p\n", eglDisplay);
    assert(eglGetError() == EGL_SUCCESS);

    int major, minor;
    eglInitialize(eglDisplay, &major, &minor);
    printf(" - EGL version: %d.%d\n", major, minor);

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

    EGLint contextAttributes[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    EGLContext eglContext = eglCreateContext(eglDisplay, configs[0], 0, contextAttributes);
    printf("EGL Context: %p\n", eglContext);

    EGLint surfaceAttributes[] = { EGL_NONE };
    EGLSurface eglSurface = eglCreateWindowSurface(eglDisplay, configs[0], 0, surfaceAttributes);
    printf("EGL Surface: %p\n", eglSurface);

    bool ok = eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
    printf("Make Current: %s\n", ok ? "ok" : "failed");
    printf(" - current display: %p\n", eglGetCurrentDisplay());
    printf(" - current read surface: %p\n", eglGetCurrentSurface(EGL_READ));
    printf(" - current draw surface: %p\n", eglGetCurrentSurface(EGL_DRAW));

    glClearColor(1, 0, 0, 0.5);
    glClear(GL_COLOR_BUFFER_BIT);
    ok = eglSwapBuffers(eglDisplay, eglSurface);

    return 0;
}