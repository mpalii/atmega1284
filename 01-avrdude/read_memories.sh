# AVRDUDE location (change it if needed)
AVRDUDE="avrdude"

# Device part number
PART_NUMBER="m1284"

# Connectivity
CONNECTOR="usbasp-clone"

# Common expression for reading different memory sections
READ_MEMORY="$AVRDUDE -c $CONNECTOR -p $PART_NUMBER -B 1 -v -U"

$READ_MEMORY eeprom:r:eeprom_dump:h
$READ_MEMORY flash:r:flash_dump:h
$READ_MEMORY lfuse:r:lfuse_dump:h
$READ_MEMORY hfuse:r:hfuse_dump:h
$READ_MEMORY efuse:r:efuse_dump:h
$READ_MEMORY lock:r:lock_dump:h
$READ_MEMORY signature:r:signature_dump:h
$READ_MEMORY calibration:r:calibration_dump:h
