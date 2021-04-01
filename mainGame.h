#pragma once

class cAdd;
class mainGame
{
private:
	cAdd* m_Add;
public:
	mainGame();
	~mainGame();

	void Init();
	void Release();
	void Update();
	void Render();
	void LostDevice();
	void ResetDevice();
};

