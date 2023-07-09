#pragma once
#include "SingletonBase.h"

struct Dialog
{
	string speaker;
	string soundKey;
	LPCWSTR* content;
	int dialongN;
	int dialogType;
};

class DialogManager : public SingletonBase<DialogManager>
{
private:
	vector<Dialog> _dialogList;
	map<string, vector<Dialog>*> _mDialogMap;

public:
	HRESULT init(void);
	void release(void);

	vector<Dialog>* addDialogs(string sceneName);
	Dialog* addDialog(string sceneName, string speaker, string soundKey, LPCWSTR* content, int dialogN, int dialogType);
	vector<Dialog>* findDialogs(string sceneName);

	DialogManager() {}
	~DialogManager() {}
};

