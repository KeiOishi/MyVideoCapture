#ifndef WEB_CAMERA
#define WEB_CAMERA

#include <memory>

// �O���錾
class DirectShowVideoCapture;
namespace cv
{
class Mat;
}


// usb��web�J�����p�N���X
// �R���X�g���N�^�Őڑ�
// GetImage��cv::Mat�̉摜���擾
// �ؒf�͎���
// ���g�̏�����DirectShowVideoCapture�N���X�ɂ��C���C�������������猩��
class WebCamera
{
public:

	// �R���X�g���N�^
	// �����ɉ�������Ȃ��ꍇ�t�H�[�}�b�g�ԍ����蓮�œ���
	explicit WebCamera(int camera_id = 0);
	
	// �R���X�g���N�^
	// camera_id USB�ɂȂ����Ă���J�����̔ԍ�
	// format_id ����web�J�������T�|�[�g���Ă���t�H�[�}�b�g�ԍ�
	WebCamera(int camera_id, int format_id);

	// �f�X�g���N�^�ł͉������Ȃ�
	~WebCamera();

	// �摜���擾
	bool GetImage(cv::Mat *image);

private:
	// ���g�̏����̕����@�C�ɂ��Ȃ�
	// �Ȃ�unique_ptr���g���Ă���̂��C��������������RAII�Ō���
	std::unique_ptr<DirectShowVideoCapture> capture_;
};

#endif