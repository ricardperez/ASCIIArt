//
//  ascii_art.h
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 06/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#ifndef __ASCIIArt__ascii_art__
#define __ASCIIArt__ascii_art__

#include <iostream>
#include <set>
#include <vector>
#include "character_opacity.h"
#include "structs.h"

namespace cv
{
	class Mat;
	class VideoCapture;
}

class ASCIIArt
{
private:
	std::set<CharacterOpacity *> characterOpacities;
	char characterForRegionOpacity(const RegionOpacity &regionOpacity) const;
	void getASCIIStringFromImageOpacities(std::vector<std::vector<RegionOpacity> > *imageOpacities, std::string *imageStr) const;
public:
	ASCIIArt();
	~ASCIIArt();
	std::string *newASCIIArtStringForImageName(const std::string &imageName, cv::Mat &resultImage) const;
	std::string *newASCIIArtStringForImageMat(const cv::Mat &imageMat, cv::Mat &resultImage) const;
};

#endif /* defined(__ASCIIArt__ascii_art__) */
