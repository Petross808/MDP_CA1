/*
* Petr Sulc - GD4b - D00261476
* Jakub Polacek - GD4b - D00260171
*/

#pragma once
// Metadata
constexpr auto kWindowTitle = "Game";
constexpr auto kWindowWidth = 1600;
constexpr auto kWindowHeight = 900;

constexpr auto actionCount = 4;

constexpr auto kPlayerSpeed = 100.f;
constexpr auto kTimePerFrame = 1.f / 60.f;
constexpr auto kMaxFireRate = 5;
constexpr auto kMaxSpread = 3;
constexpr auto kPickupDropChance = 3;
constexpr auto kMissileRefill = 3;
constexpr auto kGameOverToMenuPause = 3;