/*****************************************************/
/* Proyek:	Tugas Besar						 		 */
/* Oleh	 :											 */
/* 	1. Agung Ramadhani - 24060120120016				 */
/*	2. Muhammad Adil Raja Saputra - 24060120140060	 */	
/*	3. Muhammad Farhan Haris Rosidi - 24060120140104 */	
/*	4. M. Khoirul Ma'arif - 24060120130116			 */		
/*****************************************************/

// Template untuk mainan objek 3D 
// Kamera bisa maju mundur kiri kanan 
// Sudah dilengkapi pencahayaan 
// Sekarang pake texture 

#include <math.h> 
#include <GL/glut.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

float xAngle=0.0, deltaXAngle = 0.0, ratio;
float yAngle=0.0, deltaYAngle = 0.0;
float x=0.0f,y=10.0f,z=40.0f; // posisi awal kamera 
float lx=0.0f,ly=0.0f,lz=-1.0f; 
int deltaZMove = 0, h,w; 

const float MMin = -500, MMax = 500;
float geserJalan = -20.0;
float maxKananJalan=-65+geserJalan, maxKiriJalan=65+geserJalan;

// Mengatur posisi truck
float posXTruk=0, posYTruk=0, posZTruk=-80;
float posDepanTruk=posZTruk+40, posBelakangTruk=posZTruk-40;
float posKananTruk=posXTruk-11, posKiriTruk=posXTruk+11;

// Mengatur posisi box
float posXBox=0, posYBox=0, posZBox=0;
float posDepanBox=posZBox+4, posBelakangBox=posZBox-4;
float posKananBox=posXBox-10, posKiriBox=posXBox+10;

void Reshape(int w1, int h1) 
{ 
  	// Fungsi reshape 
  	if(h1 == 0) h1 = 1; 
  	w = w1; 
  	h = h1; 
  	ratio = 1.0f * w / h; 
  	glMatrixMode(GL_PROJECTION); 
  	glLoadIdentity(); 
  	glViewport(0, 0, w, h); 
  	gluPerspective(45,ratio,0.1,1000); 
  	glMatrixMode(GL_MODELVIEW); 
  	glLoadIdentity(); 
  	gluLookAt(
    	x, y, z, 
     	x + lx,y + ly,z + lz, 
    	0.0f,1.0f,0.0f
	); 
} 

void orientMeSide(float ang) 
{ 
  	// Fungsi ini untuk memutar arah kamera (tengok kiri/kanan) 
  	lx = sin(ang); 
  	lz = -cos(ang); 
  	glLoadIdentity(); 
  	gluLookAt(	x, y, z, 
  				x + lx,y + ly,z + lz, 
  				0.0f,1.0f,0.0f		); 
} 

void orientMeUp(float ang) 
{ 
  	// Fungsi ini untuk memutar arah kamera (tengok atas/bawah) 
  	ly = sin(ang); 
  	glLoadIdentity(); 
  	gluLookAt(	x, y, z, 
  				x + lx,y + ly,z + lz, 
  				0.0f,1.0f,0.0f		); 
} 

void moveMeFlat(int i) 
{ 
  	// Fungsi ini untuk maju mundur kamera 
  	x = x + i*(lx)*0.1; 
  	z = z + i*(lz)*0.1; 
  	glLoadIdentity();  
  	gluLookAt(	x, y, z, 
  				x + lx,y + ly,z + lz, 
  				0.0f,1.0f,0.0f); 
}

void Road() { 
	// Fungsi untuk membuat jalan
	double i;
	glPushMatrix();
	glTranslatef(geserJalan,0.0,0.0);
	glBegin(GL_QUADS);
		glColor3f(0.5, 1, 0.5);
		glVertex3f(-200, 0, MMin);
		glVertex3f(-75, 0, MMin);
		glVertex3f(-75, 0, MMax);
		glVertex3f(-200, 0, MMax);
	
		glVertex3f(75, 0, MMin);
		glVertex3f(200, 0, MMin);
		glVertex3f(200, 0, MMax);
		glVertex3f(75, 0, MMax);
	glEnd();
	
	//Jalan
	glBegin(GL_QUADS);
		glColor3f(0.0, 0, 0.0);
		glVertex3f(-75, 0, MMin);
		glVertex3f(75, 0, MMin);
		glVertex3f(75, 0, MMax);
		glVertex3f(-75, 0, MMax);
	glEnd();
	
	//Trotoar
	glBegin(GL_QUADS);
	for(i=MMin;i<MMax;i+=10.0){
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-75, 0.05, i);
		glVertex3f(-65, 0.05, i);
		glVertex3f(-65, 0.05, i+5);
		glVertex3f(-75, 0.05, i+5);
	}
	for(i=MMin;i<MMax;i+=10.0){
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(75, 0.05, i);
		glVertex3f(65, 0.05, i);
		glVertex3f(65, 0.05, i+5);
		glVertex3f(75, 0.05, i+5);
	}

	//Garis Jalan
	for(i=MMin;i<MMax;i+=40.0){
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-2.5, 0.05, i);
		glVertex3f(2.5, 0.05, i);
		glVertex3f(2.5, 0.05, i+20);
		glVertex3f(-2.5, 0.05, i+20);
	}
	glEnd();
	
	// Pembatas Jalan
	glBegin(GL_QUADS);
		glColor3f(1.0, 0.7, 0.0);
		// depan
		glVertex3f(63, 0, MMax-15);
		glVertex3f(63, 13, MMax-14);
		glVertex3f(-63, 13, MMax-14);
		glVertex3f(-63, 0, MMax-15);
		glVertex3f(63, 0, MMin+15);
		glVertex3f(63, 13, MMin+14);
		glVertex3f(-63, 13, MMin+14);
		glVertex3f(-63, 0, MMin+15);
		
		// belakang
		glVertex3f(63, 0, MMax-5);
		glVertex3f(63, 13, MMax-6);
		glVertex3f(-63, 13, MMax-6);
		glVertex3f(-63, 0, MMax-5);
		glVertex3f(63, 0, MMin+5);
		glVertex3f(63, 13, MMin+6);
		glVertex3f(-63, 13, MMin+6);
		glVertex3f(-63, 0, MMin+5);
		
		// atas
		glVertex3f(63, 13, MMax-6);
		glVertex3f(-63, 13, MMax-6);
		glVertex3f(-63, 13, MMax-14);
		glVertex3f(63, 13, MMax-14);
		glVertex3f(63, 13, MMin+6);
		glVertex3f(-63, 13, MMin+6);
		glVertex3f(-63, 13, MMin+14);
		glVertex3f(63, 13, MMin+14);
		
		// kanan
		glVertex3f(63, 0, MMax-15);
		glVertex3f(63, 13, MMax-14);
		glVertex3f(63, 13, MMax-6);
		glVertex3f(63, 0, MMax-5);
		glVertex3f(63, 0, MMin+15);
		glVertex3f(63, 13, MMin+14);
		glVertex3f(63, 13, MMin+6);
		glVertex3f(63, 0, MMin+5);
		
		// kiri
		glVertex3f(-63, 0, MMax-15);
		glVertex3f(-63, 13, MMax-14);
		glVertex3f(-63, 13, MMax-6);
		glVertex3f(-63, 0, MMax-5);
		glVertex3f(-63, 0, MMin+15);
		glVertex3f(-63, 13, MMin+14);
		glVertex3f(-63, 13, MMin+6);
		glVertex3f(-63, 0, MMin+5);
	glEnd();
	glPopMatrix();
}


void Pohon1(){ //Pohon ada 3
//============Pohon 1=====================
    //Batang
        // Bagian Bawah
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,60.0);
            glVertex3f(80.0f, 1.0,50.0);
            glVertex3f(90.0f, 1.0,50.0);
            glVertex3f(90.0f, 1.0,60.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,60.0);
            glVertex3f(80.0f, 40.0,60.0);
            glVertex3f(90.0f, 40.0,60.0);
            glVertex3f(90.0f, 1.0,60.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,50.0);
            glVertex3f(80.0f, 40.0,50.0);
            glVertex3f(90.0f, 40.0,50.0);
            glVertex3f(90.0f, 1.0,50.0);
        glEnd();
        glPopMatrix();


        // Bagian Kiri
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,60.0);
            glVertex3f(80.0f, 40.0,60.0);
            glVertex3f(80.0f, 40.0,50.0);
            glVertex3f(80.0f, 1.0,50.0);
        glEnd();
        glPopMatrix();

        // Bagian Kanan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(90.0f, 1.0,60.0);
            glVertex3f(90.0f, 40.0,60.0);
            glVertex3f(90.0f, 40.0,50.0);
            glVertex3f(90.0f, 1.0,50.0);
        glEnd();
        glPopMatrix();

    //Daun
        // Bagian Bawah
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 40.0,70.0);
            glVertex3f(70.0f, 40.0,40.0);
            glVertex3f(100.0f, 40.0,40.0);
            glVertex3f(100.0f, 40.0,70.0);
        glEnd();
        glPopMatrix();

        // Bagian Atas
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 60.0,70.0);
            glVertex3f(70.0f, 60.0,40.0);
            glVertex3f(100.0f, 60.0,40.0);
            glVertex3f(100.0f, 60.0,70.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 60.0,70.0);
            glVertex3f(70.0f, 40.0,70.0);
            glVertex3f(100.0f, 40.0,70.0);
            glVertex3f(100.0f, 60.0,70.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 60.0,40.0);
            glVertex3f(70.0f, 40.0,40.0);
            glVertex3f(100.0f, 40.0,40.0);
            glVertex3f(100.0f, 60.0,40.0);
        glEnd();
        glPopMatrix();

        // Bagian Kiri
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 40.0,40.0);
            glVertex3f(70.0f, 60.0,40.0);
            glVertex3f(70.0f, 60.0,70.0);
            glVertex3f(70.0f, 40.0,70.0);
        glEnd();
        glPopMatrix();

        // Bagian Kiri
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(100.0f, 40.0,40.0);
            glVertex3f(100.0f, 60.0,40.0);
            glVertex3f(100.0f, 60.0,70.0);
            glVertex3f(100.0f, 40.0,70.0);
        glEnd();
        glPopMatrix();

//============Pohon 2=====================
    //Batang
        // Bagian Bawah
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,100.0);
            glVertex3f(80.0f, 1.0,90.0);
            glVertex3f(90.0f, 1.0,90.0);
            glVertex3f(90.0f, 1.0,100.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,100.0);
            glVertex3f(80.0f, 25.0,100.0);
            glVertex3f(90.0f, 25.0,100.0);
            glVertex3f(90.0f, 1.0,100.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,90.0);
            glVertex3f(80.0f, 25.0,90.0);
            glVertex3f(90.0f, 25.0,90.0);
            glVertex3f(90.0f, 1.0,90.0);
        glEnd();
        glPopMatrix();


        // Bagian Kiri
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,100.0);
            glVertex3f(80.0f, 25.0,100.0);
            glVertex3f(80.0f, 25.0,90.0);
            glVertex3f(80.0f, 1.0,90.0);
        glEnd();
        glPopMatrix();

    //Daun
    //Bagian Bawah
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(75.0f, 25.0,105.0);
            glVertex3f(75.0f, 25.0,85.0);
            glVertex3f(95.0f, 25.0,85.0);
            glVertex3f(95.0f, 25.0,105.0);
        glEnd();
        glPopMatrix();

        //Bagian Atas
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(75.0f, 25.0,105.0);
            glVertex3f(75.0f, 25.0,85.0);
            glVertex3f(95.0f, 25.0,85.0);
            glVertex3f(95.0f, 25.0,105.0);
        glEnd();
        glPopMatrix();


        //Bagian Kanan
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(95.0f, 25.0,85.0);
            glVertex3f(95.0f, 40.0,85.0);
            glVertex3f(95.0f, 40.0,105.0);
            glVertex3f(95.0f, 25.0,105.0);
        glEnd();
        glPopMatrix();

        //Bagian Kiri
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(75.0f, 25.0,85.0);
            glVertex3f(75.0f, 40.0,85.0);
            glVertex3f(75.0f, 40.0,105.0);
            glVertex3f(75.0f, 25.0,105.0);
        glEnd();
        glPopMatrix();

        //Bagian Depan
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(75.0f, 25.0,105.0);
            glVertex3f(75.0f, 40.0,105.0);
            glVertex3f(95.0f, 40.0,105.0);
            glVertex3f(95.0f, 25.0,105.0);
        glEnd();
        glPopMatrix();

        //Bagian Belakang
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(75.0f, 25.0,85.0);
            glVertex3f(75.0f, 40.0,85.0);
            glVertex3f(95.0f, 40.0,85.0);
            glVertex3f(95.0f, 25.0,85.0);
        glEnd();
        glPopMatrix();

//============Pohon 3=====================
    //Batang
        // Bagian Bawah
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(130.0f, 1.0,80.0);
            glVertex3f(130.0f, 1.0,70.0);
            glVertex3f(140.0f, 1.0,70.0);
            glVertex3f(140.0f, 1.0,80.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(130.0f, 1.0,80.0);
            glVertex3f(130.0f, 35.0,80.0);
            glVertex3f(140.0f, 35.0,80.0);
            glVertex3f(140.0f, 1.0,80.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(130.0f, 1.0,70.0);
            glVertex3f(130.0f, 35.0,70.0);
            glVertex3f(140.0f, 35.0,70.0);
            glVertex3f(140.0f, 1.0,70.0);
        glEnd();
        glPopMatrix();

        // Bagian Kiri
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(130.0f, 1.0,70.0);
            glVertex3f(130.0f, 35.0,70.0);
            glVertex3f(130.0f, 35.0,80.0);
            glVertex3f(130.0f, 1.0,80.0);
        glEnd();
        glPopMatrix();

        // Bagian Kanan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(140.0f, 1.0,70.0);
            glVertex3f(140.0f, 35.0,70.0);
            glVertex3f(140.0f, 35.0,80.0);
            glVertex3f(140.0f, 1.0,80.0);
        glEnd();
        glPopMatrix();

    //Daun

        //Bagian atas
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(120.0f, 35.0f,90.0f);
            glVertex3f(120.0f, 35.0f,60.0f);
            glVertex3f(150.0f, 35.0f,60.0f);
            glVertex3f(150.0f, 35.0f,90.0f);
        glEnd();
        glPopMatrix();

        //Bagian Depan
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(120.0f, 35.0f,90.0f);
            glVertex3f(120.0f, 60.0f,90.0f);
            glVertex3f(150.0f, 60.0f,90.0f);
            glVertex3f(150.0f, 35.0f,90.0f);
        glEnd();
        glPopMatrix();

        //Bagian Belakang
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(120.0f, 35.0f,60.0f);
            glVertex3f(120.0f, 60.0f,60.0f);
            glVertex3f(150.0f, 60.0f,60.0f);
            glVertex3f(150.0f, 35.0f,60.0f);
        glEnd();
        glPopMatrix();

        //Bagian Kiri
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(120.0f, 35.0f,60.0f);
            glVertex3f(120.0f, 60.0f,60.0f);
            glVertex3f(120.0f, 60.0f,90.0f);
            glVertex3f(120.0f, 35.0f,90.0f);
        glEnd();
        glPopMatrix();

        //Bagian Kanan
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(150.0f, 35.0f,60.0f);
            glVertex3f(150.0f, 60.0f,60.0f);
            glVertex3f(150.0f, 60.0f,90.0f);
            glVertex3f(150.0f, 35.0f,90.0f);
        glEnd();
        glPopMatrix();

}

void Pohon4(){
   //============Pohon 1=====================
    //Batang
        // Bagian Bawah
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0, -150.0);
            glVertex3f(80.0f, 1.0,-140.0);
            glVertex3f(90.0f, 1.0,-140.0);
            glVertex3f(90.0f, 1.0,-150.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,-150.0);
            glVertex3f(80.0f, 40.0,-150.0);
            glVertex3f(90.0f, 40.0,-150.0);
            glVertex3f(90.0f, 1.0,-150.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,-140.0);
            glVertex3f(80.0f, 40.0,-140.0);
            glVertex3f(90.0f, 40.0,-140.0);
            glVertex3f(90.0f, 1.0,-140.0);
        glEnd();
        glPopMatrix();


        // Bagian Kiri
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,-150.0);
            glVertex3f(80.0f, 40.0,-150.0);
            glVertex3f(80.0f, 40.0,-140.0);
            glVertex3f(80.0f, 1.0,-140.0);
        glEnd();
        glPopMatrix();

        // Bagian Kanan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(90.0f, 1.0,-150.0);
            glVertex3f(90.0f, 40.0,-150.0);
            glVertex3f(90.0f, 40.0,-140.0);
            glVertex3f(90.0f, 1.0,-140.0);
        glEnd();
        glPopMatrix();

    //Daun
        // Bagian Bawah
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 40.0,-160.0);
            glVertex3f(70.0f, 40.0,-130.0);
            glVertex3f(100.0f, 40.0,-130.0);
            glVertex3f(100.0f, 40.0,-160.0);
        glEnd();
        glPopMatrix();

        // Bagian Atas
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 60.0,-130.0);
            glVertex3f(70.0f, 60.0,-160.0);
            glVertex3f(100.0f, 60.0,-160.0);
            glVertex3f(100.0f, 60.0,-130.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 60.0,-130.0);
            glVertex3f(70.0f, 40.0,-130.0);
            glVertex3f(100.0f, 40.0,-130.0);
            glVertex3f(100.0f, 60.0,-130.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 60.0,-160.0);
            glVertex3f(70.0f, 40.0,-160.0);
            glVertex3f(100.0f, 40.0,-160.0);
            glVertex3f(100.0f, 60.0,-160.0);
        glEnd();
        glPopMatrix();

        // Bagian Kiri
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 40.0,-160.0);
            glVertex3f(70.0f, 60.0,-160.0);
            glVertex3f(70.0f, 60.0,-130.0);
            glVertex3f(70.0f, 40.0,-130.0);
        glEnd();
        glPopMatrix();

        // Bagian Kanan
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(100.0f, 40.0,-160.0);
            glVertex3f(100.0f, 60.0,-160.0);
            glVertex3f(100.0f, 60.0,-130.0);
            glVertex3f(100.0f, 40.0,-130.0);
        glEnd();
        glPopMatrix();
   //============Pohon 2=====================
    //Batang
        // Bagian Bawah
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0, -210.0);
            glVertex3f(80.0f, 1.0,-200.0);
            glVertex3f(90.0f, 1.0,-200.0);
            glVertex3f(90.0f, 1.0,-210.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,-210.0);
            glVertex3f(80.0f, 30.0,-210.0);
            glVertex3f(90.0f, 30.0,-210.0);
            glVertex3f(90.0f, 1.0,-210.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,-200.0);
            glVertex3f(80.0f, 30.0,-200.0);
            glVertex3f(90.0f, 30.0,-200.0);
            glVertex3f(90.0f, 1.0,-200.0);
        glEnd();
        glPopMatrix();


        // Bagian Kiri
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,-210.0);
            glVertex3f(80.0f, 30.0,-210.0);
            glVertex3f(80.0f, 30.0,-200.0);
            glVertex3f(80.0f, 1.0,-200.0);
        glEnd();
        glPopMatrix();

        // Bagian Kanan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(90.0f, 1.0,-210.0);
            glVertex3f(90.0f, 30.0,-210.0);
            glVertex3f(90.0f, 30.0,-200.0);
            glVertex3f(90.0f, 1.0,-200.0);
        glEnd();
        glPopMatrix();

    //Daun
        // Bagian Bawah
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 30.0,-220.0);
            glVertex3f(70.0f, 30.0,-190.0);
            glVertex3f(100.0f, 30.0,-190.0);
            glVertex3f(100.0f, 30.0,-210.0);
        glEnd();
        glPopMatrix();

        // Bagian Atas
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 50.0,-190.0);
            glVertex3f(70.0f, 50.0,-220.0);
            glVertex3f(100.0f, 50.0,-220.0);
            glVertex3f(100.0f, 50.0,-190.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 50.0,-190.0);
            glVertex3f(70.0f, 30.0,-190.0);
            glVertex3f(100.0f, 30.0,-190.0);
            glVertex3f(100.0f, 50.0,-190.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 50.0,-220.0);
            glVertex3f(70.0f, 30.0,-220.0);
            glVertex3f(100.0f, 30.0,-220.0);
            glVertex3f(100.0f, 50.0,-220.0);
        glEnd();
        glPopMatrix();

        // Bagian Kiri
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 30.0,-220.0);
            glVertex3f(70.0f, 50.0,-220.0);
            glVertex3f(70.0f, 50.0,-190.0);
            glVertex3f(70.0f, 30.0,-190.0);
        glEnd();
        glPopMatrix();

        // Bagian Kanan
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(100.0f, 30.0,-220.0);
            glVertex3f(100.0f, 50.0,-220.0);
            glVertex3f(100.0f, 50.0,-190.0);
            glVertex3f(100.0f, 30.0,-190.0);
        glEnd();
        glPopMatrix();

//============Pohon 3=====================
    //Batang
        // Bagian Bawah
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(140.0f, 1.0, -190.0);
            glVertex3f(140.0f, 1.0,-180.0);
            glVertex3f(150.0f, 1.0,-180.0);
            glVertex3f(150.0f, 1.0,-190.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(140.0f, 1.0,-190.0);
            glVertex3f(140.0f, 30.0,-190.0);
            glVertex3f(150.0f, 30.0,-190.0);
            glVertex3f(150.0f, 1.0,-190.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(140.0f, 1.0,-180.0);
            glVertex3f(140.0f, 30.0,-180.0);
            glVertex3f(150.0f, 30.0,-180.0);
            glVertex3f(150.0f, 1.0,-180.0);
        glEnd();
        glPopMatrix();


        // Bagian Kiri
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(140.0f, 1.0,-190.0);
            glVertex3f(140.0f, 30.0,-190.0);
            glVertex3f(140.0f, 30.0,-180.0);
            glVertex3f(140.0f, 1.0,-180.0);
        glEnd();
        glPopMatrix();

        // Bagian Kanan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(150.0f, 1.0,-190.0);
            glVertex3f(150.0f, 30.0,-190.0);
            glVertex3f(150.0f, 30.0,-180.0);
            glVertex3f(150.0f, 1.0,-180.0);
        glEnd();
        glPopMatrix();

    //Daun
        // Bagian Bawah
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(130.0f, 30.0,-200.0);
            glVertex3f(130.0f, 30.0,-170.0);
            glVertex3f(160.0f, 30.0,-170.0);
            glVertex3f(160.0f, 30.0,-200.0);
        glEnd();
        glPopMatrix();

        // Bagian Atas
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(130.0f, 50.0,-200.0);
            glVertex3f(130.0f, 50.0,-170.0);
            glVertex3f(160.0f, 50.0,-170.0);
            glVertex3f(160.0f, 50.0,-200.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(130.0f, 50.0,-200.0);
            glVertex3f(130.0f, 30.0,-200.0);
            glVertex3f(160.0f, 30.0,-200.0);
            glVertex3f(160.0f, 50.0,-200.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(130.0f, 50.0,-170.0);
            glVertex3f(130.0f, 30.0,-170.0);
            glVertex3f(160.0f, 30.0,-170.0);
            glVertex3f(160.0f, 50.0,-170.0);
        glEnd();
        glPopMatrix();

        // Bagian Kiri
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(130.0f, 30.0,-170.0);
            glVertex3f(130.0f, 50.0,-170.0);
            glVertex3f(130.0f, 50.0,-200.0);
            glVertex3f(130.0f, 30.0,-200.0);
        glEnd();
        glPopMatrix();

        // Bagian Kanan
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(160.0f, 30.0,-170.0);
            glVertex3f(160.0f, 50.0,-170.0);
            glVertex3f(160.0f, 50.0,-200.0);
            glVertex3f(160.0f, 30.0,-200.0);
        glEnd();
        glPopMatrix();


//============Pohon 4=====================
    //Batang
        // Bagian Bawah
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(140.0f, 1.0, -260.0);
            glVertex3f(140.0f, 1.0,-250.0);
            glVertex3f(150.0f, 1.0,-250.0);
            glVertex3f(150.0f, 1.0,-260.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(140.0f, 1.0,-250.0);
            glVertex3f(140.0f, 30.0,-250.0);
            glVertex3f(150.0f, 30.0,-250.0);
            glVertex3f(150.0f, 1.0,-250.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(140.0f, 1.0,-260.0);
            glVertex3f(140.0f, 30.0,-260.0);
            glVertex3f(150.0f, 30.0,-260.0);
            glVertex3f(150.0f, 1.0,-260.0);
        glEnd();
        glPopMatrix();


        // Bagian Kiri
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(140.0f, 1.0,-250.0);
            glVertex3f(140.0f, 30.0,-250.0);
            glVertex3f(140.0f, 30.0,-260.0);
            glVertex3f(140.0f, 1.0,-260.0);
        glEnd();
        glPopMatrix();

        // Bagian Kanan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(150.0f, 1.0,-250.0);
            glVertex3f(150.0f, 30.0,-250.0);
            glVertex3f(150.0f, 30.0,-260.0);
            glVertex3f(150.0f, 1.0,-260.0);
        glEnd();
        glPopMatrix();


    //Daun
        // Bagian Bawah
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(130.0f, 30.0,-270.0);
            glVertex3f(130.0f, 30.0,-240.0);
            glVertex3f(160.0f, 30.0,-240.0);
            glVertex3f(160.0f, 30.0,-270.0);
        glEnd();
        glPopMatrix();

        // Bagian Atas
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(130.0f, 50.0,-270.0);
            glVertex3f(130.0f, 50.0,-240.0);
            glVertex3f(160.0f, 50.0,-240.0);
            glVertex3f(160.0f, 50.0,-270.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(130.0f, 50.0,-270.0);
            glVertex3f(130.0f, 30.0,-270.0);
            glVertex3f(160.0f, 30.0,-270.0);
            glVertex3f(160.0f, 50.0,-270.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(130.0f, 50.0,-240.0);
            glVertex3f(130.0f, 30.0,-240.0);
            glVertex3f(160.0f, 30.0,-240.0);
            glVertex3f(160.0f, 50.0,-240.0);
        glEnd();
        glPopMatrix();

        // Bagian Kiri
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(130.0f, 30.0,-240.0);
            glVertex3f(130.0f, 50.0,-240.0);
            glVertex3f(130.0f, 50.0,-270.0);
            glVertex3f(130.0f, 30.0,-270.0);
        glEnd();
        glPopMatrix();

        // Bagian Kanan
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(160.0f, 30.0,-240.0);
            glVertex3f(160.0f, 50.0,-240.0);
            glVertex3f(160.0f, 50.0,-270.0);
            glVertex3f(160.0f, 30.0,-270.0);
        glEnd();
        glPopMatrix();
}


void Pohon5(){
//============Pohon 1=====================
    //Batang
        // Bagian Bawah
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0, -430.0);
            glVertex3f(80.0f, 1.0,-420.0);
            glVertex3f(90.0f, 1.0,-420.0);
            glVertex3f(90.0f, 1.0,-430.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,-430.0);
            glVertex3f(80.0f, 40.0,-430.0);
            glVertex3f(90.0f, 40.0,-430.0);
            glVertex3f(90.0f, 1.0,-430.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,-420.0);
            glVertex3f(80.0f, 40.0,-420.0);
            glVertex3f(90.0f, 40.0,-420.0);
            glVertex3f(90.0f, 1.0,-420.0);
        glEnd();
        glPopMatrix();


        // Bagian Kiri
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,-430.0);
            glVertex3f(80.0f, 40.0,-430.0);
            glVertex3f(80.0f, 40.0,-420.0);
            glVertex3f(80.0f, 1.0,-420.0);
        glEnd();
        glPopMatrix();

        // Bagian Kanan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(90.0f, 1.0,-440.0);
            glVertex3f(90.0f, 40.0,-440.0);
            glVertex3f(90.0f, 40.0,-410.0);
            glVertex3f(90.0f, 1.0,-410.0);
        glEnd();
        glPopMatrix();

        //Daun
        // Bagian Bawah
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 40.0,-440.0);
            glVertex3f(70.0f, 40.0,-410.0);
            glVertex3f(100.0f, 40.0,-410.0);
            glVertex3f(100.0f, 40.0,-440.0);
        glEnd();
        glPopMatrix();

        // Bagian Atas
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 60.0,-410.0);
            glVertex3f(70.0f, 60.0,-440.0);
            glVertex3f(100.0f, 60.0,-440.0);
            glVertex3f(100.0f, 60.0,-410.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 60.0,-410.0);
            glVertex3f(70.0f, 40.0,-410.0);
            glVertex3f(100.0f, 40.0,-410.0);
            glVertex3f(100.0f, 60.0,-410.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 60.0,-440.0);
            glVertex3f(70.0f, 40.0,-440.0);
            glVertex3f(100.0f, 40.0,-440.0);
            glVertex3f(100.0f, 60.0,-440.0);
        glEnd();
        glPopMatrix();

        // Bagian Kiri
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 40.0,-440.0);
            glVertex3f(70.0f, 60.0,-440.0);
            glVertex3f(70.0f, 60.0,-410.0);
            glVertex3f(70.0f, 40.0,-410.0);
        glEnd();
        glPopMatrix();

        // Bagian Kanan
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(100.0f, 40.0,-440.0);
            glVertex3f(100.0f, 60.0,-440.0);
            glVertex3f(100.0f, 60.0,-410.0);
            glVertex3f(100.0f, 40.0,-410.0);
        glEnd();
        glPopMatrix();
}
void Rumah4(){ //Rumah Biru
// Bagian Bawah
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);//Blue
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0,-110.0);
        glVertex3f(70.0f, 1.0,-40.0);
        glVertex3f(120.0f, 1.0,-40.0);
        glVertex3f(120.0f, 1.0,-110.0);
    glEnd();
    glPopMatrix();


    // Bagian Atas
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);//Blue
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 40.0,-110.0);
        glVertex3f(70.0f, 40.0,-40.0);
        glVertex3f(120.0f, 40.0,-40.0);
        glVertex3f(120.0f, 40.0,-110.0);
        glEnd();
    glPopMatrix();

    //Bagian Depan
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);//Blue
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0,-40.0);
        glVertex3f(70.0f, 40.0,-40.0);
        glVertex3f(120.0f, 40.0,-40.0);
        glVertex3f(120.0f, 1.0,-40.0);
    glEnd();
    glPopMatrix();

    //Bagian Belakang
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);//Blue
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0f,-110.0f);
        glVertex3f(70.0f, 40.0f,-110.0f);
        glVertex3f(120.0f, 40.0f,-110.0f);
        glVertex3f(120.0f, 1.0f,-110.0f);
    glEnd();
    glPopMatrix();

    //Bagian Kiri
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);//Blue
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0f,-110.0f);
        glVertex3f(70.0f, 40.0f,-110.0f);
        glVertex3f(70.0f, 40.0f,-40.0f);
        glVertex3f(70.0f, 1.0f,-40.0f);

            glPushMatrix();
            glColor4f(1.0f, 0.5f, 0.0f, 0.0f);//orange
            glBegin(GL_QUADS);
                glVertex3f(69.5f, 15.0f,-100.0f);
                glVertex3f(70.0f, 35.0f,-100.0f);
                glVertex3f(70.0f, 35.0f,-70.0f);
                glVertex3f(70.0f, 15.0f,-70.0f);
            glEnd();
            glPopMatrix();

    glEnd();
    glPopMatrix();

    //Pintu Rumah
    glPushMatrix();
    glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
    glBegin(GL_QUADS);
        glVertex3f(69.5f, 15.0f,-42.0f);
        glVertex3f(69.5f, 1.0f,-42.0f);
        glVertex3f(69.5f, 1.0f,-52.0f);
        glVertex3f(69.5f, 15.0f,-52.0f);

        //Kusen Pintu
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex3f(69.0f, 9.0f,18.0f);
        glVertex3f(69.0f, 7.0f,18.0f);
        glVertex3f(69.0f, 7.0f,19.0f);
        glVertex3f(69.0f, 9.0f,19.0f);
    glEnd();
    glPopMatrix();

}

void Rumah5(){ //Rumah Biru Paling Kiri
	glPushMatrix();
   // Bagian Bawah
    glPushMatrix();
    glColor4f(1.0f, 0.5f, 0.0f, 0.0f);//orange
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0,-300.0);
        glVertex3f(70.0f, 1.0,-380.0);
        glVertex3f(120.0f, 1.0,-380.0);
        glVertex3f(120.0f, 1.0,-300.0);
    glEnd();
    glPopMatrix();


    // Bagian Atas
    glPushMatrix();
    glColor4f(1.0f, 0.5f, 0.0f, 0.0f);//orange
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 60.0,-380.0);
        glVertex3f(70.0f, 60.0,-300.0);
        glVertex3f(120.0f, 60.0,-300.0);
        glVertex3f(120.0f, 60.0,-380.0);
        glEnd();
    glPopMatrix();

    //Bagian Depan
    glPushMatrix();
    glColor4f(1.0f, 0.5f, 0.0f, 0.0f);//orange
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0,-300.0);
        glVertex3f(70.0f, 60.0,-300.0);
        glVertex3f(120.0f, 60.0,-300.0);
        glVertex3f(120.0f, 1.0,-300.0);
    glEnd();
    glPopMatrix();

    //Bagian Belakang
    glPushMatrix();
    glColor4f(1.0f, 0.5f, 0.0f, 0.0f);//orange
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0f,-380.0f);
        glVertex3f(70.0f, 60.0f,-380.0f);
        glVertex3f(120.0f, 60.0f,-380.0f);
        glVertex3f(120.0f, 1.0f,-380.0f);
    glEnd();
    glPopMatrix();

    //Bagian Kiri
    glPushMatrix();
    glColor4f(1.0f, 0.5f, 0.0f, 0.0f);//orange
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0f,-380.0f);
        glVertex3f(70.0f, 60.0f,-380.0f);
        glVertex3f(70.0f, 60.0f,-300.0f);
        glVertex3f(70.0f, 1.0f,-300.0f);
    glEnd();
    glPopMatrix();

    //Pintu Rumah
    glPushMatrix();
    glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
    glBegin(GL_QUADS);
        glVertex3f(69.5f, 15.0f,-360.0f);
        glVertex3f(69.5f, 1.0f,-360.0f);
        glVertex3f(69.5f, 1.0f,-370.0f);
        glVertex3f(69.5f, 15.0f,-370.0f);

        //Kusen Pintu
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex3f(69.0f, 9.0f,18.0f);
        glVertex3f(69.0f, 7.0f,18.0f);
        glVertex3f(69.0f, 7.0f,19.0f);
        glVertex3f(69.0f, 9.0f,19.0f);

        //Jendela
            //Baris 1
            glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
            glVertex3f(69.0f, 55.0f,-360.0f);
            glVertex3f(69.0f, 45.0f,-360.0f);
            glVertex3f(69.0f, 45.0f,-370.0f);
            glVertex3f(69.0f, 55.0f,-370.0f);

            glVertex3f(69.0f, 55.0f,-355.0f);
            glVertex3f(69.0f, 45.0f,-355.0f);
            glVertex3f(69.0f, 45.0f,-365.0f);
            glVertex3f(69.0f, 55.0f,-365.0f);

            glVertex3f(69.0f, 55.0f,-340.0f);
            glVertex3f(69.0f, 45.0f,-340.0f);
            glVertex3f(69.0f, 45.0f,-350.0f);
            glVertex3f(69.0f, 55.0f,-350.0f);

            glVertex3f(69.0f, 55.0f,-325.0f);
            glVertex3f(69.0f, 45.0f,-325.0f);
            glVertex3f(69.0f, 45.0f,-335.0f);
            glVertex3f(69.0f, 55.0f,-335.0f);

            glVertex3f(69.0f, 55.0f,-310.0f);
            glVertex3f(69.0f, 45.0f,-310.0f);
            glVertex3f(69.0f, 45.0f,-320.0f);
            glVertex3f(69.0f, 55.0f,-320.0f);


            //Baris 2
            glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
            glVertex3f(69.0f, 40.0f,-360.0f);
            glVertex3f(69.0f, 30.0f,-360.0f);
            glVertex3f(69.0f, 30.0f,-370.0f);
            glVertex3f(69.0f, 40.0f,-370.0f);

            glVertex3f(69.0f, 40.0f,-355.0f);
            glVertex3f(69.0f, 30.0f,-355.0f);
            glVertex3f(69.0f, 30.0f,-365.0f);
            glVertex3f(69.0f, 40.0f,-365.0f);

            glVertex3f(69.0f, 40.0f,-340.0f);
            glVertex3f(69.0f, 30.0f,-340.0f);
            glVertex3f(69.0f, 30.0f,-350.0f);
            glVertex3f(69.0f, 40.0f,-350.0f);

            glVertex3f(69.0f, 40.0f,-325.0f);
            glVertex3f(69.0f, 30.0f,-325.0f);
            glVertex3f(69.0f, 30.0f,-335.0f);
            glVertex3f(69.0f, 40.0f,-335.0f);

            glVertex3f(69.0f, 40.0f,-310.0f);
            glVertex3f(69.0f, 30.0f,-310.0f);
            glVertex3f(69.0f, 30.0f,-320.0f);
            glVertex3f(69.0f, 40.0f,-320.0f);

    glEnd();
    glPopMatrix();

	glPopMatrix();
}

void Rumah1(){ //Rumah Putih Paling Kiri


    // Bagian Bawah
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0,40.0);
        glVertex3f(70.0f, 1.0,-10.0);
        glVertex3f(120.0f, 1.0,-10.0);
        glVertex3f(120.0f, 1.0,40.0);
    glEnd();
    glPopMatrix();


    // Bagian Atas
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 30.0,40.0);
        glVertex3f(70.0f, 30.0,-10.0);
        glVertex3f(120.0f, 30.0,-10.0);
        glVertex3f(120.0f, 30.0,40.0);
    glEnd();
    glPopMatrix();

    //Bagian Depan
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0,40.0);
        glVertex3f(70.0f, 30.0,40.0);
        glVertex3f(120.0f, 30.0,40.0);
        glVertex3f(120.0f, 1.0,40.0);
    glEnd();
    glPopMatrix();

    //Bagian Belakang
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0f,-10.0f);
        glVertex3f(70.0f, 30.0f,-10.0f);
        glVertex3f(120.0f, 30.0f,-10.0f);
        glVertex3f(120.0f, 1.0f,-10.0f);
    glEnd();
    glPopMatrix();

    //Bagian Kiri
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0f,-10.0f);
        glVertex3f(70.0f, 30.0f,-10.0f);
        glVertex3f(70.0f, 30.0f,40.0f);
        glVertex3f(70.0f, 1.0f,40.0f);
    glEnd();
    glPopMatrix();

    //Pintu Rumah
    glPushMatrix();
    glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(69.5f, 15.0f,20.0f);
        glVertex3f(69.5f, 1.0f,20.0f);
        glVertex3f(69.5f, 1.0f,10.0f);
        glVertex3f(69.5f, 15.0f,10.0f);

        //Kusen Pintu
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex3f(69.0f, 9.0f,18.0f);
        glVertex3f(69.0f, 7.0f,18.0f);
        glVertex3f(69.0f, 7.0f,19.0f);
        glVertex3f(69.0f, 9.0f,19.0f);
    glEnd();
    glPopMatrix();

    //Jendela Rumah
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.5);
    glBegin(GL_QUADS);
        glVertex3f(69.5f, 15.0f,25.0f);
        glVertex3f(69.5f, 25.0f,25.0f);
        glVertex3f(69.5f, 25.0f,35.0f);
        glVertex3f(69.5f, 15.0f,35.0f);
    glEnd();
    glPopMatrix();

    //Pintu Rumah
    glPushMatrix();
    glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(69.5f, 15.0f,20.0f);
        glVertex3f(69.5f, 1.0f,20.0f);
        glVertex3f(69.5f, 1.0f,10.0f);
        glVertex3f(69.5f, 15.0f,10.0f);

        //Kusen Pintu
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex3f(69.0f, 9.0f,18.0f);
        glVertex3f(69.0f, 7.0f,18.0f);
        glVertex3f(69.0f, 7.0f,19.0f);
        glVertex3f(69.0f, 9.0f,19.0f);
    glEnd();
    glPopMatrix();


    //Bagian Kanan
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(120.0f, 1.0f,-10.0f);
        glVertex3f(120.0f, 30.0f,-10.0f);
        glVertex3f(120.0f, 30.0f,40.0f);
        glVertex3f(120.0f, 1.0f,40.0f);
    glEnd();
    glPopMatrix();

}

void Rumah2(){ //Rumah Putih Jendela Merah (Done)

    // Bagian Bawah
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0,170.0);
        glVertex3f(70.0f, 1.0,120.0);
        glVertex3f(120.0f, 1.0,120.0);
        glVertex3f(120.0f, 1.0,170.0);
    glEnd();
    glPopMatrix();

    // Bagian Depan
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0,170.0);
        glVertex3f(70.0f, 30.0,170.0);
        glVertex3f(120.0f, 30.0,170.0);
        glVertex3f(120.0f, 1.0,170.0);
    glEnd();
    glPopMatrix();

    // Bagian Belakang
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0,120.0);
        glVertex3f(70.0f, 30.0,120.0);
        glVertex3f(120.0f, 30.0,120.0);
        glVertex3f(120.0f, 1.0,120.0);
    glEnd();
    glPopMatrix();

    // Bagian Kiri
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0,170.0);
        glVertex3f(70.0f, 30.0,170.0);
        glVertex3f(70.0f, 30.0,120.0);
        glVertex3f(70.0f, 1.0,120.0);
    glEnd();

    //Pintu Rumah
    glPushMatrix();
    glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(69.5f, 15.0,140.0);
        glVertex3f(69.5f, 1.0,140.0);
        glVertex3f(69.5f, 1.0,130.0);
        glVertex3f(69.5f, 15.0,130.0);

        //Kusen Pintu
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex3f(69.0f, 9.0,138.0);
        glVertex3f(69.0f, 7.0,138.0);
        glVertex3f(69.0f, 7.0,139.0);
        glVertex3f(69.0f, 9.0,139.0);
    glEnd();
    glPopMatrix();

    // Bagian Kanan
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(120.0f, 1.0,170.0);
        glVertex3f(120.0f, 30.0,170.0);
        glVertex3f(120.0f, 30.0,120.0);
        glVertex3f(120.0f, 1.0,120.0);
    glEnd();
    glPopMatrix();

    // Bagian Atap 2
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 60.0,170.0);
        glVertex3f(120.0f, 60.0,170.0);
        glVertex3f(120.0f, 60.0,120.0);
        glVertex3f(70.0f, 60.0,120.0);
    glEnd();
    glPopMatrix();

    // Bagian Kiri 2
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 30.0,170.0);
        glVertex3f(70.0f, 60.0,170.0);
        glVertex3f(70.0f, 60.0,120.0);
        glVertex3f(70.0f, 30.0,120.0);

        //Jendela Baris 1
        //Jendela Rumah 1
        glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        glVertex3f(69.5f, 45.0,140.0);
        glVertex3f(69.5f, 55.0,140.0);
        glVertex3f(69.5f, 55.0,150.0);
        glVertex3f(69.5f, 45.0,150.0);

        //Jendela Rumah 2
        glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        glVertex3f(69.5f, 45.0,155.0);
        glVertex3f(69.5f, 55.0,155.0);
        glVertex3f(69.5f, 55.0,165.0);
        glVertex3f(69.5f, 45.0,165.0);

        //Jendela Rumah 3
        glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        glVertex3f(69.5f, 45.0,125.0);
        glVertex3f(69.5f, 55.0,125.0);
        glVertex3f(69.5f, 55.0,135.0);
        glVertex3f(69.5f, 45.0,135.0);

        //Jendela Baris 2
        //Jendela Rumah 1
        glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        glVertex3f(69.5f, 30.0,140.0);
        glVertex3f(69.5f, 40.0,140.0);
        glVertex3f(69.5f, 40.0,150.0);
        glVertex3f(69.5f, 30.0,150.0);

        //Jendela Rumah 2
        glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        glVertex3f(69.5f, 30.0,155.0);
        glVertex3f(69.5f, 40.0,155.0);
        glVertex3f(69.5f, 40.0,165.0);
        glVertex3f(69.5f, 30.0,165.0);

        //Jendela Rumah 3
        glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        glVertex3f(69.5f, 30.0,125.0);
        glVertex3f(69.5f, 40.0,125.0);
        glVertex3f(69.5f, 40.0,135.0);
        glVertex3f(69.5f, 30.0,135.0);


    glEnd();
    glPopMatrix();

    //Pintu Rumah
    glPushMatrix();
    glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(69.5f, 15.0,20.0);
        glVertex3f(69.5f, 1.0,20.0);
        glVertex3f(69.5f, 1.0,10.0);
        glVertex3f(69.5f, 15.0,10.0);

        //Kusen Pintu
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex3f(69.0f, 9.0,18.0);
        glVertex3f(69.0f, 7.0,18.0);
        glVertex3f(69.0f, 7.0,19.0);
        glVertex3f(69.0f, 9.0,19.0);
    glEnd();
    glPopMatrix();

    // Bagian Depan 2
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 30.0,170.0);
        glVertex3f(120.0f, 60.0,170.0);
        glVertex3f(120.0f, 60.0,170.0);
        glVertex3f(70.0f, 30.0,170.0);
    glEnd();
    glPopMatrix();

    // Bagian Belakang 2
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 30.0,120.0);
        glVertex3f(70.0f, 60.0,120.0);
        glVertex3f(120.0f, 60.0,120.0);
        glVertex3f(120.0f, 30.0,120.0);
    glEnd();
    glPopMatrix();

    // Bagian Kanan 2
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(120.0f, 30.0,170.0);
        glVertex3f(120.0f, 60.0,170.0);
        glVertex3f(120.0f, 60.0,120.0);
        glVertex3f(120.0f, 30.0,120.0);
    glEnd();
    glPopMatrix();

}

void Pohon2(){ //Pohon ada 2

//=============Pohon 1==============
 //Batang
        // Bagian Bawah
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,200.0);
            glVertex3f(80.0f, 1.0,190.0);
            glVertex3f(90.0f, 1.0,190.0);
            glVertex3f(90.0f, 1.0,200.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,200.0);
            glVertex3f(80.0f, 40.0,200.0);
            glVertex3f(90.0f, 40.0,200.0);
            glVertex3f(90.0f, 1.0,200.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,190.0);
            glVertex3f(80.0f, 40.0,190.0);
            glVertex3f(90.0f, 40.0,190.0);
            glVertex3f(90.0f, 1.0,190.0);
        glEnd();
        glPopMatrix();


        // Bagian Kiri
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,200.0);
            glVertex3f(80.0f, 40.0,200.0);
            glVertex3f(80.0f, 40.0,190.0);
            glVertex3f(80.0f, 1.0,190.0);
        glEnd();
        glPopMatrix();

        // Bagian Kanan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(90.0f, 1.0,200.0);
            glVertex3f(90.0f, 40.0,200.0);
            glVertex3f(90.0f, 40.0,190.0);
            glVertex3f(90.0f, 1.0,190.0);
        glEnd();
        glPopMatrix();

    //Daun
        // Bagian Bawah
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 40.0,210.0);
            glVertex3f(70.0f, 40.0,180.0);
            glVertex3f(100.0f, 40.0,180.0);
            glVertex3f(100.0f, 40.0,210.0);
        glEnd();
        glPopMatrix();

        // Bagian Atas
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 60.0,210.0);
            glVertex3f(70.0f, 60.0,180.0);
            glVertex3f(100.0f, 60.0,180.0);
            glVertex3f(100.0f, 60.0,210.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 60.0,210.0);
            glVertex3f(70.0f, 40.0,210.0);
            glVertex3f(100.0f, 40.0,210.0);
            glVertex3f(100.0f, 60.0,210.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 60.0,190.0);
            glVertex3f(70.0f, 40.0,190.0);
            glVertex3f(100.0f, 40.0,190.0);
            glVertex3f(100.0f, 60.0,190.0);
        glEnd();
        glPopMatrix();

        // Bagian Kiri
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 40.0,180.0);
            glVertex3f(70.0f, 60.0,180.0);
            glVertex3f(70.0f, 60.0,210.0);
            glVertex3f(70.0f, 40.0,210.0);
        glEnd();
        glPopMatrix();

        // Bagian Kiri
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(100.0f, 40.0,180.0);
            glVertex3f(100.0f, 60.0,180.0);
            glVertex3f(100.0f, 60.0,210.0);
            glVertex3f(100.0f, 40.0,210.0);
        glEnd();
        glPopMatrix();

//=============Pohon 2==============
 //Batang
        // Bagian Bawah
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,260.0);
            glVertex3f(80.0f, 1.0,250.0);
            glVertex3f(90.0f, 1.0,250.0);
            glVertex3f(90.0f, 1.0,260.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,250.0);
            glVertex3f(80.0f, 40.0,250.0);
            glVertex3f(90.0f, 40.0,250.0);
            glVertex3f(90.0f, 1.0,250.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,260.0);
            glVertex3f(80.0f, 40.0,260.0);
            glVertex3f(90.0f, 40.0,260.0);
            glVertex3f(90.0f, 1.0,260.0);
        glEnd();
        glPopMatrix();


        // Bagian Kiri
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,250.0);
            glVertex3f(80.0f, 40.0,250.0);
            glVertex3f(80.0f, 40.0,260.0);
            glVertex3f(80.0f, 1.0,260.0);
        glEnd();
        glPopMatrix();

        // Bagian Kanan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(90.0f, 1.0,250.0);
            glVertex3f(90.0f, 40.0,250.0);
            glVertex3f(90.0f, 40.0,260.0);
            glVertex3f(90.0f, 1.0,260.0);
        glEnd();
        glPopMatrix();

    //Daun
        // Bagian Bawah
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 40.0,270.0);
            glVertex3f(70.0f, 40.0,240.0);
            glVertex3f(100.0f, 40.0,240.0);
            glVertex3f(100.0f, 40.0,270.0);
        glEnd();
        glPopMatrix();

        // Bagian Atas
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 60.0,270.0);
            glVertex3f(70.0f, 60.0,240.0);
            glVertex3f(100.0f, 60.0,240.0);
            glVertex3f(100.0f, 60.0,270.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 60.0,270.0);
            glVertex3f(70.0f, 40.0,270.0);
            glVertex3f(100.0f, 40.0,270.0);
            glVertex3f(100.0f, 60.0,270.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 60.0,240.0);
            glVertex3f(70.0f, 40.0,240.0);
            glVertex3f(100.0f, 40.0,240.0);
            glVertex3f(100.0f, 60.0,240.0);
        glEnd();
        glPopMatrix();

        // Bagian Kiri
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 40.0,240.0);
            glVertex3f(70.0f, 60.0,240.0);
            glVertex3f(70.0f, 60.0,270.0);
            glVertex3f(70.0f, 40.0,270.0);
        glEnd();
        glPopMatrix();

        // Bagian Kiri
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(100.0f, 40.0,240.0);
            glVertex3f(100.0f, 60.0,240.0);
            glVertex3f(100.0f, 60.0,270.0);
            glVertex3f(100.0f, 40.0,270.0);
        glEnd();
        glPopMatrix();

}

void Pohon3(){ //
//=============Pohon 1==============
 //Batang
        // Bagian Bawah
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,410.0);
            glVertex3f(80.0f, 1.0,400.0);
            glVertex3f(90.0f, 1.0,400.0);
            glVertex3f(90.0f, 1.0,410.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,410.0);
            glVertex3f(80.0f, 30.0,410.0);
            glVertex3f(90.0f, 30.0,410.0);
            glVertex3f(90.0f, 1.0,410.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,400.0);
            glVertex3f(80.0f, 30.0,400.0);
            glVertex3f(90.0f, 30.0,400.0);
            glVertex3f(90.0f, 1.0,400.0);
        glEnd();
        glPopMatrix();


        // Bagian Kiri
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(80.0f, 1.0,410.0);
            glVertex3f(80.0f, 30.0,410.0);
            glVertex3f(80.0f, 30.0,400.0);
            glVertex3f(80.0f, 1.0,400.0);
        glEnd();
        glPopMatrix();

        // Bagian Kanan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(90.0f, 1.0,410.0);
            glVertex3f(90.0f, 30.0,410.0);
            glVertex3f(90.0f, 30.0,400.0);
            glVertex3f(90.0f, 1.0,400.0);
        glEnd();
        glPopMatrix();

    //Daun
        // Bagian Bawah
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 30.0,420.0);
            glVertex3f(70.0f, 30.0,390.0);
            glVertex3f(100.0f, 30.0,390.0);
            glVertex3f(100.0f, 30.0,420.0);
        glEnd();
        glPopMatrix();

        // Bagian Atas
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 50.0,420.0);
            glVertex3f(70.0f, 50.0,390.0);
            glVertex3f(100.0f, 50.0,390.0);
            glVertex3f(100.0f, 50.0,420.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 50.0,420.0);
            glVertex3f(70.0f, 30.0,420.0);
            glVertex3f(100.0f, 30.0,420.0);
            glVertex3f(100.0f, 50.0,420.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 50.0,390.0);
            glVertex3f(70.0f, 30.0,390.0);
            glVertex3f(100.0f, 30.0,390.0);
            glVertex3f(100.0f, 50.0,390.0);
        glEnd();
        glPopMatrix();

        // Bagian Kiri
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(70.0f, 30.0,390.0);
            glVertex3f(70.0f, 50.0,390.0);
            glVertex3f(70.0f, 50.0,420.0);
            glVertex3f(70.0f, 30.0,420.0);
        glEnd();
        glPopMatrix();

        // Bagian Kiri
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(100.0f, 30.0,390.0);
            glVertex3f(100.0f, 50.0,390.0);
            glVertex3f(100.0f, 50.0,420.0);
            glVertex3f(100.0f, 30.0,420.0);
        glEnd();
        glPopMatrix();

//=============Pohon 2==============
 //Batang
        // Bagian Bawah
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(85.0f, 1.0,460.0);
            glVertex3f(85.0f, 1.0,450.0);
            glVertex3f(105.0f, 1.0,450.0);
            glVertex3f(105.0f, 1.0,460.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(85.0f, 1.0,460.0);
            glVertex3f(85.0f, 30.0,460.0);
            glVertex3f(105.0f, 30.0,460.0);
            glVertex3f(105.0f, 1.0,460.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(85.0f, 1.0,450.0);
            glVertex3f(85.0f, 30.0,450.0);
            glVertex3f(105.0f, 30.0,450.0);
            glVertex3f(105.0f, 1.0,450.0);
        glEnd();
        glPopMatrix();


        // Bagian Kiri
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(105.0f, 1.0,460.0);
            glVertex3f(105.0f, 30.0,460.0);
            glVertex3f(105.0f, 30.0,450.0);
            glVertex3f(105.0f, 1.0,450.0);
        glEnd();
        glPopMatrix();

        // Bagian Kanan
        glPushMatrix();
        glColor4f(1.0f, 0.5f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex3f(85.0f, 1.0,460.0);
            glVertex3f(85.0f, 30.0,460.0);
            glVertex3f(85.0f, 30.0,450.0);
            glVertex3f(85.0f, 1.0,450.0);
        glEnd();
        glPopMatrix();

    //Daun
        // Bagian Bawah
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(75.0f, 30.0,470.0);
            glVertex3f(75.0f, 30.0,440.0);
            glVertex3f(115.0f, 30.0,440.0);
            glVertex3f(115.0f, 30.0,470.0);
        glEnd();
        glPopMatrix();

        // Bagian Atas
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(75.0f, 50.0,470.0);
            glVertex3f(75.0f, 50.0,440.0);
            glVertex3f(115.0f, 50.0,440.0);
            glVertex3f(115.0f, 50.0,470.0);
        glEnd();
        glPopMatrix();

        // Bagian Depan
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(75.0f, 50.0,470.0);
            glVertex3f(75.0f, 30.0,470.0);
            glVertex3f(115.0f, 30.0,470.0);
            glVertex3f(115.0f, 50.0,470.0);
        glEnd();
        glPopMatrix();

        // Bagian Belakang
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(75.0f, 50.0,440.0);
            glVertex3f(75.0f, 30.0,440.0);
            glVertex3f(115.0f, 30.0,440.0);
            glVertex3f(115.0f, 50.0,440.0);
        glEnd();
        glPopMatrix();

        // Bagian Kiri
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(95.0f, 30.0,440.0);
            glVertex3f(95.0f, 50.0,440.0);
            glVertex3f(95.0f, 50.0,470.0);
            glVertex3f(95.0f, 30.0,470.0);
        glEnd();
        glPopMatrix();

        // Bagian Kiri
        glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        glBegin(GL_QUADS);
            glVertex3f(115.0f, 30.0,440.0);
            glVertex3f(115.0f, 50.0,440.0);
            glVertex3f(115.0f, 50.0,470.0);
            glVertex3f(115.0f, 30.0,470.0);
        glEnd();
        glPopMatrix();
}

void Rumah3(){ //Rumah Merah Paling Kanan
    // Bagian Bawah
    glPushMatrix();
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0,280.0);
        glVertex3f(70.0f, 1.0,350.0);
        glVertex3f(120.0f, 1.0,350.0);
        glVertex3f(120.0f, 1.0,280.0);
    glEnd();
    glPopMatrix();

    // Bagian Depan
    glPushMatrix();
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0,350.0);
        glVertex3f(70.0f, 60.0,350.0);
        glVertex3f(120.0f, 60.0,350.0);
        glVertex3f(120.0f, 1.0,350.0);
    glEnd();
    glPopMatrix();

    // Bagian Belakang
    glPushMatrix();
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0,280.0);
        glVertex3f(70.0f, 60.0,280.0);
        glVertex3f(120.0f, 60.0,280.0);
        glVertex3f(120.0f, 1.0,280.0);
    glEnd();
    glPopMatrix();

    // Bagian Kiri
    glPushMatrix();
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    glBegin(GL_QUADS);
        glVertex3f(70.0f, 1.0,280.0);
        glVertex3f(70.0f, 60.0,280.0);
        glVertex3f(70.0f, 60.0,350.0);
        glVertex3f(70.0f, 1.0,350.0);


        //Pintu
        glPushMatrix();
        glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
        glBegin(GL_QUADS);
            glVertex3f(69.5f, 1.0,335.0);
            glVertex3f(69.5f, 15.0,335.0);
            glVertex3f(69.5f, 15.0,345.0);
            glVertex3f(69.5f, 1.0,345.0);
        glEnd();
        glPopMatrix();



        //Kusen
        glPushMatrix();
        glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
        glBegin(GL_QUADS);
            glVertex3f(69.0f, 7.0,343.0);
            glVertex3f(69.0f, 8.0,343.0);
            glVertex3f(69.0f, 8.0,344.0);
            glVertex3f(69.0f, 7.0,344.0);
        glEnd();
        glPopMatrix();

        //Jendela
        glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_QUADS);

        //Baris 1
            //Jendela 1
            glVertex3f(69.0f, 45.0,333.0);
            glVertex3f(69.0f, 55.0,333.0);
            glVertex3f(69.0f, 55.0,344.0);
            glVertex3f(69.0f, 45.0,344.0);


            //Jendela 2
            glVertex3f(69.0f, 45.0,330.0);
            glVertex3f(69.0f, 55.0,330.0);
            glVertex3f(69.0f, 55.0,320.0);
            glVertex3f(69.0f, 45.0,320.0);

            //Jendela 3
            glVertex3f(69.0f, 45.0,307.0);
            glVertex3f(69.0f, 55.0,307.0);
            glVertex3f(69.0f, 55.0,317.0);
            glVertex3f(69.0f, 45.0,317.0);

            //Jendela 4
            glVertex3f(69.0f, 45.0,304.0);
            glVertex3f(69.0f, 55.0,304.0);
            glVertex3f(69.0f, 55.0,294.0);
            glVertex3f(69.0f, 45.0,294.0);

        //Baris 2
            //Jendela 1
            glVertex3f(69.0f, 40.0,333.0);
            glVertex3f(69.0f, 30.0,333.0);
            glVertex3f(69.0f, 30.0,344.0);
            glVertex3f(69.0f, 40.0,344.0);


            //Jendela 2
            glVertex3f(69.0f, 40.0,330.0);
            glVertex3f(69.0f, 30.0,330.0);
            glVertex3f(69.0f, 30.0,320.0);
            glVertex3f(69.0f, 40.0,320.0);

            //Jendela 3
            glVertex3f(69.0f, 40.0,307.0);
            glVertex3f(69.0f, 30.0,307.0);
            glVertex3f(69.0f, 30.0,317.0);
            glVertex3f(69.0f, 40.0,317.0);

            //Jendela 4
            glVertex3f(69.0f, 40.0,304.0);
            glVertex3f(69.0f, 30.0,304.0);
            glVertex3f(69.0f, 30.0,294.0);
            glVertex3f(69.0f, 40.0,294.0);
        glEnd();
        glPopMatrix();
        //Jendela

    glEnd();
    glPopMatrix();

    // Bagian Kanan
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(120.0f, 1.0,280.0);
        glVertex3f(120.0f, 60.0,280.0);
        glVertex3f(120.0f, 60.0,350.0);
        glVertex3f(120.0f, 1.0,350.0);

        glEnd();
        glPopMatrix();


    glEnd();
    glPopMatrix();

}

void Truck() 
{ 
	int i;
	/**************** Kepala Truck ****************/
	glPushMatrix();
	glColor3f(0.458, 0.662, 0.156);
	//depan 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
    	glVertex3f(-8.0f,3.0f,40.0f); 
    	glVertex3f(8.0f,3.0f,40.0f); 
    	glVertex3f(8.0f,10.0f,40.0f); 
    	glVertex3f(-8.0f,10.0f,40.0f);
		
		glVertex3f(-8.0f,10.0f,40.0f); 
    	glVertex3f(8.0f,10.0f,40.0f); 
    	glVertex3f(8.0f,18.0f,38.0f); 
    	glVertex3f(-8.0f,18.0f,38.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// atas 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
    	glVertex3f(8.0f,18.0f,38.0f); 
      	glVertex3f(-8.0f,18.0f,38.0f); 
      	glVertex3f(-8.0f,18.0f,25.0f); 
      	glVertex3f(8.0f,18.0f,25.0f); 
    glEnd(); 
  	glPopMatrix(); 

  	// belakang 
  	glPushMatrix(); 
   	glBegin(GL_QUADS); 
     	glVertex3f(-8.0f,7.0f,25.0f); 
    	glVertex3f(8.0f,7.0f,25.0f); 
    	glVertex3f(8.0f,18.0f,25.0f); 
    	glVertex3f(-8.0f,18.0f,25.0f);
   	glEnd(); 
  	glPopMatrix(); 

  	// bawah 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
      	glVertex3f(8.0f,3.0f,40.0f); 
      	glVertex3f(-8.0f,3.0f,40.0f); 
      	glVertex3f(-8.0f,3.0f,33.0f); 
      	glVertex3f(8.0f,3.0f,33.0f); 
      	
      	glVertex3f(8.0f,7.0f,33.0f); 
      	glVertex3f(-8.0f,7.0f,33.0f); 
      	glVertex3f(-8.0f,7.0f,25.0f); 
      	glVertex3f(8.0f,7.0f,25.0f); 
    glEnd(); 
  	glPopMatrix(); 

  	// kiri 
  	glPushMatrix(); 
    glBegin(GL_POLYGON); 
	    glVertex3f(8.0f,7.0f,40.0f);
	    glVertex3f(8.0f,10.0f,40.0f);
      	glVertex3f(8.0f,18.0f,38.0f); 
	    glVertex3f(8.0f,18.0f,25.0f); 
      	glVertex3f(8.0f,7.0f,25.0f); 
    glEnd(); 
    glBegin(GL_QUADS); 
	    glVertex3f(8.0f,7.0f,40.0f);
	    glVertex3f(8.0f,3.0f,40.0f);
	    glVertex3f(8.0f,3.0f,33.0f); 
      	glVertex3f(8.0f,7.0f,33.0f); 
    glEnd(); 
  	glPopMatrix(); 

  	// kanan 
  	glPushMatrix(); 
    glBegin(GL_POLYGON); 
	    glVertex3f(-8.0f,7.0f,40.0f);
	    glVertex3f(-8.0f,10.0f,40.0f);
      	glVertex3f(-8.0f,18.0f,38.0f); 
	    glVertex3f(-8.0f,18.0f,25.0f); 
      	glVertex3f(-8.0f,7.0f,25.0f); 
    glEnd(); 
    glBegin(GL_QUADS); 
	    glVertex3f(-8.0f,7.0f,40.0f);
	    glVertex3f(-8.0f,3.0f,40.0f);
	    glVertex3f(-8.0f,3.0f,33.0f); 
      	glVertex3f(-8.0f,7.0f,33.0f); 
    glEnd(); 
  	glPopMatrix(); 
	
	// Kaca
	glPushMatrix(); 
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_QUADS); 
		glVertex3f(-7.5f,10.0f,40.05f); 
    	glVertex3f(7.5f,10.0f,40.05f); 
    	glVertex3f(7.5f,17.5f,38.2f); 
    	glVertex3f(-7.5f,17.5f,38.2f);
    glEnd(); 	
    
	// Jendela
	glBegin(GL_QUADS); 
	    glVertex3f(8.05f,10.0f,39.5f);
      	glVertex3f(8.05f,17.5f,37.5f); 
	    glVertex3f(8.05f,17.5f,30.0f); 
      	glVertex3f(8.05f,12.0f,30.0f); 

	    glVertex3f(-8.05f,10.0f,39.5f);
      	glVertex3f(-8.05f,17.5f,37.5f); 
	    glVertex3f(-8.05f,17.5f,30.0f); 
      	glVertex3f(-8.05f,12.0f,30.0f); 
    glEnd(); 
	glPopMatrix(); 
	
	// Lampu
	glPushMatrix(); 
	glColor3f(0.9, 0.5, 0.0);
    glBegin(GL_QUADS); 
		glVertex3f(5.0f,6.0f,40.02f); 
    	glVertex3f(8.0f,6.0f,40.02f); 
    	glVertex3f(8.0f,9.0f,40.02f); 
    	glVertex3f(5.5f,9.0f,40.02f);
    	
    	glVertex3f(-5.0f,6.0f,40.02f); 
    	glVertex3f(-8.0f,6.0f,40.02f); 
    	glVertex3f(-8.0f,9.0f,40.02f); 
    	glVertex3f(-5.5f,9.0f,40.02f);
	glEnd(); 	

	glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_QUADS); 
		glVertex3f(5.0f,5.0f,40.02f); 
    	glVertex3f(8.0f,5.0f,40.02f); 
    	glVertex3f(8.0f,4.0f,40.02f); 
    	glVertex3f(5.0f,4.0f,40.02f);
    	
    	glVertex3f(-5.0f,5.0f,40.02f); 
    	glVertex3f(-8.0f,5.0f,40.02f); 
    	glVertex3f(-8.0f,4.0f,40.02f); 
    	glVertex3f(-5.0f,4.0f,40.02f);
	glEnd(); 	
	glPopMatrix(); 
	
	// Aksesoris
	glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_QUADS); 
		glVertex3f(-4.0f,5.0f,40.02f); 
    	glVertex3f(4.0f,5.0f,40.02f); 
    	glVertex3f(4.3f,7.5f,40.02f); 
    	glVertex3f(-4.3f,7.5f,40.02f);
	glEnd(); 	
	glPopMatrix();
	
	/**************** Container 1 ****************/
	glColor3f(0.603, 0.078, 0.066);
	//depan 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
    	glVertex3f(-9.0f,7.0f,23.0f); 
    	glVertex3f(9.0f,7.0f,23.0f); 
    	glVertex3f(9.0f,22.0f,23.0f); 
    	glVertex3f(-9.0f,22.0f,23.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// atas 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
    	glVertex3f(-9.0f,22.0f,23.0f); 
    	glVertex3f(9.0f,22.0f,23.0f); 
    	glVertex3f(9.0f,22.0f,-8.0f); 
    	glVertex3f(-9.0f,22.0f,-8.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// belakang 
  	glPushMatrix(); 
   	glBegin(GL_QUADS); 
    	glVertex3f(-9.0f,7.0f,-8.0f); 
    	glVertex3f(9.0f,7.0f,-8.0f); 
    	glVertex3f(9.0f,22.0f,-8.0f); 
    	glVertex3f(-9.0f,22.0f,-8.0f);
   	glEnd(); 
  	glPopMatrix(); 

  	// bawah 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
      	glVertex3f(-9.0f,7.0f,23.0f); 
    	glVertex3f(9.0f,7.0f,23.0f); 
    	glVertex3f(9.0f,7.0f,-8.0f); 
    	glVertex3f(-9.0f,7.0f,-8.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// kiri 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
	    glVertex3f(9.0f,22.0f,23.0f); 
    	glVertex3f(9.0f,7.0f,23.0f); 
    	glVertex3f(9.0f,7.0f,-8.0f); 
    	glVertex3f(9.0f,22.0f,-8.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// kanan 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
	    glVertex3f(-9.0f,22.0f,23.0f); 
    	glVertex3f(-9.0f,7.0f,23.0f); 
    	glVertex3f(-9.0f,7.0f,-8.0f); 
    	glVertex3f(-9.0f,22.0f,-8.0f);
    glEnd(); 
  	glPopMatrix(); 
  	
  	// Aksesoris
  	glColor3f(1.0, 1.0, 0.0);
  	// Kanan
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
	    glVertex3f(-9.0f,3.0f,23.0f); 
    	glVertex3f(-9.0f,4.0f,23.0f); 
    	glVertex3f(-9.0f,4.0f,8.0f); 
    	glVertex3f(-9.0f,3.0f,8.0f);
    	
    	glVertex3f(-8.0f,3.0f,23.0f); 
    	glVertex3f(-8.0f,4.0f,23.0f); 
    	glVertex3f(-8.0f,4.0f,8.0f); 
    	glVertex3f(-8.0f,3.0f,8.0f);
    	
    	glVertex3f(-8.0f,3.0f,23.0f); 
    	glVertex3f(-9.0f,3.0f,23.0f); 
    	glVertex3f(-9.0f,3.0f,8.0f); 
    	glVertex3f(-8.0f,3.0f,8.0f);
    	
    	glVertex3f(-8.0f,4.0f,23.0f); 
    	glVertex3f(-9.0f,4.0f,23.0f); 
    	glVertex3f(-9.0f,4.0f,8.0f); 
    	glVertex3f(-8.0f,4.0f,8.0f);
    	
    	glVertex3f(-9.0f,6.0f,23.0f); 
    	glVertex3f(-9.0f,5.0f,23.0f); 
    	glVertex3f(-9.0f,5.0f,8.0f); 
    	glVertex3f(-9.0f,6.0f,8.0f);
    	
		glVertex3f(-8.0f,5.0f,23.0f); 
    	glVertex3f(-8.0f,6.0f,23.0f); 
    	glVertex3f(-8.0f,6.0f,8.0f); 
    	glVertex3f(-8.0f,5.0f,8.0f);
    	
    	glVertex3f(-8.0f,5.0f,23.0f); 
    	glVertex3f(-9.0f,5.0f,23.0f); 
    	glVertex3f(-9.0f,5.0f,8.0f); 
    	glVertex3f(-8.0f,5.0f,8.0f);
    	
    	glVertex3f(-8.0f,6.0f,23.0f); 
    	glVertex3f(-9.0f,6.0f,23.0f); 
    	glVertex3f(-9.0f,6.0f,8.0f); 
    	glVertex3f(-8.0f,6.0f,8.0f);
    	
    	glVertex3f(-9.005f,7.0f,18.5f); 
    	glVertex3f(-9.005f,3.0f,18.5f); 
    	glVertex3f(-9.005f,3.0f,17.5f); 
    	glVertex3f(-9.005f,7.0f,17.5f);
    	
    	glVertex3f(-8.005f,7.0f,18.5f); 
    	glVertex3f(-8.005f,3.0f,18.5f); 
    	glVertex3f(-8.005f,3.0f,17.5f); 
    	glVertex3f(-8.005f,7.0f,17.5f);
    	
    	glVertex3f(-9.005f,7.0f,17.5f); 
    	glVertex3f(-9.005f,3.0f,17.5f); 
    	glVertex3f(-8.005f,3.0f,17.5f); 
    	glVertex3f(-8.005f,7.0f,17.5f);
    	
    	glVertex3f(-9.005f,7.0f,18.5f); 
    	glVertex3f(-9.005f,3.0f,18.5f); 
    	glVertex3f(-8.005f,3.0f,18.5f); 
    	glVertex3f(-8.005f,7.0f,18.5f);
    	
    	glVertex3f(-9.005f,7.0f,13.5f); 
    	glVertex3f(-9.005f,3.0f,13.5f); 
    	glVertex3f(-9.005f,3.0f,12.5f); 
    	glVertex3f(-9.005f,7.0f,12.5f);
    	
    	glVertex3f(-8.005f,7.0f,13.5f); 
    	glVertex3f(-8.005f,3.0f,13.5f); 
    	glVertex3f(-8.005f,3.0f,12.5f); 
    	glVertex3f(-8.005f,7.0f,12.5f);
    	
    	glVertex3f(-9.005f,7.0f,12.5f); 
    	glVertex3f(-9.005f,3.0f,12.5f); 
    	glVertex3f(-8.005f,3.0f,12.5f); 
    	glVertex3f(-8.005f,7.0f,12.5f);
    	
    	glVertex3f(-9.005f,7.0f,13.5f); 
    	glVertex3f(-9.005f,3.0f,13.5f); 
    	glVertex3f(-8.005f,3.0f,13.5f); 
    	glVertex3f(-8.005f,7.0f,13.5f);
    glEnd(); 
  	glPopMatrix(); 
  	
  	// Kiri
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
	    glVertex3f(9.0f,3.0f,23.0f); 
    	glVertex3f(9.0f,4.0f,23.0f); 
    	glVertex3f(9.0f,4.0f,8.0f); 
    	glVertex3f(9.0f,3.0f,8.0f);
    	
    	glVertex3f(8.0f,3.0f,23.0f); 
    	glVertex3f(8.0f,4.0f,23.0f); 
    	glVertex3f(8.0f,4.0f,8.0f); 
    	glVertex3f(8.0f,3.0f,8.0f);
    	
    	glVertex3f(8.0f,3.0f,23.0f); 
    	glVertex3f(9.0f,3.0f,23.0f); 
    	glVertex3f(9.0f,3.0f,8.0f); 
    	glVertex3f(8.0f,3.0f,8.0f);
    	
    	glVertex3f(8.0f,4.0f,23.0f); 
    	glVertex3f(9.0f,4.0f,23.0f); 
    	glVertex3f(9.0f,4.0f,8.0f); 
    	glVertex3f(8.0f,4.0f,8.0f);
    	
    	glVertex3f(9.0f,6.0f,23.0f); 
    	glVertex3f(9.0f,5.0f,23.0f); 
    	glVertex3f(9.0f,5.0f,8.0f); 
    	glVertex3f(9.0f,6.0f,8.0f);
    	
		glVertex3f(8.0f,5.0f,23.0f); 
    	glVertex3f(8.0f,6.0f,23.0f); 
    	glVertex3f(8.0f,6.0f,8.0f); 
    	glVertex3f(8.0f,5.0f,8.0f);
    	
    	glVertex3f(8.0f,5.0f,23.0f); 
    	glVertex3f(9.0f,5.0f,23.0f); 
    	glVertex3f(9.0f,5.0f,8.0f); 
    	glVertex3f(8.0f,5.0f,8.0f);
    	
    	glVertex3f(8.0f,6.0f,23.0f); 
    	glVertex3f(9.0f,6.0f,23.0f); 
    	glVertex3f(9.0f,6.0f,8.0f); 
    	glVertex3f(8.0f,6.0f,8.0f);
    	
    	glVertex3f(9.005f,7.0f,18.5f); 
    	glVertex3f(9.005f,3.0f,18.5f); 
    	glVertex3f(9.005f,3.0f,17.5f); 
    	glVertex3f(9.005f,7.0f,17.5f);
    	
    	glVertex3f(8.005f,7.0f,18.5f); 
    	glVertex3f(8.005f,3.0f,18.5f); 
    	glVertex3f(8.005f,3.0f,17.5f); 
    	glVertex3f(8.005f,7.0f,17.5f);
    	
    	glVertex3f(9.005f,7.0f,17.5f); 
    	glVertex3f(9.005f,3.0f,17.5f); 
    	glVertex3f(8.005f,3.0f,17.5f); 
    	glVertex3f(8.005f,7.0f,17.5f);
    	
    	glVertex3f(9.005f,7.0f,18.5f); 
    	glVertex3f(9.005f,3.0f,18.5f); 
    	glVertex3f(8.005f,3.0f,18.5f); 
    	glVertex3f(8.005f,7.0f,18.5f);
    	
    	glVertex3f(9.005f,7.0f,13.5f); 
    	glVertex3f(9.005f,3.0f,13.5f); 
    	glVertex3f(9.005f,3.0f,12.5f); 
    	glVertex3f(9.005f,7.0f,12.5f);
    	
    	glVertex3f(8.005f,7.0f,13.5f); 
    	glVertex3f(8.005f,3.0f,13.5f); 
    	glVertex3f(8.005f,3.0f,12.5f); 
    	glVertex3f(8.005f,7.0f,12.5f);
    	
    	glVertex3f(9.005f,7.0f,12.5f); 
    	glVertex3f(9.005f,3.0f,12.5f); 
    	glVertex3f(8.005f,3.0f,12.5f); 
    	glVertex3f(8.005f,7.0f,12.5f);
    	
    	glVertex3f(9.005f,7.0f,13.5f); 
    	glVertex3f(9.005f,3.0f,13.5f); 
    	glVertex3f(8.005f,3.0f,13.5f); 
    	glVertex3f(8.005f,7.0f,13.5f);
    glEnd(); 
  	glPopMatrix(); 
	
	/**************** Container 2 ****************/
	glColor3f(0.603, 0.078, 0.066);
	//depan 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
    	glVertex3f(-9.0f,7.0f,-10.0f); 
    	glVertex3f(9.0f,7.0f,-10.0f); 
    	glVertex3f(9.0f,22.0f,-10.0f); 
    	glVertex3f(-9.0f,22.0f,-10.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// atas 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
    	glVertex3f(-9.0f,22.0f,-10.0f); 
    	glVertex3f(9.0f,22.0f,-10.0f); 
    	glVertex3f(9.0f,22.0f,-40.0f); 
    	glVertex3f(-9.0f,22.0f,-40.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// belakang 
  	glPushMatrix(); 
   	glBegin(GL_QUADS); 
    	glVertex3f(-9.0f,7.0f,-40.0f); 
    	glVertex3f(9.0f,7.0f,-40.0f); 
    	glVertex3f(9.0f,22.0f,-40.0f); 
    	glVertex3f(-9.0f,22.0f,-40.0f);
   	glEnd(); 
  	glPopMatrix(); 

  	// bawah 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
      	glVertex3f(-9.0f,7.0f,-10.0f); 
    	glVertex3f(9.0f,7.0f,-10.0f); 
    	glVertex3f(9.0f,7.0f,-40.0f); 
    	glVertex3f(-9.0f,7.0f,-40.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// kiri 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
	    glVertex3f(9.0f,22.0f,-10.0f); 
    	glVertex3f(9.0f,7.0f,-10.0f); 
    	glVertex3f(9.0f,7.0f,-40.0f); 
    	glVertex3f(9.0f,22.0f,-40.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// kanan 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
	    glVertex3f(-9.0f,22.0f,-10.0f); 
    	glVertex3f(-9.0f,7.0f,-10.0f); 
    	glVertex3f(-9.0f,7.0f,-40.0f); 
    	glVertex3f(-9.0f,22.0f,-40.0f);
    glEnd(); 
  	glPopMatrix(); 
  	
  	  	// Aksesoris
  	glColor3f(1.0, 1.0, 0.0);
  	// Kanan
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
	    glVertex3f(-9.0f,3.0f,-18.0f); 
    	glVertex3f(-9.0f,4.0f,-18.0f); 
    	glVertex3f(-9.0f,4.0f,-31.0f); 
    	glVertex3f(-9.0f,3.0f,-31.0f);
    	
    	glVertex3f(-8.0f,3.0f,-18.0f); 
    	glVertex3f(-8.0f,4.0f,-18.0f); 
    	glVertex3f(-8.0f,4.0f,-31.0f); 
    	glVertex3f(-8.0f,3.0f,-31.0f);
    	
    	glVertex3f(-8.0f,3.0f,-18.0f); 
    	glVertex3f(-9.0f,3.0f,-18.0f); 
    	glVertex3f(-9.0f,3.0f,-31.0f); 
    	glVertex3f(-8.0f,3.0f,-31.0f);
    	
    	glVertex3f(-8.0f,4.0f,-18.0f); 
    	glVertex3f(-9.0f,4.0f,-18.0f); 
    	glVertex3f(-9.0f,4.0f,-31.0f); 
    	glVertex3f(-8.0f,4.0f,-31.0f);
    	
    	glVertex3f(-9.0f,6.0f,-18.0f); 
    	glVertex3f(-9.0f,5.0f,-18.0f); 
    	glVertex3f(-9.0f,5.0f,-31.0f); 
    	glVertex3f(-9.0f,6.0f,-31.0f);
    	
		glVertex3f(-8.0f,5.0f,-18.0f); 
    	glVertex3f(-8.0f,6.0f,-18.0f); 
    	glVertex3f(-8.0f,6.0f,-31.0f); 
    	glVertex3f(-8.0f,5.0f,-31.0f);
    	
    	glVertex3f(-8.0f,5.0f,-18.0f); 
    	glVertex3f(-9.0f,5.0f,-18.0f); 
    	glVertex3f(-9.0f,5.0f,-31.0f); 
    	glVertex3f(-8.0f,5.0f,-31.0f);
    	
    	glVertex3f(-8.0f,6.0f,-18.0f); 
    	glVertex3f(-9.0f,6.0f,-18.0f); 
    	glVertex3f(-9.0f,6.0f,-31.0f); 
    	glVertex3f(-8.0f,6.0f,-31.0f);
    	
    	glVertex3f(-9.005f,7.0f,-22.0f); 
    	glVertex3f(-9.005f,3.0f,-22.0f); 
    	glVertex3f(-9.005f,3.0f,-23.0f); 
    	glVertex3f(-9.005f,7.0f,-23.0f);
    	
    	glVertex3f(-8.005f,7.0f,-22.0f); 
    	glVertex3f(-8.005f,3.0f,-22.0f); 
    	glVertex3f(-8.005f,3.0f,-23.0f); 
    	glVertex3f(-8.005f,7.0f,-23.0f);
    	
    	glVertex3f(-9.005f,7.0f,-23.0f); 
    	glVertex3f(-9.005f,3.0f,-23.0f); 
    	glVertex3f(-8.005f,3.0f,-23.0f); 
    	glVertex3f(-8.005f,7.0f,-23.0f);
    	
    	glVertex3f(-9.005f,7.0f,-22.0f); 
    	glVertex3f(-9.005f,3.0f,-22.0f); 
    	glVertex3f(-8.005f,3.0f,-22.0f); 
    	glVertex3f(-8.005f,7.0f,-22.0f);
    	
    	glVertex3f(-9.005f,7.0f,-26.0f); 
    	glVertex3f(-9.005f,3.0f,-26.0f); 
    	glVertex3f(-9.005f,3.0f,-27.0f); 
    	glVertex3f(-9.005f,7.0f,-27.0f);
    	
    	glVertex3f(-8.005f,7.0f,-26.0f); 
    	glVertex3f(-8.005f,3.0f,-26.0f); 
    	glVertex3f(-8.005f,3.0f,-27.0f); 
    	glVertex3f(-8.005f,7.0f,-27.0f);
    	
    	glVertex3f(-9.005f,7.0f,-27.0f); 
    	glVertex3f(-9.005f,3.0f,-27.0f); 
    	glVertex3f(-8.005f,3.0f,-27.0f); 
    	glVertex3f(-8.005f,7.0f,-27.0f);
    	
    	glVertex3f(-9.005f,7.0f,-26.0f); 
    	glVertex3f(-9.005f,3.0f,-26.0f); 
    	glVertex3f(-8.005f,3.0f,-26.0f); 
    	glVertex3f(-8.005f,7.0f,-26.0f);
    glEnd(); 
  	glPopMatrix(); 
  	
  	// Kiri
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
	    glVertex3f(9.0f,3.0f,-18.0f); 
    	glVertex3f(9.0f,4.0f,-18.0f); 
    	glVertex3f(9.0f,4.0f,-31.0f); 
    	glVertex3f(9.0f,3.0f,-31.0f);
    	
    	glVertex3f(8.0f,3.0f,-31.0f); 
    	glVertex3f(8.0f,4.0f,-31.0f); 
    	glVertex3f(8.0f,4.0f,-18.0f); 
    	glVertex3f(8.0f,3.0f,-18.0f);
    	
    	glVertex3f(8.0f,3.0f,-31.0f); 
    	glVertex3f(9.0f,3.0f,-31.0f); 
    	glVertex3f(9.0f,3.0f,-18.0f); 
    	glVertex3f(8.0f,3.0f,-18.0f);
    	
    	glVertex3f(8.0f,4.0f,-31.0f); 
    	glVertex3f(9.0f,4.0f,-31.0f); 
    	glVertex3f(9.0f,4.0f,-18.0f); 
    	glVertex3f(8.0f,4.0f,-18.0f);
    	
    	glVertex3f(9.0f,6.0f,-31.0f); 
    	glVertex3f(9.0f,5.0f,-31.0f); 
    	glVertex3f(9.0f,5.0f,-18.0f); 
    	glVertex3f(9.0f,6.0f,-18.0f);
    	
		glVertex3f(8.0f,5.0f,-31.0f); 
    	glVertex3f(8.0f,6.0f,-31.0f); 
    	glVertex3f(8.0f,6.0f,-18.0f); 
    	glVertex3f(8.0f,5.0f,-18.0f);
    	
    	glVertex3f(8.0f,5.0f,-31.0f); 
    	glVertex3f(9.0f,5.0f,-31.0f); 
    	glVertex3f(9.0f,5.0f,-18.0f); 
    	glVertex3f(8.0f,5.0f,-18.0f);
    	
    	glVertex3f(8.0f,6.0f,-31.0f); 
    	glVertex3f(9.0f,6.0f,-31.0f); 
    	glVertex3f(9.0f,6.0f,-18.0f); 
    	glVertex3f(8.0f,6.0f,-18.0f);
    	
    	glVertex3f(9.005f,7.0f,-22.0f); 
    	glVertex3f(9.005f,3.0f,-22.0f); 
    	glVertex3f(9.005f,3.0f,-23.0f); 
    	glVertex3f(9.005f,7.0f,-23.0f);
    	
    	glVertex3f(8.005f,7.0f,-22.0f); 
    	glVertex3f(8.005f,3.0f,-22.0f); 
    	glVertex3f(8.005f,3.0f,-23.0f); 
    	glVertex3f(8.005f,7.0f,-23.0f);
    	
    	glVertex3f(9.005f,7.0f,-23.0f); 
    	glVertex3f(9.005f,3.0f,-23.0f); 
    	glVertex3f(8.005f,3.0f,-23.0f); 
    	glVertex3f(8.005f,7.0f,-23.0f);
    	
    	glVertex3f(9.005f,7.0f,-22.0f); 
    	glVertex3f(9.005f,3.0f,-22.0f); 
    	glVertex3f(8.005f,3.0f,-22.0f); 
    	glVertex3f(8.005f,7.0f,-22.0f);
    	
    	glVertex3f(9.005f,7.0f,-26.0f); 
    	glVertex3f(9.005f,3.0f,-26.0f); 
    	glVertex3f(9.005f,3.0f,-27.0f); 
    	glVertex3f(9.005f,7.0f,-27.0f);
    	
    	glVertex3f(8.005f,7.0f,-26.0f); 
    	glVertex3f(8.005f,3.0f,-26.0f); 
    	glVertex3f(8.005f,3.0f,-27.0f); 
    	glVertex3f(8.005f,7.0f,-27.0f);
    	
    	glVertex3f(9.005f,7.0f,-27.0f); 
    	glVertex3f(9.005f,3.0f,-27.0f); 
    	glVertex3f(8.005f,3.0f,-27.0f); 
    	glVertex3f(8.005f,7.0f,-27.0f);
    	
    	glVertex3f(9.005f,7.0f,-26.0f); 
    	glVertex3f(9.005f,3.0f,-26.0f); 
    	glVertex3f(8.005f,3.0f,-26.0f); 
    	glVertex3f(8.005f,7.0f,-26.0f);
    glEnd(); 
  	glPopMatrix(); 
		
	/******************* Mesin *******************/
	glColor3f(0.0, 0.00, 0.00);
	// Kepala
	//depan 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
    	glVertex3f(-6.0f,7.0f,33.0f); 
    	glVertex3f(6.0f,7.0f,33.0f); 
    	glVertex3f(6.0f,3.0f,33.0f); 
    	glVertex3f(-6.0f,3.0f,33.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// atas 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
    	glVertex3f(-6.0f,7.0f,33.0f); 
    	glVertex3f(6.0f,7.0f,33.0f); 
    	glVertex3f(6.0f,7.0f,26.0f); 
    	glVertex3f(-6.0f,7.0f,26.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// belakang 
  	glPushMatrix(); 
   	glBegin(GL_QUADS); 
    	glVertex3f(-6.0f,7.0f,26.0f); 
    	glVertex3f(6.0f,7.0f,26.0f); 
    	glVertex3f(6.0f,3.0f,26.0f); 
    	glVertex3f(-6.0f,3.0f,26.0f);
   	glEnd(); 
  	glPopMatrix(); 

  	// bawah 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
      	glVertex3f(-6.0f,3.0f,33.0f); 
    	glVertex3f(6.0f,3.0f,33.0f); 
    	glVertex3f(6.0f,3.0f,26.0f); 
    	glVertex3f(-6.0f,3.0f,26.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// kiri 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
	    glVertex3f(6.0f,3.0f,33.0f); 
    	glVertex3f(6.0f,7.0f,33.0f); 
    	glVertex3f(6.0f,7.0f,26.0f); 
    	glVertex3f(6.0f,3.0f,26.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// kanan 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
	    glVertex3f(-6.0f,3.0f,33.0f); 
    	glVertex3f(-6.0f,7.0f,33.0f); 
    	glVertex3f(-6.0f,7.0f,26.0f); 
    	glVertex3f(-6.0f,3.0f,26.0f);
    glEnd(); 
  	glPopMatrix(); 
  	
	// Kontainer 1
	//depan 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
    	glVertex3f(-7.0f,7.0f,20.0f); 
    	glVertex3f(7.0f,7.0f,20.0f); 
    	glVertex3f(7.0f,3.0f,20.0f); 
    	glVertex3f(-7.0f,3.0f,20.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// atas 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
    	glVertex3f(-7.0f,7.0f,20.0f); 
    	glVertex3f(7.0f,7.0f,20.0f); 
    	glVertex3f(7.0f,7.0f,2.0f); 
    	glVertex3f(-7.0f,7.0f,2.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// belakang 
  	glPushMatrix(); 
   	glBegin(GL_QUADS); 
    	glVertex3f(-7.0f,7.0f,2.0f); 
    	glVertex3f(7.0f,7.0f,2.0f); 
    	glVertex3f(7.0f,3.0f,2.0f); 
    	glVertex3f(-7.0f,3.0f,2.0f);
   	glEnd(); 
  	glPopMatrix(); 

  	// bawah 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
      	glVertex3f(-7.0f,3.0f,20.0f); 
    	glVertex3f(7.0f,3.0f,20.0f); 
    	glVertex3f(7.0f,3.0f,2.0f); 
    	glVertex3f(-7.0f,3.0f,2.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// kiri 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
	    glVertex3f(7.0f,3.0f,20.0f); 
    	glVertex3f(7.0f,7.0f,20.0f); 
    	glVertex3f(7.0f,7.0f,2.0f); 
    	glVertex3f(7.0f,3.0f,2.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// kanan 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
	    glVertex3f(-7.0f,3.0f,20.0f); 
    	glVertex3f(-7.0f,7.0f,20.0f); 
    	glVertex3f(-7.0f,7.0f,2.0f); 
    	glVertex3f(-7.0f,3.0f,2.0f);
    glEnd(); 
  	glPopMatrix(); 
 	
	// Kontainer 2
	//depan 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
    	glVertex3f(-7.0f,7.0f,-14.0f); 
    	glVertex3f(7.0f,7.0f,-14.0f); 
    	glVertex3f(7.0f,3.0f,-14.0f); 
    	glVertex3f(-7.0f,3.0f,-14.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// atas 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
    	glVertex3f(-7.0f,7.0f,-14.0f); 
    	glVertex3f(7.0f,7.0f,-14.0f); 
    	glVertex3f(7.0f,7.0f,-36.0f); 
    	glVertex3f(-7.0f,7.0f,-36.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// belakang 
  	glPushMatrix(); 
   	glBegin(GL_QUADS); 
    	glVertex3f(-7.0f,7.0f,-36.0f); 
    	glVertex3f(7.0f,7.0f,-36.0f); 
    	glVertex3f(7.0f,3.0f,-36.0f); 
    	glVertex3f(-7.0f,3.0f,-36.0f);
   	glEnd(); 
  	glPopMatrix(); 

  	// bawah 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
      	glVertex3f(-7.0f,3.0f,-14.0f); 
    	glVertex3f(7.0f,3.0f,-14.0f); 
    	glVertex3f(7.0f,3.0f,-36.0f); 
    	glVertex3f(-7.0f,3.0f,-36.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// kiri 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
	    glVertex3f(7.0f,3.0f,-14.0f); 
    	glVertex3f(7.0f,7.0f,-14.0f); 
    	glVertex3f(7.0f,7.0f,-36.0f); 
    	glVertex3f(7.0f,3.0f,-36.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// kanan 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
	    glVertex3f(-7.0f,3.0f,-14.0f); 
    	glVertex3f(-7.0f,7.0f,-14.0f); 
    	glVertex3f(-7.0f,7.0f,-36.0f); 
    	glVertex3f(-7.0f,3.0f,-36.0f);
    glEnd(); 
  	glPopMatrix(); 
  	
  	/************ Sambungan Container ************/
  	// atas 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
    	glVertex3f(-2.0f,6.5f,26.0f); 
    	glVertex3f(2.0f,6.5f,26.0f); 
    	glVertex3f(2.0f,6.5f,20.0f); 
    	glVertex3f(-2.0f,6.5f,20.0f);
    
    	glVertex3f(-2.0f,6.5f,2.0f); 
    	glVertex3f(2.0f,6.5f,2.0f); 
    	glVertex3f(2.0f,6.5f,-14.0f); 
    	glVertex3f(-2.0f,6.5f,-14.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// bawah 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
      	glVertex3f(-2.0f,4.5f,20.0f); 
    	glVertex3f(2.0f,4.5f,20.0f); 
    	glVertex3f(2.0f,4.5f,26.0f); 
    	glVertex3f(-2.0f,4.5f,26.0f);

      	glVertex3f(-2.0f,4.5f,-14.0f); 
    	glVertex3f(2.0f,4.5f,-14.0f); 
    	glVertex3f(2.0f,4.5f,2.0f); 
    	glVertex3f(-2.0f,4.5f,2.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// kiri 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
	    glVertex3f(2.0f,4.5f,-14.0f); 
    	glVertex3f(2.0f,6.5f,-14.0f); 
    	glVertex3f(2.0f,6.5f,2.0f); 
    	glVertex3f(2.0f,4.5f,2.0f);
    	
	    glVertex3f(2.0f,4.5f,26.0f); 
    	glVertex3f(2.0f,6.5f,26.0f); 
    	glVertex3f(2.0f,6.5f,20.0f); 
    	glVertex3f(2.0f,4.5f,20.0f);
    glEnd(); 
  	glPopMatrix(); 

  	// kanan 
  	glPushMatrix(); 
    glBegin(GL_QUADS); 
	    glVertex3f(-2.0f,4.5f,20.0f); 
    	glVertex3f(-2.0f,6.5f,20.0f); 
    	glVertex3f(-2.0f,6.5f,26.0f); 
    	glVertex3f(-2.0f,4.5f,26.0f);
    
	    glVertex3f(-2.0f,4.5f,-14.0f); 
    	glVertex3f(-2.0f,6.5f,-14.0f); 
    	glVertex3f(-2.0f,6.5f,2.0f); 
    	glVertex3f(-2.0f,4.5f,2.0f);
    glEnd(); 
  	glPopMatrix(); 
	
	/******************** Roda ********************/
	glColor3f(0.2,0.2,0.2);
	// Kanan
	// Depan
	glPushMatrix();
	for(i=0;i<=360;i++){
		glPushMatrix();
		glTranslatef(-6.0,3.5,29.0);
		glRotated(90,0,0,1);
		glRotated(i,0,1,0);
		glScalef(23,5,10);
		glBegin(GL_QUADS);
			glVertex3f(0,0,0);
			glVertex3f(0.15,0,0);
			glVertex3f(0.15,0.6,0);
			glVertex3f(0,0.6,0);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
	
	// Kontainer 1
	glPushMatrix();
	for(i=0;i<=360;i++){
		glPushMatrix();
		glTranslatef(-7.0,3.5,4.0);
		glRotated(90,0,0,1);
		glRotated(i,0,1,0);
		glScalef(23,5,10);
		glBegin(GL_QUADS);
			glVertex3f(0,0,0);
			glVertex3f(0.15,0,0);
			glVertex3f(0.15,0.6,0);
			glVertex3f(0,0.6,0);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
	
	// Kontainer 2
	glPushMatrix();
	for(i=0;i<=360;i++){
		glPushMatrix();
		glTranslatef(-7.0,3.5,-14.0);
		glRotated(90,0,0,1);
		glRotated(i,0,1,0);
		glScalef(23,5,10);
		glBegin(GL_QUADS);
			glVertex3f(0,0,0);
			glVertex3f(0.15,0,0);
			glVertex3f(0.15,0.6,0);
			glVertex3f(0,0.6,0);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix();
	for(i=0;i<=360;i++){
		glPushMatrix();
		glTranslatef(-7.0,3.5,-35.0);
		glRotated(90,0,0,1);
		glRotated(i,0,1,0);
		glScalef(23,5,10);
		glBegin(GL_QUADS);
			glVertex3f(0,0,0);
			glVertex3f(0.15,0,0);
			glVertex3f(0.15,0.6,0);
			glVertex3f(0,0.6,0);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
	
	// Kiri
	// Depan
	glPushMatrix();
	for(i=0;i<=360;i++){
		glPushMatrix();
		glTranslatef(9.0,3.5,29.0);
		glRotated(90,0,0,1);
		glRotated(i,0,1,0);
		glScalef(23,5,10);
		glBegin(GL_QUADS);
			glVertex3f(0,0,0);
			glVertex3f(0.15,0,0);
			glVertex3f(0.15,0.6,0);
			glVertex3f(0,0.6,0);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
	
	// Kontainer 1
	glPushMatrix();
	for(i=0;i<=360;i++){
		glPushMatrix();
		glTranslatef(10.0,3.5,4.0);
		glRotated(90,0,0,1);
		glRotated(i,0,1,0);
		glScalef(23,5,10);
		glBegin(GL_QUADS);
			glVertex3f(0,0,0);
			glVertex3f(0.15,0,0);
			glVertex3f(0.15,0.6,0);
			glVertex3f(0,0.6,0);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
	
	// Kontainer 2
	glPushMatrix();
	for(i=0;i<=360;i++){
		glPushMatrix();
		glTranslatef(10.0,3.5,-14.0);
		glRotated(90,0,0,1);
		glRotated(i,0,1,0);
		glScalef(23,5,10);
		glBegin(GL_QUADS);
			glVertex3f(0,0,0);
			glVertex3f(0.15,0,0);
			glVertex3f(0.15,0.6,0);
			glVertex3f(0,0.6,0);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix();
	for(i=0;i<=360;i++){
		glPushMatrix();
		glTranslatef(10.0,3.5,-35.0);
		glRotated(90,0,0,1);
		glRotated(i,0,1,0);
		glScalef(23,5,10);
		glBegin(GL_QUADS);
			glVertex3f(0,0,0);
			glVertex3f(0.15,0,0);
			glVertex3f(0.15,0.6,0);
			glVertex3f(0,0.6,0);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
	glPopMatrix(); 	
} 

void Box() {
	glPushMatrix();
	glBegin(GL_QUADS);
		glColor3f(0.3,0.2,0.0);
		// depan
		glVertex3f( 10.0, 0.0,4.0);
		glVertex3f( 10.0,12.0,4.0);
		glVertex3f(-10.0,12.0,4.0);
		glVertex3f(-10.0, 0.0,4.0);
		
		// belakang
		glVertex3f( 10.0, 0.0,-4.0);
		glVertex3f( 10.0,12.0,-4.0);
		glVertex3f(-10.0,12.0,-4.0);
		glVertex3f(-10.0, 0.0,-4.0);
		
		// atas
		glVertex3f( 10.0,12.0, 4.0);
		glVertex3f( 10.0,12.0,-4.0);
		glVertex3f(-10.0,12.0,-4.0);
		glVertex3f(-10.0,12.0, 4.0);
		
		// bawah
		glVertex3f( 10.0,0.0, 4.0);
		glVertex3f( 10.0,0.0,-4.0);
		glVertex3f(-10.0,0.0,-4.0);
		glVertex3f(-10.0,0.0, 4.0);
		
		// kiri
		glVertex3f(10.0, 0.0, 4.0);
		glVertex3f(10.0,12.0, 4.0);
		glVertex3f(10.0,12.0,-4.0);
		glVertex3f(10.0, 0.0,-4.0);
		
		//kanan
		glVertex3f(-10.0, 0.0, 4.0);
		glVertex3f(-10.0,12.0, 4.0);
		glVertex3f(-10.0,12.0,-4.0);
		glVertex3f(-10.0, 0.0,-4.0);
	glEnd();
	glPopMatrix(); 	
}

void Tree(){
	double i;
	const float MIN = -200, MAX = 300;
	for(i=MIN;i<MAX;i+=100.0){
		//Batang
		glPushMatrix();
			glColor3f(0.7, 0.5, 0.2);
			glScalef(2, 20, 2);
			glTranslatef(-60,0.7,i);
			glutSolidSphere(1.0, 20, 16);
		glPopMatrix();
		//Daun
		glPushMatrix();
			glColor3f(0.3, 0.9, 0.0);
			glScalef(2, 2, 2);
			glTranslatef(-60,10,i);
			glRotatef(270, 1, 0, 0);
			glutSolidCone(10, 28, 20, 1);
		glPopMatrix();
		glPushMatrix();
			glColor3f(0.5, 1.0, 0.0);
			glScalef(2, 2, 2);
			glTranslatef(-60,20,i);
			glRotatef(270, 1, 0, 0);
			glutSolidCone(8, 23, 18, 1);
		glPopMatrix();
		glPushMatrix();
			glColor3f(0.7, 1.0, 0.10);
			glScalef(2, 2, 2);
			glTranslatef(-60,30,i);
			glRotatef(270, 1, 0, 0);
			glutSolidCone(6, 18, 16, 1);
		glPopMatrix();
	}
}

void BatuHiasJalan(){
	double j;
	const float MIN = -450, MAX = 500;
	for(j=MIN;j<MAX;j+=75.0){
		glPushMatrix();	
			glColor3f(0.0, 0.0, 0.0);
			glTranslatef(-140,8,j);
			glutSolidSphere(8, 5, 5);
		glPopMatrix();
	}
}

void Matahari(){
	glPushMatrix();
		glColor3f(1.00f, 1.00f, 0.50f);
		glTranslatef(-100,270,250);
		glutSolidSphere(25, 55, 55);
	glPopMatrix();
}

void Awan(double ax, double ay, double az){
	glPushMatrix();
	glTranslatef(ax,ay,az);  
	glScalef(0.3, 0.3, 0.3);
	glColor3f(0.6, 1.0, 1.0);
		glPushMatrix(); 
			glutSolidSphere(50, 40, 40);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(70,20,-2);
			glutSolidSphere(90, 40, 40);
		glPopMatrix();   
		glPushMatrix();
			glTranslatef(160,-3,5);
			glutSolidSphere(70, 40, 40);
		glPopMatrix();   
		glPushMatrix();
			glTranslatef(225,-10,4);
			glutSolidSphere(45, 40, 40);
		glPopMatrix();      
	glPopMatrix();
}


void specialPressKey(int key, int x, int y) { 
  	// Fungsi ini akan dijalankan saat tombol keyboard ditekan dan belum dilepas 
  	// Selama tombol ditekan, variabel angle dan move diubah => kamera bergerak 
	switch (key) { 
		case GLUT_KEY_LEFT : 
			deltaXAngle = -0.01f;
			break; 
    	case GLUT_KEY_RIGHT : 
			deltaXAngle = 0.01f;
			break; 
    	case GLUT_KEY_UP : 
			deltaYAngle = 0.01f;
			break; 
		case GLUT_KEY_DOWN : 
			deltaYAngle = -0.01f;
			break;  
  	} 
} 

void specialReleaseKey(int key, int x, int y) { 
  // Fungsi ini akan dijalankan saat tekanan tombol keyboard dilepas 
  // Saat tombol dilepas, variabel angle dan move diset nol => kamera berhenti 
	switch (key) { 
		case GLUT_KEY_LEFT : 
			if (deltaXAngle < 0.0f) 
          		deltaXAngle = 0.0f; 
       		break; 
    	case GLUT_KEY_RIGHT : 
			if (deltaXAngle > 0.0f) 
       			deltaXAngle = 0.0f; 
       		break; 
    	case GLUT_KEY_UP : 
			if (deltaYAngle > 0.0f) 
       			deltaYAngle = 0.0f; 
       		break; 
    	case GLUT_KEY_DOWN: 
			if (deltaYAngle < 0.0f) 
       			deltaYAngle = 0.0f;
	   		break;
	} 
} 

void normalPressKey(unsigned char key, int x, int y) { 
  	// Fungsi ini akan dijalankan saat tombol keyboard ditekan dan belum dilepas 
  	// Selama tombol ditekan, variabel angle dan move diubah => kamera bergerak 
	switch (key) {
    	case 'w' : 
			deltaZMove = 5;
			break; 
		case 's' : 
			deltaZMove = -5;
			break; 
        	
        case 'W' :
        	if (posDepanTruk<MMax-15){
        		if (posDepanTruk!=posBelakangBox || posKiriTruk<posKananBox || posKananTruk>posKiriBox){
	   				posZTruk += 2;
	        		posDepanTruk=posZTruk+40;
	        		posBelakangTruk=posZTruk-40;
	   			}
        	}
	   		break;
	   	case 'S' :
	   		if (posBelakangTruk>MMin+15){
	   			if (posBelakangTruk!=posDepanBox || posKiriTruk<posKananBox || posKananTruk>posKiriBox){
	   				posZTruk -= 2;
	        		posBelakangTruk=posZTruk-40;
	        		posDepanTruk=posZTruk+40;
	   			}
        	}
	   		break;
	   	case 'E' :
	   		if(posKananTruk>=maxKananJalan){
	   			if (posKananTruk != posKiriBox || posBelakangTruk>posDepanBox || posDepanTruk<posBelakangBox){
		   			posXTruk -= 1;
		   			posKananTruk=posXTruk-9;
		        	posKiriTruk=posXTruk+9;
		        	posZTruk += 1;
	        		posDepanTruk=posZTruk+40;
	        		posBelakangTruk=posZTruk-40;
	   			} 
	   		}
	   		break;
	   	case 'Q' :
	   		if(posKiriTruk<=maxKiriJalan){
	   			if (posKiriTruk!=posKananBox || posBelakangTruk>posDepanBox || posDepanTruk<posBelakangBox){
	   				posXTruk += 1;
		   			posKananTruk=posXTruk-9;
		        	posKiriTruk=posXTruk+9;
		        	posZTruk += 1;
	        		posDepanTruk=posZTruk+40;
	        		posBelakangTruk=posZTruk-40;
	   			} 
	   		}
	   		break;
	   	case 'D' :
	   		if(posKananTruk>=maxKananJalan){
	   			if (posKananTruk != posKiriBox || posBelakangTruk>posDepanBox || posDepanTruk<posBelakangBox){
		   			posXTruk -= 1;
		   			posKananTruk=posXTruk-9;
		        	posKiriTruk=posXTruk+9;
		        	posZTruk -= 1;
	        		posDepanTruk=posZTruk+40;
	        		posBelakangTruk=posZTruk-40;
	   			} 
	   		}
	   		break;
	   	case 'A' :
	   		if(posKiriTruk<=maxKiriJalan){
	   			if (posKiriTruk!=posKananBox || posBelakangTruk>posDepanBox || posDepanTruk<posBelakangBox){
	   				posXTruk += 1;
		   			posKananTruk=posXTruk-9;
		        	posKiriTruk=posXTruk+9;
		        	posZTruk -= 1;
	        		posDepanTruk=posZTruk+40;
	        		posBelakangTruk=posZTruk-40;
	   			} 
	   		}
	   		break;
	   	case 32:
         	posXTruk=0, posYTruk=0, posZTruk=-80;
			posDepanTruk=posZTruk+40, posBelakangTruk=posZTruk-40;
			posKananTruk=posXTruk-10, posKiriTruk=posXTruk+10;
			break; 
     	case 27: 
        	exit(0); 
        default: 
        	break;
  	} 
} 

void normalReleaseKey(unsigned char key, int x, int y) { 
  // Fungsi ini akan dijalankan saat tekanan tombol keyboard dilepas 
  // Saat tombol dilepas, variabel angle dan move diset nol => kamera berhenti 
	switch (key) { 
   		case 'w' : 
			if (deltaZMove > 0) 
       			deltaZMove = 0; 
       			break; 
    	case 's' :
			if (deltaZMove < 0) 
       			deltaZMove = 0;
	   		break;
	} 
} 

void objek(){
	glPushMatrix();
	// Truk
	glPushMatrix();
		glTranslatef(posXTruk,posYTruk,posZTruk);
  		Truck(); 
	glPopMatrix();
	
	// Box
	glPushMatrix();
		glTranslatef(posXBox,posYBox,posZBox);
		Box();
	glPopMatrix();
	
	glPopMatrix();
}

void display() { 
  // Kalau move dan angle tidak nol, gerakkan kamera... 
  	if (deltaZMove) 
    	moveMeFlat(deltaZMove); 
	if (deltaXAngle) { 
    	xAngle += deltaXAngle; 
    	orientMeSide(xAngle); 
  	} 
  	if (deltaYAngle) {
  		yAngle += deltaYAngle;
  		orientMeUp(yAngle);
  	}
  	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	glPushMatrix();
		// Opsi Kamera
		
	  	// Gambar background 
	  	Road();
	  	Rumah1();
	  	Rumah2();
	  	Rumah3();
	  	Rumah4();
	  	Rumah5();
		Pohon1();
	  	Pohon2();
	  	Pohon3();
	  	Pohon4();
	  	Pohon5();
	  	Tree();
	  	Matahari();
	  	BatuHiasJalan();
	  	Awan(150, 250, -300);
	  	Awan(0, 200, -300);
	  	Awan(-150, 400, -300);
	  	Awan(0, 250, 0);
	  	Awan(-150, 200, 0);
	  	Awan(-300, 250, 0);
	  	Awan(150, 250, 100);
	  	Awan(0, 200, 100);
	  	Awan(-150, 250, 100);
	  	Awan(0, 250, 400);
	  	Awan(-150, 200, 400);
	  	Awan(-300, 250, 400);
	  	// Gambar objek di sini... 
	  	objek();
  	glPopMatrix();
  	glutSwapBuffers(); 
  	glFlush(); 
} 

// Variable untuk pencahayaan  
const GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.0f }; 
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f }; 
const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f }; 
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; 
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
const GLfloat high_shininess[] = { 500.0f }; 

void lighting(){ 
	// Fungsi mengaktifkan pencahayaan 
  	glEnable(GL_DEPTH_TEST); 
  	glDepthFunc(GL_LESS); 
  	glEnable(GL_LIGHT0); 
  	glEnable(GL_NORMALIZE); 
  	glEnable(GL_COLOR_MATERIAL); 
  	glEnable(GL_LIGHTING); 
  	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); 
  	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); 
  	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); 
  	glLightfv(GL_LIGHT0, GL_POSITION, light_position); 
  	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); 
  	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); 
  	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); 
  	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess); 
} 

void init(void) 
{ 
  	glEnable (GL_DEPTH_TEST); 
  	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
} 

int main(int argc, char **argv) 
{ 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); 
	glutInitWindowPosition(100,100); 
	glutInitWindowSize(640,480); 
	glutCreateWindow("Truk Gandeng 3D"); 
//	glutIgnoreKeyRepeat(1); // Mengabaikan key repeat (saat tombol keyboard dipencet terus) 

	glutSpecialFunc(specialPressKey);
	glutSpecialUpFunc(specialReleaseKey); 
	glutKeyboardFunc(normalPressKey);
	glutKeyboardUpFunc(normalReleaseKey);
	
	glutDisplayFunc(display); 	
	glutIdleFunc(display); // Fungsi display-nya dipanggil terusmenerus
	
	glutReshapeFunc(Reshape);
	lighting();
	init();
	glClearColor(0.75, 0.75, 1.0, 1.0);
	glutMainLoop();
	return(0);
}
