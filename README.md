## bazel-sample

Provide a sample project for those people: 
- use macOS (maybe linux)
- need C++ project (support clang and gcc)
- need bazel construction
- need gRPC and protobuf
- need openssl (version 1.1.1+, or the better option is boringssl)
- use CLion (not have to)

---

## How to prepare env

### bazel

In macOS, homebrew can only install the latest version, please use 3.7.1 for this repo.

```bash
export BAZEL_VERSION=3.7.1
mkdir -p ~/tmp
cd ~/tmp
curl -fLO "https://github.com/bazelbuild/bazel/releases/download/${BAZEL_VERSION}/bazel-${BAZEL_VERSION}-installer-darwin-x86_64.sh"
chmod +x "bazel-${BAZEL_VERSION}-installer-darwin-x86_64.sh"
./bazel-${BAZEL_VERSION}-installer-darwin-x86_64.sh --user
echo 'export PATH="$PATH:$HOME/bin"' >> ~/.zshrc
source ~/.zshrc
```

### CLion

About CLion version, please check this repo: https://github.com/bazelbuild/intellij

From 2021.6.4, you can use CLion 2021.1+ with bazel plugin in beta version, follow https://github.com/bazelbuild/intellij/issues/2406#issuecomment-854745034

So just install the latest version of CLion now.

Go `CLion->Preferences...->Bazel settings->bazel binary location` and set it `~/bin/bazel`

## How to build it

### Import this repo

```bash
git clone https://github.com/WUST-mengqinyu/bazel-sample.git
```

Open your CLion, Click `File->Import bazel project` then choose this repo.

After that just click "next" until "finish".

### Sync bazel

If you open this repo for the first time, CLion will sync this bazel project by auto.

Otherwise, just click the green heart in the top-right corner. ![docs/imgs/green_heart.png]

### Build All

Open terminal in CLion and run

```bash
bazel build //...
```

If you want to build and run a spec binary, just go to a `BUILD` file or `BUILD.bazel` file, click a green triangle, then this binary will show in your top-right corner.