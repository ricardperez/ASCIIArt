//
//  ascii_art.cpp
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

#include "ascii_art.h"
#include "image_fragmenter.h"
#include "character_opacity_calculator.h"
#include <cfloat>
#include "functions.h"

ASCIIArt::ASCIIArt()
{
	CharacterOpacityCalculator characterOpacityCalculator;
	for (char nextChar='A'; nextChar<='Z'; ++nextChar)
	{
		CharacterOpacity *characterOpacity = characterOpacityCalculator.newCharacterOpacityForCharacter(nextChar);
		this->characterOpacities.push_back(characterOpacity);
	}
//	for (char nextChar='a'; nextChar<='z'; ++nextChar)
//	{
//		CharacterOpacity *characterOpacity = characterOpacityCalculator.newCharacterOpacityForCharacter(nextChar);
//		this->characterOpacities.push_back(characterOpacity);
//	}
//	for (char nextChar='0'; nextChar<='9'; ++nextChar)
//	{
//		CharacterOpacity *characterOpacity = characterOpacityCalculator.newCharacterOpacityForCharacter(nextChar);
//		this->characterOpacities.push_back(characterOpacity);
//	}
	this->characterOpacities.push_back(characterOpacityCalculator.newCharacterOpacityForCharacter('.'));
	this->characterOpacities.push_back(characterOpacityCalculator.newCharacterOpacityForCharacter('-'));
	
	NormalizeCharacerOpacities(this->characterOpacities);
}

ASCIIArt::~ASCIIArt()
{
	for (std::vector<CharacterOpacity *>::iterator it=this->characterOpacities.begin(); it!=this->characterOpacities.end(); ++it)
	{
		delete (*it);
	}
}

std::string *ASCIIArt::newASCIIArtStringForImageName(const std::string &imageName, cv::Mat &resultImage, int nRows, int nColumns)
{
	std::string *imageStr = new std::string();
	ImageFragmenter imageFragmenter;
	std::vector<std::vector<RegionOpacity> > *imageOpacities = imageFragmenter.newOpacitiesForImage(imageName, resultImage, nRows, nColumns);
	
	this->getASCIIStringFromImageOpacities(imageOpacities, imageStr);
	delete imageOpacities;
	return imageStr;
}

std::string *ASCIIArt::newASCIIArtStringForImageMat(const cv::Mat &imageMat, cv::Mat &resultImage, int nRows, int nColumns)
{	
	std::string *imageStr = new std::string();
	ImageFragmenter imageFragmenter;
	std::vector<std::vector<RegionOpacity> > *imageOpacities = imageFragmenter.newOpacitiesForImageMat(imageMat, resultImage, nRows, nColumns);
	
	this->getASCIIStringFromImageOpacities(imageOpacities, imageStr);
	delete imageOpacities;
	return imageStr;
}

void ASCIIArt::getASCIIStringFromImageOpacities(std::vector<std::vector<RegionOpacity> > *imageOpacities, std::string *imageStr)
{
	for (std::vector<std::vector<RegionOpacity> >::iterator rowsIterator=imageOpacities->begin(); rowsIterator!=imageOpacities->end(); ++rowsIterator)
	{
		std::vector<RegionOpacity> row = *rowsIterator;
		for (std::vector<RegionOpacity>::iterator columnsIterator = row.begin(); columnsIterator != row.end(); ++columnsIterator)
		{
			RegionOpacity regionOpacity = *columnsIterator;
			char character = this->characterForRegionOpacity(regionOpacity);
			imageStr->push_back(character);
			
			if (columnsIterator != (row.end()-1))
			{
				imageStr->push_back(' ');
			}
		}
		if (rowsIterator != (imageOpacities->end()-1))
		{
			imageStr->push_back('\n');
		}
	}
}


char ASCIIArt::characterForRegionOpacity(const RegionOpacity &regionOpacity)
{
	float minimumDistance = FLT_MAX;
	char character = ' ';
	
	for (std::vector<CharacterOpacity *>::iterator it=this->characterOpacities.begin(); it!=this->characterOpacities.end(); ++it)
//	for (auto it=this->characterOpacities.begin(); it!=this->characterOpacities.end(); ++it)
	{
		CharacterOpacity *characterOpacity = *it;
		
		float currDistance = characterOpacity->getRegionOpacity().meanDistanceToRegionOpacity(regionOpacity);
		if (currDistance < 0)
		{
			currDistance = -currDistance;
		}
		if (currDistance < minimumDistance)
		{
			minimumDistance = currDistance;
			character = characterOpacity->getCharacter();
		}
	}
	
	return character;
}