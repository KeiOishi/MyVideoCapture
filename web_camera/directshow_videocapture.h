

#ifndef DIRECTSHOW_VIDEO_CAPTURE
#define DIRECTSHOW_VIDEO_CAPTURE

#include <memory>

// ewclibを使ってusbカメラのキャプチャを行い,cv::Matで出力


namespace cv
{
class Mat;
}

class DirectShowVideoCapture {
public:
	explicit DirectShowVideoCapture(int cameraID = 0);
	DirectShowVideoCapture(int cameraID, int formatID);
	~DirectShowVideoCapture();

	bool GrabImage(cv::Mat *cvImage);
	void SetProperty() const;

	int width() const { return width_; }
	int height() const { return height_; }
	double fps() const { return fps_; }

	DirectShowVideoCapture(DirectShowVideoCapture const&) = delete;
	DirectShowVideoCapture(DirectShowVideoCapture&&) = delete;
	DirectShowVideoCapture& operator = (DirectShowVideoCapture const&) = delete;
	DirectShowVideoCapture& operator = (DirectShowVideoCapture&&) = delete;

private:
	void Init();
	void Init(int formatID);
	void Release();

	const int cameraID_;
	int width_;
	int height_;
	double fps_;
	std::unique_ptr<char[]> buffer_;
};


#endif