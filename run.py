import sys
import os
import subprocess

def preparePath():
	currentDir = os.getcwd()
	folders = ["shaders", "textures", "meshes", "Run"]
	for folder in folders:
		path = currentDir + os.sep + folder
		sys.path.append(path)

def run():
	procHandler = subprocess.Popen("Run" + os.sep + "ex2.exe")
		
def main():
	preparePath()
	run()

if __name__ == "__main__":
	main()