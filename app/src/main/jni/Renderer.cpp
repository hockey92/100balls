#include "Renderer.h"

//GLuint Renderer::program = 0;

const char Renderer::VERTEX_SHADER[] =
                "attribute vec3 pos;   \n"
                "uniform mat4 projection;   \n"
                "void main()                 \n"
                "{                           \n"
                "     gl_Position = projection * vec4(pos, 1.0); \n"
                "}                           \n";

const char Renderer::FRAGMENT_SHADER[] =
                "precision mediump float;\n"
                "varying vec4 vColor;\n"
                "void main() {\n"
                "    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);//vColor;\n"
                "}\n";

void Renderer::render(float* pm) {
    if (!program) {
        program = createProgram(VERTEX_SHADER, FRAGMENT_SHADER);
        mPosAttrib = glGetAttribLocation(program, "pos");
        mColorAttrib = glGetAttribLocation(program, "color");
        mScaleRotUniform = glGetUniformLocation(program, "scaleRot");
        mOffsetUniform = glGetUniformLocation(program, "offset");
        projection = glGetUniformLocation(program, "projection");
    }
    glUseProgram(program);
    innerRender(pm);
}

GLuint Renderer::createShader(GLenum shaderType, const char *src) {
    GLuint shader = glCreateShader(shaderType);
//    if (!shader) {
//        checkGlError("glCreateShader");
//        return 0;
//    }
    glShaderSource(shader, 1, &src, NULL);

//    GLint compiled = GL_FALSE;
    glCompileShader(shader);
//    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
//    if (!compiled) {
//        GLint infoLogLen = 0;
//        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
//        if (infoLogLen > 0) {
//            GLchar *infoLog = (GLchar *) malloc(infoLogLen);
//            if (infoLog) {
//                glGetShaderInfoLog(shader, infoLogLen, NULL, infoLog);
//                ALOGE("Could not compile %s shader:\n%s\n",
//                      shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment",
//                      infoLog);
//                free(infoLog);
//            }
//        }
//        glDeleteShader(shader);
//        return 0;
//    }

    return shader;
}

GLuint Renderer::createProgram(const char *vtxSrc, const char *fragSrc) {
    GLuint vtxShader = 0;
    GLuint fragShader = 0;
    GLuint program = 0;
//    GLint linked = GL_FALSE;

    vtxShader = createShader(GL_VERTEX_SHADER, vtxSrc);
    if (!vtxShader)
        goto exit;

    fragShader = createShader(GL_FRAGMENT_SHADER, fragSrc);
    if (!fragShader)
        goto exit;

    program = glCreateProgram();
    if (!program) {
//        checkGlError("glCreateProgram");
        goto exit;
    }
    glAttachShader(program, vtxShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);
//    glGetProgramiv(program, GL_LINK_STATUS, &linked);
//    if (!linked) {
//        ALOGE("Could not link program");
//        GLint infoLogLen = 0;
//        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
//        if (infoLogLen) {
//            GLchar *infoLog = (GLchar *) malloc(infoLogLen);
//            if (infoLog) {
//                glGetProgramInfoLog(program, infoLogLen, NULL, infoLog);
//                ALOGE("Could not link program:\n%s\n", infoLog);
//                free(infoLog);
//            }
//        }
//        glDeleteProgram(program);
//        program = 0;
//    }

    exit:
    glDeleteShader(vtxShader);
    glDeleteShader(fragShader);
    return program;
}
