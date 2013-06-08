//
//  ViewController.h
//  iOSAsciiArtVideo
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

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>

@interface ViewController : UIViewController <AVCaptureVideoDataOutputSampleBufferDelegate, UIGestureRecognizerDelegate>
{
}

@property (nonatomic, retain) IBOutlet UIView *cameraContainerView;
@property (nonatomic, retain) IBOutlet UILabel *imageTextRepresentationLabel;
@property (nonatomic, retain) IBOutlet UIImageView *originalImageView;
@property (nonatomic, retain) IBOutlet UIImageView *usedImageView;

@property (nonatomic, retain) IBOutlet UIView *controlsContainerView;
@property (nonatomic, retain) IBOutlet UIImageView *controlsBackgroundImageView;
@property (nonatomic, retain) IBOutlet UIButton *flipCameraButton;
@property (nonatomic, retain) IBOutlet UIButton *takePhotoButton;
@property (nonatomic, retain) IBOutlet UIButton *cameraOptionsButton;
@property (nonatomic, retain) IBOutlet UIView *controlsOptionsContainerView;
@property (nonatomic, retain) IBOutlet UIImageView *controlsOptionsBackgroundImageView;
@property (nonatomic, retain) IBOutlet UISwitch *saveImageSwitch;
@property (nonatomic, retain) IBOutlet UILabel *saveImageLabel;
@property (nonatomic, retain) IBOutlet UISwitch *setTextToClipboardSwitch;
@property (nonatomic, retain) IBOutlet UILabel *setTextToClipboardLabel;
@property (nonatomic, retain) IBOutlet UISwitch *showOriginalImageSwitch;
@property (nonatomic, retain) IBOutlet UILabel *showOriginalImageLabel;
@property (nonatomic, retain) IBOutlet UISwitch *showUsedImageSwitch;
@property (nonatomic, retain) IBOutlet UILabel *showUsedImageLabel;
@property (nonatomic, retain) IBOutlet UISwitch *matrixModeSwitch;
@property (nonatomic, retain) IBOutlet UILabel *matrixModeLabel;
@property (nonatomic, retain) IBOutlet UISlider *fontSizeSlider;
@property (nonatomic, retain) IBOutlet UILabel *fontSizeLabel;

@property (nonatomic, retain) UIPanGestureRecognizer *panGestureRecognizer;

@property (nonatomic, retain) AVCaptureSession *session;
@property (nonatomic, assign) SystemSoundID cameraSoundID;



- (IBAction)flipCameraActionAction:(id)sender;
- (IBAction)takePhotoAction:(id)sender;
- (IBAction)cameraOptionsAction:(id)sender;
- (IBAction)saveImageSwitchAction:(id)sender;
- (IBAction)setTextToClipboardSwitchAction:(id)sender;
- (IBAction)showOriginalImageSwitchAction:(id)sender;
- (IBAction)showUsedImageSwitchAction:(id)sender;
- (IBAction)fontSizeSliderAction:(id)sender;
- (IBAction)matrixModeSwitchAction:(id)sender;

@end
