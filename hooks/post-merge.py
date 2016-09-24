#!/usr/bin/env python

import datetime
import os
import subprocess
import sys

print("\nRunning post-merge hook ...\n")

regenerate_projects = False

current_working_directory = os.getcwd()
projects_timestamp_file = os.path.join(current_working_directory, "projects/.projects_timestamp")
if not os.path.exists(projects_timestamp_file):
	open(projects_timestamp_file, 'x')
	regenerate_projects = True

if not regenerate_projects:
	project_last_generated_time = os.path.getmtime(projects_timestamp_file)
	print("Project files were last generated automatically at '" + str(datetime.datetime.fromtimestamp(project_last_generated_time)) + "'.")

	project_files_file_path = os.path.join(current_working_directory, "projects/cmake.project")
	if not os.path.exists(project_files_file_path):
		print("Failed to locate project files file: " + project_files_file_path)
		sys.exit(-1)

	project_files_file = open(project_files_file_path, 'r')
	for project_file in project_files_file:
		project_file = project_file.strip()
		project_file_path = os.path.join(current_working_directory, project_file)
		current_project_file_modified_time = os.path.getmtime(project_file_path)
		if current_project_file_modified_time > project_last_generated_time:
			print("Project file '" + project_file + "' was modified at '" + str(datetime.datetime.fromtimestamp(current_project_file_modified_time)) + "', after last automatic project generation.")
			regenerate_projects = True
			break

if regenerate_projects:
	print("Regenerating projects now ...\n")
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
else:
	print("Projects are up-to-date.")