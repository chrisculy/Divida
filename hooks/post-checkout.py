#!/usr/bin/env python

import os
import subprocess
import sys

print("\nRunning post-checkout hook ...\n")

current_working_directory = os.getcwd()
projects_timestamp_file = os.path.join(current_working_directory, "projects/.projects_timestamp")
if not os.path.exists(projects_timestamp_file):
	open(projects_timestamp_file, 'x')

print("Generating projects now ...\n")
projects_directory = os.path.join(current_working_directory, "projects")
if not os.path.isdir(projects_directory):
	print("Failed to locate 'projects' directory here: " + projects_directory)
	sys.exit(-1)

sys.stdout.flush();

os.chdir(projects_directory)
result = subprocess.run("python generate.py")
if not result.returncode == 0:
	sys.exit(result.returncode)

os.utime(projects_timestamp_file)
