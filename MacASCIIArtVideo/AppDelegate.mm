//
//  AppDelegate.m
//  MacASCIIArtVideo
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
	self.nColumns = (self.nRows * usableWidth / usableHeight);
}

@end
