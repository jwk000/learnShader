#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex(); //禁用废弃的纹理坐标格式
	ofDisableAlphaBlending();//禁用alpha混合
	image1.load("saima1.png");
	image1.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
	image2.load("saima2.png");
	image2.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);



	//例子1 绘制三角形
	triangle.addVertex(glm::vec3(-1, 1, 0));
	triangle.addVertex(glm::vec3(-1, -1, 0));
	triangle.addVertex(glm::vec3(1, -1, 0));

	triangle.addColor(ofFloatColor(1, 0, 0, 1));
	triangle.addColor(ofFloatColor(0, 1, 0, 1));
	triangle.addColor(ofFloatColor(0, 0, 1, 1));

	//例子2 绘制正方形
	quad.addVertex(glm::vec3(-1, -1, 0));
	quad.addVertex(glm::vec3(-1, 1, 0));
	quad.addVertex(glm::vec3(1, 1, 0));
	quad.addVertex(glm::vec3(1, -1, 0));

	//顶点颜色
	quad.addColor(ofDefaultColorType(1, 0, 0, 1));
	quad.addColor(ofDefaultColorType(0, 1, 0, 1));
	quad.addColor(ofDefaultColorType(0, 0, 1, 1));
	quad.addColor(ofDefaultColorType(1, 1, 1, 1));

	//纹理坐标
	quad.addTexCoord(glm::vec2(0, 0));
	quad.addTexCoord(glm::vec2(0, 1));
	quad.addTexCoord(glm::vec2(1, 1));
	quad.addTexCoord(glm::vec2(1, 0));


	ofIndexType indices[6] = { 0,1,2,2,3,0 };//顺时针绕序
	quad.addIndices(indices, 6);

	shader.load("scrolling_uv.vert", "brightness.frag");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	shader.begin();
	//无论在渲染管线的哪里获取值都不变的值是uniform
	shader.setUniform4f("fragColor", glm::vec4(0, 1, 1, 1));
	shader.setUniformTexture("saimaTex1", image1, 0);//纹理位置用来区分多纹理
	shader.setUniformTexture("saimaTex2", image2, 1);//纹理位置用来区分多纹理
	shader.setUniform1f("time", ofGetElapsedTimef());//设置一个浮点数time，值为程序启动时间
	shader.setUniform1f("brightness", glm::abs(glm::sin(ofGetElapsedTimef())));
	//triangle.draw();
	quad.draw();
	shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//glm::vec3 curPos = triangle.getVertex(2);
	//triangle.setVertex(2, curPos - glm::vec3(0, 20, 0));
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
