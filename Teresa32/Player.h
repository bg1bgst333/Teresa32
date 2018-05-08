// ��d�C���N���[�h�h�~
#ifndef __PLAYER_H__
#define __PLAYER_H__

// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "Character.h"	// CCharacter

// �v���C���[�N���XCPlayer
class CPlayer : public CCharacter{

	// public�����o
	public:

		// public�����o�ϐ�
		BOOL m_bDown;	// ����������Ă���t���Om_bDown.
		BOOL m_bUp;	// �オ������Ă���t���Om_bUp.
		BOOL m_bRight;	// �E��������Ă���t���Om_bRight.
		BOOL m_bLeft;	// ����������Ă���t���Om_bLeft.
		int m_iNo;	// �A�j���[�V�����ԍ�m_iNo.

		// public�����o�֐�
		// �R���X�g���N�^�E�f�X�g���N�^
		CPlayer();	// �R���X�g���N�^CPlayer
		CPlayer(CScene *pScene);	// �f�X�g���N�^CPlayer(CScene *pScene)
		virtual ~CPlayer();	// �f�X�g���N�^~CPlayer()
		virtual void Clear();	// �}�b�v�̈ړ���Ԃ��N���A.
		virtual void Down();	// �}�b�v�̎��_�����Ɉړ�Down.(�}�b�v���̂͏�Ɉړ�.)
		virtual void Up();	// �}�b�v�̎��_����Ɉړ�Up.(�}�b�v���͉̂��Ɉړ�.)
		virtual void Right();	// �}�b�v�̎��_���E�Ɉړ�Right.(�}�b�v���͍̂��Ɉړ�.)
		virtual void Left();	// �}�b�v�̎��_�����Ɉړ�Ledt.(�}�b�v���͉̂E�Ɉړ�.))
		virtual int Proc();	// ����������Proc.
		virtual void Set(int x, int y);	// �ʒu���Z�b�g����Set.
		virtual void Set(int iNo);	// �A�j���[�V�������Z�b�g����Set.
		virtual void Draw();	// �`�������Draw.

};

#endif