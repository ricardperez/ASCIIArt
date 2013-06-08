//
//  functions.cpp
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 07/06/13.
//  Copyright (c) 2013, Ricard Pérez del Campo
//  All rights reserved.
//  
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met: 
//  
//  1. Redistributions of source code must retain the above copyright notice, this
//     list of conditions and the following disclaimer. 
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution. 
//  
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
//  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  
//  The views and conclusions contained in the software and documentation are those
//  of the authors and should not be interpreted as representing official policies, 
//  either expressed or implied, of the FreeBSD Project.
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