#ifndef __GWU_BODY__
#define __GWU_BODY__

// interpolation initialization
static GLfloat tangent[3];
static GLfloat binormal[3];
static GLfloat normal[3];
static GLfloat trace = 0;
// boday matrix 
static GLfloat body[16]; 

static GLfloat leftleg[16];
static GLfloat rightleg[16];
//walking position
static int points = 0; 
static int number = 7; 
static GLfloat pos[7][3] = { 
	{ 5, 0, -20 },  
	{ 0, 0, -20 }, 
	{ -5, 0, -10 }, 
	{ 0, 0, -10 },	
	{ 5, 0, -5 },	
	{0,0,-5},		
	{ 1, 0, -3 } }; 
//walking spines 	
GLfloat catmull_rom[16]={ 
	-0.5f, 1.0f, -0.5f, 0.0f,	  
	1.5f, -2.5f, 0.0f, 1.0f,     
	-1.5f, 2.0f, 0.5f, 0.0f,     
	0.5f, -0.5f, 0.0f, 0.0f };    

GLfloat b_spline[16]={
	-0.5f, 1.0f, -0.5f, 0.0f,	 
	1.5f, -2.5f, 0.0f, 1.0f,      
	-1.5f, 2.0f, 0.5f, 0.0f,      
	0.5f, -0.5f, 0.0f, 0.0f };    

//blending function 
GLfloat blend(GLfloat T[4], GLfloat M[16], GLfloat G[4])
{
	GLfloat res[4]={0,0,0,0};
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
			res[i]+=T[j]*M[i*4+j];
		res[i]*=G[i];
	}		
	return res[0]+res[1]+res[2]+res[3];
}

void interpolation(GLfloat t_pos[7][3], GLfloat spline[16],GLfloat t)
{
	GLfloat vec[3];
	GLfloat T[4]={t*t*t,t*t,t,1};
	GLfloat t_tangent[4] = {3*t*t,2*t,1,0};

	for (int i = 0; i < 3; i++)
	{
		GLfloat t_matrix[4] = { t_pos[points][i],
			t_pos[(points + 1) % number][i],
			t_pos[(points + 2) % number][i],
			t_pos[(points + 3) % number][i] };

		vec[i] = blend(T, spline, t_matrix);
		tangent[i] = blend(t_tangent, spline, t_matrix);
	}
	Normalization(tangent);

	if (points == 0 && trace == 0) 
	{
		GLfloat tempv[3] = { 1, 0, 0 }; 
		Normalization(tempv);
		CrossProduct(tangent, tempv, normal);
		Normalization(normal);
		CrossProduct(normal, tangent, binormal);
		Normalization(binormal);
		trace++;
	}
	else 
	{
		CrossProduct(tangent, binormal, normal);
		Normalization(normal);
		CrossProduct(normal, tangent, binormal);
		Normalization(binormal);
	}

	for(int i=0;i<3;i++)
	{
		body[i*4]=tangent[i];
		body[i*4+1]=normal[i];
		body[i*4+2]=binormal[i];
		body[i*4+3]=0;
	}

	body[12] = vec[0];  
	body[13] = vec[1]; 
	body[14] = vec[2]; 
	body[15] = 1;			
}

void Leg(GLfloat Matrix[16],GLfloat t,GLfloat direction)
{
	GLfloat t1[16] = { 1, 0, 0, 0,		
						0, 1, 0, 0,		
						0, 0, 1, 0,		
						0, -1, 0, 1 };	

	GLfloat angle = (sin(4 * 3.14*t - 3.14 / 2)*3.14) / 4*direction; 
	
	GLfloat t2[16] = { cos(angle), sin(angle), 0, 0,	 
						-sin(angle), cos(angle), 0, 0, 
						0, 0, 1, 0,						
						0, 0, 0, 1 };					

	GLfloat t3[16] = { 1, 0, 0, 0,		
						0, 1, 0, 0,		
						0, 0, 1, 0,		
						0, 0, 0.3f*direction, 1 };	

	MulMatrix(body, t2, Matrix);
	MulMatrix(Matrix, t1, Matrix);
	MulMatrix(Matrix, t3, Matrix);

	glLoadMatrixf(Matrix);
	glScalef(0.3f, 2.0f, 0.3f);
	glutSolidCube(1.0);
}

void Body(GLfloat t)
{
	interpolation(pos, catmull_rom,t);
	glLoadMatrixf(body);
	glutSolidCube(1.0);

	Leg(leftleg,t,1.0);
	Leg(rightleg,t,-1.0);
}

#endif 