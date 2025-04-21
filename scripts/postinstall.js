#!/usr/bin/env node

const fs = require('fs');
const path = require('path');
const { execSync } = require('child_process');

// Only run in non-development environments
const isDevEnvironment =
  process.env.NODE_ENV === 'development' ||
  process.cwd().includes('node_modules') === false;

// Skip if we're in a development environment
if (isDevEnvironment) {
  console.log('Development environment detected, skipping postinstall setup');
  process.exit(0);
}

console.log('Setting up ContactsManagerObjc.xcframework...');

// Paths
const modulePath = process.cwd();
const rootDir = path.resolve(modulePath);
const iosFrameworkDir = path.join(rootDir, 'ios', 'Frameworks');
const xcframeworkPath = path.join(
  iosFrameworkDir,
  'ContactsManagerObjc.xcframework'
);

try {
  // Make sure the framework exists
  if (!fs.existsSync(xcframeworkPath)) {
    console.warn(
      'Warning: ContactsManagerObjc.xcframework not found at',
      xcframeworkPath
    );
    console.warn('The module may not work correctly without it.');
    process.exit(0);
  }

  // Check for framework validity
  console.log('Validating xcframework...');

  // Check for iOS framework slices
  const deviceSlicePath = path.join(xcframeworkPath, 'ios-arm64');
  const simulatorSlicePath = path.join(
    xcframeworkPath,
    'ios-arm64_x86_64-simulator'
  );

  if (!fs.existsSync(deviceSlicePath) || !fs.existsSync(simulatorSlicePath)) {
    console.warn(
      'Warning: XCFramework is missing expected architecture slices.'
    );
    console.warn('This might cause issues during iOS builds.');
  } else {
    console.log('XCFramework structure looks good.');
  }

  // If we need to run any commands to fix permissions
  try {
    // Make binaries executable
    if (
      fs.existsSync(path.join(deviceSlicePath, 'ContactsManagerObjc.framework'))
    ) {
      const deviceBinary = path.join(
        deviceSlicePath,
        'ContactsManagerObjc.framework',
        'ContactsManagerObjc'
      );
      execSync(`chmod +x "${deviceBinary}"`, { stdio: 'ignore' });
    }

    if (
      fs.existsSync(
        path.join(simulatorSlicePath, 'ContactsManagerObjc.framework')
      )
    ) {
      const simulatorBinary = path.join(
        simulatorSlicePath,
        'ContactsManagerObjc.framework',
        'ContactsManagerObjc'
      );
      execSync(`chmod +x "${simulatorBinary}"`, { stdio: 'ignore' });
    }
  } catch (error) {
    console.warn('Warning: Could not fix binary permissions:', error.message);
  }

  console.log('ContactsManagerObjc.xcframework is ready to use');
  console.log(
    'Use ContactsManager React Native module with: yarn add contactsmanager-rn'
  );
} catch (error) {
  console.error('Error in postinstall script:', error);
  // Don't exit with error to avoid breaking the install process
  process.exit(0);
}
