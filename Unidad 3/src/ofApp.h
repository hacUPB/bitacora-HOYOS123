#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void mousePressed(int x, int y, int button);

	void generateSpheres();
	void convertMouseToRay(int mouseX, int mouseY, glm::vec3 & rayStart, glm::vec3 & rayEnd);
	bool rayIntersectsSphere(const glm::vec3 & rayStart, const glm::vec3 & rayDir,
		const glm::vec3 & sphereCenter, float sphereRadius,
		glm::vec3 & intersectionPoint);

	ofEasyCam cam;
	vector<glm::vec3> spherePositions;

	int xStep, yStep;
	float distDiv, amplitud;

	bool sphereSelected = false;
	glm::vec3 selectedSphere;

private:
	vector<ofVec2f> particles;
	ofColor particleColor;
};
