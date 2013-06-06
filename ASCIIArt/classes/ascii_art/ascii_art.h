//
//  ascii_art.h
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 06/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#ifndef __ASCIIArt__ascii_art__
#define __ASCIIArt__ascii_art__

#include <iostream>
#include <set>
#include "character_opacity.h"
#include "structs.h"

class ASCIIArt
{
private:
	std::set<CharacterOpacity *> characterOpacities;
	char characterForRegionOpacity(const RegionOpacity &regionOpacity) const;
public:
	ASCIIArt();
	~ASCIIArt();
	std::string *newASCIIArtStringForImageName(const std::string &imageName) const;
};

#endif /* defined(__ASCIIArt__ascii_art__) */
