# Equipment Cycle Hotkeys — Skyrim 1.7.104 rebuild

Fork of [panic-sell/equipment-cycle-hotkeys](https://github.com/panic-sell/equipment-cycle-hotkeys).

## Requirements

- Skyrim Special Edition / Anniversary Edition Steam runtime **1.7.104.0**.
- [SKSE64 2.3.1](https://skse.silverlock.org/).
- Address Library for SKSE Plugins with `versionlib-1-7-104-0.bin` (format 5).

This fork pins alandtse/CommonLibVR's `ng` lineage at CommonLibSSE-NG
11.0.0 (`94faaed0c60eddd8347767f2d4d29a97c93bde8c`). It adds the newer
Address Library reader and runtime classification. Both existing render and input
hook offsets were checked against the local 1.7.104.0 executable and are unchanged.
Hook installation now checks for a direct CALL opcode before patching. This check
detects an unexpected opcode; it does not prove the target's identity.
Custom logging is preserved through SKSE initialization.
Version 1.4.2 reserves both hook stubs in one 28-byte trampoline allocation.
CommonLib 11 initializes that pool only once, so separate 14-byte requests leave
the second hook without space (the startup allocation error in version 1.4.1).
The ImGui backend bridges CommonLib's REX DirectX interfaces to the Windows SDK,
and serialization uses Boost 1.89's `boost::system::result` API.

## Build

Use an x64 Visual Studio Developer Command Prompt with C++23-capable MSVC,
CMake 3.28.1 or newer, Ninja, and a bootstrapped vcpkg checkout. Set `VCPKG_ROOT`
to that checkout. The manifest installs the pinned dependencies.

```console
cmake --preset release
cmake --build build/release --config Release
ctest --test-dir build/release --output-on-failure
```

The `zip_mod` target packages the DLL and the existing configuration under `dist/`.
Install the ZIP as an MO2 mod, replacing the original DLL. Keep your current
configuration if you have customized it.

## Validation limits

The Release DLL, development app, and tests built successfully with MSVC
19.51.36256. All 31 CTest entries passed (30 cases, 313 assertions), including
a regression test that installs two distinct call hooks into a 28-byte buffer.
The DLL exports `SKSEPlugin_Version`,
`SKSEPlugin_Query`, and `SKSEPlugin_Load`; the ZIP contains `SKSE/Plugins` at its root.

Checking the executable's hook instructions and passing the automated tests do not
prove in-game compatibility. Verify SKSE loading, opening/closing the UI, cycling
equipment and powers, and save/load persistence in Skyrim 1.7.104 before relying
on this rebuild. Older SE/AE runtime support remains enabled in the dependency,
but has not been retested by this fork.
