//
//  character_opacity.h
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

#ifndef __ASCIIArt__character_opacity__
#define __ASCIIArt__character_opacity__

#include <iostream>
#include "structs.h"

/**
 * This class will represent the opacity of a character.
 * The opacity will be stored by 4 zones: NW, NE, SW and SE. The mean value will
 * also be accessible.
 * Opacities will be 0..1 values.
 */
class CharacterOpacity
{
private:
	char character;
	RegionOpacity opacity;
	
public:
	
	CharacterOpacity(char character_, float NWOpacity_, float NEOpacity_, float SWOpacity_, float SEOpacity_);
	
	char &getCharacter() { return this->character; }
	RegionOpacity &getRegionOpacity() { return this->opacity; }
	bool operator<(const CharacterOpacity &other) const;
	
};

#endif /* defined(__ASCIIArt__character_opacity__) */
