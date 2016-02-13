#include "Shader.h"

#include "common.hpp"
//#include "indexbuf.hpp"
#include "Shader.h"
//#include "vertexbuf.hpp"

Shader::Shader() {
    vertShader = fragShader = program = 0;
//    mMVPMatrixLoc = -1;
//    mPositionAttribLoc = -1;
//    mPreparedVertexBuf = NULL;
}

Shader::~Shader() {
    if (vertShader) {
        glDeleteShader(vertShader);
        vertShader = 0;
    }
    if (fragShader) {
        glDeleteShader(fragShader);
        fragShader = 0;
    }
    if (program) {
        glDeleteProgram(program);
        program = 0;
    }
}

static void _printShaderLog(GLuint shader) {
    char buf[2048];
    memset(buf, 0, sizeof(buf));
    LOGE("*** Getting info log for shader %u", shader);
    glGetShaderInfoLog(shader, sizeof(buf) - 1, NULL, buf);
    LOGE("*** Info log:\n%s", buf);
}

static void _printProgramLog(GLuint program) {
    char buf[2048];
    memset(buf, 0, sizeof(buf));
    LOGE("*** Getting info log for program %u", program);
    glGetProgramInfoLog(program, sizeof(buf) - 1, NULL, buf);
    LOGE("*** Info log:\n%s", buf);
}

void Shader::compile() {
    const char *vsrc = 0, *fsrc = 0;
    GLint status = 0;

    LOGD("Compiling shader.");
    LOGD("Shader name: %s", getShaderName());

    vsrc = getVertexShaderSource();
    fsrc = getFragmentShaderSource();

    vertShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!vertShader || !fragShader) {
        LOGE("*** Failed to create shader.");
        ABORT_GAME;
    }
    glShaderSource(vertShader, 1, &vsrc, NULL);
    glCompileShader(vertShader);
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        LOGE("*** Vertex shader compilation failed.");
        _printShaderLog(vertShader);
        ABORT_GAME;
    }
    LOGD("Vertex shader compilation succeeded.");

    glShaderSource(fragShader, 1, &fsrc, NULL);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        LOGE("*** Fragment shader compilation failed, %d", status);
        _printShaderLog(fragShader);
        ABORT_GAME;
    }
    LOGD("Fragment shader compilation succeeded.");

    program = glCreateProgram();
    if (!program) {
        LOGE("*** Failed to create program");
        _printProgramLog(program);
        ABORT_GAME;
    }

    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == 0) {
        LOGE("*** Shader program link failed, %d", status);
        ABORT_GAME;
    }
    LOGD("Program linking succeeded.");

    glUseProgram(program);
    MVPMatrix = glGetUniformLocation(program, "projection");
    if (MVPMatrix < 0) {
        LOGE("*** Couldn't get shader's u_MVP matrix location from shader.");
        ABORT_GAME;
    }
    positionAttrib = glGetAttribLocation(program, "a_Position");
    if (positionAttrib < 0) {
        LOGE("*** Couldn't get shader's a_Position attribute location.");
        ABORT_GAME;
    }
    LOGD("Shader compilation/linking successful.");
    glUseProgram(0);
}

void Shader::bindShader() {
    if (program == 0) {
        LOGW("!!! WARNING: attempt to use shader before compiling.");
        LOGW("!!! Compiling now. Shader: %s", getShaderName());
        compile();
    }
    glUseProgram(program);
}

void Shader::unbindShader() {
    glUseProgram(0);
}

// To be called by child classes only.
//void Shader::PushMVPMatrix(glm::mat4 *mat) {
//    MY_ASSERT(mMVPMatrixLoc >= 0);
//    glUniformMatrix4fv(mMVPMatrixLoc, 1, GL_FALSE, glm::value_ptr(*mat));
//}

// To be called by child classes only.
void Shader::PushPositions(int vbo_offset, int stride) {
//    MY_ASSERT(mPositionAttribLoc >= 0);
//    glVertexAttribPointer(mPositionAttribLoc, 3, GL_FLOAT, GL_FALSE, stride,
//                          BUFFER_OFFSET(vbo_offset));
//    glEnableVertexAttribArray(mPositionAttribLoc);
}

void Shader::beginRender(/*VertexBuf *vbuf*/) {
    // Activate shader
    bindShader();

    // bind geometry's VBO
//    vbuf->BindBuffer();

    // push positions to shader
//    PushPositions(vbuf->GetPositionsOffset(), vbuf->GetStride());

    // store geometry
//    mPreparedVertexBuf = vbuf;
}

//void Shader::Render(IndexBuf *ibuf, glm::mat4* mvpMat) {
//    MY_ASSERT(mPreparedVertexBuf != NULL);
//
//    // push MVP matrix to shader
//    PushMVPMatrix(mvpMat);
//
//    if (ibuf) {
//        // draw with index buffer
//        ibuf->BindBuffer();
//        glDrawElements(mPreparedVertexBuf->GetPrimitive(), ibuf->GetCount(), GL_UNSIGNED_SHORT,
//                       BUFFER_OFFSET(0));
//        ibuf->UnbindBuffer();
//    } else {
//        // draw straight from vertex buffer
//        glDrawArrays(mPreparedVertexBuf->GetPrimitive(), 0, mPreparedVertexBuf->GetCount());
//    }
//}

void Shader::endRender() {
//    if (mPreparedVertexBuf) {
//        mPreparedVertexBuf->UnbindBuffer();
//        mPreparedVertexBuf = NULL;
//    }
}