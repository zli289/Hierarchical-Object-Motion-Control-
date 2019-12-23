#ifndef __GWU_MATH__
#define __GWU_MATH__

//matrix multiplation
void MulMatrix(GLfloat Templeftleg[16], GLfloat Temprightleg[16], GLfloat MResult[16])
{
	for(int i=0;i<16;i++)
	{
		GLfloat row=0;
		for(int j=0;j<4;j++)
			row+= Templeftleg[i%4+j*4]*Temprightleg[(i/4)*4+j];
		MResult[i]=row;
	}
}
//vector normalization
void Normalization(GLfloat v[3])
{
	GLfloat base =sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);	
	if (base != 0) 
	{
		for(int i=0;i<3;i++)
			v[i]/=base;
	}
}
//vector crossproduct 
void CrossProduct(GLfloat a[3], GLfloat b[3], GLfloat res[3])
{
	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}

#endif 
