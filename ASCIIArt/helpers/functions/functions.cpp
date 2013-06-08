//
//  functions.cpp
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

#include "functions.h"
#include <cfloat>
#include "character_opacity.h"

void NormalizeRegions(std::vector<std::vector<RegionOpacity> > &regions)
{
	float minOpacity = FLT_MAX;
	float maxOpacity = FLT_MIN;
	
	for (std::vector<std::vector<RegionOpacity> >::iterator rowsIterator = regions.begin(); rowsIterator != regions.end(); ++rowsIterator)
	{
		std::vector<RegionOpacity> row = *rowsIterator;
		for (std::vector<RegionOpacity>::iterator rowIterator = row.begin(); rowIterator != row.end(); ++rowIterator)
		{
			RegionOpacity currRegion = *rowIterator;
			
			if (currRegion.meanOpacity > maxOpacity)
			{
				maxOpacity = currRegion.meanOpacity;
			}
			if (currRegion.meanOpacity < minOpacity)
			{
				minOpacity = currRegion.meanOpacity;
			}
		}
	}
	
	float opacityRange = (maxOpacity - minOpacity);
	
	for (std::vector<std::vector<RegionOpacity> >::iterator rowsIterator = regions.begin(); rowsIterator != regions.end(); ++rowsIterator)
	{
		std::vector<RegionOpacity> row = *rowsIterator;
		for (std::vector<RegionOpacity>::iterator rowIterator = row.begin(); rowIterator != row.end(); ++rowIterator)
		{
			RegionOpacity *region = &(*rowIterator);
			
			region->NWOpacity = ((region->NWOpacity - minOpacity) / opacityRange);
			region->NEOpacity = ((region->NEOpacity - minOpacity) / opacityRange);
			region->SWOpacity = ((region->SWOpacity - minOpacity) / opacityRange);
			region->SEOpacity = ((region->SEOpacity - minOpacity) / opacityRange);
			region->calculateMeanOpacity();
		}
	}
	
}


void NormalizeCharacerOpacities(std::vector<CharacterOpacity *> &characterOpacities)
{
	float minOpacity = FLT_MAX;
	float maxOpacity = FLT_MIN;
	
	for (std::vector<CharacterOpacity *>::iterator charactersIterator = characterOpacities.begin(); charactersIterator != characterOpacities.end(); ++charactersIterator)
	{
		RegionOpacity &currRegion = (*charactersIterator)->getRegionOpacity();
		
		if (currRegion.meanOpacity > maxOpacity)
		{
			maxOpacity = currRegion.meanOpacity;
		}
		if (currRegion.meanOpacity < minOpacity)
		{
			minOpacity = currRegion.meanOpacity;
		}
	}
	
	float opacityRange = (maxOpacity - minOpacity);
	
	for (std::vector<CharacterOpacity *>::iterator charactersIterator = characterOpacities.begin(); charactersIterator != characterOpacities.end(); ++charactersIterator)
	{
		RegionOpacity &region = (*charactersIterator)->getRegionOpacity();
		
		region.NWOpacity = ((region.NWOpacity - minOpacity) / opacityRange);
		region.NEOpacity = ((region.NEOpacity - minOpacity) / opacityRange);
		region.SWOpacity = ((region.SWOpacity - minOpacity) / opacityRange);
		region.SEOpacity = ((region.SEOpacity - minOpacity) / opacityRange);
		region.calculateMeanOpacity();
	}
}