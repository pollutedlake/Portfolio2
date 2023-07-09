#include "Stdafx.h"
#include "DialogManager.h"

HRESULT DialogManager::init(void)
{
	return S_OK;
}

void DialogManager::release(void)
{
}

vector<Dialog>* DialogManager::addDialogs(string sceneName)
{
	vector<Dialog>* dialogs = findDialogs(sceneName);
	if(dialogs) return dialogs;

	_mDialogMap.insert(make_pair(sceneName, dialogs));
	return dialogs;
}

Dialog* DialogManager::addDialog(string sceneName, string speaker, string soundKey, LPCWSTR* content, int dialogN, int dialogType)
{
	vector<Dialog>* dialogs = findDialogs(sceneName);
	Dialog dialog;
	if (dialogs)
	{
		dialog.speaker = speaker;
		dialog.dialongN = dialogN;
		dialog.dialogType = dialogType;
		dialog.content = content;
		dialog.soundKey = soundKey;
		dialogs->push_back(dialog);
		return &dialog;
	}
	return NULL;
}

vector<Dialog>* DialogManager::findDialogs(string sceneName)
{
	auto key = _mDialogMap.find(sceneName);
	if (key != _mDialogMap.end())
	{
		return key->second;
	}
	return nullptr;
}


