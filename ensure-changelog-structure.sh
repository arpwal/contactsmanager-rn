#!/bin/bash

# Script to ensure frontend/public/changelogs directory exists
# and create it if it doesn't

set -e

REPO_DIR=$1
CHANGELOG_DIR="${REPO_DIR}/frontend/public/changelogs"

if [ ! -d "$REPO_DIR" ]; then
    echo "Error: Repository directory does not exist: $REPO_DIR"
    exit 1
fi

# Check if frontend directory exists, create if not
if [ ! -d "${REPO_DIR}/frontend" ]; then
    echo "Creating frontend directory..."
    mkdir -p "${REPO_DIR}/frontend"
fi

# Check if public directory exists, create if not
if [ ! -d "${REPO_DIR}/frontend/public" ]; then
    echo "Creating frontend/public directory..."
    mkdir -p "${REPO_DIR}/frontend/public"
fi

# Check if changelogs directory exists, create if not
if [ ! -d "$CHANGELOG_DIR" ]; then
    echo "Creating changelogs directory..."
    mkdir -p "$CHANGELOG_DIR"
fi

echo "Changelog directory structure verified: $CHANGELOG_DIR"
