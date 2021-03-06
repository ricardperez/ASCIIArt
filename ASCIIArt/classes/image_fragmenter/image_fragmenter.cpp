//
//  image_fragmenter.cpp
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

#include "image_fragmenter.h"
#include <opencv2/opencv.hpp>
#include "functions.h"

#ifndef IOS
#include <opencv2/highgui.hpp>
#endif

std::vector<std::vector<RegionOpacity> > *ImageFragmenter::newOpacitiesForImage(const std::string &imageName, cv::Mat &resultImage, int nRows, int nColumns) const
{
	cv::Mat imageMat = cv::imread(imageName);
	return this->newOpacitiesForImageMat(imageMat, resultImage, nRows, nColumns);
}

void ImageFragmenter::transformImage(const cv::Mat &input, cv::Mat &output) const
{
	if (&input != &output)
	{
		input.copyTo(output);
	}
	
	if (output.channels() != 1)
	{
		cv::cvtColor(output, output, cv::COLOR_BGR2GRAY);
	}
	
	//	cv::Canny(resultImage, resultImage, 20, 100);
	
	if (this->negative)
	{
		output = 255-output;
	}
	
	const uchar* imageDataPtr;
	
	int maxGray = 0;
	int minGray = 255;
	for (int iRow=0; iRow<output.rows; ++iRow)
	{
		imageDataPtr = output.ptr(iRow);
		for (int iCol=0; iCol<output.cols; ++iCol)
		{
			int grayValue = imageDataPtr[iCol];
			if (grayValue < minGray)
			{
				minGray = grayValue;
			}
			if (grayValue > maxGray)
			{
				maxGray = grayValue;
			}
		}
	}
	float graysRange = (maxGray - minGray);
	
	
	int nSteps = (this->nGrays <= 0 ? 1 : this->nGrays);
	int minThreshold = 30;
	int maxThreshold = 225;
	int step = ((maxThreshold-minThreshold) / nSteps);
	
	float alpha = this->contrastAlpha;
	int beta = this->contrastBeta;
	
	for (int iRow=0; iRow<output.rows; ++iRow)
	{
		imageDataPtr = output.ptr(iRow);
		for (int iCol=0; iCol<output.cols; ++iCol)
		{
			int pixelGrayScale = imageDataPtr[iCol];
			int scaledGray = (((pixelGrayScale - minGray) / graysRange) * 255);
			
			scaledGray = cv::saturate_cast<uchar>(alpha * scaledGray + beta );
			
			int usedGray;
			if (scaledGray < minThreshold)
			{
				usedGray = 0;
			} else if (scaledGray > maxThreshold)
			{
				usedGray = 255;
			} else
			{
				bool found = false;
				int i = minThreshold+step;
				while (i < maxThreshold && !found)
				{
					found = (scaledGray < i);
					if (!found)
					{
						i += step;
					}
				}
				
				if (found)
				{
					usedGray = (i - step);
				} else
				{
					usedGray = maxThreshold;
				}
				
			}
			output.ptr(iRow)[iCol] = usedGray;
		}
	}
}

ASCII_Size ImageFragmenter::imageChunksSizeForRowsAndColumns(const cv::Mat &image, int nRows, int nColumns, float &remainingWidthPerColumn, float &remainingHeightPerRow) const
{
	int _nRows = nRows;
	int _nColumns = nColumns;
	
	
	int chunksWidth = (nColumns <= 0 ? 22 : (image.cols / nColumns));
	int chunksHeight = (nRows <= 0 ? 22 : (image.rows / nRows));
	
	if (_nRows <= 0)
	{
		if (_nColumns <= 0)
		{
			nRows = (image.rows / chunksHeight);
			chunksHeight = (image.rows / nRows);
			chunksWidth = chunksHeight;
			nColumns = (image.cols / chunksWidth);
		} else
		{
			chunksHeight = chunksWidth;
			nRows = (image.rows / chunksHeight);
		}
		
	} else if (_nColumns <= 0)
	{
		chunksWidth = chunksHeight;
		nColumns = (image.cols / chunksWidth);
		
	}
	
	int remainingWidth = (image.cols - chunksWidth*nColumns);
	int remainingHeight = (image.rows - chunksHeight*nRows);
	
	remainingWidthPerColumn = ((float)remainingWidth / nColumns);
	remainingHeightPerRow = ((float)remainingHeight / nRows);
	
	
	ASCII_Size chunksSize(chunksWidth, chunksHeight);
	return chunksSize;
}

std::vector<std::vector<RegionOpacity> > *ImageFragmenter::newOpacitiesForImageMat(const cv::Mat &imageMat, cv::Mat &resultImage, int nRows, int nColumns) const
{	
	this->transformImage(imageMat, resultImage);
	
	float remainingWidthPerColumn, remainingHeightPerRow;
	ASCII_Size chunksSize = this->imageChunksSizeForRowsAndColumns(resultImage, nRows, nColumns, remainingWidthPerColumn, remainingHeightPerRow);
	float cumulatedRemainingWidth = 0.0f;
	float cumulatedRemainingHeight = 0.0f;
	
	float chunksHeight = chunksSize.height;
	float chunksWidth = chunksSize.width;
	
	int r = 0;
	std::vector<std::vector<RegionOpacity> > *rows = new std::vector<std::vector<RegionOpacity> >();
	for (int iRow=0; iRow<nRows; ++iRow)
	{
		cumulatedRemainingHeight += remainingHeightPerRow;
		if (cumulatedRemainingHeight >= 1.0f)
		{
			chunksSize.height = chunksHeight + (int)cumulatedRemainingHeight;
			cumulatedRemainingHeight -= (int)cumulatedRemainingHeight;
		} else
		{
			chunksSize.height = chunksHeight;
		}
		
		int c = 0;
		std::vector<RegionOpacity> row;
		for (int iCol=0; iCol<nColumns; ++iCol)
		{
			cumulatedRemainingWidth += remainingWidthPerColumn;
			if (cumulatedRemainingWidth >= 1.0f)
			{
				chunksSize.width = chunksWidth + (int)cumulatedRemainingWidth;
				cumulatedRemainingWidth -= (int)cumulatedRemainingWidth;
			} else
			{
				chunksSize.width = chunksWidth;
			}
			
			RegionOpacity regionOpacity = this->getOpacityForRegionForImage(r, c, chunksSize, resultImage);
			row.push_back(regionOpacity);
			c += chunksSize.width;
		}
		rows->push_back(row);
		r += chunksSize.height;
	}
	
	NormalizeRegions(*rows);
	
	return rows;
}

RegionOpacity ImageFragmenter::getOpacityForRegionForImage(const int &rowIndex, const int &columnIndex, const ASCII_Size &regionSize, const cv::Mat &imageMat) const
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