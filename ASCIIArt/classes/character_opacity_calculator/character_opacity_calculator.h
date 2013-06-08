//
//  character_opacity_calculator.h
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
