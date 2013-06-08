//
//  character_opacity_calculator.cpp
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