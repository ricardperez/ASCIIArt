//
//  functions.h
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 07/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#ifndef __ASCIIArt__functions__
#define __ASCIIArt__functions__

#include <iostream>
#include <vector>
#include <set>
#include "structs.h"

class CharacterOpacity;

/**
 * Will normalize the values for each region.
 * This means that the one with the greater opacity will have an opacity of 1 
 * and the one with smaller opacity will have an opacity of 0. The others will 
 * be scaled suitably.
 * Mean opacity will be used to get the minimum/maximum values, but the 4 zones
 * of each region will be scaled.
 */
void NormalizeRegions(std::vector<std::vector<RegionOpacity> > &regions);

void NormalizeCharacerOpacities(std::vector<CharacterOpacity *> &characterOpacities);

#endif /* defined(__ASCIIArt__functions__) */
