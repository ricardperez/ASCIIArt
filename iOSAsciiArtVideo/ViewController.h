//
//  ViewController.h
//  iOSAsciiArtVideo
//
//  Created by Ricard Pérez del Campo on 07/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>


@interface ViewController : UIViewController <AVCaptureVideoDataOutputSampleBufferDelegate>
{
}

@property (nonatomic, retain) IBOutlet UILabel *imageTextRepresentationLabel;
@property (nonatomic, retain) IBOutlet UIButton *flipCameraButton;
@property (nonatomic, retain) AVCaptureSession *session;
@property (nonatomic, retain) IBOutlet UIImageView *debugImageView;

- (IBAction)flipCameraActionAction:(id)sender;

@end
