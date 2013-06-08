//
//  camera_to_ascii_art.cpp
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 07/06/13.
//  Copyright (c) 2013, Ricard Pérez del Campo
//  All rights reserved.
//  
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met: 
//  
//  1. Redistributions of source code must retain the above copyright notice, this
//     list of conditions and the following disclaimer. 
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution. 
//  
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
//  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  
//  The views and conclusions contained in the software and documentation are those
//  of the authors and should not be interpreted as representing official policies, 
//  either expressed or implied, of the FreeBSD Project.
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