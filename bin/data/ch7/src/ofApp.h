#pragma once

#include "ofMain.h"

struct DirectionalLight {
	glm::vec3 direction;
	glm::vec3 color;
	float intensity;

	glm::vec3 getLightDir() {
		return glm::normalize(direction * -1);
	}

	glm::vec3 getLightCol() {
		return color * intensity;
	}
};

class ofApp : public ofBaseApp{
	ofMesh torusMesh;
	ofImage torusImage;
	ofShader uvShader;

	glm::vec3 camPos;
	glm::mat4 mvp;
	glm::mat3 model;
	glm::mat3 view;
	glm::mat3 proj;
	glm::mat3 normalMatrix;//法线矩阵
	DirectionalLight dlight;//方向光
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};

