[![ECLAIR](https://eclairit.com:3787/rsrc/eclair.png)](https://www.bugseng.com/eclair)

[![ECLAIR normal main](https://eclairit.com:3787/fs/home/eclair-github/public/IMProject/IMUtility.ecdf/ECLAIR_normal/main/latest/badge.svg)](https://eclairit.com:3787/fs/home/eclair-github/public/IMProject/IMUtility.ecdf/ECLAIR_normal/main/latest/index.html)

[![ECLAIR final main](https://eclairit.com:3787/fs/home/eclair-github/public/IMProject/IMUtility.ecdf/ECLAIR_final/main/latest/badge.svg)](https://eclairit.com:3787/fs/home/eclair-github/public/IMProject/IMUtility.ecdf/ECLAIR_final/main/latest/index.html)

[Browse all ECLAIR analyses](https://eclairit.com:3787/fs/home/eclair-github/public/IMProject/IMUtility.ecdf/)


[![Discord Shield](https://discordapp.com/api/guilds/1059535033347604560/widget.png?style=shield)](https://discord.gg/R6nZxZqDH3)
[![Build](https://github.com/IMProject/IMUtility/actions/workflows/compile.yml/badge.svg)](https://github.com/IMProject/IMUtility/actions/workflows/compile.yml?query=branch%3Amain) [![Build](https://github.com/IMProject/IMUtility/actions/workflows/checks.yml/badge.svg)](https://github.com/IMProject/IMUtility/actions/workflows/checks.yml?query=branch%3Amain)


# Incorporated MISRA C 2012 Utility code

## About

The IMUtility (<b>I</b>ncorporated <b>M</b>ISRA <b>U</b>tility Code) originated as a sub-repository of the [IMBootloader](https://github.com/IMProject/IMBootloader) project. After a thorough review of the available safety-critical utility open-source projects in C, we realized that none of them met our standards. Therefore, we made the decision to create our own project and make it publicly available.

Our team has meticulously laid the foundation for everything necessary to ensure the code meets the rigorous standards required for safety-critical applications. Presently, we have incorporated unit tests using the [Unity](https://github.com/ThrowTheSwitch/Unity) framework, ensured code style conformance through Astyle formatting, and implemented cppcheck with all checks enabled. Additionally, we have enforced MISRA C 2012 checks using both cppcheck and [ECLAIR](https://www.bugseng.com/eclair), sponsored by Buggseng.

However, to further enhance the project's quality, we intend to add a code coverage check for unit tests to achieve 100% coverage where feasible. This will serve as an additional layer of assurance that the code is of the highest quality and complies with safety-critical standards.

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

After PR is open ECLAIR will check your code and Bot will report any MISRA violation existing in the code. 
After you fix all violations we will review your code, and after that code can be merged into the main branch.

#### Discord
Join us on the Discord channel https://discord.gg/R6nZxZqDH3

## List of modules
### Base64
- Base64_encode
- Base64_decode

### Bubble sort
- BubbleSort_sort

### CRC32
- CalculateCRC32

### Heap sort
- HeapSort_sort

### JSON
- Json_startString
- Json_addData
- Json_endString
- Json_findByKey

### Priority queue
- PriorityQueue_initQueue
- PriorityQueue_isEmpty
- PriorityQueue_enqueue
- PriorityQueue_dequeue

### Queue
- Queue_initQueue
- Queue_isFull
- Queue_isEmpty
- Queue_enqueue
- Queue_dequeue
- Queue_front
- Queue_rear

### Scheduler
- Scheduler_init
- Scheduler_addTask
- Scheduler_run

### Utils
- Utils_QuickUint32Pow10
- Utils_StringToUint32
- Utils_SwapElements

- Utils_SerializeBlobBE
- Utils_Serialize32BE
- Utils_Serialize24BE
- Utils_Serialize16BE
- Utils_Serialize8BE
- Utils_DeserializeBlobBE
- Utils_Deserialize32BE
- Utils_Deserialize24BE
- Utils_Deserialize16BE
- Utils_Deserialize8BE

- Utils_SerializeBlobLE
- Utils_DeserializeBlobLE

