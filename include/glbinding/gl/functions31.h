#pragma once

#include <glbinding/nogl.h>
#include <glbinding/gl/functions.h>


namespace gl31
{

using gl::glAccum;
using gl::glActiveTexture;
using gl::glAlphaFunc;
using gl::glAreTexturesResident;
using gl::glArrayElement;
using gl::glAttachShader;
using gl::glBegin;
using gl::glBeginConditionalRender;
using gl::glBeginQuery;
using gl::glBeginTransformFeedback;
using gl::glBindAttribLocation;
using gl::glBindBuffer;
using gl::glBindBufferBase;
using gl::glBindBufferRange;
using gl::glBindFragDataLocation;
using gl::glBindFramebuffer;
using gl::glBindRenderbuffer;
using gl::glBindTexture;
using gl::glBindVertexArray;
using gl::glBitmap;
using gl::glBlendColor;
using gl::glBlendEquation;
using gl::glBlendEquationSeparate;
using gl::glBlendFunc;
using gl::glBlendFuncSeparate;
using gl::glBlitFramebuffer;
using gl::glBufferData;
using gl::glBufferSubData;
using gl::glCallList;
using gl::glCallLists;
using gl::glCheckFramebufferStatus;
using gl::glClampColor;
using gl::glClear;
using gl::glClearAccum;
using gl::glClearBufferfi;
using gl::glClearBufferfv;
using gl::glClearBufferiv;
using gl::glClearBufferuiv;
using gl::glClearColor;
using gl::glClearDepth;
using gl::glClearIndex;
using gl::glClearStencil;
using gl::glClientActiveTexture;
using gl::glClipPlane;
using gl::glColor3b;
using gl::glColor3bv;
using gl::glColor3d;
using gl::glColor3dv;
using gl::glColor3f;
using gl::glColor3fv;
using gl::glColor3i;
using gl::glColor3iv;
using gl::glColor3s;
using gl::glColor3sv;
using gl::glColor3ub;
using gl::glColor3ubv;
using gl::glColor3ui;
using gl::glColor3uiv;
using gl::glColor3us;
using gl::glColor3usv;
using gl::glColor4b;
using gl::glColor4bv;
using gl::glColor4d;
using gl::glColor4dv;
using gl::glColor4f;
using gl::glColor4fv;
using gl::glColor4i;
using gl::glColor4iv;
using gl::glColor4s;
using gl::glColor4sv;
using gl::glColor4ub;
using gl::glColor4ubv;
using gl::glColor4ui;
using gl::glColor4uiv;
using gl::glColor4us;
using gl::glColor4usv;
using gl::glColorMask;
using gl::glColorMaski;
using gl::glColorMaterial;
using gl::glColorPointer;
using gl::glCompileShader;
using gl::glCompressedTexImage1D;
using gl::glCompressedTexImage2D;
using gl::glCompressedTexImage3D;
using gl::glCompressedTexSubImage1D;
using gl::glCompressedTexSubImage2D;
using gl::glCompressedTexSubImage3D;
using gl::glCopyBufferSubData;
using gl::glCopyPixels;
using gl::glCopyTexImage1D;
using gl::glCopyTexImage2D;
using gl::glCopyTexSubImage1D;
using gl::glCopyTexSubImage2D;
using gl::glCopyTexSubImage3D;
using gl::glCreateProgram;
using gl::glCreateShader;
using gl::glCullFace;
using gl::glDeleteBuffers;
using gl::glDeleteFramebuffers;
using gl::glDeleteLists;
using gl::glDeleteProgram;
using gl::glDeleteQueries;
using gl::glDeleteRenderbuffers;
using gl::glDeleteShader;
using gl::glDeleteTextures;
using gl::glDeleteVertexArrays;
using gl::glDepthFunc;
using gl::glDepthMask;
using gl::glDepthRange;
using gl::glDetachShader;
using gl::glDisable;
using gl::glDisableClientState;
using gl::glDisableVertexAttribArray;
using gl::glDisablei;
using gl::glDrawArrays;
using gl::glDrawArraysInstanced;
using gl::glDrawBuffer;
using gl::glDrawBuffers;
using gl::glDrawElements;
using gl::glDrawElementsInstanced;
using gl::glDrawPixels;
using gl::glDrawRangeElements;
using gl::glEdgeFlag;
using gl::glEdgeFlagPointer;
using gl::glEdgeFlagv;
using gl::glEnable;
using gl::glEnableClientState;
using gl::glEnableVertexAttribArray;
using gl::glEnablei;
using gl::glEnd;
using gl::glEndConditionalRender;
using gl::glEndList;
using gl::glEndQuery;
using gl::glEndTransformFeedback;
using gl::glEvalCoord1d;
using gl::glEvalCoord1dv;
using gl::glEvalCoord1f;
using gl::glEvalCoord1fv;
using gl::glEvalCoord2d;
using gl::glEvalCoord2dv;
using gl::glEvalCoord2f;
using gl::glEvalCoord2fv;
using gl::glEvalMesh1;
using gl::glEvalMesh2;
using gl::glEvalPoint1;
using gl::glEvalPoint2;
using gl::glFeedbackBuffer;
using gl::glFinish;
using gl::glFlush;
using gl::glFlushMappedBufferRange;
using gl::glFogCoordPointer;
using gl::glFogCoordd;
using gl::glFogCoorddv;
using gl::glFogCoordf;
using gl::glFogCoordfv;
using gl::glFogf;
using gl::glFogfv;
using gl::glFogi;
using gl::glFogiv;
using gl::glFramebufferRenderbuffer;
using gl::glFramebufferTexture1D;
using gl::glFramebufferTexture2D;
using gl::glFramebufferTexture3D;
using gl::glFramebufferTextureLayer;
using gl::glFrontFace;
using gl::glFrustum;
using gl::glGenBuffers;
using gl::glGenFramebuffers;
using gl::glGenLists;
using gl::glGenQueries;
using gl::glGenRenderbuffers;
using gl::glGenTextures;
using gl::glGenVertexArrays;
using gl::glGenerateMipmap;
using gl::glGetActiveAttrib;
using gl::glGetActiveUniform;
using gl::glGetActiveUniformBlockName;
using gl::glGetActiveUniformBlockiv;
using gl::glGetActiveUniformName;
using gl::glGetActiveUniformsiv;
using gl::glGetAttachedShaders;
using gl::glGetAttribLocation;
using gl::glGetBooleani_v;
using gl::glGetBooleanv;
using gl::glGetBufferParameteriv;
using gl::glGetBufferPointerv;
using gl::glGetBufferSubData;
using gl::glGetClipPlane;
using gl::glGetCompressedTexImage;
using gl::glGetDoublev;
using gl::glGetError;
using gl::glGetFloatv;
using gl::glGetFragDataLocation;
using gl::glGetFramebufferAttachmentParameteriv;
using gl::glGetIntegeri_v;
using gl::glGetIntegerv;
using gl::glGetLightfv;
using gl::glGetLightiv;
using gl::glGetMapdv;
using gl::glGetMapfv;
using gl::glGetMapiv;
using gl::glGetMaterialfv;
using gl::glGetMaterialiv;
using gl::glGetPixelMapfv;
using gl::glGetPixelMapuiv;
using gl::glGetPixelMapusv;
using gl::glGetPointerv;
using gl::glGetPolygonStipple;
using gl::glGetProgramInfoLog;
using gl::glGetProgramiv;
using gl::glGetQueryObjectiv;
using gl::glGetQueryObjectuiv;
using gl::glGetQueryiv;
using gl::glGetRenderbufferParameteriv;
using gl::glGetShaderInfoLog;
using gl::glGetShaderSource;
using gl::glGetShaderiv;
using gl::glGetString;
using gl::glGetStringi;
using gl::glGetTexEnvfv;
using gl::glGetTexEnviv;
using gl::glGetTexGendv;
using gl::glGetTexGenfv;
using gl::glGetTexGeniv;
using gl::glGetTexImage;
using gl::glGetTexLevelParameterfv;
using gl::glGetTexLevelParameteriv;
using gl::glGetTexParameterIiv;
using gl::glGetTexParameterIuiv;
using gl::glGetTexParameterfv;
using gl::glGetTexParameteriv;
using gl::glGetTransformFeedbackVarying;
using gl::glGetUniformBlockIndex;
using gl::glGetUniformIndices;
using gl::glGetUniformLocation;
using gl::glGetUniformfv;
using gl::glGetUniformiv;
using gl::glGetUniformuiv;
using gl::glGetVertexAttribIiv;
using gl::glGetVertexAttribIuiv;
using gl::glGetVertexAttribPointerv;
using gl::glGetVertexAttribdv;
using gl::glGetVertexAttribfv;
using gl::glGetVertexAttribiv;
using gl::glHint;
using gl::glIndexMask;
using gl::glIndexPointer;
using gl::glIndexd;
using gl::glIndexdv;
using gl::glIndexf;
using gl::glIndexfv;
using gl::glIndexi;
using gl::glIndexiv;
using gl::glIndexs;
using gl::glIndexsv;
using gl::glIndexub;
using gl::glIndexubv;
using gl::glInitNames;
using gl::glInterleavedArrays;
using gl::glIsBuffer;
using gl::glIsEnabled;
using gl::glIsEnabledi;
using gl::glIsFramebuffer;
using gl::glIsList;
using gl::glIsProgram;
using gl::glIsQuery;
using gl::glIsRenderbuffer;
using gl::glIsShader;
using gl::glIsTexture;
using gl::glIsVertexArray;
using gl::glLightModelf;
using gl::glLightModelfv;
using gl::glLightModeli;
using gl::glLightModeliv;
using gl::glLightf;
using gl::glLightfv;
using gl::glLighti;
using gl::glLightiv;
using gl::glLineStipple;
using gl::glLineWidth;
using gl::glLinkProgram;
using gl::glListBase;
using gl::glLoadIdentity;
using gl::glLoadMatrixd;
using gl::glLoadMatrixf;
using gl::glLoadName;
using gl::glLoadTransposeMatrixd;
using gl::glLoadTransposeMatrixf;
using gl::glLogicOp;
using gl::glMap1d;
using gl::glMap1f;
using gl::glMap2d;
using gl::glMap2f;
using gl::glMapBuffer;
using gl::glMapBufferRange;
using gl::glMapGrid1d;
using gl::glMapGrid1f;
using gl::glMapGrid2d;
using gl::glMapGrid2f;
using gl::glMaterialf;
using gl::glMaterialfv;
using gl::glMateriali;
using gl::glMaterialiv;
using gl::glMatrixMode;
using gl::glMultMatrixd;
using gl::glMultMatrixf;
using gl::glMultTransposeMatrixd;
using gl::glMultTransposeMatrixf;
using gl::glMultiDrawArrays;
using gl::glMultiDrawElements;
using gl::glMultiTexCoord1d;
using gl::glMultiTexCoord1dv;
using gl::glMultiTexCoord1f;
using gl::glMultiTexCoord1fv;
using gl::glMultiTexCoord1i;
using gl::glMultiTexCoord1iv;
using gl::glMultiTexCoord1s;
using gl::glMultiTexCoord1sv;
using gl::glMultiTexCoord2d;
using gl::glMultiTexCoord2dv;
using gl::glMultiTexCoord2f;
using gl::glMultiTexCoord2fv;
using gl::glMultiTexCoord2i;
using gl::glMultiTexCoord2iv;
using gl::glMultiTexCoord2s;
using gl::glMultiTexCoord2sv;
using gl::glMultiTexCoord3d;
using gl::glMultiTexCoord3dv;
using gl::glMultiTexCoord3f;
using gl::glMultiTexCoord3fv;
using gl::glMultiTexCoord3i;
using gl::glMultiTexCoord3iv;
using gl::glMultiTexCoord3s;
using gl::glMultiTexCoord3sv;
using gl::glMultiTexCoord4d;
using gl::glMultiTexCoord4dv;
using gl::glMultiTexCoord4f;
using gl::glMultiTexCoord4fv;
using gl::glMultiTexCoord4i;
using gl::glMultiTexCoord4iv;
using gl::glMultiTexCoord4s;
using gl::glMultiTexCoord4sv;
using gl::glNewList;
using gl::glNormal3b;
using gl::glNormal3bv;
using gl::glNormal3d;
using gl::glNormal3dv;
using gl::glNormal3f;
using gl::glNormal3fv;
using gl::glNormal3i;
using gl::glNormal3iv;
using gl::glNormal3s;
using gl::glNormal3sv;
using gl::glNormalPointer;
using gl::glOrtho;
using gl::glPassThrough;
using gl::glPixelMapfv;
using gl::glPixelMapuiv;
using gl::glPixelMapusv;
using gl::glPixelStoref;
using gl::glPixelStorei;
using gl::glPixelTransferf;
using gl::glPixelTransferi;
using gl::glPixelZoom;
using gl::glPointParameterf;
using gl::glPointParameterfv;
using gl::glPointParameteri;
using gl::glPointParameteriv;
using gl::glPointSize;
using gl::glPolygonMode;
using gl::glPolygonOffset;
using gl::glPolygonStipple;
using gl::glPopAttrib;
using gl::glPopClientAttrib;
using gl::glPopMatrix;
using gl::glPopName;
using gl::glPrimitiveRestartIndex;
using gl::glPrioritizeTextures;
using gl::glPushAttrib;
using gl::glPushClientAttrib;
using gl::glPushMatrix;
using gl::glPushName;
using gl::glRasterPos2d;
using gl::glRasterPos2dv;
using gl::glRasterPos2f;
using gl::glRasterPos2fv;
using gl::glRasterPos2i;
using gl::glRasterPos2iv;
using gl::glRasterPos2s;
using gl::glRasterPos2sv;
using gl::glRasterPos3d;
using gl::glRasterPos3dv;
using gl::glRasterPos3f;
using gl::glRasterPos3fv;
using gl::glRasterPos3i;
using gl::glRasterPos3iv;
using gl::glRasterPos3s;
using gl::glRasterPos3sv;
using gl::glRasterPos4d;
using gl::glRasterPos4dv;
using gl::glRasterPos4f;
using gl::glRasterPos4fv;
using gl::glRasterPos4i;
using gl::glRasterPos4iv;
using gl::glRasterPos4s;
using gl::glRasterPos4sv;
using gl::glReadBuffer;
using gl::glReadPixels;
using gl::glRectd;
using gl::glRectdv;
using gl::glRectf;
using gl::glRectfv;
using gl::glRecti;
using gl::glRectiv;
using gl::glRects;
using gl::glRectsv;
using gl::glRenderMode;
using gl::glRenderbufferStorage;
using gl::glRenderbufferStorageMultisample;
using gl::glRotated;
using gl::glRotatef;
using gl::glSampleCoverage;
using gl::glScaled;
using gl::glScalef;
using gl::glScissor;
using gl::glSecondaryColor3b;
using gl::glSecondaryColor3bv;
using gl::glSecondaryColor3d;
using gl::glSecondaryColor3dv;
using gl::glSecondaryColor3f;
using gl::glSecondaryColor3fv;
using gl::glSecondaryColor3i;
using gl::glSecondaryColor3iv;
using gl::glSecondaryColor3s;
using gl::glSecondaryColor3sv;
using gl::glSecondaryColor3ub;
using gl::glSecondaryColor3ubv;
using gl::glSecondaryColor3ui;
using gl::glSecondaryColor3uiv;
using gl::glSecondaryColor3us;
using gl::glSecondaryColor3usv;
using gl::glSecondaryColorPointer;
using gl::glSelectBuffer;
using gl::glShadeModel;
using gl::glShaderSource;
using gl::glStencilFunc;
using gl::glStencilFuncSeparate;
using gl::glStencilMask;
using gl::glStencilMaskSeparate;
using gl::glStencilOp;
using gl::glStencilOpSeparate;
using gl::glTexBuffer;
using gl::glTexCoord1d;
using gl::glTexCoord1dv;
using gl::glTexCoord1f;
using gl::glTexCoord1fv;
using gl::glTexCoord1i;
using gl::glTexCoord1iv;
using gl::glTexCoord1s;
using gl::glTexCoord1sv;
using gl::glTexCoord2d;
using gl::glTexCoord2dv;
using gl::glTexCoord2f;
using gl::glTexCoord2fv;
using gl::glTexCoord2i;
using gl::glTexCoord2iv;
using gl::glTexCoord2s;
using gl::glTexCoord2sv;
using gl::glTexCoord3d;
using gl::glTexCoord3dv;
using gl::glTexCoord3f;
using gl::glTexCoord3fv;
using gl::glTexCoord3i;
using gl::glTexCoord3iv;
using gl::glTexCoord3s;
using gl::glTexCoord3sv;
using gl::glTexCoord4d;
using gl::glTexCoord4dv;
using gl::glTexCoord4f;
using gl::glTexCoord4fv;
using gl::glTexCoord4i;
using gl::glTexCoord4iv;
using gl::glTexCoord4s;
using gl::glTexCoord4sv;
using gl::glTexCoordPointer;
using gl::glTexEnvf;
using gl::glTexEnvfv;
using gl::glTexEnvi;
using gl::glTexEnviv;
using gl::glTexGend;
using gl::glTexGendv;
using gl::glTexGenf;
using gl::glTexGenfv;
using gl::glTexGeni;
using gl::glTexGeniv;
using gl::glTexImage1D;
using gl::glTexImage2D;
using gl::glTexImage3D;
using gl::glTexParameterIiv;
using gl::glTexParameterIuiv;
using gl::glTexParameterf;
using gl::glTexParameterfv;
using gl::glTexParameteri;
using gl::glTexParameteriv;
using gl::glTexSubImage1D;
using gl::glTexSubImage2D;
using gl::glTexSubImage3D;
using gl::glTransformFeedbackVaryings;
using gl::glTranslated;
using gl::glTranslatef;
using gl::glUniform1f;
using gl::glUniform1fv;
using gl::glUniform1i;
using gl::glUniform1iv;
using gl::glUniform1ui;
using gl::glUniform1uiv;
using gl::glUniform2f;
using gl::glUniform2fv;
using gl::glUniform2i;
using gl::glUniform2iv;
using gl::glUniform2ui;
using gl::glUniform2uiv;
using gl::glUniform3f;
using gl::glUniform3fv;
using gl::glUniform3i;
using gl::glUniform3iv;
using gl::glUniform3ui;
using gl::glUniform3uiv;
using gl::glUniform4f;
using gl::glUniform4fv;
using gl::glUniform4i;
using gl::glUniform4iv;
using gl::glUniform4ui;
using gl::glUniform4uiv;
using gl::glUniformBlockBinding;
using gl::glUniformMatrix2fv;
using gl::glUniformMatrix2x3fv;
using gl::glUniformMatrix2x4fv;
using gl::glUniformMatrix3fv;
using gl::glUniformMatrix3x2fv;
using gl::glUniformMatrix3x4fv;
using gl::glUniformMatrix4fv;
using gl::glUniformMatrix4x2fv;
using gl::glUniformMatrix4x3fv;
using gl::glUnmapBuffer;
using gl::glUseProgram;
using gl::glValidateProgram;
using gl::glVertex2d;
using gl::glVertex2dv;
using gl::glVertex2f;
using gl::glVertex2fv;
using gl::glVertex2i;
using gl::glVertex2iv;
using gl::glVertex2s;
using gl::glVertex2sv;
using gl::glVertex3d;
using gl::glVertex3dv;
using gl::glVertex3f;
using gl::glVertex3fv;
using gl::glVertex3i;
using gl::glVertex3iv;
using gl::glVertex3s;
using gl::glVertex3sv;
using gl::glVertex4d;
using gl::glVertex4dv;
using gl::glVertex4f;
using gl::glVertex4fv;
using gl::glVertex4i;
using gl::glVertex4iv;
using gl::glVertex4s;
using gl::glVertex4sv;
using gl::glVertexAttrib1d;
using gl::glVertexAttrib1dv;
using gl::glVertexAttrib1f;
using gl::glVertexAttrib1fv;
using gl::glVertexAttrib1s;
using gl::glVertexAttrib1sv;
using gl::glVertexAttrib2d;
using gl::glVertexAttrib2dv;
using gl::glVertexAttrib2f;
using gl::glVertexAttrib2fv;
using gl::glVertexAttrib2s;
using gl::glVertexAttrib2sv;
using gl::glVertexAttrib3d;
using gl::glVertexAttrib3dv;
using gl::glVertexAttrib3f;
using gl::glVertexAttrib3fv;
using gl::glVertexAttrib3s;
using gl::glVertexAttrib3sv;
using gl::glVertexAttrib4Nbv;
using gl::glVertexAttrib4Niv;
using gl::glVertexAttrib4Nsv;
using gl::glVertexAttrib4Nub;
using gl::glVertexAttrib4Nubv;
using gl::glVertexAttrib4Nuiv;
using gl::glVertexAttrib4Nusv;
using gl::glVertexAttrib4bv;
using gl::glVertexAttrib4d;
using gl::glVertexAttrib4dv;
using gl::glVertexAttrib4f;
using gl::glVertexAttrib4fv;
using gl::glVertexAttrib4iv;
using gl::glVertexAttrib4s;
using gl::glVertexAttrib4sv;
using gl::glVertexAttrib4ubv;
using gl::glVertexAttrib4uiv;
using gl::glVertexAttrib4usv;
using gl::glVertexAttribI1i;
using gl::glVertexAttribI1iv;
using gl::glVertexAttribI1ui;
using gl::glVertexAttribI1uiv;
using gl::glVertexAttribI2i;
using gl::glVertexAttribI2iv;
using gl::glVertexAttribI2ui;
using gl::glVertexAttribI2uiv;
using gl::glVertexAttribI3i;
using gl::glVertexAttribI3iv;
using gl::glVertexAttribI3ui;
using gl::glVertexAttribI3uiv;
using gl::glVertexAttribI4bv;
using gl::glVertexAttribI4i;
using gl::glVertexAttribI4iv;
using gl::glVertexAttribI4sv;
using gl::glVertexAttribI4ubv;
using gl::glVertexAttribI4ui;
using gl::glVertexAttribI4uiv;
using gl::glVertexAttribI4usv;
using gl::glVertexAttribIPointer;
using gl::glVertexAttribPointer;
using gl::glVertexPointer;
using gl::glViewport;
using gl::glWindowPos2d;
using gl::glWindowPos2dv;
using gl::glWindowPos2f;
using gl::glWindowPos2fv;
using gl::glWindowPos2i;
using gl::glWindowPos2iv;
using gl::glWindowPos2s;
using gl::glWindowPos2sv;
using gl::glWindowPos3d;
using gl::glWindowPos3dv;
using gl::glWindowPos3f;
using gl::glWindowPos3fv;
using gl::glWindowPos3i;
using gl::glWindowPos3iv;
using gl::glWindowPos3s;
using gl::glWindowPos3sv;

} // namespace gl31
