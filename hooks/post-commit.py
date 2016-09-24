#!/usr/bin/env python

from regenerate_projects import regenerate_projects
import sys

print("\nRunning post-commit hook ...\n")

regenerate_projects()
