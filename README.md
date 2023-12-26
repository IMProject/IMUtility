<a href="https://www.bugseng.com/eclair">
  <img src="https://eclairit.com:3787/rsrc/eclair.svg" width="100" />
</a>

[![ECLAIR normal main](https://eclairit.com:3787/fs/var/local/eclair/github/IMProject/IMUtility.ecdf/ECLAIR_normal/main/latest/badge.svg)](https://eclairit.com:3787/fs/var/local/eclair/github/IMProject/IMUtility.ecdf/ECLAIR_normal/main/latest/index.html)

[Browse all ECLAIR analyses](https://eclairit.com:3787/fs/var/local/eclair/github/IMProject/IMUtility.ecdf/)


[![Discord Shield](https://discordapp.com/api/guilds/1059535033347604560/widget.png?style=shield)](https://discord.gg/R6nZxZqDH3)
[![Build](https://github.com/IMProject/IMUtility/actions/workflows/compile.yml/badge.svg)](https://github.com/IMProject/IMUtility/actions/workflows/compile.yml?query=branch%3Amain) [![Build](https://github.com/IMProject/IMUtility/actions/workflows/checks.yml/badge.svg)](https://github.com/IMProject/IMUtility/actions/workflows/checks.yml?query=branch%3Amain)
[![codecov](https://codecov.io/gh/IMProject/IMUtility/branch/main/graph/badge.svg?token=XF771QJZ1G)](https://codecov.io/gh/IMProject/IMUtility)


# IMUtility: A Safety-Critical Utility Code

## About

The IMUtility (<b>I</b>ncorporated <b>M</b>ISRA <b>U</b>tility Code) originated as a sub-repository of the [IMBootloader](https://github.com/IMProject/IMBootloader) project. After a thorough review of the available safety-critical utility open-source projects in C, we realized that none of them met our standards. Therefore, we made the decision to create our own project and make it publicly available.

Our team has meticulously laid the foundation for everything necessary to ensure the code meets the rigorous standards required for safety-critical applications. Presently, we have incorporated unit tests using the [Unity](https://github.com/ThrowTheSwitch/Unity) framework, code coverage using gcov/lcov, ensured code style conformance through Astyle formatting, and implemented cppcheck with all checks enabled. Additionally, we have enforced MISRA C 2012 checks using both cppcheck and [ECLAIR](https://www.bugseng.com/eclair), sponsored by Bugseng.

However, to further enhance the project's quality, we intend to achieve 100% coverage where feasible. This will serve as an additional layer of assurance that the code is of the highest quality and complies with safety-critical standards.

## ECLAIR
<b>ECLAIR 3.12.0</b> is certified for use in safety-critical development in compliance with:

    ISO 26262 up to ASIL D
    IEC 61508 up to SIL 4
    EN 50128 up to SIL 4
    IEC 62304 up to Class C
    ISO 25119 up to SRL 3

More info at its official web page [https://www.bugseng.com/eclair](https://www.bugseng.com/eclair).

## For contributors
We are happy to see contributions. You can add utility code that you see is missing, improve existing one, or open issue tickets. 
Before you open PR:
- write unit tests for your code
- run `make format`
- run `make cppcheck`
- run `make misra`

After PR is opened, ECLAIR will check your code and Bot will report if any MISRA violation exists in the code. 
After all violations are fixed, we will review your code, and after that code can be merged into the main branch.

#### Discord
Join us on the Discord channel https://discord.gg/R6nZxZqDH3

## List of modules
### Base64
- Base64_encode
- Base64_decode

### Bit manipulation
- BitManipulation_reflect
- BitManipulation_bitSet
- BitManipulation_setBit
- BitManipulation_clearBit
- BitManipulation_toggleBit

### Bubble sort
- BubbleSort_sort

### Crc8
- Crc8Base_tableCalculator
- Crc8Base   // Base used for calculating all Crc8 variants
- Crc8       // Basic Crc8, polynomial 0x07
- Crc8_8h2f
- Crc8_cdma2000
- Crc8_darc
- Crc8_dvbS2
- Crc8_ebu
- Crc8_icode
- Crc8_itu
- Crc8_maxim
- Crc8_rohc
- Crc8_SaeJ1850
- Crc8_saeJ1850Zero
- Crc8_wcdma

### Crc16
- Crc16Base_tableCalculator
- Crc16Base // Base used for calculating all Crc16 variants
- Crc16_a
- Crc16_arc
- Crc16_augCcit
- Crc16_buypass
- Crc16_ccitFalse
- Crc16_ccitZero (XModem)
- Crc16_cdma2000
- Crc16_dds110
- Crc16_dectR
- Crc16_dectX
- Crc16_dnp
- Crc16_en13757
- Crc16_genibus
- Crc16_kermit
- Crc16_maxim
- Crc16_mcrf4xx
- Crc16_modbus
- Crc16_riello
- Crc16_t10Dif
- Crc16_teledisk
- Crc16_tms37157
- Crc16_usb
- Crc16_x25
    
### Crc32
- Crc32Base_tableCalculator
- Crc32Base  // Base used for calculating all Crc32 variants
- Crc32      // Basic Crc32
- Crc32_bzip2
- Crc32_c
- Crc32_d
- Crc32_jamcrc
- Crc32_mpeg2
- Crc32_posix
- Crc32_q
- Crc32_xfer

### Heap sort
- HeapSort_sort

### JSON
- Json_startString
- Json_addData
- Json_endString
- Json_findByKey

### Map
- Map_init
- Map_insert
- Map_getValue

### Priority queue
- PriorityQueue_init
- PriorityQueue_empty
- PriorityQueue_enqueue
- PriorityQueue_dequeue

### Queue
- Queue_init
- Queue_full
- Queue_empty
- Queue_enqueue
- Queue_dequeue
- Queue_front
- Queue_rear

### Scheduler
- Scheduler_init
- Scheduler_addTask
- Scheduler_run

### Selection sort
- SelectionSort_sort

### Utils
- Utils_StringToUint32
- Utils_swapElements
- Utils_QuickUint32Pow10
- Utils_Serialize8
- Utils_Deserialize8
- Utils_Serialize16BE
- Utils_Serialize24BE
- Utils_Serialize32BE
- Utils_SerializeBlobBE
- Utils_Deserialize16BE
- Utils_Deserialize24BE
- Utils_Deserialize32BE
- Utils_DeserializeBlobBE
- Utils_Serialize16LE
- Utils_Serialize24LE
- Utils_Serialize32LE
- Utils_SerializeBlobLE
- Utils_Deserialize16LE
- Utils_Deserialize24LE
- Utils_Deserialize32LE
- Utils_DeserializeBlobLE
