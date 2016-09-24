#!/usr/bin/env python

from regenerate_projects import regenerate_projects
import sys

print("\nRunning post-rewrite hook ...\n")

# only run when rebasing to handle the 'git pull --rebase' case
if not sys.argv[1] == "rebase":
	print("Operation is not a rebase; exiting.")
	sys.exit(0)

regenerate_projects()
