#pragma once


//TO DO ONE ARGUMENT READ

//INCLUDE NEW ALGO
    //NEW VARS

//CONTINUOUS TIME

//CLEAN UP THE UNNCESSARY


#define ALGO  0
#define PLAY 1
//SLIDERS
#define SL1  2
#define SL2  3
#define SL3  4
#define SL4  5
#define SL5  6
//TOGGLES
#define TG1  7
#define TG2  8
#define TG3  9
#define TG4  10
#define TG5  11

#define RESW 12
#define RESH 13
#define TIMER  14
#define NAME  15
#define COLORNUM  16
//COLORS
#define RGB1  17
#define RGB2  18
#define RGB3  19
#define RGB4  20
#define RGB5  21
#define RGB6  22
#define RGB7  23
//
#define VIEW  24
#define SIZE  25
#define ITEM  26
#define FABRIC  27
#define GETVAR  28

/*
#define R1  15
#define G1  16
#define B1  17
#define R2  18
#define G2  19
#define B2  20
#define R3  21
#define G3  22
#define B3  23
#define R4  24
#define G4  25
#define B4  26
#define R5  27
#define G5  28
#define B5  29
#define R6  30
#define G6  31
#define B6  32
#define R7  33
#define G7  34
#define B7  35
*/


#define FRACTIONAL 0
#define VERTICES 1



#include "ofMain.h"
//#include "ofxControlPanel.h"
//#include "ofxXmlSettings.h"
//#include "ofxGui.h"
//#include "simpleButtons.h"
//#include "simpleButtonsTwoStates.h"
#include "ofxColorGradient.h"
//#include "ofxOsc.h"
//#include "ofxSimpleSlider.h"
//#include "ofxColorPicker.h"
//#include "arrow.h"


#include "ofxOcean.h"
#include "ofxOceanRenderer.h"



#ifdef TARGET_EMSCRIPTEN
#include <emscripten/emscripten.h>
#include <stdlib.h>
#endif



#define MAX_COLOR 5
#define MIN_COLOR 2



//#define widthScarf 768//*2
//#define heightScarf 768//*2//5800


//#define screenWidthInit 1366
//#define screenHeightInit 768

#define dimensionWeb 400


//#define widthPreview 768
//#define heightPreview 768

#define COLOR 0
#define SHAPE 1


struct cameraPt {
    
    ofPoint pos;
    ofPoint rot;
    float fov;
    
};




class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed  (int key);
		void keyReleased (int key);

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	//	void setupB();
//		void drawB();
        void checkChange();
    
    void setupFrac();
    void updateFrac();
    void drawFrac();

		ofShader shader;
		bool doShader;

        void importDesignString();
		string exportDesignString();
    
    
    int divWidth;
    
    vector<string>varMap;
    
    float colorThreshold;
//		ofxControlPanel gui;
//ofxPanel gui;
//ofxFloatSlider red[2];
//ofxFloatSlider green[2];
//ofxFloatSlider blue[2];


		//float red[2];
	//	float green[2];
	//	float blue[2];

//ofxToggle timeFreeze;

//ofxSimpleSlider
    float fluidityVal[3];
//ofxSimpleSlider
    float timeMotionVal;
//ofxSimpleSlider
    float scaleVal;
//		ofxSimpleSlider
    float rVal[MAX_COLOR];
//		ofxSimpleSlider
    float gVal[MAX_COLOR];
//		ofxSimpleSlider
    float bVal[MAX_COLOR];

		int currentState;
	//	int currentColor;

		int widthScarf;
		int heightScarf;


  vector<string>vars;
  vector<float>floatVars;

int width;
int height;

//float widthThings;
 //   float xThings;
/*
   simpleButtons btColor[MAX_COLOR];
    simpleButtons btPlus;
    simpleButtons btMinus;

	simpleButtons btDesignCat;
	simpleButtons btColorCat;
	simpleButtonsTwoStates btPlayPauseCat;
*/


    int currentColorNum;


	void layoutVar();
	void updateB();

	float margin;
	float marginInner;
	float buttonWidth;
	float buttonWidthSmall;
	ofRectangle gradRect;

    int wVid;
    int hVid;

    void addColor();
    void removeColor();

    int name;
    bool takingStill;
    bool saveVideo;

    ofImage gradient;


    ofImage background; //initially I got some weird artifacts without creating a background image large enough for your print it drew part of my screen desktop to the FBO...
    ofPixels pix;
   // ofPixels vidPix;

   //ofShader shader2;
    
    int drawX;
 //ofTrueTypeFont *font;

    
 //   ofxColorPicker colorPicker[MAX_COLOR];
    
    ofColor colorPickerR[MAX_COLOR];
    
   // arrow arrows[MAX_COLOR];
    
    
  //  bool minimalViewB;
    
    int currentAlgo;
    
    
    ofxColorGradient grad;
    ofImage colorImage;
    ofPixels pixel;
    ofTexture tex;
  //  ofxColorGradient gradGrey;
    
    
    
    
    float currentTime;
    float baseTime;
    float scaleMult;
    
    
    bool gradInfo;

    int currentScene;
    
    bool play;
    
    bool useMessage;
    string message;
 
    ofImage image;
    ofImage imageBlack;
    ofImage imageWhite;
    
    vector<ofPoint>pts;
    
    
    string info;
    
    
    
    
    /*VERTICES*/
    
    void setupVert();
    void updateVert();
    void drawVert();
    
    
    ofxOcean ocean;
    ofxOceanRenderer renderer;
    
    //ofShader oceanShader; //not used
    
    
    
    //bool shouldRegenerateOcean;
    
    int oceanTileResolution;
    //int oceanTileSizeX;
    //int oceanTileSizeY;
    
    
    
    ofEasyCam easyCam;
    ofCamera cam;

    
    ofMaterial mat;
    
    
    //material
    ofColor bgColor1;
    ofColor bgColor2;
    ofFloatColor fogColor;
    ofFloatColor ambientColor;
    ofFloatColor diffuseColor;
    ofFloatColor emissiveColor;
    ofFloatColor specularColor;
    float shininess;
    //ocean
    //ofxIntSlider resolutionMesh;
    //ofxFloatSlider windSpeed;
    float fogDensity;
    float waveScale;
    float choppyScale;
    float waveSpeed;
    bool depthTesting;
    
    bool useFlatSurface;
    float cameraMove;
    //Light
    ofLight pointLight;
    ofVec3f centerLight;
    ofFloatColor lightColor;
    //
    bool drawWireFrame;
    bool drawVertices;
    bool drawFaces;
    
    float oceanAlpha;
    float pointSize;
    //camera position
    ofVec3f camPosition;
    ofVec3f camAngle;
    float radiusFlat;
    float fov;
    bool  useEasyCam;
    
    bool drawGui;
    
    float lightSituation;
    
    //
    ofColor tCol[MAX_COLOR];
    
    vector<cameraPt>cameraPts;
    
    
    int opacityButtons;
    //ofColor colorSliders[MAX_COLOR];
    ofColor wireFrameOnlyColor;
    
//    int currentColorNum;
//    void addColor();
//    void removeColor();
//    vector<string>vars;
//    vector<float>floatVars;
    
    //float red[MAX_COLOR], green[MAX_COLOR], blue[MAX_COLOR];
    //
    string productSize;
    
    
    ofTrueTypeFont font;
    
};

