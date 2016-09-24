#!/bin/sh

HOOKS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
GITHOOKS_DIR="$HOOKS_DIR/../.git/hooks"

# copy to git hooks folder
cp "$HOOKS_DIR/post-checkout.py" "$GITHOOKS_DIR/post-checkout"
cp "$HOOKS_DIR/post-commit.py" "$GITHOOKS_DIR/post-commit"
cp "$HOOKS_DIR/post-merge.py" "$GITHOOKS_DIR/post-merge"
cp "$HOOKS_DIR/post-rewrite.py" "$GITHOOKS_DIR/post-rewrite"
cp "$HOOKS_DIR/regenerate_projects.py" "$GITHOOKS_DIR/regenerate_projects.py"

# make git hooks executable
chmod 755 "$GITHOOKS_DIR/post-checkout"
chmod 755 "$GITHOOKS_DIR/post-commit"
chmod 755 "$GITHOOKS_DIR/post-merge"
chmod 755 "$GITHOOKS_DIR/post-rewrite"
