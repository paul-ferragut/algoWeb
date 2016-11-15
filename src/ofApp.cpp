#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    
    
    //   ofEnableSmoothing();
    //   ofEnableAntiAliasing();
    ofSetFrameRate(30);
    
    currentItem=0;
    
    message="";
    
    string arr[] ={"algo","play","sl1","sl2","sl3","sl4","sl5","tg1","tg2","tg3","tg4","tg5","resw","resh","time","name","colorNum","rgb1","rgb2","rgb3","rgb4","rgb5","rgb6","rgb7","view","size","item","fabric","getvar"};
    

    
    vector<string> myvec ( arr, arr + sizeof(arr) / sizeof(string) );
    varMap=myvec;
    
    
    for(int i=0;i<varMap.size();i++){
        //cout<<"i"<<varMap[i]<<endl;
    }
    
    
    widthScarf = ofGetHeight();
    heightScarf= ofGetHeight();
    //    minimalViewB=false;
    
    
    scaleMult=1;
    currentTime=0;
    currentScene=0;
    currentAlgo=0;
    name=0;
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(255, 255, 255);
    currentColorNum=MIN_COLOR;
    currentColorNum=MIN_COLOR;
    scaleVal=1.0;
    play=true;
    
#ifdef TARGET_EMSCRIPTEN
    
    
    
    divWidth=emscripten_run_script_int("$('#scarvesDiv').width();");
   // cout<<"divWidth launch"<<divWidth<<endl;
    
    widthScarf =  divWidth;//dimensionWeb;//screenWidthInit;//(float)divWidth;
    heightScarf=  divWidth;//dimensionWeb;//screenWidthInit;//(float)divWidth;
    
    ofSetWindowShape(divWidth, divWidth);
    
    //  scaleMult = widthScarf/ inputScarfW;
    

    
#endif
    //INIT LAYOUT VARIABLE
  //  cout<<"setup fract"<<endl;
    
    fluidityVal[0]=1.0;
    fluidityVal[1]=0.5;
    fluidityVal[2]=10.5;
    scaleVal=1.0;
    
    cout<<"pix allocated"<<endl;
    pix.allocate(widthScarf,heightScarf,OF_IMAGE_COLOR);
    
    //  ofEnableAlphaBlending();
    cout<<"load shader"<<endl;
    shader.load("shaders/noise");
    
    //custom gradient design
    
    grad.setup(256, 256);
    
    for (int i=0; i<MIN_COLOR; i++)
    {
        ofColor col;
        col.set(rVal[i], gVal[i], bVal[i]);
        if (i !=0) {
            grad.addColor(col);
        }else{
            grad.addColor(ofColor(255,255,255));
        }
        
    }
    
    
    cout<<"load wheel and color picker"<<endl;
    colorImage.load("wheel.png");
    colorImage.setImageType(OF_IMAGE_COLOR_ALPHA);
    
    ofLoadImage(pixel, "wheel.png");
    
    cout<<"load wheel and color picker"<<endl;
    
    
    rVal[0]=0;
    gVal[0]=0;
    bVal[0]=0;
    
    //SETUP VERT
    //SETUP VERT
    //SETUP VERT
    cout<<"setup vert"<<endl;
    // setupVert();
    waveScale=60;
    fogDensity=0.04;
    waveSpeed=2;
    choppyScale=3;
    
    alphaBlending=false;
    oceanAlpha=0.5;
    pointSize=4;
    radiusFlat=4;
    centerLight.set(0,0,0);
    
    drawWireFrame=true;
    drawVertices=false;
    drawFaces=true;
    camPosition.set(200,0,-200);
    camAngle.set(0,180,0);
    fov=60;
    fovMult=1.0;
    useEasyCam=false;
    oceanTileResolution=80;
    cameraMove=0.25;
    useFlatSurface=false;
    shininess=1.25;
    
    bgColor1.set(ofColor(0,0,0));
    bgColor2.set(ofColor(30,30,30));
    fogColor.set(ofFloatColor(0.5, 0.5, 0.5));
    ambientColor.set(ofFloatColor(0.5, 0.5, 0.5));
    diffuseColor.set(ofFloatColor(0.5, 0.5, 0.5));
    emissiveColor.set(ofFloatColor(0.5, 0.5, 0.5));
    specularColor.set(ofFloatColor(0.5, 0.5, 0.5));
    lightColor.set(ofFloatColor(0.5, 0.5, 0.5));
    
    for (int i = 0;i < MAX_COLOR;i++) {
        tCol[i].set(0, 0, 0);
    }
    tCol[1] = ofColor(255, 255, 255);
    
    // cout << "gui setup" << endl;
    ocean.size = ofVec3f(int(400), 1.0, int(400));
    // ocean.windSpeed = waveSpeed;
    ocean.waveScale = waveScale;
    ocean.setup();
    cout << "ocean setup" << endl;
    renderer.setup(&ocean, 1, 1);
    cout << "renderer setup" << endl;
    

    cout<<"fog"<<endl;
    fog.load("shaders/fog");
    
    
    // ofSetSmoothLighting(true);
    
    pointLight.setDiffuseColor(ofColor(255.f, 255.f, 255.f));
    pointLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
    pointLight.setPosition(centerLight);
    
    cameraPt cPt;
    cPt.fov = 40;
    cPt.pos.set(200, 0, -200);
    cPt.rot.set(360, 180, 0);
    cameraPts.push_back(cPt);
    cPt.pos.set(200, 0, 0);
    cPt.rot.set(360, 180, 0);
    cameraPts.push_back(cPt);
    
    cPt.pos.set(200, 40, 0);
    cPt.rot.set(340, 170, 0);
    cameraPts.push_back(cPt);
    
    cPt.pos.set(200, 300, 200);
    cPt.rot.set(270, 160, 0);
    cameraPts.push_back(cPt);
    cPt.pos.set(200, 150, 200);
    cPt.rot.set(270, 140, 0);
    cameraPts.push_back(cPt);
    
    cPt.pos.set(200, 50, 200);
    cPt.rot.set(270, 140, 0);
    cameraPts.push_back(cPt);
    
    
    
    opacityButtons=255;
    

    
    cout<<"load images"<<endl;
    
    for(int i=0;i<ITEMSNUM;i++){
        image[i].load("app"+ofToString(i+1)+".png");
        imageT[i].load("t"+ofToString(i+1)+".png");
    }
    
    //ofImage image[3];
    //ofImage imageT[3];
    
    
   // image.load("under.png");
   // imageBlack.load("over.png");
   // imageWhite.load("overw.png");
    cout<<"images loaded"<<endl;
    /*
    string pointString = "1030.2, 580.6 1029.9, 578.2 1029.6, 576 1029.2, 574.1 1028.7, 572.5 1028, 570.8 1027.1, 568.5 1026, 565.4 1024.8, 561.3 1023.5, 556.1 1022.1, 549.6 1020.6, 541.7 1019, 532.2 1016.6, 523.1 1010.2, 500.6 1005.9, 486.5 1001, 471.8 995.7, 457.3 990.2, 443.9 985.4, 432.8 982, 424.2 979.7, 417.7 978.2, 412.9 977.3, 409.4 976.3, 404.4 975.7, 402.1 974.4, 399.1 972.3, 395.1 969.5, 390.4 966.2, 385.3 962.5, 380.1 958.6, 375 954.7, 370.4 951, 366.5 946.7, 362.6 940.9, 358 933.9, 352.8 925.8, 347.2 916.8, 341.4 907.1, 335.5 896.8, 329.6 886.1, 324 876.7, 319.4 869.9, 316.2 865.2, 314.3 862.3, 313.3 861, 313 860.4, 313.1 860.3, 313.4 860.4, 313.5 860.2, 313.5 859.6, 313.3 858.7, 313 857.5, 312.6 856.1, 312.1 854.5, 311.5 852.8, 310.7 851, 309.8 849.1, 308.4 847.1, 306.5 845, 304.2 843, 301.7 838.2, 295.2 837.3, 294 836.7, 293.4 836.2, 293 835.8, 292.8 835.5, 292.8 835.3, 292.9 835.2, 293 835.2, 293.1 835, 295.4 834.6, 301.1 834.4, 304.7 834.3, 308.4 834.3, 312 834.6, 318.8 834.6, 322.8 834.4, 327.2 834.1, 332 833.6, 337 832.9, 342 832, 347 830.9, 351.8 818.7, 381.8 805.7, 418 799.8, 433 793.2, 448.6 786.1, 463.9 778.6, 477.9 741.3, 543.1 697.5, 609.1 681.1, 586 674.2, 575.7 667.3, 565 661, 554.5 644.1, 522 622.4, 478.1 616.5, 465.1 612.5, 455.3 562.6, 342.1 560, 335.8 558.6, 332.1 555.4, 321.7 554.1, 317 552.9, 311.9 552, 306.5 551.5, 301 551.6, 295.6 549.7, 288 547.3, 290.9 544.6, 294.1 541.1, 298.1 539.2, 300.4 537.3, 302.9 535.4, 305.6 511.2, 342.3 505, 347.6 499.6, 352.6 497, 355.2 492.5, 360 488.1, 364.5 482.1, 370.3 481.8, 370.6 435, 419.3 431.6, 423.2 427.5, 428.5 422.4, 434.8 419.7, 438 417, 441.1 414, 444 411.5, 446.4 408.2, 449.8 403.3, 455.3 391, 470.1 384.6, 478.1 378.8, 485.7 374, 492.3 370.8, 497.3 370.4, 498.2 369.4, 500.8 368, 504.8 366.5, 510 365.1, 516.1 364, 522.9 363.4, 530.2 363.6, 537.8 370.5, 605 383, 679.8 384.3, 686 423.2, 843.6 445.1, 924.6 462.9, 984.6 464.5, 989.5 469.2, 1002.2 479.4, 1027.1 481, 1030.8 483.3, 1035.3 513, 1087.9 515.4, 1091.9 559.9, 1157.1 563.6, 1162 673.4, 1301.1 684.7, 1316.1 690.4, 1324.4 691.9, 1326.4 695.6, 1331.4 697.8, 1334.6 700.1, 1338.1 702.3, 1341.6 704.2, 1345 705.8, 1348.3 708.5, 1354.2 710.4, 1358.7 711.5, 1361.6 718.8, 1374.2 718.8, 1374.1 718.9, 1373.9 719.2, 1373.5 719.8, 1373 720.8, 1372.2 722.3, 1371.2 724.4, 1370 730.3, 1366.7 733.3, 1364.8 736.2, 1362.9 738.9, 1361.1 741.2, 1359.4 743.1, 1358 744.5, 1356.9 745.3, 1356.2 746.2, 1355.4 747.7, 1353.8 749.7, 1351.4 752.2, 1348.2 755.1, 1344.2 758.4, 1339.4 761.9, 1333.8 778.1, 1306.1 782.5, 1298.8 787.1, 1291.6 791.8, 1284.6 796.6, 1277.9 801.4, 1271.6 806.2, 1264.3 812.1, 1255.8 820.1, 1244.6 830.1, 1231.2 842, 1216 855.7, 1199.5 871, 1182 902, 1143.3 914.1, 1127.4 925.4, 1111.8 934.7, 1098 940.7, 1087.3 951.2, 1069.5 958.4, 1047.6 960.4, 1042 973.8, 1001.5 979.5, 979.3 982.1, 970.3 984.8, 961.5 987.5, 953.8 990, 948 993, 939.1 996.1, 930.6 997.9, 926.1 1001.5, 917.8 1002.8, 914.4 1003.8, 911.5 1004.5, 909 1005, 906.9 1006.2, 900.2 1006.4, 898.3 1006.6, 896.2 1006.7, 894 1006.7, 891.7 1006.7, 889.3 1006.6, 886.9 1006.4, 884.5 1006.1, 882.3 1005.6, 878.8 1005.4, 877.2 1005.2, 875.5 1005.1, 873.5 1005.1, 871 1005.2, 867.9 1014.7, 743.4 1030.7, 599.4 1031.1, 591.2 1030.8, 588.5";
    vector<string>parsedString;
    parsedString= ofSplitString(pointString, " ");
    for (int i = 0;i < parsedString.size();i+=2) {
        ofPoint ptTemp(ofToFloat(parsedString[i]), ofToFloat(parsedString[i + 1]));
        pts.push_back(ptTemp);
    }
    */
    
    
    
    font.load("brown.ttf", 14);
    
    
#ifdef TARGET_EMSCRIPTEN
    // importDesignString();
#endif
    
    
}

void ofApp::layoutVar() {
    
    margin = ofGetHeight() * 0.0666;
    marginInner = margin / 2;
    buttonWidth = ((ofGetWidth() - widthScarf) *0.5) *0.333;
    buttonWidthSmall = buttonWidth*0.3;
    
    
}
//--------------------------------------------------------------
void ofApp::update()
{
    
    
#ifdef TARGET_EMSCRIPTEN
    
    /*
    int prevDivWidth=divWidth;
    
    
    divWidth=  emscripten_run_script_int("$('#scarvesDiv').width();");
    if (divWidth!=prevDivWidth) {
        ofSetWindowShape(divWidth, divWidth);
        cout<<"resized"<<endl;
    }
    */
    
    checkChange();
    
#endif
    
    //cout<<"color num"<<currentColorNum<<endl;
    if(currentAlgo==FRACTIONAL){
        updateFrac();
    }
    if(currentAlgo==VERTICES){
        updateVert();
    }
    //if(minimalViewB==true){
    //importDesignString();
    
    //}
    
    
    
    
    //RESPONSIVE LAYOUT VARIABLE
    
    
    //	layoutVar();
    
    //  if(minimalViewB==false){
    //	updateB();
    //  }
    
    
    
    
    
    
    
    
    
    
#ifdef TARGET_EMSCRIPTEN
    //emscripten_run_script("document.getElementById('stringJava')");
#endif
    
    
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(255, 255, 255);
    
    ofSetColor(0,0,0,255);
    ofDrawRectangle(0,0,widthScarf,heightScarf);
    
    
    //ofPushMatrix();
    //ofTranslate(mouseX, 0);
    //ofScale(ofClamp(mouseY/100,1,10), ofClamp(mouseY/50,1,10));
    if(currentAlgo==FRACTIONAL){
        drawFrac();
        
    }
    if(currentAlgo==VERTICES){
        //cam.setLensOffset(ofVec2f(0,ofMap(ofGetMouseY(),0,ofGetHeight(),0,1.0)));
        //fovMult=ofMap(ofGetMouseX(), 0, ofGetWidth(), 1.0, 1.5);
        ofSetColor(255, 255, 255);
        ofEnableAlphaBlending();
        drawVert();

    }
    //ofPopMatrix();
    
    
    //tCol[0].set(255,0,0);
    //message="center test";
    if(message!="" && message!=" " && message!="%20"){
        ofSetColor(rVal[1],gVal[1],bVal[1]);
    font.drawString(message,(widthScarf/2)-(font.getStringBoundingBox(message,0,0).width)/2 , (heightScarf*0.16));
    }
    
    
    if (currentScene==0){
        // cout<<"before draw image"<<endl;
        ofEnableAlphaBlending();
        ofFill();
        ofSetColor(255, 255, 255, 255);
        image[currentItem].draw(0, 0, widthScarf, heightScarf);
        // cout<<"after draw image"<<endl;
    }else{
        ofEnableAlphaBlending();
        ofFill();
        ofSetColor(255, 255, 255, 255);
        imageT[currentItem].draw(0, 0, widthScarf, heightScarf);
    }
    
    ofSetColor(255, 255, 255,150);
    ofRectangle r(0,0,widthScarf,heightScarf);
    
    
    if(r.inside(mouseX, mouseY)){
        //   float ratio=widthScarf*0.03;
        //   ofDrawTriangle(ratio, heightScarf/2, ratio*2, heightScarf/2-ratio, ratio*2,  heightScarf/2+ratio);
        //  ofDrawTriangle(widthScarf-ratio, heightScarf/2,widthScarf- ratio*2, heightScarf/2-ratio,widthScarf- ratio*2,  heightScarf/2+ratio);
        
        opacityButtons+=10;
        if(opacityButtons>255){
            opacityButtons=255;
        }
        
    }else{
        opacityButtons-=2.5;
        if (opacityButtons<0) {
            opacityButtons=0;
        }
    }
    
    
    int viewNum=2;
    float radius=widthScarf*0.007;
    
    
    //float opacity
    
    for(int i=0;i<viewNum;i++){
        
        float xPos= ofLerp((widthScarf/2)-(radius*viewNum), (radius*viewNum)+(widthScarf/2),ofMap(i,0,viewNum-1,0,1,true));
        float yPos=heightScarf-(heightScarf*0.1);
        
        int hover=0;
        if(ofDist(mouseX, mouseY, xPos, yPos)<radius*2){
            hover=30;
        }
        
        ofSetColor(30-hover, 30-hover, 30-hover,opacityButtons);
        
        
        if(i==currentScene){
            ofSetColor(190-hover, 190-hover, 190-hover,opacityButtons);
        }
        //   }else{
        
        //  }
        //cout<<(i*(radius*4))+centered<<endl;
        //cout<<heightScarf-(heightScarf*0.07)<<endl;
        
        ofFill();
        ofDrawCircle(xPos,yPos , radius);
        
        
        
        
        ofNoFill();
        ofSetColor(215,215,215,opacityButtons);
        ofDrawCircle(xPos, heightScarf-(heightScarf*0.1), radius);
        //ofDrawCircle(0,0,30);
        
        
        //ofDrawCircle(widthScarf/2, heightScarf-(heightScarf*0.2), radius);
        
    }
    ofFill();
    ofSetColor(255,255,255,255);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    
    
}
//--------------------------------------------------------------
void ofApp::exit()
{
    //   gui.saveToFile("settings.xml");
    
    //   for (int i=0; i<currentColorNum; i++)
    //   {
    //r[i]->saveSettings("settingsColor"+ofToString(i)+".xml");
    //  delete guiColorG[i];
    //  }
    
    //   xml.setValue("color", currentColorNum);
    //   xml.save("settingsColor.xml");
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
    
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
#ifdef TARGET_EMSCRIPTEN
    //emscripten_run_script("alert('hi')");
    //int emscripten_run_script_int(" ");
    //char * inputString= emscripten_run_script_string("document.getElementById('stringJava').value");
#endif
   // useFogDebug=!useFogDebug;
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    
    
    
    
    
    
    
#ifdef TARGET_EMSCRIPTEN
    string e;
    //  e=exportDesignString();
#endif
    
    
    
    ofRectangle r(0,0,widthScarf,heightScarf);
    if(r.inside(mouseX, mouseY)){
        currentScene++;
        if(currentScene>1){
            currentScene=0;
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
    
}





void ofApp::addColor(){
   // if(currentAlgo==FRACTIONAL){
    if(currentColorNum<5){
    
        //if (currentColorNum<MAX_COLOR)
        //{
       // cout << "NEW COLOR" << endl;
        ofColor col = grad.getColorAtPercent(1);
        
        //TO CHANGE
        
        rVal[currentColorNum]=col.r;
        gVal[currentColorNum]=col.g;
        bVal[currentColorNum]=col.b;
        
        grad.addColor(grad.getColorAtPercent(1));
        //currentColorNum++;//
        //}
   // }
    //}
    
   // if(currentAlgo==VERTICES){
     //     if (currentColorNum<5)
      //   {
        
        tCol[currentColorNum]=tCol[currentColorNum-1];
        //red[currentColorNum]=red[currentColorNum-1];
        //green[currentColorNum]= green[currentColorNum - 1];
        //blue[currentColorNum]= blue[currentColorNum - 1];
        //}
  
    currentColorNum++;
    }

//}

}

void ofApp::removeColor(){
    
    
    
    //if(currentAlgo==FRACTIONAL){
        if(currentColorNum>2){
        //if (currentColorNum>=MIN_COLOR)
        //{
       // cout << "REMOVED COLOR" << endl;
        grad.deleteColor();
        
        //currentColorNum--;
        //}
     //   }
   // }
    //if(currentAlgo==VERTICES){
      //  if(currentColorNum>2){
        // {
      //  cout << "REMOVED COLOR" << endl;
        currentColorNum--;
        //}
    //}
        }
}

string ofApp::exportDesignString() {
    /*
    string designSt = "";
    
    //float widthThings2 = widthThings - bWidth;
    
    
    
    designSt += ofToString(fluidityVal[0]);
    designSt += ";";
    designSt += ofToString(fluidityVal[1]);
    designSt += ";";
    designSt += ofToString(fluidityVal[2]);
    designSt += ";";
    designSt += ofToString(scaleVal);
    designSt += ";";
    designSt += ofToString(currentTime);//ofGetFrameNum() *timeMotionVal.getValue());
    designSt += ";";
    
    designSt += ofToString(widthScarf);//ofGetFrameNum() *timeMotionVal.getValue());
    designSt += ";";
    
    designSt += ofToString(heightScarf);//ofGetFrameNum() *timeMotionVal.getValue());
    designSt += ";";
    
    
    designSt += ofToString(currentColorNum);
    designSt += ";";
    
    
    for (int i = 0; i<currentColorNum; i++)
    {
        
        designSt += ofToString(rVal[i]);
        designSt += ";";
        designSt += ofToString(gVal[i]);
        designSt += ";";
        designSt += ofToString(bVal[i]);
        designSt += ";";
        
    }
    
#ifdef TARGET_EMSCRIPTEN
    //  string stringUrl="'http://www.convivialproject.com/shop/create-your-own-silk-habotai?usc="+exportDesignString()+"'";
    //  std::replace( stringUrl.begin(), stringUrl.end(), ';', ',');
    string ofString="setUsc('"+designSt+"');";
    const char * passString=ofString.c_str();
    emscripten_run_script(passString);
#endif
    */
    
    string designSt;
    return designSt;
}

void ofApp::importDesignString() {
    
    
#ifdef TARGET_EMSCRIPTEN

#endif
    
    
}


void ofApp::checkChange(){
    
    
#ifdef TARGET_EMSCRIPTEN
    
    
    char * input= emscripten_run_script_string("getVar();");
    string inputString(input);
    
    
  //  cout<<"designString"<<inputString<<endl;
    if (inputString!="") {
        
        
        vector<string>parsedString=ofSplitString(inputString, ";",true,true);
        
        
        for(int i=0;i<parsedString.size();i++){
            
            //string parsedString = inputString;//ofSplitString(inputString, ";",true,true);//ignore empty and trim
      //        cout<<"input"<<parsedString[i]<<endl;
            
            
            
            vector<string>pVar=ofSplitString(parsedString[i], ":",true,true);
            
            
            if(pVar.size()<1){
                // cout<<"reading unlabeled var"<<endl;
            }
            int indexVar;
            
            for(int j=0;j<varMap.size();j++){
                if(varMap[j]==pVar[0]){
                    indexVar=j;
              //      cout<<"indexVar"<<ofToString(indexVar)<<endl;
                    //val=ofToFloat(pVar[index]
                    //cout<<"val"<<pVar[1]<<endl;
                }
            }
            if(indexVar==ALGO){
                currentAlgo=ofToInt(pVar[1]);
                
                
                //RESET COLOR TO 2
                if(currentAlgo==FRACTIONAL){
               // while (currentColorNum>2) {
               //     removeColor();
                 //   currentColorNum--;
                //}
                }
                //RESET COLOR TO 2
                if(currentAlgo==VERTICES){
                   // while (currentColorNum>2) {
                     //   removeColor();
                    //}
                }
          
                
                
            }
            
            
            if(currentAlgo==FRACTIONAL){
                
                switch (indexVar){
                    case PLAY:
                    {
               //         cout<<"play pause"<<pVar[1]<<endl;
                        play=ofToBool(pVar[1]);
                        
                        break;
                    }
                    case SL1:
                    {
                        fluidityVal[0]=ofMap(ofToFloat(pVar[1]),0,100,0.001f, 5,true);
                        
                        break;
                    }
                    case SL2:
                    {
                        fluidityVal[1]=ofMap(ofToFloat(pVar[1]),0,100,0.100f, 1,true);
                        
                        break;
                    }
                    case SL3:
                    {
                        fluidityVal[2]=ofMap(ofToFloat(pVar[1]),0,100,1, 7,true);
                        
                        break;
                    }
                    case SL4:
                    {
                        scaleVal=ofMap(ofToFloat(pVar[1]),0,100,5, 1000,true);////scaleMult;
                        
                        break;
                    }
                    case RESW:
                    {
                        //float inputScarfW = ofToFloat(pVar[1]);
                        //  float inputScarfH = ofToFloat(parsedString[6]);
                        
                  
                        
                        int prevDivWidth=divWidth;
                        divWidth=ofToFloat(pVar[1]);
                        
                        
                        scaleMult = (float)dimensionWeb / (float)divWidth;
                        
                      //  cout<<"previous size:"<<prevDivWidth<<" new size:"<<divWidth<<" scaleMult:"<<scaleMult<<endl;
                        
                        if (divWidth!=prevDivWidth) {
                        
                            ofSetWindowShape(divWidth, divWidth);// *0.666
                        //    cout<<"resized"<<endl;
                            widthScarf=divWidth;
                            heightScarf=divWidth;
                        
                        }
                        
                        
                        break;}
                    case TIMER:
                    {
                        currentTime=ofToFloat(pVar[1]);
                        
                        break;}
                    case NAME:
                    {
                        message=ofToString(pVar[1]);
                        
                        break;}
                    case COLORNUM:
                    {
                        
                        /*
                        if (ofToInt(pVar[1]) != currentColorNum) {
                            
                            // cout<<" inputVar:"<<ofToInt(pVar[1])<<" current col:"<<currentColorNum<<endl;
                            
                            if(ofToInt(pVar[1])>currentColorNum){
                                
                                int newColN=(ofToInt(pVar[1])-currentColorNum);
                                
                                for(int n=0;n<newColN;n++){
                                    cout<<" add col in em:"<<ofToInt(pVar[1])<<" current col:"<<currentColorNum<<endl;
                                    
                                    addColor();
                                    }
                                
                            }
                            
                            if( ofToInt(pVar[1]) < currentColorNum ){
                                //   cout<<"remove"<<endl;
                                int newColN=(currentColorNum-ofToInt(pVar[1]));
                                for(int n=0;i<newColN;n++){
                                    cout<<" remove col in em:"<<ofToInt(pVar[1])<<" current col:"<<currentColorNum<<endl;
                                    
                                    //addColor();
                                    removeColor();
                                }
                                
                                //removeColor();
                            }
                            cout<<"SHOULD MATCH"<<currentColorNum<<"with"<<ofToInt(pVar[1]);
                            //currentColorNum=ofToInt(pVar[1]);
                         
                        }*/
                        if(ofToInt(pVar[1])>=MIN_COLOR && ofToInt(pVar[1])<=MAX_COLOR){
                            if (ofToInt(pVar[1]) != currentColorNum) {
                                
                                while(currentColorNum!=ofToInt(pVar[1])){
                                    if(ofToInt(pVar[1])>currentColorNum){
                                        //for (int i = 0;i < MAX_COLOR;i++) {
                                        addColor();
                                        //}
                                    }else if(ofToInt(pVar[1])<currentColorNum){
                                        //
                                        //for (int i = 0;i < ofToInt(pVar[1]);i++) {//-2
                                        removeColor();
                                        //}
                                    }
                                }
                            }
                            
                            //currentColorNum=ofToInt(pVar[1]);
                        }cout<<"SHOULD MATCH"<<currentColorNum<<"with"<<ofToInt(pVar[1]);
                        
                        break;}
                    case RGB1:
                    {
                        vector<string>colRGB=ofSplitString(pVar[1], ",",true,true);
                        int rgbIndex=0;
                        rVal[rgbIndex]=ofToInt(colRGB[0]);
                        gVal[rgbIndex]=ofToInt(colRGB[1]);
                        bVal[rgbIndex]=ofToInt(colRGB[2]);
                        //ofColor col(rVal[rgbIndex],gVal[rgbIndex],bVal[rgbIndex]);
                        //colorPicker[rgbIndex].setColor(col);
                        
                        break;}
                    case RGB2:
                    {
                        vector<string>colRGB=ofSplitString(pVar[1], ",",true,true);
                        int rgbIndex=1;
                        rVal[rgbIndex]=ofToInt(colRGB[0]);
                        gVal[rgbIndex]=ofToInt(colRGB[1]);
                        bVal[rgbIndex]=ofToInt(colRGB[2]);
                        //ofColor col(rVal[rgbIndex],gVal[rgbIndex],bVal[rgbIndex]);
                        //colorPicker[rgbIndex].setColor(col);
                        
                        break;}
                    case RGB3:
                    {
                        vector<string>colRGB=ofSplitString(pVar[1], ",",true,true);
                        int rgbIndex=2;
                        rVal[rgbIndex]=ofToInt(colRGB[0]);
                        gVal[rgbIndex]=ofToInt(colRGB[1]);
                        bVal[rgbIndex]=ofToInt(colRGB[2]);
                        //ofColor col(rVal[rgbIndex],gVal[rgbIndex],bVal[rgbIndex]);
                        //colorPicker[rgbIndex].setColor(col);
                        
                        break;}
                    case RGB4:
                    {
                        vector<string>colRGB=ofSplitString(pVar[1], ",",true,true);
                        int rgbIndex=3;
                        rVal[rgbIndex]=ofToInt(colRGB[0]);
                        gVal[rgbIndex]=ofToInt(colRGB[1]);
                        bVal[rgbIndex]=ofToInt(colRGB[2]);
                        //ofColor col(rVal[rgbIndex],gVal[rgbIndex],bVal[rgbIndex]);
                        //colorPicker[rgbIndex].setColor(col);
                        
                        break;}
                    case RGB5:
                    {
                        vector<string>colRGB=ofSplitString(pVar[1], ",",true,true);
                        int rgbIndex=4;
                        rVal[rgbIndex]=ofToInt(colRGB[0]);
                        gVal[rgbIndex]=ofToInt(colRGB[1]);
                        bVal[rgbIndex]=ofToInt(colRGB[2]);
                        //ofColor col(rVal[rgbIndex],gVal[rgbIndex],bVal[rgbIndex]);
                        //colorPicker[rgbIndex].setColor(col);
                        
                        break;}
                    case VIEW:
                    {
                        currentScene=ofToInt(pVar[1]);
                        
                        break;}
                    case SIZE:
                    {
                        productSize=ofToString(pVar[1]);
                        
                        break;}
                    case GETVAR:
                    {
                    //    cout<<"input var getvar"<<pVar[1]<<endl;
                        if(ofToInt(pVar[1])==1){
                            cout<<"currentTime="+ofToString(currentTime)+";"<<endl;
                            string ofString="currentTime="+ofToString(currentTime)+";";
                            const char * passString=ofString.c_str();
                            emscripten_run_script(passString);
                        }
                           
                           break;}
                    default :{
                       // cout<<"default"<<endl;
                    }
                }
                
                
                if(indexVar==COLORNUM||indexVar==RGB1||indexVar==RGB2||indexVar==RGB3||indexVar==RGB4||indexVar==RGB5){
                    for(int i=0; i< currentColorNum ; i++)
                    {
                        //rVal[i].setValue(copyColR[i]);
                        //gVal[i].setValue(copyColG[i]);
                        //bVal[i].setValue(copyColB[i]);
                        ofColor c;
                        c.set(rVal[i], gVal[i],bVal[i]);
                        grad.replaceColorAtIndex(i, c);
                    }
                    
                    ofPixels pix=grad.getRef(256, 256);
                    
                    ofTexture tex;
                    tex.allocate(pix);
                    shader.begin();
                    shader.setUniformTexture( "gradient", tex, 1 );
                    shader.end();
                }
                
                
            }
            if(currentAlgo==VERTICES){
                
                //gui1.setup("camera", "settings1.xml",0,20);
                //gui1.add(windSpeed.setup("wind speed", 32, 2, 1000));
                //gui1.add(waveScale.setup("wave scale", 60, 0.0, 1000));
                //gui1.add(fogDensity.setup("fogDensity", 0.04, 0.0, 0.15));
                //gui1.add(waveSpeed.setup("waveSpeed", 2, 0, 10));
                //gui1.add(choppyScale.setup("choppyScale", 3, 0.0, 20));
                switch (indexVar){
                    case PLAY:
                    {
                        play=ofToBool(pVar[1]);
                        
                        break;}
                    case SL1:
                    {
                        waveScale=ofMap(ofToFloat(pVar[1]),0,100,0,1000,true);
                        
                        break;}
                    case SL2:
                    {
                        cameraMove=ofMap(ofToFloat(pVar[1]),0,100,0, 1.0,true);
                        
                        break;}
                    case SL3:
                    {
                        oceanTileResolution=ofMap(ofToFloat(pVar[1]),0,100,4, 104,true);
                        
                        break;}
                    case SL4:
                    {
                        fogDensity=ofMap(ofToFloat(pVar[1]),0,100,0,0.006,true);//*scaleMult;
                        
                        break;}
                    case TG1:
                    {
                        //cout<<" to bool"<<ofToBool(pVar[1])<<endl;
                        drawFaces=ofToBool(pVar[1]);
                        break;}
                    case TG2:
                    {
                        //cout<<" to bool"<<ofToBool(pVar[1])<<endl;
                        drawWireFrame=ofToBool(pVar[1]);
                        break;}
                    case TG3:
                    {
                        //cout<<" to bool"<<ofToBool(pVar[1])<<endl;
                        drawVertices=ofToBool(pVar[1]);
                        break;}
                    case TG4:
                    {
                        alphaBlending=ofToBool(pVar[1]);
                        break;}
                    case NAME:
                    {
                        message=ofToString(pVar[1]);
                        break;}
                        
                    case TIMER:
                    {
                        currentTime=ofToFloat(pVar[1]);
                        
                        break;}
                    case COLORNUM:
                    {
                        if(ofToInt(pVar[1])>=MIN_COLOR && ofToInt(pVar[1])<=MAX_COLOR){
                            if (ofToInt(pVar[1]) != currentColorNum) {
                                
                                while(currentColorNum!=ofToInt(pVar[1])){
                                    if(ofToInt(pVar[1])>currentColorNum){
                                        //for (int i = 0;i < MAX_COLOR;i++) {
                                        addColor();
                                        //}
                                    }else if(ofToInt(pVar[1])<currentColorNum){
                                        //
                                        //for (int i = 0;i < ofToInt(pVar[1]);i++) {//-2
                                        removeColor();
                                        //}
                                    }
                                }
                            }
                            
                            //currentColorNum=ofToInt(pVar[1]);
                        }cout<<"SHOULD MATCH"<<currentColorNum<<"with"<<ofToInt(pVar[1]);
                        
                        
                        
                        break;}
                    case RESW:
                    {
                        int prevDivWidth=divWidth;
                        divWidth=ofToFloat(pVar[1]);
                        
                        
                        scaleMult = (float)dimensionWeb / (float)divWidth;
                        
                        //  cout<<"previous size:"<<prevDivWidth<<" new size:"<<divWidth<<" scaleMult:"<<scaleMult<<endl;
                        
                        if (divWidth!=prevDivWidth) {
                            
                            ofSetWindowShape(divWidth, divWidth);// *0.666
                            //    cout<<"resized"<<endl;
                            widthScarf=divWidth;
                            heightScarf=divWidth;
                            
                        }
                        
                        break;}
                    case RGB1:
                    {
                        vector<string>colRGB=ofSplitString(pVar[1], ",",true,true);
                        int rgbIndex=0;
                        tCol[rgbIndex].set(ofToInt(colRGB[0]),ofToInt(colRGB[1]),ofToInt(colRGB[2]));
                        
                        break;}
                    case RGB2:
                    {
                        vector<string>colRGB=ofSplitString(pVar[1], ",",true,true);
                        int rgbIndex=1;
                        tCol[rgbIndex].set(ofToInt(colRGB[0]),ofToInt(colRGB[1]),ofToInt(colRGB[2]));
                        
                        break;}
                    case RGB3:
                    {
                        vector<string>colRGB=ofSplitString(pVar[1], ",",true,true);
                        int rgbIndex=2;
                        tCol[rgbIndex].set(ofToInt(colRGB[0]),ofToInt(colRGB[1]),ofToInt(colRGB[2]));
                        
                        break;}
                    case RGB4:
                    {
                        vector<string>colRGB=ofSplitString(pVar[1], ",",true,true);
                        int rgbIndex=3;
                        tCol[rgbIndex].set(ofToInt(colRGB[0]),ofToInt(colRGB[1]),ofToInt(colRGB[2]));
                        
                        break;}
                    case RGB5:
                    {
                        vector<string>colRGB=ofSplitString(pVar[1], ",",true,true);
                        int rgbIndex=4;
                        tCol[rgbIndex].set(ofToInt(colRGB[0]),ofToInt(colRGB[1]),ofToInt(colRGB[2]));
                        
                        break;}
                    case VIEW:
                    {
                        currentScene=ofToInt(pVar[1]);
                        
                        break;}
                    case SIZE:
                    {
                        productSize=ofToString(pVar[1]);
                        
                        break;}
                    case GETVAR:
                    {
                        // cout<<"input var getvar"<<pVar[1]<<endl;
                        if(ofToInt(pVar[1])==1){
                           // cout<<"send time var"<<endl;
                            string ofString="currentTime="+ofToString(currentTime)+";";
                            const char * passString=ofString.c_str();
                            emscripten_run_script(passString);
                        }
                        
                    break;}
                    default :{
                       // cout<<"default"<<endl;
                    }
                }
                
                if(indexVar==COLORNUM||indexVar==RGB1||indexVar==RGB2||indexVar==RGB3||indexVar==RGB4||indexVar==RGB5){
                    for(int i=0; i< currentColorNum ; i++)
                    {
                        //rVal[i].setValue(copyColR[i]);
                        //gVal[i].setValue(copyColG[i]);
                        //bVal[i].setValue(copyColB[i]);
                        ofColor c;
                        c.set(rVal[i], gVal[i],bVal[i]);
                        grad.replaceColorAtIndex(i, c);
                    }
                    
                    ofPixels pix=grad.getRef(256, 256);
                    
                    ofTexture tex;
                    tex.allocate(pix);
                    shader.begin();
                    shader.setUniformTexture( "gradient", tex, 1 );
                    shader.end();
                }
                
                
            }
            
            //MIXED
            switch (indexVar){
            
            
            }
            
            
            
            
        }
        
    
        /*
    string ofStringClear="sentVar='';";
    const char * passStringc=ofStringClear.c_str();
    emscripten_run_script(passStringc);
    */
    }
    

    
#endif
    
    
}

void ofApp::setupFrac(){
    
    
}

void ofApp::updateFrac(){
    if (play) {
        // relativeTime +=0.000000002;
        currentTime+=0.00125;
        // timeMotionVal.setPercent(0.3);
    }
    
    for(int i=0; i<grad.getNumColors(); i++)
    {
        //    if (btColor[i].buttonState==true) {
        ofColor c;
        c.set(rVal[i], gVal[i],bVal[i]);
        grad.replaceColorAtIndex(i, c);
    }
    
    
}

void ofApp::drawFrac(){
    
    
    ofSetColor(255,255,255,255);
    
    ofPixels pix=grad.getRef(256, 256);
    
    ofTexture tex;
    
    tex.allocate(pix);
    
    shader.begin();
    
    shader.setUniform1f("fluidity1", fluidityVal[0]);
    shader.setUniform1f("fluidity2", fluidityVal[1]);
    shader.setUniform1i("fluidity3", fluidityVal[2]);
    
    
    float testDivide= (float)divWidth/(float)dimensionWeb  ;
    
    shader.setUniform1f("scaleWidth",scaleVal*testDivide);//*scaleMult
    shader.setUniform1f("scaleHeight", scaleVal*testDivide);//*scaleMult
    shader.setUniform1f("time", currentTime);//ofGetFrameNum() *timeMotionVal.getValue());
    shader.setUniformTexture( "gradient", tex, 1 );
    shader.setUniform1f("colorThreshold", colorThreshold);
    shader.setUniform1f("gradientWidth", 256.0);
    
   // shader.setUniform2f("offset",ofMap((float)ofGetMouseX(),0,ofGetWidth()/2,0,-1.0),ofMap((float)ofGetMouseY(),0,ofGetHeight()/2,0,1.0));
    
   // shader.setUniform2f("offset",(float)ofMap(ofGetMouseX(),0,ofGetWidth(),ofGetWidth()/2,0),(float)ofGetMouseY()/2);
    
    
    if(currentScene==1){
        ofDrawRectangle(0,0,widthScarf,heightScarf);
    }else if (currentScene==0){
        
        shader.setUniform1f("scaleWidth", scaleVal/scaleMult);// *1.3);*scaleMult
        shader.setUniform1f("scaleHeight", scaleVal/scaleMult);// 1.3);*scaleMult
        
        
      //  cout<<" scale multiply"<<scaleVal*scaleMult<<endl;
        
        ofSetColor(255, 255, 255);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        
        /*
        ofPushMatrix();
        ofScale((float)widthScarf/1400.0, (float)widthScarf/1400.0);
        ofBeginShape();
        for (int i = 0;i < pts.size();i++) {
            ofVertex(pts[i]);
        }
        ofEndShape();
        */
        
        
        
        //ofPopMatrix();
    }
    
    
    
    
    
    shader.end();
    ofSetColor(255, 255, 255);
    
    ofFill();
    ofSetColor(255, 255, 255,255);
    ofEnableAlphaBlending();
    /*
     if(minimalViewB==false){
     drawB();
     }
     */
}


void ofApp::setupVert(){
    fogShader.load("fog");
    
}
//
void ofApp::updateVert(){
    
    /*
     for (int i = 0;i < MAX_COLOR;i++) {
     ofColor tCol = colorSliders[i];
     red[i] = tCol.r;
     green[i] = tCol.g;
     blue[i] = tCol.b;
     }
     */
    
    
    //   ofColor tCol[MAX_COLOR];
    
    // for (int i = 0;i < MAX_COLOR;i++) {
    //     tCol[i].set(red[i], green[i], blue[i]);
    // }
    
    switch (currentColorNum) {
        case 2:
            
            bgColor1 = tCol[0];
            bgColor2 = tCol[0];
            fogColor = tCol[0];
            emissiveColor = tCol[1];
            ambientColor = tCol[0];
            diffuseColor = tCol[1];
            specularColor = tCol[0];
            wireFrameOnlyColor = tCol[0];
            pointLight.setDiffuseColor(tCol[0]);
            pointLight.setSpecularColor(tCol[0]);
            
            break;
            
        case 3:
            
            bgColor1 = tCol[0];
            bgColor2 = tCol[2];
            fogColor = tCol[0];
            emissiveColor = tCol[1];
            ambientColor = tCol[2];
            diffuseColor = tCol[1];
            specularColor = tCol[2];
            wireFrameOnlyColor = tCol[0];
            pointLight.setAmbientColor(ofFloatColor(1.0, 1.0, 1.0));
            pointLight.setDiffuseColor(tCol[0]);
            pointLight.setSpecularColor(tCol[2]);
            
            break;
            
        case 4:
            
            bgColor1 = tCol[0];
            bgColor2 = tCol[2];
            fogColor = tCol[3];
            emissiveColor = tCol[1];
            ambientColor = tCol[2];
            diffuseColor = tCol[3];
            specularColor = tCol[2];
            wireFrameOnlyColor = tCol[3];
            pointLight.setAmbientColor(ofFloatColor(1.0, 1.0, 1.0));
            pointLight.setDiffuseColor(tCol[0]);
            pointLight.setSpecularColor(tCol[3]);
            
            break;
            
        case 5:
            
            bgColor1 = tCol[0];
            bgColor2 = tCol[2];
            fogColor = tCol[3];
            emissiveColor = tCol[1];
            ambientColor = tCol[2];
            diffuseColor = tCol[4];
            specularColor = tCol[4];
            wireFrameOnlyColor = tCol[3];
            pointLight.setAmbientColor(ofFloatColor(1.0, 1.0, 1.0));
            pointLight.setDiffuseColor(tCol[4]);
            pointLight.setSpecularColor(tCol[3]);
            
            break;
            /*
             case 11:
             
             bgColor1 = tCol[0];
             bgColor2 = tCol[1];
             fogColor = tCol[2];
             emissiveColor = tCol[3];
             ambientColor = tCol[4];
             diffuseColor = tCol[5];
             specularColor = tCol[6];
             wireFrameOnlyColor = tCol[7];
             pointLight.setAmbientColor(tCol[8]);
             pointLight.setDiffuseColor(tCol[9]);
             pointLight.setSpecularColor(tCol[10]);
             
             break;
             */
    }
    
    
    
    
    
    if (useEasyCam == false){
        cam.setPosition(camPosition);
        cam.setOrientation(camAngle);
        cam.setFov(fov*fovMult);
    }
    
    //ocean.size = ofVec3f(int(resolutionMesh), 1.0, int(resolutionMesh));
    if (oceanTileResolution != ocean.width) {
        ocean.changeResolution(oceanTileResolution, oceanTileResolution);
        renderer.setup(&ocean, 1, 1);
    }
    
    if(play){
        currentTime++;
    }
    ocean.setFrameNum((int)currentTime);
    //cout << "set frame num" << ofGetFrameNum() << endl;
    //ocean.windSpeed = windSpeed;
    
    float newWaveScale = ofMap(waveScale, 0, 400,0,ofMap(oceanTileResolution,4,220,0,400,true),true);
    //cout << "new wave scale" << newWaveScale << endl;
    ocean.waveScale = newWaveScale;//waveScale;;
    ocean.waveSpeed = waveSpeed;
    ocean.choppyScale = choppyScale;
    
    
    
    mat.setAmbientColor(ambientColor);
    mat.setDiffuseColor(diffuseColor);
    mat.setEmissiveColor(emissiveColor);
    mat.setSpecularColor(specularColor);
    mat.setShininess(shininess);
    
    pointLight.setDiffuseColor(lightColor);
    pointLight.setPosition(centerLight);
    ocean.update(camPosition,radiusFlat);
    
    renderer.update();
    
    
    float cameraSteps = 1.0 / ((float)cameraPts.size());
    for (int i = 0;i < cameraPts.size()-1;i++)
    {
        if (cameraMove >= i*cameraSteps && cameraMove < (i + 1) * cameraSteps) {
            
            //cout << "i" << i << endl;
            
            float x = ofMap(cameraMove, i*cameraSteps, (i + 1) * cameraSteps, cameraPts[i].pos.x, cameraPts[i + 1].pos.x,true);
            float y = ofMap(cameraMove, i*cameraSteps, (i + 1) * cameraSteps, cameraPts[i].pos.y, cameraPts[i + 1].pos.y, true);
            float z = ofMap(cameraMove, i*cameraSteps, (i + 1) * cameraSteps, cameraPts[i].pos.z, cameraPts[i + 1].pos.z, true);
            camPosition = ofPoint(x, y, z);
            //cam.setPosition(x, y, z);
            float xr = ofMap(cameraMove, i*cameraSteps, (i + 1) * cameraSteps, cameraPts[i].rot.x, cameraPts[i + 1].rot.x, true);
            float yr = ofMap(cameraMove, i*cameraSteps, (i + 1) * cameraSteps, cameraPts[i].rot.y, cameraPts[i + 1].rot.y, true);
            float zr = ofMap(cameraMove, i*cameraSteps, (i + 1) * cameraSteps, cameraPts[i].rot.z, cameraPts[i + 1].rot.z, true);
            camAngle = ofPoint(xr, yr, zr);
            //cam.setOrientation(ofVec3f(xr, yr, zr));
            return;
        }
        
    }
}
//
void ofApp::drawVert(){
    
    


    
    //ofSetColor(0, 255, 0);
    //ofSphere(camPosition, 1);
    ofSetColor(255, 255, 255);
    
    
#ifdef TARGET_EMSCRIPTEN
        ofBackgroundGradient(bgColor1, bgColor2,OF_GRADIENT_LINEAR);
    
    ofSetLineWidth(3);
    

    
    ofCamera cam2;
    cam2 =cam;
    cam2.setScale(0.9);
    
    if (useEasyCam){
        easyCam.begin();
    }
    else{
        cam2.begin();
    }
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    ofEnableLighting();
    pointLight.enable();
    mat.begin();
    
    if (alphaBlending){
        ofEnableBlendMode(OF_BLENDMODE_ADD);
    }
    else{
        glEnable(GL_DEPTH_TEST);
        
    }
    
    if (drawFaces)renderer.draw();
    
    if (drawFaces == false ) { //LIGHTS ON VERTICES AND WIREFRAME IF NO FACES
        if (drawWireFrame)renderer.drawWireframe();
        if (drawVertices)renderer.drawVertices();
    }
    
    mat.end();
    ofDisableLighting();
    pointLight.disable();
    
    if (drawFaces) {
        ofEnableAlphaBlending();
        ofSetColor(wireFrameOnlyColor);
        if (drawWireFrame)renderer.drawWireframe();
        if (drawVertices)renderer.drawVertices();
    }
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    if (useEasyCam){
        easyCam.end();
    }
    else{
        cam2.end();
    }
    
    if (useEasyCam){
        easyCam.begin();
    }
    else{
        cam.begin();
    }
    
    //if(useFogDebug){
        fog.begin();
        fog.setUniform1f("u_fogMinDist",fogDensity);
        fog.setUniform4f("u_fogColor", fogColor);//("u_fogMinDist",fogMin);
    //}
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    
    if (drawFaces)renderer.draw();
    if (drawFaces == false ) { //LIGHTS ON VERTICES AND WIREFRAME IF NO FACES
        if (drawWireFrame)renderer.drawWireframe();
        if (drawVertices)renderer.drawVertices();
    }
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    //if(useFogDebug){
        fog.end();
    //}
    
    if (useEasyCam){
        easyCam.end();
    }
    else{
        cam.end();
    }
    
    
#else
    
    
    if (useEasyCam){
        easyCam.begin();
    }
    else{
        cam.begin();
    }
    glPushAttrib(GL_POINT_BIT | GL_POLYGON_BIT | GL_FOG_BIT | GL_DEPTH_BITS);
    
    
    
    ofSetLineWidth(3);
    
    
    
    
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glPointSize(pointSize*3);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glEnable(GL_FOG);
    glFogi(GL_FOG_COORD_SRC, GL_FRAGMENT_DEPTH);
    glFogi(GL_FOG_MODE, GL_EXP);
    //ofFloatColor fogCol = fogColor;
    //float FogCol[3] = { fogCol.r, fogCol.g, fogCol.b };
    //glFogfv(GL_FOG_COLOR, FogCol);
    glFogf(GL_FOG_DENSITY, powf(fogDensity, 2));
    
    
    
    
    ofEnableLighting();
    pointLight.enable();
    
    mat.begin();
    
    
    
    
    
    if (useFlatSurface) {
        glShadeModel(GL_FLAT);
    }
    //	glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
    
    if (alphaBlending){
        //ofFloatColor bgCol = bgColor1;
        ofFloatColor nfogColor=fogColor;
        GLfloat glfogColor[4] = { nfogColor.r,nfogColor.g, nfogColor.b, 1.0 };
        glFogfv(GL_FOG_COLOR, glfogColor);
        glEnable(GL_DEPTH_TEST);
        ofEnableAlphaBlending();
    }
    else{
        ofFloatColor nfogColor = fogColor;
        GLfloat glfogColor[4] = { nfogColor.r,nfogColor.g, nfogColor.b, 1.0 };
        glFogfv(GL_FOG_COLOR, glfogColor);
        glDisable(GL_DEPTH_TEST);
        ofEnableBlendMode(OF_BLENDMODE_ADD);
    }
    
    glPolygonOffset(1, 0);
    glPointSize(pointSize*3);
    if (drawFaces)renderer.draw();
    
    //	glProvokingVertex(GL_LAST_VERTEX_CONVENTION);
    
    if (drawFaces == false ) { //LIGHTS ON VERTICES AND WIREFRAME IF NO FACES
        if (drawWireFrame)renderer.drawWireframe();
        if (drawVertices)renderer.drawVertices();
    }
    
    
    
    mat.end();
    
    ofDisableLighting();
    pointLight.disable();
    
    if (drawFaces) {
        ofEnableAlphaBlending();
        ofSetColor(wireFrameOnlyColor);
        if (drawWireFrame)renderer.drawWireframe();
        if (drawVertices)renderer.drawVertices();
    }
    
    
    glPopAttrib();
    
    if (useEasyCam){
        easyCam.end();
    }
    else{
        cam.end();
    }
    
    
#endif
    
    
 
    
    
    //	ofEnableAlphaBlending();
    ofSetColor(255, 255, 255);
    
    
}
//
