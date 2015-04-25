//
//  CoolLib.cpp
//  Lession4
//
//  Created by 唐如麟 on 15/4/8.
//  Copyright (c) 2015年 唐如麟. All rights reserved.
//

#include "CoolCG.h"

const GLfloat RotateInitSpeed = 0.2;
const GLfloat RotateMaxSpeed = RotateInitSpeed * 20;
const GLfloat RotateSpeedDelta = 1.4;

const GLfloat MoveInitSpeed = 5;
const GLfloat MoveMaxSpeed = MoveInitSpeed * 3;
const GLfloat MoveSpeedDelta = 1.1;

CC::classControl::
classControl(){
	setPos(1,1,1);
	setUp(-1,1,-1);
	setCenter(0,0,0);
	m3dLoadIdentity44(TotalRotation44);
	m3dLoadIdentity33(TotalRotation33);
};

CC::classControl::
~classControl(){
};

void
CC::classControl::
setLookAt(){
	gluLookAt(_Pos[0],_Pos[1],_Pos[2], _Center[0], _Center[1], _Center[2], _Up[0], _Up[1], _Up[2]);
}

void
CC::classControl::
keyRotateByCenter(int key,int,int){
	M3DVector3f     up0;
	M3DVector3f     view0;
	M3DVector3f     right;
	M3DVector3f     view;
	M3DMatrix33f    RotationMartix33;
	M3DMatrix44f    RotationMartix44;
	M3DVector3f     axis;
	
	static GLfloat	angle;
	static GLint last_key;
	
	if (!((key==GLUT_KEY_UP)
		  ||(key==GLUT_KEY_DOWN)
		  ||(key==GLUT_KEY_LEFT)
		  ||(key==GLUT_KEY_RIGHT)))return;
	
	m3dSubtractVectors3(view0, _Pos, _Center);
	m3dCrossProduct3(right, _Up, view0);
	
	//绕right旋转
	if(key==GLUT_KEY_UP || key==GLUT_KEY_DOWN){
		if(key==GLUT_KEY_UP)   {
			if(last_key==GLUT_KEY_UP)
				angle = fmin(RotateMaxSpeed,angle*RotateSpeedDelta);
			else
				angle = RotateInitSpeed;
		}
		if(key==GLUT_KEY_DOWN)  {
			if(last_key==GLUT_KEY_DOWN)
				angle = fmax(-RotateMaxSpeed,angle*RotateSpeedDelta);
			else
				angle = -RotateInitSpeed;
		}
		m3dCopyVector3(axis, right);
	}
	
	//绕up旋转
	if(key==GLUT_KEY_LEFT || key==GLUT_KEY_RIGHT){
		if(key==GLUT_KEY_LEFT)    {
			if(last_key==GLUT_KEY_LEFT)
				angle = fmin(RotateMaxSpeed,angle*RotateSpeedDelta);
			else
				angle = RotateInitSpeed;
		}
		if(key==GLUT_KEY_RIGHT)  {
			if(last_key==GLUT_KEY_RIGHT)
				angle = fmax(-RotateMaxSpeed,angle*RotateSpeedDelta);
			else
				angle = -RotateInitSpeed;
		}
		m3dCopyVector3(axis, _Up);
	}
	
	m3dRotationMatrix33(RotationMartix33,angle/180*M_PI,axis[0], axis[1], axis[2]);
	m3dRotateVector(view,view0,RotationMartix33);
	m3dCopyVector3(up0, _Up);
	m3dRotateVector(_Up, up0, RotationMartix33);
	m3dAddVectors3(_Pos, _Center, view);
	
	last_key = key;
	m3dCopyMatrix33(LastRotationMartix33,RotationMartix33);
	
	M3DMatrix33f TotalRotation0;
	m3dCopyMatrix33(TotalRotation0,TotalRotation33);
	m3dMatrixMultiply33(TotalRotation33, TotalRotation0, RotationMartix33);
	
	m3dRotationMatrix44(RotationMartix44,angle/180*M_PI,axis[0], axis[1], axis[2]);
	m3dCopyMatrix44(LastRotationMartix44,RotationMartix44);
	M3DMatrix44f TotalRotation1;
	m3dCopyMatrix44(TotalRotation1,TotalRotation44);
	m3dMatrixMultiply44(TotalRotation44, TotalRotation1, RotationMartix44);
	
	glutPostRedisplay();
	return;
}

void
CC::classControl::
keyRotateBySelf(int key,int,int){
	M3DVector3f     up0;
	M3DVector3f     view0;
	M3DVector3f     right;
	M3DVector3f     view;
	M3DMatrix33f    RotationMartix33;
	M3DMatrix44f    RotationMartix44;
	M3DVector3f     axis;
	
	static GLfloat	angle;
	static GLint last_key;
	
	if (!((key==GLUT_KEY_UP)
		  ||(key==GLUT_KEY_DOWN)
		  ||(key==GLUT_KEY_LEFT)
		  ||(key==GLUT_KEY_RIGHT)))return;
	
	m3dSubtractVectors3(view0, _Pos, _Center);
	m3dCrossProduct3(right, _Up, view0);
	
	//绕right旋转
	if(key==GLUT_KEY_UP || key==GLUT_KEY_DOWN){
		if(key==GLUT_KEY_UP)    {
			if(last_key==GLUT_KEY_UP)
				angle = fmin(RotateMaxSpeed,angle*RotateSpeedDelta);
			else
				angle = RotateInitSpeed;
		}
		if(key==GLUT_KEY_DOWN)  {
			if(last_key==GLUT_KEY_DOWN)
				angle = fmax(-RotateMaxSpeed,angle*RotateSpeedDelta);
			else
				angle = -RotateInitSpeed;
		}
		
		m3dCopyVector3(axis, right);
	}
	
	//绕up旋转
	if(key==GLUT_KEY_LEFT || key==GLUT_KEY_RIGHT){
		if(key==GLUT_KEY_LEFT)    {
			if(last_key==GLUT_KEY_LEFT)
				angle = fmin(RotateMaxSpeed,angle*RotateSpeedDelta);
			else
				angle = RotateInitSpeed;
		}
		if(key==GLUT_KEY_RIGHT)  {
			if(last_key==GLUT_KEY_RIGHT)
				angle = fmax(-RotateMaxSpeed,angle*RotateSpeedDelta);
			else
				angle = -RotateInitSpeed;
		}
		
		axis[0]=0;axis[1]=1;axis[2]=0;
	}
	
	m3dRotationMatrix33(RotationMartix33,angle/180*M_PI,axis[0], axis[1], axis[2]);
	m3dRotateVector(view,view0,RotationMartix33);
	m3dCopyVector3(up0, _Up);
	m3dRotateVector(_Up, up0, RotationMartix33);
	m3dSubtractVectors3(_Center, _Pos, view);
	
	last_key = key;
	m3dCopyMatrix33(LastRotationMartix33,RotationMartix33);
	M3DMatrix33f TotalRotation0;
	m3dCopyMatrix33(TotalRotation0,TotalRotation33);
	m3dMatrixMultiply33(TotalRotation33, TotalRotation0, RotationMartix44);
	
	m3dRotationMatrix44(RotationMartix44,angle/180*M_PI,axis[0], axis[1], axis[2]);
	m3dCopyMatrix44(LastRotationMartix44,RotationMartix44);
	M3DMatrix44f TotalRotation1;
	m3dCopyMatrix44(TotalRotation1,TotalRotation44);
	m3dMatrixMultiply44(TotalRotation44, TotalRotation1, RotationMartix44);
	
	glutPostRedisplay();
	return;
}

void
CC::classTex::
setAnisotropy(GLenum target){
	GLfloat fLargest;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
	glTexParameterf(target,GL_TEXTURE_MAX_ANISOTROPY_EXT,fLargest);
}

void
CC::classTex::
setMipmap(GLenum target){
	glTexParameteri(target,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(target,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}

GLuint
CC::classTex::
LoadMipmapTex(const char * filename)
{
	return SOIL_load_OGL_texture(filename,SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
}
GLuint
CC::classTex::
LoadCubeMapMipmapTex(const char *x_pos_file, const char *x_neg_file, const char *y_pos_file, const char *y_neg_file, const char *z_pos_file,	const char *z_neg_file){
	return SOIL_load_OGL_cubemap(x_pos_file, x_neg_file, y_pos_file, y_neg_file, z_pos_file, z_neg_file, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
}

void
CC::classControl::
keyMove(unsigned char key,int,int){
	M3DVector3f	view0;
	M3DVector3f pos0;
	M3DVector3f center0;
	M3DVector3f right;
	
	static GLfloat CurrntSpeed;
	static GLint last_key;
	
	m3dCopyVector3(center0, _Center);
	m3dCopyVector3(pos0, _Pos);
	m3dSubtractVectors3(view0, pos0, _Center);
	switch (key) {
		case 'w':{
			if(last_key==key)
				CurrntSpeed = fmin(MoveMaxSpeed, CurrntSpeed* MoveSpeedDelta);
			else
				CurrntSpeed = MoveInitSpeed;
			m3dNormalizeVector3(view0);
			m3dScaleVector3(view0,CurrntSpeed);
			m3dSubtractVectors3(_Pos, pos0, view0);
			m3dSubtractVectors3(_Center, center0, view0);
			break;
		}
		case 's':{
			if(last_key==key)
				CurrntSpeed = fmin(MoveMaxSpeed, CurrntSpeed* MoveSpeedDelta);
			else
				CurrntSpeed = MoveInitSpeed;
			m3dNormalizeVector3(view0);
			m3dScaleVector3(view0,CurrntSpeed);
			m3dAddVectors3(_Pos, pos0, view0);
			m3dAddVectors3(_Center, center0, view0);
			break;
		}
		case 'a':{
			if(last_key==key)
				CurrntSpeed = fmin(MoveMaxSpeed, CurrntSpeed* MoveSpeedDelta);
			else
				CurrntSpeed = MoveInitSpeed;
			m3dCrossProduct3(right, _Up, view0);
			m3dNormalizeVector3(right);
			m3dScaleVector3(right,CurrntSpeed);
			m3dSubtractVectors3(_Pos, pos0, right);
			m3dSubtractVectors3(_Center, center0, right);
			break;
		}
		case 'd':{
			if(last_key==key)
				CurrntSpeed = fmin(MoveMaxSpeed, CurrntSpeed* MoveSpeedDelta);
			else
				CurrntSpeed = MoveInitSpeed;
			m3dCrossProduct3(right, _Up, view0);
			m3dNormalizeVector3(right);
			m3dScaleVector3(right,CurrntSpeed);
			m3dAddVectors3(_Pos, pos0, right);
			m3dAddVectors3(_Center, center0, right);
			break;
		}
		case 'h':{
			if(last_key==key)
				CurrntSpeed = fmin(MoveMaxSpeed, CurrntSpeed* MoveSpeedDelta);
			else
				CurrntSpeed = MoveInitSpeed;
			M3DVector3f yaxis={0,CurrntSpeed,0};
			m3dAddVectors3(_Pos, pos0, yaxis);
			m3dAddVectors3(_Center, center0, yaxis);
			break;
		}
		case 'l':{
			if(last_key==key)
				CurrntSpeed = fmax(-MoveMaxSpeed, CurrntSpeed* MoveSpeedDelta);
			else
				CurrntSpeed = -MoveInitSpeed;
			M3DVector3f yaxis={0,CurrntSpeed,0};
			m3dAddVectors3(_Pos, pos0, yaxis);
			m3dAddVectors3(_Center, center0, yaxis);
			break;
		}
		default:{
			keyPressOtherKey(key, NULL, NULL);
		}
	}
	last_key = key;
	glutPostRedisplay();
}

void
CC::classControl::
keyPressOtherKey(unsigned char key, int, int){
};

void
CC::classControl::
setPos(M3DVector3f Pos){
	m3dCopyVector3(_Pos, Pos);
}
void
CC::classControl::
setUp(M3DVector3f Up){
	m3dCopyVector3(_Up, Up);
}
void
CC::classControl::
setCenter(M3DVector3f Center){
	m3dCopyVector3(_Center, Center);
}
void
CC::classControl::
setPos(GLfloat x,GLfloat y,GLfloat z){
	_Pos[0]=x;
	_Pos[1]=y;
	_Pos[2]=z;
}
void
CC::classControl::
setUp(GLfloat x,GLfloat y,GLfloat z){
	_Up[0]=x;
	_Up[1]=y;
	_Up[2]=z;
}
void
CC::classControl::
setCenter(GLfloat x,GLfloat y,GLfloat z){
	_Center[0]=x;
	_Center[1]=y;
	_Center[2]=z;
}
