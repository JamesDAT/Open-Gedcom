#!/usr/bin/env python3

import os
import sys
import subprocess
import platform
from pathlib import Path


PROJECT_NAME = "OpenGedcom"
BUILD_DIR = "build"

print("Beginning OpenGedcom Build")


def run(cmd, cwd=None):
    print(f"\n>>> {' '.join(cmd)}\n")
    result = subprocess.run(cmd, cwd=cwd)
    if result.returncode != 0:
        sys.exit(result.returncode)


def prompt_run_project():
    choice = input("\nRun OpenGedcom Test Now? (y/n): ").strip().lower()

    if choice == "y":
        system = platform.system()

        if system == "Windows":
            exe_path = Path(BUILD_DIR) / "Release" / "OpenGedcomTests.exe"
        else:
            exe_path = Path(BUILD_DIR) / "test" / "OpenGedcomTests"

        if not exe_path.exists():
            print(f"Test executable not found at \"{exe_path}\"")
            return

        print(f"Launching \"{exe_path}\", end script.\n")

        subprocess.run([str(exe_path)])


def main():
    system = platform.system()
    build_path = Path(BUILD_DIR)

    if not build_path.exists():
        build_path.mkdir()

    if system == "Linux":
        print("Detected Linux — using LLVM Toolchain + Ninja")

        cmake_configure = [
            "cmake",
            "-S", ".",
            "-B", BUILD_DIR,
            "-G", "Ninja",

            "-DCMAKE_C_COMPILER=clang",
            "-DCMAKE_CXX_COMPILER=clang++",

            "-DCMAKE_BUILD_TYPE=Release",
            "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON",
            "-DOPENGEDCOM_BUILD_TESTS=ON"
        ]

        cmake_build = [
            "cmake",
            "--build", BUILD_DIR,
        ]

    elif system == "Windows":
        print("Detected Windows — using MSVC")

        cmake_configure = [
            "cmake",
            "-S", ".",
            "-B", BUILD_DIR,
            "-G", "Visual Studio 17 2022",
            "-A", "x64",
        ]

        cmake_build = [
            "cmake",
            "--build", BUILD_DIR,
            "--config", "Release",
        ]

    else:
        print(f"Unsupported platform: {system}")
        sys.exit(1)

    run(cmake_configure)
    run(cmake_build)

    print("\nBuild completed successfully.")


if __name__ == "__main__":
    main()
    try:
        prompt_run_project()
    except KeyboardInterrupt:
        sys.exit(0)