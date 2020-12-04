#include <iostream>
#include <bangtal>
#include <ctime>
#include <string>
#include <string.h>

using namespace bangtal;
using namespace std;


// 키보드 
enum{
		UP = 84,
		LEFT = 82,
		RIGHT = 83,
		DOWN = 85,
		SPACEBAR = 75
};

// 좌표 위치
typedef struct _pos {
	int x = 0;
	int y = 0;
}Pos;

// Game3 map
int map[21][32] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,5,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0},
	{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
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

//멥에서의 캐릭터 위치
Pos now;

//  맵이 씬에서 어디에 위치인지 기준점을 잡아준다.
Pos criteria;


// GAME 2 함수
void makingImage(string filename[5], string number[10], ObjectPtr comboNum[10], int& num_index, int& index, ScenePtr& gamescene) {
	for (num_index = 0; num_index < 10; num_index++) {
		number[num_index] = "images2/" + to_string(num_index + 1) + ".png";
		comboNum[num_index] = Object::create(number[num_index], gamescene, 515, 500, false);
		comboNum[num_index]->setScale(3.0f);
	}
	for (index = 0; index < 5; index++) {
		filename[index] = "images2/ingredient" + to_string(index + 1) + ".png";
	}
}

void ingredientCase(int& num, int& i, int& level, int question[], ObjectPtr q_ingredient[], string filename[], ScenePtr& gamescene, int questX, int questY[], ObjectPtr& q_bread1) {
	for (i = 0; i < level; i++) {
		num = rand() % 5;
		switch (num) {
		case 0:
			question[i] = UP;
			q_ingredient[i] = Object::create(filename[0], gamescene, questX, questY[i]);
			q_ingredient[i]->setScale(1.5f);
			break;
		case 1:
			question[i] = RIGHT;
			q_ingredient[i] = Object::create(filename[1], gamescene, questX, questY[i]);
			q_ingredient[i]->setScale(1.5f);
			break;
		case 2:
			question[i] = LEFT;
			q_ingredient[i] = Object::create(filename[2], gamescene, questX, questY[i]);
			q_ingredient[i]->setScale(1.5f);
			break;
		case 3:
			question[i] = DOWN;
			q_ingredient[i] = Object::create(filename[3], gamescene, questX, questY[i]);
			q_ingredient[i]->setScale(1.5f);
			break;
		case 4:
			question[i] = SPACEBAR;
			q_ingredient[i] = Object::create(filename[4], gamescene, questX, questY[i]);
			q_ingredient[i]->setScale(1.5f);
			break;
		}
	}
	q_bread1->locate(gamescene, questX, questY[i]);
	q_bread1->show();
}

void ingredient2case(int& q_index, int& key_flag, int question[], ObjectPtr ingredient[], string filename[], ScenePtr& gamescene, int& answerX, int answerY[]) {
	switch (question[q_index]) {
	case UP:
		ingredient[q_index] = Object::create(filename[0], gamescene, answerX, answerY[q_index]);
		ingredient[q_index]->setScale(1.5f);
		break;
	case RIGHT:
		ingredient[q_index] = Object::create(filename[1], gamescene, answerX, answerY[q_index]);
		ingredient[q_index]->setScale(1.5f);
		break;
	case LEFT:
		ingredient[q_index] = Object::create(filename[2], gamescene, answerX, answerY[q_index]);
		ingredient[q_index]->setScale(1.5f);
		break;
	case DOWN:
		ingredient[q_index] = Object::create(filename[3], gamescene, answerX, answerY[q_index]);
		ingredient[q_index]->setScale(1.5f);
		break;
	case SPACEBAR:
		ingredient[q_index] = Object::create(filename[4], gamescene, answerX, answerY[q_index]);
		ingredient[q_index]->setScale(1.5f);
	}
	cout << "correct" << endl;
	key_flag = 1;
	q_index++;
}
void clearArray(int key_press[], ObjectPtr ingredient[], ObjectPtr q_ingredient[], int& q_index, int& key_index, int& key_flag) {
	for (int i = 0; i < 100; i++) {
		key_press[i] = 0;
	}
	for (int i = 0; i < 5; i++) {
		ingredient[i]->hide();
		ingredient[i] = nullptr;
	}
	for (int i = 0; i < 5; i++) {
		q_ingredient[i]->hide();
		q_ingredient[i] = nullptr;
	}
	q_index = 0;
	key_index = 0;
	key_flag = 0;
}
void makeTimer(ObjectPtr& bread1, ObjectPtr& clear, ObjectPtr& combo, ObjectPtr comboNum[], int& cnt, int& q_index, int& answerX, int answerY[], TimerPtr& breadTimer, TimerPtr& clearTimer, TimerPtr& comboTimer, ScenePtr& gamescene) {
	bread1->locate(gamescene, answerX, answerY[q_index]);
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



//GAME3함수

void init(ScenePtr scene, ObjectPtr* rockets, ObjectPtr* hearts)
{
	// map 내에서의 좌표
	now.x = 0;
	now.y = 6;

	//scene 에서 map의 기준점 
	criteria.x = 6;
	criteria.y = -12;

	for (int i = 0; i < 20; i++)
	{
		rockets[i] = Object::create("images3/rocket.png", scene, 1280, 0);
	}

	for (int i = 0; i < 3; i++)
	{
		hearts[i] = Object::create("images3/filledheart.png", scene, 700 + 80 * i, 600);
	}
	return;
}

void sceneChange(ScenePtr scene, ObjectPtr garden, ObjectPtr con, ObjectPtr crown, int xMove, int yMove, int& find)
{
	// 배경은 반대로 움직임
	criteria.x = criteria.x - xMove;
	criteria.y = criteria.y + yMove;

	// map  상에서의 캐릭터 위치 변경 -> scene내에서의 좌표는 고정
	now.x = now.x + xMove;
	now.y = now.y + yMove;

	
	// 왕관 위치
	if (map[now.y][now.x] == 5)
	{
		find++;
		crown->pick();
		map[now.y][now.x] = 1;
	}

	// 뿔위치
	if (map[now.y][now.x] == 6)
	{
		find++;
		con->pick();
		map[now.y][now.x] = 1;
	}

	//도착 지점
	if (map[now.y][now.x] == 3)
	{
		if (find == 2) endGame();
	}

	//scene 변경 
	garden->locate(scene, (criteria.x * 80), (criteria.y * 80));
	crown->locate(scene, (criteria.x * 80) + (18 * 80), (criteria.y * 80) + (18 * 80));
	con->locate(scene, (criteria.x * 80) + (24 * 80), (criteria.y * 80));

}

bool moveAvailable(int xMove, int yMove)
{
	return  map[now.y + yMove][now.x + xMove] != 0;

}

void rocketInitPos(Pos* rocketPos)
{

	for (int i = 0; i < 20; i++)
	{
		rocketPos[i].x = 16 + rand() % 8; // 화면 밖의 좌표에 설정
		rocketPos[i].y = rand() % 21;
	}
	return;
}

bool checkTouched(int x, int y)
{
	return (480 == x && 160 == y);

}

bool moveRocket(ScenePtr scene, ObjectPtr* rockets, Pos* rocketPos, int xspeed, ObjectPtr explode, TimerPtr rocketstop)
{
	int x, y;
	int finishCount = 0;

	for (int i = 0; i < 20; i++)
	{
		x = rocketPos[i].x * 80 - xspeed * 8; //좌표 계속 변경
		y = rocketPos[i].y * 80 + (criteria.y * 80);

		rockets[i]->locate(scene, x, y);

		// 움직이는 로켓마다 캐릭터에 닿는지 체크 
		if (checkTouched(x, y))
		{
			cout << "X :" << x << "Y: " << y << endl;
			explode->show();
			rocketstop->start();
		}

		// 로켓이 화면 밖을 벗어난 경우 체크 
		if (x <= 0) finishCount++;

	}

	//모든 로켓이 화면을 벗어나면 
	return finishCount == 20;
}

//메인
int main()
{
	unsigned int srand(time(NULL));
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	
// GAME 2 변수
	//-----start scene ----------
	auto startscene = Scene::create("Start Game", "images2/startscene.png");

	// game scene
	auto gamescene = Scene::create("Hamburger Game", "images2/backgroundscene.png");

	auto startbtn = Object::create("images2/startbtn.png", startscene, 550, 400);
	auto badbgm = Sound::create("images2/badbgm.mp3");
	auto bigmac = Sound::create("images2/bigmac.mp3");
	badbgm->play(true);
	showMessage("나에게 10개의 햄버거를 각 햄버거당 5초만에 만들어주면 너에게 날개를 주겠다!!");

	startbtn->setScale(0.25f);
	startbtn->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		gamescene->enter();
		bigmac->play(true);
		badbgm->stop();
		return true;
		});


	int level = 5;
	int num = 0;
	int questX = 200;
	int answerX = 830;
	int answerY[10] = { 317,354,391,428,465,502,539,576,613,650 };
	int questY[10] = { 317,354,391,428,465,502,539,576,613,650 };
	int i = 0;
	int question[10] = { 0 };

	auto clear = Object::create("images2/clear.png", gamescene, 500, 320, false);
	clear->setScale(1.5f);
	auto combo = Object::create("images2/combo.png", gamescene, 570, 500, false);
	combo->setScale(1.5f);
	auto bread2 = Object::create("images2/bread2.png", gamescene, 830, 290);
	auto q_bread2 = Object::create("images2/bread2.png", gamescene, 200, 290);
	auto q_bread1 = Object::create("images2/bread1.png", gamescene, questX, questY[0], false);
	auto bread1 = Object::create("images2/bread1.png", gamescene, answerX, answerY[0], false);
	auto timer = Timer::create(0.1f);
	auto basetimer = Timer::create(4.0f);
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
	basetimer->set(40.f);


//GAME 3 변수

	//1280 * 720 화면
	auto scene = Scene::create("escape game", "images3/sea.png");

	// garden 크기 : 2560 x 1680  

	// 맵의 맨 왼쪽, 맨 아랫 상단은 초기 scene에서 (480,-960) 좌표에 위치한다.
	auto garden = Object::create("images3/garden2.png", scene, 480, -960);
	auto character = Object::create("images3/yonggam7.png", scene, 480, 165);

	// 콘, 왕관
	auto crown = Object::create("images3/crown.png", scene, 480 + 18 * 80, -960 + 18 * 80); //가든 모서리를 기준으로 (18 * 80 ,18*80 ) 떨어진 곳에 위치  480 + (18*80) , -960 + 18 * 80 
	auto con = Object::create("images3/key.png", scene, 480 + 24 * 80, -960); // 가든 모서리를 기준으로 (24 * 80 , 0) 떨어진 곳에 위치 480 + (24*80), -960 
	int find = 0;

	// 안내 지도
	auto map = Object::create("images3/map.png", scene, 1000, 500);

	// 날라오는 로켓들 
	ObjectPtr rockets[20];
	Pos rocketPos[20];
	int xspeed = 0;


	// 생명
	ObjectPtr hearts[3];
	int heartCount = 3;


	// 초기화 
	init(scene, rockets, hearts);
	rocketInitPos(rocketPos);

	// 폭발
	auto explode = Object::create("images3/explode.png", scene, 480, 160);
	explode->hide();



	// 폭발했을 때를 위한 제어
	auto rocketStopTimer = Timer::create(0.1f);

	// 이동제어 - 키보드 입력

	int pressedkey = 0;
	int moveX, moveY = 0;
	auto keyMoveTimer = Timer::create(0.1f);


	// 로켓의 움직임을 제어 
	auto rocketMoveTimer = Timer::create(0.5f);




//GAME2 제어함수 

	makingImage(filename, number, comboNum, num_index, index, gamescene);

	timer->setOnTimerCallback([&](TimerPtr t)->bool {
		ingredientCase(num, i, level, question, q_ingredient, filename, gamescene, questX, questY, q_bread1);
		return true;
		});
	timer->start();
	showTimer(basetimer);

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

	basetimer->setOnTimerCallback([&](TimerPtr baseT)->bool {
		showMessage("YOU LOSE");
		//endGame();
		return true;
		});

	gamescene->setOnKeyboardCallback([&](ScenePtr gamescene, int key, bool pressed)->bool {
		basetimer->start();
		key_press[key_index] = key;
		timer->stop();
		if (key_index % 2 == 0) {
			if (question[q_index] == key_press[key_index]) {
				ingredient2case(q_index, key_flag, question, ingredient, filename, gamescene, answerX, answerY);
			}
			else if (question[q_index] != key_press[key_index] && question[q_index] != 0) {
				showMessage("YOU LOSE");
				//endGame();
			}
			else if (question[q_index] == 0 && key_flag == 1) {
				basetimer->set(40.0f);
				combosound->play(true);
				basetimer->stop();
				makeTimer(bread1, clear, combo, comboNum, cnt, q_index, answerX, answerY, breadTimer, clearTimer, comboTimer, gamescene);
				clearArray(key_press, ingredient, q_ingredient, q_index, key_index, key_flag);
				if (cnt > 1) {
					basetimer->stop();
					bigmac->stop();
					hideTimer();
			
					scene->enter();
					rocketMoveTimer->start();
				}
				timer->start();
			}
		}
		key_index++;
		return true;
	});


// GAME 3 제어함수
	rocketStopTimer->setOnTimerCallback([&](TimerPtr timer)->bool {
		explode->hide();
		hearts[--heartCount]->setImage("images3/emptyheart.png");

		if (heartCount == 0) endGame();

		rocketStopTimer->set(0.1f);

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
					sceneChange(scene, garden, con, crown, moveX, moveY,find);
					keyMoveTimer->set(0.1f);
					keyMoveTimer->start();
				}
				break;

			case RIGHT:
				if (moveAvailable(1, 0))
				{
					moveX = 1; moveY = 0;
					sceneChange(scene, garden, con, crown, moveX, moveY, find);
					keyMoveTimer->set(0.1f);
					keyMoveTimer->start();
				}
				break;
			case UP:
				if (moveAvailable(0, -1))
				{
					moveX = 0; moveY = -1;
					sceneChange(scene, garden, con, crown, moveX, moveY, find);
					keyMoveTimer->set(0.1f);
					keyMoveTimer->start();
				}
				break;
			case DOWN:
				if (moveAvailable(0, 1))
				{
					moveX = 0; moveY = 1;
					sceneChange(scene, garden, con, crown, moveX, moveY, find);
					keyMoveTimer->set(0.1f);
					keyMoveTimer->start();
				}

				break;
			}
			return false;
	});

	scene->setOnKeyboardCallback([&](ScenePtr scene, int key, bool pressed)->bool
		{
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
			if (moveRocket(scene, rockets, rocketPos, xspeed, explode, rocketStopTimer))
			{
				rocketInitPos(rocketPos);
				xspeed = 0;

			}
			rocketMoveTimer->start();
			xspeed++;
			return true;
		});



	startGame(startscene);

	return 0;
}
