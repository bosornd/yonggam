#include <iostream>
#include <bangtal>
#include <ctime>
#include <string>
#include <string.h>
#include <Windows.h>

using namespace bangtal;
using namespace std;


// 키보드 
enum
{
	UP = 84,
	LEFT = 82,
	RIGHT = 83,
	DOWN = 85,
	SPACEBAR = 75
};

// GAME 1 메서드

ObjectPtr paw[10];
int pawcnt;

class P {
public:
	int px;
	int py;
	int pcnt;
	P(int x, int y, int cnt) :px(x), py(y), pcnt(cnt) {}
};

void gaugecheck(int pcnt, ObjectPtr paw[]) {
	if (pcnt == 0) { //재시작 시 초기화를 위해
		for (int i = 0; i < 10; i++) {
			paw[i]->hide(); //모든 게이지 초기화
		}
		pawcnt = 0;
	}
	if (pcnt == 3) {
		paw[0]->show();
		pawcnt = 1;
	}
	else if (pcnt == 6) {
		paw[1]->show();
		pawcnt = 2;
	}
	else if (pcnt == 9) {
		paw[2]->show();
		pawcnt = 3;
	}
	else if (pcnt == 12) {
		paw[3]->show();
		pawcnt = 4;
	}
	else if (pcnt == 15) {
		paw[4]->show();
		pawcnt = 5;
	}
	else if (pcnt == 18) {
		paw[5]->show();
		pawcnt = 6;
	}
	else if (pcnt == 21) {
		paw[6]->show();
		pawcnt = 7;
	}
	else if (pcnt == 24) {
		paw[7]->show();
		pawcnt = 8;
	}
	else if (pcnt == 30) {
		paw[8]->show();
		pawcnt = 9;
	}
	else if (pcnt == 33) {
		paw[9]->show();
		pawcnt = 10;
	}
}




// GAME 2 메서드
void makingImage(string filename[5], string number[10], ObjectPtr comboNum[10], int& num_index, int& index, ScenePtr& game2scene) {
	for (num_index = 0; num_index < 10; num_index++)
	{
		number[num_index] = "images2/" + to_string(num_index + 1) + ".png";
		comboNum[num_index] = Object::create(number[num_index], game2scene, 515, 500, false);
		comboNum[num_index]->setScale(3.0f);
	}
	for (index = 0; index < 5; index++) {
		filename[index] = "images2/ingredient" + to_string(index + 1) + ".png";
	}
}

void ingredientCase(int& num, int& i, int& level, int question[], ObjectPtr q_ingredient[], string filename[], ScenePtr& game2scene, int questX, int questY[], ObjectPtr& q_bread1) {
	for (i = 0; i < level; i++)
	{
		num = rand() % 5;
		switch (num) {
		case 0:
			question[i] = UP;
			q_ingredient[i] = Object::create(filename[0], game2scene, questX, questY[i]);
			q_ingredient[i]->setScale(1.5f);
			break;
		case 1:
			question[i] = RIGHT;
			q_ingredient[i] = Object::create(filename[1], game2scene, questX, questY[i]);
			q_ingredient[i]->setScale(1.5f);
			break;
		case 2:
			question[i] = LEFT;
			q_ingredient[i] = Object::create(filename[2], game2scene, questX, questY[i]);
			q_ingredient[i]->setScale(1.5f);
			break;
		case 3:
			question[i] = DOWN;
			q_ingredient[i] = Object::create(filename[3], game2scene, questX, questY[i]);
			q_ingredient[i]->setScale(1.5f);
			break;
		case 4:
			question[i] = SPACEBAR;
			q_ingredient[i] = Object::create(filename[4], game2scene, questX, questY[i]);
			q_ingredient[i]->setScale(1.5f);
			break;
		}
	}
	q_bread1->locate(game2scene, questX, questY[i]);
	q_bread1->show();
}

void ingredient2case(int& q_index, int& key_flag, int question[], ObjectPtr ingredient[], string filename[], ScenePtr& game2scene, int& answerX, int answerY[]) {
	switch (question[q_index])
	{
	case UP:
		ingredient[q_index] = Object::create(filename[0], game2scene, answerX, answerY[q_index]);
		ingredient[q_index]->setScale(1.5f);
		break;
	case RIGHT:
		ingredient[q_index] = Object::create(filename[1], game2scene, answerX, answerY[q_index]);
		ingredient[q_index]->setScale(1.5f);
		break;
	case LEFT:
		ingredient[q_index] = Object::create(filename[2], game2scene, answerX, answerY[q_index]);
		ingredient[q_index]->setScale(1.5f);
		break;
	case DOWN:
		ingredient[q_index] = Object::create(filename[3], game2scene, answerX, answerY[q_index]);
		ingredient[q_index]->setScale(1.5f);
		break;
	case SPACEBAR:
		ingredient[q_index] = Object::create(filename[4], game2scene, answerX, answerY[q_index]);
		ingredient[q_index]->setScale(1.5f);
	}
	cout << "correct" << endl;
	key_flag = 1;
	q_index++;
}
void clearArray(int key_press[], ObjectPtr ingredient[], ObjectPtr q_ingredient[], int& q_index, int& key_index, int& key_flag) {
	for (int i = 0; i < 100; i++)
	{
		key_press[i] = 0;
	}
	for (int i = 0; i < 5; i++)
	{
		ingredient[i]->hide();
		ingredient[i] = nullptr;
	}
	for (int i = 0; i < 5; i++)
	{
		q_ingredient[i]->hide();
		q_ingredient[i] = nullptr;
	}
	q_index = 0;
	key_index = 0;
	key_flag = 0;
}
void makeTimer(ObjectPtr& bread1, ObjectPtr& clear, ObjectPtr& combo, ObjectPtr comboNum[], int& cnt, int& q_index, int& answerX, int answerY[], TimerPtr& breadTimer, TimerPtr& clearTimer, TimerPtr& comboTimer, ScenePtr& game2scene) {
	bread1->locate(game2scene, answerX, answerY[q_index]);
	bread1->show();
	clear->show();
	combo->show();
	comboNum[cnt - 1]->show();
	cnt++;
	breadTimer->set(0.2f);
	breadTimer->start();
	clearTimer->set(0.4f);
	clearTimer->start();
	comboTimer->set(0.4f);
	comboTimer->start();
}



//GAME3 메서드

// game3 좌표 위치

typedef struct _pos {
	int x = 0;
	int y = 0;
}Pos;

// Game3 map
const int map[21][32] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,5,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,3},
	{0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,0,1,0,0,0,0,1,1,1,1,0,0,0,0,1,0,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,0,1,0,0,0,0,1,1,1,1,0,0,0,0,1,0,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,6,1,0,0,0,0,0,0},
};

//game 3 멥에서의 캐릭터 위치
Pos now;

// game3 맵이 씬에서 어디에 위치인지 기준점을 잡아준다.
Pos criteria;


void initGame3(ScenePtr scene, ObjectPtr* rockets, ObjectPtr* hearts, int& findCon, int& findCrown, int& xspeed, int& heartCount, int& located, ObjectPtr garden, ObjectPtr crown, ObjectPtr con, ObjectPtr explode)
{
	// map 내에서의 좌표
	now.x = 0;
	now.y = 6;

	//scene 에서 map의 기준점 
	criteria.x = 6;
	criteria.y = -12;

	//변수 초기화
	findCon = 0;
	findCrown = 0;

	xspeed = 0;
	heartCount = 3;
	located = 0;



	garden->locate(scene, 480, -960);

	crown->locate(scene, 480 + 18 * 80, -960 + 18 * 80); //가든 모서리를 기준으로 (18 * 80 ,18*80 ) 떨어진 곳에 위치  480 + (18*80) , -960 + 18 * 80 
	con->locate(scene, 480 + 24 * 80, -960); // 가든 모서리를 기준으로 (24 * 80 , 0) 떨어진 곳에 위치 480 + (24*80), -960 
	explode->hide();

	for (int i = 0; i < 10; i++)
	{
		rockets[i]->locate(scene, 1280, 0);
	}

	for (int i = 0; i < 3; i++)
	{
		hearts[i]->setImage("images3/filledheart.png");
		hearts[i]->locate(scene, 700 + 80 * i, 600);
	}
	return;
}

int sceneChange(int xMove, int yMove)
{
	// 배경은 반대로 움직임
	criteria.x = criteria.x - xMove;
	criteria.y = criteria.y + yMove;

	// map  상에서의 캐릭터 위치 변경 -> scene내에서의 좌표는 고정
	now.x = now.x + xMove;
	now.y = now.y + yMove;



	return map[now.y][now.x];
}

bool moveAvailable(int xMove, int yMove)
{
	return  map[now.y + yMove][now.x + xMove] != 0;

}

void rocketInitPos(Pos* rocketPos)
{

	for (int i = 0; i < 10; i++)
	{
		rocketPos[i].x = 16 + rand() % 8; // 화면 밖의 좌표에 설정
		rocketPos[i].y = rand() % 21;
	}
	return;
}

bool checkTouched(int x, int y)
{
	return (475 <= x && x <= 480 && 155 <= y && y <= 160);

}

bool moveRocket(ScenePtr scene, ObjectPtr* rockets, Pos* rocketPos, int xspeed, ObjectPtr explode, TimerPtr rocketstop)
{
	int x, y;
	int finishCount = 0;

	for (int i = 0; i < 10; i++)
	{
		x = rocketPos[i].x * 80 - xspeed * 8; //좌표 계속 변경
		y = rocketPos[i].y * 80 + (criteria.y * 80);

		rockets[i]->locate(scene, x, y);

		// 움직이는 로켓마다 캐릭터에 닿는지 체크 
		if (checkTouched(x, y))
		{
			explode->show();
			rocketstop->start();
		}

		// 로켓이 화면 밖을 벗어난 경우 체크 
		if (x <= 0) finishCount++;

	}

	//모든 로켓이 화면을 벗어나면 
	return finishCount == 10;
}




//main 함수 
int main()
{
	unsigned int srand(time(NULL));
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);


	// intro

		//scenechange Timer
	auto sceneTimer = Timer::create(1.5f);
	auto sceneTimer2 = Timer::create(1.5f);
	auto sceneTimer3 = Timer::create(1.5f);
	auto sceneTimerEnd = Timer::create(3.f);



	//인트로 
	auto intro = Scene::create(" intro ", "images/intro.png");
	auto introMusic = Sound::create("images/introMusic.mp3");
	introMusic->play();

	auto nextToStage1 = Object::create("images/next.png", intro, 990, 10);
	nextToStage1->setScale(0.8f);

	//stage1
	auto stage1 = Scene::create("stage1", "images/stage1.png");
	auto stage1story = Scene::create("stage1", "images/stage1story.png");
	auto nextToGame1 = Object::create("images/next.png", stage1story, 1120, 10);
	nextToGame1->setScale(0.8f);

	//stage2
	auto stage2 = Scene::create("stage2", "images/stage2.png");
	auto stage2story = Scene::create("stage2", "images/stage2story.png");
	auto nextToGame2 = Object::create("images/next.png", stage2story, 1120, 10);
	nextToGame2->setScale(0.8f);


	// stage3 
	auto stage3 = Scene::create("stage3", "images/stage3.png");
	auto stage3story = Scene::create("stage3", "images/stage3story.png");
	auto nextToGame3 = Object::create("images/next.png", stage3story, 1120, 10);
	nextToGame3->setScale(0.8f);



	//win page
	auto win1 = Scene::create("stage3", "images/win1.png");
	auto nextToStage2 = Object::create("images/next.png", win1, 1120, 10);

	auto win2 = Scene::create("stage3", "images/win2.png");
	auto nextToStage3 = Object::create("images/next.png", win2, 1120, 10);

	auto win3 = Scene::create("stage3", "images/win3.png");
	auto winMusic = Sound::create("images/win.mp3");

	//lose page
	auto lose1 = Scene::create("stage3", "images/lose1.png");
	auto re_start = Object::create("images1/restart.png", lose1, 800, 100); //재시작을 위한 변수 re_start

	auto lose2 = Scene::create("stage3", "images/lose2.png");
	auto re_start2 = Object::create("images1/restart.png", lose2, 800, 100); //restart

	auto lose3 = Scene::create("stage3", "images/lose3.png");
	auto loseMusic = Sound::create("images/lose.mp3");

	// end page
	auto end = Scene::create("stage3", "images/end.png");

	// GAME 1 변수

	auto game1intro = Scene::create("", "images1/game1intro.png");
	auto game1 = Scene::create("", "images1/room (1).png");
	auto game1Music = Sound::create("images1/game1bgm.mp3");

	auto cat_start = Object::create("images1/start.png", game1intro, 1060, 550);
	cat_start->setScale(0.5f);

	P toy_class(360, -20, 0);
	//int tmcnt;
	bool check_start;

	auto tail = Object::create("images1/tail.png", game1, 630, 260);
	tail->setScale(0.5f);

	auto cat = Object::create("images1/cat.png", game1, 400, 100);
	auto cat_1_left = Object::create("images1/cat_1(1).png", game1, 400, 100);
	auto cat_1_right = Object::create("images1/cat_1(2).png", game1, 400, 100);
	auto cat_2_left = Object::create("images1/cat_2(1).png", game1, 400, 100);
	auto cat_2_right = Object::create("images1/cat_2(2).png", game1, 400, 100);
	auto cat_final = Object::create("images1/cat_finish.png", game1, 270, 80);
	cat->setScale(0.4f);
	cat_1_left->setScale(0.4f);
	cat_1_right->setScale(0.4f);
	cat_2_left->setScale(0.65f);
	cat_2_right->setScale(0.4f);
	cat_final->setScale(0.65f);

	cat_1_left->hide();
	cat_1_right->hide();
	cat_2_left->hide();
	cat_2_right->hide();
	cat_final->hide();

	auto left = Object::create("images1/left.png", game1, 1050, 50);
	auto right = Object::create("images1/right.png", game1, 1150, 50);
	left->setScale(0.7f);
	right->setScale(0.7f);

	auto toy = Object::create("images1/toy.png", game1, toy_class.px, toy_class.py);
	toy->setScale(0.2f);
	//toy의 좌표 -> 변수로 설정 : 기본 상태일 때 계산, 좌우로 움직일 경우 계산

	for (int i = 0; i < 10; i++) {
		paw[i] = Object::create("images1/paw.png", game1, 620 + 60 * i, 630);
		paw[i]->setScale(0.25f);
		paw[i]->hide();
	}



	auto game1MainTimer = Timer::create(15.f);



	// GAME 2 변수

		//-----start scene ----------
	auto game2intro = Scene::create("game2intro", "images2/startscene.png");
	auto badbgm = Sound::create("images2/badbgm.mp3");
	auto method = Object::create("images2/game2method.png", game2intro, 720, 200);
	auto game2startbtn = Object::create("images1/start.png", game2intro, 853, 150);
	game2startbtn->setScale(0.5f);


	// game scene
	auto game2scene = Scene::create("Hamburger Game", "images2/backgroundscene.png");
	auto bigmac = Sound::create("images2/bigmac.mp3");



	int level = 5;
	int num = 0;
	int questX = 200;
	int answerX = 830;
	int answerY[10] = { 317,354,391,428,465,502,539,576,613,650 };
	int questY[10] = { 317,354,391,428,465,502,539,576,613,650 };
	int i = 0;
	int question[10] = { 0 };

	auto clear = Object::create("images2/clear.png", game2scene, 500, 320, false);
	clear->setScale(1.5f);
	auto combo = Object::create("images2/combo.png", game2scene, 570, 500, false);
	combo->setScale(1.5f);
	auto bread2 = Object::create("images2/bread2.png", game2scene, 830, 290);
	auto q_bread2 = Object::create("images2/bread2.png", game2scene, 200, 290);
	auto q_bread1 = Object::create("images2/bread1.png", game2scene, questX, questY[0], false);
	auto bread1 = Object::create("images2/bread1.png", game2scene, answerX, answerY[0], false);
	auto timer = Timer::create(0.1f);
	auto game2BaseTimer = Timer::create(5.f);
	auto combosound = Sound::create("images2/gamesound.mp3");
	bread1->setScale(3.0f);
	q_bread1->setScale(3.0f);

	ObjectPtr q_ingredient[5] = { 0 };
	ObjectPtr ingredient[5] = { 0 };
	ObjectPtr comboNum[10] = { 0 };
	string filename[5];
	string number[10];

	int index = 0;
	int num_index = 0;
	int key_index = 0;
	int q_index = 0;
	int key_press[100] = { 0 };
	int key_flag = 0;
	int cnt = 1;

	q_bread2->setScale(3.0f);
	bread2->setScale(3.0f);



	//GAME 3 변수

		//1280 * 720 화면
	auto game3intro = Scene::create("escape game", "images3/game3intro.png");
	auto game3startBtn = Object::create("images1/start.png", game3intro, 740, 70);
	game3startBtn->setScale(0.5f);

	auto game3scene = Scene::create("escape game", "images3/sea.png");
	auto game3Music = Sound::create("images3/game3bgm.mp3");

	// garden 크기 : 2560 x 1680  
	// 맵의 맨 왼쪽, 맨 아랫 상단은 초기 scene에서 (480,-960) 좌표에 위치한다.
	auto garden = Object::create("images3/garden2.png", game3scene, 480, -960);
	auto character = Object::create("images3/yonggam7.png", game3scene, 480, 165);
	int located;

	// 콘, 왕관
	auto crown = Object::create("images3/crown.png", game3scene, 480 + 18 * 80, -960 + 18 * 80); //가든 모서리를 기준으로 (18 * 80 ,18*80 ) 떨어진 곳에 위치  480 + (18*80) , -960 + 18 * 80 
	auto con = Object::create("images3/key.png", game3scene, 480 + 24 * 80, -960); // 가든 모서리를 기준으로 (24 * 80 , 0) 떨어진 곳에 위치 480 + (24*80), -960 

	int findCon;
	int findCrown;

	// 안내 지도
	auto guide = Object::create("images3/map.png", game3scene, 1000, 500);

	// 날라오는 로켓들 
	ObjectPtr rockets[10];
	Pos rocketPos[10];
	int xspeed;


	// end, restart
	auto game3restartBtn = Object::create("images3/restart.png", lose3, 800, 100);

	// 생명
	ObjectPtr hearts[3];
	int heartCount;

	// 폭발
	auto explode = Object::create("images3/explode.png", game3scene, 480, 160);


	// 폭발했을 때를 위한 제어
	auto rocketStopTimer = Timer::create(0.1f);

	// 이동제어 - 키보드 입력
	int pressedkey = 0;
	int moveX, moveY = 0;
	auto keyMoveTimer = Timer::create(0.1f);


	// 로켓의 움직임을 제어 
	auto rocketMoveTimer = Timer::create(0.5f);

	//로켓 생성
	for (int i = 0; i < 10; i++)
	{
		rockets[i] = Object::create("images3/rocket.png", game3scene, 1280, 0);
	}

	//하트 생성
	for (int i = 0; i < 3; i++)
	{
		hearts[i] = Object::create("images3/filledheart.png", game3scene, 700 + 80 * i, 600);
	}


	// 변수 초기화 -> 변경되는 이후에 변경되는 모든 변수들은 다 초기화를 해준다.
	initGame3(game3scene, rockets, hearts, findCon, findCrown, xspeed, heartCount, located, garden, crown, con, explode);
	rocketInitPos(rocketPos);




	//인트로 제어함수

		//--------------------------scenechange timercallback-----------------------
	sceneTimer->setOnTimerCallback([&](TimerPtr sceneT)->bool {
		stage1story->enter();
		return true;
		});

	sceneTimer2->setOnTimerCallback([&](TimerPtr sceneT)->bool {
		stage2story->enter();
		return true;
		});

	sceneTimer3->setOnTimerCallback([&](TimerPtr sceneT)->bool {
		stage3story->enter();
		return true;
		});
	sceneTimerEnd->setOnTimerCallback([&](TimerPtr sceneT)->bool {
		end->enter();
		return true;
		});

	// -------------------------------- scenechange mousecallback ---------------------
	//stage1
	nextToStage1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		stage1->enter();
		sceneTimer->start();
		return true;
		});

	nextToGame1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		game1intro->enter();
		introMusic->stop();
		game1Music->play();
		return true;
		});


	//stage2
	nextToStage2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		winMusic->stop();
		introMusic->play();
		stage2->enter();
		sceneTimer2->start();
		return true;
		});

	nextToGame2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		game2intro->enter();
		introMusic->stop();
		badbgm->play();
		return true;
		});

	//stage3
	nextToStage3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		winMusic->stop();
		introMusic->play();
		stage3->enter();
		sceneTimer3->start();
		return true;
		});

	nextToGame3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		game3intro->enter();
		introMusic->stop();
		game3Music->play();
		return true;
		});



	//GAME1 제어함수
	game1MainTimer->setOnTimerCallback([&](TimerPtr)->bool {
		hideTimer();
		lose1->enter();
		game1Music->stop();
		loseMusic->play();
		return true;
		});

	cat_start->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		game1->enter();
		showTimer(game1MainTimer);
		game1MainTimer->start();
		check_start = 1;
		return true;
		});

	tail->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		win1->enter();
		game1Music->stop();
		winMusic->play();
		return true;
		});


	left->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (check_start == 1) {
			//1. 기본 -> left
			if ((toy_class.px == 360) && (toy_class.py == -20) && (toy_class.pcnt == 0)) {
				toy_class.px = 290;
				toy->locate(game1, toy_class.px, toy_class.py);
				toy_class.pcnt++;
				gaugecheck(toy_class.pcnt, paw);

				if (pawcnt < 5) {
					cat->hide();
					cat_1_left->show();
				}
				else if (pawcnt >= 5 && pawcnt < 10) {
					//cat->hide();
					cat_1_right->hide();
					cat_2_right->hide();
					cat_2_left->show();
				}
				else if (pawcnt == 10) {
					cat_2_right->hide();
					cat_final->show();
				}
			}
			//2. right -> left
			else if ((toy_class.px == 440) && (toy_class.py == -20) && (toy_class.pcnt != 0)) {
				toy_class.px = 290;
				toy->locate(game1, toy_class.px, toy_class.py);
				toy_class.pcnt++;
				gaugecheck(toy_class.pcnt, paw);

				if (pawcnt < 5) {
					cat_1_right->hide();
					cat_1_left->show();
				}
				else if (pawcnt >= 5 && pawcnt < 10) {
					cat_1_right->hide();
					cat_2_right->hide();
					cat_2_left->show();
				}
				else if (pawcnt == 10) {
					cat_2_right->hide();
					cat_final->show();
				}
			}

			if (pawcnt == 10) {
				game1MainTimer->stop();
				showMessage("고양이를 나오게 하는 데에 성공했습니다! 쇼파에 있는 꼬리 털을 클릭하여 가져가세요!");
				hideTimer();


			}
		}

		else {
			toy_class.pcnt = 0;
			showMessage("start 버튼을 클릭하세요!");
		}

		return true;
		});

	right->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (check_start == 1) {
			//1. 기본 -> right
			if ((toy_class.px == 360) && (toy_class.py == -20) && (toy_class.pcnt == 0)) {
				toy_class.px = 440;
				toy->locate(game1, toy_class.px, toy_class.py);
				toy_class.pcnt++;
				gaugecheck(toy_class.pcnt, paw);

				if (pawcnt < 5) {
					cat->hide();
					cat_1_right->show();
				}
				else if (pawcnt >= 5 && pawcnt < 10) {
					cat_1_left->hide();
					cat_2_left->hide();
					cat_2_right->show();
				}
				else if (pawcnt == 10) {
					cat_2_left->hide();
					cat_final->show();
				}

			}
			//2. left -> right
			if ((toy_class.px == 290) && (toy_class.py == -20) && (toy_class.pcnt != 0)) {
				toy_class.px = 440;
				toy->locate(game1, toy_class.px, toy_class.py);
				toy_class.pcnt++;
				gaugecheck(toy_class.pcnt, paw);

				if (pawcnt < 5) {
					cat_1_left->hide();
					cat_1_right->show();
				}
				else if (pawcnt >= 5 && pawcnt < 10) {
					cat_1_left->hide();
					cat_2_left->hide();
					cat_2_right->show();
				}
				else if (pawcnt == 10) {
					cat_2_left->hide();
					cat_final->show();
				}
			}

			if (pawcnt == 10) {
				game1MainTimer->stop();
				showMessage("고양이를 나오게 하는 데에 성공했습니다! 꼬리 털을 가져가세요!");
				hideTimer();

			}
		}

		else {
			toy_class.pcnt = 0;
			showMessage("start 버튼을 클릭하세요!");
		}

		return true;
		});



	//실패 시 재시작

	re_start->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		toy_class.pcnt = 0;
		toy_class.px = 360;
		toy_class.py = -20;

		gaugecheck(toy_class.pcnt, paw);

		cat_1_left->hide();
		cat_1_right->hide();
		cat_2_left->hide();
		cat_2_right->hide();
		cat_final->hide();
		cat->show();

		game1->enter();
		game1MainTimer->set(15.f);
		showTimer(game1MainTimer);
		game1MainTimer->start();

		loseMusic->stop();
		game1Music->play();

		return true;
		});

	//GAME2 제어함수 
	makingImage(filename, number, comboNum, num_index, index, game2scene);

	game2startbtn->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		game2scene->enter();
		showTimer(game2BaseTimer);
		bigmac->play(true);
		badbgm->stop();
		timer->start();
		return true;
		});

	re_start2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		game2intro->enter();
		cnt = 1;
		game2BaseTimer->set(5.0f);
		badbgm->play(true);
		loseMusic->stop();
		for (auto& e1 : ingredient) {
			if (e1 != nullptr) {
				e1->hide();
			}
			e1 = nullptr;
		}
		for (auto& e2 : q_ingredient) {
			if (e2 != nullptr) {
				e2->hide();
			}
			e2 = nullptr;
		}
		q_bread1->hide();
		bigmac->stop();
		re_start2->hide();
		return true;
		});

	timer->setOnTimerCallback([&](TimerPtr t)->bool {
		ingredientCase(num, i, level, question, q_ingredient, filename, game2scene, questX, questY, q_bread1);
		return true;
		});
	timer->start();


	auto clearTimer = Timer::create(0.3f);
	clearTimer->setOnTimerCallback([&](TimerPtr clearT)->bool {
		clear->hide();
		return true;
		});
	auto comboTimer = Timer::create(0.3f);
	comboTimer->setOnTimerCallback([&](TimerPtr comboT)->bool {
		combo->hide();
		for (auto& e : comboNum) {
			e->hide();
		}
		combosound->stop();
		return true;
		});
	int flag = 0;
	auto breadTimer = Timer::create(0.3f);
	breadTimer->setOnTimerCallback([&](TimerPtr breadT)->bool {
		bread1->hide();
		if (1) {
			breadT->set(0.3f);
		}
		flag = 1;
		return true;
		});


	game2scene->setOnKeyboardCallback([&](ScenePtr game2scene, KeyCode code, bool pressed)->bool {
		/* translate new key code to old key value */
		int key = 0;
		switch (code) {
		case KeyCode::KEY_LEFT_ARROW: key = LEFT; break;
		case KeyCode::KEY_RIGHT_ARROW: key = RIGHT; break;
		case KeyCode::KEY_UP_ARROW: key = UP; break;
		case KeyCode::KEY_DOWN_ARROW: key = DOWN; break;
		case KeyCode::KEY_SPACE: key = SPACEBAR; break;
		}

		game2BaseTimer->start();
		key_press[key_index] = key;
		timer->stop();
		if (key_index % 2 == 0)
		{
			if (question[q_index] == key_press[key_index]) {
				ingredient2case(q_index, key_flag, question, ingredient, filename, game2scene, answerX, answerY);
			}
			else if (question[q_index] != key_press[key_index] && question[q_index] != 0) {
				game2BaseTimer->stop();
				for (auto& e : key_press) {
					e = 0;
				}
				q_index = 0;
				key_index = 0;
				key_flag = 0;
				bigmac->stop();
				loseMusic->play();
				lose2->enter();
				re_start2->show();
				hideTimer();
			}
			else if (question[q_index] == 0 && key_flag == 1) {
				game2BaseTimer->set(5.0f);
				combosound->play(true);
				//game2BaseTimer->stop();
				makeTimer(bread1, clear, combo, comboNum, cnt, q_index, answerX, answerY, breadTimer, clearTimer, comboTimer, game2scene);
				clearArray(key_press, ingredient, q_ingredient, q_index, key_index, key_flag);
				if (cnt > 10) {
					game2BaseTimer->stop();
					bigmac->stop();
					hideTimer();
					win2->enter();
					winMusic->play();

				}
				timer->start();
			}
		}
		key_index++;
		return true;
		});
	game2BaseTimer->setOnTimerCallback([&](TimerPtr baseT)->bool {
		game2BaseTimer->stop();
		bigmac->stop();
		for (auto& e : key_press) {
			e = 0;
		}
		q_index = 0;
		key_index = 0;
		key_flag = 0;
		loseMusic->play();
		lose2->enter();
		re_start2->show();
		hideTimer();
		return true;
		});




	// GAME 3 제어함수
	game3startBtn->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		game3scene->enter();
		rocketMoveTimer->start();
		return true;
		});


	game3restartBtn->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
		{

			initGame3(game3scene, rockets, hearts, findCon, findCrown, xspeed, heartCount, located, garden, crown, con, explode);
			rocketInitPos(rocketPos);

			game3intro->enter();
			loseMusic->stop();
			game3Music->play();
			return true;
		});

	rocketStopTimer->setOnTimerCallback([&](TimerPtr timer)->bool {

		hearts[--heartCount]->setImage("images3/emptyheart.png");
		explode->hide();
		rocketStopTimer->set(0.1f);

		// 게임종료
		if (heartCount == 0)
		{
			rocketMoveTimer->stop();
			keyMoveTimer->stop();
			keyMoveTimer->stop();

			if (findCrown == 1) crown->drop();
			if (findCon == 1) con->drop();
			game3Music->stop();

			loseMusic->play();
			lose3->enter();

		}
		return true;
		});



	keyMoveTimer->setOnTimerCallback([&](TimerPtr timer)->bool
		{
			switch (pressedkey)
			{
			case LEFT:
				if (moveAvailable(-1, 0))
				{
					moveX = -1; moveY = 0;
					located = sceneChange(moveX, moveY);

				}
				break;

			case RIGHT:
				if (moveAvailable(1, 0))
				{
					moveX = 1; moveY = 0;
					located = sceneChange(moveX, moveY);
				}
				break;
			case UP:
				if (moveAvailable(0, -1))
				{
					moveX = 0; moveY = -1;
					located = sceneChange(moveX, moveY);
				}
				break;
			case DOWN:
				if (moveAvailable(0, 1))
				{
					moveX = 0; moveY = 1;
					located = sceneChange(moveX, moveY);
				}

				break;
			}

			// 왕관 위치
			if (located == 5 && findCrown == 0)
			{
				findCrown = 1;
				crown->pick();

			}

			// 뿔위치
			if (located == 6 && findCon == 0)
			{
				findCon = 1;
				con->pick();
			}

			//도착 지점
			if (located == 3)
			{
				if (findCrown == 1 && findCon == 1)
				{
					rocketMoveTimer->stop();
					rocketStopTimer->stop();
					keyMoveTimer->stop();
					game3Music->stop();

					win3->enter();
					winMusic->play();
					sceneTimerEnd->start();
				}
				return true;

			}

			//scene 변경 
			garden->locate(game3scene, (criteria.x * 80), (criteria.y * 80));
			crown->locate(game3scene, (criteria.x * 80) + (18 * 80), (criteria.y * 80) + (18 * 80));
			con->locate(game3scene, (criteria.x * 80) + (24 * 80), (criteria.y * 80));

			keyMoveTimer->set(0.1f);
			keyMoveTimer->start();

			return true;
		});

	game3scene->setOnKeyboardCallback([&](ScenePtr scene, KeyCode code, bool pressed)->bool
		{
			/* translate new key code to old key value */
			int key = 0;
			switch (code) {
			case KeyCode::KEY_LEFT_ARROW: key = LEFT; break;
			case KeyCode::KEY_RIGHT_ARROW: key = RIGHT; break;
			case KeyCode::KEY_UP_ARROW: key = UP; break;
			case KeyCode::KEY_DOWN_ARROW: key = DOWN; break;
			case KeyCode::KEY_SPACE: key = SPACEBAR; break;
			}

			if (pressed)
			{
				pressedkey = key;
				keyMoveTimer->start();
			}
			if (!pressed) keyMoveTimer->stop();

			return true;
		});


	rocketMoveTimer->setOnTimerCallback([&](TimerPtr timer)->bool
		{
			// 모든 로켓이 지나갔는지 확인 
			if (moveRocket(game3scene, rockets, rocketPos, xspeed, explode, rocketStopTimer))
			{
				rocketInitPos(rocketPos);
				xspeed = 0;

			}
			rocketMoveTimer->start();
			xspeed++;
			return true;
		});



	startGame(intro);

	return 0;
}