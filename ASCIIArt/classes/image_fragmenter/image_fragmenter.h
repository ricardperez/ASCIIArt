//
//  image_fragmenter.h
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
	int nGrays;
	float contrastAlpha;
	int contrastBeta;
	bool negative;
	
	void transformImage(const cv::Mat &input, cv::Mat &output) const;
	ASCII_Size imageChunksSizeForRowsAndColumns(const cv::Mat &image, int nRows, int nColumns, float &remainingWidthPerColumn, float &remainingHeightPerRow) const;
	
public:
	ImageFragmenter() : nGrays(8), contrastAlpha(1.7f), contrastBeta(30), negative(false) {}
	std::vector<std::vector<RegionOpacity> > *newOpacitiesForImage(const std::string &imageName, cv::Mat &resultImage, int nRows=-1, int nColumns=-1) const;
	std::vector<std::vector<RegionOpacity> > *newOpacitiesForImageMat(const cv::Mat &imageMat, cv::Mat &resultImage, int nRows=-1, int nColumns=-1) const;
	
	void setNGrays(int nGrays_) { this->nGrays = nGrays_; }
	int getNGrays() { return this->nGrays; }
	
	void setContrastAlpha(float alpha) { this->contrastAlpha = alpha; }
	float getContrastAlpha() { return this->contrastAlpha; }
	
	void setContrastBeta(int beta) { this->contrastBeta = beta; }
	int getContrastBeta() { return this->contrastBeta; }
	
	void setNegative(bool negative) { this->negative = negative; }
	bool getNegative() { return this->negative; }
};

#endif /* defined(__ASCIIArt__image_fragmenter__) */
