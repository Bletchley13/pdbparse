#include <stdio.h>
#include "msf.h"
#include "gsi.h"


//
// Load symbols for the MSF
//
// Return Value: symbol descriptor (SYMD) for the supplied PDB
//
PSYMD SYMLoadSymbols (MSF* msf)
{
        PSYMD Symd = (PSYMD) calloc (sizeof(SYMD), 1);

        if (Symd != NULL)
        {
                Symd->msf = msf;
                Symd->dbi = (PNewDBIHdr) MsfReferenceStream (msf, PDB_STREAM_DBI, &Symd->DbiSize);
                if (Symd->dbi != NULL && Symd->DbiSize >= sizeof(NewDBIHdr))
                {
                        Symd->SymRecs = (PSYM) MsfReferenceStream (msf, Symd->dbi->snSymRecs, &Symd->SymSize);
                        if (Symd->SymRecs != NULL)
                        {
                                Symd->SymMac = (PSYM)((PUCHAR)Symd->SymRecs + Symd->SymSize);

                                Symd->TpiHdr = TPILoadTypeInfo (msf);
                                if (Symd->TpiHdr != NULL)
                                {
                                        return Symd;
                                }
                        }
                }

                free (Symd);
        }

        return NULL;
}




void GSIInit (PSYMD Symd)
{
        // Load GSI & PSGSI
        MsfReferenceStreamType (
                Symd->msf,
                Symd->dbi->snGSSyms,
                &Symd->gsi
                );
        MsfReferenceStreamType(
                Symd->msf,
                Symd->dbi->snPSSyms,
                &Symd->psi
                );

        // Parse GSI
        Symd->pGSHr = (uint8_t*)(Symd->gsi.Data + 1);
        Symd->pGSBuckets = (uint8_t*)(Symd->gsi.Data + 1) + Symd->gsi.Data->cbHr;
        Symd->nGSHrs = Symd->gsi.Data->cbHr / sizeof(HRFile);
        Symd->nGSBuckets = Symd->gsi.Data->cbBuckets / sizeof(ULONG);

        // parse PSGSI
        Symd->pgsiPSHash = (PGSIHashHdr)(Symd->psi.Data + 1);
        Symd->pPSHr = (uint8_t*)(Symd->pgsiPSHash + 1);
        Symd->pPSBuckets = (uint8_t*)(Symd->pgsiPSHash + 1) + Symd->pgsiPSHash->cbHr;
        Symd->nPSHrs = Symd->pgsiPSHash->cbHr / sizeof(HRFile);
        Symd->nPSBuckets = Symd->pgsiPSHash->cbBuckets / sizeof(ULONG);
        Symd->pPSAddrMap = (uint8_t*)(Symd->pgsiPSHash + 1) + Symd->psi.Data->cbSymHash;
        Symd->nPSAddrMap = Symd->psi.Data->cbAddrMap / sizeof(ULONG);
}

