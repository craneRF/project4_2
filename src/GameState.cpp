#include "ofApp.h"
#include "GameState.h"
#include "GameActor.h"
#include "EnemyType.h"
#include "ItemType.h"
#include "stdComponent.h"
#include "BattleHUD.h"
#include "LoadCSVFile.h"
#include "MapState.h"
#include "BattleState.h"
#include "CreateActor.h"

/*
* 1.hierarchyRoot_のGameMainCtrlComponent内でシーン制御をし、アクターの生成を行うことから、
*   GameMainCtrlComponentは常にActive状態であり、update()を行わなければならない。(hierarchyRoot_自体はActive状態でなくても良い)
* 2.GameMainCtrlComponentのupdate()内に存在するGameStateも常に行われるため、GameStateのupdate()も常に行われる。
* 3.GameStateのupdate()内で行われる「GameActor」・「UIActor」・「Coponentが持つインスタンス」のプロパティ(Actorでいうm_posやm_rotAngle、Pos()など)
*   に対する処理はそれぞれがどんな状態だろうが問答無用で行われる。
*
* 以上の3点とGameActor・UIActor・Component それぞれのState処理の都合上、
* GameStateのupdate()内では
* 「GameActor」・「UIActor」・「Coponentが持つインスタンス」のプロパティ(Actorでいうm_posやm_rotAngle、Pos()など)を変えないでください。
* もし変更が必要になったなら、直接的に変えるのではなく、それぞれのプロパティに影響のない変数を作って、そこから間接的にプロパティを変化させるようにしてください。
* 間接的に変更するのは面倒くさいし、ややこしくなるので非推奨。

* 例：
	・GameActorのプロパティの場合、それ専用のComponentを作り、そのComponentのupdate()内で変更する。
	・UIActorのプロパティの場合、それが存在しているUIScreenのupdate()内で変更する。
	・Componentが持つインスタンスのプロパティの場合、そのupdate()内で変更するか
	 もしくはそのComponentを持つGameActorのupdate()で変更する。

	※最終的に何が言いたいかというと、
	GameStateのupdate()内は極力シーン制御のみにし、
	例に書かれているような設計にしてください、ということです。
*/

void GameStateTitle::enter()
{
	// タイトルなので、プレイヤーのパラメータを初期化
	ofApp::getInstance()->mp_prm->initialize();

	// マップのクリア
	MapComponent::ClearMap();

	ofApp::getInstance()->mp_soundManager->setVolume(0, 0.4f);
	ofApp::getInstance()->mp_soundManager->setVolume(1, 0.4f);
	ofApp::getInstance()->mp_soundManager->loop(0);

	mp_actor1 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	//タイトル背景
	{
		auto spriteCpnt_bg = mp_actor1->addComponent<SpriteComponent>();
		spriteCpnt_bg->initialize("backGround_title_1.jpg");
	}

	//タイトルロゴ
	{
		auto spriteCpnt_title = mp_actor1->addComponent<SpriteComponent>();
		spriteCpnt_title->initialize("title.png");
		spriteCpnt_title->AlignPivotCenter();
		spriteCpnt_title->Offset() += {(float)Define::FULLWIN_W / 2, (float)Define::FULLWIN_H / 2 - 200.f};
	}

	//mp_actor1->addComponent<FontRendererComponent>()->
	//	initialize(ofToString(ofApp::getInstance()->mp_prm->getPlayerParam("HP")), 18, { 300,400 });

	//mp_itemlist = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	//mp_itemlist->addComponent<FontRendererComponent>()->
	//	initialize(ofApp::getInstance()->mp_itemManager->DisplayItemList(), 18, { 400,600 });

	// 選択肢を表示するアクター
	{
		mp_actor2 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_actor2->Pos() = { (float)Define::FULLWIN_W * 0.5f, (float)Define::FULLWIN_H * 0.8f };
		{
			// フレーム
			auto spriteCpnt = mp_actor2->addComponent<SpriteComponent>();
			spriteCpnt->initialize("button1.png", { 0,0,0 }, { 1.f,0.25f });
			spriteCpnt->AlignPivotCenter();

			// フォント
			auto fontCpnt = mp_actor2->addComponent<FontRendererComponent>();
			fontCpnt->initialize(u8"スタート", 18, { 0,0 }, ofColor::white, { 2,2,1 });
			fontCpnt->AlignPivotCenter();
		}
	}

	// 操作方法を表示するアクター
	{
		mp_operationFontactor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_operationFontactor->Pos() = { 0.f, (float)Define::FULLWIN_H * 0.9f };
		mp_operationFontactor->addComponent<FontRendererComponent>()->initialize(u8"Spaceキー:決定");
	}
}

GameState* GameStateTitle::update()
{
	//mp_actor1->getComponent<FontRendererComponent>()->String() = ofToString(ofApp::getInstance()->mp_prm->getPlayerParam("HP"));
	//mp_itemlist->getComponent<FontRendererComponent>()->String() = ofApp::getInstance()->mp_itemManager->DisplayItemList();
	//auto itemCmp = mp_actor1->addComponent<ItemComponent>();
	//if (ofApp::getInstance()->mp_inputManager->getButtonDown("Fire")) {
	//	itemCmp->useItem(ItemType::ATKUp);
	//}
	//if (ofApp::getInstance()->mp_inputManager->getButtonDown("Bomb")) {
	//	itemCmp->useItem(ItemType::POTION);
	//}
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
		//return &GameMainCtrlComponent::m_gameStateEvent;
		return &GameMainCtrlComponent::m_gameStateMap;
	}

	return nullptr;
}

void GameStateTitle::exit()
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild<GameActor>();
	ofApp::getInstance()->mp_soundManager->stop(0);
	ofApp::getInstance()->mp_soundManager->play(4);
}

void GameStateClear::enter()
{
	ofApp::getInstance()->mp_soundManager->setVolume(0, 0.4f);
	ofApp::getInstance()->mp_soundManager->loop(0);

	mp_actor1 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	//背景
	{
		auto spriteCpnt_bg = mp_actor1->addComponent<SpriteComponent>();
		spriteCpnt_bg->initialize("backGround_gaemclear_1.jpg");
	}

	// 選択肢を表示するアクター
	{
		mp_actor2 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_actor2->Pos() = { (float)Define::FULLWIN_W * 0.5f, (float)Define::FULLWIN_H * 0.8f };
		{
			// フレーム
			auto spriteCpnt = mp_actor2->addComponent<SpriteComponent>();
			spriteCpnt->initialize("button1.png", { 0,0,0 }, { 1.f,0.25f });
			spriteCpnt->AlignPivotCenter();

			// フォント
			auto fontCpnt = mp_actor2->addComponent<FontRendererComponent>();
			fontCpnt->initialize(u8"タイトルに戻る", 18, { 0,0 }, ofColor::white, { 2,2,1 });
			fontCpnt->AlignPivotCenter();
		}
	}

	// 操作方法を表示するアクター
	{
		mp_operationFontactor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_operationFontactor->Pos() = { 0.f, (float)Define::FULLWIN_H * 0.9f };
		mp_operationFontactor->addComponent<FontRendererComponent>()->initialize(u8"Spaceキー:決定");
	}
}

GameState * GameStateClear::update()
{
	// タイトルシーンへ遷移
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
		return &GameMainCtrlComponent::m_gameStateTitle;
	}

	return nullptr;
}

void GameStateClear::exit()
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild<GameActor>();
	ofApp::getInstance()->mp_soundManager->stop(0);
	ofApp::getInstance()->mp_soundManager->play(4);
}

void GameStateOver::enter()
{
	ofApp::getInstance()->mp_soundManager->setVolume(0, 0.4f);
	ofApp::getInstance()->mp_soundManager->loop(0);

	mp_actor1 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	//背景
	{
		auto spriteCpnt_bg = mp_actor1->addComponent<SpriteComponent>();
		spriteCpnt_bg->initialize("backGround_gaemover_1.jpg");
	}

	// 選択肢を表示するアクター
	{
		// 選択肢カウント
		int count = 0;
		mp_actor2 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_actor2->Pos() = { (float)Define::FULLWIN_W * 0.5f, (float)Define::FULLWIN_H * 0.8f };
		{
			// スケール
			float scale = 2;
			// 残機数
			int life = ofApp::getInstance()->mp_prm->getPlayerParam("LIFE");

			// フレーム
			auto spriteCpnt = mp_actor2->addComponent<SpriteComponent>();
			spriteCpnt->initialize("button1.png", { 0,0,0 }, { 1.f,0.5f });
			spriteCpnt->AlignPivotCenter();

			// オフセット
			auto offset = spriteCpnt->Offset() * 0.4f;

			// 選択肢１
			if (life != 0) {
				// フォント
				auto fontCpnt = mp_actor2->addComponent<FontRendererComponent>();
				fontCpnt->initialize(u8"復活する (残機数 : " + to_string(life) + ")", 18, { 0,0 }, ofColor::gray, { scale,scale,1 });
				fontCpnt->AlignPivotCenter();
				fontCpnt->Offset().y += offset.y;
				m_selectFontCpntList.emplace_back(fontCpnt);

				// 選択時の処理
				m_funcList.emplace_back([] {
					// 残機を減らす
					ofApp::getInstance()->mp_prm->setPlayerParam("LIFE", ofApp::getInstance()->mp_prm->getPlayerParam("LIFE") - 1);
					// マップへ
					MapComponent::BackStep();
					return &GameMainCtrlComponent::m_gameStateMap;
					}
				);

				++count;
			}
			else {
				spriteCpnt->Scale().y *= 0.5f;
				spriteCpnt->AlignPivotCenter();
				offset.y = 0.f;
			}
			// 選択肢２
			{
				// フォント
				auto fontCpnt = mp_actor2->addComponent<FontRendererComponent>();
				fontCpnt->initialize(u8"タイトルに戻る", 18, { 0,0 }, ofColor::gray, { scale,scale,1 });
				fontCpnt->AlignPivotCenter();
				m_selectFontCpntList.emplace_back(fontCpnt);

				// 選択時の処理
				m_funcList.emplace_back([] {
					MapComponent::ClearMap();
					return &GameMainCtrlComponent::m_gameStateTitle;
					}
				);
			}
		}
	}

	// 操作方法を表示するアクター
	{
		mp_operationFontactor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_operationFontactor->Pos() = { 0.f, (float)Define::FULLWIN_H * 0.9f };
		if (ofApp::getInstance()->mp_prm->getPlayerParam("LIFE") != 0) {
			mp_operationFontactor->addComponent<FontRendererComponent>()->initialize(u8"Spaceキー:決定\nWSキー:選択");
		}
		else {
			mp_operationFontactor->addComponent<FontRendererComponent>()->initialize(u8"Spaceキー:決定");
		}
	}
}

GameState * GameStateOver::update()
{
	// 選択肢が複数ある場合は上下で選択を行う
	if (m_selectFontCpntList.size() >= 2) {
		m_selectFontCpntList.at(m_selectIndex)->Color() = ofColor::gray;

		// 選択
		if (ofApp::getInstance()->mp_inputManager->getButtonDown("Up"))
		{
			ofApp::getInstance()->mp_soundManager->play(3);

			if (--m_selectIndex < 0)
			{
				m_selectIndex = m_selectFontCpntList.size() - 1;
			}
		}
		else if (ofApp::getInstance()->mp_inputManager->getButtonDown("Down"))
		{
			ofApp::getInstance()->mp_soundManager->play(3);

			if (++m_selectIndex >= m_selectFontCpntList.size())
			{
				m_selectIndex = 0;
			}
		}
	}
	m_selectFontCpntList.at(m_selectIndex)->Color() = ofColor::white;

	// 決定
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
		return m_funcList.at(m_selectIndex)();
	}

	return nullptr;
}


void GameStateOver::exit()
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild<GameActor>();
	ofApp::getInstance()->mp_soundManager->stop(0);
	ofApp::getInstance()->mp_soundManager->play(4);

	m_selectIndex = 0;
	m_funcList.clear();
	m_selectFontCpntList.clear();
}

void GameStateMap::enter()
{
	ofApp::getInstance()->mp_soundManager->loop(1);

	/*for (int i = 0; i < 900; i++) {
		auto actor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		actor->Pos() = { float(i), float(i) };
		actor->addComponent<SpriteComponent>();
	}*/

	auto mapActor = GameActor::createMap(ofApp::getInstance()->hierarchyRoot_.get(), { 0.f, 0.f, 0.f });
	mp_mapComp = mapActor->getComponent<MapComponent>();
	mp_mapComp->Initialize();

	auto spriteCpnt_bg = mapActor->addComponent<SpriteComponent>();
	spriteCpnt_bg->initialize("backGround_map_2.jpg");

	// 操作方法を表示するアクター
	{
		mp_operationFontactor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_operationFontactor->Pos() = { 0.f, (float)Define::FULLWIN_H * 0.9f };
		mp_operationFontactor->addComponent<FontRendererComponent>()->initialize(u8"Spaceキー:決定\nWSキー:選択");
	}
}
GameState * GameStateMap::update()
{
	auto kind = mp_mapComp->GetResKind();
	switch (kind)
	{
	case StepKind::EVENT:
		return &GameMainCtrlComponent::m_gameStateEvent;
		break;
	case StepKind::BATTLE:
		return &GameMainCtrlComponent::m_gameStateBattle;
	case StepKind::GOAL:
		GameMainCtrlComponent::m_gameStateBattle.SetIsBossBattle(true);
		return &GameMainCtrlComponent::m_gameStateBattle;
		break;
	default:
		break;
	}
	return nullptr;
}

void GameStateMap::exit()
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild<GameActor>();
	ofApp::getInstance()->mp_soundManager->stop(1);
}


void GameStateBattle::enter()
{
	// 戦闘システム初期化
	{
		// 戦闘コンポーネント
		mp_BattleComp = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>()->addComponent<BattleComponent>();
		mp_BattleComp->Initialize(m_isBossBattle);
	}

	// プレイヤーのHPを表示するアクター
	{
		mp_hpFontActor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_hpFontActor->Pos() = { (float)Define::FULLWIN_W * 0.3f, (float)Define::FULLWIN_H * 0.9f };
		mp_hpFontActor->addComponent<FontRendererComponent>()->
			initialize(u8"");
	}

	// 戦闘のメッセージを表示するアクター
	{
		mp_actor2 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_actor2->Pos() = { (float)Define::FULLWIN_W * 0.7f, (float)Define::FULLWIN_H * 0.8f };

		// フレーム
		auto spriteCpnt = mp_actor2->addComponent<SpriteComponent>();
		spriteCpnt->initialize("button1.png", { 0,0,0 }, { 0.8f,0.5f });
		spriteCpnt->AlignPivotCenter();
		spriteCpnt->Offset().x *= 0.2f;
		// メッセージ
		mp_actor2->addComponent<FontRendererComponent>()->
			initialize(ofToString(""));
	}

	// 操作方法を表示するアクター
	{
		mp_operationFontactor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_operationFontactor->Pos() = { 0.f, (float)Define::FULLWIN_H * 0.9f };
		mp_operationFontactor->addComponent<FontRendererComponent>()->initialize(u8"Spaceキー:決定\nWSキー:選択");
	}

	mp_prePrameter = make_unique<Parameter>(*ofApp::getInstance()->mp_prm);
}

GameState * GameStateBattle::update()
{
	// メッセージ表示
	mp_actor2->getComponent<FontRendererComponent>()->String() = mp_BattleComp->GetInfo();

	// HP表示
	int playerHP = ofApp::getInstance()->mp_prm->getPlayerParam("HP");
	mp_hpFontActor->getComponent<FontRendererComponent>()->String() = u8"プレイヤーのHP:" + to_string(playerHP);

	// 勝敗の結果
	auto result = mp_BattleComp->GetResult();
	switch (result)
	{
	case Result::WIN:
		if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
			// ボス戦だった場合
			if (m_isBossBattle) {
				// クリアシーンへ
				return &GameMainCtrlComponent::m_gameStateClear;
			}
			// 道中戦闘だった場合
			else {
				// マップシーンへ
				return &GameMainCtrlComponent::m_gameStateMap;
			}
		}
	case Result::LOSE:
		if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start")) {
			ofApp::getInstance()->mp_prm.swap(mp_prePrameter);
			return &GameMainCtrlComponent::m_gameStateOver;
		}
	default:
		break;
	}

	return nullptr;
}

void GameStateBattle::exit()
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild<GameActor>();
	m_isBossBattle = false;
}

void GameStateEvent::enter()
{
	mp_actor1 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
	//背景
	{
		auto spriteCpnt_bg = mp_actor1->addComponent<SpriteComponent>();
		spriteCpnt_bg->initialize("backGround_title_1.jpg");
	}

	m_isDead = false;

	mp_prePrameter = make_unique<Parameter>(*ofApp::getInstance()->mp_prm);

	// イベント処理
	string eventStrInfo = "";
	{
		auto eventIndex = static_cast<EVENT_INDEX>(rand() % static_cast<int>(EVENT_INDEX::INDEX_NUM));
		switch (eventIndex)
		{
		case GameStateEvent::EVENT_INDEX::NONE:
			eventStrInfo = u8"何も起こらなかった。\n";
			break;
		case GameStateEvent::EVENT_INDEX::HEAL:
		{
			Effect::healHP(1);
			int hp = ofApp::getInstance()->mp_prm->getPlayerParam("HP");
			eventStrInfo = u8"体力が1回復した。\n現在のHP:" + to_string(hp) + "\n";
			break;
		}
		case GameStateEvent::EVENT_INDEX::DAMAGE:
		{
			Effect::healHP(-1);
			int hp = ofApp::getInstance()->mp_prm->getPlayerParam("HP");
			eventStrInfo = u8"1ダメージを受けた\n";
			// ダメージを受けた後
			// 死亡
			if (hp <= 0)
			{
				eventStrInfo += u8"HPが0になった。\n";
				m_isDead = true;
				// イベント前のパラメータに戻す
				ofApp::getInstance()->mp_prm.swap(mp_prePrameter);
			}
			// 生存
			else
			{
				eventStrInfo += u8"現在のHP:" + to_string(hp) + "\n";
			}
			break;
		}
		case GameStateEvent::EVENT_INDEX::ATTACK_UP:
		{
			Effect::increaseATK(1);
			int attack = ofApp::getInstance()->mp_prm->getPlayerParam("ATTACK");
			eventStrInfo = u8"攻撃力が1上がった。\n現在の攻撃力:" + to_string(attack) + "\n";
			break;
		}
		default:
			break;
		}
	}

	// メッセージを表示するアクター
	{
		mp_actor2 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_actor2->Pos() = { (float)Define::FULLWIN_W * 0.5f, (float)Define::FULLWIN_H * 0.4f };

		// フレーム
		auto spriteCpnt = mp_actor2->addComponent<SpriteComponent>();
		spriteCpnt->initialize("button1.png", { 0,0,0 }, { 1.5f,1.f });
		spriteCpnt->AlignPivotCenter();

		// メッセージ
		auto fontCpnt = mp_actor2->addComponent<FontRendererComponent>();
		fontCpnt->initialize(eventStrInfo);
		fontCpnt->Scale() = { 2,2,1 };
		fontCpnt->AlignPivotCenter();
		//mp_actor2 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		//mp_actor2->Pos() = { (float)Define::FULLWIN_W * 0.7f, (float)Define::FULLWIN_H * 0.8f };

		//// フレーム
		//auto spriteCpnt = mp_actor2->addComponent<SpriteComponent>();
		//spriteCpnt->initialize("button1.png", { 0,0,0 }, { 0.8f,0.5f });
		//spriteCpnt->AlignPivotCenter();
		//spriteCpnt->Offset().x *= 0.2f;
		//// メッセージ
		//mp_actor2->addComponent<FontRendererComponent>()->
		//	initialize(eventStrInfo);
	}

	// 選択肢を表示するアクター
	{
		mp_actor2 = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_actor2->Pos() = { (float)Define::FULLWIN_W * 0.5f, (float)Define::FULLWIN_H * 0.8f };
		{
			// フレーム
			auto spriteCpnt = mp_actor2->addComponent<SpriteComponent>();
			spriteCpnt->initialize("button1.png", { 0,0,0 }, { 1.f,0.25f });
			spriteCpnt->AlignPivotCenter();

			// フォント
			auto fontCpnt = mp_actor2->addComponent<FontRendererComponent>();
			if (m_isDead) {
				fontCpnt->initialize(u8"ゲームオーバーへ", 18, { 0,0 }, ofColor::white, { 2,2,1 });
			}
			else {
				fontCpnt->initialize(u8"マップに戻る", 18, { 0,0 }, ofColor::white, { 2,2,1 });
			}
			fontCpnt->AlignPivotCenter();
		}
	}

	// 操作方法を表示するアクター
	{
		mp_operationFontactor = ofApp::getInstance()->hierarchyRoot_->addChild<GameActor>();
		mp_operationFontactor->Pos() = { 0.f, (float)Define::FULLWIN_H * 0.9f };
		mp_operationFontactor->addComponent<FontRendererComponent>()->initialize(u8"Spaceキー:決定");
	}
}

GameState * GameStateEvent::update()
{
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Start"))
	{
		if (m_isDead)
		{
			return &GameMainCtrlComponent::m_gameStateOver;
		}
		else
		{
			return &GameMainCtrlComponent::m_gameStateMap;
		}
	}

	return nullptr;
}

void GameStateEvent::exit()
{
	ofApp::getInstance()->hierarchyRoot_->RemoveAllChild<GameActor>();
	//ofApp::getInstance()->mp_soundManager->stop(1);
}
