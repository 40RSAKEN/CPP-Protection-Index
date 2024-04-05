#pragma once

#include <Windows.h>
#include <winternl.h>
#include <string>


namespace AntiCrack {
    
    int PreventDumping() {
        const auto peb = (PPEB)__readgsqword(0x60);
        const auto in_load_order_module_list = (PLIST_ENTRY)peb->Ldr->Reserved2[1];
        const auto table_entry = CONTAINING_RECORD(in_load_order_module_list, LDR_DATA_TABLE_ENTRY, Reserved1[0]);
        const auto p_size_of_image = (PULONG)&table_entry->Reserved3[1];
        *p_size_of_image = (ULONG)((INT_PTR)table_entry->DllBase + 0x100000);
        return 0;
    }
}  

namespace {
    
    constexpr char kObfuscatedString[] = "\x25\x18\x15\x2F\x2F\x1C\x1D\x06\x18\x0C\x14\x25\x2E\x1A\x1F\x17\x25\x1F\x15\x1A\x17\x25\x1A\x0F\x06\x1D\x14\x25\x1F\x04\x0C\x0C\x1D\x06\x18\x0C\x0C\x2E\x1A\x06\x0F\x1D\x14\x25\x1A\x1F\x0C\x14\x25\x2E\x1A\x1F\x17\x25\x0E\x06\x14\x0F\x2B\x25\x18\x15\x2F\x2F\x1C\x1D\x06\x18\x0C\x14\x25\x2E\x1A\x1F\x17\x25\x1F\x15\x1A\x17\x25\x1A\x0F\x06\x1D\x14\x25\x1F\x04\x0C\x0C\x1D\x06\x18\x0C\x0C\x2E\x1A\x06\x0F\x1D\x14\x25\x1A\x1F\x0C\x14\x25\x2E\x1A\x1F\x17\x25\x0E\x06\x14\x0F\x2B\x25\x18\x15\x2F\x2F\x1C\x1D\x06\x18\x0C\x14\x25\x2E\x1A\x1F\x17\x25\x1F\x15\x1A\x17\x25\x1A\x0F\x06\x1D\x14\x25\x1F\x04\x0C\x0C\x1D\x06\x18\x0C\x0C\x2E\x1A\x06\x0F\x1D\x14\x25\x1A\x1F\x0C\x14\x25\x2E\x1A\x1F\x17\x25\x0E\x06\x14\x0F\x2B\x25\x18\x15\x2F\x2F\x1C\x1D\x06\x18\x0C\x14\x25\x2E\x1A\x1F\x17\x25\x1F\x15\x1A\x17\x25\x1A\x0F\x06\x1D\x14\x25\x1F\x04\x0C\x0C\x1D\x06\x18\x0C\x0C\x2E\x1A\x06\x0F\x1D\x14\x25\x1A\x1F\x0C\x14\x25\x2E\x1A\x1F\x17\x25\x0E\x06\x14\x0F\x2B";

    // Modify the string since this is open source, and then modify the decode function

    std::string Decode(const char* obfuscated_string) {
        std::string result;
        for (size_t i = 0; obfuscated_string[i]; ++i) {
            result += static_cast<char>(obfuscated_string[i] ^ 0x23); // <---
        }
        return result;
    }

    int OPD() {
        const std::string decoded_string = Decode(kObfuscatedString);
        const auto peb = (PPEB)__readgsqword(0x60);
        const auto in_load_order_module_list = (PLIST_ENTRY)peb->Ldr->Reserved2[1];
        const auto table_entry = CONTAINING_RECORD(in_load_order_module_list, LDR_DATA_TABLE_ENTRY, Reserved1[0]);
        const auto p_size_of_image = (PULONG)&table_entry->Reserved3[1];
        *p_size_of_image = (ULONG)((INT_PTR)table_entry->DllBase + 0x100000);
        return 0;
    }
}  