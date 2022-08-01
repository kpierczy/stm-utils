/* ============================================================================================================================= *//**
 * @file       link.ld
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Wednesday, 16th June 2021 12:31:43 am
 * @modified   Wednesday, 16th June 2021 12:31:43 am
 * @project    stm-utils
 * @brief      Linker script for STM32 MCUs. User needs to define `stack_size` symbol as well as `RAM` and `FLASH` memory regions
 *
 * @note `stack_size` is jsut an approximation that makes linker able to check whether it will fit in memory and how much 
 *    of it can be used as heap
 *
 * @copyright Krzysztof Pierczyk © 2021
 * @see https://github.com/lucckb/isixrtos/blob/master/libstm32/scripts/stm32_flash.ld
 */// ============================================================================================================================= */

/* ============================================ Interrupts' table (defined in .c file) ============================================ */

ENTRY(isrVectors)
EXTERN(isrVectors)
ASSERT(DEFINED(isrVectors), "Error no exceptions vectors entries")

/* ===================================================== Sections Definitions ===================================================== */

SECTIONS
{
    /**
     * For Cortex devices, the beginning of the startup 
	 * code is stored in the .isr_vector section, which
     * goes to FLASH
     */ 
    .isr_vector : { 
        . = ALIGN(4);
        KEEP(*(.isr_vector)) 
        . = ALIGN(4);
    } >FLASH

    /**
     * Stack-unwinding-related sections
     */	

    __exidx_start = .;
	.ARM.exidx ALIGN(4) :
	{

		*(.ARM.exidx* .gnu.linkonce.armexidx.*)

	} >FLASH
    __exidx_end = .;
	
 	.eh_frame_hdr ALIGN(4) : { KEEP (*(.eh_frame_hdr)) } >FLASH
	.eh_frame     ALIGN(4) : { KEEP (*(.eh_frame))     } >FLASH

    /**
    * Exceptions-handlers' table
    */    
    .ARM.extab ALIGN(4) :
    { 
        *(.ARM.extab* .gnu.linkonce.armextab.*) 
        . = ALIGN(4);
        *(.gcc_except_table)

    } >FLASH

    /** 
     * The program code is stored in the .text section, which goes to Flash  
     */
    .text ALIGN(4) :
    {
        /* Code start */
        _stext = .;
        
        /* User's code */
        *(.text)
        *(.text.*)

        /* Const data */
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)

        /* Glue arm to thumb and thumb to arm code */
        . = ALIGN(4);
        *(.glue_7)
        *(.glue_7t)
        /* Once-linkable GCC code */
        . = ALIGN(4);
        *(.gnu.linkonce.t.*)
        *(.gnu.linkonce.r.*)

        /* Exceptions-handlers' table */
        . = ALIGN(4);
        *(.ARM.extab* .gnu.linkonce.armextab.*)
	    . = ALIGN(4);
        *(.gcc_except_table)

        /* Floating-point related section */
        . = ALIGN(4);
        *(.vfp11_veneer)

        /* libc initialization code */
        . = ALIGN(4);
        KEEP (*(.init))
        /* GCC Perinitialization array */
		. = ALIGN(4);
		__preinit_array_start = .;
		KEEP(*(.preinit_array));
		. = ALIGN(4);
		__preinit_array_end = .;
        /* GCC Initialization array */
        . = ALIGN(4);
		__init_array_start = .;
		KEEP(*(SORT(.init_array.*)));
		. = ALIGN(4);
		KEEP(*(.init_array));
		. = ALIGN(4);
		__init_array_end = .;

        /* libc deinitialization code */
        . = ALIGN(4);
        KEEP (*(.fini))
        /* GCC Deinitialization array */
		. = ALIGN(4);
		__fini_array_start = .;
		KEEP(*(.fini_array));
		. = ALIGN(4);
		KEEP(*(SORT(.fini_array.*)));
		. = ALIGN(4);
		__fini_array_end = .;

        /* Code end */
	    . = ALIGN(4);
   	    _etext = .;
        /* This is used by the startup in order to initialize the .data secion */
   	    _sidata = _etext;
           
    } >FLASH

    /**
     * This is the initialized data section. The program executes knowing that
     * the data is in the RAM but the loader puts the initial values in the FLASH
     * (inidata). It is one task of the startup to copy the initial values from 
     * FLASH to RAM. 
     */
    .data : AT( _sidata )
    {
        /* This is used by the startup in order to initialize the .data secion */
	    . = ALIGN(8); 
        _sdata = . ;
        
        *(.data)
        *(.data.*)
		*(.gnu.linkonce.d.*)

	    /* This is used by the startup in order to initialize the .data secion */
	    . = ALIGN(8);
   	    _edata = . ;

    } >RAM

    /**
     * System's stack
     */
	.stack (NOLOAD):
	{
		. += stack_size;
		. = ALIGN(8);
		_estack = .;

	} > RAM

    /** 
     * The uninitialized data section
     */
    .bss (NOLOAD) : 
    {
        /* This is used by the startup in order to initialize the .bss secion */
        . = ALIGN(8);
        _sbss = .;
        
        *(.bss)
        *(.bss.*)
        *(.gnu.linkonce.b.*)
        *(COMMON)
        
	    /* This is used by the startup in order to initialize the .bss secion */
	    . = ALIGN(8);
   	    _ebss = . ;

    } >RAM
    
    /** 
     * The heap section
     */
    /* .heap (NOLOAD):
    {
        . = ALIGN(8);
        _heap_start = .;

        . = ORIGIN(RAM) + LENGTH(RAM);

        . = ALIGN(8);
        _heap_end = .;
        
    } > RAM */
    
    PROVIDE( __heap_start = _heap_start );
    PROVIDE( __heap_end = _heap_end );
    
    /**
     * Remove the debugging information from the standard libraries 
     */
    /DISCARD/ :
    {
		libc.a ( * )
		libm.a ( * )
		libgcc.a ( * )
	}

    /** 
     * Stabs debugging sections
     */
    .stab          0 : { *(.stab) }
    .stabstr       0 : { *(.stabstr) }
    .stab.excl     0 : { *(.stab.excl) }
    .stab.exclstr  0 : { *(.stab.exclstr) }
    .stab.index    0 : { *(.stab.index) }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment       0 : { *(.comment) }

    /**
     * DWARF debug sections. Symbols in the DWARF debugging sections are relative
     * to the beginning of the section so we begin them at 0.  
     */

    /* DWARF 1 */
    .debug          0 : { *(.debug) }
    .line           0 : { *(.line) }
    /* GNU DWARF 1 extensions */
    .debug_srcinfo  0 : { *(.debug_srcinfo) }
    .debug_sfnames  0 : { *(.debug_sfnames) }
    /* DWARF 1.1 and DWARF 2 */
    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
    /* DWARF 2 */
    .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev   0 : { *(.debug_abbrev) }
    .debug_line     0 : { *(.debug_line) }
    .debug_frame    0 : { *(.debug_frame) }
    .debug_str      0 : { *(.debug_str) }
    .debug_loc      0 : { *(.debug_loc) }
    .debug_macinfo  0 : { *(.debug_macinfo) }
    /* SGI/MIPS DWARF 2 extensions */
    .debug_weaknames 0 : { *(.debug_weaknames) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames  0 : { *(.debug_varnames) }
    
    note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
	.ARM.attributes 0 : { KEEP (*(.ARM.attributes)) }
	/DISCARD/ : { *(.note.GNU-stack) }
}
