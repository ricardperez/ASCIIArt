//
//  character_opacity.h
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 06/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
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
	
};

#endif /* defined(__ASCIIArt__character_opacity__) */
