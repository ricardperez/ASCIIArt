//
//  parameters_manager.h
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
	bool argumentIsInputVideo(const std::string &argument) const;
	const std::string parametersKeyForKeyArgument(const std::string &argument) const;
public:
	static const std::string INPUT_IMAGE_NAME;
	static const std::string OUTPUT_FILE_NAME;
	static const std::string INPUT_VIDEO;
	static const std::string HELP_DEMANDED;
	static const std::string ROWS;
	static const std::string COLUMNS;
	static const std::string UNKNOWN_PARAMETER;
	
	ParametersManager(int argc, const char *argv[]);
	
	bool inputImageName(std::string *inputNameRef);
	bool outputFileName(std::string *outputNameRef);
	bool helpWasDemanded() const;
	bool inputVideoWasDemanded() const;
	bool unknownParameter(std::string *parameterRef);
	bool nRows(int &nRows);
	bool nColumns(int &nColumns);
};

#endif /* defined(__ASCIIArt__parameters_manager__) */
