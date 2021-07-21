load("@rules_foreign_cc//foreign_cc:configure.bzl", "configure_make")

# Read https://wiki.openssl.org/index.php/Compilation_and_Installation

config_setting(
    name = "platform_osx",
    constraint_values = [
        "@bazel_tools//platforms:osx",
    ],
)

config_setting(
    name = "platform_linux",
    constraint_values = [
        "@bazel_tools//platforms:linux",
    ],
)

filegroup(
    name = "all",
    srcs = glob(["**"]),
    visibility = ["//visibility:public"],
)

alias(
    name = "openssl",
    actual = select({
        # Comment this and retry when https://github.com/openssl/openssl/issues/11620 is fixed.
        ":platform_osx": ":openssl_shared",
        "//conditions:default": ":openssl_static",
    }),
    visibility = ["//visibility:public"],
)

CONFIGURE_OPTIONS = [
    "no-weak-ssl-ciphers",
    "no-idea",
    "no-comp",
]

configure_make(
    name = "openssl_static",
    configure_command = "config",
    configure_env_vars = select({
        ":platform_osx": {"AR": ""},
        "//conditions:default": {},
    }),
    configure_in_place = True,
    configure_options = select({
        ":platform_osx": [
            "no-asm",
            "no-afalgeng",
            "no-shared",
            "ARFLAGS=r",
        ] + CONFIGURE_OPTIONS,
        "//conditions:default": [
            "no-shared",
        ] + CONFIGURE_OPTIONS,
    }),
    lib_source = "@openssl//:all",
    out_lib_dir = "lib",
    static_libraries = [
        "libssl.a",
        "libcrypto.a",
    ],
    visibility = ["//visibility:public"],
)

configure_make(
    name = "openssl_shared",
    configure_command = "config",
    configure_env_vars = select({
        ":platform_osx": {
            "AR": "",
        },
        "//conditions:default": {},
    }),
    configure_options = select({
        ":platform_osx": [
            "shared",
            "no-afalgeng",
            "ARFLAGS=r",
        ] + CONFIGURE_OPTIONS,
        "//conditions:default": [
        ] + CONFIGURE_OPTIONS,
    }),
    lib_source = "@openssl//:all",
    out_shared_libs = select({
        ":platform_osx": [
            "libssl.dylib",
            "libcrypto.dylib",
        ],
        "//conditions:default": [
            "libssl.so",
            "libcrypto.so",
        ],
    }),
    visibility = ["//visibility:public"],
)

