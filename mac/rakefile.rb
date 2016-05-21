###############################################################################
#
# Rakefile for building RedWeasel. 
#
# Usage 'rake [rev=<rev>] [nosign=nosign]' to build all.
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