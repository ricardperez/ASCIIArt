//
//  character_opacity_calculator.cpp
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

#include "character_opacity_calculator.h"
#include "character_opacity.h"
#include <opencv2/opencv.hpp>

CharacterOpacity *CharacterOpacityCalculator::newCharacterOpacityForCharacter(char character) const
{
	IplImage *img = cvCreateImage(cvSize(this->lettersSize.width, this->lettersSize.height), 8, 1);
	cvSet(img, cvScalarAll(255.0));
	
	char buffer[2];
	sprintf(buffer, "%c", character);
	
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1.0, 1.0);
	cvPutText(img, buffer, cvPoint(0, this->lettersSize.height-1), &font, cvScalar(0));
	
	long nBlackPixelsNW = 0;
	int nPixelsNW = 0;
	
	long nBlackPixelsNE = 0;
	int nPixelsNE = 0;
	
	long nBlackPixelsSW = 0;
	int nPixelsSW = 0;
	
	long nBlackPixelsSE = 0;
	int nPixelsSE = 0;
	
	for (int y=0; y<img->height/2; ++y)
	{
		uchar *ptr = (uchar *)(img->imageData + y*img->widthStep);
		for (int x=0; x<img->width/2; ++x)
		{
			nBlackPixelsNW += ptr[x];
			++nPixelsNW;
		}
		for (int x=img->width/2; x<img->width; ++x)
		{
			nBlackPixelsNE += ptr[x];
			++nPixelsNE;
		}
	}
	
	for (int y=img->height/2; y<img->height; ++y)
	{
		uchar *ptr = (uchar *)(img->imageData + y*img->widthStep);
		for (int x=0; x<img->width/2; ++x)
		{
			nBlackPixelsSW += ptr[x];
			++nPixelsSW;
		}
		for (int x=img->width/2; x<img->width; ++x)
		{
			nBlackPixelsSE += ptr[x];
			++nPixelsSE;
		}
	}
	
	cvReleaseImage(&img);
	
	float opacityNW = (((float)nBlackPixelsNW / nPixelsNW)/255.0f);
	float opacityNE = (((float)nBlackPixelsNE / nPixelsNE)/255.0f);
	float opacitySW = (((float)nBlackPixelsSW / nPixelsSW)/255.0f);
	float opacitySE = (((float)nBlackPixelsSE / nPixelsSE)/255.0f);
	
	CharacterOpacity *characterOpacity = new CharacterOpacity(character, opacityNW, opacityNE, opacitySW, opacitySE);
	return characterOpacity;
}