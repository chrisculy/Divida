#!/usr/bin/env python

import regenerate_projects
import sys

print("\nRunning post-checkout hook ...\n")

is_branch_checkout = sys.argv[3] == '1'
if not is_branch_checkout:
	print("Not a branch checkout; exiting.")
	sys.exit(0)

regenerate_projects()
