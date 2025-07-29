#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Lib3D_Cube.h"
#include "/home/codeleaded/System/Static/Library/Lib3D_Mathlib.h"
#include "/home/codeleaded/System/Static/Library/Lib3D_Mesh.h"

#include "RoboticArm.h"

Camera cam;
World3D world;
int Mode = 0;
int Menu = 0;
float Speed = 4.0f;

RoboticArm ra;


void Menu_Set(int m){
	if(Menu==0 && m==1){
		AlxWindow_Mouse_SetInvisible(&window);
		SetMouse((Vec2){ GetWidth() / 2,GetHeight() / 2 });
	}
	if(Menu==1 && m==0){
		AlxWindow_Mouse_SetVisible(&window);
	}
	
	Menu = m;
}

void Setup(AlxWindow* w){
	Menu_Set(1);

	cam = Camera_Make(
		(vec3d){-5.0f,5.0f,3.0f,1.0f },
		(vec3d){ 0.0f,0.0f,0.0f,1.0f },
		(vec3d){ F32_PI025 * 0.5f,-F32_PI05,0.0f,1.0f },
		90.0f
	);

	world = World3D_Make(
		Matrix_MakeWorld((vec3d){ 0.0f,0.0f,0.0f,1.0f },(vec3d){ 0.0f,0.0f,0.0f,1.0f }),
		Matrix_MakePerspektive(cam.p,cam.up,cam.a),
		Matrix_MakeProjection(cam.fov,(float)GetHeight() / (float)GetWidth(),0.1f,1000.0f)
	);
	world.normal = WORLD3D_NORMAL_CAP;

	ra = RoboticArm_New((vec3d){ 1.0f,0.0f,1.0f,1.0f },0.0f);
}
void Update(AlxWindow* w){
	if(Menu==1){
		Camera_Focus(&cam,GetMouseBefore(),GetMouse(),GetScreenRect().d);
		Camera_Update(&cam);
		SetMouse((Vec2){ GetWidth() / 2,GetHeight() / 2 });
	}
	
	if(Stroke(ALX_KEY_ESC).PRESSED)
		Menu_Set(!Menu);

	if(Stroke(ALX_KEY_Z).PRESSED)
		Mode = Mode < 3 ? Mode+1 : 0;

	if(Stroke(ALX_KEY_W).DOWN)
		cam.p = vec3d_Add(cam.p,vec3d_Mul(cam.ld,Speed * w->ElapsedTime));
	if(Stroke(ALX_KEY_S).DOWN)
		cam.p = vec3d_Sub(cam.p,vec3d_Mul(cam.ld,Speed * w->ElapsedTime));
	if(Stroke(ALX_KEY_A).DOWN)
		cam.p = vec3d_Add(cam.p,vec3d_Mul(cam.sd,Speed * w->ElapsedTime));
	if(Stroke(ALX_KEY_D).DOWN)
		cam.p = vec3d_Sub(cam.p,vec3d_Mul(cam.sd,Speed * w->ElapsedTime));
	if(Stroke(ALX_KEY_R).DOWN)
		cam.p.y += Speed * w->ElapsedTime;
	if(Stroke(ALX_KEY_F).DOWN)
		cam.p.y -= Speed * w->ElapsedTime;

	
	if(Stroke(ALX_KEY_LEFT).DOWN)
		RoboticArm_Set(&ra,(int[]){ -1 },RoboticArm_Get(&ra,(int[]){ -1 }) + 1.0f * w->ElapsedTime);
	if(Stroke(ALX_KEY_RIGHT).DOWN)
		RoboticArm_Set(&ra,(int[]){ -1 },RoboticArm_Get(&ra,(int[]){ -1 }) - 1.0f * w->ElapsedTime);
	
	if(Stroke(ALX_KEY_UP).DOWN)
		RoboticArm_Set(&ra,(int[]){ 0,-1 },RoboticArm_Get(&ra,(int[]){ 0,-1 }) + 1.0f * w->ElapsedTime);
	if(Stroke(ALX_KEY_DOWN).DOWN)
		RoboticArm_Set(&ra,(int[]){ 0,-1 },RoboticArm_Get(&ra,(int[]){ 0,-1 }) - 1.0f * w->ElapsedTime);
		
	if(Stroke(ALX_KEY_T).DOWN)
		RoboticArm_Set(&ra,(int[]){ 0,0,-1 },RoboticArm_Get(&ra,(int[]){ 0,0,-1 }) + 1.0f * w->ElapsedTime);
	if(Stroke(ALX_KEY_G).DOWN)
		RoboticArm_Set(&ra,(int[]){ 0,0,-1 },RoboticArm_Get(&ra,(int[]){ 0,0,-1 }) - 1.0f * w->ElapsedTime);

	if(Stroke(ALX_KEY_U).DOWN)
		RoboticArm_Set(&ra,(int[]){ 0,0,0,-1 },RoboticArm_Get(&ra,(int[]){ 0,0,0,-1 }) + 1.0f * w->ElapsedTime);
	if(Stroke(ALX_KEY_J).DOWN)
		RoboticArm_Set(&ra,(int[]){ 0,0,0,-1 },RoboticArm_Get(&ra,(int[]){ 0,0,0,-1 }) - 1.0f * w->ElapsedTime);

	if(Stroke(ALX_KEY_I).DOWN){
		RoboticArm_Set(&ra,(int[]){ 0,0,0,0,-1 },RoboticArm_Get(&ra,(int[]){ 0,0,0,0,-1 }) + 1.0f * w->ElapsedTime);
		RoboticArm_Set(&ra,(int[]){ 0,0,0,1,-1 },RoboticArm_Get(&ra,(int[]){ 0,0,0,1,-1 }) - 1.0f * w->ElapsedTime);
	}
	if(Stroke(ALX_KEY_K).DOWN){
		RoboticArm_Set(&ra,(int[]){ 0,0,0,0,-1 },RoboticArm_Get(&ra,(int[]){ 0,0,0,0,-1 }) - 1.0f * w->ElapsedTime);
		RoboticArm_Set(&ra,(int[]){ 0,0,0,1,-1 },RoboticArm_Get(&ra,(int[]){ 0,0,0,1,-1 }) + 1.0f * w->ElapsedTime);
	}



	World3D_Set_Model(&world,Matrix_MakeWorld((vec3d){ 0.0f,0.0f,0.0f,1.0f },(vec3d){ 0.0f,0.0f,0.0f,1.0f }));
	World3D_Set_View(&world,Matrix_MakePerspektive(cam.p,cam.up,cam.a));
	World3D_Set_Proj(&world,Matrix_MakeProjection(cam.fov,(float)GetHeight() / (float)GetWidth(),0.1f,1000.0f));
	
	Vector_Clear(&world.trisIn);
	RoboticArm_Render(&ra,&world.trisIn,vec3d_New(0.3f,0.4f,0.5f));

	Clear(LIGHT_BLUE);

	World3D_update(&world,cam.p);

	for(int i = 0;i<world.trisOut.size;i++){
		triangle* t = (triangle*)Vector_Get(&world.trisOut,i);

		if(Mode==0)
			RenderTriangle(((Vec2){ t->p[0].x, t->p[0].y }),((Vec2){ t->p[1].x, t->p[1].y }),((Vec2){ t->p[2].x, t->p[2].y }),t->c);
		if(Mode==1)
			RenderTriangleWire(((Vec2){ t->p[0].x, t->p[0].y }),((Vec2){ t->p[1].x, t->p[1].y }),((Vec2){ t->p[2].x, t->p[2].y }),t->c,1.0f);
		if(Mode==2){
			RenderTriangle(((Vec2){ t->p[0].x, t->p[0].y }),((Vec2){ t->p[1].x, t->p[1].y }),((Vec2){ t->p[2].x, t->p[2].y }),t->c);
			RenderTriangleWire(((Vec2){ t->p[0].x, t->p[0].y }),((Vec2){ t->p[1].x, t->p[1].y }),((Vec2){ t->p[2].x, t->p[2].y }),WHITE,1.0f);
		}
	}

	String str = String_Format("X: %f, Y: %f, Z: %f",cam.p.x,cam.p.y,cam.p.z);
	RenderCStrSize(str.Memory,str.size,0,0,RED);
	String_Free(&str);
	str = String_Format("SizeIn: %d, SizeBuff: %d, SizeOut: %d",world.trisIn.size,world.trisBuff.size,world.trisOut.size);
	RenderCStrSize(str.Memory,str.size,0,window.AlxFont.CharSizeY + 1,RED);
	String_Free(&str);
}
void Delete(AlxWindow* w){
	RoboticArm_Free(&ra);

	World3D_Free(&world);
	AlxWindow_Mouse_SetVisible(&window);
}

int main(){
    if(Create("Robotic Arm Simulation",2500,1200,1,1,Setup,Update,Delete))
        Start();
    return 0;
}