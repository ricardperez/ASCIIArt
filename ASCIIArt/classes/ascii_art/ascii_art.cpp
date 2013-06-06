//
//  ascii_art.cpp
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 06/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#include "ascii_art.h"
#include "image_fragmenter.h"
#include "character_opacity_calculator.h"
#include <cfloat>

ASCIIArt::ASCIIArt()
{
	CharacterOpacityCalculator characterOpacityCalculator;
	for (char nextChar='A'; nextChar<='Z'; ++nextChar)
	{
		CharacterOpacity *characterOpacity = characterOpacityCalculator.newCharacterOpacityForCharacter(nextChar);
		this->characterOpacities.insert(characterOpacity);
	}
	for (char nextChar='a'; nextChar<='z'; ++nextChar)
	{
		CharacterOpacity *characterOpacity = characterOpacityCalculator.newCharacterOpacityForCharacter(nextChar);
		this->characterOpacities.insert(characterOpacity);
	}
	for (char nextChar='0'; nextChar<='9'; ++nextChar)
	{
		CharacterOpacity *characterOpacity = characterOpacityCalculator.newCharacterOpacityForCharacter(nextChar);
		this->characterOpacities.insert(characterOpacity);
	}
//	this->characterOpacities.insert(characterOpacityCalculator.newCharacterOpacityForCharacter(' '));
//	this->characterOpacities.insert(characterOpacityCalculator.newCharacterOpacityForCharacter('.'));
//	this->characterOpacities.insert(characterOpacityCalculator.newCharacterOpacityForCharacter(','));
//	this->characterOpacities.insert(characterOpacityCalculator.newCharacterOpacityForCharacter(':'));
//	this->characterOpacities.insert(characterOpacityCalculator.newCharacterOpacityForCharacter('?'));
//	this->characterOpacities.insert(characterOpacityCalculator.newCharacterOpacityForCharacter('!'));
}

ASCIIArt::~ASCIIArt()
{
	for (std::set<CharacterOpacity *>::iterator it=this->characterOpacities.begin(); it!=this->characterOpacities.end(); ++it)
	{
		delete (*it);
	}
}

std::string *ASCIIArt::newASCIIArtStringForImageName(const std::string &imageName) const
{
	std::string *imageStr = new std::string();
	ImageFragmenter imageFragmenter;
	std::vector<std::vector<RegionOpacity> > *imageOpacities = imageFragmenter.newOpacitiesForImage(imageName);
	
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
	
	delete imageOpacities;
	
	return imageStr;
}

char ASCIIArt::characterForRegionOpacity(const RegionOpacity &regionOpacity) const
{
	float minimumDistance = FLT_MAX;
	char character = ' ';
	for (std::set<CharacterOpacity *>::iterator it=this->characterOpacities.begin(); it!=this->characterOpacities.end(); ++it)
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