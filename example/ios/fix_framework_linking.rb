#!/usr/bin/env ruby
require 'xcodeproj'
require 'fileutils'

# Path to the Xcode project
project_path = 'ContactsmanagerRnExample.xcodeproj'
project = Xcodeproj::Project.open(project_path)

# Find the main target
main_target = project.targets.find { |t| t.name == 'ContactsmanagerRnExample' }

if main_target.nil?
  puts "Error: Main target 'ContactsmanagerRnExample' not found"
  exit 1
end

puts "Found main target: #{main_target.name}"

# Check possible framework paths
possible_paths = [
  '../../ios/Frameworks/ContactsManagerObjc.xcframework',
  '../../../ios-objc/ContactsManagerObjc.xcframework'
]

framework_path = nil
framework_exists = false

possible_paths.each do |path|
  if File.exist?(path)
    framework_path = path
    framework_exists = true
    puts "Framework found at: #{path}"
    break
  end
end

unless framework_exists
  puts "Warning: Could not find ContactsManagerObjc.xcframework in any of the expected locations."
  puts "The build may fail if the framework is not available."
end

# Check if ContactsManagerObjc.framework is already in the frameworks
frameworks_build_phase = main_target.frameworks_build_phase
framework_already_added = frameworks_build_phase.files.any? do |build_file|
  build_file.display_name == 'ContactsManagerObjc.framework'
end

if framework_already_added
  puts "ContactsManagerObjc.framework is already added to the main target"
else
  if framework_exists
    # Find an appropriate reference path (device or simulator)
    device_path = "#{framework_path}/ios-arm64/ContactsManagerObjc.framework"
    simulator_path = "#{framework_path}/ios-arm64_x86_64-simulator/ContactsManagerObjc.framework"

    if File.exist?(device_path)
      reference_path = device_path
    elsif File.exist?(simulator_path)
      reference_path = simulator_path
    else
      puts "Warning: Could not find either device or simulator slice in xcframework"
      puts "Available contents:"
      Dir.glob("#{framework_path}/*").each do |item|
        puts "  - #{item}"
      end
      reference_path = framework_path
    end

    # Check if the file reference already exists
    framework_ref = project.files.find { |f| f.path == reference_path }

    if framework_ref.nil?
      # Add the framework reference
      framework_group = project.groups.find { |g| g.name == 'Frameworks' }

      if framework_group.nil?
        framework_group = project.new_group('Frameworks')
        puts "Created Frameworks group"
      end

      framework_ref = framework_group.new_reference(reference_path)
      puts "Added framework reference: #{framework_ref.path}"
    else
      puts "Framework reference already exists: #{framework_ref.path}"
    end

    # Add the framework to the target
    build_file = frameworks_build_phase.add_file_reference(framework_ref)
    puts "Added framework to target: #{build_file.display_name}"

    # Set "Embed & Sign" for the framework
    attributes = ['CodeSignOnCopy', 'RemoveHeadersOnCopy']
    build_file.settings = { 'ATTRIBUTES' => attributes }
    puts "Set 'Embed & Sign' for framework"
  else
    puts "Skipping framework addition as it could not be found"
  end
end

# Make sure the copy frameworks script exists
copy_script_path = "ContactsmanagerRnExample/copy_frameworks.sh"
unless File.exist?(copy_script_path)
  puts "Warning: copy_frameworks.sh doesn't exist at expected path: #{copy_script_path}"
end

# Make sure the copy frameworks script is added
script_phase_name = 'Copy ContactsManagerObjc Framework'
script_phase = main_target.shell_script_build_phases.find { |phase| phase.name == script_phase_name }

if script_phase.nil?
  script_phase = main_target.new_shell_script_build_phase(script_phase_name)
  script_phase.shell_path = '/bin/bash'
  script_phase.shell_script = '"${PROJECT_DIR}/ContactsmanagerRnExample/copy_frameworks.sh"'
  puts "Added copy frameworks script phase"
else
  puts "Copy frameworks script phase already exists"
end

# Make sure framework search paths include the frameworks directory
main_target.build_configurations.each do |config|
  framework_search_paths = config.build_settings['FRAMEWORK_SEARCH_PATHS'] || ['$(inherited)']

  # Add standard framework search paths
  ['$(SRCROOT)/../../ios/Frameworks', '$(SRCROOT)/../../../ios-objc'].each do |path|
    unless framework_search_paths.include?(path)
      framework_search_paths << path
      puts "Added framework search path #{path} to #{config.name} build configuration"
    end
  end

  config.build_settings['FRAMEWORK_SEARCH_PATHS'] = framework_search_paths

  # Set OTHER_LDFLAGS to include the framework
  other_ldflags = config.build_settings['OTHER_LDFLAGS'] || ['$(inherited)']

  unless other_ldflags.include?('-framework ContactsManagerObjc')
    other_ldflags << '-framework' << 'ContactsManagerObjc'
    config.build_settings['OTHER_LDFLAGS'] = other_ldflags
    puts "Added framework to OTHER_LDFLAGS in #{config.name} build configuration"
  end
end

# Save the project
project.save
puts "Project saved successfully"
