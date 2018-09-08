###############################################################################
#
# Rakefile for building RedWeasel on Windows. 
#
# Usage 'rake [rev=<rev>] [sign=<signtool params>]' to build the app.
#
# The optional 'rev' parameter sets the third digit of the version string.
# The optional 'sign' parameter, when present, will will code sign the app with <identity>. Example: sign="/f \"C:\Users\jay\My Documents\certs\heynow-codesign-pw.pfx\" /p=foo123bletch"
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
sign = ENV["sign"] || ""

projucer = "C:\\JUCE\\Projucer.exe"
if !File.exists?(projucer)
  projucer = "c:\\JUCE\\extras\\Projucer\\Builds\\VisualStudio2017\\x64\\Release\\App\\Projucer.exe"
end

class FailedBuildException < Exception;end

###############################################################################
# Top level tasks
###############################################################################

task :default => [:build_app]

desc "build the 32-bit standalone application"
task :build_app => [:jucer] do
  sh "msbuild ..\\common\\RedWeasel\\Builds\\VisualStudio2017\\RedWeasel.sln /p:configuration=Release /p:platform=Win32 /v:quiet"

  if sign.length > 0
    puts "Signing the app"
    sh "SignTool sign #{sign} ..\\common\\RedWeasel\\Builds\\VisualStudio2017\\Release\\RedWeasel.exe"
  end
end
desc "build Projucer"
task :build_projucer do
  puts "Building Projucer"
  sh "msbuild \"C:\\JUCE\\extras\\Projucer\\Builds\\VisualStudio2017\\Projucer.sln\" /p:configuration=Release /v:quiet"
end

desc "make the IDE project for the application"
task :jucer do
  puts "Generating the app's VS2017 projects"
  Dir.chdir "..\\common\\RedWeasel" do
    rm_rf "Builds"
    sh "xml ed -u \"JUCERPROJECT/@version\" -v 1.0.#{rev} RedWeasel.jucer > tmp.jucer"
    sh "#{projucer} --resave tmp.jucer"
    rm "tmp.jucer"
  end
end

