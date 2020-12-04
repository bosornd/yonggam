
#include <bangtal>
#include<iostream>
#include <time.h>
using namespace bangtal;
using namespace std;

/*
게임 설명 :
5초마다 로켓이 날라온다.

맵 초기화 : 2560 x 1680 이므로 80 x 80 크기 단위의  네모로 나누면 map[21][32]

막힌 구간 : 0
움직일 수 있는 구간 : 1
용감이 현재 위치 : 2
시작점 : 3
끝점 : 4
열쇠 위치 : 5
왕관 위치 : 6


화면 초기화
보여지는 화면의 크기가 1280 x 720 이므로 scene[8][16]


*/

typedef struct _pos {
	int x = 0;
	int y = 0;
}Pos;

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
		rockets[i] = Object::create("images/rocket.png", scene, 1280, 0);
	}

	for (int i = 0; i < 3; i++)
	{
		hearts[i] = Object::create("images/filledheart.png", scene, 700 + 80 * i, 600);
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
		rocketPos[i].x = 16 + rand() % 4; // 화면 밖의 좌표에 설정
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
		x = rocketPos[i].x * 80 - xspeed * 4; //좌표 계속 변경
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

int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	srand(time(NULL));

	//1280 * 720 화면
	auto scene = Scene::create("sea", "images/sea.png");

	// garden 크기 : 2560 x 1680  

	// 맵의 맨 왼쪽, 맨 아랫 상단은 초기 scene에서 (480,-960) 좌표에 위치한다.
	auto garden = Object::create("images/garden2.png", scene, 480, -960);
	auto character = Object::create("images/yonggam7.png", scene, 480, 165);

	// 콘, 왕관
	auto crown = Object::create("images/crown.png", scene, 480 + 18 * 80, -960 + 18 * 80); //가든 모서리를 기준으로 (18 * 80 ,18*80 ) 떨어진 곳에 위치  480 + (18*80) , -960 + 18 * 80 
	auto con = Object::create("images/key.png", scene, 480 + 24 * 80, -960); // 가든 모서리를 기준으로 (24 * 80 , 0) 떨어진 곳에 위치 480 + (24*80), -960 
	int find = 0;
	/*
	crown->setOnPickCallback([](ObjectPtr object)->bool {

		object->setImage("Images/문서.png");

		});
	con-> setOnPickCallback([](ObjectPtr object)->bool {

		object->setImage("Images/문서.png");
		});
		*/
		// 안내 지도
	auto map = Object::create("images/map.png", scene, 1000, 500);

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
	auto explode = Object::create("images/explode.png", scene, 480, 160);
	explode->hide();



	// 폭발했을 때를 위한 제어
	auto rocketStopTimer = Timer::create(0.1f);

	rocketStopTimer->setOnTimerCallback([&](TimerPtr timer)->bool {
		explode->hide();
		hearts[--heartCount]->setImage("images/emptyheart.png");

		if (heartCount == 0) endGame();

		rocketStopTimer->set(0.1f);

		return true;
		});


	// 이동제어 - 키보드 입력

	// 82 83 84 85
	int pressedkey = 0;
	int moveX, moveY = 0;
	auto keyMoveTimer = Timer::create(0.1f);

	keyMoveTimer->setOnTimerCallback([&](TimerPtr timer)->bool
		{
			switch (pressedkey)
			{
			case 82:
				if (moveAvailable(-1, 0))
				{
					moveX = -1; moveY = 0;
					sceneChange(scene, garden, con, crown, moveX, moveY,find);
					keyMoveTimer->set(0.1f);
					keyMoveTimer->start();
				}
				break;

			case 83:
				if (moveAvailable(1, 0))
				{
					moveX = 1; moveY = 0;
					sceneChange(scene, garden, con, crown, moveX, moveY, find);
					keyMoveTimer->set(0.1f);
					keyMoveTimer->start();
				}
				break;
			case 84:
				if (moveAvailable(0, -1))
				{
					moveX = 0; moveY = -1;
					sceneChange(scene, garden, con, crown, moveX, moveY, find);
					keyMoveTimer->set(0.1f);
					keyMoveTimer->start();
				}
				break;
			case 85:
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



	// 로켓의 움직임을 제어 
	auto rocketMoveTimer = Timer::create(0.5f);
	rocketMoveTimer->start();

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



	startGame(scene);

	return 0;
}
