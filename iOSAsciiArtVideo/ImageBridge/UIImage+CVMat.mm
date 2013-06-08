//
//  UIImage+CVMat.m
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 07/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#import "UIImage+CVMat.h"

@implementation UIImage (CVMat)

-(cv::Mat)CVMat
{
	CGColorSpaceRef colorSpace = CGImageGetColorSpace(self.CGImage);
	
	CGFloat cols;
	CGFloat rows;
	
	if  (self.imageOrientation == UIImageOrientationLeft || self.imageOrientation == UIImageOrientationRight)
	{
		cols = self.size.height;
		rows = self.size.width;
    } else
	{
		cols = self.size.width;
		rows = self.size.height;
	}
	
	cv::Mat cvMat(rows, cols, CV_8UC4); // 8 bits per component, 4 channels
	
	CGContextRef contextRef = CGBitmapContextCreate(cvMat.data,                 // Pointer to backing data
													cols,                      // Width of bitmap
													rows,                     // Height of bitmap
													8,                          // Bits per component
													cvMat.step[0],              // Bytes per row
													colorSpace,                 // Colorspace
													kCGImageAlphaNoneSkipLast |
													kCGBitmapByteOrderDefault); // Bitmap info flags
	
	CGContextDrawImage(contextRef, CGRectMake(0, 0, cols, rows), self.CGImage);
	CGContextRelease(contextRef);
	
	return cvMat;
}

@end
