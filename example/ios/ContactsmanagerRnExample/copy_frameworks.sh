#!/bin/bash

# Define paths
FRAMEWORK_PATH="$PODS_ROOT/../../ios/Frameworks/ContactsManagerObjc.xcframework"
TARGET_PATH="$BUILT_PRODUCTS_DIR/$FRAMEWORKS_FOLDER_PATH"
TEAM_ID="2C87X9VM3V"

# Log debug info
echo "FRAMEWORK_PATH: $FRAMEWORK_PATH"
echo "TARGET_PATH: $TARGET_PATH"
echo "PLATFORM_NAME: $PLATFORM_NAME"
echo "CONFIGURATION: $CONFIGURATION"
echo "EXPANDED_CODE_SIGN_IDENTITY: $EXPANDED_CODE_SIGN_IDENTITY"

# Create destination directory if it doesn't exist
mkdir -p "$TARGET_PATH"

# Determine which slice to use
if [[ "$PLATFORM_NAME" == *simulator* ]]; then
  echo "Copying simulator framework..."

  FRAMEWORK_SLICE="$FRAMEWORK_PATH/ios-arm64_x86_64-simulator/ContactsManagerObjc.framework"

  # Check if path exists
  if [[ ! -d "$FRAMEWORK_SLICE" ]]; then
    echo "Error: Framework slice not found at $FRAMEWORK_SLICE"
    exit 1
  fi

  cp -R "$FRAMEWORK_SLICE" "$TARGET_PATH/"
else
  echo "Copying device framework..."

  FRAMEWORK_SLICE="$FRAMEWORK_PATH/ios-arm64/ContactsManagerObjc.framework"

  # Check if path exists
  if [[ ! -d "$FRAMEWORK_SLICE" ]]; then
    echo "Error: Framework slice not found at $FRAMEWORK_SLICE"
    exit 1
  fi

  cp -R "$FRAMEWORK_SLICE" "$TARGET_PATH/"
fi

FRAMEWORK_EXECUTABLE_PATH="$TARGET_PATH/ContactsManagerObjc.framework/ContactsManagerObjc"

# Make sure the binary is executable
chmod +x "$FRAMEWORK_EXECUTABLE_PATH"

# Find the developer identity for the team
if [ -z "$EXPANDED_CODE_SIGN_IDENTITY" ]; then
  echo "No expanded code sign identity provided, looking for one from the team..."
  IDENTITY=$(security find-identity -v -p codesigning | grep "$TEAM_ID" | head -1 | awk '{print $2}')

  if [ -z "$IDENTITY" ]; then
    echo "Warning: No identity found for team ID: $TEAM_ID"
    echo "Available identities:"
    security find-identity -v -p codesigning
  else
    echo "Using identity: $IDENTITY for team: $TEAM_ID"
    EXPANDED_CODE_SIGN_IDENTITY="$IDENTITY"
  fi
fi

# Make sure frameworks are signed properly
if [ -n "$EXPANDED_CODE_SIGN_IDENTITY" ]; then
  echo "Signing framework with identity: $EXPANDED_CODE_SIGN_IDENTITY"

  # First strip any existing signatures
  codesign --force --deep --preserve-metadata=identifier,entitlements --sign "" "$TARGET_PATH/ContactsManagerObjc.framework"

  # Then re-sign with our identity
  codesign --force --deep --sign "$EXPANDED_CODE_SIGN_IDENTITY" --preserve-metadata=identifier,entitlements --verbose "$TARGET_PATH/ContactsManagerObjc.framework"

  # Verify the signature
  codesign -v "$TARGET_PATH/ContactsManagerObjc.framework"
else
  echo "No code signing identity found, skipping signing"
fi

echo "Framework copied successfully to $TARGET_PATH"
