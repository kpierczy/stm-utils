/* ============================================================================================================================= *//**
 * @file       version.ld
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Wednesday, 16th June 2021 12:31:43 am
 * @modified   Wednesday, 16th June 2021 12:31:43 am
 * @project    stm-utils
 * @brief      Linker script defining .version section layout
 *
 * @copyright Krzysztof Pierczyk © 2022
 *//* ============================================================================================================================= */

/* ===================================================== Sections Definitions ===================================================== */

SECTIONS
{
    /**
     * Auxiliary section storing versioning informations
     */
    .fill :
    {
        FILL(0xFF);
        . = ORIGIN(FLASH) + LENGTH(FLASH) - 0x70;
        FILL(0x00);
        PROVIDE(version_struct = .);
        *(.version)
        . = ORIGIN(FLASH) + LENGTH(FLASH) - 1;
        BYTE(0x0);
        PROVIDE(_flash_end = .);
    } > FLASH
}
