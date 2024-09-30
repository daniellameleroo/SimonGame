#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
	//Let's create our buttons
	RedButton = new Button(ofGetWindowWidth()/2-20,ofGetWindowHeight()/2-260,302,239,"images/RedButton.png","sounds/RedButton.mp3");
	BlueButton = new Button(ofGetWindowWidth()/2+35,ofGetWindowHeight()/2-10,236,290,"images/BlueButton.png","sounds/BlueButton.mp3");
	YellowButton = new Button(ofGetWindowWidth()/2-260,ofGetWindowHeight()/2+40,287,239,"images/YellowButton.png","sounds/YellowButton.mp3");
	GreenButton = new Button(ofGetWindowWidth()/2-260,ofGetWindowHeight()/2-260,234,294,"images/GreenButton.png","sounds/GreenButton.mp3");
	ModeButton = new Button(ofGetWindowWidth()/2-400,ofGetWindowHeight()/2-350,150,150,"images/Mode.png","sounds/BackgroundMusic.mp3");
	MultiplayerButton = new Button(ofGetWindowWidth()/2+300,ofGetWindowHeight()/2-350,150,150,"images/Multiplayer.png","sounds/BackgroundMusic.mp3");
	//Load the glowing images for the buttons
	redLight.load("images/RedLight.png");
    blueLight.load("images/BlueLight.png");
    yellowLight.load("images/YellowLight.png");
    greenLight.load("images/GreenLight.png");
	//Load other images
	logo.load("images/Logo.png");
	logoLight.load("images/LogoLight.png");
	startUpScreen.load("images/StartScreen.png");
	gameOverScreen.load("images/GameOverScreen.png");
	multiplayerIndicator.load("images/multiplayerIndicator(1).png");
	modeIndicator.load("images/modeIndicator.png");
	classicIndicator.load("images/classicIndicator(1).png");
	record.load("images/Record.png");
	replaying.load("images/Replay.png");
	backspace.load("images/Backspace.png");
    //Load Music
	backgroundMusic.load("sounds/BackgroundMusic.mp3");
	backgroundMusic.setLoop(true);
	backgroundMusic.play();
	//Initial State
	gameState = StartUp;
}
//--------------------------------------------------------------
void ofApp::update(){
	//We will tick the buttons, aka constantly update them
	//while expecting input from the user to see if anything changed
	if(gameState == PlayerInput)
	{
		RedButton->tick();
		BlueButton->tick();
		YellowButton->tick();
		GreenButton->tick();
		//If the amount of user input equals the sequence limit
		//that means the user has successfully completed the whole
		//sequence and we can proceed with the next level of multiplayer mode
		if(userIndex == sequenceLimit and multiplayer_mode == false)
		{
			generateSequence();
			userIndex = 0;
			showingSequenceDuration = 0;
			gameState = PlayingSequence;
		}
		if(userIndex == sequenceLimit && player1 == true && multiplayer_mode == true)
		{
			//generateSequence();
			highscoreplayer1++;
			generateSequenceplayer2();
			userIndex = 0;
			showingSequenceDuration = 0;
			player1 = false;
			gameState = PlayingSequence;
	}
	if(userIndex == sequenceLimit && player1 == false && multiplayer_mode == true){
			//generateSequenceplayer2();'
			highscoreplayer2++;
			generateSequence();
			userIndex = 0;
			showingSequenceDuration = 0;
			gameState = PlayingSequence;
			player1 = true;
		}
	}

	if (gameState==Mode &&mode_mode==true){
		RedButton->tick();
		BlueButton->tick();
		YellowButton->tick();
		GreenButton->tick();
		}
	
	//This will take care of turning on the lights after a few
	//ticks so that they dont stay turned on forever or too long
	if(lightDisplayDuration > 0){
		lightDisplayDuration--;
		if(lightDisplayDuration <= 0){
			lightOff(RED);
			lightOff(BLUE);
			lightOff(YELLOW);
			lightOff(GREEN);
		}
	}
	//High scores max between previous score and new score
	if (highscore>maxhighscore){
		maxhighscore = highscore;
	}
	if(max(highscoreplayer1,highscoreplayer2)>ultimatescore){
		ultimatescore = max(highscoreplayer1, highscoreplayer2);
	}
}
//--------------------------------------------------------------
void ofApp::draw(){
	//Create the background
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));
	//Draw the buttons
	ofSetColor(255,0,0);
	RedButton->render();
	BlueButton->render();
	YellowButton->render();
	GreenButton->render();
	if(gameState==StartUp){
	ModeButton->render();
	MultiplayerButton->render();
	
}
	//High scores indicators
	if (gameState!=StartUp || gameState!=GameOver || gameState==Mode){
	if (gameState!=StartUp && multiplayer_mode==true){
		ofDrawBitmapString("Mario's score: "+to_string(highscoreplayer2), 20, 60);
		ofDrawBitmapString("Luigi's score: "+to_string(highscoreplayer1), 890, 60);
		ofDrawBitmapString("High score: "+to_string(ultimatescore), 480, 10);
		}
	if (gameState!=StartUp && gameState!=Mode && multiplayer_mode == false){
		ofDrawBitmapString("Your score is: "+to_string(highscore), 60, 10);
		ofDrawBitmapString("High score: "+to_string(maxhighscore), 700, 10);
	}

	//This whole if statement will take care of showing
	//the sequence to the user before accepting any input
	if(gameState == PlayingSequence){
		if (multiplayer_mode == false){
		showingSequenceDuration++;
		if(showingSequenceDuration == 120){
			color = Sequence[userIndex];
			lightOn(color);
			lightDisplayDuration = 30;
		}
		if(showingSequenceDuration == 140){
			lightOff(color);
			showingSequenceDuration = 60;
			userIndex++;
		}
		if(userIndex == sequenceLimit){
			lightOff(color);
			userIndex = 0;
			player1 = false;
			player2 = true;
			gameState = PlayerInput;
		}
	}
		else if(gameState == PlayingSequence && multiplayer_mode == true && player1 == true){
		showingSequenceDuration++;
		if(showingSequenceDuration == 120){
			color = Sequence[userIndex];
			lightOn(color);
			lightDisplayDuration = 30;
		}
		if(showingSequenceDuration == 140){
			lightOff(color);
			showingSequenceDuration = 60;
			userIndex++;
		}
		if(userIndex == sequenceLimit){
			lightOff(color);
			userIndex = 0;
			player1 = true;
			gameState = PlayerInput;
		}
	}
	else if(gameState == PlayingSequence && multiplayer_mode == true && player1 == false){
		showingSequenceDuration++;
		if(showingSequenceDuration == 120){
			color = player2Sequence[userIndex];
			lightOn(color);
			lightDisplayDuration = 30;
		}
		if(showingSequenceDuration == 140){
			lightOff(color);
			showingSequenceDuration = 60;
			userIndex++;
		}
		if(userIndex == sequenceLimit){
			lightOff(color);
			userIndex = 0;
			player1 = false;
			gameState = PlayerInput;
		}
	}
}

	if(gameState == Mode && replay == true && mode_mode == true){
		showingSequenceDuration++;
			if(showingSequenceDuration == 120){
			color = Sequence[userIndex];
			lightOn(color);
			lightDisplayDuration = 30;
		}
			if(showingSequenceDuration == 140){
			lightOff(color);
			showingSequenceDuration = 60;
			userIndex++;
		}
		if(userIndex == sequenceLimit){
			lightOff(color);
			userIndex = 0;
			replay = false;
		}
	}

	//Recording and replay indicators
	if(recording){
		record.draw(ofGetWindowWidth()/2-340,ofGetWindowHeight()/2-370,90,160);
		ofDrawBitmapString("Recording",200,15);
	}
	if(gameState == Mode && replay && mode_mode==true){
		replaying.draw(ofGetWindowWidth()/2-340,ofGetWindowHeight()/2-370,90,170);
		ofDrawBitmapString("Playing Recording",200,15);
	}

	//Text game Multiplayer indicators
	if(gameState == Multiplayer){
		ofDrawBitmapString("Multiplayer Mode",90,10);
		
	}
	if(gameState == PlayingSequencePlayer1){
		ofDrawBitmapString("Multiplayer Mode",90,10);
		
	}
	
	//StartUP (You dont need to pay much attention to this)
	//(This is only to create a animation effect at the start of the game)
	if(gameState == StartUp){
		showingSequenceDuration++;
		startUpSequence(showingSequenceDuration);
	}

	//If the statements to see see if the buttons should be lit up
	//If they are then we will draw the glowing images on top of them
	if (RedButton->GetIsLightUp()) {
		redLight.draw(ofGetWindowWidth()/2-60, ofGetWindowHeight()/2-305, 376, 329);
	}
	if (BlueButton->GetIsLightUp()) {
		blueLight.draw(ofGetWindowWidth()/2+5, ofGetWindowHeight()/2-60, 309, 376);
	} 
	if (YellowButton->GetIsLightUp()) {
		yellowLight.draw(ofGetWindowWidth()/2-300, ofGetWindowHeight()/2+5, 374, 318);
	} 
	if (GreenButton->GetIsLightUp()) {
		greenLight.draw(ofGetWindowWidth()/2-307, ofGetWindowHeight()/2-295, 315, 356);
	}

	//Part of the Start Up
	if(logoIsReady){
		logo.draw(ofGetWindowWidth()/2-160,ofGetWindowHeight()/2-150,330,330);
	}

	//Game indicators
	if ((gameState != StartUp && gameState!= GameOver)&&(multiplayer_mode == false && mode_mode == false)){
		classicIndicator.draw(ofGetWindowWidth()/2-160,ofGetWindowHeight()/2-470,330,330);
		backspace.draw(ofGetWindowWidth()/2+250,ofGetWindowHeight()/2+250,100,50);
	}
	if(gameState == Mode && mode_mode == true){
		modeIndicator.draw(ofGetWindowWidth()/2-160,ofGetWindowHeight()/2-470,330,330);
		backspace.draw(ofGetWindowWidth()/2+250,ofGetWindowHeight()/2+250,100,50);
	}

	//player 1 and 2 as Mario and Luigi
	if(multiplayer_mode){
		multiplayerIndicator.draw(ofGetWindowWidth()/2-160,ofGetWindowHeight()/2-470,330,330);
		backspace.draw(ofGetWindowWidth()/2+250,ofGetWindowHeight()/2+250,100,50);
		if(!player1){
			ofDrawBitmapString("Mario's Turn", 20, 20);
		
		}else{
			ofDrawBitmapString("Luigi's Turn", 890, 20);
		
		}
	}
	//Draw the game over screen
	if(gameState == GameOver){
		gameOverScreen.draw(0,0,1024,768);
	}
	//This will draw the "Press to Start" screen at the beginning
	else if(!idle && gameState == StartUp){
		startUpScreen.draw(20,0,1024,768);
	}
 
}
}
//--------------------------------------------------------------
void ofApp::GameReset(){
	//This function will reset the game to its initial state
	lightOff(RED);
	lightOff(BLUE);
	lightOff(YELLOW);
	lightOff(GREEN);
	Sequence.clear();
	player1Sequence.clear();
	player2Sequence.clear();
	player1Index = 0;
	player2Index = 0;
	generateSequence();
	generateSequenceplayer2();
	userIndex = 0;
	gameState = PlayingSequence;
	showingSequenceDuration = 0;
	multiplayer_mode = false;
	available = true;
	highscoreplayer1=0;
	highscoreplayer2=0;
	highscore=0;
	mode_mode=false;
	available_mode=true;
}
	
	
	
void ofApp::GameResetMultiplayer(){
	//This function will reset the game to its initial state in Multiplayer
	lightOff(RED);
	lightOff(BLUE);
	lightOff(YELLOW);
	lightOff(GREEN);
	player1Sequence.clear();
	player2Sequence.clear();
	generateSequenceplayer1();
	player1Index = 0;
	player2Index = 0;
	gameState = Multiplayer;
	showingSequenceDuration = 0;
	multiplayer_mode = true;
	available = true;
	highscoreplayer1=0;
	highscoreplayer2=0;
	highscore=0;
}
//--------------------------------------------------------------
void ofApp::generateSequence(){
	//This function will generate a random number between 0 and 3
	int random = ofRandom(4);
	if(multiplayer_mode ==false){
		highscore=highscore+1;
	}
	//Depending on the random number, we will add a button to the sequence
	if(random == 0)
	{
		Sequence.push_back(RED);
	}
	else if(random == 1)
	{
		Sequence.push_back(BLUE);
	}
	else if(random == 2)
	{
		Sequence.push_back(GREEN);
	}
	else if(random == 3)
	{
		Sequence.push_back(YELLOW);
	}
	
	
	//We will adjust the sequence limit to the new size of the Sequence list
	sequenceLimit = Sequence.size();
}
void ofApp::generateSequenceplayer1(){
	//This function will generate a random number between 0 and 3
	int random = ofRandom(4);
	
	//Depending on the random number, we will add a button to the sequence
	if(random == 0){
		player1Sequence.push_back(RED);
	}
	else if(random == 1){
		player1Sequence.push_back(BLUE);
	}
	else if(random == 2){
		player1Sequence.push_back(GREEN);
	}
	else if(random == 3){
		player1Sequence.push_back(YELLOW);
	}
	
	//We will adjust the sequence limit to the new size of the Sequence list
	sequenceLimitplayer1 = player1Sequence.size();
}
void ofApp::generateSequenceplayer2(){
int random2 = ofRandom(4);
if(random2 ==0){
	player2Sequence.push_back(RED);
}
else if(random2 ==1){
	player2Sequence.push_back(BLUE);
}
else if(random2 == 2){
	player2Sequence.push_back(YELLOW);
}
else if(random2 == 3){
	player2Sequence.push_back(GREEN);
}
sequenceLimit = player2Sequence.size();
}
//--------------------------------------------------------------
bool ofApp::checkUserInput(Buttons input){
	//This function will varify if the user input matches the color
	//of the sequence at the current index
	if(Sequence[userIndex] == input){
		return true;
	}
	else{
		return false;
	}
}
bool ofApp::checkPlayer1Input(Buttons input){
	//This function will varify if the user input matches the color
	//of the sequence at the current index
	if(player1Sequence[player1Index] == input){
		return true;
	}
	else{
		return false;
	}
}
bool ofApp::checkPlayer2Input(Buttons input){
	//This function will varify if the user input matches the color
	//of the sequence at the current index
	if(player2Sequence[userIndex] == input){
		return true;
	}
	else{
		return false;
	}
}
//------------------------------------------------------------
void ofApp::lightOn(Buttons color){
	//This function will take care of toggling the "isLightUp" variable to
	//true for the button that matches the color, and also play the button sound
	if(color == RED){
		RedButton->toggleLightOn();
		RedButton->playSound();
	}
	else if(color == BLUE){
		BlueButton->toggleLightOn();
		BlueButton->playSound();
	}
	else if(color == YELLOW){
		YellowButton->toggleLightOn();
        YellowButton->playSound();
	}
	else if(color == GREEN){
		GreenButton->toggleLightOn();
		GreenButton->playSound();
	}
}
//--------------------------------------------------------------
void ofApp::lightOff(Buttons color){
	//This function will take care of toggling the "isLightUp" variable to false
	if(color == RED){
		RedButton->toggleLightOff();
	}
	else if(color == BLUE){
		BlueButton->toggleLightOff();
	}
	else if(color == YELLOW){
		YellowButton->toggleLightOff();
	}
	else if(color == GREEN){
		GreenButton->toggleLightOff();
	}
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
		//As long as we're not in Idle OR the gameState is GameOver;
	//AND we press the SPACEBAR, we will reset the game
	if((!idle || gameState == GameOver) && tolower(key) == ' '){
		GameReset();
		
	}
	
	if(key == 8){
		multiplayer_mode=false;
		mode_mode=false;
		gameState = StartUp;
	}
	if (gameState == Mode && mode_mode==true){
		if(!recording && tolower(key)=='r'){
			Sequence.clear();
			recording = true;
			userIndex=0;
			showingSequenceDuration=0;
		}
		else if(tolower(key)=='r'){
			recording = false;
		}
		else if(tolower(key)=='p'){
			replay = true;
		}
	}	
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int mouseX, int mouseY ){
	
}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	//If we're not in Idle and the gameState equals PlayerInput,
	//We will pay attention to the mousePresses from the user
	if(!idle && (gameState == PlayerInput || gameState == Mode || gameState == Multiplayer)){
		//We mark the pressed button as "pressed"
		
		lightOff(RED);
		lightOff(BLUE);
		lightOff(YELLOW);
		lightOff(GREEN);
		RedButton->setPressed(x,y);
		BlueButton->setPressed(x,y);
		YellowButton->setPressed(x,y);
		GreenButton->setPressed(x,y);
		//We check which button got pressed
		if(RedButton->wasPressed()){
			color = RED;
		}
		else if(BlueButton->wasPressed()){
			color = BLUE;
		}
		else if(YellowButton->wasPressed()){
			color = YELLOW;
		}
		else if(GreenButton->wasPressed()){
			color = GREEN;
		}
		//Light up the pressed button for a few ticks
		lightOn(color);
		lightDisplayDuration = 15;
		if (gameState == Mode){
			// We check which button got pressed
			if (RedButton->wasPressed()){
				Sequence.push_back(RED);
			}
			else if (BlueButton->wasPressed()){
				Sequence.push_back(BLUE);
			}
			else if (YellowButton->wasPressed()){
				Sequence.push_back(YELLOW);
			}
			else if (GreenButton->wasPressed()){
				Sequence.push_back(GREEN);
			}
			sequenceLimit = Sequence.size();
		}
		if(gameState == PlayerInput){
			//If the user input is correct, we can continue checking
			if(multiplayer_mode == false){
			if(checkUserInput(color)){
				userIndex++;
			}
			
			//If not, then we will terminate the game by 
			//putting it in the GameOver state.
			else{
				gameState = GameOver;
			}
		}
		if(multiplayer_mode == true && player1){
			if(checkUserInput(color)){
				userIndex++;
			}
			
			//If not, then we will terminate the game by 
			//putting it in the GameOver state.
			else{
				gameState = GameOver;
			}
		}
		if(multiplayer_mode == true && player1 == false){
			if(checkPlayer2Input(color)){
				userIndex++;
			}
			
			//If not, then we will terminate the game by 
			//putting it in the GameOver state.
			else{
				gameState = GameOver;
			}
		}
			
	}	
	    
		
	}	
				 
//Where the mode's bottons are pressed 
ModeButton->setPressed(x, y);
if (ModeButton->wasPressed()and available_mode){
	mode_mode=true;
	gameState=Mode;
	available_mode = false;
}
MultiplayerButton->setPressed(x, y);
	if (MultiplayerButton->wasPressed() and available){
		// gameState=Multiplayer;
		
		player1 = true;
		player2 = false;
		multiplayer_mode = true;
		gameState = PlayerInput;
		available =  false;
	}		
	
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
//--------------------------------------------------------------
//You may honestly ignore this function, shouldnt be something you need
//to change or anything. It's only for the start up animation. But ofc,
//If you wish to make something out of it or make it better, be my guest.
void ofApp::startUpSequence(int count){
	
	if(count < 200){
		GreenButton->toggleLightOn();
	}
	else if(count >= 200 && count < 260){
		GreenButton->toggleLightOff();
		RedButton->toggleLightOn();
	}
	else if(count >= 260 && count < 320){
		RedButton->toggleLightOff();
		BlueButton->toggleLightOn();
	}
	else if(count >= 320 && count < 380){
		BlueButton->toggleLightOff();
		YellowButton->toggleLightOn();
	}
	else if(count >= 380 && count < 440){
		YellowButton->toggleLightOff();
	}
	else if(count >= 440 && count < 500){
		GreenButton->toggleLightOn();
		RedButton->toggleLightOn();
		YellowButton->toggleLightOn();
		BlueButton->toggleLightOn();
	}
	else if(count >= 500 && count < 560){
		GreenButton->toggleLightOff();
		RedButton->toggleLightOff();
		YellowButton->toggleLightOff();
		BlueButton->toggleLightOff();
	}
	else if(count >= 560){
		showingSequenceDuration = 400;
	}
	//Logo Drawing
	if(logoIsReady && logoCounter > 0){
		logoCounter--;
		ofSetColor(256,256,256,logoCounter);
		logoLight.draw(ofGetWindowWidth()/2-160,ofGetWindowHeight()/2-150,330,330);
		ofSetColor(256,256,256);
	}
	if((count > 375) && !logoIsReady){
		logoCounter++;
		ofSetColor(256,256,256,logoCounter);
		logoLight.draw(ofGetWindowWidth()/2-160,ofGetWindowHeight()/2-150,330,330);
		ofSetColor(256,256,256,logoCounter);
		logo.draw(ofGetWindowWidth()/2-160,ofGetWindowHeight()/2-150,330,330);
		ofSetColor(256,256,256);
	}
	if(logoCounter >=255){
		logoIsReady = true;
		idle = false;
	}
}