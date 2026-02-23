/*
* Petr Sulc - GD4b - D00261476
* Jakub Polacek - GD4b - D00260171
*/

#pragma once
// Metadata
constexpr auto kWindowTitle = "Game";
constexpr auto kWindowWidth = 1600;
constexpr auto kWindowHeight = 900;

constexpr auto kLocalPlayerCount = 2;
constexpr auto kActionCount = 5;

constexpr auto kPlayerSpeed = 100.f;
constexpr auto kTimePerFrame = 1.f / 60.f;
//TODO review these
constexpr auto kPickupDropChance = 3;
constexpr auto kPointsToWin = 11;
constexpr auto kGameOverToMenuPause = 3;