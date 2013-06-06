//
//  image_fragmenter.cpp
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 06/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#include "image_fragmenter.h"
#include <opencv2/opencv.hpp>

std::vector<std::vector<RegionOpacity> > *ImageFragmenter::newOpacitiesForImage(const std::string &imageName, const int chunksWidth, const int chunksHeight) const
{
	Size chunksSize(chunksWidth, chunksHeight);
	
	cv::Mat imageMat = cv::imread(imageName, cv::IMREAD_GRAYSCALE);
	
	std::vector<std::vector<RegionOpacity>> *rows = new std::vector<std::vector<RegionOpacity> >();
	for (int iRow=0; iRow<imageMat.rows; iRow += chunksSize.height)
	{
		std::vector<RegionOpacity> row;
		for (int iCol=0; iCol<imageMat.cols; iCol += chunksSize.width)
		{
			RegionOpacity regionOpacity = this->getOpacityForRegionForImage(iRow, iCol, chunksSize, imageMat);
			row.push_back(regionOpacity);
		}
		rows->push_back(row);
	}
	
	return rows;
}


RegionOpacity ImageFragmenter::getOpacityForRegionForImage(const int &rowIndex, const int &columnIndex, const Size &regionSize, const cv::Mat &imageMat) const
{
	int opaquePixelsNW = 0;
	int nPixelsNW = 0;
	int opaquePixelsNE = 0;
	int nPixelsNE = 0;
	int opaquePixelsSW = 0;
	int nPixelsSW = 0;
	int opaquePixelsSE = 0;
	int nPixelsSE = 0;
	
	int quarterWidth = regionSize.width / 2;
	int quarterHeight = regionSize.height / 2;
	int firstColumnWest = columnIndex;
	int firstColumnEast = columnIndex + quarterWidth;
	int lastColumn = MIN(columnIndex + regionSize.width, imageMat.cols);
	int firstRowNorth = rowIndex;
	int firstRowSouth = rowIndex + quarterHeight;
	int lastRow = MIN(rowIndex + regionSize.height, imageMat.rows);
	
	const uchar* imageDataPtr;
	
	for (int iRow=firstRowNorth; iRow<firstRowSouth; ++iRow)
	{
		imageDataPtr = imageMat.ptr(iRow);
		//NW
		for (int iCol=firstColumnWest; iCol<firstColumnEast; ++iCol)
		{
			opaquePixelsNW += imageDataPtr[iCol];
			++nPixelsNW;
		}
		
		//NE
		for (int iCol=firstColumnEast; iCol<lastColumn; ++iCol)
		{
			opaquePixelsNE += imageDataPtr[iCol];
			++nPixelsNE;
		}
	}
	
	for (int iRow=firstRowSouth; iRow<lastRow; ++iRow)
	{
		imageDataPtr = imageMat.ptr(iRow);
		//SW
		for (int iCol=firstColumnWest; iCol<firstColumnEast; ++iCol)
		{
			opaquePixelsSW += imageDataPtr[iCol];
			++nPixelsSW;
		}
		
		//SE
		for (int iCol=firstColumnEast; iCol<lastColumn; ++iCol)
		{
			opaquePixelsSE += imageDataPtr[iCol];
			++nPixelsSE;
		}
	}
	
	
	float opacityNW = ((float)opaquePixelsNW / nPixelsNW)/255.0f;
	float opacityNE = ((float)opaquePixelsNE / nPixelsNE)/255.0f;
	float opacitySW = ((float)opaquePixelsSW / nPixelsSW)/255.0f;
	float opacitySE = ((float)opaquePixelsSE / nPixelsSE)/255.0f;
	
	RegionOpacity regionOpacity(opacityNW, opacityNE, opacitySW, opacitySE);
	return regionOpacity;
}