#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Generate a large UTF-8 GEDCOM file for testing
"""

import sys

# Config
output_file = "large_test.ged"
num_individuals = 500000  # adjust for file size
use_unicode = True  # include multibyte UTF-8 characters

# Sample data
name_base = "Jöhn MiddleName /Döe" if use_unicode else "John /Doe"
birth_place = "München, Bayern, Plus Some Extra Text to make this much long. The more text stored in tags, the better the file size to memory size ratio." if use_unicode else "Springfield, State"
death_place = birth_place

with open(output_file, "wb") as f:
    # Write UTF-8 BOM
    f.write(b"\xEF\xBB\xBF")

    for i in range(1, num_individuals + 1):
        lines = [
            f"0 @I{i}@ INDI",
            f"1 NAME {name_base}{i}",
            "1 SEX M",
            "1 BIRT",
            "2 DATE 1 JAN 1900",
            f"2 PLAC {birth_place}",
            "1 DEAT",
            "2 DATE 31 DEC 1970",
            f"2 PLAC {death_place}",
            ""  # blank line between individuals
        ]
        # Join lines with CRLF or LF depending on your preference
        f.write(("\n".join(lines)).encode("utf-8"))

print(f"Generated {output_file} with {num_individuals} individuals.")
