#workspace(name = "com_github_grpc_grpc")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
# load rules_foreign_cc
git_repository(
    name = "rules_foreign_cc",
    remote = "https://github.com/bazelbuild/rules_foreign_cc",
    commit = "d02390f1363cdd2ba5a7f7907a481503d483d569",
    shallow_since = "1616082096 +0000",
#    branch = "0.2.0"
)
load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")
rules_foreign_cc_dependencies()

# load gtest
git_repository(
    name = "gtest",
    remote = "https://github.com/google/googletest",
    commit = "ba96d0b1161f540656efdaed035b3c062b60e006",
#    branch = "release-1.10.x",
)

# load sqlite3
http_archive(
    name = "sqlite3",
    strip_prefix = "sqlite-bazel-6473349723a61ecf929a422795790bf657d86ed9",
    urls = ["https://github.com/rockwotj/sqlite-bazel/archive/6473349723a61ecf929a422795790bf657d86ed9.zip"],
    sha256 = "a04556cb10fe365329c673303b13c0e7a7ad4488767c8537d4e5e8ee0403031c",
)

## load openssl
all_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""
http_archive(
    name = "openssl",
    build_file_content = all_content,
    strip_prefix = "openssl-OpenSSL_1_1_1i",
    urls = ["https://github.com/openssl/openssl/archive/OpenSSL_1_1_1i.tar.gz"],
)

# load protobuf
git_repository(
    name = "com_google_protobuf",
    remote = "https://github.com/protocolbuffers/protobuf",
    commit = "19fb89416f3fdc2d6668f3738f444885575285bc",
    shallow_since = "1610561587 -0800",
#    branch = "4.0.x",
#    branch = "v3.17.3",
)
load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
protobuf_deps()

# load grpc
git_repository(
    name = "com_github_grpc_grpc",
    remote = "https://github.com/grpc/grpc",
    commit = "257d0045ab958eb767a3591c88e9d0c2bdf4b916",
    shallow_since = "1611079677 -0800",
#    branch = "v1.35.0",
)
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()
load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()

# load fmtlib
http_archive(
    name = "fmtlib",
    url = "https://github.com/fmtlib/fmt/releases/download/8.0.0/fmt-8.0.0.zip",
    strip_prefix = "fmt-8.0.0",
    build_file = "//third_party/fmtlib:BUILD.bazel",
    sha256 = "36016a75dd6e0a9c1c7df5edb98c93a3e77dabcf122de364116efb9f23c6954a",
)
