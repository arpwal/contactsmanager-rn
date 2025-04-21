#!/bin/bash

# Define paths
XCFRAMEWORK_PATH="ios/Frameworks/ContactsManagerObjc.xcframework"
TEMP_DIR="temp_framework"

# Create temp directory
mkdir -p "$TEMP_DIR"

# Function to process each architecture slice
process_slice() {
    local slice_path="$1"
    local slice_id="$2"

    echo "Processing slice: $slice_id"

    # Create a destination directory
    mkdir -p "$TEMP_DIR/$slice_id"

    # Copy the framework
    cp -R "$XCFRAMEWORK_PATH/$slice_path" "$TEMP_DIR/$slice_id/"

    # Make sure the binary is executable
    chmod +x "$TEMP_DIR/$slice_id/ContactsManagerObjc.framework/ContactsManagerObjc"

    # Remove any existing signature
    codesign --force --deep --sign "" "$TEMP_DIR/$slice_id/ContactsManagerObjc.framework"
}

# Process each slice
process_slice "ios-arm64/ContactsManagerObjc.framework" "ios-arm64"
process_slice "ios-arm64_x86_64-simulator/ContactsManagerObjc.framework" "ios-arm64_x86_64-simulator"

# Create new xcframework
echo "Creating new xcframework..."
rm -rf "$XCFRAMEWORK_PATH.new"

xcodebuild -create-xcframework \
    -framework "$TEMP_DIR/ios-arm64/ContactsManagerObjc.framework" \
    -framework "$TEMP_DIR/ios-arm64_x86_64-simulator/ContactsManagerObjc.framework" \
    -output "$XCFRAMEWORK_PATH.new"

# Replace old xcframework with new one
echo "Replacing old xcframework..."
rm -rf "$XCFRAMEWORK_PATH"
mv "$XCFRAMEWORK_PATH.new" "$XCFRAMEWORK_PATH"

# Clean up
rm -rf "$TEMP_DIR"

echo "XCFramework successfully fixed!"
