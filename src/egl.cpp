/*
    Copyright (c) 2016, Gunnar Sletta <gunnar@sletta.org>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
    ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "egls.h"
#include "logging.h"
#include "transport.h"

#include <iostream>


struct EGLSConfig
{
    unsigned char redBufferSize;
    unsigned char blueBufferSize;
    unsigned char greenBufferSize;
    unsigned char alphaBufferSize;

    unsigned char stencilBufferSize;
    unsigned char depthBufferSize;
    unsigned char sampleBuffers;
    unsigned char samples;
};

EGLSDisplayImpl egls_global_display;

EGLSConfig egls_global_config = {
    .redBufferSize = 8,
    .blueBufferSize = 8,
    .greenBufferSize = 8,
    .alphaBufferSize = 8,

    .stencilBufferSize = 8,
    .depthBufferSize = 24,

    .sampleBuffers = 0,
    .samples = 0,
};

EGLSThreadState *egls_getThreadState()
{
    __thread static EGLSThreadState state;
    return &state;
}


#define ABORT_ON_BAD_DISPLAY_WITH(returnOnFail)       \
    if (!dpy                                          \
        || dpy != &egls_global_display                \
        || !egls_global_display.isInitialized()) {        \
        printf("call failed...\n");                   \
        threadState->error = EGL_BAD_DISPLAY;         \
        return returnOnFail;                          \
    }

#define ABORT_WITH_BAD_PARAM_IF_NULL(param, returnOnFail)    \
    if (!param) {                                            \
        threadState->error = EGL_BAD_PARAMETER;              \
        return returnOnFail;                                 \
    }

#define GET_THREAD_STATE_AND_ASSUME_SUCCESS                  \
    EGLSThreadState *threadState = egls_getThreadState();    \
    threadState->error = EGL_SUCCESS

EGLAPI EGLDisplay EGLAPIENTRY eglGetDisplay(EGLNativeDisplayType display_id)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    if (display_id == EGL_DEFAULT_DISPLAY)
        return &egls_global_display;
    return EGL_NO_DISPLAY;
}


EGLAPI EGLBoolean EGLAPIENTRY eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    if (!dpy || dpy != &egls_global_display) {
        threadState->error = EGL_BAD_DISPLAY;
        return false;
    }
    EGLSDisplayImpl *display = (EGLSDisplayImpl *) dpy;
    if (!display->connectToServer())
        return false;

    display->setInitialized(true);
    *major = 1;
    *minor = 0;
    return true;
}


EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(false);

    EGLSDisplayImpl *display = (EGLSDisplayImpl *) dpy;
    threadState->context->cmds.swapBuffers();
    display->flush(threadState->context);

    return true;
}


EGLAPI EGLBoolean EGLAPIENTRY eglTerminate(EGLDisplay dpy)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(false);
    std::cerr << __PRETTY_FUNCTION__ << ": not implemented!" << std::endl;
    return false;
}


EGLAPI EGLBoolean EGLAPIENTRY eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(false);

    ABORT_WITH_BAD_PARAM_IF_NULL(num_config, false);

    if (configs == 0) {
        *num_config = 1;
    } else {
        ABORT_WITH_BAD_PARAM_IF_NULL(configs, false);
        configs[0] = &egls_global_config;
    }

    return false;
}


EGLAPI EGLBoolean EGLAPIENTRY eglCopyBuffers(EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(false);
    std::cerr << __PRETTY_FUNCTION__ << ": not implemented!" << std::endl;
    return false;
}


EGLAPI EGLContext EGLAPIENTRY eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(nullptr);
    // ### ignoring attrib_list for now..
    EGLSContextImpl *context = new EGLSContextImpl();
    context->config = config;
    context->display = dpy;
    return context;
}


EGLAPI EGLSurface EGLAPIENTRY eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(nullptr);
    std::cerr << __PRETTY_FUNCTION__ << ": not implemented!" << std::endl;
    return nullptr;
}


EGLAPI EGLSurface EGLAPIENTRY eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint *attrib_list)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(nullptr);
    std::cerr << __PRETTY_FUNCTION__ << ": not implemented!" << std::endl;
    return nullptr;
}


EGLAPI EGLSurface EGLAPIENTRY eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(nullptr);
    EGLSWindowSurface *surface = new EGLSWindowSurface();
    surface->display = dpy;
    surface->config = config;
    return surface;
}


EGLAPI EGLBoolean EGLAPIENTRY eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(false);
    ABORT_WITH_BAD_PARAM_IF_NULL(ctx, false);
    delete (EGLSContextImpl *) ctx;
    return true;
}


EGLAPI EGLBoolean EGLAPIENTRY eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(false);
    delete (EGLSWindowSurface *) surface;
    return true;
}


EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(false);
    ABORT_WITH_BAD_PARAM_IF_NULL(value, false);

    EGLSConfig *c = (EGLSConfig *) config;

    switch (attribute) {

    case EGL_RED_SIZE:               *value = c->redBufferSize; break;
    case EGL_GREEN_SIZE:             *value = c->greenBufferSize; break;
    case EGL_BLUE_SIZE:              *value = c->blueBufferSize; break;
    case EGL_ALPHA_SIZE:             *value = c->alphaBufferSize; break;

    case EGL_STENCIL_SIZE:           *value = c->stencilBufferSize; break;
    case EGL_DEPTH_SIZE:             *value = c->depthBufferSize; break;

    case EGL_ALPHA_MASK_SIZE:        *value = 0; break;
    case EGL_BUFFER_SIZE:            *value = c->redBufferSize + c->greenBufferSize + c->blueBufferSize + c->alphaBufferSize; break;

    case EGL_SAMPLE_BUFFERS:         *value = 0; break;
    case EGL_SAMPLES:                *value = 0; break;

    case EGL_BIND_TO_TEXTURE_RGB:    *value = 0; break;
    case EGL_BIND_TO_TEXTURE_RGBA:   *value = 0; break;
    case EGL_COLOR_BUFFER_TYPE:      *value = 0; break;
    case EGL_CONFIG_CAVEAT:          *value = 0; break;
    case EGL_CONFIG_ID:              *value = 0; break;
    case EGL_CONFORMANT:             *value = 0; break;
    case EGL_LEVEL:                  *value = 0; break;
    case EGL_LUMINANCE_SIZE:         *value = 0; break;
    case EGL_MAX_PBUFFER_WIDTH:      *value = 0; break;
    case EGL_MAX_PBUFFER_HEIGHT:     *value = 0; break;
    case EGL_MAX_PBUFFER_PIXELS:     *value = 0; break;
    case EGL_MAX_SWAP_INTERVAL:      *value = 1; break;
    case EGL_MIN_SWAP_INTERVAL:      *value = 1; break;
    case EGL_NATIVE_RENDERABLE:      *value = 0; break;
    case EGL_NATIVE_VISUAL_ID:       *value = 0; break;
    case EGL_NATIVE_VISUAL_TYPE:     *value = 0; break;
    case EGL_RENDERABLE_TYPE:        *value = 0; break;
    case EGL_SURFACE_TYPE:           *value = EGL_WINDOW_BIT; break;
    case EGL_TRANSPARENT_TYPE:       *value = 0; break;
    case EGL_TRANSPARENT_RED_VALUE:  *value = 0; break;
    case EGL_TRANSPARENT_GREEN_VALUE:*value = 0; break;
    case EGL_TRANSPARENT_BLUE_VALUE: *value = 0; break;
    default:
        threadState->error = EGL_BAD_ATTRIBUTE;
        return false;
    }

    return true;
}


EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigs(EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(false);
    std::cerr << __PRETTY_FUNCTION__ << ": not implemented!" << std::endl;
    return false;
}


EGLAPI EGLDisplay EGLAPIENTRY eglGetCurrentDisplay (void)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    return threadState->context->display;
}


EGLAPI EGLSurface EGLAPIENTRY eglGetCurrentSurface (EGLint mode)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    if (mode == EGL_DRAW)
        return threadState->drawSurface;
    else if (mode == EGL_READ)
        return threadState->readSurface;
    threadState->error = EGL_BAD_PARAMETER;
    return nullptr;
}


EGLAPI EGLint EGLAPIENTRY eglGetError (void)
{
    return egls_getThreadState()->error;
}

EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY eglGetProcAddress (const char *procname)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    return nullptr;
}


EGLAPI EGLBoolean EGLAPIENTRY eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(false);
    threadState->drawSurface = draw;
    threadState->readSurface = read;
    threadState->context = (EGLSContextImpl *) ctx;
    return true;
}


EGLAPI EGLBoolean EGLAPIENTRY eglQueryContext(EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *value)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(false);
    ABORT_WITH_BAD_PARAM_IF_NULL(ctx, false);
    ABORT_WITH_BAD_PARAM_IF_NULL(value, false);

    EGLSContextImpl *context = (EGLSContextImpl *) ctx;
    switch (attribute) {
        case EGL_CONFIG_ID:                 *value = 0;                     return true;
        case EGL_CONTEXT_CLIENT_TYPE:       *value = EGL_OPENGL_ES_API;     return true;
        case EGL_CONTEXT_CLIENT_VERSION:    *value = EGL_OPENGL_ES2_BIT;    return true;
        case EGL_RENDER_BUFFER:             *value = EGL_BACK_BUFFER;       return true;
        default: break;
    }

    threadState->error = EGL_BAD_ATTRIBUTE;
    return false;
}


EGLAPI const char *EGLAPIENTRY eglQueryString(EGLDisplay dpy, EGLint name)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(nullptr);
    switch (name) {
        case EGL_CLIENT_APIS:    return "OpenGL_ES";
        case EGL_VENDOR:         return "Sletta";
        case EGL_VERSION:        return "1.0";
        case EGL_EXTENSIONS:     return "";
        default: break;
    }
    threadState->error = EGL_BAD_ATTRIBUTE;
    return nullptr;
}


EGLAPI EGLBoolean EGLAPIENTRY eglQuerySurface(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value)
{
    std::cerr << __PRETTY_FUNCTION__ << ": not implemented!" << std::endl;
    return false;
}


EGLAPI EGLBoolean EGLAPIENTRY eglWaitGL (void)
{
    std::cerr << __PRETTY_FUNCTION__ << ": not implemented!" << std::endl;
    return false;
}


EGLAPI EGLBoolean EGLAPIENTRY eglWaitNative (EGLint engine)
{
    std::cerr << __PRETTY_FUNCTION__ << ": not implemented!" << std::endl;
    return false;
}


bool EGLSDisplayImpl::connectToServer()
{
    const char *address = getenv("GLSTREAM_ADDRESS");
    if (!address || strlen(address) == 0) {
        logwe("EGLDisplay: environment variable GLSTREAM_ADDRESS is not specified");
        return false;
    }

    logi("EGLDisplay: making connection to server at '%s'\n", address);
    m_transport = Transport::createClient(address);

    return m_transport != 0;
}

bool EGLSDisplayImpl::flush(EGLSContextImpl *context)
{
    m_transportMutex.lock();
    CommandBuffer &cmds(context->cmds);
    bool ok = m_transport->write(cmds.buffer(), cmds.size());
    cmds.reset();
    if (!ok)
        return false;
    logde(" - waiting for server to accept our buffer\n");
    m_transport->read(cmds.writableBuffer());
    logd(" - server consumed buffer, returned %d bytes\n", cmds.size());
    cmds.reset();

    m_transportMutex.unlock();
    return ok;
}

