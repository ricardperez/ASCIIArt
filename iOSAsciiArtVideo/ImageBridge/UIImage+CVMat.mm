//
//  UIImage+CVMat.m
//  ASCIIArt
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

#import "UIImage+CVMat.h"

@implementation UIImage (CVMat)

-(cv::Mat)CVMat
{
	CGColorSpaceRef colorSpace = CGImageGetColorSpace(self.CGImage);
	
	CGFloat cols = self.size.height;
	CGFloat rows = self.size.width;
	
//	if  (self.imageOrientation == UIImageOrientationLeft || self.imageOrientation == UIImageOrientationRight)
//	{
//		cols = self.size.height;
//		rows = self.size.width;
//    } else
//	{
//		cols = self.size.width;
//		rows = self.size.height;
//	}
	
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


+ (UIImage *)imageWithCVMat:(const cv::Mat&)cvMat
{
    NSData *data = [NSData dataWithBytes:cvMat.data length:cvMat.elemSize() * cvMat.total()];
	
    CGColorSpaceRef colorSpace;
	
    if (cvMat.elemSize() == 1) {
        colorSpace = CGColorSpaceCreateDeviceGray();
    } else {
        colorSpace = CGColorSpaceCreateDeviceRGB();
    }
	
    CGDataProviderRef provider = CGDataProviderCreateWithCFData((CFDataRef)data);
	
    CGImageRef imageRef = CGImageCreate(cvMat.cols,                                     // Width
										cvMat.rows,                                     // Height
										8,                                              // Bits per component
										8 * cvMat.elemSize(),                           // Bits per pixel
										cvMat.step[0],                                  // Bytes per row
										colorSpace,                                     // Colorspace
										kCGImageAlphaNone | kCGBitmapByteOrderDefault,  // Bitmap info flags
										provider,                                       // CGDataProviderRef
										NULL,                                           // Decode
										false,                                          // Should interpolate
										kCGRenderingIntentDefault);                     // Intent
	
    UIImage *image = [[[UIImage alloc] initWithCGImage:imageRef] autorelease];
    CGImageRelease(imageRef);
    CGDataProviderRelease(provider);
    CGColorSpaceRelease(colorSpace);
	
    return image;
}

@end
