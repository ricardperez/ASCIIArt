//
//  UIImage+CVMat.h
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 07/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#import <UIKit/UIKit.h>

namespace cv
{
	class Mat;
};

@interface UIImage (CVMat)

-(cv::Mat)CVMat;

@end
