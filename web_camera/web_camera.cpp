#include "web_camera.h"

#include <opencv2/core.hpp>

#include "directshow_videocapture.h"



WebCamera::WebCamera(const int camera_id) :
capture_(std::make_unique<DirectShowVideoCapture>(camera_id)) {}


WebCamera::WebCamera(const int camera_id, const int format_id) :
capture_(std::make_unique<DirectShowVideoCapture>(camera_id, format_id)) {}


WebCamera::~WebCamera() {}


bool WebCamera::GetImage(cv::Mat *image)
{
	return capture_->GrabImage(image);
}