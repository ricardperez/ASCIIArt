//
//  character_opacity.cpp
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 06/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#include "character_opacity.h"


CharacterOpacity::CharacterOpacity(char character_,
										  float NWOpacity_, float NEOpacity_,
										  float SWOpacity_, float SEOpacity_) :
character(character_),
opacity(NWOpacity_, NEOpacity_, SWOpacity_, SEOpacity_)
{
}

bool CharacterOpacity::operator<(const CharacterOpacity &other) const
{
	return ((this->character < other.character) || ((this->character == other.character) && (this->opacity < other.opacity)));
}