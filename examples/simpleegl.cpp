#include <EGL/egl.h>
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>

#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string>
#include <chrono>

#include "logging.h"

#include "openglhelpers.h"

struct {
    EGLDisplay display;
    EGLContext context;
    EGLSurface surface;
} egl;

struct {
    GLuint program;
} gl;

bool init_egl()
{
    egl.display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    printf("EGL Display: %p\n", egl.display);
    if (!egl.display)
        return false;

    assert(eglGetError() == EGL_SUCCESS);

    int major, minor;
    if (!eglInitialize(egl.display, &major, &minor))
        return false;
    printf(" - EGL version: %d.%d\n", major, minor);

    printf(" - EGL_CLIENT_APIS: %s\n", eglQueryString(egl.display, EGL_CLIENT_APIS));
    printf(" - EGL_VENDOR:      %s\n", eglQueryString(egl.display, EGL_VENDOR));
    printf(" - EGL_VERSION:     %s\n", eglQueryString(egl.display, EGL_VERSION));
    printf(" - EGL_EXTENSIONS:  %s\n", eglQueryString(egl.display, EGL_EXTENSIONS));
    assert(eglGetError() == EGL_SUCCESS);

    int configCount;
    eglChooseConfig(egl.display, 0, 0, 0, &configCount);
    assert(eglGetError() == EGL_SUCCESS);

    printf("Number of available EGLConfigs: %d\n", configCount);

    EGLConfig configs[256];
    EGLint attributes[] = {
        EGL_NONE
    };
    eglChooseConfig(egl.display, attributes, configs, 256, &configCount);
    printf("   cfg: BS -  R  G  B  A -  D  S\n");
    for (int i=0; i<configCount; ++i) {
        int bufferSize, red, green, blue, alpha, depth, stencil;
        eglGetConfigAttrib(egl.display, configs[i], EGL_BUFFER_SIZE, &bufferSize);
        eglGetConfigAttrib(egl.display, configs[i], EGL_RED_SIZE, &red);
        eglGetConfigAttrib(egl.display, configs[i], EGL_GREEN_SIZE, &green);
        eglGetConfigAttrib(egl.display, configs[i], EGL_BLUE_SIZE, &blue);
        eglGetConfigAttrib(egl.display, configs[i], EGL_ALPHA_SIZE, &alpha);
        eglGetConfigAttrib(egl.display, configs[i], EGL_DEPTH_SIZE, &depth);
        eglGetConfigAttrib(egl.display, configs[i], EGL_STENCIL_SIZE, &stencil);
        printf("   %03d: %2d - %2d %2d %2d %2d - %2d %2d\n",
               i,
               bufferSize,
               red, green, blue, alpha,
               depth, stencil);
    }

    EGLint contextAttributes[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    egl.context = eglCreateContext(egl.display, configs[0], 0, contextAttributes);
    printf("EGL Context: %p\n", egl.context);

    EGLint surfaceAttributes[] = { EGL_NONE };
    egl.surface = eglCreateWindowSurface(egl.display, configs[0], 0, surfaceAttributes);
    printf("EGL Surface: %p\n", egl.surface);

    bool ok = eglMakeCurrent(egl.display, egl.surface, egl.surface, egl.context);
    printf("Make Current: %s\n", ok ? "ok" : "failed");
    printf(" - current display: %p\n", eglGetCurrentDisplay());
    printf(" - current read surface: %p\n", eglGetCurrentSurface(EGL_READ));
    printf(" - current draw surface: %p\n", eglGetCurrentSurface(EGL_DRAW));

    return true;
}

bool init_gl()
{
    printf("GL_VERSION ........: %s\n", glGetString(GL_VERSION));
    printf("GL_RENDERER .......: %s\n", glGetString(GL_RENDERER));
    printf("GL_VENDOR .........: %s\n", glGetString(GL_VENDOR));
    printf("GL_EXTENSIONS .....: %s\n", glGetString(GL_EXTENSIONS));

    const char *attributes[] = { "aV", "aTC", 0 };
    gl.program = gl_create_program(// Vertex Shader
                                   "\n attribute vec4 aV;"
                                   "\n attribute vec2 aTC;"
                                   "\n varying vec2 vTC;"
                                   "\n void main() {"
                                   "\n     gl_Position = aV;"
                                   "\n     vTC = 3.0 * (aTC - 0.5);"
                                   "\n }",
                                   // Fragment Shader
                                   "\n uniform vec2 c;"
                                   "\n varying vec2 vTC;"
                                   "\n #define ITERATIONS 50"
                                   "\n void main() {"
                                   "\n      vec2 z = vTC;"
                                   "\n     int i;"
                                   "\n     for (i=0; i<ITERATIONS; ++i) {"
                                   "\n         float x = (z.x * z.x - z.y * z.y) + c.x;"
                                   "\n         float y = (z.y * z.x + z.x * z.y) + c.y;"
                                   "\n         if (x*x + y*y > 4.0) break;"
                                   "\n         z = vec2(x,y);"
                                   "\n     }"
                                   "\n     float v = i == ITERATIONS ? 0.0 : pow(float(i) / float(ITERATIONS), 0.5);"
                                   "\n     gl_FragColor = vec4(v * vec3(v, v*v, 1), 1);"
                                   "\n }",
                                   attributes);

    printf(" - program: %d\n", gl.program);

    return gl.program != 0;
}

int main(int argc, char **argv)
{
    if (!init_egl()) {
        printf("EGL init failed!!\n");
        return 0;
    }

    if (!init_gl()) {
        printf("GL init failed!\n");
        return 0;
    }

    bool ok;
    int frame = 0;
    while (frame < 10) {
        int c = ++frame % 2;

        logd(" -- start frame\n");
        glClearColor(c, 0, 1-c, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        logd(" -- swapping\n");
        ok = eglSwapBuffers(egl.display, egl.surface);
        logd(" -- done swapping\n");

        assert(ok);
    }

    return 0;
}