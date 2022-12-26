#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup() {
	ofDisableArbTex(); //���÷��������������ʽ
	ofEnableDepthTest();

	using namespace glm;

	camPos = vec3(0, 0.75, 1);
	float fov = radians(90.f);
	float aspect = 1024.0f / 768.0f;

	model = rotate(0.f, vec3(1, 1, 1)) * scale(vec3(0.5f, 0.5f, 0.5f));
	view = inverse(translate(camPos)*rotate(radians(-45.0f), vec3(1, 0, 0)));
	proj = perspective(fov, aspect, 0.01f, -10.0f);
	mvp = proj * view * model;
	//���߾���=ģ�;���������Ǿ����������ת��
	normalMatrix = transpose(inverse(mat3(model)));

	torusMesh.load("ch7/torus.ply");
	uvShader.load("ch7/mesh.vert", "ch7/specular.frag");

	dlight.direction = normalize(vec3(-1, -1, 0));//��������
	dlight.color = vec3(1, 1, 1);//��ɫ
	dlight.intensity = 1;//ǿ��
}

float angleY;
//--------------------------------------------------------------
void ofApp::update() {
	using namespace glm;
	float t = ofGetElapsedTimef();
	angleY += (sin(t))*.05f;
	model = rotate(angleY, vec3(0, 1, 0)) * scale(vec3(0.5f, 0.5f, 0.5f));
	mvp = proj * view * model;
	normalMatrix = transpose(inverse(mat3(model)));

}

//--------------------------------------------------------------
void ofApp::draw() {

	uvShader.begin();
	uvShader.setUniformMatrix4f("mvp", mvp);
	uvShader.setUniformMatrix4f("model", model);
	uvShader.setUniformMatrix3f("normal", normalMatrix);
	uvShader.setUniform3f("camPos", camPos);
	uvShader.setUniform3f("lightDir", dlight.getLightDir());
	uvShader.setUniform3f("lightCol", dlight.getLightCol());
	uvShader.setUniform3f("meshCol", glm::vec3(0.5, 0.6, 0.2));
	uvShader.setUniform3f("ambientCol", glm::vec3(0.1, 0.1, 0.3));
	torusMesh.draw();
	uvShader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

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
