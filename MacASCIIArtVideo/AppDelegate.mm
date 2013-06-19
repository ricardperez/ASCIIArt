//
//  AppDelegate.m
//  MacASCIIArtVideo
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

#import "AppDelegate.h"

@interface AppDelegate ()

@property (nonatomic, assign) int nRows;
@property (nonatomic, assign) int nColumns;

@end

@implementation AppDelegate

- (void)dealloc
{
	[_representationTextField release];
	delete cameraToASCIIArt;
    [super dealloc];
}

- (id)init
{
	self = [super init];
	if (self != nil)
	{
		cameraToASCIIArt = new CameraToASCIIArt(true);
		self.nRows = 50;
		self.nColumns = 60;
	}
	return self;
}


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	[self performSelector:@selector(startVideo) withObject:nil afterDelay:1.0];
}

- (void)startVideo
{
	dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
		while (1)
		{
			cameraToASCIIArt->currentFrameASCII(asciiString, self.nRows, self.nColumns);
			NSString *nsstring = [NSString stringWithUTF8String:asciiString.c_str()];
			asciiString.clear();
			
			dispatch_async(dispatch_get_main_queue(), ^{
				[self.representationTextField setStringValue:nsstring];
			});
		}
	});
	
}


- (IBAction)fontSizeSliderAction:(id)sender
{
	NSFont *font = [NSFont fontWithName:[self.representationTextField.font fontName] size:[self.fontSizeSlider floatValue]];
	[self.representationTextField setFont:font];
	
	CGSize oneCharSize = [@"X" sizeWithAttributes: [NSDictionary dictionaryWithObject:font forKey:NSFontAttributeName]];
	
	float usableWidth = 1280;
	float usableHeight = 720;
	
	
	self.nRows = (usableHeight / oneCharSize.height);
	if (cameraToASCIIArt->getImageConverter().isUsingWhiteSpaceBetweenColumns())
	{
		self.nColumns = (self.nRows * usableWidth / usableHeight);
	} else
	{
		self.nColumns = 2*(self.nRows * usableWidth / usableHeight);
	}
	
//	NSLog(@"%i", self.nColumns);
}

@end
