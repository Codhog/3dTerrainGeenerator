//Name: Zihao Chen
//Student#: 001405956

#ifndef __TERRAIN_H__
#define __TERRAIN_H__

class setTerrain {
public:
	float** points;
	int size;
	
	setTerrain();
	void setRandom(int a, int b, int number);
	void setPoints(int size);
	void drawPolygon();
	void drawLineLoop();
	void drawTriangle();
	void drawTriangleLine();
	void Circles(int centerx, int centerz, int circleSize, int height);

};

#endif
