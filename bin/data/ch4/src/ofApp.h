#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	ofMesh alienMesh;
	ofMesh cloudMesh;
	ofMesh forestMesh;
	ofMesh sunMesh;
	ofImage alienImage;
	ofImage cloudImage;
	ofImage forestImage;
	ofImage sunImage;
	ofShader forestShader;
	ofShader cloudShader;
	ofShader sunShader;
	ofShader alienShader;


	float frame = 0;
	float speed = 0;
	bool jump = false;
	float jumpspeed = 0;
	glm::vec3 charPos;
	glm::vec3 cloudPos;
	glm::vec3 viewPos;
	bool returnO = false;
	float shakeTime = 0;
	float cloudspeed = 0.1;
	glm::mat4 view;
	glm::mat4 proj;

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
