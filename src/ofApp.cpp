#include "ofApp.h"
namespace {
	std::string obj_file_pass = "./data/teddy.obj";
}


//--------------------------------------------------------------
void ofApp::setup(){
	// mesh setting
	mesh = new ObjMesh();

	mesh->read_from_file(obj_file_pass);
	mesh->Init();

	// light setting
	light.resize(3);
	float light_distance = 300;
	light[0].setPosition( 2.0*light_distance,  1.0*light_distance, 0.);			
	light[1].setPosition(-2.0*light_distance, -1.0*light_distance, 1.0*light_distance);
	
	for (int i = 0; i < light.size(); ++i) 
	{ 
		//light[i].setDiffuseColor(ofFloatColor(3., 3., 100.)); 
		//light[i].setSpecularColor(ofColor(30., 30., 30.));
		//light[i].set;
	}

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor(64), ofColor(0));
	glEnable(GL_DEPTH_TEST);

	ofEnableLighting();
	for (int i = 0; i < light.size(); ++i) { light[i].enable(); }

	cam.begin(); //@@@@@@@@@@@@@@@@@@@@
	ofPushMatrix();

		ofSetColor(ofColor(133, 180, 250));

		mesh->renderPoly();

	ofPopMatrix();
	cam.end();  //@@@@@@@@@@@@@@@@@@@@

	for (int i = 0; i < light.size(); ++i) { light[i].disable(); }
	ofDisableLighting();
	glDisable(GL_DEPTH_TEST);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
