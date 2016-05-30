###############################################################################
#
# Rakefile for building RedWeasel. 
#
# Usage 'rake [rev=<rev>] [nosign=nosign]' to build the app.
#
# The optional 'rev' parameter sets the third digit of the version string.
# The optional 'nosign' parameter, when present, will disable code signing 
#
# You have options to build individual components. Use 'rake -T' for a list of 
# all available build tasks.
#
###############################################################################

require 'rake'
# handy-dandy rake profiling! http://dogbiscuit.org/mdub/weblog/Tech/Programming/Ruby/RakeProfiling
module Rake
  class Task
    def execute_with_timestamps(*args)
      start = Time.now
      execute_without_timestamps(*args)
      execution_time_in_seconds = Time.now - start
      printf("** %s took %.1f seconds\n", name, execution_time_in_seconds)
    end
    alias :execute_without_timestamps :execute
    alias :execute :execute_with_timestamps 
  end
end

rev = ENV["rev"] || 0
nosign = ENV["nosign"] || ""

class FailedBuildException < Exception;end

###############################################################################
# Top level tasks
###############################################################################

task :default => [:build_app]

desc "build the application."
task :build_app  => [:jucer] do
  puts "\nBuilding the release binary for the app v1.0.#{rev}"
  testXcodeVersion
  build_result = %x{xcodebuild -project ../common/RedWeasel/Builds/MacOSX/RedWeasel.xcodeproj -configuration Release}
  if !build_result.match(/build succeeded/i)
    puts "build failed with:"
    puts build_result.lines.grep(/error/i)
    throw FailedBuildException.new
  end
  if nosign.length == 0
    sh "codesign -s \"Heynow Software\" ../common/RedWeasel/Builds/MacOSX/build/Release/RedWeasel.app"
  end
  puts "RedWeasel.app is available at ../common/RedWeasel/Builds/MacOSX/build/Release/RedWeasel.app"
end

desc "build Projucer"
task :build_projucer do
  puts "\nBuilding Projucer"
  testXcodeVersion
  build_result = %x{xcodebuild -project ../common/juce/extras/Projucer/Builds/MacOSX/Projucer.xcodeproj -configuration Release}
  if !build_result.match(/build succeeded/i)
    puts "build failed with:"
    puts build_result.lines.grep(/error/i)
    throw FailedBuildException.new
  end
end

desc "make the IDE projects for the application"
task :jucer => [:build_projucer] do
  puts "\nMaking the projects for the application."
  Dir.chdir "../common/RedWeasel/" do
    rm_rf "Builds"
    sh "/usr/local/bin/xml ed -u \"JUCERPROJECT/@version\" -v \"1.0.#{rev}\" RedWeasel.jucer > tmp.jucer"
    sh "../juce/extras/Projucer/Builds/MacOSX/build/Release/Projucer.app/Contents/MacOS/Projucer --resave tmp.jucer"
    sh "/usr/libexec/PlistBuddy -c \"Add LSArchitecturePriority array\" Builds/MacOSX/Info.plist"
    sh "/usr/libexec/PlistBuddy -c \"Add LSArchitecturePriority:0 string \'i386\'\" Builds/MacOSX/Info.plist"
    sh "/usr/libexec/PlistBuddy -c \"Add LSArchitecturePriority:1 string \'x86_64\'\" Builds/MacOSX/Info.plist"
    rm "tmp.jucer"
  end
end

###############################################################################
# utility functions
###############################################################################
class FailedXcodeTestException < Exception;end
def testXcodeVersion
  version = `xcodebuild -version`
  if !version.match(/Xcode #{$requiredXCodeVersion}/)
    puts "Expected Xcode version to be #{$requiredXCodeVersion}"
    throw FailedXcodeTestException.new
  end 
end