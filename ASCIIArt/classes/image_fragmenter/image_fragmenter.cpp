//
//  image_fragmenter.cpp
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 06/06/13.
//  Copyright (c) 2013, Ricard Pérez del Campo
//  All rights reserved.
//  
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met: 
//  
//  1. Redistributions of source code must retain the above copyright notice, this
//     list of conditions and the following disclaimer. 
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution. 
//  
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
//  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  
//  The views and conclusions contained in the software and documentation are those
//  of the authors and should not be interpreted as representing official policies, 
//  either expressed or implied, of the FreeBSD Project.
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

std::vector<std::vector<RegionOpacity> > *ImageFragmenter::newOpacitiesForImageMat(const cv::Mat &imageMat, cv::Mat &resultImage, int nRows, int nColumns) const
{	
	if (&imageMat != &resultImage)
	{
		imageMat.copyTo(resultImage);
	}
	
	cv::cvtColor(resultImage, resultImage, cv::COLOR_BGR2GRAY);
	
//	cv::Canny(resultImage, resultImage, 20, 100);
//	resultImage = 255-resultImage;
	
	const uchar* imageDataPtr;
	
	int maxGray = 0;
	int minGray = 255;
	for (int iRow=0; iRow<resultImage.rows; ++iRow)
	{
		imageDataPtr = resultImage.ptr(iRow);
		for (int iCol=0; iCol<resultImage.cols; ++iCol)
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
	
	
	int nSteps = 6;
	int minThreshold = 50;
	int maxThreshold = 200;
	int step = ((maxThreshold-minThreshold) / nSteps);
	
	float alpha = 2.5f;
	int beta = 1;
	
	for (int iRow=0; iRow<resultImage.rows; ++iRow)
	{
		imageDataPtr = resultImage.ptr(iRow);
		for (int iCol=0; iCol<resultImage.cols; ++iCol)
		{
			int pixelGrayScale = imageDataPtr[iCol];
			int scaledGray = (((pixelGrayScale - minGray) / graysRange) * 255);
			
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
			
#ifdef IOS
//			resultImage.at<uchar>(iRow, iCol) = usedGray;
			resultImage.at<uchar>(iRow, iCol) = cv::saturate_cast<uchar>(alpha * usedGray + beta );
#else
			resultImage.ptr(iRow)[iCol] = cv::saturate_cast<uchar>(alpha * usedGray + beta );
#endif
		}
	}
	
	int _nRows = nRows;
	int _nColumns = nColumns;

	
	int chunksWidth = (nColumns <= 0 ? 4 : (resultImage.cols / nColumns));
	int chunksHeight = (nRows <= 0 ? 4 : (resultImage.rows / nRows));
	
	if (_nRows <= 0)
	{
		if (_nColumns <= 0)
		{
			nRows = (resultImage.rows / chunksHeight);
			chunksHeight = (resultImage.rows / nRows);
			chunksWidth = chunksHeight;
			nColumns = (resultImage.cols / chunksWidth);
		} else
		{
			chunksHeight = chunksWidth;
			nRows = (resultImage.rows / chunksHeight);
		}
		
	} else if (_nColumns <= 0)
	{
		chunksWidth = chunksHeight;
		nColumns = (resultImage.cols / chunksWidth);
		
	}
	
	
	
	ASCII_Size chunksSize(chunksWidth, chunksHeight);
	
	std::vector<std::vector<RegionOpacity> > *rows = new std::vector<std::vector<RegionOpacity> >();
	for (int iRow=0; iRow<nRows; ++iRow)
	{
		std::vector<RegionOpacity> row;
		for (int iCol=0; iCol<nColumns; ++iCol)
		{
			RegionOpacity regionOpacity = this->getOpacityForRegionForImage((iRow*chunksHeight), (iCol*chunksWidth), chunksSize, resultImage);
			row.push_back(regionOpacity);
		}
		rows->push_back(row);
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