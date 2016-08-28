import os
import subprocess
import sys

# get the path to the directory containing the script
projects_directory = os.path.dirname(os.path.realpath(__file__))

platform_name = sys.platform
platform_folder = ""
if platform_name == 'win32':
	platform_folder = "win"
elif platform_name == 'darwin':
	platform_folder = "mac"
else:
	print("Unsupported platform %s." % platform_name)
	sys.exit(-1)

# create the platform specific project folder if it does not exist
platform_project_directory = os.path.join(projects_directory, platform_folder)
if not os.path.exists(platform_project_directory):
	os.makedirs(platform_project_directory)

# run CMake from within the platform specific folder
os.chdir(platform_project_directory)
result = subprocess.run("cmake ../")
if not result.returncode == 0:
	sys.exit(result.returncode)
