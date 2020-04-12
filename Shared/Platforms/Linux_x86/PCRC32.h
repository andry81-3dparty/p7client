////////////////////////////////////////////////////////////////////////////////
//                                                                             /
// 2012-2020 (c) Baical                                                        /
//                                                                             /
// This library is free software; you can redistribute it and/or               /
// modify it under the terms of the GNU Lesser General Public                  /
// License as published by the Free Software Foundation; either                /
// version 3.0 of the License, or (at your option) any later version.          /
//                                                                             /
// This library is distributed in the hope that it will be useful,             /
// but WITHOUT ANY WARRANTY; without even the implied warranty of              /
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU           /
// Lesser General Public License for more details.                             /
//                                                                             /
// You should have received a copy of the GNU Lesser General Public            /
// License along with this library.                                            /
//                                                                             /
////////////////////////////////////////////////////////////////////////////////
#ifndef PCRC32_H
#define PCRC32_H


////////////////////////////////////////////////////////////////////////////////
//Get_CRC32
//This function implement 2 calculation kinds:
// * AT&T assembler for X86 architecture for GNU C compiler
// * standard C function for all other cases like X64 or ARM
//Assembler code if faster than generated by GCC (o2) up to 1% it is not a lot
//but for big amount of data and often calculation is enough to use it.
static UNUSED_FUNC tUINT32 Get_CRC32(tUINT8 *i_pData, size_t i_szCount)
{
    tUINT32 l_dwResult = 0xFFFFFFFF;

    if (    (NULL == i_pData)
         || (0  >= i_szCount) 
       )
    {
        return l_dwResult;
    }
    
#if defined(__i386__) && defined(__GNUC__) && !defined(__PIC__)
    // Register use:
    //  eax - CRC32 value
    //  ebx - a lot of things
    //  ecx - CRC32 value
    //  edx - address of end of buffer
    //  esi - address of start of buffer
    //  edi - CRC32 table
    
    __asm__("push %%esi;" // Save the esi and edi registers
            "push %%edi;"
            //"movl l_dwResult, %%ecx;" do it already by constraints
            //"movl g_ppCRC32_Table, %%edi;"
            "leal (%%esi,%%ebx),%%edx;" // Calculate the end of the buffer
            "crc32loop%=:;"
            "xorl %%eax, %%eax;"         // Clear the eax register"
            "movb (%%esi), %%bl;"
            "movb %%cl, %%al;"           // Copy crc value into eax
            "incl %%esi;"                // Advance the source pointer
            "xorb %%bl, %%al;"           // Create the index into the CRC32 table
            "shr $8, %%ecx;"
            "movl (%%edi, %%eax, 4), %%ebx;" // Get the value out of the table
            "xorl %%ebx, %%ecx;"             // xor with the current byte
            "cmpl %%edx, %%esi;"              // Have we reached the end of the buffer?
            "jne crc32loop%=;"
            "pop %%edi;"
            "pop %%esi;"
    
            //output 
            :"=c"(l_dwResult)                       
            //input
            :"D"(g_ppCRC32_Table), "c"(l_dwResult), "S"(i_pData), "b"(i_szCount)  
           );
#else
    for (size_t l_szI = 0;  l_szI < i_szCount;  l_szI ++)
    {
        l_dwResult = g_ppCRC32_Table[(l_dwResult  ^ i_pData[l_szI]) & 0xFF ] ^ (l_dwResult >> 8);
    }
    /* Suppress warning that this is not used */
    (void)g_ppCRC32_Table;
#endif    
    return l_dwResult;
} 

#endif //PCRC32_H
