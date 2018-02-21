project('UniStyle', 'c',
  version : '2018.02.20',
  license : 'GPL3'
)

PROJECT_NAME = 'unistyle'

lib_src = [
  'src/common.c',
  'src/unistyle.c'
]

bin_src = [
  'bin/main.c'
]

deps = [
  dependency('yaml-0.1')
]


shared_library(
    PROJECT_NAME,
    sources: [lib_src],
    link_args: '-lm',
    dependencies : deps,
    install: true
)

executable(
    PROJECT_NAME,
    sources: [lib_src, bin_src],
    link_args: '-lm',
    c_args: ['-I../src/'],
    dependencies : deps,
    install: true
)
