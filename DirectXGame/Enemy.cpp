#include "MyMath.h"
#include "cassert"
#include "numbers"
#include "player.h"
#define NOMINMAX
#include "Enemy.h"
#include "MapChipField.h"
#include "algorithm"

using namespace KamataEngine;
using namespace MathUtility;

void Enemy::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position) {
    assert(model);
    model_ = model;
    worldTransform_.Initialize();
    worldTransform_.translation_ = position;
    camera_ = camera;
    worldTransform_.rotation_.y = -std::numbers::pi_v<float> / 2.0f;
    velocity_ = { -kWalkSpeed, 0, 0 };

    walkTimer_ = 0.0f;
}

void Enemy::Update() {

    // 移動処理
    worldTransform_.translation_ += velocity_;

    // アニメーション用タイマー
    walkTimer_ += 1.0f / 60.0f;

    // 歩行アニメーションの回転
    worldTransform_.rotation_.x = std::sin(walkTimer_ * 5.0f);

    // ワールド行列を更新
    worldTransform_.matWorld_ = MakeAffineMatrix(
        worldTransform_.scale_,
        worldTransform_.rotation_,
        worldTransform_.translation_
    );

  
    worldTransform_.TransferMatrix();
}

void Enemy::Draw() {
    model_->Draw(worldTransform_, *camera_);
}
