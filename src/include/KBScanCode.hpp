//Lookup tables for scancodes

namespace ENUS_Querty{
    const char ScanCodeLookupTable[] = {
        0, 0, '1', '2',
        '3', '4', '5', '6',
        '7', '8', '9', '0',
        '-', '=', 0, 0,
        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0, 0,
        'a', 's', 'd', 'f','g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
        'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
    };
}

namespace HU_Qwertz{
    const char ScanCodeLookupTable[] = {
        0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', (char)0x94, (char)0x81, (char)0xA2, 0, 0,
        'q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p', (char)0x94, (char)0xA3, 0, 0,
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', (char)0x82, (char)0xA0, '0', 0, (char)0x81,
        'y', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '-', 0, '*', 0, ' '
    };
}