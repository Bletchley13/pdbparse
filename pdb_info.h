

// =================================================================
// TPI STRUCTURES (STREAM #2)
// =================================================================


// -----------------------------------------------------------------

typedef struct _OffCb
        {
/*000*/ int32_t off;
/*004*/ int32_t cb;
/*008*/ }
        OffCb, *POffCb, **PPOffCb;

#define OffCb_ sizeof (OffCb)

// -----------------------------------------------------------------

typedef struct _TpiHash
        {
/*000*/ uint16_t  sn;            // stream #
/*002*/ uint16_t  snPad;         // padding
/*004*/ int32_t  cbHashKey;
/*008*/ int32_t  cHashBuckets;
/*00C*/ OffCb offcbHashVals;
/*014*/ OffCb offcbTiOff;
/*01C*/ OffCb offcbHashAdj;
/*024*/ }
        TpiHash, *PTpiHash, **PPTpiHash;

#define TpiHash_ sizeof (TpiHash)

// -----------------------------------------------------------------

typedef struct _HDR          // TPI stream header
        {
/*000*/ uint32_t   vers;        // implementation version
/*004*/ int32_t    cbHdr;       // header size
/*008*/ uint32_t   tiMin;       // type index base  (0x1000..0xFFFFFF)
/*00C*/ uint32_t   tiMac;       // type index limit (0x1000..0xFFFFFF)
/*010*/ uint32_t   cbGprec;     // size of follow-up data
/*014*/ TpiHash tpihash;
/*038*/ }
        HDR, *PHDR, **PPHDR;

#define HDR_ sizeof (HDR)

// -----------------------------------------------------------------

typedef struct _OHDR
        {
/*000*/ uint8_t  szMagic [0x2C]; // magic string
/*02C*/ uint32_t vers;           // implementation version
/*030*/ uint32_t sig;            // signature
/*034*/ uint32_t age;            // file age
/*038*/ uint16_t  tiMin;          // type index base
/*03A*/ uint16_t  tiMac;          // type index limit
/*03C*/ int32_t  cb;             // size
/*040*/ }
        OHDR, *POHDR, **PPOHDR;

#define OHDR_ sizeof (OHDR)

// -----------------------------------------------------------------

typedef struct _CV_prop_t
        {
/*000.0*/ uint16_t packed   : 1;
/*000.1*/ uint16_t ctor     : 1;
/*000.2*/ uint16_t ovlops   : 1;
/*000.3*/ uint16_t isnested : 1;
/*000.4*/ uint16_t cnested  : 1;
/*000.5*/ uint16_t opassign : 1;
/*000.6*/ uint16_t opcast   : 1;
/*000.7*/ uint16_t fwdref   : 1;
/*001.0*/ uint16_t scoped   : 1;
/*001.1*/ uint16_t reserved : 7;
/*002*/ }
        CV_prop_t, *PCV_prop_t, **PPCV_prop_t;

#define CV_prop_t_ sizeof (CV_prop_t)

// -----------------------------------------------------------------

typedef struct _CV_fldattr_t
        {
/*000.0*/ uint16_t access      : 2; // CV_access_e
/*000.2*/ uint16_t mprop       : 3; // CV_methodprop_e
/*000.5*/ uint16_t pseudo      : 1;
/*000.6*/ uint16_t noinherit   : 1;
/*000.7*/ uint16_t noconstruct : 1;
/*001.0*/ uint16_t compgenx    : 1;
/*001.1*/ uint16_t unused      : 7;
/*002*/ }
        CV_fldattr_t, *PCV_fldattr_t, **PPCV_fldattr_t;

#define CV_fldattr_t_ sizeof (CV_fldattr_t)

// -----------------------------------------------------------------

typedef struct _lfArray         // array
        {
/*000*/ uint16_t  leaf;             // LF_ARRAY
/*002*/ uint32_t elemtype;         // element type index
/*006*/ uint32_t idxtype;          // indexing type index
/*00A*/ uint8_t  data [];          // size in bytes
/*00A*/ }
        lfArray, *PlfArray, **PPlfArray;

#define lfArray_ sizeof (lfArray)

// -----------------------------------------------------------------

typedef struct _lfBitfield      // bitfield structure
        {
/*000*/ uint16_t  leaf;             // LF_BITFIELD
/*002*/ uint32_t type;             // base type index
/*006*/ uint8_t  length;           // number of bits
/*007*/ uint8_t  position;         // bit offset of bit 0
/*008*/ }
        lfBitfield, *PlfBitfield, **PPlfBitfield;

#define lfBitfield_ sizeof (lfBitfield)

// -----------------------------------------------------------------

typedef struct _lfClass         // class or structure
        {
/*000*/ uint16_t      leaf;         // LF_CLASS, LF_STRUCTURE
/*002*/ uint16_t      count;        // number of members
/*004*/ CV_prop_t property;     // type properties
/*006*/ uint32_t     field;        // LF_FIELD descriptor index
/*00A*/ uint32_t     derived;
/*00E*/ uint32_t     vshape;
/*012*/ uint8_t      data [];      // size and name
/*012*/ }
        lfClass, *PlfClass, **PPlfClass;

#define lfClass_ sizeof (lfClass)

// -----------------------------------------------------------------

typedef lfClass lfStructure, *PlfStructure, **PPlfStructure;
#define lfStructure_ sizeof (lfStructure)

// -----------------------------------------------------------------

typedef struct _lfUnion         // union
        {
/*000*/ uint16_t      leaf;         // LF_UNION
/*002*/ uint16_t      count;        // number of members
/*004*/ CV_prop_t property;     // type properties
/*006*/ uint32_t     field;        // LF_FIELD descriptor index
/*00A*/ uint8_t      data [];      // size and name
/*00A*/ }
        lfUnion, *PlfUnion, **PPlfUnion;

#define lfUnion_ sizeof (lfUnion)

// -----------------------------------------------------------------

typedef struct _lfEnum          // enumeration
        {
/*000*/ uint16_t      leaf;         // LF_ENUM
/*002*/ uint16_t      count;        // number of members
/*004*/ CV_prop_t property;     // type properties
/*006*/ uint32_t     utype;        // underlying type
/*00A*/ uint32_t     field;        // LF_FIELD descriptor index
/*00E*/ uint8_t      Name [];      // name
/*00E*/ }
        lfEnum, *PlfEnum, **PPlfEnum;

#define lfEnum_ sizeof (lfEnum)

// -----------------------------------------------------------------

typedef struct _lfPointer       // pointer to type
        {
/*000*/ struct lfPointerBody
/*000*/     {
/*000*/     uint16_t  leaf;         // LF_POINTER
/*002*/     uint32_t utype;        // underlying type
/*006*/     struct lfPointerAttr
/*006*/         {
/*006.0*/       uint32_t ptrtype     :  5; // pointer type
/*006.5*/       uint32_t ptrmode     :  3; // pointer mode
/*007.0*/       uint32_t isflat32    :  1; // 0:32 pointer
/*007.1*/       uint32_t isvolatile  :  1; // volatile pointer
/*007.2*/       uint32_t isconst     :  1; // constant pointer
/*007.3*/       uint32_t isunaligned :  1; // unaligned pointer
/*007.4*/       uint32_t isrestrict  :  1; // restricted pointer
/*007.5*/       uint32_t unused      : 19; // currently unused
/*00A*/         } attr;
/*00A*/     } body;
/*00A*/ union
/*00A*/     {
/*00A*/     struct
/*00A*/         {
/*00A*/         uint32_t pmclass;
/*00E*/         uint16_t  pmenum;
/*010*/         } pm;
/*00A*/     uint16_t bseg;
/*00A*/     uint8_t Sym [1];
/*00A*/     struct
/*00A*/         {
/*00A*/         uint32_t index;
/*00E*/         uint8_t  name [1];
/*00E*/         } btype;
/*010*/     } pbase;
/*010*/ }
        lfPointer, *PlfPointer, **PPlfPointer;

#define lfPointer_ sizeof (lfPointer)

// -----------------------------------------------------------------

typedef struct _lfProc          // procedure
        {
/*000*/ uint16_t  leaf;             // LF_PROCEDURE
/*002*/ uint32_t rvtype;           // return value type
/*006*/ uint8_t  calltype;         // calling convention (CV_call_e)
/*007*/ uint8_t  reserved;         // currently not used
/*008*/ uint16_t  parmcount;        // number of parameters
/*00A*/ uint32_t arglist;          // argument list type
/*00E*/ }
        lfProc, *PlfProc, **PPlfProc;

#define lfProc_ sizeof (lfProc)

// -----------------------------------------------------------------

typedef struct _lfMFunc         // member function
        {
/*000*/ uint16_t  leaf;             // LF_MFUNCTION
/*002*/ uint32_t rvtype;           // return value type
/*006*/ uint32_t classtype;        // containing class type
/*00A*/ uint32_t thistype;         // this-pointer type
/*00E*/ uint8_t  calltype;         // calling convention (CV_call_e)
/*00F*/ uint8_t  reserved;         // currently not used
/*010*/ uint16_t  parmcount;        // number of parameters
/*012*/ uint32_t arglist;          // argument list type
/*016*/ int32_t  thisadjust;       // this-adjuster
/*01A*/ }
        lfMFunc, *PlfMFunc, **PPlfMFunc;

#define lfMFunc_ sizeof (lfMFunc)

// -----------------------------------------------------------------

typedef struct _lfArgList       // procedure argument list
        {
/*000*/ uint16_t  leaf;             // LF_ARGLIST
/*002*/ uint32_t count;            // number of arguments
/*006*/ uint32_t arg [];           // argument types
/*006*/ }
        lfArgList, *PlfArgList, **PPlfArgList;

#define lfArgList_ sizeof (lfArgList)

// -----------------------------------------------------------------

typedef struct _lfVTShape       // virtual function table shape
        {
/*000*/ uint16_t leaf;              // LF_VTSHAPE
/*002*/ uint16_t count;             // number of VFT entries
/*004*/ uint8_t desc [];           // 4-bit descriptor list
/*004*/ }
        lfVTShape, *PlfVTShape, **PPlfVTShape;

#define lfVTShape_ sizeof (lfVTShape)

// -----------------------------------------------------------------

typedef struct _lfEnumerate     // enumeration member
        {
/*000*/ uint16_t         leaf;      // LF_ENUMERATE
/*002*/ CV_fldattr_t attr;
/*004*/ uint8_t         value [];
/*004*/ }
        lfEnumerate, *PlfEnumerate, **PPlfEnumerate;

#define lfEnumerate_ sizeof (lfEnumerate)

// -----------------------------------------------------------------

typedef struct _lfMember        // non-static data member
        {
/*000*/ uint16_t         leaf;      // LF_MEMBER
/*002*/ CV_fldattr_t attr;
/*004*/ uint32_t        index;
/*008*/ uint8_t         offset [];
/*00^8*/ }
        lfMember, *PlfMember, **PPlfMember;

#define lfMember_ sizeof (lfMember)

// -----------------------------------------------------------------

typedef struct _lfBClass        // base class field
        {
/*000*/ uint16_t         leaf;      // LF_BCLASS
/*002*/ CV_fldattr_t attr;
/*004*/ uint32_t        index;
/*008*/ uint8_t         offset [];
/*008*/ }
        lfBClass, *PlfBClass, **PPlfBClass;

#define lfBClass_ sizeof (lfBClass)

// -----------------------------------------------------------------

typedef struct _lfVFuncTab      // virtual function table pointer
        {
/*000*/ uint16_t  leaf;             // LF_VFUNCTAB
/*002*/ uint16_t  pad0;             // padding
/*004*/ uint32_t type;             // VFT pointer type
/*008*/ }
        lfVFuncTab, *PlfVFuncTab, **PPlfVFuncTab;

#define lfVFuncTab_ sizeof (lfVFuncTab)

// -----------------------------------------------------------------

typedef struct _lfOneMethod     // non-overloaded method
        {
/*000*/ uint16_t         leaf;      // LF_ONEMETHOD
/*002*/ CV_fldattr_t attr;
/*004*/ uint32_t        index;
/*008*/ uint32_t        vbaseoff []; // VFT base offset, if present
/*008*/ }
        lfOneMethod, *PlfOneMethod, **PPlfOneMethod;

#define lfOneMethod_ sizeof (lfOneMethod)

// -----------------------------------------------------------------

typedef struct _lfMethod        // overloaded method list
        {
/*000*/ uint16_t  leaf;             // LF_METHOD
/*002*/ uint16_t  count;            // number of occurrences
/*004*/ uint32_t mList;            // LF_METHODLIST descriptor index
/*008*/ uint8_t  Name [];
/*008*/ }
        lfMethod, *PlfMethod, **PPlfMethod;

#define lfMethod_ sizeof (lfMethod)

// -----------------------------------------------------------------

typedef struct _lfNestType      // nested type definition
        {
/*000*/ uint16_t  leaf;             // LF_NESTTYPE
/*002*/ uint16_t  pad0;
/*004*/ uint32_t index;
/*008*/ uint8_t  Name [];
/*008*/ }
        lfNestType, *PlfNestType, **PPlfNestType;

#define lfNestType_ sizeof (lfNestType)

// -----------------------------------------------------------------

typedef union _lfSubRecord
        {
/*000*/ uint16_t        leaf;      // LF_*
/*000*/ lfEnumerate Enumerate; // LF_ENUMERATE
/*000*/ lfMember    Member;    // LF_MEMBER
/*000*/ lfBClass    BClass;    // LF_BCLASS
/*000*/ lfVFuncTab  VFuncTab;  // LF_VFUNCTAB
/*000*/ lfOneMethod OneMethod; // LF_ONEMETHOD
/*000*/ lfMethod    Method;    // LF_METHOD
/*000*/ lfNestType  NestType;  // LF_NESTTYPE
        }
        lfSubRecord, *PlfSubRecord, **PPlfSubRecord;

#define lfSubRecord_ sizeof (lfSubRecord)

// -----------------------------------------------------------------

typedef struct _lfFieldList     // struct/union/enum members
        {
/*000*/ uint16_t        leaf;       // LF_FIELDLIST
/*002*/ lfSubRecord SubRecord;
/*002*/ }
        lfFieldList, *PlfFieldList, **PPlfFieldList;

#define lfFieldList_ sizeof (lfFieldList)

// -----------------------------------------------------------------

typedef union _lfRecord
        {
/*000*/ uint16_t        leaf;      // LF_*
/*000*/ lfArray     Array;     // LF_ARRAY
/*000*/ lfBitfield  Bitfield;  // LF_BITFIELD
/*000*/ lfClass     Class;     // LF_CLASS
/*000*/ lfStructure Structure; // LF_STRUCTURE
/*000*/ lfUnion     Union;     // LF_UNION
/*000*/ lfEnum      Enum;      // LF_ENUM
/*000*/ lfPointer   Pointer;   // LF_POINTER
/*000*/ lfProc      Proc;      // LF_PROCEDURE
/*000*/ lfMFunc     MFunc;     // LF_MFUNCTION
/*000*/ lfArgList   ArgList;   // LF_ARGLIST
/*000*/ lfVTShape   VTShape;   // LF_VTSHAPE
/*000*/ lfFieldList FieldList; // LF_FIELDLIST
        }
        lfRecord, *PlfRecord, **PPlfRecord;

#define lfRecord_ sizeof (lfRecord)

// -----------------------------------------------------------------


// =================================================================
// SYMBOL RECORDS
// =================================================================

// -----------------------------------------------------------------

typedef enum _CV_PUBSYMFLAGS_e
    {
    cvpsfNone     = 0x00000000,
    cvpsfCode     = 0x00000001,
    cvpsfFunction = 0x00000002,
    cvpsfManaged  = 0x00000004,
    cvpsfMSIL     = 0x00000008,
    }
    CV_PUBSYMFLAGS_e, *PCV_PUBSYMFLAGS_e, **PPCV_PUBSYMFLAGS_e;

// -----------------------------------------------------------------

typedef union _CV_GENERIC_FLAG
        {
/*000.0*/ uint16_t cstyle  :  1;
/*000.1*/ uint16_t rsclean :  1;
/*000.2*/ uint16_t unused  : 14;
/*002*/ }
        CV_GENERIC_FLAG, *PCV_GENERIC_FLAG, **PPCV_GENERIC_FLAG;


// -----------------------------------------------------------------

typedef union _CV_PUBSYMFLAGS
        {
/*000*/ uint32_t grfFlags; // CV_PUBSYMFLAGS_e
/*000*/ struct
/*000*/     {
/*000.0*/   uint32_t fCode     :  1;
/*000.1*/   uint32_t fFunction :  1;
/*000.2*/   uint32_t fManaged  :  1;
/*000.3*/   uint32_t fMSIL     :  1;
/*000.4*/   uint32_t reserved  : 28;
/*004*/     };
/*004*/ }
        CV_PUBSYMFLAGS, *PCV_PUBSYMFLAGS, **PPCV_PUBSYMFLAGS;


// -----------------------------------------------------------------

typedef union _CV_PROCFLAGS
        {
/*000*/ uint8_t bAll;
/*000*/ uint8_t grfAll;
/*000*/ struct
/*000*/     {
/*000.0*/   uint8_t CV_PFLAG_NOFPO      : 1;
/*000.1*/   uint8_t CV_PFLAG_INT        : 1;
/*000.2*/   uint8_t CV_PFLAG_FAR        : 1;
/*000.3*/   uint8_t CV_PFLAG_NEVER      : 1;
/*000.4*/   uint8_t CV_PFLAG_NOTREACHED : 1;
/*000.5*/   uint8_t CV_PFLAG_CUST_CALL  : 1;
/*000.6*/   uint8_t CV_PFLAG_NOINLINE   : 1;
/*000.7*/   uint8_t unused              : 1;
/*001*/     };
/*001*/ }
        CV_PROCFLAGS, *PCV_PROCFLAGS, **PPCV_PROCFLAGS;


// -----------------------------------------------------------------

typedef struct _CV_LVARFLAGS
        {
/*000.0*/ uint16_t fIsParam   :  1;
/*000.1*/ uint16_t fAddrTaken :  1;
/*000.2*/ uint16_t fCompGenx  :  1;
/*000.3*/ uint16_t unused     : 13;
/*002*/ }
        CV_LVARFLAGS, *PCV_LVARFLAGS, **PPCV_LVARFLAGS;


// -----------------------------------------------------------------

typedef struct _CV_lvar_attr
        {
/*000*/ uint32_t        off;
/*004*/ uint16_t         seg;
/*006*/ CV_LVARFLAGS flags;
/*008*/ }
        CV_lvar_attr, *PCV_lvar_attr, **PPCV_lvar_attr;


// -----------------------------------------------------------------

typedef struct _ALIGNSYM
        {
/*000*/ uint16_t reclen; // record length
/*002*/ uint16_t rectyp; // record type
/*004*/ }
        ALIGNSYM, *PALIGNSYM, **PPALIGNSYM;


// -----------------------------------------------------------------

typedef struct _ANNOTATIONSYM
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t off;
/*008*/ uint16_t  seg;
/*00A*/ uint16_t  csz;
/*00C*/ uint8_t  rgsz [1];
/*00D*/ }
        ANNOTATIONSYM, *PANNOTATIONSYM, **PPANNOTATIONSYM;


// -----------------------------------------------------------------

typedef struct _ATTRMANYREGSYM
        {
/*000*/ uint16_t         reclen;   // record length
/*002*/ uint16_t         rectyp;   // record type
/*004*/ uint32_t        typind;
/*008*/ CV_lvar_attr attr;
/*010*/ uint8_t         count;
/*011*/ uint8_t         reg [1];
/*012*/ }
        ATTRMANYREGSYM, *PATTRMANYREGSYM, **PPATTRMANYREGSYM;


// -----------------------------------------------------------------

typedef struct _ATTRMANYREGSYM2
        {
/*000*/ uint16_t         reclen;   // record length
/*002*/ uint16_t         rectyp;   // record type
/*004*/ uint32_t        typind;
/*008*/ CV_lvar_attr attr;
/*010*/ uint16_t         count;
/*012*/ uint16_t         reg [1];
/*014*/ }
        ATTRMANYREGSYM2, *PATTRMANYREGSYM2, **PPATTRMANYREGSYM2;


// -----------------------------------------------------------------

typedef struct _ATTRREGREL
        {
/*000*/ uint16_t         reclen;   // record length
/*002*/ uint16_t         rectyp;   // record type
/*004*/ uint32_t        off;
/*008*/ uint32_t        typind;
/*00C*/ uint16_t         reg;
/*00E*/ CV_lvar_attr attr;
/*016*/ uint8_t         name [1];
/*017*/ }
        ATTRREGREL, *PATTRREGREL, **PPATTRREGREL;


// -----------------------------------------------------------------

typedef struct _ATTRREGSYM
        {
/*000*/ uint16_t         reclen;   // record length
/*002*/ uint16_t         rectyp;   // record type
/*004*/ uint32_t        typind;
/*008*/ CV_lvar_attr attr;
/*010*/ uint16_t         reg;
/*012*/ uint8_t         name [1];
/*013*/ }
        ATTRREGSYM, *PATTRREGSYM, **PPATTRREGSYM;

#define ATTRREGSYM_ sizeof (ATTRREGSYM)

// -----------------------------------------------------------------

typedef struct _ATTRSLOTSYM
        {
/*000*/ uint16_t         reclen;   // record length
/*002*/ uint16_t         rectyp;   // record type
/*004*/ uint32_t        iSlot;
/*008*/ uint32_t        typind;
/*00C*/ CV_lvar_attr attr;
/*014*/ uint8_t         name [1];
/*015*/ }
        ATTRSLOTSYM, *PATTRSLOTSYM, **PPATTRSLOTSYM;

#define ATTRSLOTSYM_ sizeof (ATTRSLOTSYM)

// -----------------------------------------------------------------

typedef struct _BLOCKSYM
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t pParent;
/*008*/ uint32_t pEnd;
/*00C*/ }
        BLOCKSYM, *PBLOCKSYM, **PPBLOCKSYM;

#define BLOCKSYM_ sizeof (BLOCKSYM)

// -----------------------------------------------------------------

typedef struct _BLOCKSYM16
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t pParent;
/*008*/ uint32_t pEnd;
/*00C*/ uint16_t  len;
/*00E*/ uint16_t  off;
/*010*/ uint16_t  seg;
/*012*/ uint8_t  name [1];
/*013*/ }
        BLOCKSYM16, *PBLOCKSYM16, **PPBLOCKSYM16;

#define BLOCKSYM16_ sizeof (BLOCKSYM16)

// -----------------------------------------------------------------

typedef struct _BLOCKSYM32
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t pParent;
/*008*/ uint32_t pEnd;
/*00C*/ uint32_t len;
/*010*/ uint32_t off;
/*014*/ uint16_t  seg;
/*016*/ uint8_t  name [1];
/*017*/ }
        BLOCKSYM32, *PBLOCKSYM32, **PPBLOCKSYM32;

#define BLOCKSYM32_ sizeof (BLOCKSYM32)

// -----------------------------------------------------------------

typedef struct _BPRELSYM16
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint16_t off;
/*006*/ uint16_t  typind;
/*008*/ uint8_t  name [1];
/*009*/ }
        BPRELSYM16, *PBPRELSYM16, **PPBPRELSYM16;

#define BPRELSYM16_ sizeof (BPRELSYM16)

// -----------------------------------------------------------------

typedef struct _BPRELSYM32
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ int32_t  off;
/*008*/ uint32_t typind;
/*00C*/ uint8_t  name [1];
/*00D*/ }
        BPRELSYM32, *PBPRELSYM32, **PPBPRELSYM32;

#define BPRELSYM32_ sizeof (BPRELSYM32)

// -----------------------------------------------------------------

typedef struct _BPRELSYM32_16t
        {
/*000*/ uint16_t reclen;   // record length
/*002*/ uint16_t rectyp;   // record type
/*004*/ int32_t off;
/*008*/ uint16_t typind;
/*00A*/ uint8_t name [1];
/*00B*/ }
        BPRELSYM32_16t, *PBPRELSYM32_16t, **PPBPRELSYM32_16t;

#define BPRELSYM32_16t_ sizeof (BPRELSYM32_16t)

// -----------------------------------------------------------------

typedef struct _CEXMSYM16
        {
/*000*/ uint16_t reclen;   // record length
/*002*/ uint16_t rectyp;   // record type
/*004*/ uint16_t off;
/*006*/ uint16_t seg;
/*008*/ uint16_t model;
/*00A*/ union
/*00A*/     {
/*00A*/     struct
/*00A*/         {
/*00A*/         uint16_t pcdtable;
/*00C*/         uint16_t pcdspi;
/*00E*/         } pcode;
/*00A*/     struct
/*00A*/         {
/*00A*/         uint16_t  subtype;
/*00C*/         uint16_t  flag;
/*00E*/         } cobol;
/*00E*/     };
/*00E*/ }
        CEXMSYM16, *PCEXMSYM16, **PPCEXMSYM16;

#define CEXMSYM16_ sizeof (CEXMSYM16)

// -----------------------------------------------------------------

typedef struct _CEXMSYM32
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t off;
/*008*/ uint16_t  seg;
/*00A*/ uint16_t  model;
/*00C*/ union
/*00C*/     {
/*00C*/     struct
/*00C*/         {
/*00C*/         uint32_t pcdtable;
/*010*/         uint32_t pcdspi;
/*014*/         } pcode;
/*00C*/     struct
/*00C*/         {
/*00C*/         uint16_t  subtype;
/*00E*/         uint16_t  flag;
/*010*/         } cobol;
/*00C*/     struct
/*00C*/         {
/*00C*/         uint32_t calltableOff;
/*010*/         uint16_t  calltableSeg;
/*012*/         } pcode32Mac;
/*014*/     };
/*014*/ }
        CEXMSYM32, *PCEXMSYM32, **PPCEXMSYM32;

#define CEXMSYM32_ sizeof (CEXMSYM32)

// -----------------------------------------------------------------

typedef struct _CFLAGSYM
        {
/*000*/ uint16_t reclen;  // record length
/*002*/ uint16_t rectyp;  // record type
/*004*/ uint8_t machine;
        struct
            {
/*005.0*/   uint8_t language  : 8;
/*006.0*/   uint8_t pcode     : 1;
/*006.1*/   uint8_t floatprec : 2;
/*006.3*/   uint8_t floatpkg  : 2;
/*006.5*/   uint8_t ambdata   : 3;
/*007.0*/   uint8_t ambcode   : 3;
/*007.3*/   uint8_t mode32    : 1;
/*007.4*/   uint8_t pad       : 4;
            } flags;
/*008*/ uint8_t ver [];
/*009*/ }
        CFLAGSYM, *PCFLAGSYM, **PPCFLAGSYM;

#define CFLAGSYM_ sizeof (CFLAGSYM)

// -----------------------------------------------------------------

typedef struct _COMPILESYM
        {
/*000*/ uint16_t reclen;   // record length
/*002*/ uint16_t rectyp;   // record type
/*004*/ struct
/*004*/     {
/*004.0*/   uint32_t iLanguage       :  8;
/*004.0*/   uint32_t fEC             :  1;
/*004.0*/   uint32_t fNoDbgInfo      :  1;
/*004.0*/   uint32_t fLTCG           :  1;
/*004.0*/   uint32_t fNoDataAlign    :  1;
/*004.0*/   uint32_t fManagedPresent :  1;
/*004.0*/   uint32_t pad             : 19;
            } flags;
/*008*/ uint16_t machine;
/*00A*/ uint16_t verFEMajor;
/*00C*/ uint16_t verFEMinor;
/*00E*/ uint16_t verFEBuild;
/*010*/ uint16_t verMajor;
/*012*/ uint16_t verMinor;
/*014*/ uint16_t verBuild;
/*016*/ uint8_t verSt [1];
/*017*/ }
        COMPILESYM, *PCOMPILESYM, **PPCOMPILESYM;

#define COMPILESYM_ sizeof (COMPILESYM)

// -----------------------------------------------------------------

typedef struct _CONSTSYM
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t typind;
/*008*/ uint16_t  value;
/*00A*/ uint8_t  name [];
/*00A*/ }
        CONSTSYM, *PCONSTSYM, **PPCONSTSYM;

#define CONSTSYM_ sizeof (CONSTSYM)

// -----------------------------------------------------------------

typedef struct _CONSTSYM_16t
        {
/*000*/ uint16_t reclen;   // record length
/*002*/ uint16_t rectyp;   // record type
/*004*/ uint16_t typind;
/*006*/ uint16_t value;
/*008*/ uint8_t name [];
/*008*/ }
        CONSTSYM_16t, *PCONSTSYM_16t, **PPCONSTSYM_16t;

#define CONSTSYM_16t_ sizeof (CONSTSYM_16t)

// -----------------------------------------------------------------

typedef struct _DATASYM16
        {
/*000*/ uint16_t reclen;   // record length
/*002*/ uint16_t rectyp;   // record type
/*004*/ uint16_t off;
/*006*/ uint16_t seg;
/*008*/ uint16_t typind;
/*00A*/ uint8_t name [1];
/*00B*/ }
        DATASYM16, *PDATASYM16, **PPDATASYM16;

#define DATASYM16_ sizeof (DATASYM16)

// -----------------------------------------------------------------

typedef struct _DATASYM32
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t typind;
/*008*/ uint32_t off;
/*00C*/ uint16_t  seg;
/*00E*/ uint8_t  name [1];
/*00F*/ }
        DATASYM32, *PDATASYM32, **PPDATASYM32;

#define DATASYM32_ sizeof (DATASYM32)

// -----------------------------------------------------------------

typedef struct _ENTRYTHISSYM
        {
/*000*/ uint16_t reclen;  // record length
/*002*/ uint16_t rectyp;  // record type
/*004*/ uint8_t thissym;
/*005*/ }
        ENTRYTHISSYM, *PENTRYTHISSYM, **PPENTRYTHISSYM;

#define ENTRYTHISSYM_ sizeof (ENTRYTHISSYM)

// -----------------------------------------------------------------

typedef struct _FRAMEPROCSYM
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t cbFrame;
/*008*/ uint32_t cbPad;
/*00C*/ uint32_t offPad;
/*010*/ uint32_t cbSaveRegs;
/*014*/ uint32_t offExHdlr;
/*018*/ uint16_t  sectExHdlr;
        struct
            {
/*01A.0*/   uint32_t fHasAlloca  :  1;
/*01A.1*/   uint32_t fHasSetJmp  :  1;
/*01A.2*/   uint32_t fHasLongJmp :  1;
/*01A.3*/   uint32_t fHasInlAsm  :  1;
/*01A.4*/   uint32_t fHasEH      :  1;
/*01A.5*/   uint32_t fInlSpec    :  1;
/*01A.6*/   uint32_t fHasSEH     :  1;
/*01A.7*/   uint32_t pad         : 25;
            };
/*01E*/ }
        FRAMEPROCSYM, *PFRAMEPROCSYM, **PPFRAMEPROCSYM;

#define FRAMEPROCSYM_ sizeof (FRAMEPROCSYM)

// -----------------------------------------------------------------

typedef struct _FRAMERELSYM
        {
/*000*/ uint16_t         reclen;   // record length
/*002*/ uint16_t         rectyp;   // record type
/*004*/ int32_t         off;
/*008*/ uint32_t        typind;
/*00C*/ CV_lvar_attr attr;
/*014*/ uint8_t         name [1];
/*015*/ }
        FRAMERELSYM, *PFRAMERELSYM, **PPFRAMERELSYM;

#define FRAMERELSYM_ sizeof (FRAMERELSYM)

// -----------------------------------------------------------------

typedef struct _LABELSYM16
        {
/*000*/ uint16_t         reclen;   // record length
/*002*/ uint16_t         rectyp;   // record type
/*004*/ uint16_t         off;
/*006*/ uint16_t         seg;
/*008*/ CV_PROCFLAGS flags;
/*009*/ uint8_t         name [1];
/*00A*/ }
        LABELSYM16, *PLABELSYM16, **PPLABELSYM16;

#define LABELSYM16_ sizeof (LABELSYM16)

// -----------------------------------------------------------------

typedef struct _LABELSYM32
        {
/*000*/ uint16_t         reclen;   // record length
/*002*/ uint16_t         rectyp;   // record type
/*004*/ uint32_t        off;
/*008*/ uint16_t         seg;
/*00A*/ CV_PROCFLAGS flags;
/*00B*/ uint8_t         name [1];
/*00C*/ }
        LABELSYM32, *PLABELSYM32, **PPLABELSYM32;

#define LABELSYM32_ sizeof (LABELSYM32)

// -----------------------------------------------------------------

typedef struct _MANPROCSYM
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t pParent;
/*008*/ uint32_t pEnd;
/*00C*/ uint32_t pNext;
/*010*/ uint32_t len;
/*014*/ uint32_t DbgStart;
/*018*/ uint32_t DbgEnd;
/*01C*/ uint32_t token;
/*020*/ uint32_t off;
/*024*/ uint16_t  seg;
/*026*/ CV_PROCFLAGS flags;
/*027*/ uint16_t  retReg;
/*029*/ uint8_t  name [1];
/*02A*/ }
        MANPROCSYM, *PMANPROCSYM, **PPMANPROCSYM;

#define MANPROCSYM_ sizeof (MANPROCSYM)

// -----------------------------------------------------------------

typedef struct _MANPROCSYMMIPS
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t pParent;
/*008*/ uint32_t pEnd;
/*00C*/ uint32_t pNext;
/*010*/ uint32_t len;
/*014*/ uint32_t DbgStart;
/*018*/ uint32_t DbgEnd;
/*01C*/ uint32_t regSave;
/*020*/ uint32_t fpSave;
/*024*/ uint32_t intOff;
/*028*/ uint32_t fpOff;
/*02C*/ uint32_t token;
/*030*/ uint32_t off;
/*034*/ uint16_t  seg;
/*036*/ uint8_t  retReg;
/*037*/ uint8_t  frameReg;
/*038*/ uint8_t  name [1];
/*039*/ }
        MANPROCSYMMIPS, *PMANPROCSYMMIPS, **PPMANPROCSYMMIPS;

#define MANPROCSYMMIPS_ sizeof (MANPROCSYMMIPS)

// -----------------------------------------------------------------

typedef struct _MANTYPREF
        {
/*000*/ uint16_t  reclen; // record length
/*002*/ uint16_t  rectyp; // record type
/*004*/ uint32_t typind;
/*008*/ }
        MANTYPREF, *PMANTYPREF, **PPMANTYPREF;

#define MANTYPREF_ sizeof (MANTYPREF)

// -----------------------------------------------------------------

typedef struct _MANYREGSYM_16t
        {
/*000*/ uint16_t reclen;  // record length
/*002*/ uint16_t rectyp;  // record type
/*004*/ uint16_t typind;
/*006*/ uint8_t count;
/*007*/ uint8_t reg [1];
/*008*/ }
        MANYREGSYM_16t, *PMANYREGSYM_16t, **PPMANYREGSYM_16t;

#define MANYREGSYM_16t_ sizeof (MANYREGSYM_16t)

// -----------------------------------------------------------------

typedef struct _MANYREGSYM
        {
/*000*/ uint16_t  reclen;  // record length
/*002*/ uint16_t  rectyp;  // record type
/*004*/ uint32_t typind;
/*008*/ uint8_t  count;
/*009*/ uint8_t  reg [1];
/*00A*/ }
        MANYREGSYM, *PMANYREGSYM, **PPMANYREGSYM;

#define MANYREGSYM_ sizeof (MANYREGSYM)

// -----------------------------------------------------------------

typedef struct _MANYREGSYM2
        {
/*000*/ uint16_t  reclen;  // record length
/*002*/ uint16_t  rectyp;  // record type
/*004*/ uint32_t typind;
/*008*/ uint16_t  count;
/*00A*/ uint16_t  reg [1];
/*00C*/ }
        MANYREGSYM2, *PMANYREGSYM2, **PPMANYREGSYM2;

#define MANYREGSYM2_ sizeof (MANYREGSYM2)

// -----------------------------------------------------------------

typedef struct _OBJNAMESYM
        {
/*000*/ uint16_t  reclen;    // record length
/*002*/ uint16_t  rectyp;    // record type
/*004*/ uint32_t signature;
/*008*/ uint8_t  name [1];
/*009*/ }
        OBJNAMESYM, *POBJNAMESYM, **PPOBJNAMESYM;

#define OBJNAMESYM_ sizeof (OBJNAMESYM)

// -----------------------------------------------------------------

typedef struct _OEMSYMBOL
        {
/*000*/ uint16_t  reclen;     // record length
/*002*/ uint16_t  rectyp;     // record type
/*004*/ uint8_t  idOem [16];
/*014*/ uint32_t typind;
/*018*/ uint32_t rgl [];
/*018*/ }
        OEMSYMBOL, *POEMSYMBOL, **PPOEMSYMBOL;

#define OEMSYMBOL_ sizeof (OEMSYMBOL)

// -----------------------------------------------------------------

typedef struct _PROCSYM16
        {
/*000*/ uint16_t         reclen;   // record length
/*002*/ uint16_t         rectyp;   // record type
/*004*/ uint32_t        pParent;
/*008*/ uint32_t        pEnd;
/*00C*/ uint32_t        pNext;
/*010*/ uint16_t         len;
/*012*/ uint16_t         DbgStart;
/*014*/ uint16_t         DbgEnd;
/*016*/ uint16_t         off;
/*018*/ uint16_t         seg;
/*01A*/ uint16_t         typind;
/*01C*/ CV_PROCFLAGS flags;
/*01D*/ uint8_t         name [1];
/*01E*/ }
        PROCSYM16, *PPROCSYM16, **PPPROCSYM16;

#define PROCSYM16_ sizeof (PROCSYM16)

// -----------------------------------------------------------------

typedef struct _PROCSYM32
        {
/*000*/ uint16_t         reclen;   // record length
/*002*/ uint16_t         rectyp;   // record type
/*004*/ uint32_t        pParent;
/*008*/ uint32_t        pEnd;
/*00C*/ uint32_t        pNext;
/*010*/ uint32_t        len;
/*014*/ uint32_t        DbgStart;
/*018*/ uint32_t        DbgEnd;
/*01C*/ uint32_t        typind;
/*020*/ uint32_t        off;
/*024*/ uint16_t         seg;
/*026*/ CV_PROCFLAGS flags;
/*027*/ uint8_t         name [1];
/*028*/ }
        PROCSYM32, *PPROCSYM32, **PPPROCSYM32;

#define PROCSYM32_ sizeof (PROCSYM32)

// -----------------------------------------------------------------

typedef struct _PROCSYM32_16t
        {
/*000*/ uint16_t         reclen;   // record length
/*002*/ uint16_t         rectyp;   // record type
/*004*/ uint32_t        pParent;
/*008*/ uint32_t        pEnd;
/*00C*/ uint32_t        pNext;
/*010*/ uint32_t        len;
/*014*/ uint32_t        DbgStart;
/*018*/ uint32_t        DbgEnd;
/*01C*/ uint32_t        off;
/*020*/ uint16_t         seg;
/*022*/ uint16_t         typind;
/*024*/ CV_PROCFLAGS flags;
/*025*/ uint8_t         name [1];
/*026*/ }
        PROCSYM32_16t, *PPROCSYM32_16t, **PPPROCSYM32_16t;

#define PROCSYM32_16t_ sizeof (PROCSYM32_16t)

// -----------------------------------------------------------------

typedef struct _PROCSYMIA64
        {
/*000*/ uint16_t         reclen;   // record length
/*002*/ uint16_t         rectyp;   // record type
/*004*/ uint32_t        pParent;
/*008*/ uint32_t        pEnd;
/*00C*/ uint32_t        pNext;
/*010*/ uint32_t        len;
/*014*/ uint32_t        DbgStart;
/*018*/ uint32_t        DbgEnd;
/*01C*/ uint32_t        typind;
/*020*/ uint32_t        off;
/*024*/ uint16_t         seg;
/*026*/ uint16_t         retReg;
/*028*/ CV_PROCFLAGS flags;
/*029*/ uint8_t         name [1];
/*02A*/ }
        PROCSYMIA64, *PPROCSYMIA64, **PPPROCSYMIA64;

#define PROCSYMIA64_ sizeof (PROCSYMIA64)

// -----------------------------------------------------------------

typedef struct _PROCSYMMIPS
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t pParent;
/*008*/ uint32_t pEnd;
/*00C*/ uint32_t pNext;
/*010*/ uint32_t len;
/*014*/ uint32_t DbgStart;
/*018*/ uint32_t DbgEnd;
/*01C*/ uint32_t regSave;
/*020*/ uint32_t fpSave;
/*024*/ uint32_t intOff;
/*028*/ uint32_t fpOff;
/*02C*/ uint32_t typinf;
/*030*/ uint32_t off;
/*034*/ uint16_t  seg;
/*036*/ uint8_t  retReg;
/*037*/ uint8_t  frameReg;
/*038*/ uint8_t  name [1];
/*039*/ }
        PROCSYMMIPS, *PPROCSYMMIPS, **PPPROCSYMMIPS;

#define PROCSYMMIPS_ sizeof (PROCSYMMIPS)

// -----------------------------------------------------------------

typedef struct _PROCSYMMIPS_16t
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t pParent;
/*008*/ uint32_t pEnd;
/*00C*/ uint32_t pNext;
/*010*/ uint32_t len;
/*014*/ uint32_t DbgStart;
/*018*/ uint32_t DbgEnd;
/*01C*/ uint32_t regSave;
/*020*/ uint32_t fpSave;
/*024*/ uint32_t intOff;
/*028*/ uint32_t fpOff;
/*02C*/ uint32_t off;
/*030*/ uint16_t  seg;
/*032*/ uint16_t  typind;
/*034*/ uint8_t  retReg;
/*035*/ uint8_t  frameReg;
/*036*/ uint8_t  name [1];
/*037*/ }
        PROCSYMMIPS_16t, *PPROCSYMMIPS_16t, **PPPROCSYMMIPS_16t;

#define PROCSYMMIPS_16t_ sizeof (PROCSYMMIPS_16t)

// -----------------------------------------------------------------

typedef struct _PUBSYM32
        {
/*000*/ uint16_t           reclen;      // record length
/*002*/ uint16_t           rectyp;      // record type
/*004*/ CV_PUBSYMFLAGS pubsymflags;
/*008*/ uint32_t          off;
/*00C*/ uint16_t           seg;
/*00E*/ uint8_t           name [1];
/*00F*/ }
        PUBSYM32, *PPUBSYM32, **PPPUBSYM32;

#define PUBSYM32_ sizeof (PUBSYM32)

// -----------------------------------------------------------------

typedef struct _REFSYM
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t sumName;
/*008*/ uint32_t ibSym;
/*00C*/ uint16_t  imod;
/*00E*/ uint16_t  usFill;
/*010*/ }
        REFSYM, *PREFSYM, **PPREFSYM;

#define REFSYM_ sizeof (REFSYM)

// -----------------------------------------------------------------

typedef struct _REFSYM2
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t sumName;
/*008*/ uint32_t ibSym;
/*00C*/ uint16_t  imod;
/*00E*/ uint8_t  name [1];
/*00F*/ }
        REFSYM2, *PREFSYM2, **PPREFSYM2;

#define REFSYM2_ sizeof (REFSYM2)

// -----------------------------------------------------------------

typedef struct _REGREL16
        {
/*000*/ uint16_t reclen;   // record length
/*002*/ uint16_t rectyp;   // record type
/*004*/ uint16_t off;
/*006*/ uint16_t reg;
/*008*/ uint16_t typind;
/*00A*/ uint8_t name [1];
/*00B*/ }
        REGREL16, *PREGREL16, **PPREGREL16;

#define REGREL16_ sizeof (REGREL16)

// -----------------------------------------------------------------

typedef struct _REGREL32_16t
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t off;
/*008*/ uint16_t  reg;
/*00A*/ uint16_t  typind;
/*00C*/ uint8_t  name [1];
/*00D*/ }
        REGREL32_16t, *PREGREL32_16t, **PPREGREL32_16t;

#define REGREL32_16t_ sizeof (REGREL32_16t)

// -----------------------------------------------------------------

typedef struct _REGREL32
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t off;
/*008*/ uint32_t typind;
/*00C*/ uint16_t  reg;
/*00E*/ uint8_t  name [1];
/*00F*/ }
        REGREL32, *PREGREL32, **PPREGREL32;

#define REGREL32_ sizeof (REGREL32)

// -----------------------------------------------------------------

typedef struct _REGSYM
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t typind;
/*008*/ uint16_t  reg;
/*00A*/ uint8_t  name [1];
/*00B*/ }
        REGSYM, *PREGSYM, **PPREGSYM;

#define REGSYM_ sizeof (REGSYM)

// -----------------------------------------------------------------

typedef struct _REGSYM_16t
        {
/*000*/ uint16_t reclen; // record length
/*002*/ uint16_t rectyp; // record type
/*004*/ uint16_t typind;
/*006*/ uint16_t reg;
/*008*/ uint8_t name [1];
/*009*/ }
        REGSYM_16t, *PREGSYM_16t, **PPREGSYM_16t;

#define REGSYM_16t_ sizeof (REGSYM_16t)

// -----------------------------------------------------------------

typedef struct _RETURNSYM
        {
/*000*/ uint16_t            reclen;   // record length
/*002*/ uint16_t            rectyp;   // record type
/*004*/ CV_GENERIC_FLAG flags;
/*006*/ uint8_t            style;
/*007*/ }
        RETURNSYM, *PRETURNSYM, **PPRETURNSYM;

#define RETURNSYM_ sizeof (RETURNSYM)

// -----------------------------------------------------------------

typedef struct _SEARCHSYM
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t startsym;
/*008*/ uint16_t  seg;
/*00A*/ }
        SEARCHSYM, *PSEARCHSYM, **PPSEARCHSYM;

#define SEARCHSYM_ sizeof (SEARCHSYM)

// -----------------------------------------------------------------

typedef struct _SLINK32
        {
/*000*/ uint16_t  reclen;    // record length
/*002*/ uint16_t  rectyp;    // record type
/*004*/ uint32_t framesize;
/*008*/ int32_t  off;
/*00C*/ uint16_t  reg;
/*00E*/ }
        SLINK32, *PSLINK32, **PPSLINK32;

#define SLINK32_ sizeof (SLINK32)

// -----------------------------------------------------------------

typedef struct _SLOTSYM32
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t iSlot;
/*008*/ uint32_t typind;
/*00C*/ uint8_t  name [1];
/*00D*/ }
        SLOTSYM32, *PSLOTSYM32, **PPSLOTSYM32;

#define SLOTSYM32_ sizeof (SLOTSYM32)

// -----------------------------------------------------------------

typedef struct _SYMTYPE
        {
/*000*/ uint16_t reclen;   // record length
/*002*/ uint16_t rectyp;   // record type
/*004*/ uint8_t data [];
/*004*/ }
        SYMTYPE, *PSYMTYPE, **PPSYMTYPE;

#define SYMTYPE_ sizeof (SYMTYPE)

// -----------------------------------------------------------------

typedef struct _THREADSYM32_16t
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t off;
/*008*/ uint16_t  seg;
/*00A*/ uint16_t  typind;
/*00C*/ uint8_t  name [1];
/*00D*/ }
        THREADSYM32_16t, *PTHREADSYM32_16t, **PPTHREADSYM32_16t;

#define THREADSYM32_16t_ sizeof (THREADSYM32_16t)

// -----------------------------------------------------------------

typedef struct _THUNKSYM
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t pParent;
/*008*/ uint32_t pEnd;
/*00C*/ uint32_t pNext;
/*010*/ }
        THUNKSYM, *PTHUNKSYM, **PPTHUNKSYM;

#define THUNKSYM_ sizeof (THUNKSYM)

// -----------------------------------------------------------------

typedef struct _THUNKSYM16
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t pParent;
/*008*/ uint32_t pEnd;
/*00C*/ uint32_t pNext;
/*010*/ uint16_t  off;
/*012*/ uint16_t  seg;
/*014*/ uint16_t  len;
/*016*/ uint8_t  ord;
/*017*/ uint8_t  name    [1];
/*018*/ uint8_t  variant [ ];
/*018*/ }
        THUNKSYM16, *PTHUNKSYM16, **PPTHUNKSYM16;

#define THUNKSYM16_ sizeof (THUNKSYM16)

// -----------------------------------------------------------------

typedef struct _THUNKSYM32
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t pParent;
/*008*/ uint32_t pEnd;
/*00C*/ uint32_t pNext;
/*010*/ uint32_t off;
/*014*/ uint16_t  seg;
/*016*/ uint16_t  len;
/*018*/ uint8_t  ord;
/*019*/ uint8_t  name    [1];
/*01A*/ uint8_t  variant [ ];
/*01A*/ }
        THUNKSYM32, *PTHUNKSYM32, **PPTHUNKSYM32;

#define THUNKSYM32_ sizeof (THUNKSYM32)

// -----------------------------------------------------------------

typedef struct _TRAMPOLINESYM
        {
/*000*/ uint16_t  reclen;    // record length
/*002*/ uint16_t  rectyp;    // record type
/*004*/ uint16_t  trampType;
/*006*/ uint16_t  cbThunk;
/*008*/ uint32_t offThunk;
/*00C*/ uint32_t offTarget;
/*010*/ uint16_t  sectThunk;
/*012*/ uint16_t  sectTarget;
/*014*/ }
        TRAMPOLINESYM, *PTRAMPOLINESYM, **PPTRAMPOLINESYM;

#define TRAMPOLINESYM_ sizeof (TRAMPOLINESYM)

// -----------------------------------------------------------------

typedef struct _UDTSYM
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t typind;
/*008*/ uint8_t  name [1];
/*009*/ }
        UDTSYM, *PUDTSYM, **PPUDTSYM;

#define UDTSYM_ sizeof (UDTSYM)

// -----------------------------------------------------------------

typedef struct _UDTSYM_16t
        {
/*000*/ uint16_t reclen;   // record length
/*002*/ uint16_t rectyp;   // record type
/*004*/ uint16_t typind;
/*006*/ uint8_t name [1];
/*007*/ }
        UDTSYM_16t, *PUDTSYM_16t, **PPUDTSYM_16t;

#define UDTSYM_16t_ sizeof (UDTSYM_16t)

// -----------------------------------------------------------------

typedef struct _UNAMESPACE
        {
/*000*/ uint16_t reclen;   // record length
/*002*/ uint16_t rectyp;   // record type
/*004*/ uint8_t name [1];
/*005*/ }
        UNAMESPACE, *PUNAMESPACE, **PPUNAMESPACE;

#define UNAMESPACE_ sizeof (UNAMESPACE)

// -----------------------------------------------------------------

typedef struct _VPATHSYM16
        {
/*000*/ uint16_t reclen; // record length
/*002*/ uint16_t rectyp; // record type
/*004*/ uint16_t off;
/*006*/ uint16_t seg;
/*008*/ uint16_t root;
/*00A*/ uint16_t path;
/*00C*/ }
        VPATHSYM16, *PVPATHSYM16, **PPVPATHSYM16;

#define VPATHSYM16_ sizeof (VPATHSYM16)

// -----------------------------------------------------------------

typedef struct _VPATHSYM32
        {
/*000*/ uint16_t  reclen; // record length
/*002*/ uint16_t  rectyp; // record type
/*004*/ uint32_t root;
/*008*/ uint32_t path;
/*00C*/ uint32_t off;
/*010*/ uint16_t  seg;
/*012*/ }
        VPATHSYM32, *PVPATHSYM32, **PPVPATHSYM32;

#define VPATHSYM32_ sizeof (VPATHSYM32)

// -----------------------------------------------------------------

typedef struct _VPATHSYM32_16t
        {
/*000*/ uint16_t  reclen;    // record length
/*002*/ uint16_t  rectyp;    // record type
/*004*/ uint32_t off;
/*008*/ uint16_t  seg;
/*00A*/ uint16_t  root;
/*00C*/ uint16_t  path;
/*00E*/ }
        VPATHSYM32_16t, *PVPATHSYM32_16t, **PPVPATHSYM32_16t;

#define VPATHSYM32_16t_ sizeof (VPATHSYM32_16t)

// -----------------------------------------------------------------

typedef struct _WITHSYM16
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t pParent;
/*008*/ uint32_t pEnd;
/*00C*/ uint16_t  len;
/*00E*/ uint16_t  off;
/*010*/ uint16_t  seg;
/*012*/ uint8_t  expr [1];
/*013*/ }
        WITHSYM16, *PWITHSYM16, **PPWITHSYM16;

#define WITHSYM16_ sizeof (WITHSYM16)

// -----------------------------------------------------------------

typedef struct _WITHSYM32
        {
/*000*/ uint16_t  reclen;   // record length
/*002*/ uint16_t  rectyp;   // record type
/*004*/ uint32_t pParent;
/*008*/ uint32_t pEnd;
/*00C*/ uint32_t len;
/*010*/ uint32_t off;
/*014*/ uint16_t  seg;
/*016*/ uint8_t  expr [1];
/*017*/ }
        WITHSYM32, *PWITHSYM32, **PPWITHSYM32;

#define WITHSYM32_ sizeof (WITHSYM32)

// -----------------------------------------------------------------

typedef struct _OMAP_DATA
        {
/*000*/ uint32_t rva;   // relative virtual address
/*004*/ uint32_t rvaTo; // converted relative virtual address
/*008*/ }
        OMAP_DATA, *POMAP_DATA, **PPOMAP_DATA;

#define OMAP_DATA_ sizeof (OMAP_DATA)

// -----------------------------------------------------------------

#pragma pack ()

// =================================================================
// END OF FILE
// =================================================================
