#pragma once

#include "ofMain.h"
#include "ofxEasyCubemap.h"

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
	ofMesh shieldMesh;
	ofMesh waterMesh;
	ofMesh skyMesh;

	ofImage diffImage;
	ofImage specImage;
	ofImage normalImage;
	ofImage waterNormalImage;
	ofImage skyImage;

	ofShader uvShader;
	ofShader waterShader;
	ofShader skyShader;
	
	glm::vec3 camPos;
	glm::mat4 mvp;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
	glm::mat3 normalMatrix;//法线矩阵
	DirectionalLight dlight;//方向光

	glm::mat4 waterModel;
	glm::mat4 waterMVP;
	glm::mat3 waterNormalMatrix;
	glm::vec3 waterColor;

	ofxEasyCubemap cubeMap;
	glm::mat4 skyMVP;


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

