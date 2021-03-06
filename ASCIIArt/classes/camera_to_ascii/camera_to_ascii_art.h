//
//  camera_to_ascii_art.h
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 07/06/13.
//  Copyright (c) 2013, Ricard Pérez del Campo
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
	bool currentFrameASCII(std::string &strRepresentation, int nRows=-1, int nColumns=-1);
	
	ASCIIArt &getImageConverter() { return this->imageConverter; }
};

#endif /* defined(__ASCIIArt__camera_to_ascii_art__) */
