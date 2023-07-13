#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete debugCamera_;
	delete enemy_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textyreHandle_ = TextureManager::Load("sample.png");
	model_ = Model::Create();
	viewProjection_.Initialize();
	player_ = new Player();
	player_->Initialize(model_, textyreHandle_);
	debugCamera_ = new DebugCamera(1280, 720);
	// 軸方向の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	
	enemy_ = new Enemy();
	enemy_->SetPlayer(player_);
	enemy_->Initialize(model_, {14, 0, 40}, {0, 0, -0.5});
	
}

void GameScene::Update() {
	player_->Update();
	debugCamera_->Update();
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_RETURN)) {
		isDebugcameraActive_ = true;
	}
#endif
	// カメラの処理
	if (isDebugcameraActive_ == true) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.UpdateMatrix();
	}
	enemy_->Update();
	CheckAllCollision();
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
	if (enemy_) {
		enemy_->Draw(viewProjection_);
	}
	player_->Draw(viewProjection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollision() {

	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();
#pragma region 自キャラと敵弾の当たり判定

	for (EnemyBullet* bullet : enemyBullets) {
		CheckCollisionPair(bullet, player_);
	}
#pragma endregion
#pragma region 自弾と敵キャラの当たり判定

	for (PlayerBullet* bullet : playerBullets) {
		CheckCollisionPair(bullet, enemy_);
	}
#pragma endregion
#pragma region 自弾と敵弾の当たり判定
	for (EnemyBullet* eBullet : enemyBullets) {

		for (PlayerBullet* pbullet : playerBullets) {

			CheckCollisionPair(eBullet, pbullet);
		}
	}
#pragma endregion
}

void GameScene::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {
	Vector3 posA = colliderA->GetWorldPos();
	Vector3 posB = colliderB->GetWorldPos();
	float radA = colliderA->Getradius();
	float radB = colliderB->Getradius();
	Vector3 Distance = {
	    (posB.x - posA.x) * (posB.x - posA.x), (posB.y - posA.y) * (posB.y - posA.y),
	    (posB.z - posA.z) * (posB.z - posA.z)};
	if (Distance.x + Distance.y + Distance.z <= (radA + radB) * (radA + radB)) {
		colliderA->OnCollision();
		colliderB->OnCollision();
	}
}

