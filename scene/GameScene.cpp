#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <fstream>

GameScene::GameScene() {}

GameScene::~GameScene() { 
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textyreHandle_ = TextureManager::Load("sample.png");
	model_.reset(Model::Create());
	skyDomeModel_.reset(Model::CreateFromOBJ("skyDome",true));
	groundModel_.reset(Model::CreateFromOBJ("ground", true));
	playerModel_.reset(Model::CreateFromOBJ("Player", true));
	playerBodyModel.reset(Model::CreateFromOBJ("float_Body"));
	playerHeadModel.reset(Model::CreateFromOBJ("float_head"));
	playerL_armModel.reset(Model::CreateFromOBJ("float_L_arm"));
	playerR_armModel.reset(Model::CreateFromOBJ("float_R_arm"));
	playerHammerModel.reset(Model::CreateFromOBJ("hammer"));
	enemyModel_.reset(Model::CreateFromOBJ("needle_Body"));
	enemyBulletModel_.reset(Model::CreateFromOBJ("EnemyBullet"));
	viewprojection_.Initialize();
	debugCamera_ = std::make_unique<DebugCamera>(1280,720);
	player_ = std::make_unique<Player>();
	std::vector<Model*> playerModels = {
	    playerBodyModel.get(), playerHeadModel.get(), playerL_armModel.get(),
	    playerR_armModel.get(), playerHammerModel.get()};
	player_->Initialize(playerModels, {0.0f,0.0f,0.0f});
	skyDome_ = std::make_unique<SkyDome>();
	skyDome_->Initialize(skyDomeModel_.get());
	ground_ = std::make_unique<Ground>();
	ground_->Initialize(groundModel_.get());
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();
	followCamera_->SetTarget(&player_->GetWorldTransformBase());
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	 enemyModels={enemyModel_.get(),enemyBulletModel_.get()};
	/*enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(enemyModels);*/
	collisionManager_ = std::make_unique<CollisionManager>();
	player_->SetRadius(3.0f);
	EnemyPopData();
	
}

void GameScene::Update() { 
	UpdateEnemyPopCommands();
	if (player_) {

		player_->Update();
	}
	
	debugCamera_->Update();
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_RETURN)) {
		isDebugcameraActive_ = true;
		
		this->Initialize();
	} 
#endif
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
		if (enemy->IsAlive()==false) {
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
	
	if (player_) {

		player_->Draw(viewprojection_);
	}
	for (Enemy* enemy : enemys_) {
		enemy->Draw(viewprojection_);
	}
	for (EnemyBullet* bullet : enemyBullets_) {

		bullet->Draw(viewprojection_);
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
	if (player_) {

		player_->DrawUI();
	}
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::Finalize() {



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
