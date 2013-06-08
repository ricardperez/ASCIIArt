//
//  ascii_art.h
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 06/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#ifndef __ASCIIArt__ascii_art__
#define __ASCIIArt__ascii_art__

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
	std::vector<CharacterOpacity *> characterOpacities;
	char characterForRegionOpacity(const RegionOpacity &regionOpacity);
	void getASCIIStringFromImageOpacities(std::vector<std::vector<RegionOpacity> > *imageOpacities, std::string *imageStr);
public:
	ASCIIArt();
	~ASCIIArt();
	
	/**
	 * Negative rows and columns will take a required value with default chunks
	 * sizes of 22px
	 */
	std::string *newASCIIArtStringForImageName(const std::string &imageName, cv::Mat &resultImage, int nRows=-1, int nColumns=-1);
	std::string *newASCIIArtStringForImageMat(const cv::Mat &imageMat, cv::Mat &resultImage, int nRows=-1, int nColumns=-1);
};

#endif /* defined(__ASCIIArt__ascii_art__) */
