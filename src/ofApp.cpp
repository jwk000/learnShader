#include "ofApp.h"



void calcTangents(ofMesh& mesh)
{
	using namespace glm;
	std::vector<vec4> tangents;
	tangents.resize(mesh.getNumVertices());

	uint indexCount = mesh.getNumIndices();

	const vec3* vertices = mesh.getVerticesPointer();
	const vec2* uvs = mesh.getTexCoordsPointer();
	const uint* indices = mesh.getIndexPointer();

	for (uint i = 0; i < indexCount - 2; i += 3)
	{
		const vec3& v0 = vertices[indices[i]];
		const vec3& v1 = vertices[indices[i + 1]];
		const vec3& v2 = vertices[indices[i + 2]];
		const vec2& uv0 = uvs[indices[i]];
		const vec2& uv1 = uvs[indices[i + 1]];
		const vec2& uv2 = uvs[indices[i + 2]];

		vec3 edge1 = v1 - v0;
		vec3 edge2 = v2 - v0;
		vec2 dUV1 = uv1 - uv0;
		vec2 dUV2 = uv2 - uv0;

		float f = 1.0f / (dUV1.x * dUV2.y - dUV2.x * dUV1.y);

		vec4 tan;
		tan.x = f * (dUV2.y * edge1.x - dUV1.y * edge2.x);
		tan.y = f * (dUV2.y * edge1.y - dUV1.y * edge2.y);
		tan.z = f * (dUV2.y * edge1.z - dUV1.y * edge2.z);
		tan.w = 0;
		tan = normalize(tan);

		tangents[indices[i]] += (tan);
		tangents[indices[i + 1]] += (tan);
		tangents[indices[i + 2]] += (tan);
	}

	int numColors = mesh.getNumColors();

	for (int i = 0; i < tangents.size(); ++i)
	{
		vec3 t = normalize(tangents[i]);
		if (i >= numColors)
		{
			mesh.addColor(ofFloatColor(t.x, t.y, t.z, 0.0));
		}
		else
		{
			mesh.setColor(i, ofFloatColor(t.x, t.y, t.z, 0.0));
		}
	}
}


//--------------------------------------------------------------
void ofApp::setup() {
	ofDisableArbTex(); //禁用废弃的纹理坐标格式
	ofEnableDepthTest();

	using namespace glm;

	camPos = vec3(0, 0.75f , 1);
	float fov = radians(90.f);
	float aspect = 1024.0f / 768.0f;

	model = rotate(radians(-45.f), vec3(1, 0, 0)) * scale(vec3(1.5f, 1.5f, 1.5f));
	view = inverse(translate(camPos)*rotate(radians(-25.0f), vec3(1, 0, 0)));
	proj = perspective(fov, aspect, 0.01f, 10.0f);
	mvp = proj * view * model;
	//法线矩阵=模型矩阵的上三角矩阵的逆矩阵的转置
	normalMatrix = transpose(inverse(mat3(model)));

	shieldMesh.load("ch12/shield.ply");
	calcTangents(shieldMesh);
	uvShader.load("ch12/mesh.vert", "ch12/pointlight.frag");

	waterMesh.load("ch12/water.ply");
	calcTangents(waterMesh);
	waterShader.load("ch12/water.vert", "ch12/water.frag");

	dlight.direction = normalize(vec3(0.2, -1, -0.3));//顶部向下
	dlight.color = vec3(1, 1, 1);//白色
	dlight.intensity = 1;//强度

	plight.position = vec3(0.5, 1, 0);
	plight.color = vec3(1, 1, 1);
	plight.radius = 1.2f;
	plight.intensity = 0.5;

	diffImage.load("ch12/shield_diffuse.png");
	specImage.load("ch12/shield_spec.png");
	normalImage.load("ch12/shield_normal.png");
	waterNormalImage.load("ch12/water_nrm.png");
	//图片uv越界处理模式，重复
	waterNormalImage.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);

	waterModel = translate(vec3(0,-0.4,0))*rotate(radians(-90.f),vec3(1,0,0))*scale(vec3(5,5,5));
	waterMVP = proj * view * waterModel;
	waterNormalMatrix = transpose(inverse(mat3(waterModel)));
	waterColor = vec3(0.3, 0.3, 0.5);//偏蓝色

	skyMesh.load("ch12/cube.ply");
	skyShader.load("ch12/cube.vert", "ch12/cube.frag");
	cubeMap.load("ch12/night_front.jpg", "ch12/night_back.jpg", "ch12/night_right.jpg", "ch12/night_left.jpg", "ch12/night_top.jpg", "ch12/night_bottom.jpg");

	mat4 skymodel = translate(camPos);
	skyMVP = proj * view * skymodel;

}

float angleY;
//--------------------------------------------------------------
void ofApp::update() {
	using namespace glm;
	float t = ofGetElapsedTimef();
	angleY += (sin(t))*.05f;
	model = translate(vec3(0,0.4,0))* rotate(angleY, vec3(0, 1, 0)) ;
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
	uvShader.setUniform3f("lightPos", plight.position);
	uvShader.setUniform3f("lightCol", plight.getLightCol());
	uvShader.setUniform1f("lightRadius", plight.radius);
	uvShader.setUniform3f("ambientCol", glm::vec3(0.1, 0.1, 0.1));
	uvShader.setUniformTexture("diffuseTex", diffImage,0);
	uvShader.setUniformTexture("specularTex", specImage, 1);
	uvShader.setUniformTexture("normalTex", normalImage, 2);
	shieldMesh.draw();
	uvShader.end();

	//waterShader.begin();
	//waterShader.setUniform1f("t", ofGetElapsedTimef());
	//waterShader.setUniformTexture("normalTex", waterNormalImage, 0);
	//waterShader.setUniformTexture("cubemapTex", cubeMap.getTexture(), 1);
	//waterShader.setUniformMatrix4f("mvp", waterMVP);
	//waterShader.setUniformMatrix4f("model", waterModel);
	//waterShader.setUniformMatrix3f("normal", waterNormalMatrix);
	//waterShader.setUniform3f("camPos", camPos);
	//waterShader.setUniform3f("lightDir", dlight.getLightDir());
	//waterShader.setUniform3f("lightCol", dlight.getLightCol());
	//waterShader.setUniform3f("ambientCol", glm::vec3(0.3, 0.3, 0.3));
	//waterShader.setUniform3f("meshCol", waterColor);
	//waterMesh.draw();
	//waterShader.end();

	glDepthFunc(GL_LEQUAL);//使z==1的位置可以渲染出来
	skyShader.begin();
	skyShader.setUniformTexture("cubemap",cubeMap.getTexture(),0);
	skyShader.setUniformMatrix4f("mvp", skyMVP);
	skyMesh.draw();
	skyShader.end();
	glDepthFunc(GL_LESS);
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
