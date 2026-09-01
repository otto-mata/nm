#pragma once
#define SEC_NO_FLAGS 0x0

/* Tells the OS to allocate space for this section when loading.
   This is clear for a section containing debug information only.  */
#define SEC_ALLOC 0x1

/* Tells the OS to load the section from the file when loading.
   This is clear for a .bss section.  */
#define SEC_LOAD 0x2

/* The section contains data still to be relocated, so there is
   some relocation information too.  */
#define SEC_RELOC 0x4

/* A signal to the OS that the section contains read only data.  */
#define SEC_READONLY 0x8

/* The section contains code only.  */
#define SEC_CODE 0x10

/* The section contains data only.  */
#define SEC_DATA 0x20

/* The section will reside in ROM.  */
#define SEC_ROM 0x40

/* The section contains constructor information. This section
   type is used by the linker to create lists of constructors and
   destructors used by <<g++>>. When a back end sees a symbol
   which should be used in a constructor list, it creates a new
   section for the type of name (e.g., <<__CTOR_LIST__>>), attaches
   the symbol to it, and builds a relocation. To build the lists
   of constructors, all the linker has to do is catenate all the
   sections called <<__CTOR_LIST__>> and relocate the data
   contained within - exactly the operations it would peform on
   standard data.  */
#define SEC_CONSTRUCTOR 0x80

/* The section has contents - a data section could be
   <<SEC_ALLOC>> | <<SEC_HAS_CONTENTS>>; a debug section could be
   <<SEC_HAS_CONTENTS>>  */
#define SEC_HAS_CONTENTS 0x100

/* An instruction to the linker to not output the section
   even if it has information which would normally be written.  */
#define SEC_NEVER_LOAD 0x200

/* The section contains thread local data.  */
#define SEC_THREAD_LOCAL 0x400

/* The section's size is fixed.  Generic linker code will not
   recalculate it and it is up to whoever has set this flag to
   get the size right.  */
#define SEC_FIXED_SIZE 0x800

/* The section contains common symbols (symbols may be defined
   multiple times, the value of a symbol is the amount of
   space it requires, and the largest symbol value is the one
   used).  Most targets have exactly one of these (which we
   translate to bfd_com_section_ptr), but ECOFF has two.  */
#define SEC_IS_COMMON 0x1000

/* The section contains only debugging information.  For
   example, this is set for ELF .debug and .stab sections.
   strip tests this flag to see if a section can be
   discarded.  */
#define SEC_DEBUGGING 0x2000

/* The contents of this section are held in memory pointed to
   by the contents field.  This is checked by bfd_get_section_contents,
   and the data is retrieved from memory if appropriate.  */
#define SEC_IN_MEMORY 0x4000

/* The contents of this section are to be excluded by the
   linker for executable and shared objects unless those
   objects are to be further relocated.  */
#define SEC_EXCLUDE 0x8000

/* The contents of this section are to be sorted based on the sum of
   the symbol and addend values specified by the associated relocation
   entries.  Entries without associated relocation entries will be
   appended to the end of the section in an unspecified order.  */
#define SEC_SORT_ENTRIES 0x10000

/* When linking, duplicate sections of the same name should be
   discarded, rather than being combined into a single section as
   is usually done.  This is similar to how common symbols are
   handled.  See SEC_LINK_DUPLICATES below.  */
#define SEC_LINK_ONCE 0x20000

/* If SEC_LINK_ONCE is set, this bitfield describes how the linker
   should handle duplicate sections.  */
#define SEC_LINK_DUPLICATES 0xc0000

/* This value for SEC_LINK_DUPLICATES means that duplicate
   sections with the same name should simply be discarded.  */
#define SEC_LINK_DUPLICATES_DISCARD 0x0

/* This value for SEC_LINK_DUPLICATES means that the linker
   should warn if there are any duplicate sections, although
   it should still only link one copy.  */
#define SEC_LINK_DUPLICATES_ONE_ONLY 0x40000

/* This value for SEC_LINK_DUPLICATES means that the linker
   should warn if any duplicate sections are a different size.  */
#define SEC_LINK_DUPLICATES_SAME_SIZE 0x80000

/* This value for SEC_LINK_DUPLICATES means that the linker
   should warn if any duplicate sections contain different
   contents.  */
#define SEC_LINK_DUPLICATES_SAME_CONTENTS \
   (SEC_LINK_DUPLICATES_ONE_ONLY | SEC_LINK_DUPLICATES_SAME_SIZE)

/* This section was created by the linker as part of dynamic
   relocation or other arcane processing.  It is skipped when
   going through the first-pass output, trusting that someone
   else up the line will take care of it later.  */
#define SEC_LINKER_CREATED 0x100000

/* This section contains a section ID to distinguish different
   sections with the same section name.  */
#define SEC_ASSEMBLER_SECTION_ID 0x100000

/* This section should not be subject to garbage collection.
   Also set to inform the linker that this section should not be
   listed in the link map as discarded.  */
#define SEC_KEEP 0x200000

/* This section contains "short" data, and should be placed
   "near" the GP.  */
#define SEC_SMALL_DATA 0x400000

/* Attempt to merge identical entities in the section.
   Entity size is given in the entsize field.  */
#define SEC_MERGE 0x800000

/* If given with SEC_MERGE, entities to merge are zero terminated
   strings where entsize specifies character size instead of fixed
   size entries.  */
#define SEC_STRINGS 0x1000000

/* This section contains data about section groups.  */
#define SEC_GROUP 0x2000000

/* The section is a COFF shared library section.  This flag is
   only for the linker.  If this type of section appears in
   the input file, the linker must copy it to the output file
   without changing the vma or size.  FIXME: Although this
   was originally intended to be general, it really is COFF
   specific (and the flag was renamed to indicate this).  It
   might be cleaner to have some more general mechanism to
   allow the back end to control what the linker does with
   sections.  */
#define SEC_COFF_SHARED_LIBRARY 0x4000000

/* This input section should be copied to output in reverse order
   as an array of pointers.  This is for ELF linker internal use
   only.  */
#define SEC_ELF_REVERSE_COPY 0x4000000

/* This section contains data which may be shared with other
   executables or shared objects. This is for COFF only.  */
#define SEC_COFF_SHARED 0x8000000

/* Indicate that section has the purecode flag set.  */
#define SEC_ELF_PURECODE 0x8000000

/* When a section with this flag is being linked, then if the size of
   the input section is less than a page, it should not cross a page
   boundary.  If the size of the input section is one page or more,
   it should be aligned on a page boundary.  This is for TI
   TMS320C54X only.  */
#define SEC_TIC54X_BLOCK 0x10000000

/* This section has the SHF_X86_64_LARGE flag.  This is ELF x86-64 only.  */
#define SEC_ELF_LARGE 0x10000000

/* Conditionally link this section; do not link if there are no
   references found to any symbol in the section.  This is for TI
   TMS320C54X only.  */
#define SEC_TIC54X_CLINK 0x20000000

/* This section contains vliw code.  This is for Toshiba MeP only.  */
#define SEC_MEP_VLIW 0x20000000

/* All symbols, sizes and relocations in this section are octets
   instead of bytes.  Required for DWARF debug sections as DWARF
   information is organized in octets, not bytes.  */
#define SEC_ELF_OCTETS 0x40000000
