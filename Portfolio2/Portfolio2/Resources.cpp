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

	IMAGEMANAGER->addImage("TextBox", "Resources/Images/UI/TextBox.bmp", 230, 105);
	IMAGEMANAGER->addImage("Vermont", "Resources/Images/UI/Vermont.bmp", 260, 480, true, RGB(0, 0, 4));
	IMAGEMANAGER->addImage("Saladin", "Resources/Images/UI/Saladin.bmp", 400, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Sherazade", "Resources/Images/UI/Sherazade.bmp", 424, 480, true, RGB(255, 0, 255 ));
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
	IMAGEMANAGER->addFrameImage("Pipe", "Resources/Images/BackGrounds/EndingScene/Pipe.bmp", 20, 10, 2, 1, true, RGB(168, 208, 168));
	IMAGEMANAGER->addFrameImage("SlashRight", "Resources/Images/BackGrounds/EndingScene/SlashRight.bmp", 785, 150, 5, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("MouseCursor", "Resources/Images/UI/MouseCursor.bmp", 112, 24, 7, 1, true, RGB(80, 120, 116));
	IMAGEMANAGER->addFrameImage("TitleEFX4", "Resources/Images/Effects/TitleScene/TitleEFX4.bmp", 4080, 254, 16, 1, true, RGB(4, 0, 4));
	IMAGEMANAGER->addFrameImage("TitleEFX3", "Resources/Images/Effects/TitleScene/TitleEFX3.bmp", 20880, 240, 87, 1, true, RGB(4, 88, 4));
	IMAGEMANAGER->addImage("BossBattleBG", "Resources/Images/BackGrounds/BossBattleScene/BossBattleBG.bmp", 1600, 1800);
	IMAGEMANAGER->addImage("Table", "Resources/Images/BackGrounds/BossBattleScene/Table.bmp", 120, 136, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("SaladinIdleLeft", "Resources/Images/Characters/Saladin/SaladinIdleLeft.bmp", 272, 90, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SaladinIdleRight", "Resources/Images/Characters/Saladin/SaladinIdleRight.bmp", 272, 90, 4, 1, true, RGB(252, 0, 255));
	IMAGEMANAGER->addFrameImage("SaladinIdleUp", "Resources/Images/Characters/Saladin/SaladinIdleUp.bmp", 280, 90, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SaladinIdleDown", "Resources/Images/Characters/Saladin/SaladinIdleDown.bmp", 280, 90, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("CursorTile", "Resources/Images/UI/CursorTile.bmp", 240, 32, 6, 1);
	IMAGEMANAGER->addFrameImage("CantMoveTile", "Resources/Images/UI/CantMoveTile.bmp", 76, 42, 2, 1);
	IMAGEMANAGER->addImage("MoveAbleTile", "Resources/Images/UI/MoveAbleTile.bmp", 40, 32);
	IMAGEMANAGER->addFrameImage("VermontSherazade", "Resources/Images/BackGrounds/StoryScene/VermontSherazade.bmp", 3816, 90, 24, 1, true, RGB(168, 208, 168));
	IMAGEMANAGER->addImage("Red", "Resources/Images/BackGrounds/StoryScene/RedBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("AbandonedSwords", "Resources/Images/BackGrounds/StoryScene/AbandonedSwods.bmp", 55, 45, true, RGB(168, 208, 168));
	IMAGEMANAGER->addImage("SherazadeDead", "Resources/Images/BackGrounds/StoryScene/AbandonedSwods.bmp", 55, 45, true, RGB(168, 208, 168));
	IMAGEMANAGER->addFrameImage("SaladinStory", "Resources/Images/BackGrounds/StoryScene/SaladinStory.bmp", 260, 75, 4, 1, true, RGB(168, 208, 168));

	SOUNDMANAGER->addSoundFMOD("Brother", "Resources/Sounds/EndingScene/Brother.mp3");
	SOUNDMANAGER->addSoundFMOD("TitleScene", "Resources/Sounds/TitleScene/TitleScene.mp3");
	SOUNDMANAGER->addSoundFMOD("ScenarioScene", "Resources/Sounds/ScenarioScene/ScenarioScene.mp3");
	SOUNDMANAGER->addSoundFMOD("ScenarioSelect", "Resources/Sounds/SoundEffect/ScenarioSelect.mp3");
	SOUNDMANAGER->addSoundFMOD("TitleButton", "Resources/Sounds/SoundEffect/TitleButton.wav");

	IMAGEMANAGER->addFrameImage("StoryBG", "Resources/Images/BackGrounds/StoryScene/StoryBG.bmp", 2560, 480, 4, 1);
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
	SOUNDMANAGER->addSoundFMOD("BossBattle", "Resources/Sounds/BossBattle/BossBattle.mp3");
	//DIALOGMANAGER->addDialogs("StoryScene");
	//DIALOGMANAGER->addDialogs("EndingScene");
	//DIALOGMANAGER->addDialog("EndingScene", "Vermont", "", { L"[버몬트]", L"죽여라..." }, )
	return S_OK;
}

void Resources::release(void)
{
}
