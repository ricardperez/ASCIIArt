//
//  parameters_manager.h
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
