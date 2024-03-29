/****************************************
 ***    Project:  GL Raytracer        ***
 ***    File:     glraytracer.h        ***
 ***    Author:   Daniele Donghi      ***
 ***           d.donghi AT gmail.com  ***
 ***    Created on November 1, 2011   ***
 ****************************************/

#include <iostream>
#include "dbReader.h"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#endif
#ifndef __APPLE__
	#include <GL/glut.h>
#endif

#define MAX_RAYTRACING_DEPTH 4

#define SPHERE 1
#define TRIANGLE 2

using namespace std;

struct ray {
    point3D start;
    point3D dir;
    bool inside;
    double index_of_refraction;
};

struct color{
    double r,g,b;
};

class glraytracer {
	private:
		// Members
		int width;
		int height;
		dbReader *reader;
                point3D *PRP, *VPN, *VRP, *VUP;
                double uMin,uMax,vMin,vMax;

                // Final buffer
                color buffer[800][600];
	
	public:
		// Constructor/Destructor
                glraytracer(int w, int h);
                ~glraytracer() {};
	
		// OpenGL Methods
		void init();
		void display();
		void keyboard(unsigned char key, int x, int y);
		void specialKey(int key, int x, int y);
		void mouseButton(int button, int state, int x, int y);
		void idleFunc();
		
		// Project 3 Methods
		void readDatabase(char* fileName);

                // Helper function
                void raytrace();
                void draw();

                color RT_trace(ray r, int depth);
                color RT_shade(int INTERSECTION_TYPE, int obj_index, ray viewRay, point3D intersection, int depth);

                void setDiffuseAndSpecular_Sphere(ray&,sphere*,point3D,color*);
                void setDiffuseAndSpecular_Triangle(ray&,triangle*,point3D,color*);

                color setTransmission_Sphere(ray&,point3D newStart, sphere *s, int depth);
                color setTransmission_Triangle(ray&,point3D newStart, triangle *tri, int depth);

                color setReflection_Sphere(ray & viewVect, point3D newStart, sphere* s, int depth);
                color setReflection_Triangle(ray & viewVect,point3D newStart, triangle* tri, int depth);

                bool hitTriangle(ray&,triangle*,double*);
                bool hitSphere(ray&,sphere*,double*);

                point3D const_mult_point(double c, point3D p);
                double dot(point3D p1, point3D p2 );
                point3D normalize(point3D p);
                double mod(point3D p);
                point3D crossProduct(point3D v1, point3D v2);
                point3D min(point3D p2, point3D p1);

                // Triangle helper functions
                bool sameSide(point3D,point3D,point3D,point3D);
                bool isInTriangle(point3D p, point3D A, point3D B, point3D C);

};
