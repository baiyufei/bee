{
    'target_defaults': {
        'cflags':['-Wall -Wextra -std=c++11'],
        "link_settings": {"libraries": [ '-pthread'] }
    },
    "targets": [
        { "target_name": "s0", "type": "executable", "sources": ["s0.c"]},
        { "target_name": "s1", "type": "executable", "sources": ["s1.cc"] },
        { "target_name": "s2", "type": "executable", "sources": ["s2.cc"] },
        { "target_name": "s3", "type": "executable", "sources": ["s3.cc"] },
        { "target_name": "s4", "type": "executable", "sources": ["s4.cc"] },
        { "target_name": "s5", "type": "executable", "sources": ["s5.cc"],
            "link_settings": {"libraries": [ '-lgtest'] }},
        { "target_name": "s6", "type": "executable", "sources": ["s6.cc"] },
        { "target_name": "s7", "type": "executable", "sources": ["s7.cc"] },
        { "target_name": "s9", "type": "executable", "sources": ["s9.cc"],
            "link_settings": {"libraries": [ '-luv'] }},
         { "target_name": "s10", "type": "executable", "sources": ["s10.cc"],
            "link_settings": {"libraries": [ '-luv'] }}
    ]
}