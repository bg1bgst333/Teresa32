// �w�b�_�̃C���N���[�h
// �Ǝ��̃w�b�_
#include "GameTime.h"	// CGameTime

// �R���X�g���N�^CGameTime
CGameTime::CGameTime(){

	// �����o�̏�����.
	m_dwMilliTime = 0;	// m_dwMilliTime��0�ŏ�����.
	m_dwUserMilliTime = 0;	// m_dwUserMilliTime��0�ŏ�����.
	m_dwUserStartMilliTime = 0;	// m_dwUserStartMilliTime��0�ŏ�����.
	m_dwFrameIntervalMilliTime = 0;	// m_dwFrameIntervalMilliTime��0�ŏ�����.
	m_dwFrameIntervalStart = 0;	// m_dwFrameIntervalStart��0�ŏ�����.
	m_dwFrame = 0;	// m_dwFrame��0�ŏ�����.
	m_dwRunFrame = 0;	// m_dwRunFrame��0�ŏ�����.
	m_dwFrameStartMilliTime = 0;	// m_dwFrameStartMilliTime��0�ŏ�����.
	m_dwFPS = 0;	// m_dwFPS��0�ŏ�����.
	m_dwTargetFPS = 0;	// m_dwTargetFPS��0�ŏ�����.
	m_dwRunFPS = 0;	// m_dwRunFPS��0�ŏ�����.

}

// �f�X�g���N�^~CGameTime
CGameTime::~CGameTime(){

	// �����o�̏I������.
	m_dwMilliTime = 0;	// m_dwMilliTime��0�ɃZ�b�g.
	m_dwUserMilliTime = 0;	// m_dwUserMilliTime��0�ŏ�����.
	m_dwUserStartMilliTime = 0;	// m_dwUserStartMilliTime��0�ŏ�����.
	m_dwFrameIntervalMilliTime = 0;	// m_dwFrameIntervalMilliTime��0�ŏ�����.
	m_dwFrameIntervalStart = 0;	// m_dwFrameIntervalStart��0�ŏ�����.
	m_dwFrame = 0;	// m_dwFrame��0�ŏ�����.
	m_dwRunFrame = 0;	// m_dwRunFrame��0�ŏ�����.
	m_dwFrameStartMilliTime = 0;	// m_dwFrameStartMilliTime��0�ŏ�����.
	m_dwFPS = 0;	// m_dwFPS��0�ŏ�����.
	m_dwTargetFPS = 0;	// m_dwTargetFPS��0�ŏ�����.
	m_dwRunFPS = 0;	// m_dwRunFPS��0�ŏ�����.

}

// �V�X�e���������~���b�ŕԂ�GetSystemTime.
DWORD CGameTime::GetSystemTime(){

	// �V�X�e��������Ԃ�.
	m_dwMilliTime = timeGetTime();	// timeGetTime�̒l��m_dwMilliTime�Ɋi�[.
	return m_dwMilliTime;	// m_dwMilliTime��Ԃ�.

}

// ���[�U�������~���b�ŕԂ�GetUserTime.
DWORD CGameTime::GetUserTime(){

	// ���[�U������Ԃ�.
	m_dwUserMilliTime = GetSystemTime() - m_dwUserStartMilliTime;	// GetSystemTime() - m_dwUserStartMilliTime�Ń��[�U�^�C���Z�o.
	return m_dwUserMilliTime;	// m_dwUserMilliTime��Ԃ�.

}

// ���[�U�����̃��Z�b�gResetUserTime.
void CGameTime::ResetUserTime(){

	// �X�^�[�g���������ݎ����ɂ���.
	m_dwUserStartMilliTime = GetSystemTime();	// m_dwUserStartMilliTime��GetSystemTime()�̒l���Z�b�g.

}

// �t���[�����̃J�E���gCountFrame.
void CGameTime::CountFrame(){

	// �t���[�����̃J�E���g.
	m_dwFrame++;	// m_dwFrame���C���N�������g.

}

// �t���[�����̃��Z�b�gResetFrame.
void CGameTime::ResetFrame(){

	// �t���[�����̃��Z�b�g.
	m_dwFrame = 0;	// m_dwFrame��0�Ƀ��Z�b�g.
	m_dwFrameStartMilliTime = GetUserTime();	// m_dwFrameStartMilliTime��GetUserTime�̒l���Z�b�g.
	m_dwRunFrame = 0;	// m_dwRunFrme��0�Ƀ��Z�b�g.

}

// 1�b�o�߂������ǂ���IsNextSecond.
BOOL CGameTime::IsNextSecond(){

	// �t���[���Ԋu�擾.
	BOOL bRet = FALSE;	// �߂�lbRet.
	DWORD dwUserTime = GetUserTime();	// ���[�U�����擾.
	// 1�b�o�߂������`�F�b�N.
	if (dwUserTime - m_dwFrameStartMilliTime >= 1000){	// 1�b�ȏ㍷����������.
		m_dwFPS = m_dwFrame;	// m_dwFPS��m_dwFrame����.
		m_dwRunFPS = m_dwRunFrame;	// m_dwRunFPS��m_dwRunFrame����.
		bRet = TRUE;	// TRUE��Ԃ�.
	}
	else{
		bRet = FALSE;	// FALSE��Ԃ�.
	}
	m_dwFrameIntervalMilliTime = dwUserTime - m_dwFrameIntervalStart;	// ���ݎ�������t���[���Ԋu�J�n�b������.
	DWORD dwSleep = 1000 / m_dwTargetFPS;	// Sleep�~���b���v�Z.
	m_dwFrameIntervalStart = dwUserTime;	// ���ݎ����ɍX�V.
	if (m_dwFrameIntervalMilliTime <= dwSleep){	// Sleep���Ԋu���������ꍇ.
		Sleep(dwSleep - m_dwFrameIntervalMilliTime);	// �X���[�v.(�X���[�v���Ԃ���t���[���Ԋu������������.)
	}
	return bRet;	// bRet��Ԃ�.

}

// FPS�l�̎擾GetFPS.
DWORD CGameTime::GetFPS(){

	// FPS��Ԃ�.
	return m_dwFPS;	// m_dwFPS��Ԃ�.

}

// ���sFPS�l�̎擾GetRunFPS.
DWORD CGameTime::GetRunFPS(){

	// ���sFPS��Ԃ�.
	return m_dwRunFPS;	// m_dwRunFPS��Ԃ�.

}

// �t���[���Ԋu���擾GetFrameIntervalMilliTime.
DWORD CGameTime::GetFrameIntervalMilliTime(){

	// �t���[���Ԋu��Ԃ�.
	return m_dwFrameIntervalMilliTime;

}

// �ڕWFPS�l�̐ݒ�SetTargetFPS.
void CGameTime::SetTargetFPS(DWORD dwTargetFPS){

	// �����o�ɃZ�b�g.
	m_dwTargetFPS = dwTargetFPS;	// m_dwTargetFPS��dwTargetFPS���Z�b�g.

}

// �������邩�ǂ����𔻒�IsProc.
BOOL CGameTime::IsProc(){

	// 1�̃t���[���ȊO�͏��������Ȃ��悤�ɂ���.
	DWORD dwNowFrame = m_dwFPS / m_dwTargetFPS;	// ���ݗ]�v�Ȃ��̂��܂߂��t���[����dwNowFrame.
	if (m_dwFPS <= m_dwTargetFPS){	// FPS�����Ȃ��ꍇ��TRUE�Ƃ��ď������܂킷.
		m_dwRunFrame++;	// m_dwRunFrame���C���N�������g.
		return TRUE;	// TRUE��Ԃ�.
	}
	if ((m_dwFrame % dwNowFrame) == 0){	// dwNowFrame�̎�������������.
		m_dwRunFrame++;	// m_dwRunFrame���C���N�������g.
		return TRUE;	// TRUE��Ԃ�.
	}
	else{
		return FALSE;	// FALSE��Ԃ�.
	}

}