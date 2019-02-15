// Easy Web Camera LIBrary "ewclib.h"  by I.N.
// OS:Windows XP/Vista/7/8
// Compiler:Visual C++ 2008 Professional / 2010~+qedit.h

// 2010/04/15 ver.1.9 EWC_GetLastMessage():Unicode/�}���`�o�C�g�̗��Ή���
// 2010/05/04         �J�n
// 2010/05/06         EWC_Open()/EWC_Close()�d�l�ύX�D
// 2010/05/06         EWC_Run()/EWC_Stop()�ǉ��D
// 2010/05/08         EWC_CloseAll()�ǉ��D
// 2010/05/13 ver.2.0 ����
// 2012/02/28 ver.2.1 ������������̃��������[�N���C��
// 2014/01            �ő�J�������ύX(8->10), @device:sw���ΏۂƂ���
// 2014/01            �����f�o�C�X�g�p�ς݃t���O,EWC_GetFormat()�ǉ�
// 2014/01            EWC_Open():FriendlyName�w��,�f�t�H���g�l�ǉ�
// 2014/01/17 ver.2.2 EWC_Open()�̃o���G�[�V�����ǉ�,EWC_GetDeviceName()�ǉ�
// 2014/01/27         �f�o�C�X�o�̓s���̃t�H�[�}�b�g�w��̋@�\��ǉ�
// 2014/01/27         �t�H�[�}�b�g�ꗗ���擾����T���v���̏C��
// 2014/01/27         EWC_Open()�����ǉ�,ewc_type,ewc_device_type(EWC_DEVICE_TYPE)�ǉ�
// 2014/01/27 ver.2.3 EWC_GetDeviceSubtype(),EWC_GetSubtype(),EWC_GUIDtoTEXT()��ǉ�
// 2014/04/08         ewc_s[].count�ǉ�,EWC_Pause()�ǉ�,EWC_OneShot()�ǉ�
// 2014/04/22 ver.2.4 EWC_SaveProperty(),EWC_LoadProperty(),EWC_SetManual()�ǉ�

// ����ewclib.h�̓w�b�_�ɑS�������Ă�2��ǂނƃG���[�f���̂�
// �錾�ƒ�`�𕪂��܂���

#ifndef EWCLIB_H
#define EWCLIB_H

#include <dshow.h>

//�摜�t�H�[�}�b�g�i�o�͕����j
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
//�f�t�H���g�l
extern GUID ewc_type; // ���̃O���[�o���ϐ����������Ȃ������C�������C��������

//�摜�t�H�[�}�b�g�i�f�o�C�X�o�̓s�������j
#ifndef EWC_DEVICE_TYPE
	#define EWC_DEVICE_TYPE GUID_NULL
#endif
//�f�t�H���g�l
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
#define EWC_NCAMMAX 10	//�J�����̍ő�F����v2.2
#endif


#define EWC_RUN_TIMEOUT		3000
#define EWC_STOP_TIMEOUT	3000
#define EWC_RETRYTIMES		3

#define EWC_VPAMPMAX	10
#define EWC_CAMCTLMAX	7
#define EWC_ITEMMAX		(EWC_VPAMPMAX+EWC_CAMCTLMAX)

#define ewc_release(x) {if(x)x->Release();x=0;}



//�t�H�[�}�b�g�i�[�̂��߂̍\����v2.3
struct ewc_format{
	int width;
	int height;
	int bit;
	REFERENCE_TIME AvgTimePerFrame;
	double fps;
	GUID subtype;
	char subtype_t[80];	//subtype�ɑΉ����镶����v2.3
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


//�J�����䐔��Ԃ�
int EWC_GetCamera(void);

//�J����(�ԍ�:num)�̃t���[���o�b�t�@�T�C�Y(�P��:�o�C�g)��Ԃ�
int EWC_GetBufferSize(int num);

//�J����(�ԍ�:num)�̉摜�擾
int EWC_GetImage(int num, void *buffer);

//�o�b�t�@�A�h���X��ύX
int EWC_SetBuffer(int num, void *buffer);

//���݂̃o�b�t�@�A�h���X���擾
int EWC_GetBuffer(int num, void **buffer);

//�ݒ�l��ǂݏo��
//  �I�v�V�����Fmode�ɂ�0(manual)�܂���1(auto)���i�[�����
double EWC_GetValue(int num, int prop, int *mode = NULL);

//������蓮���[�h�ɐ؂�ւ��� v2.4
int EWC_SetManual(int num, int prop);

//�ݒ�l��ύX����(v2.4����ewc_propfunc()���Ăяo���`�ɕύX)
int EWC_SetValue(int num, int prop, double value);

//�ݒ�������l�ɖ߂�(v2.4����ewc_propfunc()���Ăяo���`�ɕύX)
int EWC_SetDefault(int num, int prop);

//������������[�h�ɂ���(v2.4����ewc_propfunc()���Ăяo���`�ɕύX)
int EWC_SetAuto(int num, int prop);

//�Ō�̃G���[���b�Z�[�W���擾����
//s:������i�[��  size:�̈�s�̃T�C�Y
void EWC_GetLastMessage(char *s, int size);

//�L���v�`���̒�~
int EWC_Stop(int num);

//�L���v�`���̍ĊJ
int EWC_Run(int num);

//�L���v�`����Pause v2.4
int EWC_Pause(int num);

//�����V���b�g v2.4
int EWC_OneShot(int num);

//�v���p�e�B�y�[�W��\��������
int EWC_PropertyPage(int num);

//�V�����摜�������������ǂ���
//  num:�J�����ԍ�  t:�擾����(�b)
int EWC_IsCaptured(int num, double *t = NULL);

//�摜�ϊ�(32�r�b�g->24�r�b�g)
void EWC_Cnv32to24(unsigned char *dst, unsigned int *src, int pxl);

//�摜�ϊ�(24�r�b�g->32�r�b�g)
void EWC_Cnv24to32(unsigned int *dst, unsigned char *src, int pxl);

//���f�B�A�T�u�^�C�v��GUID�l�ɑΉ�����������𓾂� v2.3
int EWC_GUIDtoTEXT(GUID guid, char *s, int size);

//�g�p�J�n[1]�i�f�o�C�X�ԍ��w��jv2.3
int EWC_Open(int num, int wx = 0, int wy = 0, double fps = 0, int device = -1, GUID mstype = ewc_type, GUID dev_mstype = EWC_DEVICE_TYPE);

//�g�p�J�n[2]�i�f�o�C�X���w��jv2.3
int EWC_Open(int num, int wx, int wy, double fps, char *devicename, GUID mstype = ewc_type, GUID dev_mstype = EWC_DEVICE_TYPE);

//�g�p�J�n[3]�i�f�o�C�X���w��Cwx/wy/fps�ȗ��jv2.2
int EWC_Open(int num, char *devicename, GUID mstype = ewc_type, GUID dev_mstype = EWC_DEVICE_TYPE);

//�I������
int EWC_Close(int num);

//�I�������i���ׂāj
int EWC_CloseAll(void);

//�Ή��t�H�[�}�b�g���擾����i�f�o�C�X�ԍ��jv2.2
int EWC_GetFormat(int devn, ewc_format *fmt, int *nmax);

//�Ή��t�H�[�}�b�g���擾����i�f�o�C�X���jv2.2
int EWC_GetFormat(char *devicename, ewc_format *fmt, int *nmax);

//�g�p�J�n���ꂽ�J�����̃f�o�C�X�����擾 v2.2
char *EWC_GetDeviceName(int num);

//�g�p�J�n���ꂽ�J�����̏o�̓s���̃��f�B�A�T�u�^�C�v��������擾 v2.3
char *EWC_GetDeviceSubtype(int num);

//�g�p�J�n���ꂽ�J�����̏o�͉摜�̃��f�B�A�T�u�^�C�v��������擾 v2.3
char *EWC_GetSubtype(int num);

//�ݒ���t�@�C���֕ۑ����� v2.4
int EWC_SaveProperty(int num, char *filename = NULL);

//�ݒ���t�@�C������ǂݍ��� v2.4
int EWC_LoadProperty(int num, char *filename = NULL);

#endif

//End of ewclib.h
