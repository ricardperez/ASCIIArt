//
//  ViewController.m
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

#import "ViewController.h"
#import <CoreGraphics/CoreGraphics.h>
#import <ImageIO/ImageIO.h>
#include "ascii_art.h"
#import "UIImage+CVMat.h"

#define CAPTURE_FRAMES_PER_SECOND		20
#define KEY_SAVE_IMAGES_TO_CAMERA_ROLL	@"__k_save_images_camera_roll__"
#define KEY_COPY_TEXT_TO_CLIPBOARD		@"__k_copy_text_to_clipboard__"

@interface ViewController ()
{
	ASCIIArt *imageToTextConversor;
}

@property (nonatomic, retain) AVCaptureDeviceInput *frontCameraDeviceInput;
@property (nonatomic, retain) AVCaptureDeviceInput *backCameraDeviceInput;
@property (nonatomic, assign, getter = isBackCamera) BOOL backCamera;
@property (nonatomic, assign, getter = isShowingOptions) BOOL showingOptions;
@property (nonatomic, assign) UIImageView *movingView;
@property (nonatomic, assign) NSInteger nRows;
@property (nonatomic, assign) NSInteger nColumns;

- (void)panGestureRecognizerAction:(UIPanGestureRecognizer *)panGestureRecognizer;

@end


@implementation ViewController

- (void)dealloc
{
	[self.cameraContainerView removeGestureRecognizer:self.panGestureRecognizer];
	[_panGestureRecognizer release];
	
	[_cameraContainerView release];
	[_imageTextRepresentationLabel release];
	[_originalImageView release];
	[_usedImageView release];
	[_controlsContainerView release];
	[_controlsBackgroundImageView release];
	[_flipCameraButton release];
	[_takePhotoButton release];
	[_cameraOptionsButton release];
	[_controlsOptionsContainerView release];
	[_controlsOptionsBackgroundImageView release];
	[_saveImageSwitch release];
	[_saveImageLabel release];
	[_setTextToClipboardSwitch release];
	[_setTextToClipboardLabel release];
	[_showOriginalImageSwitch release];
	[_showOriginalImageLabel release];
	[_showUsedImageSwitch release];
	[_showUsedImageLabel release];
	[_fontSizeLabel release];
	[_fontSizeSlider release];
	
	[_session release];
	[_frontCameraDeviceInput release];
	[_backCameraDeviceInput release];
	
	AudioServicesDisposeSystemSoundID(self.cameraSoundID);
	delete imageToTextConversor;
	
	[super dealloc];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	imageToTextConversor = new ASCIIArt();
	
	self.panGestureRecognizer = [[[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(panGestureRecognizerAction:)] autorelease];
	self.panGestureRecognizer.delegate = self;
	[self.cameraContainerView addGestureRecognizer:self.panGestureRecognizer];
	
	NSNumber *saveImages = [[NSUserDefaults standardUserDefaults] objectForKey:KEY_SAVE_IMAGES_TO_CAMERA_ROLL];
	NSNumber *copyText = [[NSUserDefaults standardUserDefaults] objectForKey:KEY_COPY_TEXT_TO_CLIPBOARD];
	
	[self.saveImageSwitch setOn:((saveImages == nil) || [saveImages boolValue])];
	[self.setTextToClipboardSwitch setOn:((copyText == nil) || [copyText boolValue])];
	
	NSURL *correctSoundURL = [[NSBundle mainBundle] URLForResource:@"camera_sound" withExtension:@"wav"];
	AudioServicesCreateSystemSoundID((CFURLRef)correctSoundURL, &_cameraSoundID);
	
	[self.usedImageView setHidden:YES];
	[self.showUsedImageSwitch setOn:NO];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation
{
	return (toInterfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void)viewDidAppear:(BOOL)animated
{
	[super viewDidAppear:animated];
	
	[self canvasSizeForFontSize:self.fontSizeSlider.value nRows:_nRows nColumns:_nColumns];
	[self setupCaptureSession];
}


#pragma mark - IBActions
- (IBAction)flipCameraActionAction:(id)sender
{
	if ([self isBackCamera])
	{
		[self.session removeInput:self.backCameraDeviceInput];
		if ([self.session canAddInput:self.frontCameraDeviceInput])
		{
			[self.session addInput:self.frontCameraDeviceInput];
		}
	} else
	{
		[self.session removeInput:self.frontCameraDeviceInput];
		if ([self.session canAddInput:self.backCameraDeviceInput])
		{
			[self.session addInput:self.backCameraDeviceInput];
		}
	}
	
	self.backCamera = ![self isBackCamera];
}

- (IBAction)takePhotoAction:(id)sender
{
	if ([self.setTextToClipboardSwitch isOn])
	{
		UIPasteboard *pasteboard = [UIPasteboard generalPasteboard];
		pasteboard.string = [self.imageTextRepresentationLabel text];
	}
	if ([self.saveImageSwitch isOn])
	{
		UIGraphicsBeginImageContext(self.imageTextRepresentationLabel.bounds.size);
		[self.imageTextRepresentationLabel.layer renderInContext:UIGraphicsGetCurrentContext()];
		
		UIImage * img = UIGraphicsGetImageFromCurrentImageContext();
		
		UIGraphicsEndImageContext();
		
		UIImageWriteToSavedPhotosAlbum(img, nil, NULL, NULL);
	}
	
	if ([self.setTextToClipboardSwitch isOn] || [self.saveImageSwitch isOn])
	{
		AudioServicesPlaySystemSound(self.cameraSoundID);
	}
}

- (IBAction)cameraOptionsAction:(id)sender
{
	CGRect controlsContainerFrame = self.controlsContainerView.frame;
	self.showingOptions = (![self isShowingOptions]);
	if ([self isShowingOptions])
	{
		controlsContainerFrame.origin.y = (self.view.frame.size.height - controlsContainerFrame.size.height);
	} else
	{
		controlsContainerFrame.origin.y = (self.view.frame.size.height - self.controlsOptionsContainerView.frame.origin.y);
	}
	[UIView animateWithDuration:0.2 animations:^{
		self.controlsContainerView.frame = controlsContainerFrame;
	}];
}

- (IBAction)saveImageSwitchAction:(id)sender
{
	[[NSUserDefaults standardUserDefaults] setObject:[NSNumber numberWithBool:([self.saveImageSwitch isOn])] forKey:KEY_SAVE_IMAGES_TO_CAMERA_ROLL];
	[[NSUserDefaults standardUserDefaults] synchronize];
}

- (IBAction)setTextToClipboardSwitchAction:(id)sender
{
	[[NSUserDefaults standardUserDefaults] setObject:[NSNumber numberWithBool:([self.setTextToClipboardSwitch isOn])] forKey:KEY_COPY_TEXT_TO_CLIPBOARD];
	[[NSUserDefaults standardUserDefaults] synchronize];
}

- (IBAction)showOriginalImageSwitchAction:(id)sender
{
	[self.originalImageView setHidden:(!([self.showOriginalImageSwitch isOn]))];
	if ([self.showOriginalImageSwitch isOn])
	{
		BOOL isHalfLeft = ((self.originalImageView.frame.origin.x + self.originalImageView.frame.size.width*0.5f) < (self.cameraContainerView.frame.size.width*0.5f));
		BOOL isHalfTop = ((self.originalImageView.frame.origin.y + self.originalImageView.frame.size.height*0.5f) < (self.cameraContainerView.frame.size.height*0.5f));
		
		BOOL otherIsHalfLeft = ((self.usedImageView.frame.origin.x + self.usedImageView.frame.size.width*0.5f) < (self.cameraContainerView.frame.size.width*0.5f));
		BOOL otherIsHalfTop = ((self.usedImageView.frame.origin.y + self.usedImageView.frame.size.height*0.5f) < (self.cameraContainerView.frame.size.height*0.5f));
		
		if ((isHalfLeft == otherIsHalfLeft) && (isHalfTop == otherIsHalfTop))
		{
			CGFloat xPos = (isHalfLeft ? self.cameraContainerView.frame.size.width-self.originalImageView.frame.size.width : 0.0f);
			[self.originalImageView setFrame:CGRectMake(xPos, 0.0f, self.originalImageView.frame.size.width, self.originalImageView.frame.size.height)];
		}
	}
}

- (IBAction)showUsedImageSwitchAction:(id)sender
{
	[self.usedImageView setHidden:(!([self.showUsedImageSwitch isOn]))];
	if ([self.showUsedImageSwitch isOn])
	{
		BOOL isHalfLeft = ((self.usedImageView.frame.origin.x + self.usedImageView.frame.size.width*0.5f) < (self.cameraContainerView.frame.size.width*0.5f));
		BOOL isHalfTop = ((self.usedImageView.frame.origin.y + self.usedImageView.frame.size.height*0.5f) < (self.cameraContainerView.frame.size.height*0.5f));
		
		BOOL otherIsHalfLeft = ((self.originalImageView.frame.origin.x + self.originalImageView.frame.size.width*0.5f) < (self.cameraContainerView.frame.size.width*0.5f));
		BOOL otherIsHalfTop = ((self.originalImageView.frame.origin.y + self.originalImageView.frame.size.height*0.5f) < (self.cameraContainerView.frame.size.height*0.5f));
		
		if ((isHalfLeft == otherIsHalfLeft) && (isHalfTop == otherIsHalfTop))
		{
			CGFloat xPos = (isHalfLeft ? self.cameraContainerView.frame.size.width-self.usedImageView.frame.size.width : 0.0f);
			[self.usedImageView setFrame:CGRectMake(xPos, 0.0f, self.usedImageView.frame.size.width, self.usedImageView.frame.size.height)];
		}
	}
}

- (IBAction)fontSizeSliderAction:(id)sender
{
	[self.imageTextRepresentationLabel setFont:[UIFont fontWithName:[self.imageTextRepresentationLabel.font fontName] size:self.fontSizeSlider.value]];
	[self canvasSizeForFontSize:self.fontSizeSlider.value nRows:_nRows nColumns:_nColumns];
	[self.fontSizeLabel setText:[NSString stringWithFormat:@"Font size: %.1f", self.fontSizeSlider.value]];
}


- (IBAction)matrixModeSwitchAction:(id)sender
{
	if ([self.matrixModeSwitch isOn])
	{
		[self.imageTextRepresentationLabel setBackgroundColor:[UIColor blackColor]];
		[self.imageTextRepresentationLabel setTextColor:[UIColor greenColor]];
	} else
	{
		[self.imageTextRepresentationLabel setBackgroundColor:[UIColor whiteColor]];
		[self.imageTextRepresentationLabel setTextColor:[UIColor blackColor]];
	}
}


#pragma mark - AV setup
// Create and configure a capture session and start it running
- (void)setupCaptureSession
{
    NSError *error = nil;
	
    // Create the session
    AVCaptureSession *session = [[[AVCaptureSession alloc] init] autorelease];
	
    // Configure the session to produce lower resolution video frames, if your
    // processing algorithm can cope. We'll specify medium quality for the
    // chosen device.
//	session.sessionPreset = AVCaptureSessionPresetMedium;
	session.sessionPreset = AVCaptureSessionPresetLow;
	
    // Find a suitable AVCaptureDevice
	NSArray *devices = [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
	AVCaptureDevice *frontDevice = nil;
	AVCaptureDevice *backDevice = nil;
	for (AVCaptureDevice *device in devices)
	{
		if ([device position] == AVCaptureDevicePositionBack)
		{
			backDevice = device;
		} else if ([device position] == AVCaptureDevicePositionFront)
		{
			frontDevice = device;
		}
		if ((frontDevice != nil) && (backDevice != nil))
		{
			break;
		}
	}
	
    // Create a device input with the device and add it to the session.
    self.backCameraDeviceInput = [AVCaptureDeviceInput deviceInputWithDevice:backDevice error:&error];
    if (!self.backCameraDeviceInput) {
        // Handling the error appropriately.
    }
	if ([session canAddInput:self.backCameraDeviceInput])
	{
		[session addInput:self.backCameraDeviceInput];
	}
	error = nil;
	self.frontCameraDeviceInput = [AVCaptureDeviceInput deviceInputWithDevice:frontDevice error:&error];
    if (!self.frontCameraDeviceInput) {
        // Handling the error appropriately.
    }
	self.backCamera = YES;
    
	
    // Create a VideoDataOutput and add it to the session
    AVCaptureVideoDataOutput *output = [[[AVCaptureVideoDataOutput alloc] init] autorelease];
    [session addOutput:output];
	
    // Configure your output.
    dispatch_queue_t queue = dispatch_queue_create("myQueue", NULL);
    [output setSampleBufferDelegate:self queue:queue];
    dispatch_release(queue);
	
    // Specify the pixel format
    output.videoSettings =
	[NSDictionary dictionaryWithObject:
	 [NSNumber numberWithInt:kCVPixelFormatType_32BGRA]
								forKey:(id)kCVPixelBufferPixelFormatTypeKey];
	
	
    // If you wish to cap the frame rate to a known value, such as 15 fps, set
    // minFrameDuration.
//    output.minFrameDuration = CMTimeMake(1, 15);
	
    // Start the session running to start the flow of data
    [session startRunning];
	
    // Assign session to an ivar.
    [self setSession:session];
}

// Delegate routine that is called when a sample buffer was written
- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection
{
	UIImage *realImage = [self imageFromSampleBuffer:sampleBuffer];
	cv::Mat capturedImage = [realImage CVMat];
	
	cv::transpose(capturedImage, capturedImage);
	if ([self isBackCamera])
	{
		cv::flip(capturedImage, capturedImage, 1);
	}
	
	std::string *asciiRepr = imageToTextConversor->newASCIIArtStringForImageMat(capturedImage, capturedImage, self.nRows, self.nColumns);
	
	NSString *string = [NSString stringWithCString:asciiRepr->c_str() encoding:NSUTF8StringEncoding];
	UIImage *usedImage = nil;
	if (![self.usedImageView isHidden])
	{
		usedImage = [UIImage imageWithCVMat:capturedImage];
	}
	
	dispatch_async(dispatch_get_main_queue(), ^{
		[self.imageTextRepresentationLabel setText:string];
		[self.usedImageView setImage:usedImage];
		[self.originalImageView setImage:realImage];
	});
	
	delete asciiRepr;

	
}

- (UIImage *) imageFromSampleBuffer:(CMSampleBufferRef) sampleBuffer
{
    // Get a CMSampleBuffer's Core Video image buffer for the media data
    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    // Lock the base address of the pixel buffer
    CVPixelBufferLockBaseAddress(imageBuffer, 0);
	
    // Get the number of bytes per row for the pixel buffer
    void *baseAddress = CVPixelBufferGetBaseAddress(imageBuffer);
	
    // Get the number of bytes per row for the pixel buffer
    size_t bytesPerRow = CVPixelBufferGetBytesPerRow(imageBuffer);
    // Get the pixel buffer width and height
    size_t width = CVPixelBufferGetWidth(imageBuffer);
    size_t height = CVPixelBufferGetHeight(imageBuffer);
	
    // Create a device-dependent RGB color space
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
	
    // Create a bitmap graphics context with the sample buffer data
    CGContextRef context = CGBitmapContextCreate(baseAddress, width, height, 8,
												 bytesPerRow, colorSpace, kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedFirst);
    // Create a Quartz image from the pixel data in the bitmap graphics context
    CGImageRef quartzImage = CGBitmapContextCreateImage(context);
    // Unlock the pixel buffer
    CVPixelBufferUnlockBaseAddress(imageBuffer,0);
	
    // Free up the context and color space
    CGContextRelease(context);
    CGColorSpaceRelease(colorSpace);
	
    // Create an image object from the Quartz image
    UIImage *image = [UIImage imageWithCGImage:quartzImage scale:1.0f orientation:([self isBackCamera] ? UIImageOrientationRight : UIImageOrientationLeftMirrored)];
	
    // Release the Quartz image
    CGImageRelease(quartzImage);
	
    return (image);
}


#pragma mark - UIGestureRecognizer
- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer
{
	return (![self.originalImageView isHidden] || ![self.usedImageView isHidden]);
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceiveTouch:(UITouch *)touch
{
	return (CGRectContainsPoint(self.originalImageView.frame, [touch locationInView:self.cameraContainerView]) ||
			CGRectContainsPoint(self.usedImageView.frame, [touch locationInView:self.cameraContainerView]));
}

#pragma mark - UIPanGestureRecognizer
- (void)panGestureRecognizerAction:(UIPanGestureRecognizer *)panGestureRecognizer
{
	if (panGestureRecognizer.state == UIGestureRecognizerStateBegan)
	{
		if (CGRectContainsPoint(self.originalImageView.frame, [panGestureRecognizer locationInView:self.cameraContainerView]))
		{
			self.movingView = self.originalImageView;
		} else if (CGRectContainsPoint(self.usedImageView.frame, [panGestureRecognizer locationInView:self.cameraContainerView]))
		{
			self.movingView = self.usedImageView;
		}
		if (self.movingView != nil)
		{
			[self.movingView.superview bringSubviewToFront:self.movingView];
		}
	} else if (panGestureRecognizer.state == UIGestureRecognizerStateChanged)
	{
		if (self.movingView != nil)
		{
			CGPoint position = [panGestureRecognizer locationInView:self.cameraContainerView];
			[self.movingView setFrame:CGRectMake(position.x-self.movingView.frame.size.width*0.5f, position.y-self.movingView.frame.size.height*0.5f, self.movingView.frame.size.width, self.movingView.frame.size.height)];
		}
	} else
	{
		if (self.movingView != nil)
		{
			UIView *otherView = ((self.movingView == self.usedImageView) ? self.originalImageView : self.usedImageView);
			BOOL otherVisible = (![otherView isHidden]);
			CGPoint destinyPoint;
			
			BOOL movingIsHalfLeft = ((self.movingView.frame.origin.x + self.movingView.frame.size.width*0.5f) < (self.cameraContainerView.frame.size.width*0.5f));
			BOOL movingIsHalfTop = ((self.movingView.frame.origin.y + self.movingView.frame.size.height*0.5f) < (self.cameraContainerView.frame.size.height*0.5f));
			
			BOOL otherIsHalfLeft = ((otherView.frame.origin.x + otherView.frame.size.width*0.5f) < (self.cameraContainerView.frame.size.width*0.5f));
			BOOL otherIsHalfTop = ((otherView.frame.origin.y + otherView.frame.size.height*0.5f) < (self.cameraContainerView.frame.size.height*0.5f));
			
			if (movingIsHalfLeft)
			{
				if (movingIsHalfTop)
				{
					if (otherVisible && otherIsHalfLeft && otherIsHalfTop)
					{
						destinyPoint = CGPointMake(0.0f, self.cameraContainerView.frame.size.height - self.movingView.frame.size.height);
					} else
					{
						destinyPoint = CGPointMake(0.0f, 0.0f);
					}
				} else
				{
					if (otherVisible && otherIsHalfLeft && !otherIsHalfTop)
					{
						destinyPoint = CGPointMake(0.0f, 0.0f);
					} else
					{
						destinyPoint = CGPointMake(0.0f, self.cameraContainerView.frame.size.height - self.movingView.frame.size.height);
					}
				}
			} else
			{
				if (movingIsHalfTop)
				{
					if (otherVisible && !otherIsHalfLeft && otherIsHalfTop)
					{
						destinyPoint = CGPointMake(self.cameraContainerView.frame.size.width - self.movingView.frame.size.width, self.cameraContainerView.frame.size.height - self.movingView.frame.size.height);
					} else
					{
						destinyPoint = CGPointMake(self.cameraContainerView.frame.size.width - self.movingView.frame.size.width, 0.0f);
					}
				} else
				{
					if (otherVisible && !otherIsHalfLeft && !otherIsHalfTop)
					{
						destinyPoint = CGPointMake(self.cameraContainerView.frame.size.width - self.movingView.frame.size.width, 0.0f);
					} else
					{
						destinyPoint = CGPointMake(self.cameraContainerView.frame.size.width - self.movingView.frame.size.width, self.cameraContainerView.frame.size.height - self.movingView.frame.size.height);
					}
				}
			}
			[UIView animateWithDuration:0.2 animations:^{
				[self.movingView setFrame:CGRectMake(destinyPoint.x, destinyPoint.y, self.movingView.frame.size.width, self.movingView.frame.size.height)];
			}];
		}
		self.movingView = nil;
	}
}

- (void)canvasSizeForFontSize:(float)fontSize nRows:(int &)nRows nColumns:(int &)nColumns
{
	UIFont *font = [UIFont fontWithName:[self.imageTextRepresentationLabel.font fontName] size:fontSize];
	CGSize oneCharSize = [@"X" sizeWithFont:font];
	
	int nChars = 1;
	NSMutableString *string = [NSMutableString stringWithString:@"X"];
	CGSize constrainedSize = CGSizeMake(self.imageTextRepresentationLabel.frame.size.width, FLT_MAX);
	BOOL sameLine = YES;
	while (sameLine)
	{
		[string appendString:@" X"];
		CGFloat requiredHeight = [string sizeWithFont:font constrainedToSize:constrainedSize].height;
		sameLine = (ABS(requiredHeight - oneCharSize.height) < 0.00001f);
		if (sameLine)
		{
			++nChars;
		}
	}
	
	nRows = (self.imageTextRepresentationLabel.frame.size.height / oneCharSize.height);
	nColumns = nChars;
}

@end
