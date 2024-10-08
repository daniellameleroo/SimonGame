#pragma once

#include "ofMain.h"
#include "Button.h"

class ofApp : public ofBaseApp{

	//enums to represent game states
	enum GameState{
		StartUp,
		PlayingSequence,
		PlayingSequencePlayer1,
		PlayingSequencePlayer2,
		PlayerInput,
		GameOver,
		Mode,
		Multiplayer,
		player1Input,
		player2Input,
		


	};



	public:
		//Some OpenFrameworks must-have functions
		void setup();
		void update();
		void draw();
		void handlePlayerInput();
		void handleMultiplayer();
		void handleSequence();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//Functions for our game
		void lightOn(Buttons color);
		void lightOff(Buttons color);
		void generateSequence();
		void generateSequenceplayer1();
		void generateSequenceplayer2();
		bool checkUserInput(Buttons c);
		bool checkPlayer1Input(Buttons input);
		bool checkPlayer2Input(Buttons input);
		void GameReset();
		void GameResetMultiplayer();
		void startUpSequence(int count);
		
	private:
		//This vector will basically act as list of button enums
		//for us to be able to store the sequences
		vector<Buttons> Sequence;
		

		//Let's declare the buttons we will use
		Button *RedButton;
		Button *BlueButton;
		Button *YellowButton;
		Button *GreenButton;
		Button *ModeButton;
		Button *MultiplayerButton;

		//These will be mere images which we will draw on top
		//of the actual buttons to give the mere illusion
		//that the original buttons are lighting up
		ofImage redLight;
		ofImage blueLight;
		ofImage yellowLight;
		ofImage greenLight;
		ofImage logo;
		ofImage logoLight;
		ofImage startUpScreen;
		ofImage gameOverScreen;
		ofImage multiplayerIndicator;
		ofImage modeIndicator;
		ofImage classicIndicator;
		ofImage record;
		ofImage replaying;
		ofImage replaymode;
		ofImage mainMenu;
		ofImage backspace;
		

		//Few variables we'll need
        ofSoundPlayer backgroundMusic;
		ofSoundPlayer multiplayerStartupmusic;
		int sequenceLimit = 1;
		int sequenceLimitplayer1 = 1;
		int sequenceLimitplayer2 = 1;
		int userIndex = 1;
		int player1Index = 1;
		int player2Index = 1;
		int showingSequenceDuration = 0;
		int lightDisplayDuration = -1;
		int resizedWindow=1;
		Buttons color;
		GameState gameState;
		bool logoIsReady = false;
		int logoCounter = 0;
		bool idle = true;
		bool recording = false;
		bool replay = false;
		bool mode_mode = false;
		vector<Buttons> player1Sequence;
		vector<Buttons> player2Sequence;
		bool player1 = true;
		bool player2 = false;
		bool multiplayer_mode = false;
		bool currentPlayer;
		bool available = true;
		bool available_mode = true;
		int highscoreplayer1 = -1;
		int highscoreplayer2 = 0;
		int highscore = -1;
		int maxhighscore = 0;
		int ultimatescore = 0;
		
};