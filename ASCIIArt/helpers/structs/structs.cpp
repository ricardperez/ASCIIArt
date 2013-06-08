//
//  structs.cpp
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

#include "structs.h"

RegionOpacity RegionOpacity::distanceToRegionOpacity(const RegionOpacity &otherRegionOpacity) const
{
	float distanceNW = otherRegionOpacity.NWOpacity - this->NWOpacity;
	float distanceNE = otherRegionOpacity.NEOpacity - this->NEOpacity;
	float distanceSW = otherRegionOpacity.SWOpacity - this->SWOpacity;
	float distanceSE = otherRegionOpacity.SEOpacity - this->SEOpacity;
	
	return RegionOpacity(distanceNW, distanceNE, distanceSW, distanceSE);
}

float RegionOpacity::meanDistanceToRegionOpacity(const RegionOpacity &otherRegionOpacity) const
{
	return (this->distanceToRegionOpacity(otherRegionOpacity).meanOpacity);
}

bool RegionOpacity::operator<(const RegionOpacity &other) const
{
	return (this->meanOpacity < other.meanOpacity);
}