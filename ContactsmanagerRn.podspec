require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))
min_ios_version_supported = "13.0"

Pod::Spec.new do |s|
  s.name         = "ContactsmanagerRn"
  s.version      = package["version"]
  s.summary      = package["description"]
  s.homepage     = package["homepage"]
  s.license      = package["license"]
  s.authors      = package["author"]

  s.platforms    = { :ios => min_ios_version_supported }
  s.source       = { :git => "https://github.com/arpwal/contactsmanager-rn.git", :tag => "#{s.version}" }

  s.source_files = "ios/**/*.{h,m,mm}"

  # Ensure the framework is properly embedded
  s.static_framework = true
  s.vendored_frameworks = ['ios/Frameworks/ContactsManagerObjc.xcframework']

  # Prepare the framework for use
  s.prepare_command = <<-CMD
    cd #{File.dirname(__FILE__)}

    # Make sure the Frameworks directory exists
    mkdir -p ios/Frameworks

    # Check if framework needs fixing
    if [ -e "./fix_xcframework.sh" ]; then
      echo "Fixing framework for ContactsManagerObjc..."
      chmod +x ./fix_xcframework.sh
      ./fix_xcframework.sh
    fi

    # Make sure binaries are executable
    if [ -d "ios/Frameworks/ContactsManagerObjc.xcframework/ios-arm64/ContactsManagerObjc.framework" ]; then
      chmod +x ios/Frameworks/ContactsManagerObjc.xcframework/ios-arm64/ContactsManagerObjc.framework/ContactsManagerObjc
    fi

    if [ -d "ios/Frameworks/ContactsManagerObjc.xcframework/ios-arm64_x86_64-simulator/ContactsManagerObjc.framework" ]; then
      chmod +x ios/Frameworks/ContactsManagerObjc.xcframework/ios-arm64_x86_64-simulator/ContactsManagerObjc.framework/ContactsManagerObjc
    fi
  CMD

  s.pod_target_xcconfig = {
    'FRAMEWORK_SEARCH_PATHS' => '$(inherited) $(PODS_ROOT)/../../ios/Frameworks $(PODS_ROOT)/../.. $(PODS_ROOT)/../../node_modules/contactsmanager-rn/ios/Frameworks',
    'OTHER_LDFLAGS' => '$(inherited) -framework ContactsManagerObjc',
    'ENABLE_BITCODE' => 'NO',
    'CLANG_ALLOW_NON_MODULAR_INCLUDES_IN_FRAMEWORK_MODULES' => 'YES'
  }

  s.user_target_xcconfig = {
    'FRAMEWORK_SEARCH_PATHS' => '$(inherited) $(PODS_ROOT)/../../ios/Frameworks $(PODS_ROOT)/../../node_modules/contactsmanager-rn/ios/Frameworks'
  }

  # If your framework depends on system frameworks, add them:
  s.frameworks = 'Contacts', 'ContactsUI'

  # Use install_modules_dependencies helper to install the dependencies if React Native version >=0.71.0.
  # See https://github.com/facebook/react-native/blob/febf6b7f33fdb4904669f99d795eba4c0f95d7bf/scripts/cocoapods/new_architecture.rb#L79.
  if respond_to?(:install_modules_dependencies, true)
    install_modules_dependencies(s)
  else
    s.dependency "React-Core"
  end
end
