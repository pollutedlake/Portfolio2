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
	IMAGEMANAGER->addImage("Saladin", "Resources/Images/UI/Saladin.bmp", 400, 480, true, RGB(0, 0, 4));
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

	SOUNDMANAGER->addSoundFMOD("Brother", "Resources/Sounds/EndingScene/Brother.mp3");
	SOUNDMANAGER->addSoundFMOD("TitleScene", "Resources/Sounds/TitleScene/TitleScene.mp3");
	SOUNDMANAGER->addSoundFMOD("ScenarioScene", "Resources/Sounds/ScenarioScene/ScenarioScene.mp3");
	SOUNDMANAGER->addSoundFMOD("ScenarioSelect", "Resources/Sounds/SoundEffect/ScenarioSelect.mp3");
	SOUNDMANAGER->addSoundFMOD("TitleButton", "Resources/Sounds/SoundEffect/TitleButton.wav");
	return S_OK;
}

void Resources::release(void)
{
}
