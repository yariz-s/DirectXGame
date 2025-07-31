#define NOMINMAX
#include "Player.h"
#include "MyMath.h"
#include <algorithm>
#include <numbers>



using namespace KamataEngine;
using namespace MathUtility;

void Player::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const Vector3& position) {
	assert(model);
	model_ = model;
	camera_ = camera;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.rotation_, worldTransform_.scale_, worldTransform_.translation_);
}

void Player::Update() {
	using namespace KamataEngine;

	// 接地時
	if (onGround_) {

		// 移動入力（左右キー）
		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
			Vector3 acceleration{};

			// 右移動
			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
				if (velocity_.x < 0.0f) {
					velocity_.x *= (1.0f - kAttenuation); // 逆方向入力時の減速ブレーキ
				}
				acceleration.x += kAcceleration;

				// 向きが右でないとき、向きを変える
				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTimeTurn;
				}

			// 左移動
			} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
				if (velocity_.x > 0.0f) {
					velocity_.x *= (1.0f - kAttenuation); // 逆方向入力時の減速ブレーキ
				}
				acceleration.x -= kAcceleration;

				// 向きが左でないとき、向きを変える
				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTimeTurn;
				}
			}

			// 加速処理
			velocity_ += acceleration;
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

		} else {
			// 入力がないときは減速
			velocity_.x *= (1.0f - kAttenuation);
		}

		// ジャンプ（上キー）
		if (Input::GetInstance()->PushKey(DIK_UP)) {
			velocity_.y = JumpAcceleration;
			onGround_ = false;
		}

	} else {
		// 接地していないときは重力を適用
		velocity_ += Vector3(0, -kGravityAcceleration, 0);
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed); // 落下速度の制限
	}
	

	// 位置更新
	worldTransform_.translation_ += velocity_;

	// 着地判定（Y座標が地面以下に落ちたら着地とみなす）
	if (!onGround_ && velocity_.y < 0.0f) {
		if (worldTransform_.translation_.y <= 1.0f) {
			onGround_ = true;
			velocity_.y = 0.0f;
			worldTransform_.translation_.y = 1.0f;
		}
	}

	// 旋回制御
	if (turnTimer_ > 0.0f) {
		turnTimer_ -= 1.0f / 60.0f;

		// 左右の自キャラ角度テーブル
		float destinationRotationYTable[] = {
		    std::numbers::pi_v<float> / 2.0f,       // 左向き
		    std::numbers::pi_v<float> * 3.0f / 2.0f // 右向き
		};

		// 状態に応じた角度を取得する
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

		// 自キャラの角度を設定する（イージングを使って滑らかに）
		worldTransform_.rotation_.y = EaseInOut(destinationRotationY, turnFirstRotationY_, turnTimer_ / kTimeTurn);
	}


	// アフィン変換行列の作成と転送
	worldTransform_.matWorld_ =
		MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Player::Draw() {
//3Dモデルを描画
	
		model_->Draw(worldTransform_,*camera_);
	}