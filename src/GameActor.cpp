#include "ofApp.h"
#include "GameActor.h"
#include "stdComponent.h"

GameActor::GameActor(string _name) 
	:/*Actor(_name)
	,*/ m_pos(ofVec3f(0, 0, 0))
	, m_rotAngle(0)
	, m_worldRotAngle(0)
	, m_scale({ 1,1,1 })
	, m_name(_name)
	, m_actorDelta(0.0f)
	, m_ActorState(ActorState::EActive)
	, m_ActorDrawState(ActorDrawState::EVisible)
	, m_definition(Definition::Default)
	,mp_parent(nullptr)
{
	m_fbo.allocate(ofGetWidth()/5, ofGetHeight()/5, GL_RGBA);

	m_componentList.clear();
	m_childList.clear();
	m_tagList.clear();
}

GameActor::~GameActor()
{
}

void GameActor::caluculateWorldTransform()
{
	if (this->RotAngle() > 360.0f) {
		this->RotAngle() -= 360.0f;
	}
	else if (this->RotAngle() < 0.0f) {
		this->RotAngle() += 360.0f;
	}

	if (mp_parent != nullptr) {
		this->WorldScale() = mp_parent->WorldScale() * this->Scale();
		this->WorldRotAngle() = mp_parent->WorldRotAngle() + this->RotAngle();
		this->WorldPos() = mp_parent->WorldPos() +
			this->Pos().getRotated(-(mp_parent->WorldRotAngle()), ofVec3f(0, 0, 1)) *
			mp_parent->WorldScale();
		this->m_fboPoint *= this->WorldScale();
	}
	else {
		this->WorldScale() = this->Scale() * ((float)ofGetHeight() / (float)Define::FULLWIN_H);
		this->WorldRotAngle() = this->RotAngle();
		this->WorldPos() = this->Pos().getRotated(-this->RotAngle(), ofVec3f(0, 0, 1)) * this->Scale()* ((float)ofGetHeight() / (float)Define::FULLWIN_H);
		this->m_fboPoint *= this->WorldScale();
	}
}

void GameActor::initialize(ofVec3f _pos, string _name) {
	m_pos = _pos;
	caluculateWorldTransform();
	m_name = _name;
}

//GameActor* GameActor::addChild()
//{
//	auto actor = make_unique<GameActor>();
//	auto res = actor.get();
//	m_childAddQue.push(move(actor));
//	res->mp_parent = this;
//	return res;
//}
//
//////void GameActor::RemoveAllChild()
//{
//	queue<unique_ptr<GameActor>>().swap(m_childAddQue);	//queueの全消し
//	for (auto& c : m_childList) {
//		c->waitforErase_ = true;
//	}
//}
//
//GameActor* GameActor::getChild(int _index) const
//{
//	return m_childList[_index].get();
//}

GameActor * GameActor::findActor(GameActor* _current, string _name)
{
	if (_current->m_name == _name) return _current;
	for (auto & actor : _current->m_childList) {
		auto tmp = findActor(actor.get(), _name);
		if (tmp != nullptr) return tmp;
	}
	return nullptr;
}

list<GameActor*>&& GameActor::findActors(GameActor * _current, string _name, list<GameActor*>&&	_list)
{
	if (_current->m_name == _name) _list.push_back(_current);
	for (auto & actor : _current->m_childList) {
		_list = findActors(actor.get(), _name, move(_list));
	}
	return move(_list);
}

GameActor* GameActor::createMap(GameActor * _parent, ofVec3f _pos, string _name)
{
	auto mapActor = _parent->addChild<GameActor>();
	mapActor->initialize(_pos, _name);
	mapActor->addComponent<MapComponent>();

	return mapActor;
}

void GameActor::update() {
	caluculateWorldTransform();
	m_actorDelta = ofApp::getInstance()->m_deltaTime;

	if (!m_componentList.empty()) {
		m_componentList.erase(
			remove_if(m_componentList.begin(), m_componentList.end(),
				[](const auto& cpnt) { return cpnt->GetComponentState() == Component::ComponentState::EErace; }),
			m_componentList.end()
		);
	}
	//自分のコンポーネントの更新処理
	if (!m_componentList.empty()) {
		for (const auto& cpnt : m_componentList) {
			if (cpnt->GetComponentState() != Component::ComponentState::EPause) {
				cpnt->update();
			}
		}
	}
	//DrawOrder
	//ofApp::getInstance()->draworderset_.insert(this);
	//削除予定アクターの削除
	if (!m_childList.empty()) {
		m_childList.erase(
			remove_if(m_childList.begin(), m_childList.end(),
				[](const auto& gac) { return gac->GetActorState() == ActorState::EErace; }),
			m_childList.end()
		);
	}
	//追加待ちアクターの追加処理
	while (!m_childAddQue.empty()) {
		m_childList.push_back(move(m_childAddQue.front()));
		m_childAddQue.pop();
	}
	//子ゲームアクターの更新処理
	if (!m_childList.empty()) {
		for (auto& gac : m_childList) {
			if (gac->GetActorState() != ActorState::EPause) {
				gac->update();
			}
		}
	}
}

void GameActor::input()
{
	//自分のコンポーネントの入力処理
	if (!m_componentList.empty()) {
		for (const auto& cpnt : m_componentList) {
			if (cpnt->GetComponentState() == Component::ComponentState::EActive) {
				cpnt->input();
			}
		}
	}
	//子ゲームアクターの入力処理
	if (!m_childList.empty()) {
		for (auto& gac : m_childList) {
			if (gac->GetActorState() == ActorState::EActive) {
				gac->input();
			}
		}
	}
}


void GameActor::draw()
{
	if (GetActorDrawState() == ActorDrawState::EVisible) {
		if (find_if(this->m_tagList.begin(), this->m_tagList.end(), [](pair<string, int> &v) {return v.first == "fbo"; }) == this->m_tagList.end()) {
			for (auto& df : this->drawfuncVec) {
				assert(df != nullptr);
				ofPushMatrix();
				ofTranslate(this->m_worldPos);
				ofRotateDeg(-(this->m_worldRotAngle));
				ofScale(this->m_worldScale);
				df();
				ofPopMatrix();
			}
		}
		else {
			for (auto& df : this->drawfuncVec) {
				assert(df != nullptr);
				assert(!this->m_fbo.isAllocated());
				m_fbo.begin();
				ofClear(0);
				ofTranslate(m_fboPoint /*+ ofVec2f(100.f, 100.f)*/);
				ofRotateDeg(-(this->m_worldRotAngle));
				ofScale(this->m_worldScale);
				df();
				m_fbo.end();

				m_fbo.draw(WorldPos().x, WorldPos().y, ofGetWidth()/5, ofGetHeight()/5);
				//画像サイズ分ofTraslateで動かし、fbo.drawでWorldPos-画像サイズ分動かす。
			}
		}
			//for (auto& df : this->drawfuncVec) {
			//	assert(df != nullptr);
			//	//assert(!this->m_fbo.isAllocated());
			//	m_fbo.begin();
			//	ofClear(0);
			//	//ofPushMatrix();
			//	//ofTranslate(this->m_worldPos);
			//	ofTranslate(this->m_fboPoint + ofVec2f(38.5f, 6.5f));
			//	ofRotateDeg(-(this->m_worldRotAngle));
			//	ofScale(this->m_worldScale);
			//	//m_fbo.begin();
			//	//ofClear(0);
			//	df();
			//	//m_fbo.end();
			//	//ofPopMatrix();
			//	m_fbo.end();

			//	m_fbo.draw(WorldPos().x - m_fboPoint.x, WorldPos().y - m_fboPoint.y, ofGetWidth() / 5, ofGetHeight() / 5);
			//	//m_fbo.draw(0.0f, 0.0f, ofGetWidth(), ofGetHeight());
			//	//m_fbo.draw(m_fboPoint, ofGetWidth(), ofGetHeight());
			//	//m_fbo.draw(ofGetWidth()/2, ofGetHeight()/2);
			//	//m_fbo.draw(0, 0);

			//	//画像サイズ分ofTraslateで動かし、fbo.drawでWorldPos-画像サイズ分動かす。
			//}
	}

	if (!m_childList.empty()) {
		for (auto& gac : m_childList) {
			gac->draw();
		}
	}
}

void GameActor::addTag(string _tagName)
{
	for (auto& tag : m_tagList) {
		if (tag.first == _tagName) {  //既に同じ名前のタグがあるなら、1増やして終了する
			tag.second++;
			return;
		}
	}

	//もし無かった場合は、新しくタグを作る
	pair<string, int> tagPair;
	tagPair.first = _tagName;
	tagPair.second = 1;

	m_tagList.emplace_back(tagPair);
}

void GameActor::addTags(vector<string> _tagNameList)
{
	for (auto& addtag : _tagNameList) {
		addTag(addtag);
	}
}

void GameActor::removeTag(string _tagName)
{
	for (auto iter = m_tagList.begin(); iter != m_tagList.end();) {
		if (iter->first == _tagName) {  //指定したタグがあるか検索
			iter->second--;             //タグの数を1つ減らす
			if (iter->second == 0) {
				iter = m_tagList.erase(iter);  //タグの数が0になったらリストを消す
			}
			else {
				++iter;
			}
		}
		else {
			++iter;
		}
	}
}

void GameActor::removeTags(vector<string> _tagNameList)
{
	for (auto& removetag : _tagNameList) {
		removeTag(removetag);
	}
}

void GameActor::removeAllTag(string _tagName)
{
	for (auto iter = m_tagList.begin(); iter != m_tagList.end();) {
		if (iter->first == _tagName) {  //指定したタグがあるか検索
			iter = m_tagList.erase(iter);  //あればタグをリストから消す
		}
		else {
			++iter;
		}
	}
}

void GameActor::removeAllTags(vector<string> _tagNameList)
{
	for (auto& removetags : _tagNameList) {
		removeAllTag(removetags);
	}
}

list<GameActor*>&& GameActor::findTagActors(GameActor * _current, string _tagName, list<GameActor*>&& _list)
{
	for (auto& tag : _current->m_tagList) {
		if (tag.first == _tagName) {
			_list.push_back(_current);
			break;
		}
	}

	for (auto & actor : _current->m_childList) {
		_list = findTagActors(actor.get(), _tagName, move(_list));
	}

	return move(_list);
}

list<GameActor*>&& GameActor::findTagsActorsOR(GameActor * _current, vector<string> _tagName)
{
	//正直、moveを使っているが右辺値参照が上手くできているのか不明。hierarchyRoot_を引数に渡したとき、重くなるかもしれない。

	list<GameActor*> actorList = {};
	list<GameActor*> baseList = {};
	list<GameActor*> bufferList = {};

	for (auto& tagname : _tagName) {
		if (actorList.empty()) {
			actorList = findTagActors(_current, tagname, move(actorList));
		}
		else {
			baseList = move(actorList);
			bufferList = findTagActors(_current, tagname, move(bufferList));
			set_union(baseList.begin(), baseList.end(), bufferList.begin(), bufferList.end(), inserter(actorList, actorList.end()));
			bufferList.clear();

			//set_union(actorList.begin(), actorList.end(), bufferList.begin(), bufferList.end(), inserter(actorList, actorList.end())); ← これは無限ループになっているのか実行が止まってしまうので
		}
	}

	return move(actorList);
}

list<GameActor*>&& GameActor::findTagsActorsAND(GameActor * _current, vector<string> _tagName)
{
	//正直、moveを使っているが右辺値参照が上手くできているのか不明。hierarchyRoot_を引数に渡したとき、重くなるかもしれない。

	list<GameActor*> actorList = {};
	list<GameActor*> baseList = {};
	list<GameActor*> bufferList = {};

	for (auto& tagname : _tagName) {
		if (actorList.empty()) {
			actorList = findTagActors(_current, tagname, move(actorList));
		}
		else {
			baseList = move(actorList);
			bufferList = findTagActors(_current, tagname, move(bufferList));
			set_intersection(actorList.begin(), actorList.end(), bufferList.begin(), bufferList.end(), inserter(actorList, actorList.end()));
			bufferList.clear();
		}
	}
	return move(actorList);
}

list<GameActor*>&& GameActor::findDefActors(GameActor * _current, Definition _def, list<GameActor*>&& _list)
{
	if (_current->m_definition == _def) _list.push_back(_current);
	for (auto & actor : _current->m_childList) {
		_list = findDefActors(actor.get(), _def, move(_list));
	}

	return move(_list);
}
