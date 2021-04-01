#include "DXUT.h"
#include "cAdd.h"
#include "cTitle.h"
#include "Stage.h"
#include "cEnd.h"

cAdd::cAdd()
{
}


cAdd::~cAdd()
{
}

void cAdd::AddImages()
{
	//Player
	IMAGEMANAGER->AddImage("Player", "./Image./Player/Player.png");
	IMAGEMANAGER->AddImage("Player1", "./Image./Player/Player(IsHurt1).png");
	IMAGEMANAGER->AddImage("Player2", "./Image./Player/Player(IsHurt2).png");

	//PlayerBullet
	IMAGEMANAGER->AddImage("Bullet", "./Image./Player/PlayerBullet.png");
	IMAGEMANAGER->AddImage("Bullet2", "./Image./Player/PlayerBullet2.png");

	//Enemy
	IMAGEMANAGER->AddImage("LEnemy", "./Image./Enemy/[Left]Enemy.png");
	IMAGEMANAGER->AddImage("LEnemy1", "./Image./Enemy/[Left]Enemy(IsFreeze).png");
	IMAGEMANAGER->AddImage("REnemy", "./Image./Enemy/[Right]Enemy.png");
	IMAGEMANAGER->AddImage("REnemy1", "./Image./Enemy/[Right]Enemy(IsFreeze).png");

	IMAGEMANAGER->AddImage("BombEnemy", "./Image./Enemy/BombEnemy.png");
	IMAGEMANAGER->AddImage("BombEnemy1", "./Image./Enemy/BombEnemy(IsFreeze).png");

	//Boss
	IMAGEMANAGER->AddImage("Boss", "./Image./Boss/Boss.png");

	//EnemyBullet
	IMAGEMANAGER->AddImage("EnemyBullet", "./Image./Enemy/EnemyBullet.png");

	//Scene
	IMAGEMANAGER->AddImage("Title", "./Image./Scene/Title.png");

	IMAGEMANAGER->AddImage("Stage1", "./Image./Scene/Stage1.png");

	IMAGEMANAGER->AddImage("End", "./Image./Scene/End.png");

	//UI
	IMAGEMANAGER->AddImage("PlayOff", "./Image./UI/PlayOff.png");
	IMAGEMANAGER->AddImage("SettingOff", "./Image./UI/SettingOff.png");
	IMAGEMANAGER->AddImage("CreditOff", "./Image./UI/CreditOff.png");
	IMAGEMANAGER->AddImage("ExitOff", "./Image./UI/ExitOff.png");
	IMAGEMANAGER->AddImage("PlayOn", "./Image./UI/PlayOn.png");
	IMAGEMANAGER->AddImage("SettingOn", "./Image./UI/SettingOn.png");
	IMAGEMANAGER->AddImage("CreditOn", "./Image./UI/CreditOn.png");
	IMAGEMANAGER->AddImage("ExitOn", "./Image./UI/ExitOn.png");
	IMAGEMANAGER->AddImage("Play", "./Image./UI/Play.png");
	IMAGEMANAGER->AddImage("Setting", "./Image./UI/Setting.png");
	IMAGEMANAGER->AddImage("Credit", "./Image./UI/Credit.png");
	IMAGEMANAGER->AddImage("Exit", "./Image./UI/Exit.png");
	IMAGEMANAGER->AddImage("Creditt", "./Image./UI/Creditt.png");
	IMAGEMANAGER->AddImage("Settingg", "./Image./UI/Settingg.png");

	IMAGEMANAGER->AddImage("PlayerBulletMod1", "./Image./Player/PlayerBulletMod(1).png");
	IMAGEMANAGER->AddImage("PlayerBulletMod2", "./Image./Player/PlayerBulletMod(2).png");

	//Effect
	for (int i = 1; i <= 8; i++)
	{
		if (i != 8)
		{
			IMAGEMANAGER->AddImage("EnemyDeadEffect" + to_string(i), "./Image./Effect./EnemyDeadEffect/EnemyDeadEffect" + to_string(i) + ".png");
			IMAGEMANAGER->AddImage("BossDeadEffect" + to_string(i), "./Image./Effect./BossDeadEffect/BossDeadEffect" + to_string(i) + ".png");
		}
		IMAGEMANAGER->AddImage("ShieldEffect" + to_string(i), "./Image./Effect./ShieldEffect/ShieldEffect" + to_string(i) + ".png");
	}
}

void cAdd::AddScenes()
{
	SCENEMANAGER->AddScene("Title", new cTitle);
	SCENEMANAGER->AddScene("Stage", new Stage);
	SCENEMANAGER->AddScene("End", new cEnd);
}
