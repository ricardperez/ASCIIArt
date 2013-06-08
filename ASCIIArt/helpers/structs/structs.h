//
//  structs.h
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 06/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#ifndef __ASCIIArt__structs__
#define __ASCIIArt__structs__

#include <iostream>

struct ASCII_Point
{
	int x;
	int y;
	
	ASCII_Point(int x_, int y_) : x(x_), y(y_) {}
};

struct ASCII_Size
{
	int width;
	int height;
	
	ASCII_Size(int width_, int height_) : width(width_), height(height_) {}
};


struct RegionOpacity
{
	float NWOpacity;
	float NEOpacity;
	float SWOpacity;
	float SEOpacity;
	float meanOpacity;
	
	void calculateMeanOpacity()
	{
		this->meanOpacity = ((this->NWOpacity + this->NEOpacity + this->SWOpacity + this->SEOpacity) / 4.0f);
	}
	
	RegionOpacity(float NWOpacity_, float NEOpacity_, float SWOpacity_, float SEOpacity_) : NWOpacity(NWOpacity_), NEOpacity(NEOpacity_), SWOpacity(SWOpacity_), SEOpacity(SEOpacity_) { this->calculateMeanOpacity(); }
	
	RegionOpacity distanceToRegionOpacity(const RegionOpacity &otherRegionOpacity) const;
	float meanDistanceToRegionOpacity(const RegionOpacity &otherRegionOpacity) const;
	bool operator<(const RegionOpacity &other) const;
	
};

#endif /* defined(__ASCIIArt__structs__) */
