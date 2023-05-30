//=============================================================================
//
// �^�C�g����� [Title.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once
#include "Scene.h"
#include "TitleLogo.h"
#include "StartButton.h"
#include "ExitButton.h"
#include "MouseCursor.h"
#include "GameCamera.h"

//����������������������������������������
// �񋓌^
//����������������������������������������
enum EButtonTitle
{
	START_BUTTON = 0,
	EXIT_BUTTON,

	MAX_BUTTON_TITLE
};

//����������������������������������������
// �^�C�g����� �N���X
//����������������������������������������
class CTitle : public CScene
{
private:
	int m_iEnemy;	// �I�𒆂̓G���������o���Ă���
	int m_iButtonID;

	CGameCamera m_camera;

	CTitleLogo* m_pTitleLogo;
	CStartButton* m_pStartButton;
	CExitButton* m_pExitButton;
	CMouseCursor* m_pMouseCursor;

public:
	//����������������������������������������
	// ��{
	//����������������������������������������
	CTitle();
	virtual ~CTitle();

	bool Init();
	void Fin();
	void Update();
	void Draw();
};
