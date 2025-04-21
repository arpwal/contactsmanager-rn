#!/bin/bash

echo "Configuring ContactsManagerObjc Framework..."

# Find the path to the framework
FRAMEWORK_NAME="ContactsManagerObjc.xcframework"
POSSIBLE_PATHS=(
  "${PODS_ROOT}/../../node_modules/contactsmanager-rn/ios/Frameworks/${FRAMEWORK_NAME}"
  "${PODS_ROOT}/../../../ios-objc/${FRAMEWORK_NAME}"
  "${PODS_ROOT}/../../ios/Frameworks/${FRAMEWORK_NAME}"
)

FRAMEWORK_PATH=""
for path in "${POSSIBLE_PATHS[@]}"; do
  if [ -d "$path" ]; then
    FRAMEWORK_PATH="$path"
    echo "Found framework at: $FRAMEWORK_PATH"
    break
  fi
done

if [ -z "$FRAMEWORK_PATH" ]; then
  echo "Warning: Could not find $FRAMEWORK_NAME in expected locations"
  exit 0
fi

# Make sure binaries are executable
if [ -d "$FRAMEWORK_PATH/ios-arm64/ContactsManagerObjc.framework" ]; then
  echo "Making device binary executable..."
  chmod +x "$FRAMEWORK_PATH/ios-arm64/ContactsManagerObjc.framework/ContactsManagerObjc"
fi

if [ -d "$FRAMEWORK_PATH/ios-arm64_x86_64-simulator/ContactsManagerObjc.framework" ]; then
  echo "Making simulator binary executable..."
  chmod +x "$FRAMEWORK_PATH/ios-arm64_x86_64-simulator/ContactsManagerObjc.framework/ContactsManagerObjc"
fi

echo "Framework configuration complete."
exit 0
