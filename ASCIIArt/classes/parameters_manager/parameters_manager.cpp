//
//  parameters_manager.cpp
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 06/06/13.
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

#include "parameters_manager.h"

const std::string ParametersManager::INPUT_IMAGE_NAME = "_in_image_name_";
const std::string ParametersManager::OUTPUT_FILE_NAME = "_out_file_name_";
const std::string ParametersManager::INPUT_VIDEO = "_input_video_";
const std::string ParametersManager::HELP_DEMANDED = "_help_demanded_";
const std::string ParametersManager::ROWS = "_rows_";
const std::string ParametersManager::COLUMNS = "_columns_";
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
	} else if ((argument.compare("-rows") == 0) ||
			   (argument.compare("--rows") == 0))
	{
		return ROWS;
	} else if ((argument.compare("-columns") == 0) ||
			   (argument.compare("--columns") == 0))
	{
		return COLUMNS;
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

bool ParametersManager::nRows(int &nRows)
{
	const std::map<const std::string, std::string>::iterator it = this->parameters.find(ROWS);
	if (it != this->parameters.end())
	{
		nRows = atoi(it->second.c_str());
	}
	return (it != this->parameters.end());
}

bool ParametersManager::nColumns(int &nColumns)
{
	const std::map<const std::string, std::string>::iterator it = this->parameters.find(COLUMNS);
	if (it != this->parameters.end())
	{
		nColumns = atoi(it->second.c_str());
	}
	return (it != this->parameters.end());
}
