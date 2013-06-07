//
//  camera_to_ascii_art.h
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 07/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#ifndef __ASCIIArt__camera_to_ascii_art__
#define __ASCIIArt__camera_to_ascii_art__

#include <iostream>
#include "ascii_art.h"

class CameraToASCIIArt
{
private:
	cv::VideoCapture *capture;
	ASCIIArt imageConverter;
	const bool showVideo;
public:
	CameraToASCIIArt(bool showVideo = false);
	~CameraToASCIIArt();
	bool currentFrameASCII(std::string &strRepresentation);
};

#endif /* defined(__ASCIIArt__camera_to_ascii_art__) */
