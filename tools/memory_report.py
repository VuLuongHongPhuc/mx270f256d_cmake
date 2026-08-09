#!/usr/bin/env python3

import sys
import xml.etree.ElementTree as ET


def format_bytes(value):
    if value < 1024:
        return f"{value} B"
    elif value < 1024 * 1024:
        return f"{value / 1024:.1f} KB"
    else:
        return f"{value / (1024 * 1024):.1f} MB"


def print_memory(name, used, size):
    percent = (used * 100.0 / size) if size else 0

    print(f"{name}:")
    print(f"  Used : {format_bytes(used)}")
    print(f"  Total: {format_bytes(size)}")
    print(f"  Usage: {percent:.2f} %")
    print()


def main():

    if len(sys.argv) != 2:
        print("Usage:")
        print("  memory_report.py <memorysummary.xml>")
        sys.exit(1)

    filename = sys.argv[1]

    try:
        tree = ET.parse(filename)
        root = tree.getroot()
    except Exception as e:
        print(f"Error reading {filename}: {e}")
        sys.exit(1)


    program_used = 0
    program_size = 0

    data_used = 0
    data_size = 0


    # XC32 XML structure can vary slightly between versions,
    # so search all MemoryRegion nodes.
    for region in root.iter():

        name = region.attrib.get("name", "").lower()

        if "program" in name or "data" in name:
            size = region.attrib.get("length")
            used = region.attrib.get("used")

            if used is None or size is None:
                continue

            used = int(used, 0)
            size = int(size, 0)

            if "program" in name:
                program_used += used
                program_size += size

            elif "data" in name:
                data_used += used
                data_size += size


    print("--------------------------------")
    print(" PIC32 Memory Summary")
    print("--------------------------------")

    print_memory(
        "Program Memory",
        program_used,
        program_size
    )

    print_memory(
        "Data Memory",
        data_used,
        data_size
    )

    print("--------------------------------")


if __name__ == "__main__":
    main()