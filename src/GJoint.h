#ifndef GJOINT_H
#define GJOINT_H

#include "/home/codeleaded/System/Static/Library/Lib3D_Mathlib.h"
#include "/home/codeleaded/System/Static/Library/Lib3D_Mesh.h"


typedef struct GJoint{
	vec3d a;
    vec3d a_min;
    vec3d a_max;
} GJoint;

GJoint GJoint_New(vec3d a){
	GJoint b;
	b.a = a;
	b.a_min = vec3d_New(0.0f,0.0f,0.0f);
	b.a_max = vec3d_New(F32_PI2,F32_PI2,F32_PI2);
	return b;
}
GJoint GJoint_Make(vec3d a,vec3d a_min,vec3d a_max){
	GJoint b;
	b.a = a;
	b.a_min = a_min;
	b.a_max = a_max;
	return b;
}
GJoint GJoint_Null(){
	GJoint b;
	b.a = vec3d_Null();
	b.a_min = vec3d_New(0.0f,0.0f,0.0f);
	b.a_max = vec3d_New(F32_PI2,F32_PI2,F32_PI2);
	return b;
}
void GJoint_Set(GJoint* b,vec3d a){
	if(a.x < b->a_min.x) a.x = b->a_min.x;
	if(a.y < b->a_min.y) a.y = b->a_min.y;
	if(a.z < b->a_min.z) a.z = b->a_min.z;
	if(a.x > b->a_max.x) a.x = b->a_max.x;
	if(a.y > b->a_max.y) a.y = b->a_max.y;
	if(a.z > b->a_max.z) a.z = b->a_max.z;

    b->a = a;
}
vec3d GJoint_Get(GJoint* b){
	return b->a;
}

typedef GJoint XJoint;

XJoint XJoint_New(float Xa,float Xmin,float Xmax){
	XJoint b;
	b.a = vec3d_New(Xa,0.0f,0.0f);
	b.a_min = vec3d_New(Xmin,0.0f,0.0f);;
	b.a_max = vec3d_New(Xmax,0.0f,0.0f);;
	return b;
}
void XJoint_Set(XJoint* b,float Xa){
	GJoint_Set(b,vec3d_New(Xa,b->a.y,b->a.z));
}
float XJoint_Get(XJoint* b){
	return GJoint_Get(b).x;
}
void XJoint_Set_P(XJoint* b,float Xa){
	const float d = b->a_max.x - b->a_min.x;
    const float p = Xa * d + b->a_min.x;
    XJoint_Set(b,p);
}

typedef GJoint YJoint;

YJoint YJoint_New(float Ya,float Ymin,float Ymax){
	YJoint b;
	b.a = vec3d_New(Ya,0.0f,0.0f);
	b.a_min = vec3d_New(Ymin,0.0f,0.0f);;
	b.a_max = vec3d_New(Ymax,0.0f,0.0f);;
	return b;
}
void YJoint_Set(YJoint* b,float Ya){
	GJoint_Set(b,vec3d_New(b->a.x,Ya,b->a.z));
}
float YJoint_Get(YJoint* b){
	return GJoint_Get(b).y;
}
void YJoint_Set_P(YJoint* b,float Ya){
	const float d = b->a_max.y - b->a_min.y;
    const float p = Ya * d + b->a_min.y;
    YJoint_Set(b,p);
}

typedef GJoint ZJoint;

ZJoint ZJoint_New(float Za,float Zmin,float Zmax){
	ZJoint b;
	b.a = vec3d_New(Za,0.0f,0.0f);
	b.a_min = vec3d_New(Zmin,0.0f,0.0f);;
	b.a_max = vec3d_New(Zmax,0.0f,0.0f);;
	return b;
}
void ZJoint_Set(ZJoint* b,float Za){
	GJoint_Set(b,vec3d_New(b->a.x,b->a.y,Za));
}
float ZJoint_Get(ZJoint* b){
	return GJoint_Get(b).z;
}
void ZJoint_Set_P(ZJoint* b,float Za){
	const float d = b->a_max.z - b->a_min.z;
    const float p = Za * d + b->a_min.z;
    ZJoint_Set(b,p);
}

#endif