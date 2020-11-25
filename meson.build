project('frvdec', ['c'], default_options: ['warning_level=3', 'c_std=c11'])

libfrvdec = static_library('frvdec', 'frvdec.c', install: true)
frvdec = declare_dependency(link_with: libfrvdec,
                            include_directories: include_directories('.'))
install_headers('frvdec.h')

test('decode', executable('test_decode', 'test.c', dependencies: frvdec))

pkg = import('pkgconfig')
pkg.generate(libraries: libfrvdec,
             version: '0.1',
             name: 'frvdec',
             filebase: 'frvdec',
             description: 'RISC-V Decoder')
