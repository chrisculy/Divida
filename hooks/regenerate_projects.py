import datetime
import os
import subprocess
import sys

def regenerate_projects():
	should_regenerate_projects = False

	current_working_directory = os.getcwd()
	projects_timestamp_file = os.path.join(current_working_directory, "projects/.projects_timestamp")
	if not os.path.exists(projects_timestamp_file):
		open(projects_timestamp_file, 'x')
		should_regenerate_projects = True

	if not should_regenerate_projects:
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
				should_regenerate_projects = True
				break

	if should_regenerate_projects:
		print("Regenerating projects now ...\n")
		projects_directory = os.path.join(current_working_directory, "projects")
		if not os.path.isdir(projects_directory):
			print("Failed to locate 'projects' directory here: " + projects_directory)
			sys.exit(-1)

		sys.stdout.flush();
		
		# regenerate for each platform that the user has already generated for
		valid_platforms = [ "win", "mac", "linux" ]
		os.chdir(projects_directory)
		for folder in os.listdir("."):
			if folder in valid_platforms and os.path.isdir(folder):
				result = subprocess.call("python generate.py " + folder)
				if not result == 0:
					sys.exit(result)
	else:
		print("Projects are up-to-date.")
