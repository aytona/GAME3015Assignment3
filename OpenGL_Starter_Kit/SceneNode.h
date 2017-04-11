#ifndef SCENENODE_HEADER
#define SCENENODE_HEADER


#include "glm\glm.hpp"
#include <glm\gtx\matrix_decompose.hpp>
#include "glm\gtc\matrix_transform.hpp"
#include <vector>
#include "GL\glut.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

class SceneNode
{
	protected:
	std::vector<SceneNode*> children;
	SceneNode* parent;
	glm::mat4 transformation;
	float r, g, b;
	float scale;


	public:
		//Constructor
		SceneNode(glm::mat4 transformation, float scale);

		//Methods
		void SceneNode::addChild(SceneNode*);
		void SceneNode::setColor(float r, float g, float b);
		glm::mat4 SceneNode::getTransformationMatrix();
		std::vector<SceneNode*> getChildren();
		SceneNode* SceneNode::getParent();
		void SceneNode::setParent(SceneNode* p);
		void SceneNode::render();
		virtual void SceneNode::draw(float scale) = 0;

};
#endif // !SCENENODE_HEADER