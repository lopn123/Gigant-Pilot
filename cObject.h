#pragma once
class cObject abstract
{
private:
	string m_objName;
	bool m_Del = false;
	Vec2 m_pos;
	int HP;
public :
	RECT rt = {0,0,0,0};
	void SetPos(Vec2 pos) { m_pos = pos; };
	Vec2 GetPos() { return m_pos; };
	cObject(const string & _name = "void");
	virtual ~cObject() = default;
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Release();
	void DestroyObj() { m_Del = true; }
	bool IsValid() {
		return m_Del;

	}
	void SetHp(int hp) { HP = hp; };
	void HitHp(int hp) { HP -= hp; };
	int GetHp() { return HP; };
	bool Turn=false ;
	void MakeTag(const string& str) {  m_objName= str; };
	string& GetTag() {return m_objName; };
	void SetRect(RECT RT) { rt = RT; };
	RECT GetRect() { return rt; };
	virtual void Collision(cObject * obj);
	virtual void UIRender();
	bool IsOutMap(Vec2 pos);
};

