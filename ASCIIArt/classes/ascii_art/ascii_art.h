//
//  ascii_art.h
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 06/06/13.
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
