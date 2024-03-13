project('frvdec', ['c'], default_options: ['warning_level=3', 'c_std=c11'])

libfrvdec = static_library('frvdec', 'frvdec.c', install: true)
frvdec = declare_dependency(link_with: libfrvdec,
                            include_directories: include_directories('.'))
install_headers('frvdec.h')

test('decode', executable('test_decode', 'test.c', dependencies: frvdec))

pkg = import('pkgconfig')
pkg.generate(libfrvdec,
             version: '0.1',
             description: 'RISC-V Decoder')

mytarget = custom_target('cpop.exe RISCV',
  output : 'cpop.exe',
  input : 'cpop.S' ,
  build_by_default: true,
  command : ['riscv64-linux-gnu-gcc', '-march=rv64imd_zbb', '-nostdlib', '-static', '@INPUT@', '-o', '@OUTPUT@']
)

mytarget = custom_target('strings.exe RISCV',
  output : 'strings.exe',
  input : 'strings.S' ,
  build_by_default: true,
  command : ['riscv64-linux-gnu-gcc',  '-march=rv64imd_zve64x', '-nostdlib', '-static', '@INPUT@', '-o', '@OUTPUT@']
)
