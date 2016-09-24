#!/usr/bin/env python

from regenerate_projects import regenerate_projects

print("\nRunning post-merge hook ...\n")

regenerate_projects()
