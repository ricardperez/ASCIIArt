//
//  parameters_manager.h
//  ASCIIArt
//
//  Created by Ricard Pérez del Campo on 06/06/13.
//  Copyright (c) 2013 Ricard Pérez del Campo. All rights reserved.
//

#ifndef __ASCIIArt__parameters_manager__
#define __ASCIIArt__parameters_manager__

#include <iostream>
#include <map>

class ParametersManager
{
private:
	std::map<const std::string, std::string> parameters;
	bool argumentIsAKey(const std::string &argument) const;
	bool argumentIsHelp(const std::string &argument) const;
	const std::string parametersKeyForKeyArgument(const std::string &argument) const;
public:
	static const std::string INPUT_IMAGE_NAME;
	static const std::string OUTPUT_FILE_NAME;
	static const std::string HELP_DEMANDED;
	static const std::string UNKNOWN_PARAMETER;
	
	ParametersManager(int argc, const char *argv[]);
	
	bool inputImageName(std::string *inputNameRef);
	bool outputFileName(std::string *outputNameRef);
	bool helpWasDemanded() const;
	bool unknownParameter(std::string *parameterRef);
};

#endif /* defined(__ASCIIArt__parameters_manager__) */
