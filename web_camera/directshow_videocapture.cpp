#include "directshow_videocapture.h"

#include <iostream>

#include <opencv2/core.hpp>

#include "ewclib/ewclib.h"


DirectShowVideoCapture::DirectShowVideoCapture(const int cameraID) :
	cameraID_(cameraID),
	width_(0),
	height_(0),
	fps_(0.0),
	buffer_()
{
	Init();
}


DirectShowVideoCapture::DirectShowVideoCapture(
	const int cameraID,
	const int formatID) :
	cameraID_(cameraID),
	width_(0),
	height_(0),
	fps_(0.0),
	buffer_()
{
	if (formatID < 0) {
		Init();
	}
	else {
		Init(formatID);
	}
}


DirectShowVideoCapture::~DirectShowVideoCapture()
{
	Release();
}


void DirectShowVideoCapture::Init()
{
	std::cout << "DirectShow VideoCapture  cameraID " << cameraID_ << "\n";

	ewc_format format[20]; // 20‚Í“K“–‚ÉŒˆ‚ß‚½
	int format_num = 20;
	if (!EWC_GetFormat(cameraID_, format, &format_num) == 0) {
		std::cerr << "Camera does not exist\n";
		exit(1);
	}
	std::cout << "------------------------\n";
	for (int i = 0; i < format_num; ++i) {
		std::cout << i << " : ";
		std::cout << format[i].width << " x " << format[i].height << ", ";
		std::cout << format[i].fps << " fps " << format[i].subtype_t << "\n";
	}
	std::cout << "------------------------\n";

	std::cout << "\nInput format No. -> ";
	int formatID;
	std::cin >> formatID;
	while (formatID < 0 || formatID >= format_num) {
		std::cout << "\nInvalid number\n";
		std::cout << "\nInput format No. -> ";
		std::cin >> formatID;
	}

	width_ = format[formatID].width;
	height_ = format[formatID].height;
	fps_ = format[formatID].fps;

	if (EWC_Open(cameraID_, width_, height_, fps_, cameraID_, MEDIASUBTYPE_RGB24) != 0) {
		std::cerr << "Cannot open camera\n";
		exit(1);
	}

	buffer_.reset(new char[EWC_GetBufferSize(cameraID_)]);
}


void DirectShowVideoCapture::Init(const int formatID)
{
	std::cout << "DirectShow VideoCapture  cameraID " << cameraID_ << "\n";

	ewc_format format[20]; // 20‚Í“K“–‚ÉŒˆ‚ß‚½
	int format_num = 20;
	if (!EWC_GetFormat(cameraID_, format, &format_num) == 0) {
		std::cerr << "Camera does not exist\n";
		exit(1);
	}
	std::cout << "------------------------\n";
	for (int i = 0; i < format_num; ++i) {
		std::cout << i << " : ";
		std::cout << format[i].width << " x " << format[i].height << ", ";
		std::cout << format[i].fps << " fps " << format[i].subtype_t << "\n";
	}
	std::cout << "------------------------\n";

	std::cout << "Format ID -> " << formatID << "\n";
	if (formatID < 0 || formatID >= format_num) {
		std::cout << "\nInvalid number\n";
		exit(1);
	}

	width_ = format[formatID].width;
	height_ = format[formatID].height;
	fps_ = format[formatID].fps;

	if (EWC_Open(cameraID_, width_, height_, fps_, cameraID_, MEDIASUBTYPE_RGB24) != 0) {
		std::cerr << "Cannot open camera\n" << formatID;
		exit(1);
	}

	buffer_.reset(new char[EWC_GetBufferSize(cameraID_)]);
}


void DirectShowVideoCapture::Release()
{
	std::cout << "Release ... ";
	if (!EWC_Close(cameraID_) == 0) {
		std::cerr << "Cannot close camera\n";
		exit(1);
	}
	std::cout << "Done\n";
}


bool DirectShowVideoCapture::GrabImage(cv::Mat *cvImage)
{
	if (EWC_GetImage(cameraID_, buffer_.get()) != 0) {
		std::cerr << "cannot getImage\n";
		return false;
	}

	cv::Mat tmp(height_, width_, CV_8UC3);
	memcpy(tmp.data, buffer_.get(), width_ * height_ * 3);

	std::swap(*cvImage, tmp);

	return true;
}


void DirectShowVideoCapture::SetProperty() const
{
	EWC_PropertyPage(cameraID_);
}