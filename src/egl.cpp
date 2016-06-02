/*
    Copyright (c) 2015, Gunnar Sletta <gunnar@sletta.org>
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

#include <EGL/egl.h>

#include <iostream>

// EGL 1.0 functions
struct EGLDisplayImpl
{
    bool initialized = false;
};

struct EGLContextImpl
{
    EGLint configId = 0;

};

struct EGLThreadState
{
    EGLint error = EGL_SUCCESS;
    EGLDisplay display = 0;
    EGLContext context = 0;

    EGLSurface drawSurface = 0;
    EGLSurface readSurface = 0;
};

static EGLThreadState *getThreadState()
{
    __thread static EGLThreadState state;
    return &state;
}

static EGLDisplayImpl *getDefaultDisplay()
{
    __thread static EGLDisplayImpl global;
    return &global;
}

#define ABORT_ON_BAD_DISPLAY_WITH(returnOnFail)       \
    if (dpy != getDefaultDisplay()) {                 \
        threadState->error = EGL_BAD_DISPLAY;    \
        return returnOnFail;                          \
    }

#define ABORT_WITH_BAD_PARAM_IF_NULL(param, returnOnFail)    \
    if (!param) {                                            \
        threadState->error = EGL_BAD_PARAMETER;         \
        return returnOnFail;                                 \
    }

#define GET_THREAD_STATE_AND_ASSUME_SUCCESS             \
    EGLThreadState *threadState = getThreadState();     \
    threadState->error = EGL_SUCCESS




EGLAPI EGLDisplay EGLAPIENTRY eglGetDisplay(EGLNativeDisplayType display_id)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    if (display_id == EGL_DEFAULT_DISPLAY)
        return getDefaultDisplay();
    return EGL_NO_DISPLAY;
}


EGLAPI EGLBoolean EGLAPIENTRY eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(false);
    getDefaultDisplay()->initialized = true;
    *major = 1;
    *minor = 0;
    return true;
}


EGLAPI EGLBoolean EGLAPIENTRY eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(false);
    std::cerr << __PRETTY_FUNCTION__ << ": not implemented!" << std::endl;
    return false;
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
    std::cerr << __PRETTY_FUNCTION__ << ": not implemented!" << std::endl;
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
    std::cerr << __PRETTY_FUNCTION__ << ": not implemented!" << std::endl;
    return nullptr;
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
    std::cerr << __PRETTY_FUNCTION__ << ": not implemented!" << std::endl;
    return nullptr;
}


EGLAPI EGLBoolean EGLAPIENTRY eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(false);
    std::cerr << __PRETTY_FUNCTION__ << ": not implemented!" << std::endl;
    return false;
}


EGLAPI EGLBoolean EGLAPIENTRY eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(false);
    std::cerr << __PRETTY_FUNCTION__ << ": not implemented!" << std::endl;
    return false;
}


EGLAPI EGLBoolean EGLAPIENTRY eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(false);
    std::cerr << __PRETTY_FUNCTION__ << ": not implemented!" << std::endl;
    return false;
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
    return threadState->display;
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
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    return threadState->error;
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
    threadState->context = ctx;
    return true;
}


EGLAPI EGLBoolean EGLAPIENTRY eglQueryContext(EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint *value)
{
    GET_THREAD_STATE_AND_ASSUME_SUCCESS;
    ABORT_ON_BAD_DISPLAY_WITH(false);
    ABORT_WITH_BAD_PARAM_IF_NULL(ctx, false);
    ABORT_WITH_BAD_PARAM_IF_NULL(value, false);

    EGLContextImpl *context = (EGLContextImpl *) ctx;
    switch (attribute) {
        case EGL_CONFIG_ID:                 *value = context->configId;     return true;
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

