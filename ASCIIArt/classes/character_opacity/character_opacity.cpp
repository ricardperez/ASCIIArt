//
//  character_opacity.cpp
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