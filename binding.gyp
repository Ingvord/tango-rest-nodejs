{
    "variables": {
        "tango_home_linux%": "/usr/local",
        "link_type%": "shared",
        "debug_mode%": "",
        "longlong_type%": "LONGLONG64BITS"
    },
    "targets": [{
        "target_name": "TangoRestServer",
        "include_dirs" : [
          "src",
          "<!(node -e \"require('nan')\")"
        ],
        "sources": [
          "src/index.cpp"
        ],
        "conditions":[
        ['OS=="linux"', {
            'cflags!': [ '-fno-exceptions' ],
            'cflags_cc!': [ '-fno-exceptions' ],
            'cflags': ['-fPIC', "-<(link_type)", "-O4", "-std=c++14", "-fexceptions", "-Werror"],
            'include_dirs': [
                '<(tango_home_linux)/include',
                '<(tango_home_linux)/include/tango'
            ],
            'link_settings': {
                'libraries': [
                    '-ltango', '-lzmq', '-lomniORB4', '-lomnithread', '-lCOS4', '-lomniDynamic4'
                ],
                'ldflags': [
                    '-L<(tango_home_linux)/lib'
                ]
            }
        }]
        ]
  }]
}