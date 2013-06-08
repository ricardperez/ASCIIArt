//
//  structs.h
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 06/06/13.
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
