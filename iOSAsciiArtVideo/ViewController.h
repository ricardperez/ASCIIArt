//
//  ViewController.h
//  iOSAsciiArtVideo
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
@property (nonatomic, retain) IBOutlet UISwitch *copyTextToClipboardSwitch;
@property (nonatomic, retain) IBOutlet UILabel *copyTextToClipboardLabel;
@property (nonatomic, retain) IBOutlet UISwitch *showOriginalImageSwitch;
@property (nonatomic, retain) IBOutlet UILabel *showOriginalImageLabel;
@property (nonatomic, retain) IBOutlet UISwitch *showUsedImageSwitch;
@property (nonatomic, retain) IBOutlet UILabel *showUsedImageLabel;
@property (nonatomic, retain) IBOutlet UISlider *fontSizeSlider;
@property (nonatomic, retain) IBOutlet UILabel *fontSizeLabel;

@property (nonatomic, retain) UIPanGestureRecognizer *panGestureRecognizer;

@property (nonatomic, retain) AVCaptureSession *session;
@property (nonatomic, assign) SystemSoundID cameraSoundID;



- (IBAction)flipCameraActionAction:(id)sender;
- (IBAction)takePhotoAction:(id)sender;
- (IBAction)cameraOptionsAction:(id)sender;
- (IBAction)saveImageSwitchAction:(id)sender;
- (IBAction)copyTextToClipboardSwitchAction:(id)sender;
- (IBAction)showOriginalImageSwitchAction:(id)sender;
- (IBAction)showUsedImageSwitchAction:(id)sender;
- (IBAction)fontSizeSliderAction:(id)sender;

@end
