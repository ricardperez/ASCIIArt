//
//  image_fragmenter.h
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 06/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#ifndef __ASCIIArt__image_fragmenter__
#define __ASCIIArt__image_fragmenter__

#include <iostream>
#include "structs.h"
#include <vector>

namespace cv
{
	class Mat;
}


class ImageFragmenter
{
private:
	RegionOpacity getOpacityForRegionForImage(const int &rowIndex, const int &columnIndex, const ASCII_Size &regionSize, const cv::Mat &imageMat) const;
public:
	std::vector<std::vector<RegionOpacity> > *newOpacitiesForImage(const std::string &imageName, cv::Mat &resultImage, int nRows=-1, int nColumns=-1) const;
	std::vector<std::vector<RegionOpacity> > *newOpacitiesForImageMat(const cv::Mat &imageMat, cv::Mat &resultImage, int nRows=-1, int nColumns=-1) const;
};

#endif /* defined(__ASCIIArt__image_fragmenter__) */
