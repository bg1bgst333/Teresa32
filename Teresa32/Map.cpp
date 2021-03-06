// ヘッダのインクルード
// 独自のヘッダ
#include "Map.h"	// CMap
#include "BinaryResource.h"	// CBinaryResource
#include "resource.h"	// リソース.

// コンストラクタCMap
CMap::CMap() : CSharedObject(){

	// メンバの初期化.
	m_iChipWidth = 0;	// m_iChipWidthに0をセット.
	m_iChipHeight = 0;	// m_iChipHeightに0をセット.
	m_iChipCountX;	// m_iChipCountXに0をセット.
	m_iChipCountY;	// m_iChipCountYに0をセット.
	m_ppMapDataMatrix = NULL;	// m_ppMapDataMatrixにNULLをセット.
	m_bDown = FALSE;	// m_bDownにFALSEをセット.
	m_bUp = FALSE;	// m_bUpにFALSEをセット.
	m_bRight = FALSE;	// m_bRightにFALSEをセット.
	m_bLeft = FALSE;	// m_bLeftにFALSEをセット.
	m_bLoop = FALSE;	// m_bLoopにFALSEをセット.
	m_bLoopX = FALSE;	// m_bLoopXにFALSEをセット.
	m_bLoopY = FALSE;	// m_bLoopYにFALSEをセット.
	m_iCursorX = 0;	// m_iCursorXに0をセット.
	m_iCursorY = 0;	// m_iCursorYに0をセット.
	m_iPixelX = 0;	// m_iPixelXに0をセット.
	m_iPixelY = 0;	// m_iPixelYに0をセット.
	m_dwScrollTimerInterval = 0;	// m_dwScrollTimerIntervalを0で初期化.
	m_dwScrollTimerStart = 0;	// m_dwScrollTimerStartを0で初期化.

}

// コンストラクタCMap(CScene *pScene)
CMap::CMap(CScene *pScene) : CSharedObject(pScene){

	// メンバの初期化.
	m_iChipWidth = 0;	// m_iChipWidthに0をセット.
	m_iChipHeight = 0;	// m_iChipHeightに0をセット.
	m_iChipCountX;	// m_iChipCountXに0をセット.
	m_iChipCountY;	// m_iChipCountYに0をセット.
	m_ppMapDataMatrix = NULL;	// m_ppMapDataMatrixにNULLをセット.
	m_bDown = FALSE;	// m_bDownにFALSEをセット.
	m_bUp = FALSE;	// m_bUpにFALSEをセット.
	m_bRight = FALSE;	// m_bRightにFALSEをセット.
	m_bLeft = FALSE;	// m_bLeftにFALSEをセット.
	m_bLoop = FALSE;	// m_bLoopにFALSEをセット.
	m_bLoopX = FALSE;	// m_bLoopXにFALSEをセット.
	m_bLoopY = FALSE;	// m_bLoopYにFALSEをセット.
	m_iCursorX = 0;	// m_iCursorXに0をセット.
	m_iCursorY = 0;	// m_iCursorYに0をセット.
	m_iPixelX = 0;	// m_iPixelXに0をセット.
	m_iPixelY = 0;	// m_iPixelYに0をセット.
	m_dwScrollTimerInterval = 0;	// m_dwScrollTimerIntervalを0で初期化.
	m_dwScrollTimerStart = 0;	// m_dwScrollTimerStartに0をセット.

}

// デストラクタ~CMap
CMap::~CMap(){

}

// マップの作成Create.
BOOL CMap::Create(int iChipWidth, int iChipHeight, int iChipCountX, int iChipCountY){

	// メンバのセット.
	m_iChipWidth = iChipWidth;	// m_iChipWidthにiChipWidthをセット.
	m_iChipHeight = iChipHeight;	// m_iChipHeightにiChipHeightをセット.
	m_iChipCountX = iChipCountX;	// m_iChipCountXにiChipCountXをセット.
	m_iChipCountY = iChipCountY;	// m_iChipCountYにiChipCountYをセット.

	// マップ配列作成.
	m_ppMapDataMatrix = new MapData * [m_iChipCountY + 2];	// (縦方向の要素数 + 2)分newする.
	for (int i = 0; i < m_iChipCountY + 2; i++){	// (縦方向の要素数 + 2)分繰り返す.
		m_ppMapDataMatrix[i] = new MapData[m_iChipCountX + 2];	// (横方向の要素数 + 2)分newする.
		ZeroMemory(m_ppMapDataMatrix[i], sizeof(MapData) * m_iChipCountX + 2);	// ZeroMemoryでクリア.
#if 0
		m_ppMapDataMatrix[i][0].m_nID = IDB_SHARED1;	// shared1
		m_ppMapDataMatrix[i][0].m_iDestX = 0;	// 0
		m_ppMapDataMatrix[i][0].m_iDestY = i;	// i
		m_ppMapDataMatrix[i][1].m_nID = IDB_SHARED1;	// shared1
		m_ppMapDataMatrix[i][1].m_iDestX = 1;	// 1
		m_ppMapDataMatrix[i][1].m_iDestY = i;	// i
		m_ppMapDataMatrix[i][1].m_iSrcX = 1;	// 1
		m_ppMapDataMatrix[i][1].m_iSrcY = 0;	// 0
		m_ppMapDataMatrix[i][2].m_nID = IDB_SHARED1;	// shared1
		m_ppMapDataMatrix[i][2].m_iDestX = 2;	// 2
		m_ppMapDataMatrix[i][2].m_iDestY = i;	// i
		m_ppMapDataMatrix[i][2].m_iSrcX = 2;	// 2
		m_ppMapDataMatrix[i][2].m_iSrcY = 0;	// 0
#endif
	}

	// マップ配置.
	for (int y = 1; y < m_iChipCountY + 1; y++){	// 縦方向.
		for (int x = 1; x < m_iChipCountX + 1; x++){	// 横方向.
			m_ppMapDataMatrix[y][x].m_nID = IDB_SHARED1;
			if (x <= 2){
				m_ppMapDataMatrix[y][x].m_iDestX = x - 1;
				m_ppMapDataMatrix[y][x].m_iDestY = y - 1;
				m_ppMapDataMatrix[y][x].m_iSrcX = y - 1;
				m_ppMapDataMatrix[y][x].m_iSrcY = 0;
				if (y >= 11){
					m_ppMapDataMatrix[y][x].m_iSrcX = y - 11;
					m_ppMapDataMatrix[y][x].m_iSrcY = 1;
				}
			}
			else{
				m_ppMapDataMatrix[y][x].m_iDestX = x - 1;
				m_ppMapDataMatrix[y][x].m_iDestY = y - 1;
				m_ppMapDataMatrix[y][x].m_iSrcX = 0;
				m_ppMapDataMatrix[y][x].m_iSrcY = 2;
			}
		}
	}

#if 1
#if 1
	// マップをエクスポート.
	ExportFile(_T("testmap1.bin"));	// ExportFileで"testmap1.bin"をエクスポート.
#else
	// マップをインポート.
	ImportFile(_T("testmap1.bin"));	// ImportFileで"testmap1.bin"をインポート.
#endif
#endif

	// 成功なので0.
	return 0;	// 0を返す.

}

// マップの破棄Destroy.
void CMap::Destroy(){
	
	// マップ配列の破棄.
	for (int i = 0; i < m_iChipCountY + 2; i++){	// (縦方向の要素数 + 2)分繰り返す.
		delete [] m_ppMapDataMatrix[i];	// m_ppMapDataMatrix[i]を解放.
		m_ppMapDataMatrix[i] = NULL;	// m_ppMapDataMatrix[i]にNULLをセット.
	}
	delete [] m_ppMapDataMatrix;	// m_ppMapDataMatrixを解放.
	m_ppMapDataMatrix = NULL;	// m_ppMapDataMatrixにNULLをセット.

	// メンバのリセット.
	m_iChipWidth = 0;	// m_iChipWidthに0をセット.
	m_iChipHeight = 0;	// m_iChipHeightに0をセット.
	m_iChipCountX;	// m_iChipCountXに0をセット.
	m_iChipCountY;	// m_iChipCountYに0をセット.

}

// マップの描画Draw.
void CMap::Draw(){

	// ループ.
	if (m_bLoop){	// する.
		int iStartX = 0;
		int iStartY = 0;
		if (m_iCursorX == 0){
			iStartX = m_iChipCountX;
		}
		else{
			iStartX = m_iCursorX;
		}
		if (m_iCursorY == 0){
			iStartY = m_iChipCountY;
		}
		else{
			iStartY = m_iCursorY;
		}
		for (int y = 0; y < 17/*m_iChipCountY*/; y++){	// 縦方向.
			for (int x = 0; x < 22/*m_iChipCountX*/; x++){	// 横方向.
				int valx = x + iStartX;
				int valy = y + iStartY;
				if (valx > m_iChipCountX){
					valx = valx - m_iChipCountX;
				}
				if (valy > m_iChipCountY){
					valy = valy - m_iChipCountY;
				}
				HDC hMemDC = m_pScene->m_pSharedImageBuffer->Get(m_ppMapDataMatrix[valy][valx].m_nID);
				if (hMemDC == NULL){
				}
				else{
					BitBlt(m_pScene->m_hMemDC, (x - 1) * m_iChipWidth + m_iPixelX, (y - 1) * m_iChipHeight + m_iPixelY, m_iChipWidth, m_iChipHeight, hMemDC, m_ppMapDataMatrix[valy][valx].m_iSrcX * m_iChipWidth, m_ppMapDataMatrix[valy][valx].m_iSrcY * m_iChipHeight, SRCCOPY);
				}
			}
		}
	}
	else{	// しない.
		// マップ配列の描画.
		for (int y = 0; y < 17/*m_iChipCountY*/; y++){	// 縦方向.
			for (int x = 0; x < 22/*m_iChipCountX*/; x++){	// 横方向.
				HDC hMemDC = m_pScene->m_pSharedImageBuffer->Get(m_ppMapDataMatrix[y + m_iCursorY][x + m_iCursorX].m_nID);	// 指定のIDのバッファを取得.
				if (hMemDC == NULL){
					BitBlt(m_pScene->m_hMemDC, (x - 1) * m_iChipWidth + m_iPixelX, (y - 1) * m_iChipHeight + m_iPixelY, m_iChipWidth, m_iChipHeight, hMemDC, m_ppMapDataMatrix[y + m_iCursorY][x + m_iCursorX].m_iSrcX * m_iChipWidth, m_ppMapDataMatrix[y + m_iCursorY][x + m_iCursorX].m_iSrcY * m_iChipHeight, SRCCOPY);	// BitBltで描画.
				}
				else{
					BitBlt(m_pScene->m_hMemDC, (m_ppMapDataMatrix[y + m_iCursorY][x + m_iCursorX].m_iDestX - m_iCursorX) * m_iChipWidth + m_iPixelX, (m_ppMapDataMatrix[y + m_iCursorY][x + m_iCursorX].m_iDestY - m_iCursorY) * m_iChipHeight + m_iPixelY, m_iChipWidth, m_iChipHeight, hMemDC, m_ppMapDataMatrix[y + m_iCursorY][x + m_iCursorX].m_iSrcX * m_iChipWidth, m_ppMapDataMatrix[y + m_iCursorY][x + m_iCursorX].m_iSrcY * m_iChipHeight, SRCCOPY);	// BitBltで描画.
				}
			}
		}
	}

}

// マップデータをファイルとしてエクスポートExportFile.
BOOL CMap::ExportFile(LPCTSTR lpctszFileName){

	// バイナリファイルの作成.
#if 1
	CBinaryFile *pBinaryFile = new CBinaryFile();	// CBinaryFileオブジェクトpBinaryFileの生成.
	pBinaryFile->Set((BYTE *)&m_iChipWidth, sizeof(int));	// チップ幅.
	pBinaryFile->Write(lpctszFileName);	// 指定のファイルに書き込み.
	pBinaryFile->Set((BYTE *)&m_iChipHeight, sizeof(int));	// チップ高さ.
	pBinaryFile->Write();	// 先程開いたファイルに追記.
	pBinaryFile->Set((BYTE *)&m_iChipCountX, sizeof(int));	// チップ横要素数.
	pBinaryFile->Write();	// 先程開いたファイルに追記.
	pBinaryFile->Set((BYTE *)&m_iChipCountY, sizeof(int));	// チップ縦要素数.
	pBinaryFile->Write();	// 先程開いたファイルに追記.
	// マップ配列の描画.
	for (int y = 1; y < m_iChipCountY + 1; y++){	// 縦方向.
		for (int x = 1; x < m_iChipCountX + 1; x++){	// 横方向.
			pBinaryFile->Set((BYTE *)&m_ppMapDataMatrix[y][x], sizeof(MapData));	// (x, y)マップデータ.
			pBinaryFile->Write();	// 先程開いたファイルに追記.
		}
	}
#if 0
	pBinaryFile->Set((BYTE *)&m_ppMapDataMatrix[0][1], sizeof(MapData));	// (x, y) = (1, 0)のマップデータ.
	pBinaryFile->Write();	// 先程開いたファイルに追記.
	pBinaryFile->Set((BYTE *)&m_ppMapDataMatrix[1][0], sizeof(MapData));	// (x, y) = (0, 1)のマップデータ.
	pBinaryFile->Write();	// 先程開いたファイルに追記.
	pBinaryFile->Set((BYTE *)&m_ppMapDataMatrix[1][1], sizeof(MapData));	// (x, y) = (1, 1)のマップデータ.
	pBinaryFile->Write();	// 先程開いたファイルに追記.
#endif
	delete pBinaryFile;	// pBinaryFileの終了処理.
#endif
	
	// 成功ならTRUE.
	return TRUE;	// TRUEを返す.

}

// マップデータをファイルとしてインポートImportFile.
BOOL CMap::ImportFile(LPCTSTR lpctszFileName){

#if 0
	// バイナリリソースから読み込み.
	CBinaryResource *pBinaryResource = new CBinaryResource();
	pBinaryResource->Load(m_pScene->m_pMainWnd->m_hWnd, IDR_TESTMAP1, _T("BIN"));	// pBinaryResource->Loadでロード.
	m_iChipWidth = (int)(*(BYTE *)pBinaryResource->Get(sizeof(int)));
	m_iChipHeight = (int)(*(BYTE *)pBinaryResource->Get(sizeof(int)));
	m_iChipCountX = (int)(*(BYTE *)pBinaryResource->Get(sizeof(int)));
	m_iChipCountY = (int)(*(BYTE *)pBinaryResource->Get(sizeof(int)));
	// マップ配列作成.
	m_ppMapDataMatrix = new MapData * [m_iChipCountY + 2];	// (縦方向の要素数 + 2)分newする.
	for (int i = 0; i < m_iChipCountY + 2; i++){	// (縦方向の要素数 + 2)分繰り返す.
		m_ppMapDataMatrix[i] = new MapData[m_iChipCountX + 2];	// (横方向の要素数 + 2)分newする.
		ZeroMemory(m_ppMapDataMatrix[i], sizeof(MapData) * (m_iChipCountX + 2));	// ZeroMemoryでクリア.
	}
	// マップ配列にバイナリの値をセット.
	for (int y = 1; y < m_iChipCountY + 1; y++){	// 縦方向.
		for (int x = 1; x < m_iChipCountX + 1; x++){	// 横方向.
			CopyMemory(&m_ppMapDataMatrix[y][x], (MapData *)pBinaryResource->Get(sizeof(MapData)), sizeof(MapData));	// CopyMemoryでバイナリデータをコピー.
		}
	}
	// バイナリリソースオブジェクトの破棄.
	delete pBinaryResource;	// pBinaryResourceの終了処理.
#else
	// バイナリファイルから読み込み.
	CBinaryFile *pBinaryFile = new CBinaryFile();
	pBinaryFile->Read(lpctszFileName, 0, sizeof(int));	// pBinaryFile->Readで読み込み.
	m_iChipWidth = (int)*pBinaryFile->m_pBytes;	// チップ幅を取得.
	pBinaryFile->Read(sizeof(int));	// pBinaryFile->Readで読み込み.
	m_iChipHeight = (int)*pBinaryFile->m_pBytes;	// チップ高さを取得.
	pBinaryFile->Read(sizeof(int));	// pBinaryFile->Readで読み込み.
	m_iChipCountX = (int)*pBinaryFile->m_pBytes;	// チップ横要素数を取得.
	pBinaryFile->Read(sizeof(int));	// pBinaryFile->Readで読み込み.
	m_iChipCountY = (int)*pBinaryFile->m_pBytes;	// チップ縦要素数を取得.

	// マップ配列作成.
	m_ppMapDataMatrix = new MapData * [m_iChipCountY + 2];	// (縦方向の要素数 + 2)分newする.
	for (int i = 0; i < m_iChipCountY + 2; i++){	// (縦方向の要素数 + 2)分繰り返す.
		m_ppMapDataMatrix[i] = new MapData[m_iChipCountX + 2];	// (横方向の要素数 + 2)分newする.
		ZeroMemory(m_ppMapDataMatrix[i], sizeof(MapData) * (m_iChipCountX + 2));	// ZeroMemoryでクリア.
	}

	// マップ配列にバイナリの値をセット.
	for (int y = 1; y < m_iChipCountY + 1; y++){	// 縦方向.
		for (int x = 1; x < m_iChipCountX + 1; x++){	// 横方向.
			pBinaryFile->Read(sizeof(MapData));	// pBinaryFile->Readで読み込み.
			CopyMemory(&m_ppMapDataMatrix[y][x], (MapData *)pBinaryFile->m_pBytes, sizeof(MapData));	// CopyMemoryでバイナリデータをコピー.
		}
	}

	// バイナリファイルオブジェクトの破棄.
	delete pBinaryFile;	// pBinaryFileの終了処理.
#endif

	// 成功ならTRUE.
	return TRUE;	// TRUEを返す.

}

// マップデータをリソースとしてインポートImportResource.
BOOL CMap::ImportResource(int nID){

#if 1
	// バイナリリソースから読み込み.
	CBinaryResource *pBinaryResource = new CBinaryResource();
	pBinaryResource->Load(m_pScene->m_pMainWnd->m_hWnd, nID, _T("BIN"));	// pBinaryResource->Loadでロード.
	m_iChipWidth = (int)(*(BYTE *)pBinaryResource->Get(sizeof(int)));
	m_iChipHeight = (int)(*(BYTE *)pBinaryResource->Get(sizeof(int)));
	m_iChipCountX = (int)(*(BYTE *)pBinaryResource->Get(sizeof(int)));
	m_iChipCountY = (int)(*(BYTE *)pBinaryResource->Get(sizeof(int)));
	// マップ配列作成.
	m_ppMapDataMatrix = new MapData * [m_iChipCountY + 2];	// (縦方向の要素数 + 2)分newする.
	for (int i = 0; i < m_iChipCountY + 2; i++){	// (縦方向の要素数 + 2)分繰り返す.
		m_ppMapDataMatrix[i] = new MapData[m_iChipCountX + 2];	// (横方向の要素数 + 2)分newする.
		ZeroMemory(m_ppMapDataMatrix[i], sizeof(MapData) * (m_iChipCountX + 2));	// ZeroMemoryでクリア.
	}
	// マップ配列にバイナリの値をセット.
	for (int y = 1; y < m_iChipCountY + 1; y++){	// 縦方向.
		for (int x = 1; x < m_iChipCountX + 1; x++){	// 横方向.
			CopyMemory(&m_ppMapDataMatrix[y][x], (MapData *)pBinaryResource->Get(sizeof(MapData)), sizeof(MapData));	// CopyMemoryでバイナリデータをコピー.
		}
	}
	// バイナリリソースオブジェクトの破棄.
	delete pBinaryResource;	// pBinaryResourceの終了処理.
#else
	// バイナリファイルから読み込み.
	CBinaryFile *pBinaryFile = new CBinaryFile();
	pBinaryFile->Read(lpctszFileName, 0, sizeof(int));	// pBinaryFile->Readで読み込み.
	m_iChipWidth = (int)*pBinaryFile->m_pBytes;	// チップ幅を取得.
	pBinaryFile->Read(sizeof(int));	// pBinaryFile->Readで読み込み.
	m_iChipHeight = (int)*pBinaryFile->m_pBytes;	// チップ高さを取得.
	pBinaryFile->Read(sizeof(int));	// pBinaryFile->Readで読み込み.
	m_iChipCountX = (int)*pBinaryFile->m_pBytes;	// チップ横要素数を取得.
	pBinaryFile->Read(sizeof(int));	// pBinaryFile->Readで読み込み.
	m_iChipCountY = (int)*pBinaryFile->m_pBytes;	// チップ縦要素数を取得.

	// マップ配列作成.
	m_ppMapDataMatrix = new MapData * [m_iChipCountY + 2];	// (縦方向の要素数 + 2)分newする.
	for (int i = 0; i < m_iChipCountY + 2; i++){	// (縦方向の要素数 + 2)分繰り返す.
		m_ppMapDataMatrix[i] = new MapData[m_iChipCountX + 2];	// (横方向の要素数 + 2)分newする.
		ZeroMemory(m_ppMapDataMatrix[i], sizeof(MapData) * (m_iChipCountX + 2));	// ZeroMemoryでクリア.
	}

	// マップ配列にバイナリの値をセット.
	for (int y = 1; y < m_iChipCountY + 1; y++){	// 縦方向.
		for (int x = 1; x < m_iChipCountX + 1; x++){	// 横方向.
			pBinaryFile->Read(sizeof(MapData));	// pBinaryFile->Readで読み込み.
			CopyMemory(&m_ppMapDataMatrix[y][x], (MapData *)pBinaryFile->m_pBytes, sizeof(MapData));	// CopyMemoryでバイナリデータをコピー.
		}
	}

	// バイナリファイルオブジェクトの破棄.
	delete pBinaryFile;	// pBinaryFileの終了処理.
#endif

	// 成功ならTRUE.
	return TRUE;	// TRUEを返す.

}

// マップの移動状態をクリア.
void CMap::Clear(){

	// フラグをクリア.
	m_bDown = FALSE;	// m_bDownをFALSEにする.
	m_bUp = FALSE;	// m_bUpをFALSEにする.
	m_bRight = FALSE;	// m_bRightをFALSEにする.
	m_bLeft = FALSE;	// m_bLeftをFALSEにする.

}

// マップの視点を下に移動Down.(マップ自体は上に移動.)
void CMap::Down(){

	// 下が有効.
	m_bDown = TRUE;	// m_bDownをTRUEにする.

}

// マップの視点を上に移動Up.(マップ自体は下に移動.)
void CMap::Up(){

	// 上が有効.
	m_bUp = TRUE;	// m_bUpをTRUEにする.

}

// マップの視点を右に移動Right.(マップ自体は左に移動.)
void CMap::Right(){

	// 右が有効.
	m_bRight = TRUE;	// m_bRightをTRUEにする.

}

// マップの視点を左に移動Ledt.(マップ自体は右に移動.)
void CMap::Left(){

	// 左が有効.
	m_bLeft =TRUE;	// m_bLeftをTRUEにする.

}

// 処理をするProc.
int CMap::Proc(){

	// ループ.
	if (m_bLoop){	// する.

#if 1
		// 自動スクロール.
		if (IsScrollElapsed()){
			//m_iCursorY--;
			if (m_bLoopY){
				m_iPixelY = m_iPixelY + 1;	// yを1増やす.
			}
			else{
				if (!(m_iCursorY == 0 && m_iPixelY >= 0)){
					m_iPixelY = m_iPixelY + 1;	// yを1増やす.
				}
			}
		}
#else
		// 手動スクロール.
		// 下.
		if (m_bDown){
			//m_iCursorY++;
			if (m_bLoopY){
				m_iPixelY--;
			}
			else{
				if (!(m_iCursorY == m_iChipCountY - 15 && m_iPixelY <= 0)){
					m_iPixelY--;	// yを1増やす.
				}
			}
		}
		// 上.
		if (m_bUp){
			//m_iCursorY--;
			if (m_bLoopY){
				m_iPixelY++;
			}
			else{
				if (!(m_iCursorY == 0 && m_iPixelY >= 0)){
					m_iPixelY++;	// yを1増やす.
				}
			}
		}
		// 右.
		if (m_bRight){
			//m_iCursorX++;
			if (m_bLoopX){
				m_iPixelX--;
			}
			else{
				if (!(m_iCursorX == m_iChipCountX - 20 && m_iPixelX <= 0)){
					m_iPixelX--;	// yを1増やす.
				}
			}
		}
		// 左.
		if (m_bLeft){
			//m_iCursorX--;
			if (m_bLoopX){
				m_iPixelX++;
			}
			else{
				if (!(m_iCursorX == 0 && m_iPixelX >= 0)){
					m_iPixelX++;	// xを1増やす.
				}
			}
		}
#endif

		// ピクセルの処理.
		if (m_iPixelY <= (-1 * m_iChipHeight) + 1){
			m_iPixelY = 0;	// 0
			m_iCursorY++;	// 1増える.
		}
		if (m_iPixelX <= (-1 * m_iChipWidth) + 1){
			m_iPixelX = 0;	// 0
			m_iCursorX++;	// 1増える.
		}
		if (m_iPixelY >= m_iChipHeight){
			m_iPixelY = 0;	// 0
			m_iCursorY--;	// 1減らす.
		}
		if (m_iPixelX >= m_iChipWidth){
			m_iPixelX = 0;	// 0
			m_iCursorX--;	// 1減らす.
		}

		// m_iCursorYが0未満なら.
		if (m_iCursorY < 0){
			m_iCursorY = m_iChipCountY - 1;
		}
		// m_iCursorYがm_iChipCountY - 1を超える.
		if (m_iCursorY > m_iChipCountY - 1){
			m_iCursorY = 0;
		}
		// m_iCursorXが0未満なら.
		if (m_iCursorX < 0){
			m_iCursorX = m_iChipCountX - 1;
		}
		// m_iCursorXがm_iChipCountX - 1を超える.
		if (m_iCursorX > m_iChipCountX - 1){
			m_iCursorX = 0;
		}

	}
	else{	// しない.
		// 下.
		if (m_bDown){
			//m_iCursorY++;	// yを1増やす.
			if (!(m_iCursorY == m_iChipCountY - 15 && m_iPixelY <= 0)){
				m_iPixelY--;	// yを1増やす.
			}
		}

		// 上.
		if (m_bUp){
			//m_iCursorY--;	// yを1減らす.
			if (!(m_iCursorY == 0 && m_iPixelY >= 0)){
				m_iPixelY++;	// yを1増やす.
			}
		}

		// 右.
		if (m_bRight){
			//m_iCursorX++;	// xを1増やす.
			if (!(m_iCursorX == m_iChipCountX - 20 && m_iPixelX <= 0)){
				m_iPixelX--;	// yを1増やす.
			}
		}

		// 左.
		if (m_bLeft){
			//m_iCursorX--;	// xを1減らす.
			if (!(m_iCursorX == 0 && m_iPixelX >= 0)){
				m_iPixelX++;	// xを1増やす.
			}
		}

		// ピクセルの処理.
		if (m_iPixelY <= (-1 * m_iChipHeight) + 1){
			m_iPixelY = 0;	// 0
			m_iCursorY++;	// 1増える.
		}
		if (m_iPixelX <= (-1 * m_iChipWidth) + 1){
			m_iPixelX = 0;	// 0
			m_iCursorX++;	// 1増える.
		}
		if (m_iPixelY >= m_iChipHeight){
			m_iPixelY = 0;	// 0
			m_iCursorY--;	// 1減らす.
		}
		if (m_iPixelX >= m_iChipWidth){
			m_iPixelX = 0;	// 0
			m_iCursorX--;	// 1減らす.
		}

		// カーソル最小値最大値を超えないようにする.
		if (m_iCursorX < 0){	// 0未満.
			m_iCursorX = 0;	// 0にする.
		}
		if (m_iCursorY < 0){	// 0未満.
			m_iCursorY = 0;	// 0にする.
		}
		if (m_iCursorX > m_iChipCountX - 20){	// m_iChipCountX - 20を超える.
			m_iCursorX = m_iChipCountX - 20;	// m_iChipCountX - 20にする.
		}
		if (m_iCursorY > m_iChipCountY - 15){	// m_iChipCountY - 15を超える.
			m_iCursorY = m_iChipCountY - 15;	// m_iChipCountY - 15にする.
		}
	}

	// シーン継続なら0.
	return 0;	// 0を返す.

}

// スクロールタイマーのセットSetScrollTimer.
void CMap::SetScrollTimer(DWORD dwInterval){

	// スクロールタイマーインターバルのセット.
	m_dwScrollTimerInterval = dwInterval;	// m_dwScrollTimerIntervalにdwIntervalをセット.

	// タイマーのセット.
	const CScene *pScene = m_pScene;	// m_pSceneをpSceneに格納.
	CGameTime *pTime = pScene->m_pGameTime;	// pScene->m_pGameTimeをpTimeに格納.
	m_dwScrollTimerStart = pTime->GetSystemTime();	// pTime->GetSystemTimeで取得した時刻をm_dwScrollTimerStartに格納.

}

// スクロールタイマーが経過時間を過ぎたかをチェックIsScrollElapsed.
BOOL CMap::IsScrollElapsed(){

	// 現在時刻の取得.
	const CScene *pScene = m_pScene;	// m_pSceneをpSceneに格納.
	CGameTime *pTime = pScene->m_pGameTime;	// pScene->m_pGameTimeをpTimeに格納.
	DWORD dwNow = pTime->GetSystemTime();	// pTime->GetSystemTimeで取得した時刻をdwNowに格納.

	// 経過時間チェック.
	if (dwNow - m_dwScrollTimerStart >= m_dwScrollTimerInterval){	// m_dwScrollTimerInterval以上なら.
		m_dwScrollTimerStart = dwNow;	// dwNowをm_dwScrollTimerStartにセット.
		return TRUE;	// TRUEを返す.
	}
	else{
		return FALSE;	// FALSEを返す.
	}

}
