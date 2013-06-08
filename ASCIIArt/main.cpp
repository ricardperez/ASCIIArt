//
//  main.cpp
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 06/06/13.
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

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include "ascii_art.h"
#include "camera_to_ascii_art.h"
#include "parameters_manager.h"
#include <opencv2/opencv.hpp>

void displayHelp();
int main(int argc, const char * argv[])
{
	std::string inputImageName, outputFileName, unknownParameter;
	ParametersManager paramsManager(argc, argv);
	
	int nRows = -1;
	int nColumns = -1;
	
	if (paramsManager.helpWasDemanded())
	{
		displayHelp();
	} else
	{
		bool displayMoreInfo = false;
		bool imageGiven = false;
		bool outputFileGiven = false;
		bool cameraInputDemanded = false;
		
		paramsManager.nRows(nRows);
		paramsManager.nColumns(nColumns);
		
		if (paramsManager.unknownParameter(&unknownParameter))
		{
			std::cout << "Unknown parameter: \"" << unknownParameter << "\"" << std::endl;
		}
		
		cameraInputDemanded = paramsManager.inputVideoWasDemanded();
		if (!cameraInputDemanded)
		{
			imageGiven = paramsManager.inputImageName(&inputImageName);
			if (!imageGiven)
			{
				std::cout << "You need to specify the name of the image you want to convert to ASCII art." << std::endl;
				displayMoreInfo = true;
			}
			
			outputFileGiven = paramsManager.outputFileName(&outputFileName);
			if (!outputFileGiven)
			{
				std::cout << "You need to specify the name of the output file where to write the image in ASCII characters." << std::endl;
				displayMoreInfo = true;
			}
		}
		
		if (displayMoreInfo)
		{
			std::cout << "Run the program with the -help parameter for more info." << std::endl;
		}
		
		if (cameraInputDemanded)
		{
			CameraToASCIIArt cameraToASCII;
			std::string frameStr;
			while (1)
			{
				cameraToASCII.currentFrameASCII(frameStr, nRows, nColumns);
				std::cout << frameStr << std::endl;
				frameStr.clear();
			}
			
		} else if (imageGiven && outputFileGiven)
		{
			clock_t startClock = clock();
			ASCIIArt asciiArt;
			cv::Mat resultImage;
			std::string *strImageRepresentation = asciiArt.newASCIIArtStringForImageName(inputImageName, resultImage, nRows, nColumns);
			clock_t endClock = clock();
			
			
			std::ofstream outputFile;
			outputFile.open(outputFileName.c_str());
			outputFile << (*strImageRepresentation);
			outputFile.close();
			clock_t outputEndClock = clock();
			
			delete strImageRepresentation;
			
			std::cout << "An ASCII representation of the image was saved to " << outputFileName << std::endl;
			std::cout << "Conversion time: " << (((float)(endClock - startClock)) / CLOCKS_PER_SEC) << std::endl;
			std::cout << "Total time: " << (((float)(outputEndClock - startClock)) / CLOCKS_PER_SEC) << std::endl;
		}
	}
	
	
	return 0;
}



void displayHelp()
{
	std::cout << "Welcome to the ASCII Art software." << std::endl;
	std::cout << "These are the accepted parameters for this program:" << std::endl;
	std::cout << "    -input input_image" << " <- to use that image as input" << std::endl;
	std::cout << "    -output output_file" << " <- to write the ascii characters to that file" << std::endl;
	std::cout << "    -camera" << " <- to get a realtime ascii representation of the camera input" << std::endl;
	std::cout << "    -rows nRows" << " <- to specify the number of rows to use" << std::endl;
	std::cout << "    -columns nColumns" << " <- to specify the number of columns to use" << std::endl;
	std::cout << "    -help" << " <- to display this help menu" << std::endl;
}

