//
//  main.cpp
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 06/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include "ascii_art.h"
#include "parameters_manager.h"

void displayHelp();
int main(int argc, const char * argv[])
{
	std::string inputImageName, outputFileName, unknownParameter;
	ParametersManager paramsManager(argc, argv);
	
	if (paramsManager.helpWasDemanded())
	{
		displayHelp();
	} else
	{
		bool displayMoreInfo = false;
		bool imageGiven = false;
		bool outputFileGiven = false;
		
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
		
		if (paramsManager.unknownParameter(&unknownParameter))
		{
			std::cout << "Unknown parameter: \"" << unknownParameter << "\"" << std::endl;
		}
		
		if (displayMoreInfo)
		{
			std::cout << "Run the program with the -help parameter for more info." << std::endl;
		}
		
		if (imageGiven && outputFileGiven)
		{
			ASCIIArt asciiArt;
			std::string *strImageRepresentation = asciiArt.newASCIIArtStringForImageName(inputImageName);
			
			std::ofstream outputFile;
			outputFile.open(outputFileName);
			outputFile << (*strImageRepresentation);
			
			delete strImageRepresentation;
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
	std::cout << "    -help" << " <- to display this help menu" << std::endl;
}

