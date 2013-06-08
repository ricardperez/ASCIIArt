//
//  AppDelegate.h
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

#import <Cocoa/Cocoa.h>
#import "camera_to_ascii_art.h"

@interface AppDelegate : NSObject <NSApplicationDelegate>
{
	CameraToASCIIArt *cameraToASCIIArt;
	std::string asciiString;
}

@property (assign) IBOutlet NSWindow *window;
@property (nonatomic, retain) IBOutlet NSTextField *representationTextField;
@property (nonatomic, retain) IBOutlet NSSlider *fontSizeSlider;

- (IBAction)fontSizeSliderAction:(id)sender;

@end
