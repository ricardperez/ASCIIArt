//
//  functions.h
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 07/06/13.
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
