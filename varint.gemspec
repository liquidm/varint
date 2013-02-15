# -*- encoding: utf-8 -*-
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'varint/version'

Gem::Specification.new do |gem|
  gem.name          = "varint"
  gem.version       = Varint::VERSION
  gem.authors       = ["Brian Palmer", "Benedikt Böhm", "Rob Marable", "Paulo Luis Franchini Casaretto"]
  gem.email         = ["brian@codekitchen.net", "bb@xnull.de"]
  gem.summary       = %q{varint C extension}
  gem.homepage      = "https://github.com/madvertise/varint"

  gem.files         = `git ls-files`.split($/)
  gem.executables   = gem.files.grep(%r{^bin/}).map{ |f| File.basename(f) }
  gem.test_files    = gem.files.grep(%r{^(test|spec|features)/})
  gem.require_paths = ["lib"]

  gem.extensions    = ["ext/varint/extconf.rb"]

  gem.add_development_dependency "rake"
end
