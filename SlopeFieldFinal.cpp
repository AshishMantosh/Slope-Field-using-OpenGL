#include<iostream>
#include<cstdlib>
#include<GL/freeglut.h>
#include<GL/gl.h>
#include<vector>
#include<cmath>

using namespace std;

float n1,n2;
float *arr1 = new float[1000];
float *arr2 = new float[1000];

void changeViewPort(int w, int h)
{
	glViewport(0,0,w,h);
}

void drawLine(float x, float y, float m, float gy)
{
	glColor3f(1.0f, 1.0f, 1.0f);

	float xa,ya,xb,yb;

	if(gy == 0)
	{
		ya = y + 1;
		yb = y - 1;
		xa = x;
		xb = x;
	}
	else if(abs(m)<=1)
	{
		xa = x + 1;
		xb = x - 1;
		ya = y + m;
		yb = y - m;
	}
	else
	{
		ya = y + 1;
		yb = y - 1;
		xa = x + 1.0/m;
		xb = x - 1.0/m;

	}

	glBegin(GL_LINES);

		glVertex2f(xa,ya);
		glVertex2f(xb,yb);
	
	glEnd();
	
	glFlush();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//axes
	glColor3f(1.0f, 1.0f, 1.0f);
	
	glBegin(GL_LINES);
		glVertex2d(-50,0);
		glVertex2d(50,0);
	glEnd();

	glBegin(GL_LINES);
		glVertex2d(0,50);
		glVertex2d(0,-50);
	glEnd();

	//integer points on axes
	for(int i=-50;i<50;i++)
	{
		glColor3f(1.0, 0.0, 0.0);
		
		glBegin(GL_POINTS);
			glVertex2d(i,0);
		glEnd();
	}
	for(int i=-50;i<50;i++)
	{
		glColor3f(1.0, 0.0, 0.0);

		glBegin(GL_POINTS);
			glVertex2d(0,i);
		glEnd();
	}

	glFlush();
}

void onMouseClick(int button, int state, int x, int y)
{

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		float fx=0;
        	float gy=0;
		float mx = (x*0.1666667)-50;
		float my = 50-(y*0.1666667);

		cout<<"You have clicked on the point (x,y) : "<<"("<<mx<<","<<my<<")"<<endl;

		for(int i=0,j=n1;i<n1+1;i++,j--)
		{
			fx+=arr1[i]*pow(mx,j);
		}
		for(int i=0,j=n2;i<n2+1;i++,j--)
		{
			gy+=arr2[i]*pow(my,j);
		}

		cout<<"fx ="<<fx<<endl<<"gy ="<<gy<<endl;
		
		float slope;
		slope = fx/gy;
		cout<<"slope = "<<slope<<endl;

		drawLine(mx,my,slope,gy);	
		
	}
}

void allsf(unsigned char hitkey,int x, int y)
{
	float fx=0, gy=0,slope;

	switch(hitkey)
	{
		case 27 : exit(0);
			  break;
		
		case 32 : for(int i = -50; i < 50; i+=3)
			  {
			  	for(int j = -50; j < 50; j+=3)
				{
					fx=0, gy=0;
					for(int a = 0, b = n1; a < n1 + 1; a++, b--)
					{
						fx += arr1[a] * pow(i, b);
					//cout << "fx  " << fx << " a  " << a << " b  " << b << " i   " << i << " j   " << j<<endl;

					}

					for(int a = 0, b = n2; a < n2 + 1; a++, b--)
					{
						gy += arr2[a] * pow(j, b);
					}

					slope = fx/gy;

//					cout<<slope<<endl;

					drawLine(i, j, slope, gy);

//					cout << "fx  " << fx << "  gy  " << gy <<"  slope   "<<slope<< endl;

				}	

			   }

			   break;
	}
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluOrtho2D(-50, 50, -50, 50);
}

int main(int argc, char** argv)
{
	cout<<"Enter the differential equation in the form f(x)dx=g(y)dy "<<endl;
        cout<<"Enter the degree of f(x)"<<endl;
        cin>>n1;
        cout<<"Enter the co-efficients of the equation in decreasing order of powers."<<endl;
        for(int k=0;k<n1+1;k++)
        {
                cin>>arr1[k];
        }
        cout<<"Enter the degree of g(y)"<<endl;
        cin>>n2;
        cout<<"Enter the co-efficients of the equation in decreasing order of powers."<<endl;
        for(int k=0;k<n2+1;k++)
        {
                cin>>arr2[k];
        }


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600,600);
	glutCreateWindow("Slope Field");
	glutReshapeFunc(changeViewPort);
	init();

	glutDisplayFunc(display);
	
	glutMouseFunc(onMouseClick);
	glutKeyboardFunc(allsf);

	glutMainLoop();

	return 0;
}	
			
	
	

