#!/bin/bash

# Script to publish the contactsmanager-rn package to npm

# Ensure we're in the right directory
cd "$(dirname "$0")/.." || exit

# Colors for terminal output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}Preparing to publish contactsmanager-rn to npm...${NC}"

# Check that we have the xcframework
if [ ! -d "ios/Frameworks/ContactsManagerObjc.xcframework" ]; then
  echo -e "${RED}Error: ContactsManagerObjc.xcframework not found!${NC}"
  echo -e "Make sure the framework is in ios/Frameworks/ContactsManagerObjc.xcframework"
  exit 1
fi

# Run the build and prepare script
echo -e "${YELLOW}Building and preparing package...${NC}"
npm run prepare

# Check if there are uncommitted changes
if [ -n "$(git status --porcelain)" ]; then
  echo -e "${RED}Error: There are uncommitted changes in the repository.${NC}"
  echo -e "Please commit or stash your changes before publishing."
  git status
  exit 1
fi

# Publish to npm
echo -e "${YELLOW}Publishing to npm...${NC}"
npm publish

# Check if publish was successful
if [ $? -eq 0 ]; then
  echo -e "${GREEN}Success! Package published to npm.${NC}"

  # Extract version from package.json
  VERSION=$(node -p "require('./package.json').version")

  # Create git tag
  git tag -a "v$VERSION" -m "Version $VERSION"

  # Push tag
  echo -e "${YELLOW}Pushing git tag v$VERSION...${NC}"
  git push origin "v$VERSION"

  echo -e "${GREEN}Package v$VERSION successfully published and tagged.${NC}"
else
  echo -e "${RED}Error publishing package. Please check the logs above.${NC}"
  exit 1
fi
