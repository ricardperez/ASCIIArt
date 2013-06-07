//
//  AppDelegate.m
//  MacASCIIArtVideo
//
//  Created by Ricard Pérez del Campo on 07/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#import "AppDelegate.h"


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
			cameraToASCIIArt->currentFrameASCII(asciiString);
			NSString *nsstring = [NSString stringWithUTF8String:asciiString.c_str()];
			asciiString.clear();
			
			dispatch_async(dispatch_get_main_queue(), ^{
				[self.representationTextField setStringValue:nsstring];
			});
		}
	});
	
}

@end
