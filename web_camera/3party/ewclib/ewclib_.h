// Easy Web Camera LIBrary "ewclib.h"  by I.N.
// OS:Windows XP/Vista/7/8
// Compiler:Visual C++ 2008 Professional / 2010~+qedit.h

// 2010/04/15 ver.1.9 EWC_GetLastMessage():Unicode/マルチバイトの両対応化
// 2010/05/04         開始
// 2010/05/06         EWC_Open()/EWC_Close()仕様変更．
// 2010/05/06         EWC_Run()/EWC_Stop()追加．
// 2010/05/08         EWC_CloseAll()追加．
// 2010/05/13 ver.2.0 完成
// 2012/02/28 ver.2.1 メモリ解放時のメモリリークを修正
// 2014/01            最大カメラ数変更(8->10), @device:swも対象とする
// 2014/01            物理デバイス使用済みフラグ,EWC_GetFormat()追加
// 2014/01            EWC_Open():FriendlyName指定,デフォルト値追加
// 2014/01/17 ver.2.2 EWC_Open()のバリエーション追加,EWC_GetDeviceName()追加
// 2014/01/27         デバイス出力ピンのフォーマット指定の機能を追加
// 2014/01/27         フォーマット一覧を取得するサンプルの修正
// 2014/01/27         EWC_Open()引数追加,ewc_type,ewc_device_type(EWC_DEVICE_TYPE)追加
// 2014/01/27 ver.2.3 EWC_GetDeviceSubtype(),EWC_GetSubtype(),EWC_GUIDtoTEXT()を追加
// 2014/04/08         ewc_s[].count追加,EWC_Pause()追加,EWC_OneShot()追加
// 2014/04/22 ver.2.4 EWC_SaveProperty(),EWC_LoadProperty(),EWC_SetManual()追加

// 元のewclib.hはヘッダに全部書いてて2回読むとエラー吐くので
// 宣言と定義を分けました

#ifndef EWCLIB_H
#define EWCLIB_H

#include <dshow.h>

//画像フォーマット（出力部分）
#ifndef EWC_TYPE
	#ifdef _CV_H_
		#define EWC_TYPE MEDIASUBTYPE_RGB24
	#else
		#ifdef __OPENCV_CV_H__
			#define EWC_TYPE MEDIASUBTYPE_RGB24
		#else
			#define EWC_TYPE MEDIASUBTYPE_RGB32
		#endif
	#endif
#endif
//デフォルト値
extern GUID ewc_type; // このグローバル変数だけ消せなかった，すごく気持ち悪い

//画像フォーマット（デバイス出力ピン部分）
#ifndef EWC_DEVICE_TYPE
	#define EWC_DEVICE_TYPE GUID_NULL
#endif
//デフォルト値
//GUID ewc_device_type= EWC_DEVICE_TYPE;

#ifndef EWC_WX
	#define EWC_WX 640
#endif
#ifndef EWC_WY
	#define EWC_WY 480
#endif
#ifndef EWC_FPS
	#define EWC_FPS 30
#endif

#ifndef min
	#define min(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef max
	#define max(a,b) ((a)>(b)?(a):(b))
#endif

#ifndef EWC_NCAMMAX
#define EWC_NCAMMAX 10	//カメラの最大認識数v2.2
#endif


#define EWC_RUN_TIMEOUT		3000
#define EWC_STOP_TIMEOUT	3000
#define EWC_RETRYTIMES		3

#define EWC_VPAMPMAX	10
#define EWC_CAMCTLMAX	7
#define EWC_ITEMMAX		(EWC_VPAMPMAX+EWC_CAMCTLMAX)

#define ewc_release(x) {if(x)x->Release();x=0;}



//フォーマット格納のための構造体v2.3
struct ewc_format{
	int width;
	int height;
	int bit;
	REFERENCE_TIME AvgTimePerFrame;
	double fps;
	GUID subtype;
	char subtype_t[80];	//subtypeに対応する文字列v2.3
};


//IAMVideoProcAmp
#define EWC_BRIGHTNESS				0
#define EWC_CONTRAST				1
#define EWC_HUE						2
#define EWC_SATURATION				3
#define EWC_SHARPNESS				4
#define EWC_GAMMA					5
#define EWC_COLORENABLE				6
#define EWC_WHITEBALANCE			7
#define EWC_BACKLIGHTCOMPENSATION	8
#define EWC_GAIN					9
//IAMCameraControl
#define EWC_PAN						10
#define EWC_TILT					11
#define EWC_ROLL					12
#define EWC_ZOOM					13
#define EWC_EXPOSURE				14
#define EWC_IRIS					15
#define EWC_FOCUS					16


//カメラ台数を返す
int EWC_GetCamera(void);

//カメラ(番号:num)のフレームバッファサイズ(単位:バイト)を返す
int EWC_GetBufferSize(int num);

//カメラ(番号:num)の画像取得
int EWC_GetImage(int num, void *buffer);

//バッファアドレスを変更
int EWC_SetBuffer(int num, void *buffer);

//現在のバッファアドレスを取得
int EWC_GetBuffer(int num, void **buffer);

//設定値を読み出す
//  オプション：modeには0(manual)または1(auto)が格納される
double EWC_GetValue(int num, int prop, int *mode = NULL);

//制御を手動モードに切り替える v2.4
int EWC_SetManual(int num, int prop);

//設定値を変更する(v2.4からewc_propfunc()を呼び出す形に変更)
int EWC_SetValue(int num, int prop, double value);

//設定を初期値に戻す(v2.4からewc_propfunc()を呼び出す形に変更)
int EWC_SetDefault(int num, int prop);

//制御を自動モードにする(v2.4からewc_propfunc()を呼び出す形に変更)
int EWC_SetAuto(int num, int prop);

//最後のエラーメッセージを取得する
//s:文字列格納先  size:領域sのサイズ
void EWC_GetLastMessage(char *s, int size);

//キャプチャの停止
int EWC_Stop(int num);

//キャプチャの再開
int EWC_Run(int num);

//キャプチャのPause v2.4
int EWC_Pause(int num);

//ワンショット v2.4
int EWC_OneShot(int num);

//プロパティページを表示させる
int EWC_PropertyPage(int num);

//新しい画像が到着したかどうか
//  num:カメラ番号  t:取得時刻(秒)
int EWC_IsCaptured(int num, double *t = NULL);

//画像変換(32ビット->24ビット)
void EWC_Cnv32to24(unsigned char *dst, unsigned int *src, int pxl);

//画像変換(24ビット->32ビット)
void EWC_Cnv24to32(unsigned int *dst, unsigned char *src, int pxl);

//メディアサブタイプのGUID値に対応した文字列を得る v2.3
int EWC_GUIDtoTEXT(GUID guid, char *s, int size);

//使用開始[1]（デバイス番号指定）v2.3
int EWC_Open(int num, int wx = 0, int wy = 0, double fps = 0, int device = -1, GUID mstype = ewc_type, GUID dev_mstype = EWC_DEVICE_TYPE);

//使用開始[2]（デバイス名指定）v2.3
int EWC_Open(int num, int wx, int wy, double fps, char *devicename, GUID mstype = ewc_type, GUID dev_mstype = EWC_DEVICE_TYPE);

//使用開始[3]（デバイス名指定，wx/wy/fps省略）v2.2
int EWC_Open(int num, char *devicename, GUID mstype = ewc_type, GUID dev_mstype = EWC_DEVICE_TYPE);

//終了処理
int EWC_Close(int num);

//終了処理（すべて）
int EWC_CloseAll(void);

//対応フォーマットを取得する（デバイス番号）v2.2
int EWC_GetFormat(int devn, ewc_format *fmt, int *nmax);

//対応フォーマットを取得する（デバイス名）v2.2
int EWC_GetFormat(char *devicename, ewc_format *fmt, int *nmax);

//使用開始されたカメラのデバイス名を取得 v2.2
char *EWC_GetDeviceName(int num);

//使用開始されたカメラの出力ピンのメディアサブタイプ文字列を取得 v2.3
char *EWC_GetDeviceSubtype(int num);

//使用開始されたカメラの出力画像のメディアサブタイプ文字列を取得 v2.3
char *EWC_GetSubtype(int num);

//設定をファイルへ保存する v2.4
int EWC_SaveProperty(int num, char *filename = NULL);

//設定をファイルから読み込む v2.4
int EWC_LoadProperty(int num, char *filename = NULL);

#endif

//End of ewclib.h
