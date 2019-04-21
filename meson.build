project(
  'xlpp',
  'cpp',
  version : '0.1',
  default_options : [ 'cpp_std=c++17' ]
)

add_project_link_arguments('-lstdc++fs', language : 'cpp')

threads    = dependency('threads')
xcb        = dependency('xcb')
cairo      = dependency('cairo')
pangocairo = dependency('pangocairo')


deps  = [ threads, xcb, cairo, pangocairo ]

subdir('include')
subdir('src')

clangtidy = find_program('clang-tidy', required : false)
if clangtidy.found()
  run_target('tidy', command : [ clangtidy,
                                 '-p=' + meson.build_root() ]
                               + src)
endif
