This project is based on Opengl and SimpleGLUT (https://icg.gwu.edu/sites/g/files/zaxdzs1481/f/downloads/SimpleGLUT.zip). 

Source/math.h: matrix and vector comptuation
Source/body.h: blending function and interpolation by splines, Hierarchy transformation between torso and legs. 
SimpleGLUT: rendering objects by time t. 

Compile command:	"g++ SimpleGLUT.cpp -o SimpleGLUT -lopengl32 -lglew32 -lfreeglut -lglu32"