#!/bin/bash

# AVRDUDE location (change if needed)
AVRDUDE="${AVRDUDE:-avrdude}"

# Device part number (can be overridden via env variable or argument)
PART_NUMBER="${1:-${PART_NUMBER:-m1284}}"

# Connectivity (can be overridden via env variable or argument)
CONNECTOR="${2:-${CONNECTOR:-usbasp-clone}}"

# Read format
FORMAT="h"

# Output directory (optional)
OUTPUT_DIR="avr_snapshot_$(date +%Y%m%d_%H%M%S)"
mkdir -p "$OUTPUT_DIR"

# Memory sections to read
MEMORY_SECTIONS=(eeprom flash lfuse hfuse efuse lock signature calibration)

# Check if avrdude is installed
if ! command -v "$AVRDUDE" &>/dev/null; then
    echo "Error: avrdude not found. Please install it and try again."
    exit 1
fi

# Read each memory section
for section in "${MEMORY_SECTIONS[@]}"; do
    OUTPUT_FILE="$OUTPUT_DIR/${section}_dump.$FORMAT"
    echo "Reading '$section'..."
    if ! $AVRDUDE -c "$CONNECTOR" -p "$PART_NUMBER" -v -U "$section:r:$OUTPUT_FILE:$FORMAT"; then
        echo "Warning: Failed to read $section"
    fi
done

echo "Snapshot saved in $OUTPUT_DIR"
