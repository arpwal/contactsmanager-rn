#!/bin/bash

# Set team identifier
TEAM_ID="2C87X9VM3V"

# Define paths
XCFRAMEWORK_PATH="ios/Frameworks/ContactsManagerObjc.xcframework"
TEMP_DIR="temp_framework"

# Find the developer identity for the team
IDENTITY=$(security find-identity -v -p codesigning | grep "$TEAM_ID" | head -1 | awk '{print $2}')

if [ -z "$IDENTITY" ]; then
  echo "No identity found for team ID: $TEAM_ID"
  echo "Available identities:"
  security find-identity -v -p codesigning
  exit 1
fi

echo "Using identity: $IDENTITY for team: $TEAM_ID"

# Create temp directories
mkdir -p "$TEMP_DIR/ios-arm64"
mkdir -p "$TEMP_DIR/ios-arm64_x86_64-simulator"

# Copy frameworks
echo "Copying frameworks..."
cp -R "$XCFRAMEWORK_PATH/ios-arm64/ContactsManagerObjc.framework" "$TEMP_DIR/ios-arm64/"
cp -R "$XCFRAMEWORK_PATH/ios-arm64_x86_64-simulator/ContactsManagerObjc.framework" "$TEMP_DIR/ios-arm64_x86_64-simulator/"

# Make binaries executable
chmod +x "$TEMP_DIR/ios-arm64/ContactsManagerObjc.framework/ContactsManagerObjc"
chmod +x "$TEMP_DIR/ios-arm64_x86_64-simulator/ContactsManagerObjc.framework/ContactsManagerObjc"

# Add team identifier to entitlements
ENTITLEMENTS_FILE="$TEMP_DIR/entitlements.plist"
/usr/libexec/PlistBuddy -c "Add :com.apple.developer.team-identifier string $TEAM_ID" "$ENTITLEMENTS_FILE" 2>/dev/null || true
/usr/libexec/PlistBuddy -c "Add :application-identifier string $TEAM_ID.com.arpwal.ContactsManagerObjc" "$ENTITLEMENTS_FILE" 2>/dev/null || true

# Sign frameworks with explicit team ID
echo "Signing device framework..."
codesign --force --options runtime --sign "$IDENTITY" --timestamp=none --entitlements "$ENTITLEMENTS_FILE" --verbose "$TEMP_DIR/ios-arm64/ContactsManagerObjc.framework"

echo "Signing simulator framework..."
codesign --force --options runtime --sign "$IDENTITY" --timestamp=none --entitlements "$ENTITLEMENTS_FILE" --verbose "$TEMP_DIR/ios-arm64_x86_64-simulator/ContactsManagerObjc.framework"

# Recreate XCFramework
echo "Creating new XCFramework..."
xcodebuild -create-xcframework \
  -framework "$TEMP_DIR/ios-arm64/ContactsManagerObjc.framework" \
  -framework "$TEMP_DIR/ios-arm64_x86_64-simulator/ContactsManagerObjc.framework" \
  -output "$TEMP_DIR/ContactsManagerObjc.xcframework"

# Sign the XCFramework itself
echo "Signing XCFramework..."
codesign --force --options runtime --sign "$IDENTITY" --timestamp=none --entitlements "$ENTITLEMENTS_FILE" --verbose "$TEMP_DIR/ContactsManagerObjc.xcframework"

# Replace old framework
echo "Replacing old framework..."
rm -rf "$XCFRAMEWORK_PATH"
mv "$TEMP_DIR/ContactsManagerObjc.xcframework" "$XCFRAMEWORK_PATH"

# Verify new framework
echo "Verifying signature..."
codesign -vv "$XCFRAMEWORK_PATH"

# Clean up
rm -rf "$TEMP_DIR"

echo "Framework signing complete!"
