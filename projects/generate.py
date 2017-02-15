import os
import subprocess
import sys

# get the path to the directory containing the script
projects_directory = os.path.dirname(os.path.realpath(__file__))

# check for command-line argument
if len(sys.argv) < 2:
	print("Incorrect number of arguments!\n")
	print("Usage: python generate.py <platform>\n\twhere <platform> is (win|mac|linux)\n")
	sys.exit(-1)

desired_platform = sys.argv[1]
platform_name = sys.platform
platform_folder = ""
cmake_command = "cmake ../"

if desired_platform == "win":
	if platform_name == "win32":
		platform_folder = "win"
		cmake_command += " -G \"Visual Studio 14 2015\""
	else:
		print("Generating projects for Windows is only supported on Windows.\n")
		sys.exit(-1)
elif desired_platform == "mac":
	if platform_name == "darwin":
		platform_folder = "mac"
		cmake_command += " -G \"Xcode\""
	else:
		print("Generating projects for macOS is only supported on macOS.\n")
		sys.exit(-1)
elif desired_platform == "linux":
	if platform_name.startswith("linux"):
		platform_folder = "linux"
		if "COMPILER" in os.environ:
			cmake_command = "CXX=$COMPILER {0} -G \"Unix Makefiles\"".format(cmake_command)
		else: 
			cmake_command = "CXX=clang++ {0} -G \"Unix Makefiles\"".format(cmake_command)
	else:
		print("Generating projects for Linux is only supported on Linux.\n")
		sys.exit(-1)
else:
	print("Unsupported platform '{0}'.".format(desired_platform))
	sys.exit(-1)

# create the platform specific project folder if it does not exist
platform_project_directory = os.path.join(projects_directory, platform_folder)
if not os.path.exists(platform_project_directory):
	os.makedirs(platform_project_directory)

# run CMake from within the platform specific folder
os.chdir(platform_project_directory)
result = subprocess.call(cmake_command, shell=True)

# return early if CMake failed
if not result == 0:
	sys.exit(result)

projects_timestamp_file = os.path.join(projects_directory, ".projects_timestamp")
if not os.path.exists(projects_timestamp_file):
	open(projects_timestamp_file, 'w')
	
os.utime(projects_timestamp_file, None)
