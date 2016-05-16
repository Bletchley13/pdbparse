#ifndef __PDB_H__
#define __PDB_H__


// PDB Stream IDs
#define PDB_STREAM_ROOT   0
#define PDB_STREAM_PDB    1
#define PDB_STREAM_TPI    2
#define PDB_STREAM_DBI    3
#define PDB_STREAM_FPO    5


typedef struct _PDBStream
{
/*000*/ uint32_t impv;
/*004*/ uint32_t sig;
/*008*/ uint32_t age;
/*00C*/ 
} PDBStream, *PPDBStream, **PPPDBStream;


typedef struct _PDBStream70
{
/*000*/ PDBStream pdbstream;
/*00C*/ //GUID      sig70;
/*01C*/ 
} PDBStream70, *PPDBStream70, **PPPDBStream70;

typedef struct _GSIHashHdr
{
/*000*/ uint32_t verSignature;
/*004*/ uint32_t verHdr;
/*008*/ int32_t  cbHr;
/*00C*/ int32_t  cbBuckets;
/*010*/ 
} GSIHashHdr, *PGSIHashHdr, **PPGSIHashHdr;

//extend MSF_STREAM_REF
typedef struct MSF_STREAM_REF_PDBStream70
{
        PDBStream70* Data;
        size_t Size;
} MSF_STREAM_REF_PDBStream70;

typedef struct MSF_STREAM_REF_GSIHashHdr
{
        GSIHashHdr *Data;
        size_t Size;
} MSF_STREAM_REF_GSIHashHdr;

// end of MSF_STREAM_REF
typedef struct _PDB
{
        char* szPdbFileName;
        PMSF msf;  // MSF handle for loaded multi-stream file
        //MSF_STREAM_REF<PDBStream70> pdb;
        MSF_STREAM_REF_PDBStream70 pdb;
        //MSF_STREAM_REF<NewDBIHdr> dbi;
        MSF_STREAM_REF_NewDBIHdr dbi;
        PSYMD Symd;
} PDB, *PPDB;

#endif


