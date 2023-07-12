#include <string.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <glvnd/libglxabi.h>

#include "glxglvnd.h"

const __GLXapiExports *__glXGLVNDAPIExports;


GLXContext gl4es_glXCreateContext(Display *dpy,
                            XVisualInfo *visual,
                            GLXContext shareList,
                            Bool direct);

GLXContext gl4es_glXCreateContextAttribsARB(Display *display, GLXFBConfig config,
                                      GLXContext share_context, Bool direct,
                                      const int *attrib_list);

void gl4es_glXSwapIntervalEXT(Display *display, int drawable, int interval);
void gl4es_glXSwapInterval(int interval);

// GLX 1.1?
Bool gl4es_glXIsDirect(Display * display, GLXContext ctx);
Bool gl4es_glXMakeCurrent(Display *display, GLXDrawable drawable, GLXContext context);
Bool gl4es_glXQueryExtension(Display *display, int *errorBase, int *eventBase);
Bool gl4es_glXQueryVersion(Display *display, int *major, int *minor);
const char *gl4es_glXGetClientString(Display *display, int name);
const char *gl4es_glXQueryExtensionsString(Display *display, int screen);
const char *gl4es_glXQueryServerString(Display *display, int screen, int name);
GLXDrawable gl4es_glXGetCurrentDrawable();
int gl4es_glXGetConfig(Display *display, XVisualInfo *visual, int attribute, int *value);
void gl4es_glXCopyContext(Display *display, GLXContext src, GLXContext dst, GLuint mask);
void gl4es_glXDestroyContext(Display *display, GLXContext ctx);
void gl4es_glXSwapBuffers(Display *display, GLXDrawable drawable);
void gl4es_glXUseXFont(Font font, int first, int count, int listBase);
void gl4es_glXWaitGL();
void gl4es_glXWaitX();
XVisualInfo *gl4es_glXChooseVisual(Display *display, int screen, int *attributes);
int gl4es_glXQueryDrawable(Display *dpy, GLXDrawable draw, int attribute,	unsigned int *value);

// GLX 1.2
Display *gl4es_glXGetCurrentDisplay();

// GLX 1.3
GLXContext gl4es_glXGetCurrentContext();
XVisualInfo *gl4es_glXGetVisualFromFBConfig(Display *display, GLXFBConfig config);
GLXFBConfig *gl4es_glXChooseFBConfig(Display *display, int screen, const int *attrib_list, int *count);
GLXFBConfig *gl4es_glXGetFBConfigs(Display *display, int screen, int *count);
int gl4es_glXGetFBConfigAttrib(Display *display, GLXFBConfig config, int attribute, int *value);
int gl4es_glXQueryContext(Display *display, GLXContext ctx, int attribute, int *value);
GLXFBConfig *gl4es_glXChooseFBConfigSGIX(Display *display, int screen, const int *attrib_list, int *count);

Window gl4es_glXCreateWindow(Display *display, GLXFBConfig config, Window win, int *attrib_list);
void gl4es_glXDestroyWindow(Display *display, void *win);

Bool gl4es_glXMakeContextCurrent(Display *display, int drawable, int readable, GLXContext context);
GLXContext gl4es_glXCreateNewContext(Display *display, GLXFBConfig config, int render_type, GLXContext share_list, Bool is_direct);

void gl4es_glXDestroyPbuffer(Display * dpy, GLXPbuffer pbuf);
GLXPbuffer gl4es_glXCreatePbuffer(Display * dpy, GLXFBConfig config, const int * attrib_list);

GLXPixmap gl4es_glXCreatePixmap(Display * dpy, GLXFBConfig config, Pixmap pixmap, const int * attrib_list);
void gl4es_glXDestroyPixmap(Display *display, void *pixmap);
GLXPixmap gl4es_glXCreateGLXPixmap(Display *display, XVisualInfo * visual, Pixmap pixmap);
void gl4es_glXDestroyGLXPixmap(Display *display, void *pixmap);

GLXContext gl4es_glXCreateContextAttribs(Display *dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int *attrib_list);

void* gl4es_GetProcAddress(const char *procName);

#define ARRAY_LEN(_arr) (sizeof(_arr)/sizeof((_arr)[0]))

static const struct {
    const char *name;
    void *addr;
} procAddresses[] = {
#define PROC_ENTRY(name) { #name, (void *)gl4es_ ## name }
    PROC_ENTRY(glXChooseVisual),
    PROC_ENTRY(glXCopyContext),
    PROC_ENTRY(glXCreateContext),
    PROC_ENTRY(glXCreateGLXPixmap),
    PROC_ENTRY(glXDestroyContext),
    PROC_ENTRY(glXDestroyGLXPixmap),
    PROC_ENTRY(glXGetConfig),
    PROC_ENTRY(glXIsDirect),
    PROC_ENTRY(glXMakeCurrent),
    PROC_ENTRY(glXSwapBuffers),
    PROC_ENTRY(glXUseXFont),
    PROC_ENTRY(glXWaitGL),
    PROC_ENTRY(glXWaitX),
    PROC_ENTRY(glXQueryServerString),
    PROC_ENTRY(glXGetClientString),
    PROC_ENTRY(glXQueryExtensionsString),
    PROC_ENTRY(glXChooseFBConfig),
    PROC_ENTRY(glXCreateNewContext),
    PROC_ENTRY(glXCreatePbuffer),
    PROC_ENTRY(glXCreatePixmap),
    PROC_ENTRY(glXCreateWindow),
    PROC_ENTRY(glXDestroyPbuffer),
    PROC_ENTRY(glXDestroyPixmap),
    PROC_ENTRY(glXDestroyWindow),
    PROC_ENTRY(glXGetFBConfigAttrib),
    PROC_ENTRY(glXGetFBConfigs),
    //PROC_ENTRY(glXGetSelectedEvent),
    PROC_ENTRY(glXGetVisualFromFBConfig),
    PROC_ENTRY(glXMakeContextCurrent),
    PROC_ENTRY(glXQueryContext),
    PROC_ENTRY(glXQueryDrawable),
    //PROC_ENTRY(glXSelectEvent),
    PROC_ENTRY(glXCreateContextAttribsARB),
#undef PROC_ENTRY
};

void *gl4es_glXGetProcAddress(const char *name);

static Bool __glXGLVNDIsScreenSupported(Display *dpy, int screen)
{
    return True;
}

static void *__glXGLVNDGetProcAddress(const GLubyte *procName)
{
    return gl4es_glXGetProcAddress(procName);
}

static void *__glXGLVNDGetDispatchAddress(const GLubyte *procName)
{
    for (int i = 0; i < ARRAY_LEN(procAddresses); i++) {
        if (!strcmp(procAddresses[i].name, (const char *)procName)) {
            return procAddresses[i].addr;
        }
    }

    return gl4es_GetProcAddress(procName);
}

static void __glXGLVNDSetDispatchIndex(const GLubyte *procName, int index)
{
    return;
}

__attribute__((__visibility__("default"))) Bool __glx_Main(uint32_t version, const __GLXapiExports *exports,
                          __GLXvendorInfo *vendor, __GLXapiImports *imports)
{
    static Bool initDone = False;

    if (GLX_VENDOR_ABI_GET_MAJOR_VERSION(version) !=
        GLX_VENDOR_ABI_MAJOR_VERSION ||
        GLX_VENDOR_ABI_GET_MINOR_VERSION(version) <
        GLX_VENDOR_ABI_MINOR_VERSION)
        return False;

    if (!initDone) {
        initDone = True;
        __glXGLVNDAPIExports = exports;

        imports->isScreenSupported = __glXGLVNDIsScreenSupported;
        imports->getProcAddress = __glXGLVNDGetProcAddress;
        imports->getDispatchAddress = __glXGLVNDGetDispatchAddress;
        imports->setDispatchIndex = __glXGLVNDSetDispatchIndex;
        imports->notifyError = NULL;
        imports->isPatchSupported = NULL;
        imports->initiatePatch = NULL;
    }

    return True;
}
