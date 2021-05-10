#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (int r = 50; r <= 50; r += 10) {

		int v_span = 1;
		int u_span = 30;

		ofMesh face, line;
		line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
		for (int v = 0; v <= 360; v += v_span) {

			bool flag = true;
			int u_start = r + v;
			int next_u = u_start + v_span;
			for (int u = u_start; u < u_start + 360 - u_span; u += u_span) {

				if (flag) {

					vector<glm::vec3> vertices;
					vertices.push_back(this->make_point(200, r, u, v));
					vertices.push_back(this->make_point(200, r, u + u_span, v));
					vertices.push_back(this->make_point(200, r, next_u + u_span, v + v_span));
					vertices.push_back(this->make_point(200, r, next_u, v + v_span));

					for (auto& vertex : vertices) {

						auto deg_y = ofMap(ofNoise(vertex.y * 0.003 + ofGetFrameNum() * 0.008), 0, 1, -360, 360);
						auto rotation_y = glm::rotate(glm::mat4(), deg_y * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
						vertex = glm::vec4(vertex, 0) * rotation_y;
					}

					face.addVertices(vertices);
					line.addVertices(vertices);

					ofColor color;
					color.setHsb(ofMap(u, u_start, u_start + 360, 0, 255), 180, 255);

					face.addColor(color);
					face.addColor(color);
					face.addColor(color);
					face.addColor(color);

					face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
					face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

					line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 4);
					line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 3);
				}

				next_u += u_span;
				flag = !flag;
			}
		}

		face.drawFaces();
		line.drawWireframe();
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}