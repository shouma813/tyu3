#include "Player.h"
#include "MyMath.h"
#include <numbers>
#include <algorithm>

using namespace KamataEngine;
using namespace MathUtility;

void Player::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const Vector3& position) {
    assert(model);
    model_ = model;
    camera_ = camera;

    worldTransform_.Initialize();
    worldTransform_.translation_ = position;
    worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f; // 初期右向き
    worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.rotation_,
        worldTransform_.scale_, worldTransform_.translation_);

    // 初期状態
    velocity_ = { 0.0f, 0.0f, 0.0f };
    onGround_ = false;
    lrDirection_ = LrDirection::kRight;
    turnTimer_ = 0;
}

void Player::Update() {
    const float groundHeight = 0.0f; // 地面のY座標

    // 地面に接地しているか
    if (onGround_) {
        // 移動入力
        if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
            Vector3 acceleration = {};

            // 右方向入力
            if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
                if (velocity_.x < 0.0f) {
                    velocity_.x *= (1.0f - kAttenuation);
                }
                acceleration.x += kAcceleration;

                if (lrDirection_ != LrDirection::kRight) {
                    lrDirection_ = LrDirection::kRight;
                    turnFirstRotationY_ = worldTransform_.rotation_.y;
                    turnTimer_ = kTimeTurn;
                }
            }
            // 左方向入力
            else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
                if (velocity_.x > 0.0f) {
                    velocity_.x *= (1.0f - kAttenuation);
                }
                acceleration.x -= kAcceleration;

                if (lrDirection_ != LrDirection::kLeft) {
                    lrDirection_ = LrDirection::kLeft;
                    turnFirstRotationY_ = worldTransform_.rotation_.y;
                    turnTimer_ = kTimeTurn;
                }
            }

            // 加速
            velocity_ += acceleration;
            velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
        }
        else {
            // 徐々に減速
            velocity_.x *= (1.0f - kAttenuation);
        }

        // ジャンプ処理
        if (Input::GetInstance()->PushKey(DIK_UP)) {
            velocity_.y = kJumpAcceleration;
            onGround_ = false;
        }
    }
    else {
        // 空中で重力適用
        velocity_.y -= kGravityAcceleration;
        velocity_.y = max(velocity_.y, -kLimitFallSpeed);
    }

    // 座標更新
    worldTransform_.translation_ += velocity_;

    // 着地処理
    if (worldTransform_.translation_.y <= groundHeight) {
        worldTransform_.translation_.y = groundHeight;
        velocity_.y = 0.0f;
        onGround_ = true;
    }

// 回転処理（向き変更）
    if (turnTimer_ > 0.0f) {
        turnTimer_ -= 1.0f / 60.0f; 
        float t = 1.0f - std::clamp(turnTimer_ / kTimeTurn, 0.0f, 1.0f);

        // 左右どちらに向くか
        float targetY = (lrDirection_ == LrDirection::kRight) ? std::numbers::pi_v<float> / 2.0f : -std::numbers::pi_v<float> / 2.0f;

        // 補間で滑らかに回転
        worldTransform_.rotation_.y = std::lerp(turnFirstRotationY_, targetY, t);
    }
    else {
        // 回転が完了したあと角度を確定
        if (lrDirection_ == LrDirection::kRight) {
            worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
        }
        else {
            worldTransform_.rotation_.y = -std::numbers::pi_v<float> / 2.0f;
        }
    }

    // 行列更新
    worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
    worldTransform_.TransferMatrix();
}

void Player::Draw() {
    if (camera_ && model_) {
        model_->Draw(worldTransform_, *camera_);
    }
}
