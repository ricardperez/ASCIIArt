//
//  parameters_manager.cpp
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 06/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#include "parameters_manager.h"

const std::string ParametersManager::INPUT_IMAGE_NAME = "_in_image_name_";
const std::string ParametersManager::OUTPUT_FILE_NAME = "_out_file_name_";
const std::string ParametersManager::INPUT_VIDEO = "_input_video_";
const std::string ParametersManager::HELP_DEMANDED = "_help_demanded_";
const std::string ParametersManager::UNKNOWN_PARAMETER = "_unknown_parameter_";


ParametersManager::ParametersManager(int argc, const char *argv[])
{
	for (int i=1; i<argc; ++i)
	{
		std::string nextArg = argv[i];
		if (this->argumentIsAKey(nextArg))
		{
			++i;
			if (i<argc)
			{
				this->parameters[this->parametersKeyForKeyArgument(nextArg)] = argv[i];
			}
		} else if (this->argumentIsHelp(nextArg))
		{
			this->parameters[HELP_DEMANDED] = argv[i];
		} else if (this->argumentIsInputVideo(nextArg))
		{
			this->parameters[INPUT_VIDEO] = argv[i];
		} else
		{
			if (!this->inputImageName(0))
			{
				this->parameters[INPUT_IMAGE_NAME] = argv[i];
			} else if (!this->outputFileName(0))
			{
				this->parameters[OUTPUT_FILE_NAME] = argv[i];
			} else
			{
				this->parameters[UNKNOWN_PARAMETER] = argv[i];
			}
		}
	}
}

bool ParametersManager::argumentIsAKey(const std::string &argument) const
{
	return (this->parametersKeyForKeyArgument(argument).length() > 0);
}

bool ParametersManager::argumentIsHelp(const std::string &argument) const
{
	return ((argument.compare("--help") == 0) ||
			(argument.compare("-help") == 0) ||
			(argument.compare("-h") == 0));
}

bool ParametersManager::argumentIsInputVideo(const std::string &argument) const
{
	return ((argument.compare("--camera") == 0) ||
			(argument.compare("-camera") == 0) ||
			(argument.compare("-video") == 0));
}

const std::string ParametersManager::parametersKeyForKeyArgument(const std::string &argument) const
{
	if ((argument.compare("-input") == 0) ||
		(argument.compare("--input") == 0) ||
		(argument.compare("-image") == 0) ||
		(argument.compare("--image") == 0))
	{
		return INPUT_IMAGE_NAME;
	} else if ((argument.compare("-output") == 0) ||
			   (argument.compare("--output") == 0) ||
			   (argument.compare("-out") == 0) ||
			   (argument.compare("--out") == 0))
	{
		return OUTPUT_FILE_NAME;
	} else
	{
		return "";
	}
}



bool ParametersManager::inputImageName(std::string *inputNameRef)
{
	const std::map<const std::string, std::string>::iterator it = this->parameters.find(INPUT_IMAGE_NAME);
	if (it != this->parameters.end())
	{
		if (inputNameRef != 0)
		{
			*inputNameRef = it->second;
		}
	}
	return (it != this->parameters.end());
}

bool ParametersManager::outputFileName(std::string *outputNameRef)
{
	const std::map<const std::string, std::string>::iterator it = this->parameters.find(OUTPUT_FILE_NAME);
	if (it != this->parameters.end())
	{
		if (outputNameRef != 0)
		{
			*outputNameRef = it->second;
		}
	}
	return (it != this->parameters.end());
}

bool ParametersManager::helpWasDemanded() const
{
	return (this->parameters.find(HELP_DEMANDED) != this->parameters.end());
}

bool ParametersManager::unknownParameter(std::string *parameterRef)
{
	const std::map<const std::string, std::string>::iterator it = this->parameters.find(UNKNOWN_PARAMETER);
	if (it != this->parameters.end())
	{
		if (parameterRef != 0)
		{
			*parameterRef = it->second;
		}
	}
	return (it != this->parameters.end());
}

bool ParametersManager::inputVideoWasDemanded() const
{
	return (this->parameters.find(INPUT_VIDEO) != this->parameters.end());
}
