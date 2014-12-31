#!/usr/bin/ruby -W2
require 'fileutils'
require_relative '../lib/cli'
require_relative '../lib/binary_io'
require_relative '../lib/output_files'
require_relative '../lib/archive_factory'

# CLI frontend
class ArchiveUnpacker < CLI
  def run_internal
    verbose = @options[:verbosity] == :debug

    unless @options[:archive].nil?
      unpack(@options[:archive], @options)
      return
    end

    ArchiveFactory.each do |key, archive|
      @options[:format] = key
      @options[:archive] = archive
      print format('Trying %s... ', key) if verbose
      begin
        unpack(archive, @options)
        puts 'ok' if verbose
        return
      rescue => e
        puts e.message if verbose
        next
      end
    end
  end

  def unpack(archive, options)
    fail 'Unpacking not supported' unless defined? archive::Unpacker
    if defined? archive.parse_cli_options
      archive.parse_cli_options(@arg_parser, options)
    end

    FileUtils.mkpath(options[:output_path])
    output_files = OutputFiles.new(options[:output_path], options)
    unpacker = archive::Unpacker.new
    BinaryIO.from_file(options[:input_path], 'rb') do |arc_file|
      unpacker.unpack(arc_file, output_files, options)
    end
  end
end

ArchiveUnpacker.new.run
