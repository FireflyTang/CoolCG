//
//  CoolLib.h
//  Lession4
//
//  Created by 唐如麟 on 15/4/8.
//  Copyright (c) 2015年 唐如麟. All rights reserved.
//

#ifndef __CoolLib__
#define __CoolLib__
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math3d/math3d.h"
#include <functional>
#include <glut/glut.h>
#include "OpenGL/gl.h"
#include <SOIL/SOIL.h>

namespace CC{
	
	class classTex{
	public:
		void setAnisotropy(GLenum targe = GL_TEXTURE_2D);
		void setMipmap(GLenum target = GL_TEXTURE_2D);
		GLuint LoadMipmapTex(const char * filename);
		GLuint LoadCubeMapMipmapTex(const char *x_pos_file,	const char *x_neg_file,	const char *y_pos_file, 	const char *y_neg_file, const char *z_pos_file,	const char *z_neg_file);
	};
	
	class classControl{
	public:
		classControl();
		~classControl();
		virtual void keyMove(unsigned char key,int,int);
		virtual void keyPressOtherKey(unsigned char key,int,int);
		void keyRotateByCenter(int key,int,int);
		void keyRotateBySelf(int key,int,int);
		void setLookAt();
		void setPos(M3DVector3f Pos);
		void setUp(M3DVector3f Up);
		void setCenter(M3DVector3f Center);
		void setPos(GLfloat x,GLfloat y,GLfloat z);
		void setUp(GLfloat x,GLfloat y,GLfloat z);
		void setCenter(GLfloat x,GLfloat y,GLfloat z);
		M3DMatrix33f	LastRotationMartix33;
		M3DMatrix44f	LastRotationMartix44;
		M3DMatrix44f	TotalRotation44;
		M3DMatrix33f	TotalRotation33;
	private:
		M3DVector3f _Pos;
		M3DVector3f _Up;
		M3DVector3f _Center;
	};
}

#endif /* defined(__CoolLib__) */
