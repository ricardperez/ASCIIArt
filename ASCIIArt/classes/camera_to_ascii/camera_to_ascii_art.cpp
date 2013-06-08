//
//  camera_to_ascii_art.cpp
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 07/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#include "camera_to_ascii_art.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <ctime>
#include <iostream>
#include <opencv2/opencv.hpp>
#ifndef IOS
#include <opencv2/highgui.hpp>
#endif

CameraToASCIIArt::CameraToASCIIArt(bool showVideo_) : showVideo(showVideo_)
{
	this->capture = new cv::VideoCapture(0);
	if (this->showVideo)
	{
		cv::namedWindow("Camera", cv::WINDOW_AUTOSIZE );
	}
}

CameraToASCIIArt::~CameraToASCIIArt()
{
	delete this->capture;
}

bool CameraToASCIIArt::currentFrameASCII(std::string &strRepresentation, int nRows, int nColumns)
{
	if (this->capture->isOpened())
	{
		cv::Mat capturedImage;
		cv::Mat transformedImage;
		
		this->capture->read(capturedImage);
		
		std::string *newStrRepresentation = this->imageConverter.newASCIIArtStringForImageMat(capturedImage, transformedImage, nRows, nColumns);
		strRepresentation.append(*newStrRepresentation);
		delete newStrRepresentation;
		

		if (this->showVideo)
		{
			cv::imshow("Camera", transformedImage);
		}
		
		return true;
	} else
	{
		return false;
	}
}