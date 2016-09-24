#!/bin/sh

HOOKS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
GITHOOKS_DIR="$HOOKS_DIR/../.git/hooks"

# copy to git hooks folder
cp "$HOOKS_DIR/post-checkout.py" "$GITHOOKS_DIR/post-checkout"
cp "$HOOKS_DIR/post-merge.py" "$GITHOOKS_DIR/post-merge"

# make git hooks executable
chmod 755 "$GITHOOKS_DIR/post-checkout"
chmod 755 "$GITHOOKS_DIR/post-merge"
