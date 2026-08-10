import sys
import xml.etree.ElementTree as ET


def parse_int(value):
    try:
        return int(value.strip())
    except Exception:
        return 0


def print_memory_usage(name, length, used):
    if length <= 0:
        print(f"{name}: missing or invalid <length> value")
        return

    usage = used / float(length) * 100.0 if length > 0 else 0.0
    print(f"{name:<10} {length:>10} {used:>10} {usage:>8.2f}%")


def main():
    if len(sys.argv) < 2:
        print("Usage: python memory_report.py <xml-file>")
        return 1

    filename = sys.argv[1]
    # filename = "../build/mz2048ech064_rtos_memory.xml"
    try:
        tree = ET.parse(filename)
        root = tree.getroot()
    except FileNotFoundError:
        print(f"Cannot open file: {filename}", file=sys.stderr)
        return 1
    except ET.ParseError as ex:
        print(f"Failed to load XML file: {ex}", file=sys.stderr)
        return 1

    memories = root.findall('.//memory')
    if not memories:
        print("No <memory> elements found in XML.")
        return 0

    print(f"{'Name':<10} {'Length':>10} {'Used':>10} {'Usage':>8}")
    print("-" * 41)

    for memory in memories:
        name = memory.get('name', 'unknown')
        length = parse_int(memory.findtext('length'))
        used = parse_int(memory.findtext('used'))
        print_memory_usage(name, length, used)

    return 0


if __name__ == '__main__':
    sys.exit(main())
