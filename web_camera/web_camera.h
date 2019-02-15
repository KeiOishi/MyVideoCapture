#ifndef WEB_CAMERA
#define WEB_CAMERA

#include <memory>

// 前方宣言
class DirectShowVideoCapture;
namespace cv
{
class Mat;
}


// usbのwebカメラ用クラス
// コンストラクタで接続
// GetImageでcv::Matの画像を取得
// 切断は自動
// 中身の処理はDirectShowVideoCaptureクラスにお任せ，興味があったら見て
class WebCamera
{
public:

	// コンストラクタ
	// 引数に何も入れない場合フォーマット番号を手動で入力
	explicit WebCamera(int camera_id = 0);
	
	// コンストラクタ
	// camera_id USBにつながっているカメラの番号
	// format_id そのwebカメラがサポートしているフォーマット番号
	WebCamera(int camera_id, int format_id);

	// デストラクタでは何もしない
	~WebCamera();

	// 画像を取得
	bool GetImage(cv::Mat *image);

private:
	// 中身の処理の部分　気にしない
	// なぜunique_ptrを使っているのか，興味があったらRAIIで検索
	std::unique_ptr<DirectShowVideoCapture> capture_;
};

#endif