#ifndef __WALL_H
#define __WALL_H

#include "Object.h"
#include <vector>
#include <string>

class Wall : Object
{
public:
	Wall(const GLuint& programID, 
		 const int& width,
		 const int& height,
		 const std::string textureIMG);

	void draw(const mat4& projection, const mat4& view);
	void update() {}
	void init();

	void changeColor();
private:
	int _width;
	int _height;
	std::vector<glm::vec4> _vertices;

	void _buildWall();
};

#endif
