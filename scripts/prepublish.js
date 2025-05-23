#!/usr/bin/env node

const fs = require('fs');
const path = require('path');
const { execSync } = require('child_process');

// Paths
const rootDir = path.resolve(__dirname, '..');
const iosFrameworkDir = path.join(rootDir, 'ios', 'Frameworks');
const xcframeworkPath = path.join(
  iosFrameworkDir,
  'ContactsManagerObjc.xcframework'
);

console.log('Preparing ContactsManagerObjc.xcframework for distribution...');

try {
  // Make sure Frameworks directory exists
  if (!fs.existsSync(iosFrameworkDir)) {
    console.log('Creating Frameworks directory...');
    fs.mkdirSync(iosFrameworkDir, { recursive: true });
  }

  // Check if xcframework exists
  if (fs.existsSync(xcframeworkPath)) {
    console.log('XCFramework found, preparing for distribution...');

    // Remember the original framework existence
    const frameworkExistedBefore = fs.existsSync(xcframeworkPath);

    // Fix the framework to ensure it doesn't have signing issues
    const fixScriptPath = path.join(rootDir, 'fix_xcframework.sh');
    if (fs.existsSync(fixScriptPath)) {
      console.log('Running fix_xcframework.sh...');
      try {
        execSync(`chmod +x ${fixScriptPath} && ${fixScriptPath}`, {
          stdio: 'inherit',
        });

        // Verify the framework still exists after running the fix script
        if (frameworkExistedBefore && !fs.existsSync(xcframeworkPath)) {
          throw new Error(
            'The framework was deleted during the fix process but not replaced properly.'
          );
        }

        console.log('Fixed xcframework successfully');
      } catch (error) {
        console.warn('Warning: Could not fix xcframework:', error.message);
        console.log(
          'This may not be an issue if the framework is already properly set up'
        );
      }
    }
  } else {
    console.warn(
      'Warning: ContactsManagerObjc.xcframework not found in ios/Frameworks.'
    );
    console.warn('Make sure to include it before publishing the package.');
  }

  // Final check to ensure xcframework exists before proceeding
  if (!fs.existsSync(xcframeworkPath)) {
    throw new Error(
      'ContactsManagerObjc.xcframework not found after preparation. Publishing aborted.'
    );
  }

  console.log('Prepublish script completed successfully.');
} catch (error) {
  console.error('Error in prepublish script:', error);
  process.exit(1);
}
