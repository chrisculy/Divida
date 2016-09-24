#!/usr/bin/env python

from regenerate_projects import regenerate_projects

print("\nRunning post-commit hook ...\n")

regenerate_projects()
