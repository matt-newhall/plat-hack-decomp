#!/usr/bin/env python3
import json
import pathlib
import struct
import sys

from generated import species

ANSI_BOLD_WHITE = "\033[1;37m"
ANSI_BOLD_RED = "\033[1;31m"
ANSI_RED = "\033[31m"
ANSI_CLEAR = "\033[0m"

HEADER_FMT = "<HH"
RECORD_FMT = "<HH"

input_path = pathlib.Path(sys.argv[1])
output_paths = [pathlib.Path(p) for p in sys.argv[2:5]]

try:
    with open(input_path, "r", encoding="utf-8") as input_file:
        data = json.load(input_file)
except json.decoder.JSONDecodeError as e:
    doc_lines = e.doc.splitlines()
    start_line = max(e.lineno - 2, 0)
    end_line = min(e.lineno + 1, len(doc_lines))

    error_lines = [f"{line_num:>4} | {line}" for line_num, line in zip(list(range(start_line + 1, end_line + 1)), doc_lines[start_line : end_line])][ : end_line - start_line]
    error_line_index = e.lineno - start_line - 1
    error_lines[error_line_index] = error_lines[error_line_index][ : 5] + f"{ANSI_RED}{error_lines[error_line_index][5 : ]}{ANSI_CLEAR}"
    error_out = "\n".join(error_lines)

    print(f"{ANSI_BOLD_WHITE}{input_path}:{e.lineno}:{e.colno}: {ANSI_BOLD_RED}error: {ANSI_BOLD_WHITE}{e.msg}{ANSI_CLEAR}\n{error_out}", file=sys.stderr)
    sys.exit(1)

entries = data["encounters"]

records = bytearray()
total_weight = 0

for entry in entries:
    species_id = species.Species[entry["species"]].value
    weight = int(entry["weight"])

    records.extend(struct.pack(RECORD_FMT, species_id, weight))
    total_weight += weight

blob = struct.pack(HEADER_FMT, len(entries), total_weight) + records

for output_path in output_paths:
    with open(output_path, "wb") as output_file:
        output_file.write(blob)
