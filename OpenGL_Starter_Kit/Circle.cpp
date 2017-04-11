#include "Circle.h"



Circle::Circle(glm::mat4 aTransformation, float scale) : SceneNode(aTransformation, scale)
{

}

void Circle::draw(float scale)
{
	glBegin(GL_LINE_LOOP);
	
		for (float theta = 0; theta <= 2 * 3.141; theta += 0.1)
		{
			glVertex2f(scale * cos(theta), scale * sin(theta));
		}

	glEnd();
}


