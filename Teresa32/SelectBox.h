// 二重インクルード防止
#ifndef __SELECT_BOX_H__
#define __SELECT_BOX_H__

// ヘッダのインクルード
// 既定のヘッダ
#include <string>	// std::string
#include <vector>	// std::vector

// 独自のヘッダ
#include "GameObject.h"	// CGameObject

// マクロの定義
// UNICODE切り替え
#ifdef UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

// セレクトボックスクラスCSelectBox
class CSelectBox : public CGameObject{

	// publicメンバ
	public:

		// publicメンバ変数
		HDC m_hBackgroundMemDC;	// 背景メモリデバイスコンテキストm_hBackgroundMemDC.
		HBITMAP m_hBackgroundBitmap;	// ロードした背景ビットマップm_hBackgroundBitmap.
		HBITMAP m_hOldBackgroundBitmap;	// 以前の背景ビットマップm_hOldBackgroundBitmap.
		HFONT m_hFont;	// フォントm_hFont.
		HFONT m_hOldFont;	// 以前のフォントm_hOldFont.
		int m_iLineHeight;	// 行の高さm_iLineHeight.
		int m_iMargin;	// 行の間隔m_iMargin.
		HDC m_hCursorMemDC;	// カーソルメモリデバイスコンテキストm_hCursorMemDC.
		HBITMAP m_hCursorBitmap;	// ロードしたカーソルビットマップm_hCursorBitmap.
		HBITMAP m_hOldCursorBitmap;	// 以前のカーソルビットマップm_hOldCursorBitmap.
		int m_iCursorX;	// カーソルのx座標m_iCursorX.
		int m_iCursorY;	// カーソルのy座標m_iCursorY.
		int m_iCursorWidth;	// カーソルの幅m_iCursorWidth.
		int m_iCursorHeight;	// カーソルの高さm_iCursorHeight.
		int m_iCursorIndex;	// カーソルインデックスm_iCursorIndex.
		BOOL m_bCursorVisible;	// カーソルの表示状態m_bCursorVisible.
		BOOL m_bDown;	// 下が押されているフラグm_bDown.
		BOOL m_bUp;	// 上が押されているフラグm_bUp.
		BOOL m_bReturn;	// リターンが押されているフラグm_bReturn.
		BOOL m_bDetermine;	// 確定状態かどうかフラグm_bDetermine.
		DWORD m_dwFlashInterval;	// フラッシュタイマー間隔m_dwFlashInterval.
		DWORD m_dwFlashTimerStart;	// フラッシュタイマー開始時刻m_dwFlashTimerStart.
		DWORD m_dwDetermineInterval;	// 確定タイマー間隔m_dwDetermineInterval.
		DWORD m_dwDetermineTimerStart;	// 確定タイマー開始時刻m_dwDetermineTimerStart.
		std::vector<tstring> m_vectstrSelectItemList;	// セレクトアイテムリストm_vectstrSelectItemList.

		// publicメンバ関数
		// コンストラクタ・デストラクタ
		CSelectBox();	// コンストラクタCSelectBox()
		CSelectBox(const CScene *pScene);	// コンストラクタCSelectBox(const CScene *pScene)
		virtual ~CSelectBox();	// デストラクタ~CSelectBox()
		// メンバ関数
		virtual BOOL Create(int x, int y, int iWidth, int iHeight, HWND hWnd, UINT nID, int nFontSize, LPCTSTR lpctszFontName, int iMargin, int iCursorWidth, int iCursorHeight, UINT nCursorID);	// ゲームオブジェクトの作成Create.(指定されたリソースIDの画像をロード.)
		virtual void Destroy();	// ゲームオブジェクトの破棄Destroy.
		virtual void AddSelectItem(tstring tstrSelectItem);	// セレクトアイテムの追加AddSelectItem.
		virtual void ClearSelectItem();	// セレクトアイテムのクリアClearSelectItem.
		virtual void DrawRect(int x, int y);	// ゲームオブジェクトの描画DrawRect.
		virtual void DrawSelectItemList(int x, int y, COLORREF clrColor);	// セレクトアイテムリストの描画DrawSelectItemList.
		virtual void DrawCursor(int x, int y);	// カーソルの描画DrawCursor.
		virtual void ClearInput();	// 入力クリア.
		virtual void Down();	// カーソルを下に移動Down.
		virtual void Up();	// カーソルを上に移動Up.
		virtual void Return();	// 決定Return.
		virtual int Proc();	// 処理をするProc.
		virtual void SetFlashTimer(DWORD dwInterval);	// フラッシュタイマーのセットSetFlashTimer.
		virtual BOOL IsFlashElapsed();	// フラッシュタイマーが経過時間を過ぎたかをチェックIsFlashElapsed.
		virtual void SetDetermineTimer(DWORD dwInterval);	// 確定タイマーのセットSetDetermineTimer.
		virtual BOOL IsDetermineElapsed();	// 確定タイマーが経過時間を過ぎたかをチェックIsDetermineElapsed.

};

#endif