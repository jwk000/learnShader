#include "ofApp.h"

void BuildMesh(ofMesh& mesh, float w, float h, glm::vec3 pos) {
	float verts[] = {
		-w + pos.x,-h + pos.y,pos.z,
		-w + pos.x,h + pos.y,pos.z,
		w + pos.x,h + pos.y,pos.z,
		w + pos.x,-h + pos.y,pos.z
	};
	float uvs[] = { 0,0,0,1,1,1,1,0 };

	for (int i = 0; i < 4; i++) {
		int idx = i * 3;
		int uvidx = i * 2;

		mesh.addVertex(glm::vec3(verts[idx], verts[idx + 1], verts[idx + 2]));
		mesh.addTexCoord(glm::vec2(uvs[uvidx], uvs[uvidx + 1]));
	}

	ofIndexType indices[] = { 0,1,2,2,3,0 };
	mesh.addIndices(indices, 6);
}

glm::mat4 BuildMatrix(glm::vec3 trans, float rot, glm::vec3 scale) {
	using glm::mat4;
	mat4 translation = glm::translate(trans);
	mat4 rotation = glm::rotate(rot, glm::vec3(0, 0, 1));//绕z轴旋转
	mat4 scaler = glm::scale(scale);

	return translation * rotation * scaler;
}


//--------------------------------------------------------------
void ofApp::setup() {
	ofDisableArbTex(); //禁用废弃的纹理坐标格式

	alienImage.load("ch4/walk_sheet.png");
	cloudImage.load("ch4/cloud.png");
	forestImage.load("ch4/forest.png");
	sunImage.load("ch4/sun.png");

	BuildMesh(forestMesh, 1, 1, glm::vec3(0, 0, -0.5));
	BuildMesh(alienMesh, 0.1, 0.2, glm::vec3(0, -0.25, 0));
	BuildMesh(sunMesh, 1, 1, glm::vec3(0, 0, -0.4));
	BuildMesh(cloudMesh, 0.25, 0.15, glm::vec3(0, 0, 0));


	forestShader.load("ch4/transform.vert", "ch4/alphatest.frag");
	cloudShader.load("ch4/transform.vert", "ch4/cloud.frag");
	sunShader.load("ch4/transform.vert", "ch4/cloud.frag");
	alienShader.load("ch4/spritewalk.vert", "ch4/alphatest.frag");

	view = BuildMatrix(glm::vec3(0, 0, 0), 0, glm::vec3(0.8, 0.8, 0.8));
	view = glm::inverse(view);

	proj = glm::ortho(-1.33f, 1.33f, -1.f, 1.f, -100.f, 100.f);
}

//--------------------------------------------------------------
void ofApp::update() {

	frame += 0.2f;
	if (frame > 10)frame = 0;

	float deltaTime = ofGetLastFrameTime();

	//跳跃
	float ypos = 0;
	if (jump) {
		jumpspeed -= 9.8 * deltaTime;
		ypos = jumpspeed * deltaTime;
		if (jumpspeed < -2) {
			jump = false;
		}
	}
	charPos += glm::vec3(speed * deltaTime, ypos, 0);
	if (charPos.x > 1.22) {
		charPos.x = -1.2;
	}
	if (charPos.x < -1.22) {
		charPos.x = 1.2;
	}
	if (jump == false) {
		charPos.y = 0;
	}

	//云朵飘动
	cloudPos += glm::vec3(cloudspeed * deltaTime, 0, 0);
	if (cloudPos.x > 1.2) {
		cloudPos.x = -1.2;
	}

	//相机摇晃
	glm::vec3 tempViewPos;
	shakeTime += deltaTime;
	if (shakeTime > 0.5f) {
		if (shakeTime > 1) 
		{
			shakeTime = 0;
			float x = rand();
			float y = rand();
			x = x > RAND_MAX / 2 ? x - RAND_MAX / 2 : x;
			y = y > RAND_MAX / 2 ? y - RAND_MAX / 2 : y;

			viewPos = glm::vec3(x/ RAND_MAX, y/ RAND_MAX, 0) * deltaTime * 10;
		}
		else 
		{
			tempViewPos.x = ofLerp( viewPos.x,0, shakeTime-0.5 / 0.5f);
			tempViewPos.y = ofLerp( viewPos.y,0, shakeTime-0.5 / 0.5f);
		}
	}
	else 
	{
		tempViewPos.x = ofLerp(0, viewPos.x, shakeTime / 0.5f);
		tempViewPos.y = ofLerp(0, viewPos.y, shakeTime / 0.5f);
	}

	view = BuildMatrix(tempViewPos, 0, glm::vec3(0.8, 0.8, 0.8));
	view = glm::inverse(view);

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofDisableBlendMode();


	ofEnableDepthTest();

	alienShader.begin();
	alienShader.setUniformMatrix4f("model", glm::translate(charPos));
	alienShader.setUniformMatrix4f("view", view);
	alienShader.setUniformMatrix4f("proj", proj);
	glm::vec2 spriteSize = glm::vec2(0.28, 0.19);
	glm::vec2 spriteOffset = glm::vec2((int)frame % 3, (int)frame / 3);
	alienShader.setUniform2f("size", spriteSize);
	alienShader.setUniform2f("offset", spriteOffset);
	alienShader.setUniformTexture("tex", alienImage, 0);
	alienMesh.draw();
	alienShader.end();

	forestShader.begin();
	forestShader.setUniformMatrix4f("transform", proj * view * glm::mat4());
	forestShader.setUniformTexture("tex", forestImage, 0);
	forestMesh.draw();
	forestShader.end();

	ofDisableDepthTest();

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ALPHA);
	cloudShader.begin();
	glm::mat4 cloudTransform = BuildMatrix(cloudPos, 0, glm::vec3(0.5, 0.4, 1));
	cloudShader.setUniformMatrix4f("transform", proj * view * cloudTransform);
	cloudShader.setUniformTexture("tex", cloudImage, 0);
	cloudMesh.draw();
	cloudShader.end();

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	sunShader.begin();
	sunShader.setUniformMatrix4f("transform", proj * view * glm::mat4());
	sunShader.setUniformTexture("tex", sunImage, 0);
	sunMesh.draw();
	sunShader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == OF_KEY_RIGHT) {
		speed = 0.3f;
	}
	else if (key == OF_KEY_LEFT) {
		speed = -0.3f;
	}
	else if (key == OF_KEY_UP && !jump) {
		jump = true;
		jumpspeed = 2;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == OF_KEY_RIGHT) {
		speed = 0;
	}
	else if (key == OF_KEY_LEFT) {
		speed = 0;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
