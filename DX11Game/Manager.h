//=============================================================================
//
// �}�l�[�W���[ [Manager.h]
// Author : ISAKI SUGIURA
//
//=============================================================================
#pragma once

//����������������������������������������
// �v���g�^�C�v�錾
//����������������������������������������
// �X�N���[�����W�ł̃E�B���h�E�̍���ƉE���̍��W��Ԃ�
XMFLOAT4 GetWindowTLBR();
// �E�B���h�E�̏c�A�������擾����
XMFLOAT2 GetWindowSize();
// �}�E�X�J�[�\���\���ؑ�
void SetShowCursor(bool show);
// �}�E�X���E�B���h�E�̒��S�ɌŒ肷��
void SetMouseMiddlePos();
// �}�E�X�̃X�N���[�����W���擾
XMFLOAT2 GetMouseScreenPos();
// �}�E�X�̃N���C�A���g���W���擾
XMFLOAT2 GetMouseClientPos();
// �}�E�X�̈ړ��ʂ��擾����
XMFLOAT2 GetMouseMovement();

