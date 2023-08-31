#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <fstream>

GameScene::GameScene() {
	textyreHandle_ = TextureManager::Load("title.png");
	ClearTexhandle = TextureManager::Load("Clear.png");
	gameOverTexhandle = TextureManager::Load("gameOver.png");
	MissionTexhandle = TextureManager::Load("Mission.png");
	/*model_.reset(Model::Create());*/
	skyDomeModel_.reset(Model::CreateFromOBJ("skyDome", true));
	groundModel_.reset(Model::CreateFromOBJ("ground", true));
	playerModel_.reset(Model::CreateFromOBJ("Player", true));
	playerBodyModel.reset(Model::CreateFromOBJ("float_Body"));
	playerHeadModel.reset(Model::CreateFromOBJ("float_head"));
	playerL_armModel.reset(Model::CreateFromOBJ("float_L_arm"));
	playerR_armModel.reset(Model::CreateFromOBJ("float_R_arm"));
	playerHammerModel.reset(Model::CreateFromOBJ("hammer"));
	enemyModel_.reset(Model::CreateFromOBJ("needle_Body"));
	enemyBulletModel_.reset(Model::CreateFromOBJ("EnemyBullet"));
	enemyModels = {enemyModel_.get(), enemyBulletModel_.get()};
	playerModels = {
	    playerBodyModel.get(), playerHeadModel.get(), playerL_armModel.get(),
	    playerR_armModel.get(), playerHammerModel.get()};
	titlesprite_.reset(
	    Sprite::Create(textyreHandle_, {640.0f, 300.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}));
	Clearsprite_.reset(
	    Sprite::Create(ClearTexhandle, {640.0f, 300.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}));
	GameOversprite_.reset(
	    Sprite::Create(gameOverTexhandle, {640.0f, 300.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}));
	Missionsprite_.reset(Sprite::Create(
	    MissionTexhandle, {640.0f, 300.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}));
	sceneNum = 0;
	pressCount = 0;
	missionCount = 0;
}

GameScene::~GameScene() { 
	for (Enemy* enemy : enemys_) {
		delete enemy;
	}
	for (EnemyBullet* bullet : enemyBullets_) {

		delete bullet;
	}
}

void GameScene::Initialize() {
	
	enemyCount = 0;
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	viewprojection_.Initialize();
	debugCamera_ = std::make_unique<DebugCamera>(1280,720);
	player_ = std::make_unique<Player>();
	 
	player_->Initialize(playerModels, {0.0f,0.0f,0.0f});
	skyDome_ = std::make_unique<SkyDome>();
	skyDome_->Initialize(skyDomeModel_.get());
	ground_ = std::make_unique<Ground>();
	ground_->Initialize(groundModel_.get());
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();
	followCamera_->SetTarget(&player_->GetWorldTransformBase());
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	 
	/*enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(enemyModels);*/
	collisionManager_ = std::make_unique<CollisionManager>();
	player_->SetRadius(3.0f);
	/*EnemyPopData();UpdateEnemyPopCommands();*/
	EnemySpawn({70.0f,8.0f,25.0f});
	EnemySpawn({20.0f, 7.0f, 40.0f});
	EnemySpawn({6.0f, 13.0f, 38.0f});
	EnemySpawn({35.0f, 12.0f, 50.0f});
	EnemySpawn({50.0f, 9.0f, 38.0f});
	EnemySpawn({50.0f, 9.0f, -30.0f});
	EnemySpawn({60.0f, 6.0f, -10.0f});
	EnemySpawn({70.0f, 9.0f, 0.0f});
	EnemySpawn({14.0f, 9.0f, -20.0f});
	enemyCount = 0;
}

void GameScene::Update() { 
	if (sceneNum == 0) {
		pressCount++;
		XINPUT_STATE joyState;

		if (!Input::GetInstance()->GetJoystickState(0, joyState)) {
			return;
		}

		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A&&pressCount>=30) {
			sceneNum = 1;
			
		}
	}
	if ( sceneNum == 3||sceneNum==4) {
		XINPUT_STATE joyState;

		if (!Input::GetInstance()->GetJoystickState(0, joyState)) {
			return;
		}

		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
			sceneNum = 0;
			pressCount = 0;
		}
	}
	if (sceneNum == 1) {
		missionCount++;
		if (missionCount >= 120) {
			sceneNum = 2;
			missionCount = 0;
		}
	}
	if (sceneNum == 2) {
		if (player_->GetHP() <= 0) {
			sceneNum = 3;
			this->Finalize();
			this->Initialize();
		}
		/*if (enemyCount >= 9) {
			sceneNum = 4;
			this->Finalize();
			this->Initialize();
		}*/
		if (player_) {

			player_->Update();
		}

		debugCamera_->Update();

		// カメラの処理
		if (isDebugcameraActive_ == true) {
			debugCamera_->Update();
			viewprojection_.matView = debugCamera_->GetViewProjection().matView;
			viewprojection_.matProjection = debugCamera_->GetViewProjection().matProjection;
			viewprojection_.TransferMatrix();
		}
		followCamera_->Update();
		viewprojection_.matView = followCamera_->GetViewProjection().matView;
		viewprojection_.matProjection = followCamera_->GetViewProjection().matProjection;
		viewprojection_.TransferMatrix();
		enemys_.remove_if([](Enemy* enemy) {
			if (enemy->IsAlive() == false) {
				delete enemy;
				
				return true;
			}
			return false;
		});
		for (Enemy* enemy : enemys_) {
			enemy->Update();
		}

		collisionManager_->ClearColliders();
		enemyBullets_.remove_if([](EnemyBullet* bullet) {
			if (bullet->isDead()) {
				delete bullet;
				return true;
			}
			return false;
		});
		for (EnemyBullet* bullet : enemyBullets_) {

			bullet->Update();
		}
		collisionManager_->AddCollider(player_.get());
		if (player_) {

			for (PlayerBullet* pBullet : player_->GetBullets()) {
				collisionManager_->AddCollider(pBullet);
			}
		}
		for (Enemy* enemy : enemys_) {
			collisionManager_->AddCollider(enemy);
		}
		for (EnemyBullet* eBullet : enemyBullets_) {
			collisionManager_->AddCollider(eBullet);
		}
		collisionManager_->CheckAllCollision();
#ifdef _DEBUG
if (input_->TriggerKey(DIK_RETURN)) {
			isDebugcameraActive_ = true;
			/*delete this;*/
			this->Finalize();

			/*this->Finalize();*/
			this->Initialize();
		}
	

#endif
}		
}
void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	if (sceneNum == 2) {

		if (player_) {

			player_->Draw(viewprojection_);
		}
		for (Enemy* enemy : enemys_) {

			enemy->Draw(viewprojection_);
		}
		for (EnemyBullet* bullet : enemyBullets_) {

			bullet->Draw(viewprojection_);
		}
	}
	skyDome_->Draw(viewprojection_);
	ground_->Draw(viewprojection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	if (sceneNum == 2) {

		if (player_) {

			player_->DrawUI();
		}
	} else if (sceneNum == 0) {
		titlesprite_->Draw();
	} else if (sceneNum == 1) {
	
         Missionsprite_->Draw();      	
	} else if (sceneNum == 4) {
		Clearsprite_->Draw();
	} else if (sceneNum == 3) {
		GameOversprite_->Draw();
	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::Finalize() {
	
	for (EnemyBullet* bullet : enemyBullets_) {

		bullet->SetAlive(true);
	}
	for (Enemy* enemy : enemys_) {
		enemy->SetAlive(false);
	}
	enemys_.remove_if([](Enemy* enemy) {
		if (enemy->IsAlive() == false) {
			delete enemy;
			return true;
		}
		return false;
	});
	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->isDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
	
	player_.release();
}

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) { enemyBullets_.push_back(enemyBullet); }

void GameScene::EnemySpawn(Vector3 pos) {
	Enemy* enemy = new Enemy();
	enemy->SetPlayer(player_.get());
	enemy->SetGameScene(this);
	enemy->Initialize(enemyModels, pos);

	enemys_.push_back(enemy);
}

void GameScene::EnemyPopData() {
	std::ifstream file;
	file.open("csv/enemyPop.csv");
	assert(file.is_open());

	enemyPopCommands << file.rdbuf();

	file.close();
}

void GameScene::UpdateEnemyPopCommands() {
	std::string line;

	while (getline(enemyPopCommands, line)) {
		std::istringstream line_stream(line);
		std::string word;
		getline(line_stream, word, ',');
		if (word.find("//") == 0) {

			continue;
		}
		if (word.find("POP") == 0) {
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());
			EnemySpawn({x, y, z});
		}
	}
}
