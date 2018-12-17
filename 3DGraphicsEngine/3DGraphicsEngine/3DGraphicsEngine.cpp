// 3DGraphicsEngine.cpp : Defines the entry point for the console application.
//

#include "olcConsoleGameEngine.h"
#include <exception>

struct Vec3 
{
	float x, y, z;
};

struct Matrix4x4
{
	// order is [row][column]
	float m[4][4] = { 0 };
};

struct Triangle
{
	Vec3 p[3];
};

struct Mesh
{
	std::vector<Triangle> tris;
};


class olcEngine3D : public olcConsoleGameEngine 
{
public:
	olcEngine3D() {
		m_sAppName = L"3D Demo";
	}

public:
	bool OnUserCreate() override {

		meshCube.tris = {

			// SOUTH
			{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

			// EAST                                                      
			{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
			{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

			// NORTH                                                     
			{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
			{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

			// WEST                                                      
			{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

			// TOP                                                       
			{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
			{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

			// BOTTOM                                                    
			{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
			{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
		};

		// Projection Matrix
		float fNear = 0.1f;
		float fFar = 1000.f;
		float fFOV = 90.f;
		float fAspectRatio = (float)ScreenHeight() / (float)ScreenWidth();
		float fFovRad = 1.f / tanf(fFOV * 0.5f / 180.f * 3.14159f);

		matProj.m[0][0] = fAspectRatio * fFovRad;
		matProj.m[1][1] = fFovRad;
		matProj.m[2][2] = fFar / (fFar - fNear);
		matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
		matProj.m[2][3] = 1.f;
		matProj.m[3][3] = 0.f;

		return true;
	}

	bool OnUserUpdate(float deltaTime) override {
		
		// clear screen
		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

		// draw triangles
		for (auto tri : meshCube.tris) {
			Triangle triProjected;
			MultiplyMatrixVector(tri.p[0], triProjected.p[0], matProj);
			MultiplyMatrixVector(tri.p[1], triProjected.p[1], matProj);
			MultiplyMatrixVector(tri.p[2], triProjected.p[2], matProj);

			// scale into view
			triProjected.p[0].x += 1.f; triProjected.p[0].y += 1.f;
			triProjected.p[1].x += 1.f; triProjected.p[1].y += 1.f;
			triProjected.p[2].x += 1.f; triProjected.p[2].y += 1.f;

			triProjected.p[0].x *= 0.5f * (float)ScreenWidth();
			triProjected.p[0].y *= 0.5f * (float)ScreenHeight();
			triProjected.p[1].x *= 0.5f * (float)ScreenWidth();
			triProjected.p[1].y *= 0.5f * (float)ScreenHeight();
			triProjected.p[2].x *= 0.5f * (float)ScreenWidth();
			triProjected.p[2].y *= 0.5f * (float)ScreenHeight();

			DrawTriangle(triProjected.p[0].x, triProjected.p[0].y,
				triProjected.p[1].x, triProjected.p[1].x,
				triProjected.p[2].x, triProjected.p[2].x,
				PIXEL_SOLID, FG_WHITE);
		}

		return true;
	}

private:
	Mesh meshCube;
	Matrix4x4 matProj;

	void MultiplyMatrixVector(Vec3& i, Vec3& o, Matrix4x4& m) {

		o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
		o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
		o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
		float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

		if (w != 0.f) {
			o.x /= w; o.y /= w; o.z /= w;
		}
	}
};

int main()
{
	try {
		olcEngine3D demo;
		if (demo.ConstructConsole(256, 240, 4, 4)) {
			demo.Start();
		}
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}

    return 0;
}

