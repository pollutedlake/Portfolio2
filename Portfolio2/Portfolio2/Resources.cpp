#include "Stdafx.h"
#include "Resources.h"

HRESULT Resources::init(void)
{
	IMAGEMANAGER->addImage("TitleBG", "Resources/Images/BackGrounds/TitleScene/TitleBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("TitleName", "Resources/Images/BackGrounds/TitleScene/TitleName.bmp", 451, 117, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("TitleEFX2", "Resources/Images/Effects/TitleScene/TitleEFX2.bmp", 2241, 2025, 6, 6, true, RGB(4, 0, 4));
	IMAGEMANAGER->addFrameImage("TitleEFX1", "Resources/Images/Effects/TitleScene/TitleEFX1.bmp", 3315, 2398, 13, 11, true, RGB(4, 100, 4));
	IMAGEMANAGER->addFrameImage("TitleButtons", "Resources/Images/BackGrounds/TitleScene/TitleButtons.bmp", 390, 124, 2, 4, true, RGB(252, 0, 0));


	IMAGEMANAGER->addImage("ScenarioBG", "Resources/Images/BackGrounds/ScenarioScene/Scenario_BG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addFrameImage("Scenarios", "Resources/Images/BackGrounds/ScenarioScene/Scenarios.bmp", 1680, 2700, 6, 27, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("ScrollUp", "Resources/Images/BackGrounds/ScenarioScene/ScrollUp.bmp", 19, 45, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("ScrollDown", "Resources/Images/BackGrounds/ScenarioScene/ScrollDown.bmp", 19, 45, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("ScrollNoClick", "Resources/Images/BackGrounds/ScenarioScene/ScrollNoClick.bmp", 15, 43, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("ScrollClick", "Resources/Images/BackGrounds/ScenarioScene/ScrollClick.bmp", 15, 43, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("WorldMap", "Resources/Images/BackGrounds/WorldMapScene/WorldMap.bmp", 1347, 839);

	IMAGEMANAGER->addImage("TextBox", "Resources/Images/UI/TextBox.bmp", 230, 105);
	IMAGEMANAGER->addImage("MapCoordination", "Resources/Images/UI/MapCoordination.bmp", 70, 38);
	IMAGEMANAGER->addImage("EldBar", "Resources/Images/UI/EldBar.bmp", 62, 4);
	IMAGEMANAGER->addImage("EldIcon", "Resources/Images/UI/EldIcon.bmp", 12, 15, true, RGB(252, 252, 252));
	IMAGEMANAGER->addImage("CurEld", "Resources/Images/UI/CurEld.bmp", 7, 6, true, RGB(252, 252, 252));
	IMAGEMANAGER->addImage("Vermont", "Resources/Images/UI/Vermont.bmp", 260, 480, true, RGB(0, 0, 4));
	IMAGEMANAGER->addImage("Saladin", "Resources/Images/UI/Saladin.bmp", 400, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Sherazade", "Resources/Images/UI/Sherazade.bmp", 424, 480, true, RGB(255, 0, 255 ));
	IMAGEMANAGER->addImage("HpBar", "Resources/Images/UI/HpBar.bmp", 2, 12);
	IMAGEMANAGER->addImage("MpBar", "Resources/Images/UI/MpBar.bmp", 2, 12);
	IMAGEMANAGER->addFrameImage("ForeheadKiss", "Resources/Images/BackGrounds/EndingScene/ForeheadKiss.bmp", 432, 79, 6, 1, true, RGB(168, 208, 168));
	IMAGEMANAGER->addFrameImage("VermontEnding", "Resources/Images/BackGrounds/EndingScene/VermontEnding.bmp", 130, 78, 2, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("SaladinEnding", "Resources/Images/BackGrounds/EndingScene/SaladinEnding.bmp", 1208, 101, 8, 1, true, RGB(168, 208, 168));
	IMAGEMANAGER->addImage("EndingBG", "Resources/Images/BackGrounds/EndingScene/EndingBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("Reminisce1", "Resources/Images/BackGrounds/EndingScene/Reminisce1.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("Reminisce2", "Resources/Images/BackGrounds/EndingScene/Reminisce2.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("Reminisce3", "Resources/Images/BackGrounds/EndingScene/Reminisce3.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("Reminisce4", "Resources/Images/BackGrounds/EndingScene/Reminisce4.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("Reminisce5", "Resources/Images/BackGrounds/EndingScene/Reminisce5.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("Reminisce6", "Resources/Images/BackGrounds/EndingScene/Reminisce6.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("Reminisce7", "Resources/Images/BackGrounds/EndingScene/Reminisce7.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("Reveal", "Resources/Images/BackGrounds/EndingScene/Reveal.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("Brother", "Resources/Images/BackGrounds/EndingScene/Brother.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("Subtitle1", "Resources/Images/BackGrounds/EndingScene/Subtitle1.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("Subtitle2", "Resources/Images/BackGrounds/EndingScene/Subtitle2.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("Subtitle3", "Resources/Images/BackGrounds/EndingScene/Subtitle3.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("Subtitle4", "Resources/Images/BackGrounds/EndingScene/Subtitle4.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("PlaySong", "Resources/Images/BackGrounds/EndingScene/PlaySong.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("Black", "Resources/Images/BackGrounds/EndingScene/Black.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("White", "Resources/Images/BackGrounds/EndingScene/White.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("Blue", "Resources/Images/Effects/SkillEffect/Blue.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addFrameImage("Pipe", "Resources/Images/BackGrounds/EndingScene/Pipe.bmp", 20, 10, 2, 1, true, RGB(168, 208, 168));
	IMAGEMANAGER->addFrameImage("SlashRight", "Resources/Images/BackGrounds/EndingScene/SlashRight.bmp", 785, 150, 5, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("MouseCursor", "Resources/Images/UI/MouseCursor.bmp", 112, 24, 7, 1, true, RGB(80, 120, 116));
	IMAGEMANAGER->addFrameImage("AttackMouseCursor", "Resources/Images/UI/AttackMouseCursor.bmp", 217, 32, 7, 1, true, RGB(80, 120, 116));
	IMAGEMANAGER->addFrameImage("EnemyMiniStatus", "Resources/Images/UI/EnemyMiniStatus.bmp", 900, 49, 15, 1, true, RGB(0, 44, 0));
	IMAGEMANAGER->addFrameImage("PlayerMiniStatus", "Resources/Images/UI/PlayerMiniStatus.bmp", 900, 49, 15, 1, true, RGB(0, 44, 0));
	IMAGEMANAGER->addFrameImage("TitleEFX4", "Resources/Images/Effects/TitleScene/TitleEFX4.bmp", 4080, 254, 16, 1, true, RGB(4, 0, 4));
	IMAGEMANAGER->addImage("test", "Resources/Images/Effects/StoryScene/test2.bmp", 201, 242, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("TitleEFX3", "Resources/Images/Effects/TitleScene/TitleEFX3.bmp", 20880, 240, 87, 1, true, RGB(4, 88, 4));
	IMAGEMANAGER->addImage("BossBattleBG", "Resources/Images/BackGrounds/BossBattleScene/BossBattleBG.bmp", 1600, 1800);
	IMAGEMANAGER->addImage("Table", "Resources/Images/BackGrounds/BossBattleScene/Table.bmp", 120, 136, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("SaladinIdleLeft", "Resources/Images/Characters/Saladin/SaladinIdleLeft.bmp", 272, 90, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SaladinIdleRight", "Resources/Images/Characters/Saladin/SaladinIdleRight.bmp", 272, 90, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SaladinIdleUp", "Resources/Images/Characters/Saladin/SaladinIdleUp.bmp", 280, 90, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SaladinIdleDown", "Resources/Images/Characters/Saladin/SaladinIdleDown.bmp", 280, 90, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SaladinAttackUp", "Resources/Images/Characters/Saladin/SaladinAttackUp.bmp", 648, 138, 6, 1, true, RGB(168, 208, 168));
	IMAGEMANAGER->addFrameImage("SaladinAttackSide", "Resources/Images/Characters/Saladin/SaladinAttackSide.bmp", 790, 176, 5, 2, true, RGB(168, 208, 168));
	IMAGEMANAGER->addFrameImage("SaladinAttackDown", "Resources/Images/Characters/Saladin/SaladinAttackDown.bmp", 505, 116, 5, 1, true, RGB(168, 208, 168));
	IMAGEMANAGER->addFrameImage("SaladinMove", "Resources/Images/Characters/Saladin/SaladinMove.bmp", 720, 480, 6, 4, true, RGB(168, 208, 168));
	IMAGEMANAGER->addFrameImage("CursorTile", "Resources/Images/UI/CursorTile.bmp", 240, 32, 6, 1);
	IMAGEMANAGER->addFrameImage("CantMoveTile", "Resources/Images/UI/CantMoveTile.bmp", 76, 42, 2, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("MovableTile", "Resources/Images/UI/MovableTile.bmp", 40, 32);
	IMAGEMANAGER->addImage("AttackableTile", "Resources/Images/UI/AttackableTile.bmp", 40, 32);
	IMAGEMANAGER->addImage("SkillableTile", "Resources/Images/UI/SkillableTile.bmp", 40, 32);
	IMAGEMANAGER->addImage("ActionButton", "Resources/Images/UI/ActionButton.bmp", 102, 28, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ActionButtonActive", "Resources/Images/UI/ActionButtonActive.bmp", 102, 28, true, RGB(255, 45, 254));
	IMAGEMANAGER->addImage("SkillIcon", "Resources/Images/UI/SkillIcon.bmp", 17, 17, true, RGB(252, 236, 248));
	IMAGEMANAGER->addImage("SkillButtonActive", "Resources/Images/UI/SkillButtonActive.bmp", 80, 22);
	IMAGEMANAGER->addImage("WorldMapInfo", "Resources/Images/UI/WorldMapInfo.bmp", 241, 111, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("WorldMapFlag", "Resources/Images/UI/WorldMapFlag.bmp", 61, 91, true, RGB(252, 252, 252));
	IMAGEMANAGER->addImage("WorldMapSaladin", "Resources/Images/UI/WorldMapSaladin.bmp", 50, 50);
	IMAGEMANAGER->addFrameImage("ActionIcon", "Resources/Images/UI/ActionIcon.bmp", 96, 25, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WorldMapMoveMarker", "Resources/Images/UI/WorldMapMoveMarker.bmp", 3360, 120, 28, 1, true, RGB(255, 45, 254));
	IMAGEMANAGER->addFrameImage("MiniStatusWindow", "Resources/Images/UI/MiniStatusWindow.bmp", 900, 49, 15, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WorldMapMarker", "Resources/Images/UI/WorldMapMarker.bmp", 1120, 120, 10, 1, true, RGB(0, 252, 0));
	IMAGEMANAGER->addImage("SaladinMark", "Resources/Images/UI/SaladinMark3.bmp", 41, 54, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("EnemyMarker", "Resources/Images/UI/EnemyMarker.bmp", 72, 11, 8, 1, true, RGB(80, 120, 116));
	IMAGEMANAGER->addFrameImage("PlayerMarker", "Resources/Images/UI/PlayerMarker.bmp", 72, 11, 8, 1, true, RGB(80, 120, 116));
	IMAGEMANAGER->addFrameImage("WorldMapTeam", "Resources/Images/UI/WorldMapTeam.bmp", 195, 18, 5, 1);
	IMAGEMANAGER->addFrameImage("VermontSherazade", "Resources/Images/BackGrounds/StoryScene/VermontSherazade.bmp", 3816, 90, 24, 1, true, RGB(168, 208, 168));
	IMAGEMANAGER->addImage("Red", "Resources/Images/BackGrounds/StoryScene/RedBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("AbandonedSwords", "Resources/Images/BackGrounds/StoryScene/AbandonedSwods.bmp", 55, 45, true, RGB(168, 208, 168));
	IMAGEMANAGER->addImage("Soldier1", "Resources/Images/BackGrounds/StoryScene/Soldier1.bmp", 58, 67, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("Soldier2", "Resources/Images/BackGrounds/StoryScene/Soldier2.bmp", 54, 69, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("Soldier3", "Resources/Images/BackGrounds/StoryScene/Soldier3.bmp", 55, 65, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("Soldier4", "Resources/Images/BackGrounds/StoryScene/Soldier4.bmp", 47, 76, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("SaladinStory", "Resources/Images/BackGrounds/StoryScene/SaladinStory.bmp", 260, 75, 4, 1, true, RGB(168, 208, 168));
	IMAGEMANAGER->addFrameImage("Enemy", "Resources/Images/Characters/Enemy.bmp", 516, 848, 6, 8, true, RGB(168, 208, 168));
	IMAGEMANAGER->addFrameImage("Nakama", "Resources/Images/Characters/Nakama.bmp", 516, 752, 6, 8, true, RGB(168, 208, 168));
	IMAGEMANAGER->addFrameImage("VermontMoveLeft", "Resources/Images/Characters/Vermont/VermontMoveLeft.bmp", 462, 76, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("VermontMoveRight", "Resources/Images/Characters/Vermont/VermontMoveRight.bmp", 462, 76, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("VermontMoveUp", "Resources/Images/Characters/Vermont/VermontMoveUp.bmp", 228, 80, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("VermontMoveDown", "Resources/Images/Characters/Vermont/VermontMoveDown.bmp", 372, 91, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("VermontIdleLeft", "Resources/Images/Characters/Vermont/VermontIdleLeft.bmp", 185, 75, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("VermontIdleRight", "Resources/Images/Characters/Vermont/VermontIdleRight.bmp", 185, 75, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("VermontIdleUp", "Resources/Images/Characters/Vermont/VermontIdleUp.bmp", 265, 87, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("VermontIdleDown", "Resources/Images/Characters/Vermont/VermontIdleDown.bmp", 245, 78, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("VermontAttackLeft", "Resources/Images/Characters/Vermont/VermontAttackLeft.bmp", 452, 118, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("VermontAttackRight", "Resources/Images/Characters/Vermont/VermontAttackRight.bmp", 452, 118, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("VermontAttackSideEffect", "Resources/Images/Effects/SkillEffect/VermontAttackSideEffect.bmp", 636, 166, 4, 2, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("VermontAttackUpEffect", "Resources/Images/Effects/SkillEffect/VermontAttackUpEffect.bmp", 548, 119, 4, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("VermontAttackDownEffect", "Resources/Images/Effects/SkillEffect/VermontAttackDownEffect.bmp", 512, 132, 4, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("VermontDamagedLeft", "Resources/Images/Characters/Vermont/VermontDamagedLeft.bmp", 65, 69, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("VermontDamagedRight", "Resources/Images/Characters/Vermont/VermontDamagedRight.bmp", 65, 69, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("VermontDamagedUp", "Resources/Images/Characters/Vermont/VermontDamagedUp.bmp", 47, 82, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("VermontDamagedDown", "Resources/Images/Characters/Vermont/VermontDamagedDown.bmp", 50, 68, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("SaladinDamagedLeft", "Resources/Images/Characters/Saladin/SaladinDamagedLeft.bmp", 67, 69, true, RGB(168, 208, 168));
	IMAGEMANAGER->addImage("SaladinDamagedRight", "Resources/Images/Characters/Saladin/SaladinDamagedRight.bmp", 67, 69, true, RGB(168, 208, 168));
	IMAGEMANAGER->addImage("SaladinDamagedUp", "Resources/Images/Characters/Saladin/SaladinDamagedUp.bmp", 47, 78, true, RGB(168, 208, 168));
	IMAGEMANAGER->addImage("SaladinDamagedDown", "Resources/Images/Characters/Saladin/SaladinDamagedDown.bmp", 79, 80, true, RGB(168, 208, 168));
	IMAGEMANAGER->addImage("VermontSkillCasting", "Resources/Images/Characters/Vermont/VermontSkillCasting.bmp", 53, 73, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("VermontSkillUp", "Resources/Images/Characters/Vermont/VermontSkillUp.bmp", 26, 131, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("VermontSkillDown", "Resources/Images/Characters/Vermont/VermontSkillDown.bmp", 32, 122, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("VermontSkillLeft", "Resources/Images/Characters/Vermont/VermontSkillLeft.bmp", 117, 63, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("VermontSkillRight", "Resources/Images/Characters/Vermont/VermontSkillRight.bmp", 117, 64, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("BattleEnd", "Resources/Images/UI/BattleEnd.bmp", WINSIZE_X, 90, true, RGB(0, 4, 4));
	IMAGEMANAGER->addImage("Scenario", "Resources/Images/UI/Scenario.bmp", 189, 35, true, RGB(8, 36, 44));
	IMAGEMANAGER->addImage("Clear", "Resources/Images/UI/Clear.bmp", 119, 36, true, RGB(8, 36, 44));
	IMAGEMANAGER->addImage("Snow", "Resources/Images/UI/Snow.bmp", 12, 12, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("Cham", "Resources/Images/Effects/SkillEffect/ǳ�ƿ�����/Cham.bmp", 6780, 235, 30, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("SaladinAttackUpEffect", "Resources/Images/Effects/SkillEffect/SaladinAttackUpEffect.bmp", 945, 163, 7, 1, true, RGB(0, 68, 0));
	IMAGEMANAGER->addFrameImage("SaladinAttackSideEffect", "Resources/Images/Effects/SkillEffect/SaladinAttackSideEffect.bmp", 1274, 288, 7, 2, true, RGB(0, 68, 0));
	IMAGEMANAGER->addFrameImage("SaladinAttackDownEffect", "Resources/Images/Effects/SkillEffect/SaladinAttackDownEffect.bmp", 945, 163, 7, 1, true, RGB(0, 68, 0));
	IMAGEMANAGER->addFrameImage("VermontSkillEFX1", "Resources/Images/Effects/SkillEffect/VermontSkillEFX1.bmp", 3069, 126, 31, 1, true, RGB(0, 92, 0));
	IMAGEMANAGER->addFrameImage("VermontSkillEFX2", "Resources/Images/Effects/SkillEffect/VermontSkillEFX2.bmp", 2755, 144, 19, 1, true, RGB(4, 176, 236));
	IMAGEMANAGER->addFrameImage("VermontSkillEFX3", "Resources/Images/Effects/SkillEffect/VermontSkillEFX3.bmp", 1768, 65, 26, 1, true, RGB(192, 196, 244));
	IMAGEMANAGER->addFrameImage("VermontSkillEFX4", "Resources/Images/Effects/SkillEffect/VermontSkillEFX4.bmp", 408, 32, 12, 1, true, RGB(232, 224, 176));
	IMAGEMANAGER->addFrameImage("VermontSkillEFX5", "Resources/Images/Effects/SkillEffect/VermontSkillEFX5.bmp", 480, 40, 12, 1, true, RGB(168, 168, 172));
	IMAGEMANAGER->addFrameImage("SkillCasting", "Resources/Images/Effects/SkillEffect/SkillCasting.bmp", 6325, 192, 25, 1, true, RGB(80, 0, 0));
	IMAGEMANAGER->addFrameImage("Volcano", "Resources/Images/Effects/SkillEffect/Saladin/Volcano.bmp", 696, 45, 12, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("CrackedEarth1RU", "Resources/Images/Effects/SkillEffect/Saladin/CrackedEarth1RU.bmp", 480, 32, 12, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("CrackedEarth2RU", "Resources/Images/Effects/SkillEffect/Saladin/CrackedEarth2RU.bmp", 480, 32, 12, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("CrackedEarth3RU", "Resources/Images/Effects/SkillEffect/Saladin/CrackedEarth3RU.bmp", 480, 32, 12, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("CrackedEarth1LU", "Resources/Images/Effects/SkillEffect/Saladin/CrackedEarth1LU.bmp", 480, 32, 12, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("CrackedEarth2LU", "Resources/Images/Effects/SkillEffect/Saladin/CrackedEarth2LU.bmp", 480, 32, 12, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("CrackedEarth3LU", "Resources/Images/Effects/SkillEffect/Saladin/CrackedEarth3LU.bmp", 480, 32, 12, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("RestoreEarth1RU", "Resources/Images/Effects/SkillEffect/Saladin/RestoreEarth1RU.bmp", 320, 32, 8, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("RestoreEarth2RU", "Resources/Images/Effects/SkillEffect/Saladin/RestoreEarth2RU.bmp", 320, 32, 8, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("RestoreEarth3RU", "Resources/Images/Effects/SkillEffect/Saladin/RestoreEarth3RU.bmp", 320, 32, 8, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("RestoreEarth1LU", "Resources/Images/Effects/SkillEffect/Saladin/RestoreEarth1LU.bmp", 320, 32, 8, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("RestoreEarth2LU", "Resources/Images/Effects/SkillEffect/Saladin/RestoreEarth2LU.bmp", 320, 32, 8, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("RestoreEarth3LU", "Resources/Images/Effects/SkillEffect/Saladin/RestoreEarth3LU.bmp", 320, 32, 8, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("Eruption1RU", "Resources/Images/Effects/SkillEffect/Saladin/Eruption1RU.bmp", 1280, 252, 32, 1, true, RGB(252, 236, 212));
	IMAGEMANAGER->addFrameImage("Eruption2RU", "Resources/Images/Effects/SkillEffect/Saladin/Eruption2RU.bmp", 1280, 252, 32, 1, true, RGB(252, 236, 212));
	IMAGEMANAGER->addFrameImage("Eruption3RU", "Resources/Images/Effects/SkillEffect/Saladin/Eruption3RU.bmp", 1200, 252, 30, 1, true, RGB(252, 236, 212));
	IMAGEMANAGER->addFrameImage("Eruption1LU", "Resources/Images/Effects/SkillEffect/Saladin/Eruption1LU.bmp", 1280, 252, 32, 1, true, RGB(252, 236, 212));
	IMAGEMANAGER->addFrameImage("Eruption2LU", "Resources/Images/Effects/SkillEffect/Saladin/Eruption2LU.bmp", 1280, 252, 32, 1, true, RGB(252, 236, 212));
	IMAGEMANAGER->addFrameImage("Eruption3LU", "Resources/Images/Effects/SkillEffect/Saladin/Eruption3LU.bmp", 1200, 252, 30, 1, true, RGB(252, 236, 212));
	IMAGEMANAGER->addFrameImage("Magma1LU", "Resources/Images/Effects/SkillEffect/Saladin/Magma1LU.bmp", 480, 230, 12, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("Magma2LU", "Resources/Images/Effects/SkillEffect/Saladin/Magma2LU.bmp", 480, 226, 12, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("Magma3LU", "Resources/Images/Effects/SkillEffect/Saladin/Magma3LU.bmp", 492, 93, 12, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("Magma1RU", "Resources/Images/Effects/SkillEffect/Saladin/Magma1RU.bmp", 480, 230, 12, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("Magma2RU", "Resources/Images/Effects/SkillEffect/Saladin/Magma2RU.bmp", 480, 226, 12, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("Magma3RU", "Resources/Images/Effects/SkillEffect/Saladin/Magma3RU.bmp", 492, 93, 12, 1, true, RGB(8, 88, 8));
	IMAGEMANAGER->addFrameImage("Explosion", "Resources/Images/Effects/SkillEffect/Saladin/Explosion.bmp", 3432, 130, 24, 1, true, RGB(4, 72, 4));
	IMAGEMANAGER->addFrameImage("Explosion2", "Resources/Images/Effects/SkillEffect/Saladin/Explosion2.bmp", 872, 131, 8, 1, true, RGB(4, 108, 0));
	IMAGEMANAGER->addFrameImage("Explosion3", "Resources/Images/Effects/SkillEffect/Saladin/Explosion3.bmp", 6804, 252, 28, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Stone1", "Resources/Images/Effects/SkillEffect/Saladin/Stone1.bmp", 210, 14, 15, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("Stone2", "Resources/Images/Effects/SkillEffect/Saladin/Stone2.bmp", 465, 30, 15, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("ShockWave", "Resources/Images/Effects/SkillEffect/Saladin/ShockWave.bmp", 6368, 157, 32, 1, true, RGB(4, 108, 0));
	IMAGEMANAGER->addFrameImage("VermontAttackUp", "Resources/Images/Characters/Vermont/VermontAttackUp.bmp", 464, 85, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("VermontAttackDown", "Resources/Images/Characters/Vermont/VermontAttackDown.bmp", 420, 104, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SaladinSkill", "Resources/Images/Characters/Saladin/SaladinSkill.bmp", 1100, 101, 11, 1, true, RGB(168, 208, 168));
	IMAGEMANAGER->addFrameImage("FireFly", "Resources/Images/Effects/StoryScene/FireFly.bmp", 6882, 249, 31, 1, true, RGB(4, 0, 4));

	SOUNDMANAGER->addSoundFMOD("Brother", "Resources/Sounds/EndingScene/Brother.mp3");
	SOUNDMANAGER->addSoundFMOD("TitleScene", "Resources/Sounds/TitleScene/TitleScene.mp3", true);
	SOUNDMANAGER->addSoundFMOD("ScenarioScene", "Resources/Sounds/ScenarioScene/ScenarioScene.mp3", true);
	SOUNDMANAGER->addSoundFMOD("ScenarioSelect", "Resources/Sounds/SoundEffect/ScenarioSelect.mp3");
	SOUNDMANAGER->addSoundFMOD("TitleButton", "Resources/Sounds/SoundEffect/TitleButton.wav");
	SOUNDMANAGER->addSoundFMOD("BreakIce", "Resources/Sounds/SoundEffect/BreakIce.wav");
	SOUNDMANAGER->addSoundFMOD("VermontSkillAttack", "Resources/Sounds/SoundEffect/VermontSkillAttack.wav");
	SOUNDMANAGER->addSoundFMOD("SkillCasting", "Resources/Sounds/SoundEffect/SkillCasting.wav");
	SOUNDMANAGER->addSoundFMOD("Blizzard","Resources/Sounds/SoundEffect/Blizzard.wav");
	SOUNDMANAGER->addSoundFMOD("Magma","Resources/Sounds/SoundEffect/Magma.wav");
	SOUNDMANAGER->addSoundFMOD("CrackedEarth","Resources/Sounds/SoundEffect/CrackedEarth.wav");
	SOUNDMANAGER->addSoundFMOD("Explosion","Resources/Sounds/SoundEffect/Explosion.wav");
	SOUNDMANAGER->addSoundFMOD("SaladinSkillStart","Resources/Sounds/SoundEffect/SaladinSkillStart.wav");

	IMAGEMANAGER->addFrameImage("StoryBG", "Resources/Images/BackGrounds/StoryScene/StoryBG.bmp", 3840, 480, 6, 1);
	SOUNDMANAGER->addSoundFMOD("Dialog0", "Resources/Sounds/StoryScene/0.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog1", "Resources/Sounds/StoryScene/1.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog2", "Resources/Sounds/StoryScene/2.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog3", "Resources/Sounds/StoryScene/3.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog4", "Resources/Sounds/StoryScene/4.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog5", "Resources/Sounds/StoryScene/5.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog6", "Resources/Sounds/StoryScene/6.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog7", "Resources/Sounds/StoryScene/7.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog8", "Resources/Sounds/StoryScene/8.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog9", "Resources/Sounds/StoryScene/9.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog10", "Resources/Sounds/StoryScene/10.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog11", "Resources/Sounds/StoryScene/11.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog12", "Resources/Sounds/StoryScene/12.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog13", "Resources/Sounds/StoryScene/13.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog14", "Resources/Sounds/StoryScene/14.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog15", "Resources/Sounds/StoryScene/15.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog16", "Resources/Sounds/StoryScene/16.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog17", "Resources/Sounds/StoryScene/17.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog18", "Resources/Sounds/StoryScene/18.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog19", "Resources/Sounds/StoryScene/19.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog20", "Resources/Sounds/StoryScene/20.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog21", "Resources/Sounds/StoryScene/21.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog22", "Resources/Sounds/StoryScene/22.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog23", "Resources/Sounds/StoryScene/23.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog24", "Resources/Sounds/StoryScene/24.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog25", "Resources/Sounds/StoryScene/25.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog26", "Resources/Sounds/StoryScene/26.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog27", "Resources/Sounds/StoryScene/27.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog28", "Resources/Sounds/StoryScene/28.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog29", "Resources/Sounds/StoryScene/29.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog30", "Resources/Sounds/StoryScene/30.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog31", "Resources/Sounds/StoryScene/31.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog32", "Resources/Sounds/StoryScene/32.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog33", "Resources/Sounds/StoryScene/33.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog34", "Resources/Sounds/StoryScene/34.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog35", "Resources/Sounds/StoryScene/35.mp3");
	SOUNDMANAGER->addSoundFMOD("Dialog36", "Resources/Sounds/StoryScene/36.mp3");
	SOUNDMANAGER->addSoundFMOD("Fight", "Resources/Sounds/StoryScene/Fight.wav");
	//SOUNDMANAGER->addWaveFileWithKey("Fight", "Resources/Sounds/StoryScene/0005.wav");
	//SOUNDMANAGER->addMp3FileWithKey("Fight", "Resources/Sounds/StoryScene/test.mp3");
	SOUNDMANAGER->addSoundFMOD("Scream1", "Resources/Sounds/StoryScene/Scream1.wav");
	SOUNDMANAGER->addSoundFMOD("Scream2", "Resources/Sounds/StoryScene/Scream2.wav");
	//SOUNDMANAGER->addSoundFMOD("SaladinAttack", "Resources/Sounds/SoundEffect/SaladinAttack.wav");
	//SOUNDMANAGER->addSoundFMOD("VermontAttack", "Resources/Sounds/SoundEffect/VermontAttack.wav");
	SOUNDMANAGER->addSoundFMOD("BossBattle", "Resources/Sounds/BossBattle/BossBattle.mp3", true);
	SOUNDMANAGER->addSoundFMOD("StageClear", "Resources/Sounds/BossBattle/StageClear.mp3");
	SOUNDMANAGER->addSoundFMOD("Conspiracy2", "Resources/Sounds/StoryScene/Conspiracy2.mp3", true);
	SOUNDMANAGER->addSoundFMOD("BeforeLastBattle", "Resources/Sounds/StoryScene/BeforeLastBattle.mp3", true);
	SOUNDMANAGER->addSoundFMOD("SherazadeDead", "Resources/Sounds/StoryScene/SherazadeDead.mp3");
	SOUNDMANAGER->addSoundFMOD("WorldMapBG", "Resources/Sounds/WorldMapScene/WorldMapBG.mp3", true);
	//DIALOGMANAGER->addDialogs("StoryScene");
	//DIALOGMANAGER->addDialogs("EndingScene");
	//DIALOGMANAGER->addDialog("EndingScene", "Vermont", "", { L"[����Ʈ]", L"�׿���..." }, )
	return S_OK;
}

void Resources::release(void)
{
}
