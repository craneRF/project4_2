#pragma once
#include"ofMain.h"
//#include "Actor.h"
#include "Component.h"

class GameActor// : public Actor
{
public:
	enum class ActorState {  //Actorの状態
		EActive  //通常。update()を行う
		, EUnControl  //update()は行うが、input()は行わない
		, EPause  //update()・input()を行わない
		, EErace  //削除する
	};
	enum class ActorDrawState {  //Actorの描画状態
		EVisible  //描画する
		, EHidden  //描画しない(削除はされていない)
	};

	enum class Definition {  //定義　これを使って当たり判定やアクターの判別などに使う
		Default
		, Player
		, Enemy
		, Item
		, UI
		, Misc
	};

protected:
	ofVec3f m_pos;
	ofVec3f m_worldPos;

	float m_rotAngle;
	float m_worldRotAngle;

	ofVec3f m_scale;
	ofVec3f m_worldScale;

	string m_name;

	float m_actorDelta;

	ActorState m_ActorState;
	ActorDrawState m_ActorDrawState;

	Definition m_definition;  //定義
	vector<pair<string, int>> m_tagList;  //タグリスト　　タグの名前とその数を持つ


	vector<unique_ptr<Component>> m_componentList;
	vector<unique_ptr<GameActor>> m_childList;
	queue<unique_ptr<GameActor>> m_childAddQue;

public:
	GameActor(string _name = "");
	~GameActor();

	void caluculateWorldTransform();

	void update();  //継承しない
	void input();	//継承しない
	void draw();	//継承しない

	void initialize(ofVec3f _pos, string _name);

	GameActor* mp_parent;

	ofFbo m_fbo;
	ofVec2f m_fboPoint;

	//vector<function<void()>> updatefuncVec;
	//vector<function<void()>> inputfuncVec;
	vector<function<void()>> drawfuncVec;
	//function<void()> drawfunc;
	
	//virtual GameActor* addChild();
	//void RemoveAllChild();
	//GameActor* getChild(int _index) const;
	int getChildCount() { return m_childList.size(); }

	void addTag(string _tagName);  //タグを追加する
	void addTags(vector<string> _tagNameList);  //タグを複数追加する
	void removeTag(string _tagName);  //指定したタグを1つだけ削除する
	void removeTags(vector<string> _tagNameList);  //指定した複数のタグを1つだけ削除する(2回同じタグを指定した場合、もう一度削除する)
	void removeAllTag(string _tagName);  //指定したタグをすべて削除する
	void removeAllTags(vector<string> _tagNameList);  //指定した複数のタグをすべて削除する(2回同じタグを指定した場合、もう一度削除する)

	static list<GameActor*>&& findTagActors(GameActor* _current, string _tagName, list<GameActor*>&& _list = list<GameActor*>());  //指定したタグを持つアクターをすべて取得する
	static list<GameActor*>&& findTagsActorsOR(GameActor* _current, vector<string> _tagName);  //指定した複数のタグの内の1つを持つアクターをすべて取得する
	static list<GameActor*>&& findTagsActorsAND(GameActor* _current, vector<string> _tagName);  //指定した複数のタグをすべて持つアクターをすべて取得する

	static list<GameActor*>&& findDefActors(GameActor* _current, Definition _def, list<GameActor*>&& _list = list<GameActor*>());  //指定したDefinitionを持つアクターをすべて取得する


	//static GameActor* createPlayer(GameActor* _parent, ofVec3f _pos, string _name = "Player");
	/*static void createEnemy(GameActor* _parent, ofVec3f _pos, string _name = "Enemy");*/
	static GameActor* createMap(GameActor* _parent, ofVec3f _pos, string _name = "Map");

	static GameActor * findActor(GameActor * _current, string _name);
	static list<GameActor*>&& findActors(GameActor* _current, string _name, list<GameActor*>&& _list = list<GameActor*>());

	//static GameActor * createMap(GameActor * _parent, ofVec3f _pos, string _name);

public:
	inline ofVec3f& Pos()
	{
		return m_pos;
	}
	inline ofVec3f& WorldPos()
	{
		return m_worldPos;
	}
	inline float& RotAngle()
	{
		return m_rotAngle;
	}
	inline float& WorldRotAngle()
	{
		return m_worldRotAngle;
	}
	inline ofVec3f& Scale()
	{
		return m_scale;
	}
	inline ofVec3f& WorldScale()
	{
		return m_worldScale;
	}
	inline string& Name()
	{
		return m_name;
	}
	inline float& DeltaTime()
	{
		return m_actorDelta;
	}


	inline const ActorState GetActorState()
	{
		return m_ActorState;
	}
	inline const ActorDrawState GetActorDrawState()
	{
		return m_ActorDrawState;
	}

	inline void StateActive()
	{
		m_ActorState = ActorState::EActive;
	}
	inline void StateUnControl()
	{
		m_ActorState = ActorState::EUnControl;
	}
	inline void StatePause()
	{
		m_ActorState = ActorState::EPause;
	}
	inline void StateErace()
	{
		m_ActorState = ActorState::EErace;
	}

	inline void StateVisible()
	{
		m_ActorDrawState = ActorDrawState::EVisible;
	}
	inline void StateHidden()
	{
		m_ActorDrawState = ActorDrawState::EHidden;
	}

	inline Definition& Def() 
	{ 
		return m_definition;
	}
	inline const Definition GetDef() 
	{
		return m_definition;
	}

	inline void SetParam(ofVec3f _pos = { 0,0,0 }, ofVec3f _scale = { 1,1,1 }, float _angle = 0.0f) {
		m_pos = _pos;
		m_scale = _scale;
		m_rotAngle = _angle;
	}

public:
	inline void GameActor::StateAllCpntActive()
	{
		for (auto& cpnt : m_componentList) {
			cpnt->StateCpntActive();
		}
		if (!m_childList.empty()) {
			for (auto& gac : m_childList) {
				for (auto& cpnt : gac->m_componentList) {
					cpnt->StateCpntActive();
				}
			}
		}
	}

	inline void GameActor::StateAllCpntUnControl()
	{
		for (auto& cpnt : m_componentList) {
			cpnt->StateCpntUnControl();
		}
		if (!m_childList.empty()) {
			for (auto& gac : m_childList) {
				for (auto& cpnt : gac->m_componentList) {
					cpnt->StateCpntUnControl();
				}
			}
		}
	}

	inline void GameActor::StateAllCpntPause()
	{
		for (auto& cpnt : m_componentList) {
			cpnt->StateCpntPause();
		}
		if (!m_childList.empty()) {
			for (auto& gac : m_childList) {
				for (auto& cpnt : gac->m_componentList) {
					cpnt->StateCpntPause();
				}
			}
		}
	}

	inline void GameActor::StateAllCpntErace()
	{
		for (auto& cpnt : m_componentList) {
			cpnt->StateCpntErace();
		}
		if (!m_childList.empty()) {
			for (auto& gac : m_childList) {
				for (auto& cpnt : gac->m_componentList) {
					cpnt->StateCpntErace();
				}
			}
		}
	}

	inline void GameActor::StateAllCpntVisible()
	{
		for (auto& cpnt : m_componentList) {
			cpnt->StateCpntVisible();
		}
		if (!m_childList.empty()) {
			for (auto& gac : m_childList) {
				for (auto& cpnt : gac->m_componentList) {
					cpnt->StateCpntVisible();
				}
			}
		}
	}

	inline void GameActor::StateAllCpntHidden()
	{
		for (auto& cpnt : m_componentList) {
			cpnt->StateCpntHidden();
		}
		if (!m_childList.empty()) {
			for (auto& gac : m_childList) {
				for (auto& cpnt : gac->m_componentList) {
					cpnt->StateCpntHidden();
				}
			}
		}
	}

public:
	template <typename T>
	T* addComponent() {
		auto tmp = make_unique<T>(this);
		auto res = tmp.get();
		m_componentList.push_back(move(tmp));
		return res;
	}

	template <typename T>
	T* getComponent() {
		for (auto& cpnt : m_componentList) {
			if (typeid(T) == typeid(*cpnt.get())) {
				return (dynamic_cast<T*>(cpnt.get()));
			}
		}
		return nullptr;
	}

	template <typename T>
	T* addChild(string _name = "") {
		auto actor = make_unique<T>(_name);
		auto res = actor.get();
		m_childAddQue.push(move(actor));
		res->mp_parent = this;
		return res;
	}

	template <typename T>
	void RemoveAllChild() {
		queue<unique_ptr<T>>().swap(m_childAddQue);	//queueの全消し
		for (auto& c : m_childList) {
			c->StateErace();
		}
	}

	template <typename T>
	T* getChild(int _index) const {
		return dynamic_cast<T*>(m_childList[_index].get());
	}
};