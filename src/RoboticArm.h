#ifndef ROBOTICARM_H
#define ROBOTICARM_H

#include "/home/codeleaded/System/Static/Library/Lib3D_Mathlib.h"
#include "/home/codeleaded/System/Static/Library/Lib3D_Mesh.h"

#include "Bone.h"

typedef struct RoboticArm{
    Bone b;
    vec3d p;
} RoboticArm;

RoboticArm RoboticArm_New(vec3d p,float r){
	Vector tris1 = Lib3D_Cube_Make(
        (vec3d){ -0.5f,0.0f,-0.5f,1.0f },
        (vec3d){ 1.0f,0.5f,1.0f,1.0f },
        0xFFFFFFFFU,
        0xFFFFFFFFU
    );
    Vector tris2 = Lib3D_Cube_Make(
        (vec3d){-0.25f,0.0f,-0.25f,1.0f },
        (vec3d){ 0.5f,2.5f,0.5f,1.0f },
        0xFFFFFFFFU,
        0xFFFFFFFFU
    );
    Vector tris3 = Lib3D_Cube_Make(
        (vec3d){-0.25f,0.0f,-0.25f,1.0f },
        (vec3d){ 0.5f,0.5f,2.5f,1.0f },
        0xFFFFFFFFU,
        0xFFFFFFFFU
    );
    Vector tris4 = Lib3D_Cube_Make(
        (vec3d){-0.5f,-0.25f,0.0f,1.0f },
        (vec3d){ 1.0f,0.5f,0.5f,1.0f },
        0xFFFFFFFFU,
        0xFFFFFFFFU
    );
    Vector tris5 = Lib3D_Cube_Make(
        (vec3d){ 0.0f,0.0f,0.0f,1.0f },
        (vec3d){ 0.5f,0.25f,1.0f,1.0f },
        0xFFFFFFFFU,
        0xFFFFFFFFU
    );
    Vector tris6 = Lib3D_Cube_Make(
        (vec3d){ -0.5f,0.0f,0.0f,1.0f },
        (vec3d){ 0.5f,0.25f,1.0f,1.0f },
        0xFFFFFFFFU,
        0xFFFFFFFFU
    );

	RoboticArm s;
    s.p = p;
    s.b = Bone_MakeXX(
		(vec3d){ 0.0f,0.0f,0.0f,1.0f },
		GJoint_Make(vec3d_Null(),vec3d_New(0.0f,-F32_PI,0.0f),vec3d_New(0.0f,F32_PI,0.0f)),
		&tris1,(Bone[]){
			Bone_MakeXX(
				(vec3d){ 0.0f,0.5f,0.0f,1.0f },
				GJoint_Make(vec3d_Null(),vec3d_New(-F32_PI025,0.0f,0.0f),vec3d_New(F32_PI05,0.0f,0.0f)),
				&tris2,(Bone[]){
					Bone_MakeXX(
						(vec3d){ 0.0f,2.5f,0.0f,1.0f },
				        GJoint_Make(vec3d_Null(),vec3d_New(-F32_PI025,0.0f,0.0f),vec3d_New(F32_PI025,0.0f,0.0f)),
						&tris3,(Bone[]){
							Bone_MakeXX(
								(vec3d){ 0.0f,0.25f,2.25f,1.0f },
								GJoint_Make(vec3d_Null(),vec3d_New(0.0f,0.0f,-F32_PI05),vec3d_New(0.0f,0.0f,F32_PI05)),
								&tris4,(Bone[]){
									Bone_MakeXX(
										(vec3d){ 0.5f,0.0f,0.25f,1.0f },
										GJoint_Make(vec3d_Null(),vec3d_New(0.0f,-F32_PI025,0.0f),vec3d_New(0.0f,F32_PI025,0.0f)),
										&tris5,NULL
									),
                                    Bone_MakeXX(
										(vec3d){ -0.5f,0.0f,0.25f,1.0f },
										GJoint_Make(vec3d_Null(),vec3d_New(0.0f,-F32_PI025,0.0f),vec3d_New(0.0f,F32_PI025,0.0f)),
										&tris6,NULL
									),
									Bone_Null()
								}
							),
							Bone_Null()
						}
					),
					Bone_Null()
				}
			),
			Bone_Null()
		}
	);

	Vector_Free(&tris1);
	Vector_Free(&tris2);
	Vector_Free(&tris3);
	Vector_Free(&tris4);
	Vector_Free(&tris5);

	return s;
}
Bone* RoboticArm_Get_Bone(RoboticArm* ra,int* s){
    Bone* b = &ra->b;
    for(int i = 0;s[i]>=0;i++){
        const int Index = s[i];
        
        if(Index<b->bones.size) b = (Bone*)Vector_Get(&b->bones,Index);
        else{
            printf("[RoboticArm]: Set -> Error\n");
            return NULL;
        }
    }
    return b;
}
void RoboticArm_Set(RoboticArm* ra,int* s,float value){
    Bone* b = RoboticArm_Get_Bone(ra,s);

    if(b->a.a_min.x!=b->a.a_max.x) XJoint_Set(&b->a,value);
    if(b->a.a_min.y!=b->a.a_max.y) YJoint_Set(&b->a,value);
    if(b->a.a_min.z!=b->a.a_max.z) ZJoint_Set(&b->a,value);
}
float RoboticArm_Get(RoboticArm* ra,int* s){
    Bone* b = RoboticArm_Get_Bone(ra,s);

    if(b->a.a_min.x!=b->a.a_max.x) return XJoint_Get(&b->a);
    if(b->a.a_min.y!=b->a.a_max.y) return YJoint_Get(&b->a);
    if(b->a.a_min.z!=b->a.a_max.z) return ZJoint_Get(&b->a);

    printf("[RoboticArm]: Get -> Error\n");
    return 0.0f;
}

void RoboticArm_Render(RoboticArm* ra,Vector* tris,vec3d dir){
	Bone_Render(&ra->b,tris,ra->p,dir);
}
void RoboticArm_Free(RoboticArm* ra){
	Bone_Free(&ra->b);
}

#endif