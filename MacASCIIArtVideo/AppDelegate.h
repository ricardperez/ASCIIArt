//
//  AppDelegate.h
//  MacASCIIArtVideo
//
//  Created by Ricard Pérez del Campo on 07/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "camera_to_ascii_art.h"

@interface AppDelegate : NSObject <NSApplicationDelegate>
{
	CameraToASCIIArt *cameraToASCIIArt;
	std::string asciiString;
}

@property (assign) IBOutlet NSWindow *window;
@property (nonatomic, retain) IBOutlet NSTextField *representationTextField;



@end
