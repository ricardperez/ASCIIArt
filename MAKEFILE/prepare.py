import os
import sys
import shutil
import filecmp

def MoveFilesRecursively(dir):
	if filecmp.dircmp(dir, os.getcwd()):
		for (dirpath, dirnames, filenames) in os.walk(dir):
			for filename in filenames:
				filenameWithoutExtension, fileExtension = os.path.splitext(filename)
				if fileExtension == '.cpp' or fileExtension == '.h':
					print "Copying file " + (dirpath+"/"+filename) + " to " + (os.getcwd()+"/"+filename)
					shutil.copy((dirpath+"/"+filename), (os.getcwd()+"/"+filename))
			for dirname in dirnames:
				MoveFilesRecursively(dirname)
	else:
		print "Skipping " + dir + " because it's equal to cwd: " + os.getcwd()

root_dir = "../ASCIIArt/"
MoveFilesRecursively(os.path.abspath(root_dir))