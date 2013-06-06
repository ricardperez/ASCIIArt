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
	RegionOpacity getOpacityForRegionForImage(const int &rowIndex, const int &columnIndex, const Size &regionSize, const cv::Mat &imageMat) const;
public:
	std::vector<std::vector<RegionOpacity> > *newOpacitiesForImage(const std::string &imageName, const int chunksWidth=22, const int chunksHeight=22) const;
};

#endif /* defined(__ASCIIArt__image_fragmenter__) */
