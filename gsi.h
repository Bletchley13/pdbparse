#ifndef __GSI_H__
#define __GSI_H__

#include "msf.h"
#include "pdb.h"
#include "pdb_info.h"


typedef union _SYM
{
        ALIGNSYM Sym;
        ANNOTATIONSYM Annotation;
        ATTRMANYREGSYM AttrManyReg;
        ATTRMANYREGSYM2 AttrManyReg2;
        ATTRREGREL AttrRegRel;
        ATTRREGSYM AttrReg;
        ATTRSLOTSYM AttrSlot;
        BLOCKSYM Block;
        BLOCKSYM16 Block16;
        BLOCKSYM32 Block32;
        BPRELSYM16 BpRel16;
        BPRELSYM32 BpRel32;
        BPRELSYM32_16t BpRel32_16t;
        CEXMSYM16 Cexm16;
        CEXMSYM32 Cexm32;
        CFLAGSYM CFlag;
        COMPILESYM Compile;
        CONSTSYM Const;
        CONSTSYM_16t Const_16t;
        DATASYM16 Data16;
        DATASYM32 Data32;
        ENTRYTHISSYM EntryThis;
        FRAMEPROCSYM FrameProc;
        FRAMERELSYM FrameRel;
        LABELSYM16 Label16;
        LABELSYM32 Label32;
        MANPROCSYM ManProc;
        MANPROCSYMMIPS ManProcMips;
        MANTYPREF ManTypRef;
        MANYREGSYM_16t ManyReg_16t;
        MANYREGSYM ManyReg;
        MANYREGSYM2 ManyReg2;
        OBJNAMESYM ObjName;
        OEMSYMBOL Oem;
        PROCSYM16 Proc16;
        PROCSYM32 Proc32;
        PROCSYM32_16t Proc32_16t;
        PROCSYMIA64 ProcIA64;
        PROCSYMMIPS ProcMips;
        PROCSYMMIPS_16t ProcMips_16t;
        PUBSYM32 Pub32;
        REFSYM Ref;
        REFSYM2 Ref2;
        REGREL16 RegRel16;
        REGREL32_16t RegRel32_16t;
        REGREL32 RegRel32;
        REGSYM Reg;
        RETURNSYM Return;
        SEARCHSYM Search;
        SLINK32 Slink32;
        SLOTSYM32 Slot32;
        SYMTYPE SymType;
        THREADSYM32_16t Thread_16t;
        THUNKSYM Thunk;
        THUNKSYM16 Thunk16;
        THUNKSYM32 Thunk32;
        TRAMPOLINESYM Trampoline;
        UDTSYM Udt;
        UDTSYM_16t Udt_16t;
        UNAMESPACE UNameSpace;
        VPATHSYM16 VPath16;
        VPATHSYM32 VPath32;
        VPATHSYM32_16t VPath32_16t;
        WITHSYM16 With16;
        WITHSYM32 With32;
} SYM, *PSYM;



typedef struct _PSGSIHDR
{
/*000*/ int32_t  cbSymHash;
/*004*/ int32_t  cbAddrMap;
/*008*/ uint32_t nThunks;
/*00C*/ int32_t  cbSizeOfThunk;
/*010*/ uint16_t  isectThunkTable;
/*012*/ uint16_t  reserved;        // padding
/*014*/ int32_t  offThunkTable;
/*018*/ uint32_t nSects;
/*01C*/
} PSGSIHDR, *PPSGSIHDR, **PPPSGSIHDR;

typedef struct MSF_STREAM_REF_PSGSIHDR
{
        PSGSIHDR *Data;
        size_t Size;
} MSF_STREAM_REF_PSGSIHDR;


typedef struct _NewDBIHdr
{
/*000*/ uint32_t verSignature;
/*004*/ uint32_t verHdr;
/*008*/ uint32_t age;
/*00C*/ uint16_t  snGSSyms;          // stream #
/*00E*/ uint16_t  usVerPdbDllMajMin;
/*010*/ uint16_t  snPSSyms;          // stream #
/*012*/ uint16_t  usVerPdbDllBuild;
/*014*/ union
/*014*/     {
/*014*/     uint16_t  snSymRecs;     // stream #
/*014*/     uint32_t ulunusedPad2;
/*018*/     };
/*018*/ uint32_t  cbGpModi;
/*01C*/ uint32_t  cbSC;
/*020*/ uint32_t  cbSecMap;
/*024*/ uint32_t  cbFileInfo;
/*028*/ uint32_t  cbTSMap;
/*02C*/ uint32_t iMFC;
/*030*/ uint32_t  cbDbgHdr;
/*034*/ uint32_t  cbECInfo;
/*038*/ uint16_t  flags;
/*03A*/ uint16_t  wMachine;
/*03C*/ uint32_t rgulReserved [1];
/*040*/
} NewDBIHdr, *PNewDBIHdr, **PPNewDBIHdr;

typedef struct MSF_STREAM_REF_NewDBIHdr
{
        NewDBIHdr *Data;
        size_t Size;
} MSF_STREAM_REF_NewDBIHdr;

typedef struct _SYMD
{
        MSF *msf;

        PNewDBIHdr dbi;
        uint32_t DbiSize;
        PSYM SymRecs;
        PSYM SymMac;
        uint32_t SymSize;
        PHDR TpiHdr;

        MSF_STREAM_REF_GSIHashHdr gsi;
        void* pGSHr;
        void* pGSBuckets;
        int nGSHrs;
        int nGSBuckets;
        MSF_STREAM_REF_PSGSIHDR psi;
        PGSIHashHdr pgsiPSHash;
        void* pPSHr;
        void* pPSBuckets;
        void* pPSAddrMap;
        int nPSHrs;
        int nPSBuckets;
        int nPSAddrMap;

} SYMD, *PSYMD;



PSYMD SYMLoadSymbols (MSF* msf);

#endif
