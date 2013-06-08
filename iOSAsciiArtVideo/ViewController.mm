//
//  ViewController.m
//  iOSAsciiArtVideo
//
//  Created by Ricard Pérez del Campo on 07/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#import "ViewController.h"
#import <CoreGraphics/CoreGraphics.h>
#import <ImageIO/ImageIO.h>
#include "ascii_art.h"

#define CAPTURE_FRAMES_PER_SECOND		20

@interface ViewController ()
{
	ASCIIArt *imageToTextConversor;
}

@property (nonatomic, retain) AVCaptureDeviceInput *frontCameraDeviceInput;
@property (nonatomic, retain) AVCaptureDeviceInput *backCameraDeviceInput;
@property (nonatomic, assign, getter = isBackCamera) BOOL backCamera;

@end


@implementation ViewController

- (void)dealloc
{
	[_imageTextRepresentationLabel release];
	[_flipCameraButton release];
	[_session release];
	[_frontCameraDeviceInput release];
	[_backCameraDeviceInput release];
	[_debugImageView release];
	
	delete imageToTextConversor;
	
	[super dealloc];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewDidUnload
{
	[super viewDidUnload];
	
	self.imageTextRepresentationLabel = nil;
	self.flipCameraButton = nil;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	imageToTextConversor = new ASCIIArt();
	
	[self setupCaptureSession];
		
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation
{
	return (toInterfaceOrientation == UIInterfaceOrientationPortrait);
}

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



// Create and configure a capture session and start it running
- (void)setupCaptureSession
{
    NSError *error = nil;
	
    // Create the session
    AVCaptureSession *session = [[[AVCaptureSession alloc] init] autorelease];
	
    // Configure the session to produce lower resolution video frames, if your
    // processing algorithm can cope. We'll specify medium quality for the
    // chosen device.
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
	cv::Mat capturedImage = [self imageCVMatFromSampleBuffer:sampleBuffer];
	cv::Mat result;
	std::string *asciiRepr = imageToTextConversor->newASCIIArtStringForImageMat(capturedImage, result, 30, 19);
	
	NSString *string = [NSString stringWithCString:asciiRepr->c_str() encoding:NSUTF8StringEncoding];
	UIImage *image = [self imageFromSampleBuffer:sampleBuffer];
	dispatch_async(dispatch_get_main_queue(), ^{
		[self.imageTextRepresentationLabel setText:string];
		[self.debugImageView setImage:image];
	});
	
	delete asciiRepr;

	
}

- (cv::Mat)imageCVMatFromSampleBuffer:(CMSampleBufferRef)sampleBuffer
{
	CVImageBufferRef pixelBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
	
	CVPixelBufferLockBaseAddress( pixelBuffer, 0 );
	
	int bufferWidth = CVPixelBufferGetWidth(pixelBuffer);
	int bufferHeight = CVPixelBufferGetHeight(pixelBuffer);
	unsigned char *pixel = (unsigned char *)CVPixelBufferGetBaseAddress(pixelBuffer);
	cv::Mat image = cv::Mat(bufferHeight,bufferWidth,CV_8UC4,pixel); //put buffer in open cv, no memory copied
	//Processing here
	
	//End processing
	CVPixelBufferUnlockBaseAddress( pixelBuffer, 0 );
	
//	cvTranspose(&image, &image);
	cv::transpose(image, image);
	
	return image;
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

@end
