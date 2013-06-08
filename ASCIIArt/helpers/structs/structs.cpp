//
//  structs.cpp
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 06/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
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