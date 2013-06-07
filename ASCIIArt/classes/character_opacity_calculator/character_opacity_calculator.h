//
//  character_opacity_calculator.h
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 06/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#ifndef __ASCIIArt__character_opacity_calculator__
#define __ASCIIArt__character_opacity_calculator__

#include <iostream>
#include "structs.h"

class CharacterOpacity;

class CharacterOpacityCalculator
{
private:
	const ASCII_Size lettersSize;
public:
	
	CharacterOpacityCalculator(int lettersSizeWidth=22, int lettersSizeHeight=22) : lettersSize(lettersSizeWidth, lettersSizeHeight) {}
	
	/**
	 * Will return an instance allocated with the new operator. It's responsible
	 * of the caller to deallocate it.
	 * The returned instance will have the correct information of the opacity
	 * zones of the given character.
	 */
	CharacterOpacity *newCharacterOpacityForCharacter(char character) const;
	
};

#endif /* defined(__ASCIIArt__character_opacity_calculator__) */
