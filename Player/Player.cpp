#include "Player.h"
#include <cassert>
#include "ImGuiManager.h"
#include"MyMath.h"
Player::~Player() {
	for (PlayerBullet* bullet : bullets_) {

		delete bullet;
	}
	delete sprite2DReticle_;
}

void Player::Atack() {
	XINPUT_STATE joystate;
	//キーボードの場合
	if (input_->PushKey(DIK_SPACE)) {
		if (count == 0) {

			const float KBulletSped = 1.0f;
			Vector3 velocity(0.0f, 0.0f, KBulletSped);
			// velocity = TransformNormal(velocity, worldTransform_.matWorld_);
			velocity = Subtract(
			    {worldtransform3Dreticle_.matWorld_.m[3][0],
			     worldtransform3Dreticle_.matWorld_.m[3][1],
			     worldtransform3Dreticle_.matWorld_
			         .m[3][2]} /*worldtransform3Dreticle_.translation_*/,
			    GetWorldPos());
			velocity = Multiply(KBulletSped, Normalise(velocity));
			PlayerBullet* newBulllet = new PlayerBullet();
			newBulllet->Initialize(model_, GetWorldPos(), velocity);
			// 弾を登録する
			bullets_.push_back(newBulllet);
			count++;
		}
	} else {

			count = 0;
		}
	
	//ゲームパッドの場合
	if (!Input::GetInstance()->GetJoystickState(0, joystate)) {
		return;	
	}
	if (joystate.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		if (count == 0) {

			const float KBulletSped = 1.0f;
			Vector3 velocity(0.0f, 0.0f, KBulletSped);
			// velocity = TransformNormal(velocity, worldTransform_.matWorld_);
			velocity = Subtract(
			    {worldtransform3Dreticle_.matWorld_.m[3][0],
			     worldtransform3Dreticle_.matWorld_.m[3][1],
			     worldtransform3Dreticle_.matWorld_
			         .m[3][2]} /*worldtransform3Dreticle_.translation_*/,
			    GetWorldPos());
			velocity = Multiply(KBulletSped, Normalise(velocity));
			PlayerBullet* newBulllet = new PlayerBullet();
			newBulllet->Initialize(model_, GetWorldPos(), velocity);
			// 弾を登録する
			bullets_.push_back(newBulllet);
			count++;
		}
		else {
			return;
		}
	} else {

			count = 0;
		}
	
	
}

void Player::Setreticle(const ViewProjection view) { 
	const float kDistancePlayerTo3DReticle = 50.0f;
	Vector3 offset = {0, 0, 1.0f};

	offset = TransformNormal(offset, worldTransform_.matWorld_);
	offset = Multiply(kDistancePlayerTo3DReticle, Normalise(offset));

	worldtransform3Dreticle_.translation_ = Add(GetWorldPos(), offset);
	worldtransform3Dreticle_.UpdateMatrix();

	Vector3 positionReticle = {
	    worldtransform3Dreticle_.matWorld_.m[3][0], worldtransform3Dreticle_.matWorld_.m[3][1],
	    worldtransform3Dreticle_.matWorld_.m[3][2]} /*worldtransform3Dreticle_.translation_*/;

	Matrix4x4 matViewport =
	    MakeViewportMatrix(0.0f, 0.0f, WinApp::kWindowWidth, WinApp::kWindowHeight, 0.0f, 1.0f);

	Matrix4x4 matViewProjectionViewport =
	    Multiply(Multiply(view.matView, view.matProjection), matViewport);
	positionReticle = Transform(positionReticle, matViewProjectionViewport);
	//sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));
	
	
//	//マウスの場合
//	POINT mousePosition;
////マウス座標（スクリーン座標）を取得する
//	GetCursorPos(&mousePosition);
//	//	クライアントエリア座標に変換する
//	HWND hwnd = WinApp::GetInstance()->GetHwnd();
//	ScreenToClient(hwnd, &mousePosition);
//	sprite2DReticle_->SetPosition({(float)mousePosition.x, (float)mousePosition.y});
	//キーボードの場合
	XINPUT_STATE joystate;
	Vector2 spritePostition = sprite2DReticle_->GetPosition();
	if (Input::GetInstance()->GetJoystickState(0, joystate)) {
		spritePostition.x += (float)joystate.Gamepad.sThumbRX / SHRT_MAX * 5.0f;
		spritePostition.y -= (float)joystate.Gamepad.sThumbRY / SHRT_MAX * 5.0f;
		// スプライトの座標変更を反映
		sprite2DReticle_->SetPosition(spritePostition);
	}
	

	Matrix4x4 matVPV =
	    Multiply(Multiply(view.matView, view.matProjection), matViewport);
	Matrix4x4 matInverseVPV = Inverse(matVPV);
	Vector3 posNear = {
	    (float)sprite2DReticle_->GetPosition().x, (float)sprite2DReticle_->GetPosition().y, 0};
	Vector3 posFar = {
	    (float)sprite2DReticle_->GetPosition().x, (float)sprite2DReticle_->GetPosition().y, 1};
	posNear = Transform(posNear, matInverseVPV);
	posFar = Transform(posFar, matInverseVPV);
	Vector3 mouseDirection = Subtract(posFar, posNear);
	mouseDirection = Normalise(mouseDirection);
	const float kDistancetestObject = 100.0f;
	worldtransform3Dreticle_.translation_ =
	    Add(posNear, Multiply(kDistancetestObject, mouseDirection));
	worldtransform3Dreticle_.UpdateMatrix();
	ImGui::Begin("Player");
	ImGui::Text("shotcount:(%d)", count);
	ImGui::Text("Near:(%+.2f,%+.2f,%.2f)", posNear.x, posNear.y, posNear.z);
	ImGui::Text("Far:(%+.2f,%+.2f,%.2f)", posFar.x, posFar.y, posFar.z);
	ImGui::Text(
	    "3DRetixle:(%+.2f,%+.2f,%.2f)", worldtransform3Dreticle_.translation_.x,
	    worldtransform3Dreticle_.translation_.y, worldtransform3Dreticle_.translation_.z);
	ImGui::End();
}

void Player::Initialize(Model* model, uint32_t textureHandle, Vector3 pos) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	SetCollisionAttribute(CollisionConfig::kCollisionAttributePlayer);
	SetCollisionMask(~CollisionConfig::kCollisionAttributePlayer);
	worldTransform_.translation_ = Add(worldTransform_.translation_, pos);
	worldtransform3Dreticle_.Initialize();

	uint32_t textureReticle = TextureManager::Load("Reticle.png");

	sprite2DReticle_ =
	    Sprite::Create(textureReticle, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
}

void Player::Update(const ViewProjection view) {
	// デスフラグの立った弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->isDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	worldTransform_.TransferMatrix();
	Vector3 move = {0, 0, 0};
	// キャラクターの移動量
	const float kCharacterSpeed = 0.3f;
	float imputFloat3[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};

	
	// デバッグ
	ImGui::Begin("Debug");
	ImGui::SliderFloat3("player", imputFloat3, -30.0f, 30.0f);
	ImGui::Text("DebugCamera  Enter");
	ImGui::End();
	worldTransform_.translation_.x = imputFloat3[0];
	worldTransform_.translation_.y = imputFloat3[1];
	worldTransform_.translation_.z = imputFloat3[2];

	const float kRotSpeed = 0.02f; 

	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
	if (input_->PushKey(DIK_W)) {
		worldTransform_.rotation_.x -= kRotSpeed;
	} else if (input_->PushKey(DIK_S)) {
		worldTransform_.rotation_.x += kRotSpeed;
	}
	//キーボード操作の場合
	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
	//ゲームパッドの場合
	XINPUT_STATE joystate;
	if (Input::GetInstance()->GetJoystickState(0, joystate)) {
		move.x += (float)joystate.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
		move.y += (float)joystate.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;
	}
	// 移動限界
	const float kMoveLimiX = 30.0f;
	const float kMoveLimiY = 18.0f;


	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimiX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimiX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimiY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimiY);
	
	
	worldTransform_.translation_=Add(worldTransform_.translation_, move);
	worldTransform_.UpdateMatrix();
	
	Atack();
	for (PlayerBullet* bullet : bullets_) {
	
	bullet->Updarte();
	}
	
	Setreticle(view);
}
void Player::Draw(const ViewProjection view) {
	model_->Draw(worldTransform_, view, textureHandle_);
	for (PlayerBullet* bullet : bullets_) {

	bullet->Draw(view);
	}
	//model_->Draw(worldtransform3Dreticle_, view, textureHandle_);
}

void Player::DrawUI() { sprite2DReticle_->Draw();

}

Vector3 Player::GetWorldPos() { 
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Player::OnCollision() {}
