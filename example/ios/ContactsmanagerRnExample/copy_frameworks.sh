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

# First, check if the xcframework exists
if [[ ! -d "$FRAMEWORK_PATH" ]]; then
  echo "Error: Framework not found at $FRAMEWORK_PATH"
  exit 0 # Exit gracefully, don't fail the build
fi

# List available slices for debugging
echo "Available slices:"
ls -la "$FRAMEWORK_PATH"

# Check which slices are available
SIMULATOR_SLICE="$FRAMEWORK_PATH/ios-arm64_x86_64-simulator/ContactsManagerObjc.framework"
DEVICE_SLICE="$FRAMEWORK_PATH/ios-arm64/ContactsManagerObjc.framework"
HAS_SIMULATOR_SLICE=false
HAS_DEVICE_SLICE=false

if [[ -d "$SIMULATOR_SLICE" ]]; then
  HAS_SIMULATOR_SLICE=true
  echo "Simulator slice exists"
fi

if [[ -d "$DEVICE_SLICE" ]]; then
  HAS_DEVICE_SLICE=true
  echo "Device slice exists"
fi

# Determine which slice to use
if [[ "$PLATFORM_NAME" == *simulator* ]]; then
  echo "Building for simulator..."

  if [[ "$HAS_SIMULATOR_SLICE" == true ]]; then
    echo "Using simulator slice"
    FRAMEWORK_SLICE="$SIMULATOR_SLICE"
  elif [[ "$HAS_DEVICE_SLICE" == true ]]; then
    echo "Simulator slice not found, using device slice as fallback"
    FRAMEWORK_SLICE="$DEVICE_SLICE"
  else
    echo "No appropriate framework slice found, skipping"
    exit 0 # Exit gracefully
  fi
else
  echo "Building for device..."

  if [[ "$HAS_DEVICE_SLICE" == true ]]; then
    echo "Using device slice"
    FRAMEWORK_SLICE="$DEVICE_SLICE"
  elif [[ "$HAS_SIMULATOR_SLICE" == true ]]; then
    echo "Device slice not found, using simulator slice as fallback"
    FRAMEWORK_SLICE="$SIMULATOR_SLICE"
  else
    echo "No appropriate framework slice found, skipping"
    exit 0 # Exit gracefully
  fi
fi

# Copy the framework
echo "Copying framework from $FRAMEWORK_SLICE to $TARGET_PATH/"
cp -R "$FRAMEWORK_SLICE" "$TARGET_PATH/"

FRAMEWORK_EXECUTABLE_PATH="$TARGET_PATH/ContactsManagerObjc.framework/ContactsManagerObjc"

# Make sure the binary is executable
if [[ -f "$FRAMEWORK_EXECUTABLE_PATH" ]]; then
  chmod +x "$FRAMEWORK_EXECUTABLE_PATH"
else
  echo "Warning: Framework executable not found at $FRAMEWORK_EXECUTABLE_PATH"
fi

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
if [ -n "$EXPANDED_CODE_SIGN_IDENTITY" ] && [ -d "$TARGET_PATH/ContactsManagerObjc.framework" ]; then
  echo "Signing framework with identity: $EXPANDED_CODE_SIGN_IDENTITY"

  # First strip any existing signatures
  codesign --force --deep --preserve-metadata=identifier,entitlements --sign "" "$TARGET_PATH/ContactsManagerObjc.framework" || true

  # Then re-sign with our identity
  codesign --force --deep --sign "$EXPANDED_CODE_SIGN_IDENTITY" --preserve-metadata=identifier,entitlements --verbose "$TARGET_PATH/ContactsManagerObjc.framework" || true

  # Verify the signature
  codesign -v "$TARGET_PATH/ContactsManagerObjc.framework" || echo "Warning: Code signing verification failed, but continuing"
else
  echo "No code signing identity found or framework not copied, skipping signing"
fi

echo "Framework script completed"
