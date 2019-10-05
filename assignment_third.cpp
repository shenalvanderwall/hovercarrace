/*
Name: Shenal Vanderwall
University: UClan
G Number: G20816408
Module: CO1301 Games Concepts
Description: A hover car game using TL-Engine
*/

// assignment_third.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <vector> //for handle vectors
#include <string> //for string library
#include <fstream> //for files
#include <iostream>
#include <sstream> 
#include <cmath>
#include <iomanip>
#include <ctime>


using namespace tle;
using namespace std;


//game speed
float kGameSpeed = 0.2f;
float steering = 0.0f;// Variable holding the current steering angle
const float kSteerSpeed = 0.3f; // Steering speed of the 
const float kSteerLimit = 180.0f; // Limit on the angle of steering
//game speed


//car life
float carLife = 100; //give 100 car life
//car life

//game states
int gameStates = 0; //( 0=  game no started, 1 = starting, 2 = ready to move)
string gameStateText = "Hit Space to Start"; //for text base
int gameStateTextInts; // for intiger base
bool visibleCounter = false;
//game states

//game state ------
bool gameStateZero = false;
bool gameStateOne = false;
bool gameStateTwo = false;
bool gameStateThree = false;
bool gameStateFour = false;
//game state ------

//game state ------ 1 state
bool playerCanMoveCar = false;
//game state ------ 1 state

//game statistics
float totalGameFinishDistance = 940;
float totalGameReachDistance = 0;
int totalCollidedTimes = 0;
float totalCarSpeedkmh = 0;
//game statistics

//game controls
bool gameLost = false;
bool gameWon = false;
//game controls

//find which automated car reahhes the endpoint first
float getCarOneReached;
float getCarTwoReached;
float getCarThreeReached;

bool carOneReached = false;
bool carTwoReached = false;
bool carThreeReached = false;

bool carOneIdGenerated = false;
bool carTwoIdGenerated = false;
bool carThreeIdGenerated = false;

int carOneID = 0;
int carTwoID = 0;
int carThreeID = 0;
//find which automated car reahhes the endpoint first

//functions
void drawFontMiddle(IFont* myFont, string textToDisplay, int textInt); // middle font big on backdrop
void gameNotStarted(IFont* myFont, I3DEngine* myEngine); // game state 0 - not started yet

int collisionDetecton(I3DEngine* myEngine, IModel* hoverCar,
	float carX, float carY, float carZ,
	float objectX, float objectY, float objectZ,
	char objectType, string obDesc); //collision detection
float calcCarLife(); // calculate the car life
float moveCarsAutomated(I3DEngine* myEngine, IModel* car, int module); // automated car movements
//functions

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "C:\\ProgramData\\TL-Engine\\Media" );
	myEngine->AddMediaFolder("./media");

	/**** Set up your scene here ****/
	ICamera* myCamera;
	myCamera = myEngine->CreateCamera(kManual, 0, 20, -80);
	//myCamera->RotateLocalY(-40);

	IMesh* groundMesh;
	IModel* ground;
	groundMesh = myEngine->LoadMesh("ground.x");
	ground = groundMesh->CreateModel();

	IMesh* checkpointMesh;
	IModel* checkpointOne;
	IModel* checkpointTwo; 
	IModel* checkPointThree;
	checkpointMesh = myEngine->LoadMesh("Checkpoint.x");

	checkpointOne = checkpointMesh->CreateModel(0, 0, 0);
	checkpointTwo = checkpointMesh->CreateModel(10, 0, 120);
	checkPointThree = checkpointMesh->CreateModel(25, 0, 56);

	checkpointTwo->RotateLocalY(90);


	IMesh* isleMesh;
	IModel* IsleOne;
	IModel* IsleTwo;

	isleMesh = myEngine->LoadMesh("IsleTee.x");

	

	//isles cordinates
	float isleXCordinates[2] = { -10 , 10 };
	float isleYCordinates[2] = { 0, 0 };

	int isleCordinateStart = 40;
	for (int i = 0; i <= 4; i++) {
		IsleOne = isleMesh->CreateModel(isleXCordinates[0], isleYCordinates[0], isleCordinateStart);
		IsleTwo = isleMesh->CreateModel(isleXCordinates[1], isleYCordinates[1], isleCordinateStart);

		isleCordinateStart = isleCordinateStart + 16;
		
	}
	
	//isles cordinates

	//second isles cordinates
	float isleXCordinatesSec[2] = { -30 , 30 };
	float isleYCordinatesSec[2] = { 0, 0 };

	int isleCordinateStartSec = 120;
	for (int i = 0; i <= 50; i++) {
		IsleOne = isleMesh->CreateModel(isleXCordinatesSec[0], isleYCordinatesSec[0], isleCordinateStartSec);
		IsleTwo = isleMesh->CreateModel(isleXCordinatesSec[1], isleYCordinatesSec[1], isleCordinateStartSec);

		isleCordinateStartSec = isleCordinateStartSec + 16;
	}
	//second isles cordinates
	

	IMesh* wallMesh;
	IModel* wallOne;
	IModel* wallTwo;
	IModel* wallThree;
	IModel* wallFour;

	wallMesh = myEngine->LoadMesh("Wall.x");

	//wall coordinates
	float wallXCordinates[2] = { -10 , 10 };
	float wallYCordinates[2] = { 0, 0 };



	//from start o straight
	int wallCordinateStart = 48;
	for (int i = 0; i <= 3; i++) {
		wallOne = wallMesh->CreateModel(wallXCordinates[0], wallYCordinates[0], wallCordinateStart);
		wallTwo = wallMesh->CreateModel(wallXCordinates[1], wallYCordinates[1], wallCordinateStart);

		wallCordinateStart = wallCordinateStart + 16;
		
	}
	//from start o straight
	
	//second walls set
	float wallXCordinatesSec[2] = { -30 , 30 };
	float wallYCordinatesSec[2] = { 0, 0 };

	int wallCordinateStartSec = 128;
	for (int i = 0; i <= 49; i++) {
		wallThree = wallMesh->CreateModel(wallXCordinatesSec[0], wallYCordinatesSec[0], wallCordinateStartSec);
		wallFour = wallMesh->CreateModel(wallXCordinatesSec[1], wallYCordinatesSec[1], wallCordinateStartSec);

		wallCordinateStartSec = wallCordinateStartSec + 16;
		
	}
	//second walls set

	//wall coordinates

	



	
	//hover car
	IMesh* hoverCarMesh;
	IModel* hoverCar;
	IModel* hoverCarTwo;
	IModel* hoverCarThree;
	IModel* hoverCarFour;
	hoverCarMesh = myEngine->LoadMesh("race2.x");
	hoverCar = hoverCarMesh->CreateModel(0, 0, -30);
	//hover car


	//three more automated hover cars
	hoverCarTwo = hoverCarMesh->CreateModel(-15, 0, -40);
	hoverCarThree = hoverCarMesh->CreateModel(8, 0, -20);
	hoverCarFour = hoverCarMesh->CreateModel(13, 0, -10);

	hoverCarTwo->SetSkin("sp01.jpg");
	hoverCarThree->SetSkin("Fire.jpg");
	hoverCarFour->SetSkin("td_interstellar.jpg");

	//three more automated hover cars


	//water tanks
	IMesh* waterTankMeshSmall1;
	IModel* waterTankSmall1;
	IModel* waterTankSmall2;
	waterTankMeshSmall1 = myEngine->LoadMesh("TankSmall1.x");
	waterTankSmall1 = waterTankMeshSmall1->CreateModel(-30, 0, 0);
	waterTankSmall1 = waterTankMeshSmall1->CreateModel(-30, 0, 20);
	waterTankSmall2 = waterTankMeshSmall1->CreateModel(30, 0, 0);

	//more water tanks
	 //left water tanks small
	float startingWTCordX = 120;
	for (int i = 0; i <= 50; i++) {
		waterTankSmall1 = waterTankMeshSmall1->CreateModel(-40, 0, startingWTCordX);
		startingWTCordX = startingWTCordX + 16;
	}
	//left water tanks small

	//right water tanks
	float startingWTCordXRight = 120;
	for (int i = 0; i <= 50; i++) {
		waterTankSmall2 = waterTankMeshSmall1->CreateModel(40, 0, startingWTCordXRight);
		startingWTCordXRight = startingWTCordXRight + 16;
	}
	//right water tanks

	//more water tanks

	IMesh* waterTankBigMesh;
	IModel* waterTankBig;
	waterTankBigMesh = myEngine->LoadMesh("TankLarge1.x");
	waterTankBig = waterTankBigMesh->CreateModel(-30, 0, 10);

	IMesh* waterTankBiggerMesh;
	IModel* waterTankBigger;
	IModel* waterTankBiggerInTrack;
	waterTankBiggerMesh = myEngine->LoadMesh("TankLarge2.x");
	waterTankBigger = waterTankBiggerMesh->CreateModel(-40, 0, 10);

	waterTankBiggerInTrack = waterTankBiggerMesh->CreateModel(-5, -7, 550);
	waterTankBiggerInTrack->RotateLocalX(20);
	waterTankBiggerInTrack->RotateLocalY(30);
	waterTankBiggerInTrack->RotateY(20);

	//water tanks
	
	//sky box
	IMesh* skyBoxMesh;
	IModel* skyBox;
	skyBoxMesh = myEngine->LoadMesh("Skybox 07.x");
	skyBox = skyBoxMesh->CreateModel(0, -960, 0);
	//sky box

	//backdrop 
	ISprite* backdrop = myEngine->CreateSprite("ui_backdrop.jpg", 250, 660);
	//backdrop

	
	//load font
	IFont* myFont = myEngine->LoadFont("Comic Sans MS", 36);
	IFont* statisticFont = myEngine->LoadFont("Times New Roman", 15);
	IFont* boostTextFont = myEngine->LoadFont("Times New Roman", 25);
	IFont* gameLostFont = myEngine->LoadFont("Times New Roman", 80);
	IFont* gameInstrucFont = myEngine->LoadFont("Comic Sans MS", 35);
	IFont* resetFont = myEngine->LoadFont("Times New Roman", 35);

	
	//load font


	//building
	IMesh* buildingMesh;
	IModel* building;
	buildingMesh = myEngine->LoadMesh("Lamp.x");
	building = buildingMesh->CreateModel(55, -0, 0);
	//building

	//Interstellar
	IMesh* InterstellarMesh;
	IModel* Interstellar;
	InterstellarMesh = myEngine->LoadMesh("Interstellar.x");
	Interstellar = InterstellarMesh->CreateModel(110, -0, 340);
	//Interstellar


	//add barriers
	IMesh* barrierMEsh;
	IModel* barrierOne;
	IModel* barrierTwo;
	IModel* barrierThree;
	IModel* barrierFour;
	IModel* barrierFive;
	IModel* barrierSix;
	barrierMEsh = myEngine->LoadMesh("Cross.x");

	barrierOne = barrierMEsh->CreateModel(5, 0, 170);
	barrierTwo = barrierMEsh->CreateModel(-5, 0, 210);

	barrierThree = barrierMEsh->CreateModel(3, 0, 340);
	barrierFour = barrierMEsh->CreateModel(-3, 0, 450);

	barrierFive = barrierMEsh->CreateModel(4, 0, 590);
	barrierSix = barrierMEsh->CreateModel(-2, 0, 710);

	//add barriers


	//implemented checkpoints
	IMesh* imCheckPointsMesh;
	IModel* imCheckPointsOne;
	IModel* imCheckPointsTwo;
	IModel* imCheckPointsThree;
	barrierMEsh = myEngine->LoadMesh("Checkpoint.x");
	imCheckPointsOne = barrierMEsh->CreateModel(0, 0, 170);
	imCheckPointsTwo = barrierMEsh->CreateModel(0, 0, 400);
	imCheckPointsThree = barrierMEsh->CreateModel(0, 0, 720);

	imCheckPointsOne->Scale(2.4);
	imCheckPointsTwo->Scale(2.4);
	imCheckPointsThree->Scale(2.4);

	//implemented checkpoints


	//final end point
	IMesh* finalEndPointMesh;
	IModel* finalEndPoint;
	finalEndPointMesh = myEngine->LoadMesh("wall.x");
	finalEndPoint = finalEndPointMesh->CreateModel(0, -3, 930);

	finalEndPoint->RotateLocalY(90);

	finalEndPoint->ScaleZ(9);
	//final end point

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		
	
		/**** Update your scene each frame here ****/

		//time counter
		if (visibleCounter) {
			float currentTime = clock() / 1000;
			float countDown = 5 - currentTime;
			stringstream outText;
			if (countDown > 0) {
				outText << "Time: " << countDown;
			}
			else {
				outText << "Go !";
				playerCanMoveCar = true; // enable car movements

				

			}
			myFont->Draw(outText.str(),  280, 680, kRed);
			outText.str("");

			if (countDown < 0) {
				countDown = 0;
				visibleCounter = false;

			}
		}
		//time counter


		//display Total game time
		float currentTimeStarted = clock() / 1000;
		float gameTotalTime = 60 - currentTimeStarted;
		stringstream gameTotalTimeOut;
		gameTotalTimeOut << "Game End In: " << gameTotalTime;
		myFont->Draw(gameTotalTimeOut.str(), 1000, 20, kWhite);
		gameTotalTimeOut.str("");
		//display Total game time

		//display total life of car
		stringstream carLifeOut;
		carLifeOut << "CAR LIFE: " << carLife;
		myFont->Draw(carLifeOut.str(), 50, 20, kWhite);
		carLifeOut.str("");
		//display total life of car


		//game instruction note
		stringstream gameInstructionNote;
		stringstream gameInstructionNote2;
		gameInstructionNote << "Reach the end point first before time over keeping";
		gameInstructionNote2 << "the health less than 95 to win";
		gameInstrucFont->Draw(gameInstructionNote.str(), 300, 20, kBlue);
		gameInstrucFont->Draw(gameInstructionNote2.str(), 460, 50, kBlue);
		//game instruction note


		//close the game
		if (myEngine->KeyHit(Key_Escape))
		{
			myEngine->Stop();
		}
		//close the game



		//camera movement
		
		//left
		if (myEngine->KeyHeld(Key_Left)) {
			myCamera->MoveX(-kGameSpeed);
		}
		//left

		//right
		if (myEngine->KeyHeld(Key_Right)) {
			myCamera->MoveX(kGameSpeed);
		}
		//right

		//forward
		if (myEngine->KeyHeld(Key_Up)) {
			myCamera->MoveZ(kGameSpeed);
		}
		//forward

		//backwards
		if (myEngine->KeyHeld(Key_Down)) {
			myCamera->MoveZ(-kGameSpeed);
		}
		//backwards

		

		int mouseMoveX = myEngine->GetMouseMovementX();
		myCamera->RotateY(mouseMoveX * kGameSpeed);

		//reset camera
		if (myEngine->KeyHeld(Key_1)) {
			myCamera->SetLocalPosition(0, 20, -80);
			myCamera->ResetOrientation();
		}
		//reset camera

		//camera movement


		
		//if the game is not lost
		if (gameLost == false) {
			//hover car movement
			if (playerCanMoveCar == true) {



				//move automated cars

				int randGenerate = 3 + (std::rand() % (5 - 3 + 1));
				int randGenerate2 = 3 + (std::rand() % (5 - 3 + 1));
				int randGenerate3 = 3 + (std::rand() % (5- 3 + 1));
				

				if (carOneIdGenerated == false) {
					carOneID = randGenerate;
					carOneIdGenerated = true;
				} 
				if (carTwoIdGenerated == false) {
					carTwoID = randGenerate2;
					carTwoIdGenerated = true;
				}
				if (carThreeIdGenerated == false) {
					carThreeID = randGenerate3;
					carThreeIdGenerated = true;
				}

				getCarOneReached = moveCarsAutomated(myEngine, hoverCarTwo, carOneID); //car second

				if (getCarOneReached >= 270) {
					carOneReached = true;
				}
				system("cls");
				cout << "auto car one: z : " << getCarOneReached << endl;

				getCarTwoReached = moveCarsAutomated(myEngine, hoverCarThree, carTwoID); //car third

				if (getCarOneReached >= 270) {
					carTwoReached = true;
				}

				getCarThreeReached = moveCarsAutomated(myEngine, hoverCarFour, carThreeID); //car fourth

				if (getCarOneReached >= 270) {
					carThreeReached = true;
				}

				//move automated cars

				//move forward
				if (myEngine->KeyHeld(Key_W)) {

					hoverCar->MoveLocalZ(kGameSpeed);
					hoverCar->MoveX(steering * 0.01f);

					myCamera->MoveLocalZ(kGameSpeed * 0.9);
					myCamera->RotateLocalY(steering * 0.01f);

				}
				//move forward

				//move backwards
				if (myEngine->KeyHeld(Key_S)) {
					hoverCar->MoveZ(-kGameSpeed / 2);
					hoverCar->MoveX(-steering * 0.01f);
					myCamera->MoveLocalZ(-kGameSpeed);
				}
				//move backwards

				//clockwise
				if (myEngine->KeyHeld(Key_D)) {
					if (steering <= kSteerLimit)
					{
						hoverCar->RotateY(kSteerSpeed);
						steering += kSteerSpeed;
					}
				}
				//clockwise

				//anti-clockwise
				if (myEngine->KeyHeld(Key_A)) {
					if (steering >= -kSteerLimit)
					{
						hoverCar->RotateY(-kSteerSpeed);
						steering -= kSteerSpeed;
					}
				}
				//anti-clockwise
			}
			//hover car movement
		}
		//if the game is not lost
		
		//get hover car current cordinates for collision detection
		float getCarCurrentX = hoverCar->GetX();
		float getCarCurrentY = hoverCar->GetY();
		float getCarCurrentZ = hoverCar->GetZ();

		//get hover car current cordinates for collision detection

		//collision detection
		
		//small left wall
		if (getCarCurrentZ <= 115) {
			collisionDetecton(myEngine, hoverCar,
				getCarCurrentX, getCarCurrentY, getCarCurrentZ,
				-5, 0, 0,
				'w', "swl");
		}
		//small left wall

		//small right wall detection
		if (getCarCurrentZ <= 115) {
			collisionDetecton(myEngine, hoverCar,
				getCarCurrentX, getCarCurrentY, getCarCurrentZ,
				3, 0, 0,
				'w', "swr");
		}
		//small right wall detection


		//big left wall detection
		collisionDetecton(myEngine, hoverCar,
			getCarCurrentX, getCarCurrentY, getCarCurrentZ,
			-23, 0, 0,
			'w', "bwl");
		//big left wall detection

		//big right wall detection
		collisionDetecton(myEngine, hoverCar,
			getCarCurrentX, getCarCurrentY, getCarCurrentZ,
			23, 0, 0,
			'w', "bwr");
		//big right wall detection


		//croses detection

		//cross one
		collisionDetecton(myEngine, hoverCar,
			getCarCurrentX, getCarCurrentY, getCarCurrentZ,
			5, 0, 170,
			'c', "s");
		//cross one

		//cross two
		collisionDetecton(myEngine, hoverCar,
			getCarCurrentX, getCarCurrentY, getCarCurrentZ,
			-5, 0, 210,
			'c', "s");
		//cross two

		//cross three
		collisionDetecton(myEngine, hoverCar,
			getCarCurrentX, getCarCurrentY, getCarCurrentZ,
			3, 0, 340,
			'c', "s");
		//cross three

		//cross four
		collisionDetecton(myEngine, hoverCar,
			getCarCurrentX, getCarCurrentY, getCarCurrentZ,
			-3, 0, 450,
			'c', "s");
		//cross four

		//cross five
		collisionDetecton(myEngine, hoverCar,
			getCarCurrentX, getCarCurrentY, getCarCurrentZ,
			4, 0, 590,
			'c', "s");
		//cross five

		//cross six
		collisionDetecton(myEngine, hoverCar,
			getCarCurrentX, getCarCurrentY, getCarCurrentZ,
			-2, 0, 710,
			'c', "s");
		//cross six


		//water tank in the track collision
		collisionDetecton(myEngine, hoverCar,
				getCarCurrentX, getCarCurrentY, getCarCurrentZ,
				-5, -7, 550,
				'c', "s");
		//water tank in the track collision


		//croses detection

		//collision detection


		//------------- enable states

		//state one
		if ((getCarCurrentZ >= 0) && (getCarCurrentZ <= 170)) {
			gameStateZero = false;
			gameStateOne = true;
			gameStateTwo = false;
			gameStateThree = false;
			gameStateFour = false;
			gameStateText = "State One Completed";
			
		}
		//state one

		//state two
		if ((getCarCurrentZ >= 170) && (getCarCurrentZ <= 400)) {
			gameStateZero = false;
			gameStateOne = false;
			gameStateTwo = true;
			gameStateThree = false;
			gameStateFour = false;
			gameStateText = "State Two Completed";
		}
		//state two

		//state three
		if ((getCarCurrentZ >= 400) && (getCarCurrentZ <= 720)) {
			gameStateZero = false;
			gameStateOne = false;
			gameStateTwo = false;
			gameStateThree = true;
			gameStateFour = false;
			gameStateText = "State Three Completed";

		}
		//state three

		//------------- enable states

		
		//------- increase car speed based on game state
		if (gameStateOne) {
			if (carLife >= 30) {
				kGameSpeed = 0.2f;
				totalCarSpeedkmh = (1000 / kGameSpeed) * 0.02;
			}
		} 
		if (gameStateTwo) {
			if (carLife >= 30) {
				kGameSpeed = 0.4f;
				totalCarSpeedkmh = (1000 / kGameSpeed) * 0.02;
			}
		}
		if (gameStateThree) {
			if (carLife >= 30) {
				kGameSpeed = 0.5f;
				totalCarSpeedkmh = (1000 / kGameSpeed) * 0.02;
			}
		}
		if (gameStateFour) {
			if (carLife >= 30) {
				kGameSpeed = 0.7f;
				totalCarSpeedkmh = (1000 / kGameSpeed) * 0.02;
			}
		}
		//------- increase car speed based on game state

		
		//second view camera
		if (myEngine->KeyHeld(Key_2)) {
			myCamera->SetLocalPosition(120, 30, -40);
			myCamera->RotateLocalY(-50);
			myCamera->RotateLocalZ(-0);
			myCamera->RotateLocalX(10);
		}
		//second view camera


		


		//--------------------- Game States ---------------
		
		//game not staretd yet
		if (gameStates == 0) {

			
			if (myEngine->KeyHit(Key_Space)) {
				gameStateText = "";
				visibleCounter = true; //vissible counter
				gameStateZero = true; // make the first state enable

				gameNotStarted(myFont, myEngine); //game counting and first function

			}

			//boost the car by space
			if (myEngine->KeyHeld(Key_Space)) {
				kGameSpeed = kGameSpeed +  0.4f;
				stringstream boostActivated;
				boostActivated << "BOOST ACTIVATED";
				boostTextFont->Draw(boostActivated.str(), 50, 130, kRed);
			}
			//boost the car by space
		}
		//game not staretd yet

		//game started and ready to go
		if (gameStates == 1) {
			
			
		}
		//game started and ready to go

		//--------------------- Game States ---------------


		//display statistics

		//STATISTIC CALCULATION
		totalGameReachDistance = totalGameFinishDistance - getCarCurrentZ;
		//STATISTIC CALCULATION

		stringstream totalGameFinishDistances;
		stringstream totalGameReachDistances;
		stringstream totalCollidedTimess;
		stringstream totalCarSpeedkmhs;

		

		totalGameFinishDistances << "TOTAL DISTANCE: " << totalGameFinishDistance;
		statisticFont->Draw(totalGameFinishDistances.str(), 50, 60, kWhite);

		totalGameReachDistances << "REACHED DISTANCE: " << totalGameReachDistance;
		statisticFont->Draw(totalGameReachDistances.str(), 50, 75, kWhite);

		totalCollidedTimess << "COLLIDED TIMES: " << totalCollidedTimes;
		statisticFont->Draw(totalCollidedTimess.str(), 50, 90, kWhite);

		totalCarSpeedkmhs << "HOVER CAR SPEED: " << totalCarSpeedkmh << "km/h";
		statisticFont->Draw(totalCarSpeedkmhs.str(), 50, 105, kWhite);

		//display statistics

		//------------------ MAKE THE GAME FINAL WINNING

		//game lost due to lost of life
		if ((carLife <= 0) || (gameTotalTime <=0)) {
			carLife = 0; // make the car life 0 means no more health
			gameTotalTime = 0; //make time 0 so the timer no longer continue
			gameLost = true;
			stringstream lostGameText;
			lostGameText << "Game Lost!";
			gameLostFont->Draw(lostGameText.str(), 510, 400, kRed);
		}
		//game lost due to lost of life

		
		//game winning codes
		if ((carLife >= 95) && (gameTotalTime >= 0) && (gameStateThree == true) && (totalGameReachDistance <= 0)) {

			playerCanMoveCar = false;
			gameWon = true;
			stringstream gameWonText;
			stringstream resetGameText;

			//if automated cars are not reached yet
			if ((carOneReached == false) || (carTwoReached == false) || (carThreeReached == false)) {

				
				gameWonText << "Congratulations!";
				gameLostFont->Draw(gameWonText.str(), 480, 350, kBlue);
			}
			else {

				gameWonText << "You did not win!";
				gameLostFont->Draw(gameWonText.str(), 480, 350, kRed);

			}
			//if automated cars are not reached yet

		}
		//game winning codes
		
		//------------------ MAKE THE GAME FINAL WINNING


		

		//draw the first fond
		drawFontMiddle(myFont, gameStateText, gameStateTextInts);
		//draw the first fond

		

	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}

//font for game states
void drawFontMiddle(IFont* myFont, string textToDisplay, int textInt) {

	if (textToDisplay != "") {
		myFont->Draw(textToDisplay, 280, 680);
	}

	if (textInt != 0000) {
		stringstream outText;
		outText << textInt;
		myFont->Draw(outText.str(), 280, 680);
	}
	
}
//font for game states


//game state 0

void gameNotStarted(IFont* myFont, I3DEngine* myEngine) {
	


}
//game state 0

//collision detection
int collisionDetecton(I3DEngine* myEngine, IModel* hoverCar,
	float carX, float carY, float carZ,
	float objectX, float objectY, float objectZ,
	char objectType, string obDesc) {

	int collided = 0;
	float deductingAmtFromLif;
	
	//detect wall collision

	//small left wall detection
	if ((objectType = 'w') && (obDesc == "swl")) {
		if (carX < objectX) {
			collided = 1;
			//carLife = carLife - 1;
			deductingAmtFromLif = calcCarLife();
			carLife = carLife - deductingAmtFromLif;
		}
		else {
			collided = 0;
		}
	}
	//small left wall detection

	//small right wall detection
	if ((objectType = 'w') && (obDesc == "swr")) {
		if (carX > objectX) {
			collided = 1;
			//carLife = carLife - 1;
			deductingAmtFromLif = calcCarLife();
			carLife = carLife - deductingAmtFromLif;
		}
		else {
			collided = 0;
		}
	}
	//small right wall detection


	//big wall left detection
	if ((objectType = 'w') && (obDesc == "bwl")) {
		if (carX <= objectX) {
			collided = 1;
			//carLife = carLife - 1;
			deductingAmtFromLif = calcCarLife();
			carLife = carLife - deductingAmtFromLif;
			
		}
		else {
			collided = 0;
		}
	}
	//big wall left detection

	//big wall right detection
	if ((objectType = 'w') && (obDesc == "bwr")) {
		if (carX > objectX) {
			collided = 1;
			//carLife = carLife - 1;
			deductingAmtFromLif = calcCarLife();
			carLife = carLife - deductingAmtFromLif;
		}
		else {
			collided = 0;
		}
	}
	//big wall right detection

	//detect wall collision

	//detect cross collision
	if ((objectType = 'c') && (obDesc == "s")) {

		

		float obXmaxLeft = objectX - 5.0;
		float obXmaxRight = objectX + 5.0;
		float obZMax = objectZ + 5.0;
		float obZMin = objectZ - 5.0;

		

		if ((obXmaxLeft <= carX) && (obXmaxRight >= carX) && ((obZMin <= carZ) && (obZMax >= carZ))) {
			
			collided = 1;
			//carLife = carLife - 1;
			deductingAmtFromLif = calcCarLife();
			carLife = carLife - deductingAmtFromLif;
			
		}
		else {
			collided = 0;
		}

	}
	//detect cross collision

	//update total collided times
	if (collided == 1) {
		totalCollidedTimes++;
	}
	//update total collided times


	return collided;
}
//collision detection


//reduce car life amount calc
float calcCarLife() {

	float deductingAmtFromLif;
	deductingAmtFromLif = 0.05;

	return deductingAmtFromLif;
}
//reduce car life amount calc

//move automated cars
float moveCarsAutomated(I3DEngine* myEngine, IModel* car, int module) {
	bool carMovable = true;
	float getcarZ = car->GetZ();
	float carSpeeds;

	if (module == 3) {
		carSpeeds = 0.4f;
	}
	if (module == 4) {
		carSpeeds = 0.6f;
	}
	if (module == 5) {
		carSpeeds = 0.2f;
	}

	if (carMovable) {
		car->MoveZ(carSpeeds);

		if (getcarZ >= 700) {
			carMovable = false;
		}
	}

	return getcarZ;

	
}
//move automated cars