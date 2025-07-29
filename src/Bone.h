#ifndef BONE_H
#define BONE_H

#include "/home/codeleaded/System/Static/Library/Lib3D_Mathlib.h"
#include "/home/codeleaded/System/Static/Library/Lib3D_Mesh.h"

#include "GJoint.h"


typedef struct Bone{
	vec3d p;
	GJoint a;
	Vector trisIn;
	Vector trisOut;
	Vector bones;
} Bone;

Bone Bone_New(vec3d p,GJoint a){
	Bone b;
	b.p = p;
	b.a = a;
	b.trisIn = Vector_New(sizeof(triangle));
	b.trisOut = Vector_New(sizeof(triangle));
	b.bones = Vector_New(sizeof(Bone));
	return b;
}
Bone Bone_Make(vec3d p,GJoint a,triangle* tris){
	Bone b = Bone_New(p,a);

	if(tris){
		for(int i = 0;tris[i].c!=0x00000000;i++){
			Vector_Push(&b.trisIn,&tris[i]);
		}
	}

	return b;
}
Bone Bone_MakeX(vec3d p,GJoint a,triangle* tris,Bone* bones){
	Bone b = Bone_Make(p,a,tris);

	if(bones){
		for(int i = 0;bones[i].trisIn.size>0 && bones[i].bones.size>0;i++){
			Vector_Push(&b.bones,&bones[i]);
		}
	}

	return b;
}
Bone Bone_MakeXX(vec3d p,GJoint a,Vector* tris,Bone* bones){
	Bone b = Bone_New(p,a);

	if(tris){
		for(int i = 0;i<tris->size;i++){
			triangle* t = (triangle*)Vector_Get(tris,i);
			Vector_Push(&b.trisIn,t);
		}
	}

	if(bones){
		for(int i = 0;bones[i].trisIn.size>0;i++){
			Vector_Push(&b.bones,&bones[i]);
		}
	}

	return b;
}
Bone Bone_Null(){
	Bone b;
	b.p = (vec3d){ 0.0f,0.0f,0.0f,1.0f };
	b.a = GJoint_Null();
	b.trisIn = Vector_Null();
	b.trisOut = Vector_Null();
	b.bones = Vector_Null();
	return b;
}
void Bone_RenderTrans_R(Bone* b,mat4x4* mat){
	for(int i = 0;i<b->bones.size;i++){
		Bone* child = (Bone*)Vector_Get(&b->bones,i);
		Bone_RenderTrans_R(child,mat);
	}

	for(int i = 0;i<b->trisOut.size;i++){
		triangle* t = (triangle*)Vector_Get(&b->trisOut,i);

		t->p[0] = Matrix_MultiplyVector(*mat,t->p[0]);
		t->p[1] = Matrix_MultiplyVector(*mat,t->p[1]);
		t->p[2] = Matrix_MultiplyVector(*mat,t->p[2]);
		triangle_CalcNorm(t);
	}
}
void Bone_Render_R(Bone* b){
	for(int i = 0;i<b->bones.size;i++){
		Bone* child = (Bone*)Vector_Get(&b->bones,i);
		Bone_Render_R(child);
	}

	Vector_Clear(&b->trisOut);
	for(int i = 0;i<b->trisIn.size;i++){
		triangle* t = (triangle*)Vector_Get(&b->trisIn,i);
		Vector_Push(&b->trisOut,t);
	}

	mat4x4 mat = Matrix_MakeWorldR(b->p,b->a.a);
	Bone_RenderTrans_R(b,&mat);
}
void Bone_RenderAll_R(Bone* b,Vector* tris,vec3d p,vec3d dir){
	for(int i = 0;i<b->bones.size;i++){
		Bone* child = (Bone*)Vector_Get(&b->bones,i);
		Bone_RenderAll_R(child,tris,p,dir);
	}

	for(int i = 0;i<b->trisOut.size;i++){
		triangle* t = (triangle*)Vector_Get(&b->trisOut,i);
		
        t->p[0] = vec3d_Add(p,t->p[0]);
		t->p[1] = vec3d_Add(p,t->p[1]);
		t->p[2] = vec3d_Add(p,t->p[2]);

        triangle_CalcNorm(t);
        triangle_ShadeNorm(t,dir);
        
        Vector_Push(tris,t);
	}
}
void Bone_Render(Bone* b,Vector* tris,vec3d p,vec3d dir){
	Vector trisBuff = Vector_New(sizeof(triangle));

	Bone_Render_R(b);
	Bone_RenderAll_R(b,tris,p,dir);

	Vector_Free(&trisBuff);
}
void Bone_Free(Bone* b){
	Vector_Free(&b->trisIn);
	Vector_Free(&b->trisOut);
	Vector_Free(&b->bones);
}

#endif