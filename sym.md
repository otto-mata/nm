## st_info

This member specifies the symbol's type and binding attributes:
- STT_NOTYPE
  - The symbol's type is not defined.
- STT_OBJECT
  - The symbol is associated with a data object.
- STT_FUNC
  - The  symbol is associated with a function or other executable
       code.
- STT_SECTION
  - The symbol is associated with a section.   Symbol  table  en‐
       tries  of  this  type exist primarily for relocation and nor‐
       mally have STB_LOCAL bindings.
- STT_FILE
  - By convention, the symbol's name gives the name of the source
       file associated with the object  file.   A  file  symbol  has
       STB_LOCAL bindings, its section index is SHN_ABS, and it pre‐
       cedes  the  other  STB_LOCAL  symbols  of  the file, if it is
       present.
- STT_LOPROC, STT_IPROC
  - Values in the inclusive range  [STT_LOPROC,  STT_HIPROC]  are
       reserved for processor-specific semantics.
- STB_LOCAL
  - Local  symbols  are  not visible outside the object file con‐
       taining their definition.  Local symbols of the same name may
       exist in multiple files without interfering with each other.
- STB_GLOBAL
  - Global symbols are visible to all  object  files  being  com‐
       bined.  One file's definition of a global symbol will satisfy
       another file's undefined reference to the same symbol.
- STB_WEAK
  - Weak  symbols  resemble global symbols, but their definitions
       have lower precedence.
