#!/bin/bash

echo "Fixing framework linking..."

# Make sure Ruby script is executable
chmod +x fix_framework_linking.rb

# Run the Ruby script
ruby fix_framework_linking.rb

# Print completion message
echo "Framework linking fixed. Please build the project in Xcode now."
