#pragma once

#include "SceneNode.h"
#include "glm\glm.hpp"
#include <glm\gtx\matrix_decompose.hpp>
#include "glm\gtc\matrix_transform.hpp"
#include <vector>
#include <math.h>

class Circle : public SceneNode
{
public:
	Circle::Circle(glm::mat4 transformation, float scale);
	void draw(float scale) override;
};
