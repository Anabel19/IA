#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>
#include <random>
#include <ctime>	
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#define KEY_ESC 27
using namespace std;
#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27
#define GL_PI 3.14159f
int W=5;

//COMPILAR
//g++ -std=c++11 -o c practica5.cpp -lglut -lGL
//./c

using namespace std;
float rand_FloatRange(float a, float b)
{
	return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

class PerceptronMultiLayer
{
    public:
    	PerceptronMultiLayer();
		PerceptronMultiLayer(float nLearning);
    	void init(float entry[],float Outpu[]);
    	void propagation();
    	void Backpropagation();
    	void train();
    	void draw();
    private:
    	float ActiveFuntion(float x);
    	float ActiveDFuntion(float x);
    	void dibujarRecta();
    private:
	float Input[2];//2 neuronas en capa de entrada 
	float MaskLayer[2];//2 neuronas en la capa oculta
	float expected[1];//espero la salida de nuero en la capa de salida 
	float Output[1];//una neurona en la capa de salida 
	float weightB[2];//dos bias por que tengo dos capas 
	float weightEO[2][2];
	float weightOS[2][1];
	

	int mInput=2;//cantidad de neuronas en la entrada 
	int nMaskLayer=2;//cantidad de neuronas en la capa Oculta 
	int nOutPut=1;////cantidad de neuronas  en la salida
	float nLearning;
private://extras 
     float *Xext,*Yext,*Veo,*Yeo,*vos,*Yos;
     float *Yps,*Ypo,*Eos,*Eeo;



};
PerceptronMultiLayer::PerceptronMultiLayer(){}
PerceptronMultiLayer::PerceptronMultiLayer(float nLearn){
	nLearning=nLearn;
	 //llenando......Weight Eo......

	 for (int i = 0; i <mInput; ++i)
	 {	for(int j= 0; j<nMaskLayer;++j){
	 		weightEO[i][j]=rand_FloatRange(0,1);
	 	}
	 } 
	 /*weightEO[0][0]=0.1;
	 weightEO[0][1]=0.5;
	 weightEO[1][0]=-0.7;
	 weightEO[1][1]=0.3;*/


	 //llenando......Weight OS......

	 for (int i = 0; i < nMaskLayer; ++i)
	 {		for(int j= 0; j<nOutPut;++j){
	 			weightOS[i][j]=rand_FloatRange(0,1);
	 	   }
	 } 
	 /*weightOS[0][0]=0.2;
	 weightOS[1][0]=0.4;*/
    //llenando weight BIas 

	 for(int i=0;i<2;i++){	
	 	weightB[i]=rand_FloatRange(-2,2);
	 }
	
}

void PerceptronMultiLayer::init(float entry[],float Outpu[]){
 
	 for(int i=0;i<mInput;i++)
	 {
	 	Input[i]=entry[i];
	 }
	 Output[0]=Outpu[0];

}
void PerceptronMultiLayer::propagation(){	
	//Entrada para capa oculta
    float Xext[mInput]; //Input + WB;
    float Yext[nMaskLayer];

	     for(int i=0;i<mInput;++i){
	     	Xext[i]=Input[i]+weightB[0];//Input + WB;
	     }
        //
		for(int j=0; j<mInput; ++j){		//neuronas de Entrada para capa oculta
			MaskLayer[j]=0;
	        for(int z=0; z<nMaskLayer; ++z)
	                MaskLayer[j]+=Xext[z]*weightEO[z][j];
	        }

	    for(int i=0;i<nMaskLayer;++i){
	    	MaskLayer[i]=ActiveFuntion(MaskLayer[i]);
	    }

     ///
	     for(int i=0;i<nMaskLayer;++i){		// CAPA DE SALIDA 
	     	Yext[i]=MaskLayer[i]+weightB[1];
	     }
     
	    for(int i=0;i<nOutPut;++i)
	    {	expected[i]=0;
	    	for(int j=0;j<nMaskLayer;++j){
	    		expected[i]+=Yext[j]*weightOS[j][i];}
	    }
	    expected[0]=ActiveFuntion(expected[0]);
	     
}
/*void PerceptronMultiLayer::propagation(){	
	//Entrada para capa oculta
    float Xext[nInput],Yext[nMaskLayer];
    Veo=new float[nMaskLayer];
    Yeo=new float [nMaskLayer];

	     for(int i=0;i<nInput;++i){
	     	Xext[i]=Input[i]+weightB[0];
	     }
	    //Entrada para capa oculta
		for(int j=0; j<mInput; ++j){
			Veo[j]=0;
	        for(int z=0; z<nMaskLayer; ++z)
	                Veo[j]+=Xext[z]*weightEO[z][j];
	        }

	    for(int i=0;i<nMaskLayer;++i){
	    	Yeo[j]=ActiveFuntion(Veo[i]);
	    }
	    //matriz Y EXT , que es la extensión de la matriz Y EO con el segundo  elemento de la matriz W B
	     for(int i=0;i<nMaskLayer;++i){
	     	Yext[i]=Yeo[i]+weightB[1];
	     }

	vos=new float[nOutPut];
	Yos=new float[nOutPut];
	   // De capa oculta  asi la salida esperada
	    for(int i=0;i<nOutPut;++i)
	    {
	    	vos[i]=0;//fijarse

	    	for(int j=0;j<nMaskLayer;++j){
	    		vos[i]+=Yext[j]*weightOS[j][i];
	    	}
	    }
	    for(int i=0;i<nOutPut;++i){
	    	Yos[i]=ActiveFuntion(vos[i]);
	    }}*/
void PerceptronMultiLayer::Backpropagation()
{
//***************(1) Pesos de la capa de salida  **********	
   //hallando error
	float eOut,VarK,VarJ;
	float tmpweighOS[2];


     eOut=Output[0]-expected[0];
     VarK=expected[0]*(1-expected[0])*eOut;		 //calculando VariacionK para la capa de salida 
    for(int i=0;i<nMaskLayer;++i){				  //update weightOS
    	tmpweighOS[i]=weightOS[i][0];
    	weightOS[i][0]+=nLearning*(MaskLayer[i]*VarK);  
    }
    //cout<<"debug Backpropagation"<<endl;
//***************(2) Pesos de la capa Oculta **********	
 
  for(int i=0;i<nMaskLayer;++i){
  	    //cout<<"i  "<<i<<endl;
	  	VarJ=MaskLayer[i]*(1-MaskLayer[i])*(tmpweighOS[i]*VarK);
	  	//cout<<"  VarJ  "<<VarJ<<endl;
	    for(int j=0; j<mInput;++j){					 //update Weight weighEO
	    //cout<<"debug Backpropagation  VarJ  ......."<<"j  "<<j<<VarJ<<endl;
	  	  weightEO[j][i]+=nLearning*Input[j]*VarJ;
	  	  //cout<< "weightEO  "<<"("<<j<<" , "<<i<<" )   "<< weightEO[j][i]<<endl;
	  	}
  }
  //cout<<"debug Backpropagation  222"<<endl;
   
}
/*void PerceptronMultiLayer::Backpropagation(){	
   //hallando error
    Eos=new float[nOutPut];
	for(int i=0;i<nOutPut;++i)
		{
			Eos[i]=Output[i]-Yos[i];
		}
   
   //Calcular la matriz Y P S = f 0 (V OS )
 	Yps=new float[nOutPut];

 	for(int i=0;i<nOutPut;++i){
    	Yps[j]=ActiveDFuntion(vos[i]);
    }

   //update weightOS
    for(int i=0;i<nMaskLayer,++i)
    {
    	
    		for(int k=0;k<nOutPut;++k){
    			weightOS[i][k]+=nLearning*(Yext[k]*(Eos[k]*Yps[k]));
    	    }
    }

    //hallando error 

   Eeo=new float[nMaskLayer];

    for(int i=0;i<nMaskLayer;++i)
	    {
	    	Eeo[i]=0;
	    	for(int j=0;j<nOutPut;++j){
	    		Eeo[i]=weightOS[i][j]*Yps[j];
	    	}
	    }


	 //Ypos;

	Ypo=new float[nMaskLayer];
	for(int i=0;i<nMaskLayer;++i){
	    	Ypo[j]=ActiveDFuntion(Veo[i]);
	    }

    //UPDATE WEIGT eo
   for(int i=0;i<nInput;++i)
   {
	   	for(int j=0;j<nMaskLayer;++j){

	   	    weightEO[i][j]+=nLearning*(Xext[j]*(Eeo[j]*Ypo[j]))	
	   	}
   }



 	for(int j=0; j<mInput; ++j){
        for(int z=0; z<nMaskLayer; ++z)
                MaskLayer[j]+=Input[z]*weightEO[z][j];
        }

    for(int i=0;i<nMaskLayer;++i){
    	MaskLayer[j]=ActiveFuntion(MaskLayer[i]);
    }
   // De capa oculta  asi la salida esperada
    for(int i=0;i<nOutPut;++i)
    {
    	expected[i]=0;//fijarse

    	for(int j=0;j<nMaskLayer;++j){
    		expected[i]+=MaskLayer[j]*weightOS[j][i];
    	}
    }
    for(int i=0;i<nOutPut;++i){
    	expected[i]=ActiveFuntion(expected[i]);
    } 
}*/

float PerceptronMultiLayer::ActiveFuntion(float x){
	//sigmoidal
	float tmp=1+exp(-x);
		return 1/tmp;
}
float PerceptronMultiLayer::ActiveDFuntion(float x){
	float tmp,tmp2;
	tmp=exp(-x);
	tmp2=exp(x);
	return tmp/(pow(tmp2-tmp,2));
}

/*void PerceptronMultiLayer::dibujarRecta(){
	float tmp=0;
	float m;
	float b;
	glBegin(GL_LINES);
	    m=-weight[0]/weight[1];
	    b=-Bias/weight[1];
		glVertex2f(-5,m*-5+b);
		glVertex2f(5,m*5+b);
		cout<<"Ecuacion  y= "<<m<<" x +"<<b<<endl;
	   
    glEnd();
}*/
void PerceptronMultiLayer::train(){

	int iT=0;
	float error=10;
    //cout<<"		start error "<<error<<endl;
	
	while(error>0.1)
	{  
		propagation();
		//cout<<"debug"<<endl;
		Backpropagation();
		//cout<<"debug ........"<<endl;
		error=Output[0]-expected[0];
		iT+=1;
	}

	/*cout<<"Lo hizo en "<<iT<<endl;
	//dibujarRecta();
	cout<<" error  Fin  "<<error<<endl;*/

}
void Circle(float x,float y ,float r)
{
	 float i;
	 int precision = 20;
	 
	 glBegin(GL_LINE_LOOP);
		
	       for (i=0; i< GL_PI*2; i = i + (GL_PI/precision)) {
		      glVertex2f(r*cosf(i)+x,r*sinf(i)+y);
	  		}
    glEnd();
}
void PerceptronMultiLayer::draw(){
	glBegin(GL_LINES);
      glColor3f(1.0f,1.0f,1.0f);
      glVertex2f(-W,0);
      glVertex2f(W,0);
      glVertex2f(0,-W);
      glVertex2f(0,W);
   glEnd();

   glColor3d(255,255,0);//CUANDO ES 1 =AMARILLO
    Circle(-1,-1,0.1);
    Circle(1,1,0.1);
    
    glColor3d(255,0,0);
    Circle(-1,1,0.1);
    Circle(1,-1,0.1);

    train();

}
//************************************EL trabajo***************************
PerceptronMultiLayer *RNP;
float Paterns[4][2]={{-1,-1},{-1,1},{1,-1},{1,1}};
float OutputXOR[4][1];
int i=0;

void funcion(){


	float nLearning;
	cout<<" 											  "<<endl;
	cout<<"****************PERCEPTRON MULTILAYER**********"<<endl;
	cout<<" 											  "<<endl;

	cout<<"tasa de aprendizaje entre 0 y 1 :";
	cin>>nLearning;

	/*cout<<"----------------- Funcion AND -----------------"<<endl;
	
	//Cuatro patrones con dos entradas;
    float Paterns[4][2]={{-1,-1},{-1,1},{1,-1},{1,1}};
    float OutputAND[4][1]={{-1},{-1},{-1},{1}};
	//Perceptron RNP(nLearning);
	RNP=new PerceptronMultiLayer(nLearning);
	//entrenando;
	for(int i=0;i<4;++i)
	{
      cout<<"		-> i "<<i<<endl;
      RNP->init(Paterns[i],OutputAND[i]);
      RNP->train();
      
	}
	cout<<"termino"<<endl;
    cout<<endl;
	cout<<"----------------- Funcion OR -----------------"<<endl;
	
	//Cuatro patrones con dos entradas;
    //float Paterns[4][2]={{-1,-1},{-1,1},{1,-1},{1,1}};
    float OutputOR[4][1]={{-1},{1},{1},{1}};
	//Perceptron RNP(nLearning);
	RNP=new PerceptronMultiLayer(nLearning);
	//entrenando;
	for(int i=0;i<4;i++)
	{
      RNP->init(Paterns[i],OutputOR[i]);
      RNP->train();
	}*/
	cout<<"----------------- Funcion XOR -----------------"<<endl;
	
	//Cuatro patrones con dos entradas;
    //float Paterns[4][2]={{0,1},{1,0},{1,1},{0,0}};

    OutputXOR[0][0]={1};
    OutputXOR[1][0]={1};
    OutputXOR[2][0]={0};
    OutputXOR[3][0]={0};
	//Perceptron RNP(nLearning);
	RNP=new PerceptronMultiLayer(nLearning);
	//entrenando;
	/*for(int i=0;i<4;i++)
	{
      RNP->init(Paterns[i],OutputXOR[i]);
      RNP->train();
	}*/

}

GLvoid initGL()
{
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(RED, GREEN, BLUE, ALPHA);
}

GLvoid window_display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//PARA BORRAR EL MATRIZ DE POSITIONRS
	glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, -1.0f, 1.0f);

	//dibuja
	if(i>4)
	{
		i=0;
	}
	RNP->init(Paterns[i],OutputXOR[i]);
 	RNP->draw();

	glutSwapBuffers();
	glFlush();
}

//function called on each frame
GLvoid window_idle()
{
	glutPostRedisplay();
	i+=1;
}
void init_scene(){}
int main(int argc, char **argv)
{
	funcion();
	//Inicializacion de la GLUT
	/*funcionXOR();*/

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(" Red Neuronal");


	initGL();
	init_scene();

	glutDisplayFunc(&window_display);

	//function called on each frame
	glutIdleFunc(&window_idle);

	glutMainLoop();

	return 1;
}

